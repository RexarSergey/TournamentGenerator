// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "FPlayOffTournament.h"
#include "TournamentEnums.h"
#include "JsonStructs.h"
#include "UPlayOffTournamentComponent.generated.h"


UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class TOURNAMENTGENERATOR_API UPlayOffTournamentComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UPlayOffTournamentComponent();

protected:
	FPlayOffTournament Tournament;

	// Called when the game starts
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable, Category = "PlayOffTournamentComponent")
		void GenerateTournamentNoRating(const TArray<int32>& arr, TEnumAsByte<EPlayOffTournamentGenerator> Generator);

	UFUNCTION(BlueprintCallable, Category = "PlayOffTournamentComponent")
		void GenerateTournament(const TArray<int32>& arr, const TArray<int32>& rating, TEnumAsByte<EPlayOffTournamentGenerator> Generator);

	UFUNCTION(BlueprintCallable, Category = "PlayOffTournamentComponent")
		void RandomizeWinners();

	UFUNCTION(BlueprintCallable, Category = "PlayOffTournamentComponent")
		void ChooseWinner(int32 WinnerId);

	UFUNCTION(BlueprintCallable, Category = "PlayOffTournamentComponent")
		bool NextStage();

	UFUNCTION(BlueprintCallable, Category = "PlayOffTournamentComponent")
		void PrintTournamentInfo();

	UFUNCTION(BlueprintCallable, Category = "PlayOffTournamentComponent")
		void SetMemberStatus(int32 MemberId, MemberStatus Status);

	UFUNCTION(BlueprintCallable, Category = "PlayOffTournamentComponent")
		TArray<int32> GetCurrentStageMembers();

	UFUNCTION(BlueprintCallable, Category = "PlayOffTournamentComponent")
		TArray<int32> GetWinnersByStageIndex(int32 StageIndex);

	UFUNCTION(BlueprintCallable, Category = "PlayOffTournamentComponent")
		TArray<int32> GetWinners();

	UFUNCTION(BlueprintCallable, Category = "PlayOffTournamentComponent")
		int32 GetMatchCount();

	UFUNCTION(BlueprintCallable, Category = "PlayOffTournamentComponent")
		int32 GetCurrentStageIndex();

	UFUNCTION(BlueprintCallable, Category = "PlayOffTournamentComponent")
		bool IsTournamentFinished();

	UFUNCTION(BlueprintCallable, Category = "PlayOffTournamentComponent")
		FMatch GetMatchByIndex(int32 MatchIndex);

	UFUNCTION(BlueprintCallable, Category = "PlayOffTournamentComponent")
		void SaveJson(const FString& FileName);

	UFUNCTION(BlueprintCallable, Category = "PlayOffTournamentComponent")
		void LoadJson(const FString& FileName);
};

