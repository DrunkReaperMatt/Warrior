// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PawnExtensionComponentBase.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class WARRIOR_API UPawnExtensionComponentBase : public UActorComponent
{
	GENERATED_BODY()

protected:
	template <class T>
	T* GetOwningPawn() const
	{
		static_assert(TPointerIsConvertibleFromTo<T, APawn>::Value, "GetOwningPawn must be convertible to a Pawn");
		return CastChecked<T>(GetOwner());
	}

	template <class T>
	T* GetOwningController() const
	{
		static_assert(TPointerIsConvertibleFromTo<T, AController>::Value, "GetOwningController must be convertible to a Controller");
		return GetOwningPawn<APawn>()->GetController<T>();
	}

	APawn* GetOwningPawn() const
	{
		return GetOwningPawn<APawn>();
	}
};
