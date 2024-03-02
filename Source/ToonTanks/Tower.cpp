// Fill out your copyright notice in the Description page of Project Settings.


#include "Tower.h"

#include "Tank.h"

void ATower::BeginPlay()
{
	Super::BeginPlay();

	GetWorldTimerManager().SetTimer(FireRateTimerHandle, this, &ATower::CheckFireCondition, FireRate, true);
	if (const APlayerController* PlayerController = GetWorld()->GetFirstPlayerController())
	{
		TankReference = Cast<ATank>(PlayerController->GetPawn());
	}
}

void ATower::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (TankReference && InFireRange())
	{
		RotateTurret(TankReference->GetActorLocation());
	}
}

void ATower::HandleDestruction()
{
	Super::HandleDestruction();
	Destroy();
}

void ATower::CheckFireCondition()
{
	if (TankReference && InFireRange())
	{
		Fire();
	}
}

bool ATower::InFireRange() const
{
	return FVector::Dist(TankReference->GetActorLocation(), GetActorLocation()) <= FireRange;
}
