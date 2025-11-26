// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include  "AbilitySystemInterface.h"
#include "Attributes/GGShieldSet.h"
#include "GGBaseCharacter.generated.h"

struct FOnAttributeChangeData;

UCLASS()
class UE5_WORKSHOP_API AGGBaseCharacter : public ACharacter, public  IAbilitySystemInterface
{
	GENERATED_BODY()


protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "GAS", meta = (AllowPrivateAccess = "true"))
	class UAbilitySystemComponent* AbilitySystemComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "GAS", meta = (AllowPrivateAccess = "true"))
	class UGGHealthSet*  HealthSet;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "GAS", meta = (AllowPrivateAccess = "true"))
	class UGGShieldSet* ShieldSet;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "GAS", meta = (AllowPrivateAccess = "true"))
	class UGGDamageSet*  InDamageSet;

	UPROPERTY(BlueprintReadOnly,EditDefaultsOnly, Category= "GAS")
	TArray<TSubclassOf<class UGGGameplayAbility>> DefaultAbilities;

	UPROPERTY(BlueprintReadOnly,EditDefaultsOnly, Category= "GAS")
	TArray<TSubclassOf<class UGameplayEffect>> DefaultEffects;
	

public:
	// Sets default values for this character's properties
	AGGBaseCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	

public:
	void InitializeAbilities();
	void InitializeGameEffects();
	virtual void PostInitializeComponents() override;
	
	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;

	virtual  void OnHealthAttributeChanged(const FOnAttributeChangeData& Data);
	virtual  void OnShieldAttributeChanged(const FOnAttributeChangeData& Data);
	virtual  void OnDamageAttributeChanged(const FOnAttributeChangeData& Data);

	UFUNCTION(BlueprintImplementableEvent, Category ="GAS")
	void OnHealthChanged(float OldValue, float NewValue);

	UFUNCTION(BlueprintImplementableEvent, Category ="GAS")
	void OnShieldChanged(float OldValue, float NewValue);

	UFUNCTION(BlueprintImplementableEvent, Category ="GAS")
	void OnDamageChanged(float OldValue, float NewValue);

	UFUNCTION(BlueprintCallable, Category= "GAS")
	void UpdateHealthAttribute(float newValue);
	
	UFUNCTION()
	virtual float TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;
};
