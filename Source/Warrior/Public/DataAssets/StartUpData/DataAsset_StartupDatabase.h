// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "DataAsset_StartupDatabase.generated.h"

class UWarriorAbilitySystemComponent;
class UWarriorGameplayAbility;
class UGameplayEffect;
/**
 * 
 */
UCLASS()
class WARRIOR_API UDataAsset_StartupDatabase : public UDataAsset
{
	GENERATED_BODY()

public:
	virtual void GiveToAbilitySystemComponent(UWarriorAbilitySystemComponent* InASCToGive, int32 ApplyLevel = 1);
	
protected:
	UPROPERTY(EditAnywhere, Category = "StartupData")
	TArray<TSubclassOf<UWarriorGameplayAbility>> ActivateOnGivenAbilities;

	UPROPERTY(EditAnywhere, Category = "StartupData")
	TArray<TSubclassOf<UWarriorGameplayAbility>> ReactiveAbilities;

	UPROPERTY(EditAnywhere, Category = "StartupData")
	TArray<TSubclassOf<UGameplayEffect>> StartupGameplayEffects;

	void GrantAbilities(const TArray<TSubclassOf<UWarriorGameplayAbility>>& AbilitiesToGive, UWarriorAbilitySystemComponent* InASCToGive, int32 ApplyLevel = 1);
};
