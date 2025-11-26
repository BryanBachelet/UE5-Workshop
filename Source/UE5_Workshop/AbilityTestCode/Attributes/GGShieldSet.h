// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UGGBaseSet.h"
#include "GGShieldSet.generated.h"

/**
 * 
 */
UCLASS()
class UE5_WORKSHOP_API UGGShieldSet : public UGGBaseSet
{
	GENERATED_BODY()

public:
	UGGShieldSet();

	UPROPERTY(BlueprintReadOnly, Category = "Attributes", meta = (AllowPrivateAccess = true))
	FGameplayAttributeData Shield;
	ATTRIBUTE_ACCESSORS(UGGShieldSet,Shield);

	UPROPERTY(BlueprintReadOnly, Category = "Attributes", meta = (AllowPrivateAccess = true))
	FGameplayAttributeData MaxShield;
	ATTRIBUTE_ACCESSORS(UGGShieldSet, MaxShield);

protected:
	void ClampAttributeOnChange(const FGameplayAttribute& Attribute, float& NewValue) const override;
	
};
