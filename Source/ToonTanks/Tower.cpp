// Fill out your copyright notice in the Description page of Project Settings.


#include "Tower.h"

#include "Tank.h"

void ATower::BeginPlay()
{
	Super::BeginPlay();

	if (const APlayerController* PlayerController = GetWorld()->GetFirstPlayerController())
	{
		TankReference = Cast<ATank>(PlayerController->GetPawn());
	}
}

void ATower::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if(TankReference)
	{
		float Distance = FVector::Dist(TankReference->GetActorLocation(), GetActorLocation());

		if (Distance <= TargetDistance)
		{
			RotateTurret(TankReference->GetActorLocation());
		}
	}
}