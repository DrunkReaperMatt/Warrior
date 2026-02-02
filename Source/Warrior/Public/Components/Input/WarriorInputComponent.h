// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EnhancedInputComponent.h"
#include "DataAssets/Input/DataAsset_InputConfig.h"
#include "WarriorInputComponent.generated.h"

/**
 * 
 */
UCLASS()
class WARRIOR_API UWarriorInputComponent : public UEnhancedInputComponent
{
	GENERATED_BODY()

public:
	template<class UserObject, typename CallbackFunction>
	void BindNativeInputAction(const UDataAsset_InputConfig* InputConfig, const FGameplayTag& InputTag, ETriggerEvent TriggerEvent,
	                           UserObject* ContextObject, CallbackFunction Callback);

	template<class UserObject, typename CallbackFunction>
	void BindAbilityInputAction(const UDataAsset_InputConfig* InputConfig, UserObject* ContextObject, CallbackFunction InputPressedCallback, CallbackFunction InputReleasedCallback);

};

template<class UserObject, typename CallbackFunction>
inline void UWarriorInputComponent::BindNativeInputAction(const UDataAsset_InputConfig* InputConfig, const FGameplayTag& InputTag, ETriggerEvent TriggerEvent,
						   UserObject* ContextObject, CallbackFunction Callback)
{
	check(InputConfig);

	if (UInputAction* FoundAction = InputConfig->FindNativeInputActionByTag(InputTag))
	{
		BindAction(FoundAction, TriggerEvent, ContextObject, Callback);
	}
			
}

template <class UserObject, typename CallbackFunction>
void UWarriorInputComponent::BindAbilityInputAction(const UDataAsset_InputConfig* InputConfig,
	UserObject* ContextObject, CallbackFunction InputPressedCallback, CallbackFunction InputReleasedCallback)
{
	check(InputConfig);

	for (const FWarriorInputActionConfig& AbilityInputActionConfig : InputConfig->AbilityInputActions)
	{
		if (AbilityInputActionConfig.IsValid())
		{
			BindAction(AbilityInputActionConfig.InputAction, ETriggerEvent::Started, ContextObject, InputPressedCallback, AbilityInputActionConfig.InputTag);
			BindAction(AbilityInputActionConfig.InputAction, ETriggerEvent::Completed, ContextObject, InputReleasedCallback, AbilityInputActionConfig.InputTag);
		}
	}
}
