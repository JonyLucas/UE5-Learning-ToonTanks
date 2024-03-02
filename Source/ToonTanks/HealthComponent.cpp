// Fill out your copyright notice in the Description page of Project Settings.


#include "HealthComponent.h"

#include "ToonTankGameMode.h"
#include "Kismet/GameplayStatics.h"

// Sets default values for this component's properties
UHealthComponent::UHealthComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

// Called when the game starts
void UHealthComponent::BeginPlay()
{
	Super::BeginPlay();
	CurrentHealth = MaxHealth;
	GetOwner()->OnTakeAnyDamage.AddDynamic(this, &UHealthComponent::TakeDamage);
	GameMode = Cast<AToonTankGameMode>(UGameplayStatics::GetGameMode(GetWorld()));
}

// Called every frame
void UHealthComponent::TickComponent(float DeltaTime, ELevelTick TickType,
                                     FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UHealthComponent::TakeDamage(AActor* DamagedActor, float Damage, const UDamageType* DamageType,
                                  AController* InstigatedBy, AActor* DamageCauser)
{
	CurrentHealth -= Damage;
	UE_LOG(LogTemp, Warning, TEXT("Health of %s: %f"), *GetOwner()->GetName(), CurrentHealth);
	if (CurrentHealth <= 0)
	{
		if (GameMode)
		{
			GameMode->ActorDied(GetOwner());
		}
	}
}
