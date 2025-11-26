// Fill out your copyright notice in the Description page of Project Settings.


#include "GGDamageSet.h"

UGGDamageSet::UGGDamageSet()
{
}

void UGGDamageSet::ClampAttributeOnChange(const FGameplayAttribute& Attribute, float& NewValue) const
{
	if(Attribute == GetInDamageAttribute())
	{
		NewValue  = FMath::Clamp(NewValue, 0.0f, INFINITY);
	}
}
