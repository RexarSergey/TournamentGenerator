// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "JsonStructs.h"

/**
 *
 */
class TOURNAMENTGENERATOR_API JsonUtils
{
public:
	JsonUtils();
	~JsonUtils();

	static void LoadIntArray(const TSharedPtr<FJsonObject>& JsonObject, TArray<int32>& OutArray, const FString& ParamName);
	static void LoadTripleTupleArray(const TSharedPtr<FJsonObject>& JsonObject, TArray < TTuple<int32, int32, int32>>& OutArray,
		const FString& ArrayName, const FString& First, const FString& Second, const FString& Third);
	static void LoadNestedIntArray(const TSharedPtr<FJsonObject>& JsonObject, TArray<TArray<int32>>& OutArray,
		const FString& MainArrayName, const FString& SubArrayName);
	static void LoadNestedTripleTupleArray(const TSharedPtr<FJsonObject>& JsonObject, TArray<TArray<TTuple<int32, int32, int32>>>& OutArray,
		const FString& MainArrayName, const FString& SubArrayName, const FString& First, const FString& Second, const FString& Third);
	static void LoadMapArray(const TSharedPtr<FJsonObject>& JsonObject, TMap<int32, int32>& OutMapconst, const FString& ArrayName, const FString& First, const FString& Second);

	static TArray<FIntPair> GetArrayFromMap(const TMap<int32, int32>& Map);
};
