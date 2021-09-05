// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "JsonStructs.generated.h"

USTRUCT(BlueprintType)
struct FIntArray
{
	GENERATED_BODY()

		UPROPERTY()
		TArray<int32> IntArr;
};

USTRUCT(BlueprintType)
struct FTripleTuple
{
	GENERATED_BODY()

	UPROPERTY()
		int32 first;
	UPROPERTY()
		int32 second;
	UPROPERTY()
		int32 third;
};

USTRUCT(BlueprintType)
struct FTripleTupleArray
{
	GENERATED_BODY()

		UPROPERTY()
		TArray<FTripleTuple> TripleTupleArr;
};

USTRUCT(BlueprintType)
struct FIntPair
{
	GENERATED_BODY()

		UPROPERTY()
		int32 first;

		UPROPERTY()
		int32 second;
};

USTRUCT(BlueprintType)
struct FMatch
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly)
		int32 FirstPlayer;

	UPROPERTY(BlueprintReadOnly)
		int32 SecondPlayer;

	UPROPERTY(BlueprintReadOnly)
		int32 Winner;
};