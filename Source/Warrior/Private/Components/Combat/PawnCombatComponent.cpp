// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/Combat/PawnCombatComponent.h"

#include "WarriorDebugHelper.h"
#include "Components/BoxComponent.h"
#include "Items/Weapons/WarriorWeaponBase.h"

void UPawnCombatComponent::RegisterSpawnedWeapon(FGameplayTag WeaponTagToRegister, AWarriorWeaponBase* WeaponToRegister,
                                                 bool bRegisterAsEquipped)
{
	checkf(!CharacterCarriedWeaponMap.Contains(WeaponTagToRegister), TEXT("Gameplay Tag '%s' already exists in Map"), *WeaponTagToRegister.ToString());
	check(WeaponToRegister);

	CharacterCarriedWeaponMap.Emplace(WeaponTagToRegister, WeaponToRegister);

	WeaponToRegister->OnWeaponHitTarget.BindUObject(this, &UPawnCombatComponent::OnHitTargetActor);
	WeaponToRegister->OnWeaponPulledFromTarget.BindUObject(this, &UPawnCombatComponent::OnPulledTargetActor);
	
	if (bRegisterAsEquipped)
	{
		CurrentEquippedWeaponTag = WeaponTagToRegister;
	}
}

AWarriorWeaponBase* UPawnCombatComponent::GetCharacterCarriedWeaponByTag(FGameplayTag WeaponTagToGet) const
{
	if (CharacterCarriedWeaponMap.Contains(WeaponTagToGet))
	{
		if (AWarriorWeaponBase* const* FoundWeapon = CharacterCarriedWeaponMap.Find(WeaponTagToGet))
		{
			return *FoundWeapon;
		}
	}

	return nullptr;
}

AWarriorWeaponBase* UPawnCombatComponent::GetCharacterCurrentEquippedWeapon() const
{
	if (!CurrentEquippedWeaponTag.IsValid())
	{
		return nullptr;
	}

	return GetCharacterCarriedWeaponByTag(CurrentEquippedWeaponTag);
}

void UPawnCombatComponent::ToggleWeaponCollision(bool bShouldEnable, EToggleDamageType ToggleDamageType)
{
	switch (ToggleDamageType)
	{
	case EToggleDamageType::CurrentEquippedWeapon:
		AWarriorWeaponBase* WeaponToToggle = GetCharacterCurrentEquippedWeapon();

		check(WeaponToToggle)

		if (bShouldEnable)
		{
			WeaponToToggle->GetWeaponCollisionBox()->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
		}
		else
		{
			WeaponToToggle->GetWeaponCollisionBox()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
			OverlappedActors.Empty();
		}
		break;
	}

	//TODO - Handle body collision box
}

void UPawnCombatComponent::OnHitTargetActor(AActor* HitActor)
{
}

void UPawnCombatComponent::OnPulledTargetActor(AActor* PulledActor)
{
}
