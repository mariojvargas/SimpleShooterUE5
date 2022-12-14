// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Gun.generated.h"

UCLASS()
class SIMPLESHOOTERUE5_API AGun : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AGun();

	void PullTrigger();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	UPROPERTY(VisibleAnywhere)
	USceneComponent* RootSceneComponent = nullptr;

	UPROPERTY(VisibleAnywhere)
	class USkeletalMeshComponent* SkeletalMesh = nullptr;

	UPROPERTY(EditAnywhere)
	UParticleSystem* MuzzleFlash = nullptr;

	UPROPERTY(EditAnywhere)
	USoundBase* MuzzleSound = nullptr;
	
	UPROPERTY(EditAnywhere)
	UParticleSystem* ImpactEffect = nullptr;

	UPROPERTY(EditAnywhere)
	USoundBase* ImpactSound = nullptr;

	UPROPERTY(EditAnywhere)
	float MaxRange = 1000.f;

	UPROPERTY(EditAnywhere)
	float Damage = 10.f;

	bool TryBulletImpactTrace(FHitResult& OutHitResult, FVector& OutShotDirection);

	AController* GetOwnerController() const;
};
