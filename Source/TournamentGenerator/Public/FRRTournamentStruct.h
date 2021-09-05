// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "JsonStructs.h"
#include "FRRTournamentStruct.generated.h"

USTRUCT(BlueprintType)
struct FRRTournamentStruct
{
	GENERATED_BODY()

		UPROPERTY()
		TArray<int32> Members;

	UPROPERTY()
		TArray<FIntPair> RatingMap;

	UPROPERTY()
		TArray<FIntPair> MembersStatusMap;

	UPROPERTY()
		TArray<int32> MembersIndex;

	UPROPERTY()
		TArray<FTripleTuple> Matches;

	UPROPERTY()
		TArray<FIntPair> WinsCountMap;
};