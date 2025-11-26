// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UGGBaseSet.h"
#include "GGDamageSet.generated.h"

/**
 * 
 */
UCLASS()
class UE5_WORKSHOP_API UGGDamageSet : public UGGBaseSet
{
	GENERATED_BODY()

public:
	UGGDamageSet();

	UPROPERTY(BlueprintReadOnly, Category = "Attributes", meta = (AllowPrivateAccess = true))
	FGameplayAttributeData InDamage;
	ATTRIBUTE_ACCESSORS(UGGDamageSet,InDamage);

protected:
	
	void ClampAttributeOnChange(const FGameplayAttribute& Attribute, float& NewValue) const override;
	
};
