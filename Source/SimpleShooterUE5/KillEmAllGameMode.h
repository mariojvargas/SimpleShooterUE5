// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SimpleShooterUE5GameModeBase.h"
#include "KillEmAllGameMode.generated.h"

/**
 * 
 */
UCLASS()
class SIMPLESHOOTERUE5_API AKillEmAllGameMode : public ASimpleShooterUE5GameModeBase
{
	GENERATED_BODY()

public:
	virtual void PawnKilled(APawn* DeadPawn) override;

private:
	void EndGame(bool bPlayerIsWinner);
	bool AreAllEnemiesDead() const;
	bool IsMainPlayer(const APawn* Pawn) const;
};
