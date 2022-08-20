// Fill out your copyright notice in the Description page of Project Settings.


#include "Gun.h"
#include "Components/SkeletalMeshComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AGun::AGun()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	RootSceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root Scene Component"));
	SetRootComponent(RootSceneComponent);

	SkeletalMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Gun Skeletal Mesh"));
	SkeletalMesh->SetupAttachment(RootSceneComponent);
}

// Called when the game starts or when spawned
void AGun::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AGun::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

bool AGun::TryBulletImpactTrace(FHitResult& OutHitResult, FVector& OutShotDirection)
{
	AController* OwnerController = GetOwnerController();
	if (!OwnerController)
	{
		return false;
	}

	FVector PlayerViewPointLocation;
	FRotator PlayerViewPointRotation;
	OwnerController->GetPlayerViewPoint(PlayerViewPointLocation, PlayerViewPointRotation);
	
	FVector End = PlayerViewPointLocation + PlayerViewPointRotation.Vector() * MaxRange;

	OutShotDirection = -PlayerViewPointRotation.Vector();

	FCollisionQueryParams CollisionQueryParams;
	CollisionQueryParams.AddIgnoredActor(this);
	CollisionQueryParams.AddIgnoredActor(GetOwner());


	return GetWorld()->LineTraceSingleByChannel(
		OutHitResult, 
		PlayerViewPointLocation, 
		End, 
		ECollisionChannel::ECC_GameTraceChannel1,
		CollisionQueryParams
	);
}

AController* AGun::GetOwnerController() const
{
	APawn* OwnerPawn = Cast<APawn>(GetOwner());
	if (OwnerPawn)
	{
		return OwnerPawn->GetController();
	}

	return nullptr;
}

void AGun::PullTrigger()
{
	if (MuzzleFlash)
	{
		UGameplayStatics::SpawnEmitterAttached(MuzzleFlash,  SkeletalMesh, TEXT("MuzzleFlashSocket"));
	}

	if (MuzzleSound)
	{
		UGameplayStatics::SpawnSoundAttached(MuzzleSound, SkeletalMesh, TEXT("MuzzleFlashSocket"));
	}

	AController* OwnerController = GetOwnerController();
	if (!OwnerController)
	{
		return;
	}

	FHitResult HitResult;
	FVector ShotDirection;
	bool bHitSuccess = TryBulletImpactTrace(HitResult, ShotDirection);
	
	if (bHitSuccess)
	{
		if (ImpactEffect)
		{
			UGameplayStatics::SpawnEmitterAtLocation(
				GetWorld(), 
				ImpactEffect, 
				HitResult.ImpactPoint, 
				ShotDirection.Rotation()
			);
		}

		if (ImpactSound)
		{
			UGameplayStatics::PlaySoundAtLocation(GetWorld(), ImpactSound, HitResult.ImpactPoint);
		}
		
		AActor* ImpactedActor = HitResult.GetActor();
		if (ImpactedActor)
		{
			FPointDamageEvent BulletDamageEvent(Damage, HitResult, ShotDirection, nullptr);
			ImpactedActor->TakeDamage(Damage, BulletDamageEvent, OwnerController, this);
		}
	}
}
