// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseClass.h"
#include "ISerializable.h"
#include "Math/UnrealMathUtility.h"
#include "Runtime/JsonUtilities/Public/JsonObjectConverter.h"
#include "FRRTournamentStruct.h"
#include "JsonStructs.h"
#include "Misc/FileHelper.h"
#include "JsonUtils.h"

/**
 *
 */
class TOURNAMENTGENERATOR_API RR : public ISerializable, BaseClass
{
public:

	RR();
	RR(TArray<int32>& Members);
	RR(TArray<int32>& Members, TArray<int32>& RatingPoints);
	~RR();

	void GenerateTournament() override;
	void PrintTournamentInfo() override;

private:
	void SortMembersRM();
	void SortMembersBT();
	void Rotate(TArray<int32>& Indexes);

public:
	void GenerateRoundMethod();
	void GenerateBergerTables();
	void SetWinnerByMatchNumber(int32 MatchNumber, int32 Chooser);

	void DisqualificationByIndex(int32 Index);

	FString GetAllMatchesInfo();
	FString GetWinStatistics();
	FString GetAllMembersInfo();
	FString GetMemberInfoByIndex(int32 Index);
	FString GetMatchInfoByNumber(int32 Index);

	void SetWinnersManually(TArray<int32> Winner);
	void SetWinnersRandomly();
	void SetWinnersRandomlyWithRating();

	void SetAllRatingPoints(TArray<int32> RatingPoints);
	void SetRatingPointsByIndex(int32 Index, int32 RatingPoints);

	int32 GetMatchesCount();
	FString ChooseWinner();
	bool IsOnePersonOnFirstPlace();
	FString GenerateExtraMatches();

	virtual bool LoadJson(const FString& FileName) override;
	virtual bool SaveJson(const FString& FileName) override;

private:
	TArray<int32> MembersIndex;
	// First team index; Second team index; Index of team winner.
	TArray<TTuple<int32, int32, int32>> Matches;
	// ID; count
	TMap<int32, int32> WinsCountMap;
	// Win count, ID
	TArray<TTuple<int32, int32>> MembersPlace;
	TArray<TTuple<int32, int32>> FirstPlace;
};
