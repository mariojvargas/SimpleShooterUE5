// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "ShooterAIController.generated.h"

/**
 * 
 */
UCLASS()
class SIMPLESHOOTERUE5_API AShooterAIController : public AAIController
{
	GENERATED_BODY()

public:
	virtual void Tick(float DeltaTime) override;

protected:
	virtual void BeginPlay() override;
	

private:
	UPROPERTY(EditAnywhere)
	class UBehaviorTree* AIBehaviorTree = nullptr;

	// UPROPERTY(EditAnywhere)
	// float AcceptanceRadius = 200.f;
};
