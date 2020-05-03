// Fill out your copyright notice in the Description page of Project Settings.


#include "SGameMode.h"
#include "TimerManager.h"
#include "SCharacter.h"
#include "SHealthComponent.h"

#include"SPlayerState.h"

ASGameMode::ASGameMode()
{
	//gametime = 60.0;

	PlayerStateClass = ASPlayerState::StaticClass();

    PrimaryActorTick.bCanEverTick = true;
    PrimaryActorTick.TickInterval = 5.0f;
}

void ASGameMode::BeginPlay()
{
	Super::BeginPlay();
	StartGameSession();
}

void ASGameMode::StartGameSession()
{
	
	GetWorldTimerManager().SetTimer(TimerHandle_MatchTime, this, &ASGameMode::EndGameSession, 10.0f, true, 30.0f);
}
void ASGameMode::EndGameSession()
{
	if (GEngine)
	{
		//GEngine->AddOnScreenDebugMessage(0, 5.f, FColor::Red, TEXT("Game over"));
	}

	//End Game
	//Super::EndPlay();
}


//void ASGameMode::StartGame()
//{
//	GetWorldTimerManager().SetTimer(TimerHandle_MatchTime, this, &ASGameMode::EndGame, 60.0f, false);
//}


//void ASGameMode::EndGame()
//{
//
//}

void ASGameMode::PlayerDead()
{
    for (FConstPawnIterator It = GetWorld()->GetPawnIterator(); It; ++It)
    {
        APawn* TestPawn = It->Get();
        if (TestPawn == nullptr || TestPawn->IsPlayerControlled())
        {
            continue;
        }
        USHealthComponent* HealthComp = Cast<USHealthComponent>(TestPawn->GetComponentByClass(USHealthComponent::StaticClass()));
        if (HealthComp && HealthComp->GetHealth() <= 0.0f)
        {
            RestartDeadPlayers();
        }
    }
}

void ASGameMode::RestartDeadPlayers()
{
    for (FConstPlayerControllerIterator It = GetWorld()->GetPlayerControllerIterator(); It; ++It)
    {
        APlayerController* PC = It->Get();
        if (PC && PC->GetPawn() == nullptr)
        {
            RestartPlayer(PC);
        }
    }
}

void ASGameMode::Tick(float DeltaSeconds)
{
    Super::Tick(DeltaSeconds);

    PlayerDead();
}
