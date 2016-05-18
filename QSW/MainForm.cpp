#include <QtConcurrentRun>
#include <QFuture>
#include <QTime>
#include <QStandardItemModel>
#include <QStringListModel>
#include <QDir>
#include <QMessageBox>
#include <QPropertyAnimation>

#include "MainForm.h"
#include "AboutForm.h"
#include "SettingsForm.h"
#include "SWModels.h"
#include "Defines.h"
#include "WovWidget.h"

MainForm::MainForm(QWidget* parent)
    : QMainWindow(parent)
{
    QTime m_time;
    m_time.start();

    setupUi(this);

    m_advancedFilterWidget = new AdvancedFilterWidget(page);
    gridLayout_4->addWidget(m_advancedFilterWidget, 0, 1, 2, 1);
    m_advancedFilterWidget->hide();

    m_enums = new SWEnums();
    m_sw = new SWObject(this);
    m_watcher = new SearchResultWatcher();
    connect(m_watcher, SIGNAL(finished()), this, SLOT(slotSearchResult()));

    m_sortedModel = new SpellListSortedModel(this);
    m_sortedModel->setDynamicSortFilter(true);
    SpellList->setModel(m_sortedModel);

    loadComboBoxes();
    detectLocale();
    createModeButton();
    initializeCompleter();

    mainToolBar->addSeparator();
    mainToolBar->addWidget(m_modeButton);
    mainToolBar->addSeparator();
    m_actionRegExp = mainToolBar->addAction(QIcon(":/qsw/resources/regExp.png"), "<font color=red>Off</font>");
    m_actionRegExp->setCheckable(true);
    mainToolBar->addSeparator();
    m_actionSettings = mainToolBar->addAction(QIcon(":/qsw/resources/cog.png"), "Settings");
    mainToolBar->addSeparator();
    m_actionWov = mainToolBar->addAction(QIcon(":/qsw/resources/wand.png"), "Wov");
    mainToolBar->addSeparator();
    m_actionAbout = mainToolBar->addAction(QIcon(":/qsw/resources/information.png"), "About");

    QAction* selectedAction = new QAction(this);
    selectedAction->setShortcut(QKeySequence::MoveToPreviousLine);
    connect(selectedAction, SIGNAL(triggered()), this, SLOT(slotPrevRow()));
    SpellList->addAction(selectedAction);

    selectedAction = new QAction(this);
    selectedAction->setShortcut(QKeySequence::MoveToNextLine);
    connect(selectedAction, SIGNAL(triggered()), this, SLOT(slotNextRow()));
    SpellList->addAction(selectedAction);

    connect(adFilterButton, SIGNAL(clicked()), this, SLOT(slotAdvancedFilter()));

    // List search connection
    connect(SpellList, SIGNAL(clicked(QModelIndex)), this, SLOT(slotSearchFromList(QModelIndex)));

    // Main search connections
    connect(findLine_e1, SIGNAL(returnPressed()), this, SLOT(slotButtonSearch()));
    connect(findLine_e3, SIGNAL(returnPressed()), this, SLOT(slotButtonSearch()));

    // Menu connections
    connect(m_actionAbout, SIGNAL(triggered()), this, SLOT(slotAbout()));

    // RegExp connection
    connect(m_actionRegExp, SIGNAL(triggered()), this, SLOT(slotRegExp()));

    // Settings form connection
    connect(m_actionSettings, SIGNAL(triggered()), this, SLOT(slotSettings()));

    // Wov form connection
    connect(m_actionWov, SIGNAL(triggered()), this, SLOT(slotWov()));

    // Filter search connections
    connect(comboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(slotFilterSearch()));
    connect(comboBox_2, SIGNAL(currentIndexChanged(int)), this, SLOT(slotFilterSearch()));
    connect(comboBox_3, SIGNAL(currentIndexChanged(int)), this, SLOT(slotFilterSearch()));
    connect(comboBox_4, SIGNAL(currentIndexChanged(int)), this, SLOT(slotFilterSearch()));
    connect(comboBox_5, SIGNAL(currentIndexChanged(int)), this, SLOT(slotFilterSearch()));

    // Search connection
    connect(this, SIGNAL(signalSearch(quint8)), this, SLOT(slotSearch(quint8)));

    connect(m_advancedFilterWidget->pushButton, SIGNAL(clicked()), this, SLOT(slotAdvancedApply()));

    connect(compareSpell_1, SIGNAL(returnPressed()), this, SLOT(slotCompareSearch()));
    connect(compareSpell_2, SIGNAL(returnPressed()), this, SLOT(slotCompareSearch()));

    connect(webView1, SIGNAL(anchorClicked(QUrl)), this, SLOT(slotLinkClicked(QUrl)));
    connect(webView2, SIGNAL(anchorClicked(QUrl)), this, SLOT(slotLinkClicked(QUrl)));
    connect(webView3, SIGNAL(anchorClicked(QUrl)), this, SLOT(slotLinkClicked(QUrl)));

    webView1->setHtml(QString("Load time: %0 ms").arg(m_time.elapsed()));

    // Load settings at end
    loadSettings();
}

