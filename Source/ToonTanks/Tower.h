// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BasePawn.h"
#include "Tower.generated.h"

/**
 * 
 */
UCLASS()
class TOONTANKS_API ATower : public ABasePawn
{
	GENERATED_BODY()

public:
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable)
	virtual void HandleDestruction() override;

protected:
	virtual void BeginPlay() override;
	
private:
	void CheckFireCondition();
	bool InFireRange() const;
	
	UPROPERTY(EditAnywhere)
	float FireRange = 500.f;

	UPROPERTY(EditAnywhere)
	float FireRate = 2.f;

	FTimerHandle FireRateTimerHandle;
	
	class ATank* TankReference;	
};
