// Fill out your copyright notice in the Description page of Project Settings.


#include "KillEmAllGameMode.h"
#include "EngineUtils.h"
#include "GameFramework/Controller.h"
#include "ShooterAIController.h"


void AKillEmAllGameMode::PawnKilled(APawn* DeadPawn)
{
    Super::PawnKilled(DeadPawn);

    if (IsMainPlayer(DeadPawn))
    {
       EndGame(false);
    }
    else if (AreAllEnemiesDead())
    {
        EndGame(true);
    }
}

bool AKillEmAllGameMode::IsMainPlayer(const APawn* Pawn) const
{
    APlayerController* PlayerController = Cast<APlayerController>(Pawn->GetController());

    return PlayerController != nullptr;
}

void AKillEmAllGameMode::EndGame(bool bPlayerIsWinner)
{
    for (AController* Controller : TActorRange<AController>(GetWorld()))
    {
        // Invariant: bWinSuccess is any of these values
        //  true: playerController && bPlayerIsWinner
        //  true: !playerController && !bPlayerIswinner
        //  false: playerController && !bPlayerIsWinner
        //  false: !playerController && bPlayerIsWinner

        bool bWinSuccess = Controller->IsPlayerController() == bPlayerIsWinner;
        Controller->GameHasEnded(Controller->GetPawn(), bWinSuccess);
    }
}

bool AKillEmAllGameMode::AreAllEnemiesDead() const
{
    for (AShooterAIController* EnemyController : TActorRange<AShooterAIController>(GetWorld()))
    {
        if (!EnemyController->IsDead())
        {
            return false;
        }
    }

    return true;
}
