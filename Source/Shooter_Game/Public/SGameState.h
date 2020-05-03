// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "SGameState.generated.h"

/**
 * 
 */
UCLASS()
class SHOOTER_GAME_API ASGameState : public AGameStateBase
{
	GENERATED_BODY()
	
public:
	int kills;
	ASGameState();
	void AddKills();
};
