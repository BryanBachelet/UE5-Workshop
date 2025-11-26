// Fill out your copyright notice in the Description page of Project Settings.


#include "UGGHealthSet.h"

UGGHealthSet::UGGHealthSet()
{
	
}

void UGGHealthSet::ClampAttributeOnChange(const FGameplayAttribute& Attribute, float& NewValue) const
{
	if(Attribute == GetHealthAttribute())
	{
		NewValue  = FMath::Clamp(NewValue, 0.0f, GetMaxHealth());
	}
	
	
}
