// Fill out your copyright notice in the Description page of Project Settings.


#include "GGBaseCharacter.h"

#include "AbilitySystemComponent.h"
#include "GGGameplayAbility.h"
#include "Attributes/GGDamageSet.h"
#include "Attributes/GGShieldSet.h"
#include "Attributes/UGGHealthSet.h"
#include "Kismet/GameplayStatics.h"


// Sets default values
AGGBaseCharacter::AGGBaseCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	AbilitySystemComponent = CreateDefaultSubobject<UAbilitySystemComponent>("AbilitySystemComp");
	HealthSet = CreateDefaultSubobject<UGGHealthSet>("HealthSet");
	ShieldSet = CreateDefaultSubobject<UGGShieldSet>("ShieldSet");
	InDamageSet = CreateDefaultSubobject<UGGDamageSet>("InDamageSet");
}

// Called when the game starts or when spawned
void AGGBaseCharacter::BeginPlay()
{
	Super::BeginPlay();

	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(HealthSet->GetHealthAttribute()).AddUObject(
		this, &AGGBaseCharacter::OnHealthAttributeChanged);
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(ShieldSet->GetShieldAttribute()).AddUObject(
		this, &AGGBaseCharacter::OnShieldAttributeChanged);
}


void AGGBaseCharacter::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	if (!AbilitySystemComponent)
		return;

	AbilitySystemComponent->InitAbilityActorInfo(this, this);

	InitializeAbilities();
	InitializeGameEffects();
}

void AGGBaseCharacter::InitializeAbilities()
{
	if (!HasAuthority() || !AbilitySystemComponent)
		return;

	for (TSubclassOf<UGGGameplayAbility>& Ability : DefaultAbilities)
	{
		FGameplayAbilitySpecHandle SpecHandle =
			AbilitySystemComponent->GiveAbility(
				FGameplayAbilitySpec(Ability, 1, static_cast<int>(Ability.GetDefaultObject()->GetAbilityInputID()),
				                     this));
	}
}

void AGGBaseCharacter::InitializeGameEffects()
{
	if (!AbilitySystemComponent)
		return;

	FGameplayEffectContextHandle EffectContext = AbilitySystemComponent->MakeEffectContext();
	EffectContext.AddSourceObject(this);

	for (TSubclassOf<UGameplayEffect>& effect : DefaultEffects)
	{
		FGameplayEffectSpecHandle SpecHandle = AbilitySystemComponent->MakeOutgoingSpec(effect, 1, EffectContext);
		if (SpecHandle.IsValid())
		{
			FActiveGameplayEffectHandle GEHandle = AbilitySystemComponent->ApplyGameplayEffectSpecToSelf(
				*SpecHandle.Data.Get());
		}
	}
}


// Called every frame
void AGGBaseCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void AGGBaseCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

UAbilitySystemComponent* AGGBaseCharacter::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

void AGGBaseCharacter::OnHealthAttributeChanged(const FOnAttributeChangeData& Data)
{
	OnHealthChanged(Data.OldValue, Data.NewValue);
}

void AGGBaseCharacter::OnShieldAttributeChanged(const FOnAttributeChangeData& Data)
{
	OnShieldChanged(Data.OldValue, Data.NewValue);
}

void AGGBaseCharacter::OnDamageAttributeChanged(const FOnAttributeChangeData& Data)
{
	float damage = InDamageSet->GetInDamage();

	if (ShieldSet)
	{
		float shieldValue = ShieldSet->GetShield();
		damage -= shieldValue;
		ShieldSet->SetShield(shieldValue - damage);
	}
	float healthValue = HealthSet->GetHealth();
	if (damage > 0)
	{
		HealthSet->SetHealth(healthValue - damage);
	}

	
	InDamageSet->SetInDamage(0);

	OnDamageChanged(Data.OldValue, Data.NewValue);
}

void AGGBaseCharacter::UpdateHealthAttribute(float newValue)
{
	HealthSet->SetHealth(newValue);
}

float AGGBaseCharacter::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator,
                                   AActor* DamageCauser)
{
	float value = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);

	InDamageSet->SetInDamage(DamageAmount);


	return DamageAmount;
}