MainForm::~MainForm()
{
    saveSettings();
}

void MainForm::slotSettings()
{
    SettingsForm settingsForm(this);
    settingsForm.exec();
}

void MainForm::slotAdvancedFilter()
{
    if (m_advancedFilterWidget->isVisible())
    {
        webView1->show();
        m_advancedFilterWidget->hide();
    }
    else
    {
        webView1->hide();
        m_advancedFilterWidget->show();
    }
}

void MainForm::slotAdvancedApply()
{
    emit signalSearch(3);
}

void MainForm::loadSettings()
{
    // Global
    setRegExp(QSW::settings().value("Global/RegExp", false).toBool());

    // Search and filters
    findLine_e1->setText(QSW::settings().value("Search/IdOrName", "").toString());
    findLine_e3->setText(QSW::settings().value("Search/Description", "").toString());
    comboBox->setCurrentIndex(QSW::settings().value("Search/SpellFamilyIndex", 0).toInt());
    comboBox_2->setCurrentIndex(QSW::settings().value("Search/EffectIndex", 0).toInt());
    comboBox_3->setCurrentIndex(QSW::settings().value("Search/AuraIndex", 0).toInt());
    comboBox_4->setCurrentIndex(QSW::settings().value("Search/TargetAIndex", 0).toInt());
    comboBox_5->setCurrentIndex(QSW::settings().value("Search/TargetBIndex", 0).toInt());

    if (!findLine_e1->text().isEmpty())
        slotButtonSearch();
}

void MainForm::saveSettings()
{
    // Global
    QSW::settings().setValue("Global/RegExp", isRegExp());

    // Search and filters
    QSW::settings().setValue("Search/IdOrName", findLine_e1->text());
    QSW::settings().setValue("Search/Description", findLine_e3->text());
    QSW::settings().setValue("Search/SpellFamilyIndex", comboBox->currentIndex());
    QSW::settings().setValue("Search/EffectIndex", comboBox_2->currentIndex());
    QSW::settings().setValue("Search/AuraIndex", comboBox_3->currentIndex());
    QSW::settings().setValue("Search/TargetAIndex", comboBox_4->currentIndex());
    QSW::settings().setValue("Search/TargetBIndex", comboBox_5->currentIndex());
}

void MainForm::slotPrevRow()
{
    SpellList->selectRow(SpellList->currentIndex().row() - 1);

    QVariant var = SpellList->model()->data(SpellList->model()->index(SpellList->currentIndex().row(), 0));
    m_sw->showInfo(Spell::getRecord(var.toInt(), true));
}

void MainForm::slotNextRow()
{
    SpellList->selectRow(SpellList->currentIndex().row() + 1);

    QVariant var = SpellList->model()->data(SpellList->model()->index(SpellList->currentIndex().row(), 0));
    m_sw->showInfo(Spell::getRecord(var.toInt(), true));
}

void MainForm::initializeCompleter()
{
    QSet<QString> names;

    for (quint32 i = 0; i < Spell::getHeader()->recordCount; ++i)
    {
        if (const Spell::entry* spellInfo = Spell::getRecord(i))
        {
            QString sName = spellInfo->name();
            if (names.find(sName) == names.end())
                names << sName;
        }
    }

    QCompleter* completer = new QCompleter(names.toList(), this);
    completer->setCaseSensitivity(Qt::CaseInsensitive);
    findLine_e1->setCompleter(completer);
}

