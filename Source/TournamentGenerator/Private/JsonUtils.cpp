// Fill out your copyright notice in the Description page of Project Settings.


#include "JsonUtils.h"

JsonUtils::JsonUtils()
{
}

JsonUtils::~JsonUtils()
{
}

void JsonUtils::LoadIntArray(const TSharedPtr<FJsonObject>& JsonObject, TArray<int32>& OutArray, const FString& ParamName)
{
	TArray<TSharedPtr<FJsonValue>> Array = JsonObject->GetArrayField(ParamName);
	OutArray.Empty();
	for (TSharedPtr<FJsonValue> elem : Array) {
		OutArray.Add(static_cast<int32>(elem->AsNumber()));
	}
}

void JsonUtils::LoadTripleTupleArray(const TSharedPtr<FJsonObject>& JsonObject, TArray<TTuple<int32, int32, int32>>& OutArray, const FString& ArrayName, const FString& First, const FString& Second, const FString& Third)
{
	TArray<TSharedPtr<FJsonValue>> Array = JsonObject->GetArrayField(ArrayName);
	OutArray.Empty();
	for (TSharedPtr<FJsonValue> elem : Array) {
		TTuple<int32, int32, int32> match(
			elem->AsObject()->GetIntegerField(First),
			elem->AsObject()->GetIntegerField(Second),
			elem->AsObject()->GetIntegerField(Third));
		OutArray.Add(match);
	}
}

void JsonUtils::LoadNestedIntArray(const TSharedPtr<FJsonObject>& JsonObject, TArray<TArray<int32>>& OutArray, const FString& MainArrayName, const FString& SubArrayName)
{
	TArray<TSharedPtr<FJsonValue>> Array = JsonObject->GetArrayField(MainArrayName);
	OutArray.Empty();
	for (TSharedPtr<FJsonValue> elem : Array)
	{
		TArray<int32> NewStage;
		LoadIntArray(elem->AsObject(), NewStage, SubArrayName);
		OutArray.Add(NewStage);
	}
}

void JsonUtils::LoadNestedTripleTupleArray(const TSharedPtr<FJsonObject>& JsonObject, TArray<TArray<TTuple<int32, int32, int32>>>& OutArray, const FString& MainArrayName, const FString& SubArrayName, const FString& First, const FString& Second, const FString& Third)
{
	TArray<TSharedPtr<FJsonValue>> Array = JsonObject->GetArrayField(MainArrayName);
	OutArray.Empty();
	for (TSharedPtr<FJsonValue> elem : Array)
	{
		TArray<TTuple<int32, int32, int32>>NewStage;
		LoadTripleTupleArray(elem->AsObject(), NewStage, SubArrayName, First, Second, Third);
		OutArray.Add(NewStage);
	}
}

void JsonUtils::LoadMapArray(const TSharedPtr<FJsonObject>& JsonObject, TMap<int32, int32>& OutMap, const FString& ArrayName, const FString& First, const FString& Second)
{
	TArray<TSharedPtr<FJsonValue>> Array = JsonObject->GetArrayField(ArrayName);
	OutMap.Empty();
	for (TSharedPtr<FJsonValue> elem : Array)
	{
		OutMap.Add(elem->AsObject()->GetIntegerField(First), elem->AsObject()->GetIntegerField(Second));
	}
}


TArray<FIntPair> JsonUtils::GetArrayFromMap(const TMap<int32, int32>& Map)
{
	TArray<FIntPair> Array;
	for (const TPair<int32, int32>& p : Map)
	{
		FIntPair NewPair;
		NewPair.first = p.Get<0>();
		NewPair.second = p.Get<1>();
		Array.Add(NewPair);
	}
	return Array;
}