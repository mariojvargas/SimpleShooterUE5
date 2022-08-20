// Fill out your copyright notice in the Description page of Project Settings.


#include "ShooterPlayerController.h"
#include "TimerManager.h"
#include "Blueprint/UserWidget.h"


void AShooterPlayerController::BeginPlay()
{
    Super::BeginPlay();

    HUD = AddWidgetToViewport(HUDClass);
}

UUserWidget* AShooterPlayerController::AddWidgetToViewport(const TSubclassOf<class UUserWidget>& WidgetClass)
{
    if (!WidgetClass)
    {
        return nullptr;
    }
    
    UUserWidget* Widget = CreateWidget(this, WidgetClass);
    if (Widget)
    {
        Widget->AddToViewport();

        return Widget;
    }

    return nullptr;
}

void AShooterPlayerController::GameHasEnded(AActor* EndGameFocus, bool bIsWinner)
{
    Super::GameHasEnded(EndGameFocus, bIsWinner);

    if (HUD)
    {
        HUD->RemoveFromViewport();
    }

    DisplayMatchResultScreen(bIsWinner);

    FTimerHandle RestartTimerHandle;
    GetWorldTimerManager().SetTimer(RestartTimerHandle, this, &APlayerController::RestartLevel, RestartDelay);
}

void AShooterPlayerController::DisplayMatchResultScreen(bool bPlayerIsWinner)
{
    if (bPlayerIsWinner)
    {
        AddWidgetToViewport(VictoryScreenClass);
    }
    else
    {
        AddWidgetToViewport(LoseScreenClass);
    }
}
