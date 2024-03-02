// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Projectile.generated.h"

UCLASS()
class TOONTANKS_API AProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AProjectile();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse,
	           const FHitResult& Hit);
	
	UPROPERTY(EditAnywhere, Category="Combat")
	UStaticMeshComponent* ProjectileMesh;

	UPROPERTY(EditAnywhere, Category="Combat")
	UParticleSystem* HitParticle;

	UPROPERTY(VisibleAnywhere, Category="Combat")
	UParticleSystemComponent* ParticleComponent;

	UPROPERTY(VisibleAnywhere)
	class UProjectileMovementComponent* ProjectileMovement;

	UPROPERTY(EditAnywhere)
	float Speed = 2000.f;

	UPROPERTY(EditAnywhere)
	float MaxSpeed = 4000.f;

	UPROPERTY(EditAnywhere)
	float Damage = 30.f;
};
