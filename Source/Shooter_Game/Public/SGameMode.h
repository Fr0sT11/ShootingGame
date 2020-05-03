// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "SGameMode.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FOnActorKilled, AActor*, VictimActor, AActor*, KillerActor, AController*, KillerController);

/**
 * 
 */

UCLASS()
class SHOOTER_GAME_API ASGameMode : public AGameModeBase
{
	GENERATED_BODY()

protected:
	FTimerHandle TimerHandle_MatchTime;//TimerHandler

	//UPROPERTY(EditDefaultsOnly,Category="GameMode")
	//float gametime;

	void RestartDeadPlayers();

	void PlayerDead();

	virtual void BeginPlay() override;
	  
	void StartGameSession();
	void EndGameSession();

	
public:
	ASGameMode();


	virtual void Tick(float DeltaSeconds) override;

	UPROPERTY(BlueprintAssignable, Category = "GameMode")
		FOnActorKilled OnActorKilled;

};