void MainForm::createModeButton()
{
    QAction* actionShow = new QAction(QIcon(":/qsw/resources/application.png"), "Show", this);
    QAction* actionCompare = new QAction(QIcon(":/qsw/resources/application_tile_horizontal.png"), "Compare", this);

    connect(actionShow, SIGNAL(triggered()), this, SLOT(slotModeShow()));
    connect(actionCompare, SIGNAL(triggered()), this, SLOT(slotModeCompare()));

    m_modeButton = new QToolButton(this);
    m_modeButton->setText("Mode");
    m_modeButton->setIcon(actionShow->icon());
    m_modeButton->setPopupMode(QToolButton::InstantPopup);

    m_modeButton->addAction(actionShow);
    m_modeButton->addAction(actionCompare);
}

void MainForm::detectLocale()
{
    if (const Spell::entry* spellInfo = Spell::getRecord(1, true))
    {
        m_sw->setMetaEnum("LocalesDBC");
        for (quint8 i = 0; i < m_sw->getMetaEnum().keyCount(); ++i)
        {
            if (spellInfo->nameOffset[i])
            {
                QSW::Locale = i;
                QLabel* label = new QLabel;
                label->setText(QString("%0<b>DBC Locale: <font color=green>%1 </font><b>")
                    .arg(QChar(QChar::Nbsp), 2, QChar(QChar::Nbsp))
                    .arg(m_sw->getMetaEnum().valueToKey(m_sw->getMetaEnum().value(i))));
                mainToolBar->addWidget(label);
                break;
            }
        }
    }
}

void MainForm::slotLinkClicked(const QUrl &url)
{
    QWebEngineView* webView = static_cast<QWebEngineView*>(sender());

    qint32 browserId = webView->objectName().at(7).digitValue();
    qint32 id = url.toString().section('/', -1).toInt();

    switch (browserId)
    {
        case 1:
        {
            m_sw->showInfo(Spell::getRecord(id, true), browserId);
            break;
        }
        case 2:
        {
            qint32 id3 = webView3->url().toString().section('/', -1).toInt();
            m_sw->showInfo(Spell::getRecord(id, true), browserId);
            m_sw->showInfo(Spell::getRecord(id3, true), 3);
            m_sw->compare();
            break;
        }
        case 3:
        {
            qint32 id2 = webView2->url().toString().section('/', -1).toInt();
            m_sw->showInfo(Spell::getRecord(id, true), browserId);
            m_sw->showInfo(Spell::getRecord(id2, true), 2);
            m_sw->compare();
            break;
        }
        default: break;
    }
}

void MainForm::slotModeShow()
{
    m_modeButton->setIcon(m_modeButton->actions().at(0)->icon());
    stackedWidget->setCurrentIndex(0);
}

void MainForm::slotModeCompare()
{
    m_modeButton->setIcon(m_modeButton->actions().at(1)->icon());
    stackedWidget->setCurrentIndex(1);
}

void MainForm::loadComboBoxes()
{
    comboBox->clear();
    comboBox->setModel(new QStandardItemModel);
    comboBox->insertItem(0, "SpellFamilyName", 0);

    EnumIterator itr(m_enums->getSpellFamilies());
    quint32 i = 0;
    while (itr.hasNext())
    {
        ++i;
        itr.next();
        comboBox->insertItem(i, QString("(%0) %1")
            .arg(itr.key(), 3, 10, QChar('0'))
            .arg(itr.value()), itr.key());
    }

    comboBox_2->clear();
    comboBox_2->setModel(new QStandardItemModel);
    comboBox_2->insertItem(0, "Aura", 0);
    
    itr = EnumIterator(m_enums->getSpellAuras());
    i = 0;
    while (itr.hasNext())
    {
        ++i;
        itr.next();
        comboBox_2->insertItem(i, QString("(%0) %1")
            .arg(itr.key(), 3, 10, QChar('0'))
            .arg(itr.value()), itr.key());
    }

    comboBox_3->clear();
    comboBox_3->setModel(new QStandardItemModel);
    comboBox_3->insertItem(0, "Effect", 0);
    
    itr = EnumIterator(m_enums->getSpellEffects());
    i = 0;
    while (itr.hasNext())
    {
        ++i;
        itr.next();
        comboBox_3->insertItem(i, QString("(%0) %1")
            .arg(itr.key(), 3, 10, QChar('0'))
            .arg(itr.value()), itr.key());
    }

    comboBox_4->clear();
    comboBox_4->setModel(new QStandardItemModel);
    comboBox_4->insertItem(0, "Target A", 0);

    comboBox_5->clear();
    comboBox_5->setModel(new QStandardItemModel);
    comboBox_5->insertItem(0, "Target B", 0);

    itr = EnumIterator(m_enums->getTargets());
    i = 0;
    while (itr.hasNext())
    {
        ++i;
        itr.next();
        comboBox_4->insertItem(i, QString("(%0) %1")
            .arg(itr.key(), 3, 10, QChar('0'))
            .arg(itr.value()), itr.key());

        comboBox_5->insertItem(i, QString("(%0) %1")
            .arg(itr.key(), 3, 10, QChar('0'))
            .arg(itr.value()), itr.key());
    }
}

