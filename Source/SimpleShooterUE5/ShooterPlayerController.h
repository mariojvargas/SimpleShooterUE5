// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "ShooterPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class SIMPLESHOOTERUE5_API AShooterPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	virtual void GameHasEnded(class AActor* EndGameFocus = nullptr, bool bIsWinner = false) override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	UPROPERTY(EditAnywhere)
	TSubclassOf<class UUserWidget> LoseScreenClass = nullptr;

	UPROPERTY(EditAnywhere)
	TSubclassOf<class UUserWidget> VictoryScreenClass = nullptr;

	UPROPERTY(EditAnywhere)
	TSubclassOf<class UUserWidget> HUDClass = nullptr;

	UPROPERTY(EditAnywhere)
	float RestartDelay = 5.f;

	UPROPERTY()
	class UUserWidget* HUD = nullptr;

	void DisplayMatchResultScreen(bool bPlayerIsWinner);

	class UUserWidget* AddWidgetToViewport(const TSubclassOf<class UUserWidget>& Widget);
};
