#include "DBCStructure.h"
#include "DBCStores.h"

SpellAuraOptionsEntry const* SpellEntry::getSpellAuraOptions() const
{
    return SpellAuraOptionsId ? sSpellAuraOptionsStore.LookupEntry(SpellAuraOptionsId) : NULL;
}

SpellAuraRestrictionsEntry const* SpellEntry::getSpellAuraRestrictions() const
{
    return SpellAuraRestrictionsId ? sSpellAuraRestrictionsStore.LookupEntry(SpellAuraRestrictionsId) : NULL;
}

SpellCastingRequirementsEntry const* SpellEntry::getSpellCastingRequirements() const
{
    return SpellCastingRequirementsId ? sSpellCastingRequirementsStore.LookupEntry(SpellCastingRequirementsId) : NULL;
}

SpellCategoriesEntry const* SpellEntry::getSpellCategories() const
{
    return SpellCategoriesId ? sSpellCategoriesStore.LookupEntry(SpellCategoriesId) : NULL;
}

SpellClassOptionsEntry const* SpellEntry::getSpellClassOptions() const
{
    return SpellClassOptionsId ? sSpellClassOptionsStore.LookupEntry(SpellClassOptionsId) : NULL;
}

SpellCooldownsEntry const* SpellEntry::getSpellCooldowns() const
{
    return SpellCooldownsId ? sSpellCooldownsStore.LookupEntry(SpellCooldownsId) : NULL;
}

SpellEffectEntry const* SpellEntry::getSpellEffect(quint8 eff) const
{
    return GetSpellEffectEntry(Id, eff);
}

SpellEquippedItemsEntry const* SpellEntry::getSpellEquippedItems() const
{
    return SpellEquippedItemsId ? sSpellEquippedItemsStore.LookupEntry(SpellEquippedItemsId) : NULL;
}

SpellInterruptsEntry const* SpellEntry::getSpellInterrupts() const
{
    return SpellInterruptsId ? sSpellInterruptsStore.LookupEntry(SpellInterruptsId) : NULL;
}

SpellLevelsEntry const* SpellEntry::getSpellLevels() const
{
    return SpellLevelsId ? sSpellLevelsStore.LookupEntry(SpellLevelsId) : NULL;
}

SpellPowerEntry const* SpellEntry::getSpellPower() const
{
    return SpellPowerId ? sSpellPowerStore.LookupEntry(SpellPowerId) : NULL;
}

SpellReagentsEntry const* SpellEntry::getSpellReagents() const
{
    return SpellReagentsId ? sSpellReagentsStore.LookupEntry(SpellReagentsId) : NULL;
}

SpellScalingEntry const* SpellEntry::getSpellScaling() const
{
    return SpellScalingId ? sSpellScalingStore.LookupEntry(SpellScalingId) : NULL;
}

SpellShapeshiftEntry const* SpellEntry::getSpellShapeshift() const
{
    return SpellShapeshiftId ? sSpellShapeshiftStore.LookupEntry(SpellShapeshiftId) : NULL;
}

SpellTargetRestrictionsEntry const* SpellEntry::getSpellTargetRestrictions() const
{
    return SpellTargetRestrictionsId ? sSpellTargetRestrictionsStore.LookupEntry(SpellTargetRestrictionsId) : NULL;
}

SpellTotemsEntry const* SpellEntry::getSpellTotems() const
{
    return SpellTotemsId ? sSpellTotemsStore.LookupEntry(SpellTotemsId) : NULL;
}

/**
    SpellAuraOptions methods
 */

quint32 SpellEntry::getStackAmount() const
{
    SpellAuraOptionsEntry const* aura = getSpellAuraOptions();
    return aura ? aura->StackAmount : 0;
}

quint32 SpellEntry::getProcCharges() const
{
    SpellAuraOptionsEntry const* aura = getSpellAuraOptions();
    return aura ? aura->ProcCharges : 0;
}

quint32 SpellEntry::getProcChance() const
{
    SpellAuraOptionsEntry const* aura = getSpellAuraOptions();
    return aura ? aura->ProcChance : 0;
}

quint32 SpellEntry::getProcFlags() const
{
    SpellAuraOptionsEntry const* aura = getSpellAuraOptions();
    return aura ? aura->ProcFlags : 0;
}

/**
    SpellAuraRestrictions methods
 */

quint32 SpellEntry::getCasterAuraState() const
{
    SpellAuraRestrictionsEntry const* aura = getSpellAuraRestrictions();
    return aura ? aura->CasterAuraState : 0;
}

