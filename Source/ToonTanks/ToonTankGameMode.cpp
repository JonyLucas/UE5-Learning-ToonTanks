// Fill out your copyright notice in the Description page of Project Settings.


#include "ToonTankGameMode.h"

#include "Tank.h"
#include "TankPlayerController.h"
#include "Tower.h"
#include "Kismet/GameplayStatics.h"

void AToonTankGameMode::BeginPlay()
{
	Super::BeginPlay();

	HandleGameStart();
}

void AToonTankGameMode::HandleGameStart()
{
	Tank = Cast<ATank>(UGameplayStatics::GetPlayerPawn(this, 0));
	PlayerControllerRef = Cast<ATankPlayerController>(UGameplayStatics::GetPlayerController(this, 0)); // Game Mode can be passed as world context object
	TArray<AActor*> Towers;
	UGameplayStatics::GetAllActorsOfClass(this, ATower::StaticClass(), Towers);
	TargetTowersCount = Towers.Num();

	GameStart();

	if (PlayerControllerRef)
	{
		PlayerControllerRef->SetPlayerEnabledState(false);
		FTimerHandle PlayerEnableHandle;
		const FTimerDelegate PlayerEnableDelegate = FTimerDelegate::CreateUObject(
			PlayerControllerRef, &ATankPlayerController::SetPlayerEnabledState, true);
		GetWorldTimerManager().SetTimer(PlayerEnableHandle, PlayerEnableDelegate, StartDelay, false);
	}
}

void AToonTankGameMode::ActorDied(AActor* DeadActor)
{
	if (DeadActor == Tank)
	{
		Tank->HandleDestruction();
		if (PlayerControllerRef)
		{
			PlayerControllerRef->SetPlayerEnabledState(false);
		}

		GameOver(false);
	}
	else if (const auto Tower = Cast<ATower>(DeadActor))
	{
		Tower->HandleDestruction();
		--TargetTowersCount;
		if (TargetTowersCount == 0)
		{
			GameOver(true);
		}
	}
}

