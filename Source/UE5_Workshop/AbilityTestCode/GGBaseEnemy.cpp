// Fill out your copyright notice in the Description page of Project Settings.


#include "GGBaseEnemy.h"

#include "AbilitySystemComponent.h"
#include "GGGameplayAbility.h"
#include "Attributes/GGDamageSet.h"
#include "Attributes/UGGHealthSet.h"


// Sets default values
AGGBaseEnemy::AGGBaseEnemy()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	AbilitySystemComponent = CreateDefaultSubobject<UAbilitySystemComponent>("AbilitySystemComp");
	HealthSet = CreateDefaultSubobject<UGGHealthSet>("HealthSet");
	InDamageSet = CreateDefaultSubobject<UGGDamageSet>("InDamageSet");

}

// Called when the game starts or when spawned
void AGGBaseEnemy::BeginPlay()
{
	Super::BeginPlay();

	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(HealthSet->GetHealthAttribute()).AddUObject(
		this, &AGGBaseEnemy::OnHealthAttributeChanged);
}

void AGGBaseEnemy::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	if(!AbilitySystemComponent)
		return;

	AbilitySystemComponent->InitAbilityActorInfo(this,this);

	InitializeAbilities();
	InitializeGameEffects();
}


void AGGBaseEnemy::InitializeAbilities()
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

void AGGBaseEnemy::InitializeGameEffects()
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


void AGGBaseEnemy::OnHealthAttributeChanged(const FOnAttributeChangeData& Data)
{
	OnHealthChanged(Data.OldValue, Data.NewValue);
}

void AGGBaseEnemy::OnInDamageAttributeChanged(const FOnAttributeChangeData& Data)
{
	float damage = InDamageSet->GetInDamage();
	float healthValue = HealthSet->GetHealth();
	if (damage > 0)
	{
		HealthSet->SetHealth(healthValue - damage);
	}

	
	InDamageSet->SetInDamage(0);

	OnDamageChanged(Data.OldValue, Data.NewValue);
}

// Called every frame
void AGGBaseEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void AGGBaseEnemy::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

float AGGBaseEnemy::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator,
                               AActor* DamageCauser)
{
	float value = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);

	InDamageSet->SetInDamage(DamageAmount);
	
	return DamageAmount;
}
