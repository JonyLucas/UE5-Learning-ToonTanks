// Fill out your copyright notice in the Description page of Project Settings.


#include "Tank.h"

#include "DrawDebugHelpers.h"
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
	PlayerController = Cast<APlayerController>(Controller);
	
	if (PlayerController)
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
		EnhancedInputComponent->BindAction(FireAction, ETriggerEvent::Triggered, this, &ATank::Fire);
	}
}

void ATank::BeginPlay()
{
	Super::BeginPlay();
	// GetWorldTimerManager().SetTimer(FireRateTimerHandle, this, &ATank::CheckFireCondition, FireRate, true);
}

void ATank::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if(PlayerController)
	{
		FHitResult MouseHitResult;
		if(PlayerController->GetHitResultUnderCursor(ECC_Visibility, false, MouseHitResult))
		{
			const FVector MouseLocation = MouseHitResult.ImpactPoint;
			// DrawDebugSphere(GetWorld(), MouseLocation, 25, 12, FColor::Red, false, 0.5f);
			RotateTurret(MouseLocation);
		}
	}
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
