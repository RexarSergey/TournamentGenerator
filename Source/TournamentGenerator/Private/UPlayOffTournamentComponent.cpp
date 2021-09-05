// Fill out your copyright notice in the Description page of Project Settings.


#include "UPlayOffTournamentComponent.h"

// Sets default values for this component's properties
UPlayOffTournamentComponent::UPlayOffTournamentComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UPlayOffTournamentComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...

}


// Called every frame
void UPlayOffTournamentComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UPlayOffTournamentComponent::GenerateTournamentNoRating(const TArray<int32>& arr, TEnumAsByte<EPlayOffTournamentGenerator> Generator)
{
	Tournament = FPlayOffTournament(arr);
	Tournament.SetGenerator(Generator);
	Tournament.GenerateTournament();
}

void UPlayOffTournamentComponent::GenerateTournament(const TArray<int32>& arr, const TArray<int32>& rating, TEnumAsByte<EPlayOffTournamentGenerator> Generator)
{
	Tournament = FPlayOffTournament(arr, rating);
	Tournament.SetGenerator(Generator);
	Tournament.GenerateTournament();
}

void UPlayOffTournamentComponent::RandomizeWinners()
{
	Tournament.RandomizeWinners();
}

void UPlayOffTournamentComponent::PrintTournamentInfo()
{
	Tournament.PrintTournamentInfo();
}

void UPlayOffTournamentComponent::SetMemberStatus(int32 MemberId, MemberStatus Status)
{
	Tournament.SetMemberStatus(MemberId, Status);
}

TArray<int32> UPlayOffTournamentComponent::GetCurrentStageMembers()
{
	return Tournament.GetCurrentStageMembers();
}

TArray<int32> UPlayOffTournamentComponent::GetWinnersByStageIndex(int32 StageIndex)
{
	return Tournament.GetWinnersId(StageIndex);
}

TArray<int32> UPlayOffTournamentComponent::GetWinners()
{
	return GetWinnersByStageIndex(GetCurrentStageIndex() - 1);
}

int32 UPlayOffTournamentComponent::GetMatchCount()
{
	return Tournament.GetMatchCount();
}

int32 UPlayOffTournamentComponent::GetCurrentStageIndex()
{
	return Tournament.GetCurrentStageIndex();
}

bool UPlayOffTournamentComponent::IsTournamentFinished()
{
	return Tournament.IsTournamentFinished();

}

FMatch UPlayOffTournamentComponent::GetMatchByIndex(int32 MatchIndex)
{
	FMatch match;
	match.FirstPlayer = Tournament.GetMatchByIndex(MatchIndex).Get<0>();
	match.SecondPlayer = Tournament.GetMatchByIndex(MatchIndex).Get<1>();
	match.Winner = Tournament.GetMatchByIndex(MatchIndex).Get<2>();
	return match;
}

void UPlayOffTournamentComponent::SaveJson(const FString& FileName)
{

	Tournament.SaveJson(FileName);
}

void UPlayOffTournamentComponent::LoadJson(const FString& FileName)
{
	Tournament.LoadJson(FileName);
}

void UPlayOffTournamentComponent::ChooseWinner(int32 WinnerId)
{
	Tournament.ChooseWinner(WinnerId);
}

bool UPlayOffTournamentComponent::NextStage()
{
	return Tournament.NextStage();
}
