// Fill out your copyright notice in the Description page of Project Settings.


#include "ShooterPlayerController.h"
#include "TimerManager.h"
#include "Blueprint/UserWidget.h"


void AShooterPlayerController::GameHasEnded(AActor* EndGameFocus, bool bIsWinner)
{
    Super::GameHasEnded(EndGameFocus, bIsWinner);

    DisplayMatchResultScreen(bIsWinner);

    FTimerHandle RestartTimerHandle;
    GetWorldTimerManager().SetTimer(RestartTimerHandle, this, &APlayerController::RestartLevel, RestartDelay);
}

void AShooterPlayerController::DisplayMatchResultScreen(bool bPlayerIsWinner)
{
    UUserWidget* ScreenToDisplay;

    if (bPlayerIsWinner)
    {
        ScreenToDisplay = CreateWidget(this, VictoryScreenClass);
    }
    else
    {
        ScreenToDisplay = CreateWidget(this, LoseScreenClass);
    }

    if (ScreenToDisplay)
    {
        ScreenToDisplay->AddToViewport();
    }
}
