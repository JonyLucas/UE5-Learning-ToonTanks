// Fill out your copyright notice in the Description page of Project Settings.


#include "ToonTankGameMode.h"

#include "Tank.h"
#include "Tower.h"
#include "Kismet/GameplayStatics.h"

void AToonTankGameMode::BeginPlay()
{
	Super::BeginPlay();

	Tank = Cast<ATank>(UGameplayStatics::GetPlayerPawn(this, 0));
}

void AToonTankGameMode::ActorDied(AActor* DeadActor)
{
	if (DeadActor == Tank)
	{
		Tank->HandleDestruction();
		if(const auto PlayerController = Tank->GetPlayerController())
		{
			DisableInput(PlayerController);
			PlayerController->bShowMouseCursor = false;
		}		
	} else if(const auto Tower = Cast<ATower>(DeadActor))
	{
		Tower->HandleDestruction();
	}
}