quint32 SpellEntry::getTargetAuraState() const
{
    SpellAuraRestrictionsEntry const* aura = getSpellAuraRestrictions();
    return aura ? aura->TargetAuraState : 0;
}

quint32 SpellEntry::getCasterAuraStateNot() const
{
    SpellAuraRestrictionsEntry const* aura = getSpellAuraRestrictions();
    return aura ? aura->CasterAuraStateNot : 0;
}

quint32 SpellEntry::getTargetAuraStateNot() const
{
    SpellAuraRestrictionsEntry const* aura = getSpellAuraRestrictions();
    return aura ? aura->TargetAuraStateNot : 0;
}

quint32 SpellEntry::getCasterAuraSpell() const
{
    SpellAuraRestrictionsEntry const* aura = getSpellAuraRestrictions();
    return aura ? aura->CasterAuraSpell : 0;
}

quint32 SpellEntry::getTargetAuraSpell() const
{
    SpellAuraRestrictionsEntry const* aura = getSpellAuraRestrictions();
    return aura ? aura->TargetAuraSpell : 0;
}

quint32 SpellEntry::getExcludeCasterAuraSpell() const
{
    SpellAuraRestrictionsEntry const* aura = getSpellAuraRestrictions();
    return aura ? aura->ExcludeCasterAuraSpell : 0;
}

quint32 SpellEntry::getExcludeTargetAuraSpell() const
{
    SpellAuraRestrictionsEntry const* aura = getSpellAuraRestrictions();
    return aura ? aura->ExcludeTargetAuraSpell : 0;
}

/**
    SpellCastingRequirements methods
 */

quint32 SpellEntry::getFacingCasterFlags() const
{
    SpellCastingRequirementsEntry const* castReq = getSpellCastingRequirements();
    return castReq ? castReq->FacingCasterFlags : -1;
}

qint32 SpellEntry::getAreaGroupId() const
{
    SpellCastingRequirementsEntry const* castReq = getSpellCastingRequirements();
    return castReq ? castReq->AreaGroupId : -1;
}

quint32 SpellEntry::getRequiresSpellFocus() const
{
    SpellCastingRequirementsEntry const* castReq = getSpellCastingRequirements();
    return castReq ? castReq->RequiresSpellFocus : 0;
}

/**
    SpellCategories methods
 */

quint32 SpellEntry::getCategory() const
{
    SpellCategoriesEntry const* cat = getSpellCategories();
    return cat ? cat->Category : 0;
}

quint32 SpellEntry::getDmgClass() const
{
    SpellCategoriesEntry const* cat = getSpellCategories();
    return cat ? cat->DmgClass : 0;
}

quint32 SpellEntry::getDispel() const
{
    SpellCategoriesEntry const* cat = getSpellCategories();
    return cat ? cat->Dispel : 0;
}

quint32 SpellEntry::getMechanic() const
{
    SpellCategoriesEntry const* cat = getSpellCategories();
    return cat ? cat->Mechanic : 0;
}

quint32 SpellEntry::getPreventionType() const
{
    SpellCategoriesEntry const* cat = getSpellCategories();
    return cat ? cat->PreventionType : 0;
}

quint32 SpellEntry::getStartRecoveryCategory() const
{
    SpellCategoriesEntry const* cat = getSpellCategories();
    return cat ? cat->StartRecoveryCategory : 0;
}

/**
    SpellClassOptions methods
 */

quint32 SpellEntry::getSpellFamilyName() const
{
    SpellClassOptionsEntry const* classOpt = getSpellClassOptions();
    return classOpt ? classOpt->SpellFamilyName : 0;
}

uarray3 SpellEntry::getSpellFamilyFlags() const
{
    SpellClassOptionsEntry const* option = getSpellClassOptions();
    return option ? option->SpellFamilyFlags : uarray3();
}

quint32 SpellEntry::getModalNextSpell() const
{
    SpellClassOptionsEntry const* option = getSpellClassOptions();
    return option ? option->ModalNextSpell : 0;
}

/**
    SpellCooldowns methods
 */

quint32 SpellEntry::getStartRecoveryTime() const
{
    SpellCooldownsEntry const* cd = getSpellCooldowns();
    return cd ? cd->StartRecoveryTime : 0;
}

quint32 SpellEntry::getRecoveryTime() const
{
    SpellCooldownsEntry const* cd = getSpellCooldowns();
    return cd ? cd->RecoveryTime : 0;
}

quint32 SpellEntry::getCategoryRecoveryTime() const
{
    SpellCooldownsEntry const* cd = getSpellCooldowns();
    return cd ? cd->CategoryRecoveryTime : 0;
}

