// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TournamentEnums.h"	
#include "RR.h"
#include "URRTournamentComponent.generated.h"


UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class TOURNAMENTGENERATOR_API URRTournamentComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	URRTournamentComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	RR Tournament;

	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable, Category = "Tournament Functions")
		FString GenerateNewTournament(TArray<int32> MembersID, TArray<int32> RatingPoints, TEnumAsByte<GenerationMethod> Method);

	UFUNCTION(BlueprintCallable, Category = "Tournament Functions")
		FString GetAllMatchesInfo();
	UFUNCTION(BlueprintCallable, Category = "Tournament Functions")
		FString GetWinStatistics();
	UFUNCTION(BlueprintCallable, Category = "Tournament Functions")
		FString GetAllMembersInfo();
	UFUNCTION(BlueprintCallable, Category = "Tournament Functions")
		FString GetMemberInfoByMemberIndex(int32 MemberIndex);
	UFUNCTION(BlueprintCallable, Category = "Tournament Functions")
		FString GetMatchInfoByMatchNumber(int32 MatchNumber);

	UFUNCTION(BlueprintCallable, Category = "Tournament Functions")
		void SetAllWinners(TArray<int32> Winners, TEnumAsByte<RandomizeMethod> Method);
	UFUNCTION(BlueprintCallable, Category = "Tournament Functions")
		void SetWinnerByMatchNumber(int32 MatchNumber, TEnumAsByte<WinChooser> Chooser);

	UFUNCTION(BlueprintCallable, Category = "Tournament Functions")
		void SetAllRatingPoints(TArray<int32> RatingPoints);
	UFUNCTION(BlueprintCallable, Category = "Tournament Functions")
		void SetRatingPointsByMemberIndex(int32 MemberIndex, int32 RatingPoints);

	UFUNCTION(BlueprintCallable, Category = "Tournament Functions")
		void DisqualificationByMemberIndex(int32 MemberIndex);

	UFUNCTION(BlueprintCallable, Category = "Tournament Functions")
		int32 GetMatchesCount();
	UFUNCTION(BlueprintCallable, Category = "Tournament Functions")
		FString ChooseWinner();
	UFUNCTION(BlueprintCallable, Category = "Tournament Functions")
		bool IsOnePersonOnFirstPlace();
	UFUNCTION(BlueprintCallable, Category = "Tournament Functions")
		FString GenerateExtraMatches();

	UFUNCTION(BlueprintCallable, Category = "Tournament Functions")
		void SaveJson(const FString& FileName);
	UFUNCTION(BlueprintCallable, Category = "Tournament Functions")
		void LoadJson(const FString& FileName);
};
