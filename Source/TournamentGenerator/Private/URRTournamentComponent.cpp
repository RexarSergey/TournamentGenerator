// Fill out your copyright notice in the Description page of Project Settings.


#include "URRTournamentComponent.h"

// Sets default values for this component's properties
URRTournamentComponent::URRTournamentComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

// Called when the game starts
void URRTournamentComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...

}


// Called every frame
void URRTournamentComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

RR Tournament;

FString URRTournamentComponent::GenerateNewTournament(TArray<int32> MembersID, TArray<int32> RatingPoints, TEnumAsByte<GenerationMethod> Method)
{
	if (MembersID.Num() < 2)
		return FString::Printf(TEXT("Length of arrays \'MembersID\' must be greater than 1.\n"));

	if (Method == RoundMethod)
	{
		Tournament = RR(MembersID, RatingPoints);
		Tournament.GenerateRoundMethod();

		return FString::Printf(TEXT("Round Method tournament was generated with %d members.\n"), MembersID.Num());
	}
	else if (Method == BergerTables)
	{
		Tournament = RR(MembersID, RatingPoints);
		Tournament.GenerateBergerTables();

		return FString::Printf(TEXT("Berger Tables tournament was generated with %d members.\n"), MembersID.Num());
	}

	return FString::Printf(TEXT("Somethings wrong."));
}

FString URRTournamentComponent::GetAllMatchesInfo()
{
	return Tournament.GetAllMatchesInfo();
}

FString URRTournamentComponent::GetWinStatistics()
{
	return Tournament.GetWinStatistics();
}

FString URRTournamentComponent::GetAllMembersInfo()
{
	return Tournament.GetAllMembersInfo();
}

FString URRTournamentComponent::GetMemberInfoByMemberIndex(int32 MemberIndex)
{
	return Tournament.GetMemberInfoByIndex(MemberIndex);
}

FString URRTournamentComponent::GetMatchInfoByMatchNumber(int32 MatchNumber)
{
	return Tournament.GetMatchInfoByNumber(MatchNumber);
}

void URRTournamentComponent::SetAllWinners(TArray<int32> Winners, TEnumAsByte<RandomizeMethod> Method)
{
	switch (Method) {
	case MethodManualy:
		Tournament.SetWinnersManually(Winners);
		break;
	case MethodRandomly:
		Tournament.SetWinnersRandomly();
		break;
	case MethodRandomlyWithRank:
		Tournament.SetWinnersRandomlyWithRating();
	default:
		break;
	}
}

void URRTournamentComponent::SetWinnerByMatchNumber(int32 MatchNumber, TEnumAsByte<WinChooser> Chooser)
{
	if (MatchNumber >= 0)
		switch (Chooser) {
		case ChooserFirst:
			Tournament.SetWinnerByMatchNumber(MatchNumber, 1);
			break;
		case ChooserSecond:
			Tournament.SetWinnerByMatchNumber(MatchNumber, 2);
			break;
		case ChooserRandomly:
			Tournament.SetWinnerByMatchNumber(MatchNumber, 3);
			break;
		case ChooserRandomlyWithRank:
			Tournament.SetWinnerByMatchNumber(MatchNumber, 4);
			break;
		default:
			break;
		}
}

void URRTournamentComponent::SetAllRatingPoints(TArray<int32> RatingPoints)
{
	Tournament.SetAllRatingPoints(RatingPoints);
}

void URRTournamentComponent::SetRatingPointsByMemberIndex(int32 MemberIndex, int32 RatingPoints)
{
	Tournament.SetRatingPointsByIndex(MemberIndex, RatingPoints);
}

void URRTournamentComponent::DisqualificationByMemberIndex(int32 MemberIndex)
{
	Tournament.DisqualificationByIndex(MemberIndex);
}

int32 URRTournamentComponent::GetMatchesCount()
{
	return Tournament.GetMatchesCount();
}

FString URRTournamentComponent::ChooseWinner()
{
	return Tournament.ChooseWinner();
}

bool URRTournamentComponent::IsOnePersonOnFirstPlace()
{
	return Tournament.IsOnePersonOnFirstPlace();
}

FString URRTournamentComponent::GenerateExtraMatches()
{
	return Tournament.GenerateExtraMatches();
}

void URRTournamentComponent::SaveJson(const FString& FileName)
{
	Tournament.SaveJson(FileName);
}

void URRTournamentComponent::LoadJson(const FString& FileName)
{
	Tournament.LoadJson(FileName);
}