void MainForm::slotRegExp()
{
    if (isRegExp())
    {
        m_actionRegExp->setChecked(true);
        m_actionRegExp->setIcon(QIcon(":/qsw/resources/regExp.png"));
        m_actionRegExp->setText("<font color=green>On</font>");
    }
    else
    {
        m_actionRegExp->setChecked(false);
        m_actionRegExp->setIcon(QIcon(":/qsw/resources/regExp.png"));
        m_actionRegExp->setText("<font color=red>Off</font>");
    }

    m_sw->showInfo(Spell::getRecord(webView1->url().path().remove(0, 1).toInt(), true));

    bool compared[2] = { false, false };
    if (const Spell::entry* spellInfo = Spell::getRecord(webView2->url().path().remove(0, 1).toInt(), true))
    {
        m_sw->showInfo(spellInfo, 2);
        compared[0] = true;
    }

    if (const Spell::entry* spellInfo = Spell::getRecord(webView3->url().path().remove(0, 1).toInt(), true))
    {
        m_sw->showInfo(spellInfo, 3);
        compared[1] = true;
    }

    if (compared[0] || compared[1])
        m_sw->compare();
}

void MainForm::slotWov()
{
    WovWidget* wov = new WovWidget();
    wov->show();
}

void MainForm::slotAbout()
{
    AboutForm aboutView(this);
    aboutView.exec();
}

void MainForm::slotButtonSearch()
{
    emit signalSearch(0);
}

void MainForm::slotFilterSearch()
{
    emit signalSearch(1);
}

void MainForm::slotCompareSearch()
{
    if (!compareSpell_1->text().isEmpty() && !compareSpell_2->text().isEmpty())
    {
        m_sw->showInfo(Spell::getRecord(compareSpell_1->text().toInt(), true), 2);
        m_sw->showInfo(Spell::getRecord(compareSpell_2->text().toInt(), true), 3);
        m_sw->compare();
    }
}

void MainForm::slotSearch(quint8 type)
{
    SpellListSortedModel* smodel = static_cast<SpellListSortedModel*>(SpellList->model());
    SpellListModel* model = static_cast<SpellListModel*>(smodel->sourceModel());
    delete model;
    model = NULL;

    m_sw->setType(type);

    m_watcher->setFuture(QtConcurrent::run<EventList, SWObject>(m_sw, &SWObject::search));
}

void MainForm::slotSearchResult()
{
    SearchResultWatcher* watcher = (SearchResultWatcher*)QObject::sender();

    EventList eventList = watcher->future().result();
    for (EventList::iterator itr = eventList.begin(); itr != eventList.end(); ++itr)
        QApplication::postEvent(this, *itr);
}

void MainForm::slotSearchFromList(const QModelIndex &index)
{
    QVariant var = SpellList->model()->data(SpellList->model()->index(index.row(), 0));
    m_sw->showInfo(Spell::getRecord(var.toInt(), true));
}

bool MainForm::event(QEvent* ev)
{
    switch (Event::Events(ev->type()))
    {
    case Event::EVENT_SEND_MODEL:
        {
            Event* m_ev = (Event*)ev;
            m_sortedModel->sourceModel()->deleteLater();
            m_sortedModel->setSourceModel(m_ev->getValue(0).value<SpellListModel*>());
            SpellList->setColumnWidth(0, 40);
            SpellList->setColumnWidth(1, 150);
            return true;
        }
        break;
    case Event::EVENT_SEND_SPELL:
        {
            Event* m_ev = (Event*)ev;
            m_sw->showInfo(Spell::getRecord(m_ev->getValue(0).toUInt(), true));
            return true;
        }
        break;
    default:
        break;
    }

    return QWidget::event(ev);
}

AdvancedFilterWidget::AdvancedFilterWidget(QWidget* parent /* = NULL */)
    : QWidget(parent)
{
    setupUi(this);
    setAutoFillBackground(true);
}