// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

/**
 * 
 */
class TOURNAMENTGENERATOR_API BaseClass
{
public:
	BaseClass();
	BaseClass(const TArray<int32>& Members);
	BaseClass(const TArray<int32>& Members, const TArray<int32>& RaitingPoints);
	//BaseClass(TArray<TTuple<FString, int32>> Info);
	virtual ~BaseClass();

	virtual void GenerateTournament() = 0;
	virtual void PrintTournamentInfo() = 0;

protected:
	TArray<int32> Members; 
	TArray<int32> RatingPoints;
	TMap<int32, int32> RatingMap; 
	TMap<int32, int32> MembersStatusMap; 
};
