// Fill out your copyright notice in the Description page of Project Settings.


#include "GGShieldSet.h"

UGGShieldSet::UGGShieldSet()
{
}

void UGGShieldSet::ClampAttributeOnChange(const FGameplayAttribute& Attribute, float& NewValue) const
{
	if(Attribute == GetShieldAttribute())
	{
		NewValue  = FMath::Clamp(NewValue, 0.0f, GetMaxShield());
	}
}
