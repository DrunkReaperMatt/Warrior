// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimInstances/Hero/WarriorHeroLinkedAnimLayer.h"

#include "AnimInstances/Hero/WarriorHeroAnimInstance.h"

UWarriorHeroAnimInstance* UWarriorHeroLinkedAnimLayer::GetHeroAnimInstance() const
{
	return CastChecked<UWarriorHeroAnimInstance>( GetOwningComponent()->GetAnimInstance());
}
