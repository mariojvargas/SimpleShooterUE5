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

void AGun::PullTrigger()
{
	if (MuzzleFlash)
	{
		UGameplayStatics::SpawnEmitterAttached(MuzzleFlash,  SkeletalMesh, TEXT("MuzzleFlashSocket"));

		APawn* OwnerPawn = Cast<APawn>(GetOwner());
		if (!OwnerPawn)
		{
			return;
		}

		AController* OwnerController = OwnerPawn->GetController();
		if (!OwnerController)
		{
			return;
		}

		FVector PlayerViewPointLocation;
		FRotator PlayerViewPointRotation;
		OwnerController->GetPlayerViewPoint(PlayerViewPointLocation, PlayerViewPointRotation);
		
		FVector End = PlayerViewPointLocation + PlayerViewPointRotation.Vector() * MaxRange;

		FCollisionQueryParams CollisionQueryParams;
		CollisionQueryParams.AddIgnoredActor(this);
		CollisionQueryParams.AddIgnoredActor(GetOwner());

		FHitResult HitResult;
		bool bHitSuccess = GetWorld()->LineTraceSingleByChannel(
			HitResult, 
			PlayerViewPointLocation, 
			End, 
			ECollisionChannel::ECC_GameTraceChannel1,
			CollisionQueryParams
		);

		if (bHitSuccess && ImpactEffect)
		{
			FVector ShotDirection = -PlayerViewPointRotation.Vector();
			UGameplayStatics::SpawnEmitterAtLocation(
				GetWorld(), 
				ImpactEffect, 
				HitResult.ImpactPoint, 
				ShotDirection.Rotation()
			);

			AActor* ImpactedActor = HitResult.GetActor();
			if (ImpactedActor)
			{
				FPointDamageEvent BulletDamageEvent(Damage, HitResult, ShotDirection, nullptr);
				ImpactedActor->TakeDamage(Damage, BulletDamageEvent, OwnerController, this);
			}
		}
	}
}
