// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayEffectTypes.h"
#include "GameFramework/Pawn.h"
#include "GGBaseEnemy.generated.h"

UCLASS()
class UE5_WORKSHOP_API AGGBaseEnemy : public APawn
{
	GENERATED_BODY()


protected:
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "GAS", meta = (AllowPrivateAccess = "true"))
	class UAbilitySystemComponent* AbilitySystemComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "GAS", meta = (AllowPrivateAccess = "true"))
	class UGGHealthSet*  HealthSet;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "GAS", meta = (AllowPrivateAccess = "true"))
	class UGGDamageSet* InDamageSet;

	UPROPERTY(BlueprintReadOnly,EditDefaultsOnly, Category= "GAS")
	TArray<TSubclassOf<class UGGGameplayAbility>> DefaultAbilities;

	UPROPERTY(BlueprintReadOnly,EditDefaultsOnly, Category= "GAS")
	TArray<TSubclassOf<class UGameplayEffect>> DefaultEffects;

	
public:
	// Sets default values for this pawn's properties
	AGGBaseEnemy();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	void PostInitializeComponents();

public:
	void InitializeAbilities();
	void InitializeGameEffects();
	void OnHealthAttributeChanged(const FOnAttributeChangeData& Data);
	void OnInDamageAttributeChanged(const FOnAttributeChangeData& Data);

	UFUNCTION(BlueprintImplementableEvent, Category ="GAS")
	void OnHealthChanged(float OldValue, float NewValue);

	UFUNCTION(BlueprintImplementableEvent, Category ="GAS")
	void OnDamageChanged(float OldValue, float NewValue);
	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	
	UFUNCTION()
	virtual float TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;
};
