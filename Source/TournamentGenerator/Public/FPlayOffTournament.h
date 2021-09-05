// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

//TOURNAMENTGENERATOR_API 

#include "CoreMinimal.h"
#include "BaseClass.h"
#include "TournamentEnums.h"	
#include "ISerializable.h"
#include "Math/RandomStream.h"
#include "Runtime/JsonUtilities/Public/JsonObjectConverter.h"
#include "FPlayOffTournamentStruct.h"
#include "JsonStructs.h"
#include "Misc/FileHelper.h"
#include "JsonUtils.h"

/**
 * Play-Off Tournament
 */
class TOURNAMENTGENERATOR_API FPlayOffTournament : public ISerializable, BaseClass
{
public:
	FPlayOffTournament();
	FPlayOffTournament(const TArray<int32>& TournamentMembers);
	FPlayOffTournament(const TArray<int32>& TournamentMembers, const TArray<int32>& TournamentMembersRating);
	~FPlayOffTournament();

	void GenerateTournament() override;
	void PrintTournamentInfo() override;
	void ChooseWinner(const int32& Round, const int32& Winner);
	void ChooseWinner(const int32& WinnerId);
	bool NextStage();
	void RandomizeWinners();
	void SetGenerator(const EPlayOffTournamentGenerator& Generator);
	void SetMemberStatus(const int32& MemberId, const MemberStatus& Status);

	// Inherited via ISerializable
	virtual bool LoadJson(const FString& FileName) override;
	virtual bool SaveJson(const FString& FileName) override;

	TArray<int32> GetWinnersId(const int32& Stage);
	TArray<int32> GetMembers();
	TArray<int32> GetCurrentStageMembers();
	TArray<TTuple<int32, int32, int32>> GetCurrentStage();
	TTuple<int32, int32, int32> GetMatchByIndex(const int32& MatchIndex);
	int32 GetCurrentStageIndex();
	int32 GetMatchCount();
	bool IsTournamentFinished();

private:
	int32 StageCount = 0; 
	int32 CurrentStageIndex = 0; 
	EPlayOffTournamentGenerator GenerationType = Random;
	FRandomStream s = FRandomStream();
	TArray<TArray<int32>> StageWinners; 
	TArray<TTuple<int32, int32, int32>> CurrentStage; 
	TArray<int32> CurrentStageMembers; 
	TArray<TArray<TTuple<int32, int32, int32>>> TournamentInfo; 
	TMap<int32, int32> RoundMap; 

	void ShuffleTArray(TArray<int32>& Arr);
	TTuple<int32, int32, int32> CreateMatchFromWinners(const TTuple<int32, int32, int32>& Match1, const TTuple<int32, int32, int32>& Match2);

	void GenerateRandomTournament();
	void GenerateWorstAgainstBestTournament();
	void GenerateDirectTournament();
};
