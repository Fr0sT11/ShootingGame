// Fill out your copyright notice in the Description page of Project Settings.


#include "SPlayerState.h"

//void ASPlayerState::AddScore(float ScoreDelta)
//{
//	Score += ScoreDelta;
//}
ASPlayerState::ASPlayerState()
{
	Score = 0;
}
void ASPlayerState::AddScore(float ScoreDelta)
{
	Score+=ScoreDelta;
}