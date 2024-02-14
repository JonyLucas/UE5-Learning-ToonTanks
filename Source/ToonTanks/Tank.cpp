// Fill out your copyright notice in the Description page of Project Settings.


#include "Tank.h"

#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"

ATank::ATank()
{
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("Spring Arm"));
	SpringArm->SetupAttachment(RootComponent);

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(SpringArm);
}

void ATank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (const APlayerController* PlayerController = Cast<APlayerController>(Controller))
	{
		if (UEnhancedInputLocalPlayerSubsystem* LocalPlayerSubsystem = ULocalPlayer::GetSubsystem<
			UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			LocalPlayerSubsystem->AddMappingContext(InputContext, 0);
		}
	}

	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ATank::Move);
	}
}

void ATank::BeginPlay()
{
	Super::BeginPlay();
}

void ATank::Move(const FInputActionInstance& ActionValue)
{
	const FVector2d MoveValue = ActionValue.GetValue().Get<FVector2d>();
	// UE_LOG(LogTemp, Warning, TEXT("Move Value: %s"), *MoveValue.ToString());
	// const FVector MoveVector =  FVector(MoveValue.Y, MoveValue.X, 0).GetSafeNormal();
	Translate(MoveValue.Y);
	Turn(MoveValue.X);
}

void ATank::Translate(const float ForwardValue)
{
	const FVector MoveVector = ForwardValue * FVector::ForwardVector;
	AddActorLocalOffset(MoveVector * Speed * GetWorld()->DeltaTimeSeconds, true);
}

void ATank::Turn(const float TurnValue)
{
	const FRotator Rotation = FRotator(0, TurnValue * TurnSpeed * GetWorld()->DeltaTimeSeconds, 0);
	AddActorLocalRotation(Rotation, true);
}
