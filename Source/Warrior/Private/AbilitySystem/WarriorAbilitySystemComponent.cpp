// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/WarriorAbilitySystemComponent.h"

#include "WarriorTypes/WarriorStructTypes.h"
#include "AbilitySystem/Abilities/WarriorHeroGameplayAbility.h"

void UWarriorAbilitySystemComponent::OnAbilityInputPressed(const FGameplayTag& InputTag)
{
	if (!InputTag.IsValid())
	{
		return;
	}

	for (const FGameplayAbilitySpec& AbilitySpec : GetActivatableAbilities())
	{
		if (!AbilitySpec.GetDynamicSpecSourceTags().HasTagExact(InputTag))
		{
			continue;
		}

		TryActivateAbility(AbilitySpec.Handle);
	}
}

void UWarriorAbilitySystemComponent::OnAbilityInputReleased(const FGameplayTag& InputTag)
{
}

void UWarriorAbilitySystemComponent::GrantHeroWeaponAbilities(
	TArray<FWarriorHeroAbilitySet> DefaultWeaponAbilities, int32 ApplyLevel, TArray<FGameplayAbilitySpecHandle>&
	OutGrantedAbilitySpecHandles)
{
	if (DefaultWeaponAbilities.IsEmpty())
	{
		return;
	}

	for (FWarriorHeroAbilitySet& AbilitySet : DefaultWeaponAbilities)
	{
		if (!AbilitySet.IsValid())
		{
			continue;
		}
		
		FGameplayAbilitySpec AbilitySpec(AbilitySet.AbilityToGrant);
		AbilitySpec.SourceObject = GetAvatarActor();
		AbilitySpec.Level = ApplyLevel;
		AbilitySpec.GetDynamicSpecSourceTags().AddTag(AbilitySet.InputTag);
		
		OutGrantedAbilitySpecHandles.AddUnique(GiveAbility(AbilitySpec));
	}
}

void UWarriorAbilitySystemComponent::RemoveHeroWeaponAbilities(
	TArray<FGameplayAbilitySpecHandle>& AbilitySpecHandlesToRemove)
{
	if (AbilitySpecHandlesToRemove.IsEmpty())
	{
		return;
	}

	for (FGameplayAbilitySpecHandle& AbilitySpec : AbilitySpecHandlesToRemove)
	{
		if (AbilitySpec.IsValid())
		{
			ClearAbility(AbilitySpec);
		}
	}

	AbilitySpecHandlesToRemove.Empty();
}
