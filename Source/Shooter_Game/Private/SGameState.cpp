// Fill out your copyright notice in the Description page of Project Settings.


#include "SGameState.h"

ASGameState::ASGameState()
{
	kills = 0;
}
void ASGameState::AddKills()
{
	kills = kills + 1;
}