/**
    SpellEquippedItems methods
 */

qint32 SpellEntry::getEquippedItemClass() const
{
    SpellEquippedItemsEntry const* items = getSpellEquippedItems();
    return items ? items->EquippedItemClass : -1;
}

qint32 SpellEntry::getEquippedItemSubClassMask() const
{
    SpellEquippedItemsEntry const* items = getSpellEquippedItems();
    return items ? items->EquippedItemSubClassMask : -1;
}

qint32 SpellEntry::getEquippedItemInventoryTypeMask() const
{
    SpellEquippedItemsEntry const* items = getSpellEquippedItems();
    return items ? items->EquippedItemInventoryTypeMask : -1;
}

/**
    SpellInterrupts methods
 */

quint32 SpellEntry::getInterruptFlags() const
{
    SpellInterruptsEntry const* interrupt = getSpellInterrupts();
    return interrupt ? interrupt->InterruptFlags : 0;
}

quint32 SpellEntry::getAuraInterruptFlags() const
{
    SpellInterruptsEntry const* interrupt = getSpellInterrupts();
    return interrupt ? interrupt->AuraInterruptFlags : 0;
}

quint32 SpellEntry::getChannelInterruptFlags() const
{
    SpellInterruptsEntry const* interrupt = getSpellInterrupts();
    return interrupt ? interrupt->ChannelInterruptFlags : 0;
}

/**
    SpellLevels methods
 */

quint32 SpellEntry::getBaseLevel() const
{
    SpellLevelsEntry const* levels = getSpellLevels();
    return levels ? levels->BaseLevel : 0;
}

quint32 SpellEntry::getMaxLevel() const
{
    SpellLevelsEntry const* levels = getSpellLevels();
    return levels ? levels->MaxLevel : 0;
}

quint32 SpellEntry::getSpellLevel() const
{
    SpellLevelsEntry const* levels = getSpellLevels();
    return levels ? levels->SpellLevel : 0;
}

/**
    SpellPower methods
 */

quint32 SpellEntry::getManaCost() const
{
    SpellPowerEntry const* power = getSpellPower();
    return power ? power->ManaCost : 0;
}

quint32 SpellEntry::getManaCostPercentage() const
{
    SpellPowerEntry const* power = getSpellPower();
    return power ? power->ManaCostPercentage : 0;
}

quint32 SpellEntry::getManaPerSecond() const
{
    SpellPowerEntry const* power = getSpellPower();
    return power ? power->ManaPerSecond : 0;
}

quint32 SpellEntry::getManaCostPerLevel() const
{
    SpellPowerEntry const* power = getSpellPower();
    return power ? power->ManaCostPerlevel : 0;
}

/**
    SpellShapeshift methods
 */

uarray2 SpellEntry::getStances() const
{
    SpellShapeshiftEntry const* ss = getSpellShapeshift();
    return ss ? ss->Stances : uarray2();
}

uarray2 SpellEntry::getStancesNot() const
{
    SpellShapeshiftEntry const* ss = getSpellShapeshift();
    return ss ? ss->StancesNot : uarray2();
}

quint32 SpellEntry::getStanceBarOrder() const
{
    SpellShapeshiftEntry const* ss = getSpellShapeshift();
    return ss ? ss->StanceBarOrder : 0;
}

/**
    SpellTargetRestrictions methods
 */

quint32 SpellEntry::getTargets() const
{
    SpellTargetRestrictionsEntry const* target = getSpellTargetRestrictions();
    return target ? target->Targets : 0;
}

quint32 SpellEntry::getTargetCreatureType() const
{
    SpellTargetRestrictionsEntry const* target = getSpellTargetRestrictions();
    return target ? target->TargetCreatureType : 0;
}

quint32 SpellEntry::getMaxAffectedTargets() const
{
    SpellTargetRestrictionsEntry const* target = getSpellTargetRestrictions();
    return target ? target->MaxAffectedTargets : 0;
}

quint32 SpellEntry::getMaxTargetLevel() const
{
    SpellTargetRestrictionsEntry const* target = getSpellTargetRestrictions();
    return target ? target->MaxTargetLevel : 0;
}

/**
    SpellEffect methods
 */

quint32 SpellEntry::getEffect(quint8 index) const
{
    SpellEffectEntry const* effect = getSpellEffect(index);
    return effect ? effect->Effect : 0;
}

