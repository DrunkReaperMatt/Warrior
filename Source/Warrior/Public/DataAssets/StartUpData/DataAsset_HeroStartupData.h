// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DataAssets/StartUpData/DataAsset_StartupDatabase.h"
#include "WarriorTypes/WarriorStructTypes.h"
#include "DataAsset_HeroStartupData.generated.h"



/**
 * 
 */
UCLASS()
class WARRIOR_API UDataAsset_HeroStartupData : public UDataAsset_StartupDatabase
{
	GENERATED_BODY()

public:
	virtual void GiveToAbilitySystemComponent(UWarriorAbilitySystemComponent* InASCToGive, int32 ApplyLevel = 1) override;
	
private:
	UPROPERTY(EditDefaultsOnly, Category = "StartupData", meta = (TitleProperty = "InputTag"))
	TArray<FWarriorHeroAbilitySet> HeroStartUpAbilitySets;
};
