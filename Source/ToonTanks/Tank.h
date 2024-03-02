// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BasePawn.h"
#include "InputMappingContext.h"
#include "Tank.generated.h"

UCLASS()
class TOONTANKS_API ATank : public ABasePawn
{
	GENERATED_BODY()

public:
	ATank();
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION(BlueprintCallable)
	virtual void HandleDestruction() override;

	UFUNCTION(BlueprintCallable)
	APlayerController* GetPlayerController() const { return PlayerController; }

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, Category="Input")
	UInputMappingContext* InputContext;

	UPROPERTY(EditAnywhere, Category="Input")
	UInputAction* MoveAction;

	UPROPERTY(EditAnywhere, Category="Input")
	UInputAction* FireAction;

private:
	UPROPERTY(VisibleAnywhere)
	class USpringArmComponent* SpringArm;

	UPROPERTY(VisibleAnywhere)
	class UCameraComponent* Camera;

	UPROPERTY(EditAnywhere)
	float FireRate = 2.f;

	APlayerController* PlayerController;
	FTimerHandle FireRateTimerHandle;
	
	void Move(const FInputActionInstance& ActionValue);
	void Translate(float ForwardValue);
	void Turn(float TurnValue);
};
