// Fill out your copyright notice in the Description page of Project Settings.


#include "BasePawn.h"

#include "Components/CapsuleComponent.h"
#include "Projectile.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ABasePawn::ABasePawn()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CapsuleComponent = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Capsule Collider"));
	SetRootComponent(CapsuleComponent);

	BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Base Mesh"));
	BaseMesh->SetupAttachment(CapsuleComponent);

	TurretMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Turret Mesh"));
	TurretMesh->SetupAttachment(BaseMesh);

	ProjectileSpawnPoint = CreateDefaultSubobject<USceneComponent>(TEXT("Projectile"));
	ProjectileSpawnPoint->SetupAttachment(TurretMesh);
}


// Called when the game starts or when spawned
void ABasePawn::BeginPlay()
{
	Super::BeginPlay();
	bIsActorAlive = true;
}

void ABasePawn::HandleDestruction()
{
	if (DeathParticle)
	{
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), DeathParticle, GetActorLocation(), GetActorRotation());
	}

	if (DeathSound)
	{
		UGameplayStatics::PlaySoundAtLocation(GetWorld(), DeathSound, GetActorLocation());
	}

	if(DeathShake)
	{
		GetWorld()->GetFirstPlayerController()->ClientStartCameraShake(DeathShake);
	}

	bIsActorAlive = false;
}

void ABasePawn::RotateTurret(const FVector& TargetPosition) const
{
	const FVector TargetDirection = TargetPosition - GetActorLocation();
	const FRotator TargetRotation = FRotator(0, TargetDirection.Rotation().Yaw, 0);
	TurretMesh->SetWorldRotation(FMath::RInterpTo(TurretMesh->GetComponentRotation(), TargetRotation,
	                                              GetWorld()->GetDeltaSeconds(), 5));
}

void ABasePawn::Fire()
{
	if(!bIsActorAlive)
	{
		return;
	}
	
	// UE_LOG(LogTemp, Warning, TEXT("Fire"));
	// DrawDebugSphere(GetWorld(), ProjectileSpawnPoint->GetComponentLocation(), 25, 12, FColor::Red, false, 2.f, 0, 1.f);	
	const auto Projectile = GetWorld()->SpawnActor<AProjectile>(ProjectileClass,
	                                                            ProjectileSpawnPoint->GetComponentLocation(),
	                                                            ProjectileSpawnPoint->GetComponentRotation());
	Projectile->SetOwner(this);

	if(LaunchShake)
	{
		GetWorld()->GetFirstPlayerController()->ClientStartCameraShake(LaunchShake);
	}
}
