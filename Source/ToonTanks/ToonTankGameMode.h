// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "ToonTankGameMode.generated.h"

/**
 * 
 */
UCLASS()
class TOONTANKS_API AToonTankGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	void ActorDied(AActor* DeadActor);

protected:
	void BeginPlay() override;

	UFUNCTION(BlueprintImplementableEvent)
	void GameStart();

private:
	class ATank* Tank;
	class ATankPlayerController* PlayerControllerRef;

	UPROPERTY(EditAnywhere)
	float StartDelay = 3.f;

	void HandleGameStart();
};
