// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "SimpleShooterUE5GameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class SIMPLESHOOTERUE5_API ASimpleShooterUE5GameModeBase : public AGameModeBase
{
	GENERATED_BODY()

public:
	virtual void PawnKilled(APawn* DeadPawn);
	
};
