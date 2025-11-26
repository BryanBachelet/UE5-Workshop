// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UGGBaseSet.h"
#include "UGGHealthSet.generated.h"

/**
 * 
 */
UCLASS()
class UE5_WORKSHOP_API UGGHealthSet : public UGGBaseSet
{
	GENERATED_BODY()

public:
	UGGHealthSet();

	UPROPERTY(BlueprintReadWrite, Category = "Attributes", meta = (AllowPrivateAccess = true))
	FGameplayAttributeData Health;
	ATTRIBUTE_ACCESSORS(UGGHealthSet,Health);

	UPROPERTY(BlueprintReadWrite, Category = "Attributes", meta = (AllowPrivateAccess = true))
	FGameplayAttributeData MaxHealth;
	ATTRIBUTE_ACCESSORS(UGGHealthSet, MaxHealth);

protected:

	 void ClampAttributeOnChange(const FGameplayAttribute& Attribute, float& NewValue) const override;
};