float SpellEntry::getEffectValueMultiplier(quint8 index) const
{
    SpellEffectEntry const* effect = getSpellEffect(index);
    return effect ? effect->EffectValueMultiplier : 0.0f;
}

quint32 SpellEntry::getEffectApplyAuraName(quint8 index) const
{
    SpellEffectEntry const* effect = getSpellEffect(index);
    return effect ? effect->EffectApplyAuraName : 0;
}

quint32 SpellEntry::getEffectAmplitude(quint8 index) const
{
    SpellEffectEntry const* effect = getSpellEffect(index);
    return effect ? effect->EffectAmplitude : 0;
}

qint32 SpellEntry::getEffectBasePoints(quint8 index) const
{
    SpellEffectEntry const* effect = getSpellEffect(index);
    return effect ? effect->EffectBasePoints : 0;
}

float SpellEntry::getEffectBonusCoefficient(quint8 index) const
{
    SpellEffectEntry const* effect = getSpellEffect(index);
    return effect ? effect->EffectBonusCoefficient : 0;
}

float SpellEntry::getEffectDamageMultiplier(quint8 index) const
{
    SpellEffectEntry const* effect = getSpellEffect(index);
    return effect ? effect->EffectDamageMultiplier : 0;
}

quint32 SpellEntry::getEffectChainTarget(quint8 index) const
{
    SpellEffectEntry const* effect = getSpellEffect(index);
    return effect ? effect->EffectChainTarget : 0;
}

qint32 SpellEntry::getEffectDieSides(quint8 index) const
{
    SpellEffectEntry const* effect = getSpellEffect(index);
    return effect ? effect->EffectDieSides : 0;
}

quint32 SpellEntry::getEffectItemType(quint8 index) const
{
    SpellEffectEntry const* effect = getSpellEffect(index);
    return effect ? effect->EffectItemType : 0;
}

quint32 SpellEntry::getEffectMechanic(quint8 index) const
{
    SpellEffectEntry const* effect = getSpellEffect(index);
    return effect ? effect->EffectMechanic : 0;
}

qint32 SpellEntry::getEffectMiscValue(quint8 index) const
{
    SpellEffectEntry const* effect = getSpellEffect(index);
    return effect ? effect->EffectMiscValue : 0;
}

qint32 SpellEntry::getEffectMiscValueB(quint8 index) const
{
    SpellEffectEntry const* effect = getSpellEffect(index);
    return effect ? effect->EffectMiscValueB : 0;
}

float SpellEntry::getEffectPointsPerComboPoint(quint8 index) const
{
    SpellEffectEntry const* effect = getSpellEffect(index);
    return effect ? effect->EffectPointsPerComboPoint : 0.0f;
}

quint32 SpellEntry::getEffectRadiusIndex(quint8 index) const
{
    SpellEffectEntry const* effect = getSpellEffect(index);
    return effect ? effect->EffectRadiusIndex : 0;
}

quint32 SpellEntry::getEffectRadiusMaxIndex(quint8 index) const
{
    SpellEffectEntry const* effect = getSpellEffect(index);
    return effect ? effect->EffectRadiusMaxIndex : 0;
}

float SpellEntry::getEffectRealPointsPerLevel(quint8 index) const
{
    SpellEffectEntry const* effect = getSpellEffect(index);
    return effect ? effect->EffectRealPointsPerLevel : 0.0f;
}

uarray3 SpellEntry::getEffectSpellClassMask(quint8 index) const
{
    SpellEffectEntry const* effect = getSpellEffect(index);
    return effect ? effect->EffectSpellClassMask : uarray3();
}

quint32 SpellEntry::getEffectTriggerSpell(quint8 index) const
{
    SpellEffectEntry const* effect = getSpellEffect(index);
    return effect ? effect->EffectTriggerSpell : 0;
}

quint32 SpellEntry::getEffectImplicitTargetA(quint8 index) const
{
    SpellEffectEntry const* effect = getSpellEffect(index);
    return effect ? effect->EffectImplicitTargetA : 0;
}

quint32 SpellEntry::getEffectImplicitTargetB(quint8 index) const
{
    SpellEffectEntry const* effect = getSpellEffect(index);
    return effect ? effect->EffectImplicitTargetB : 0;
}

quint32 SpellEntry::getEffectSpellId(quint8 index) const
{
    SpellEffectEntry const* effect = getSpellEffect(index);
    return effect ? effect->EffectSpellId : 0;
}

quint32 SpellEntry::getEffectIndex(quint8 index) const
{
    SpellEffectEntry const* effect = getSpellEffect(index);
    return effect ? effect->EffectIndex : 0;
}