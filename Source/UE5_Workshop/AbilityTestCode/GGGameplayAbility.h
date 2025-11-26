// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "GGGameplayAbility.generated.h"

UENUM()
enum class EAbilityInputID : uint8
{
	None,
	Confirm,
	Cancel,
	FireAbility
};


UCLASS()
class UE5_WORKSHOP_API UGGGameplayAbility : public UGameplayAbility
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, Category = "Ability")
	EAbilityInputID AbilityInputID{EAbilityInputID::None};

public:
	EAbilityInputID GetAbilityInputID() { return AbilityInputID; }
};
