// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "JsonStructs.h"
#include "FPlayOffTournamentStruct.generated.h"

USTRUCT(BlueprintType)
struct FPlayOffTournamentStruct
{
	GENERATED_BODY()

		UPROPERTY()
		TArray<int32> Members;

	UPROPERTY()
		int32 CurrentStageIndex = 0; //ser

	UPROPERTY()
		int32 StageCount = 0; //ser 

	UPROPERTY()
		TArray<int32> CurrentStageMembers; //ser

	UPROPERTY()
		TArray<FTripleTuple> CurrentStage; //ser

	UPROPERTY()
		TArray<FIntArray> StageWinners; //ser

	UPROPERTY()
		TArray<FTripleTupleArray> TournamentInfo; //ser

	UPROPERTY()
		TArray<FIntPair> RoundMap; //ser

	UPROPERTY()
		TArray<FIntPair> MembersStatusMap;

	UPROPERTY()
		TArray<FIntPair> RatingMap;
};