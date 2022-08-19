// Fill out your copyright notice in the Description page of Project Settings.


#include "ShooterAIController.h"
#include "Kismet/GameplayStatics.h"
#include "BehaviorTree/BlackboardComponent.h"


void AShooterAIController::BeginPlay()
{
    Super::BeginPlay();

    if (!AIBehaviorTree)
    {
        return;
    }

    APawn* PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
    if (!PlayerPawn)
    {
        return;
    }

    APawn* ControlledPawn = GetPawn();
    if (!ControlledPawn)
    {
        return;
    }

    RunBehaviorTree(AIBehaviorTree);

    UBlackboardComponent* BlackboardComponent = GetBlackboardComponent();

    BlackboardComponent->SetValueAsVector(TEXT("PlayerLocation"), PlayerPawn->GetActorLocation());
    BlackboardComponent->SetValueAsVector(TEXT("StartLocation"), ControlledPawn->GetActorLocation());
    
}

void AShooterAIController::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    APawn* PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
    if (!PlayerPawn)
    {
        return;
    }
    
    UBlackboardComponent* BlackboardComponent = GetBlackboardComponent();

    if (LineOfSightTo(PlayerPawn))
    {
        BlackboardComponent->SetValueAsVector(TEXT("PlayerLocation"), PlayerPawn->GetActorLocation());
        BlackboardComponent->SetValueAsVector(TEXT("LastKnownPlayerLocation"), PlayerPawn->GetActorLocation());
    }
    else
    {
        BlackboardComponent->ClearValue(TEXT("PlayerLocation"));
    }
}
