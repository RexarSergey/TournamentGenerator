// Fill out your copyright notice in the Description page of Project Settings.


#include "RR.h"

RR::RR()
{
}

RR::RR(TArray<int32>& Members) : BaseClass(Members)
{
	for (int32 i = 0; i < Members.Num(); i++)
	{
		MembersIndex.Add(i);
		WinsCountMap.Add(Members[i], 0);
	}

	if (Members.Num() % 2 != 0)
		MembersIndex.Add(-1);
}

RR::RR(TArray<int32>& Members, TArray<int32>& RatingPoints) : BaseClass(Members, RatingPoints)
{
	for (int32 i = 0; i < Members.Num(); i++)
	{
		MembersIndex.Add(i);
		WinsCountMap.Add(Members[i], 0);
	}

	if (Members.Num() % 2 != 0)
		MembersIndex.Add(-1);
}

RR::~RR()
{
}

void RR::GenerateTournament()
{
}

void RR::PrintTournamentInfo()
{
}

void RR::SortMembersRM()
{
	RatingPoints.Sort([](const int32& A, const int32& B) {
		return A > B;
	});
	Members.Sort([&, TArray(RatingMap)](const int32& A, const int32& B) {
		return RatingMap[A] > RatingMap[B];
	});

	TArray<TTuple<int32, int32>> LastHalfInfo;
	int32 Half = Members.Num() % 2 == 0 ? (Members.Num() / 2) : ((Members.Num() / 2) + 1);
	for (int32 i = Half; i < Members.Num(); i++)
	{
		LastHalfInfo.Add(TTuple<int32, int32>(Members[i], RatingPoints[i]));
	}

	LastHalfInfo.Sort([](const TTuple<int32, int32>& A, const TTuple<int32, int32>& B) {
		return A.Get<1>() < B.Get<1>();
	});

	for (int32 i = 0; i < LastHalfInfo.Num(); i++)
	{
		Members[i + Half] = LastHalfInfo[i].Get<0>();
		RatingPoints[i + Half] = LastHalfInfo[i].Get<1>();
	}
}

void RR::SortMembersBT()
{
	RatingPoints.Sort([](const int32& A, const int32& B) {
		return A > B;
	});
	Members.Sort([&, TArray(RatingMap)](const int32& A, const int32& B) {
		return RatingMap[A] > RatingMap[B];
	});
}

void RR::Rotate(TArray<int32>& Indexes)
{
	int32 Count = Indexes.Num();

	if (Count < 2)
		return;

	int32 LastIndex = Count - 1;
	int32 Factor = Count / 2;

	int32 TopRightIndex = Factor - 1;
	int32 TopRightTeam = Indexes[TopRightIndex];

	int32 BottomLeftIndex = Factor;
	int32 BottomLeftTeam = Indexes[BottomLeftIndex];

	for (int32 i = TopRightIndex; i > 0; i--)
	{
		Indexes[i] = Indexes[i - 1];
	}
	for (int32 i = BottomLeftIndex; i < LastIndex; i++)
	{
		Indexes[i] = Indexes[i + 1];
	}

	Indexes[1] = BottomLeftTeam;
	Indexes[LastIndex] = TopRightTeam;
}

// Circle method
void RR::GenerateRoundMethod()
{
	if (RatingPoints.Num() != 0)
		SortMembersRM();

	int32 TeamCount = MembersIndex.Num();

	if (TeamCount < 2)
		return;

	int32 Rounds = TeamCount - 1;
	int32 Half = TeamCount / 2;
	int32 Key;

	// Creating tours.
	for (int32 Round = 1; Round <= Rounds; Round++)
	{
		Key = 0;

		// Creating rounds.
		for (int32& Index : MembersIndex)
		{
			if (Key >= Half)
				break;

			int32 TeamIndex1 = Index;
			int32 TeamIndex2 = MembersIndex[Key + Half];

			if (Round % 2 == 0)
			{
				if (TeamIndex1 == -1 || TeamIndex2 == -1)
					Matches.Add(TTuple<int32, int32, int32>(TeamIndex1, TeamIndex2, -2));
				else
					Matches.Add(TTuple<int32, int32, int32>(TeamIndex1, TeamIndex2, -1));
			}
			else
			{
				if (TeamIndex1 == -1 || TeamIndex2 == -1)
					Matches.Add(TTuple<int32, int32, int32>(TeamIndex2, TeamIndex1, -2));
				else
					Matches.Add(TTuple<int32, int32, int32>(TeamIndex2, TeamIndex1, -1));
			}
			Key++;
		}
		// Rotate members.
		Rotate(MembersIndex);
	}
}

// Berger tables
void RR::GenerateBergerTables()
{
	if (RatingPoints.Num() != 0)
		SortMembersBT();

	int32 TeamCount = MembersIndex.Num();

	if (TeamCount < 2)
		return;

	int32 Tours = TeamCount - 1;
	int32 Half = TeamCount / 2;

	int32 TeamIndex1;
	int32 TeamIndex2;
	int32 TeamIndex3;
	int32 TeamIndex4;

	// Creating first tour.
	for (int32 i = 0; i < Half; i++)
	{
		TeamIndex1 = MembersIndex[i];
		TeamIndex2 = MembersIndex[Tours - i];

		if (TeamIndex1 == -1 || TeamIndex2 == -1)
			Matches.Add(TTuple<int32, int32, int32>(TeamIndex1, TeamIndex2, -2));
		else
			Matches.Add(TTuple<int32, int32, int32>(TeamIndex1, TeamIndex2, -1));
	}

	// Creating next tours.
	for (int32 Tour = 2; Tour <= Tours; Tour++)
	{
		TTuple<int32, int32, int32> LastRound;
		if (Tour % 2 == 0)
		{
			// First match.
			TeamIndex1 = Matches[Matches.Num() - Half].Get<1>();
			TeamIndex2 = Matches[Matches.Num() - 1].Get<1>();

			// Last match.
			TeamIndex3 = Matches[Matches.Num() - Half].Get<0>();
			TeamIndex4 = Matches[Matches.Num() - Half + 1].Get<0>();

			if (TeamIndex1 == -1 || TeamIndex2 == -1)
				Matches.Add(TTuple<int32, int32, int32>(TeamIndex1, TeamIndex2, -2));
			else
				Matches.Add(TTuple<int32, int32, int32>(TeamIndex1, TeamIndex2, -1));

			if (TeamIndex3 == -1 || TeamIndex4 == -1)
				LastRound = TTuple<int32, int32, int32>(TeamIndex3, TeamIndex4, -2);
			else
				LastRound = TTuple<int32, int32, int32>(TeamIndex3, TeamIndex4, -1);
		}
		else
		{
			// First match.
			TeamIndex1 = Matches[Matches.Num() - 1].Get<1>();
			TeamIndex2 = Matches[Matches.Num() - Half].Get<0>();

			// Last match.
			TeamIndex3 = Matches[Matches.Num() - Half].Get<1>();
			TeamIndex4 = Matches[Matches.Num() - Half + 1].Get<0>();

			if (TeamIndex1 == -1 || TeamIndex2 == -1)
				Matches.Add(TTuple<int32, int32, int32>(TeamIndex1, TeamIndex2, -2));
			else
				Matches.Add(TTuple<int32, int32, int32>(TeamIndex1, TeamIndex2, -1));

			if (TeamIndex3 == -1 || TeamIndex4 == -1)
				LastRound = TTuple<int32, int32, int32>(TeamIndex3, TeamIndex4, -2);
			else
				LastRound = TTuple<int32, int32, int32>(TeamIndex3, TeamIndex4, -1);
		}

		// Mid-matches
		for (int32 i = 1; i < Half - 1; i++)
		{
			TeamIndex1 = Matches[Matches.Num() - i * 2 - 1].Get<1>();
			TeamIndex2 = Matches[Matches.Num() - i * 2].Get<0>();

			if (TeamIndex1 == -1 || TeamIndex2 == -1)
				Matches.Add(TTuple<int32, int32, int32>(TeamIndex1, TeamIndex2, -2));
			else
				Matches.Add(TTuple<int32, int32, int32>(TeamIndex1, TeamIndex2, -1));
		}

		// Adding last match.
		Matches.Add(LastRound);
	}
}

void RR::SetWinnerByMatchNumber(int32 MatchNumber, int32 Chooser)
{
	int32 TeamIndex1 = Matches[MatchNumber].Get<0>();
	int32 TeamIndex2 = Matches[MatchNumber].Get<1>();

	if ((TeamIndex1 == -1 || TeamIndex2 == -1) &&
		(MembersStatusMap[Members[TeamIndex1]] == 0 || MembersStatusMap[Members[TeamIndex2]] == 0))
	{
		Matches[MatchNumber].Get<2>() = -2;
		return;
	}

	float Chance = (float)RatingPoints[TeamIndex1] / (RatingPoints[TeamIndex1] + RatingPoints[TeamIndex2]);
	switch (Chooser)
	{
	case 1:
		WinsCountMap[Members[TeamIndex1]]++;
		Matches[MatchNumber].Get<2>() = TeamIndex1;
		break;

	case 2:
		WinsCountMap[Members[TeamIndex2]]++;
		Matches[MatchNumber].Get<2>() = TeamIndex2;
		break;

	case 3:
		if (FMath::FRandRange(0.0f, 1.0f) < 0.5f)
		{
			WinsCountMap[Members[TeamIndex1]]++;
			Matches[MatchNumber].Get<2>() = TeamIndex1;
		}
		else
		{
			WinsCountMap[Members[TeamIndex2]]++;
			Matches[MatchNumber].Get<2>() = TeamIndex2;
		}
		break;

	case 4:
		if (FMath::FRandRange(0.0f, 1.0f) < Chance)
		{
			WinsCountMap[Members[TeamIndex1]]++;
			Matches[MatchNumber].Get<2>() = TeamIndex1;
		}
		else
		{
			WinsCountMap[Members[TeamIndex2]]++;
			Matches[MatchNumber].Get<2>() = TeamIndex2;
		}
		break;

	default:
		break;
	}
}

// Улучшить.
void RR::DisqualificationByIndex(int32 Index)
{
	WinsCountMap[Members[Index]] = 0;
	MembersStatusMap[Members[Index]] = 0;
}

FString RR::GetAllMatchesInfo()
{
	if (Matches.Num() == 0)
		return FString::Printf(TEXT("Tournament hasn't been generated.\n"));

	FString Text = TEXT("");
	int32 Team1;
	int32 Team2;
	FString MatchResult;

	int32 TourNumber = 1;
	int32 MatchesInTour = MembersIndex.Num() / 2;
	int32 MatchStatus;

	for (int32 i = 0; i < Matches.Num(); i++)
	{
		if (i % MatchesInTour == 0)
			Text += FString::Printf(TEXT("Tour %d.\n"), TourNumber++);

		MatchStatus = Matches[i].Get<2>();

		switch (MatchStatus) {
		case -1:
			MatchResult = FString::Printf(TEXT("The match isn't over yet."));
			break;
		case -2:
			MatchResult = FString::Printf(TEXT("The match was skipped."));
			break;
		default:
			MatchResult = FString::Printf(TEXT("Member \'ID%d\' won the match."), Members[MatchStatus]);
			break;
		}

		Team1 = Matches[i].Get<0>() != -1 ? Members[Matches[i].Get<0>()] : Members[Matches[i].Get<1>()];
		Team2 = Matches[i].Get<1>() != -1 ? Members[Matches[i].Get<1>()] : Members[Matches[i].Get<0>()];

		Text += FString::Printf(TEXT("Match %d: \'ID%d\' vs \'ID%d.\' Result: %s\n"), i, Team1, Team2, *MatchResult);
	}
	return Text;
}

FString RR::GetWinStatistics()
{
	if (Matches.Num() == 0)
		return FString::Printf(TEXT("Tournament hasn't been generated.\n"));

	MembersPlace.Empty();

	for (int32 i = 0; i < Members.Num(); i++)
	{
		TTuple<int32, int32> Info(WinsCountMap[Members[i]], Members[i]);
		MembersPlace.Add(Info);
	}

	MembersPlace.Sort([](const TTuple<int32, int32>& A, const TTuple<int32, int32>& B) {
		return A.Get<0>() > B.Get<0>();
	});

	FString Text = TEXT("");
	for (TTuple<int32, int32>& Place : MembersPlace)
	{
		Text += FString::Printf(TEXT("Member \'ID%d\' player wins %d times.\n"), Place.Get<1>(), Place.Get<0>());
	}

	return Text;
}

FString RR::GetAllMembersInfo()
{
	FString Text = TEXT("");
	for (int32 i = 0; i < Members.Num(); i++)
	{
		Text += FString::Printf(TEXT("Member \'ID%d\'. Rating points: %d. Won %d times.\n"), Members[i], RatingPoints[i], WinsCountMap[Members[i]]);
	}

	return Text;
}

FString RR::GetMemberInfoByIndex(int32 Index)
{
	return FString::Printf(TEXT("Member \'ID%d\'. Rating points: %d. Won %d times."), Members[Index], RatingPoints[Index], WinsCountMap[Members[Index]]);
}

FString RR::GetMatchInfoByNumber(int32 Index)
{
	if (Matches.Num() == 0)
		return FString::Printf(TEXT("Tournament hasn't been generated.\n"));
	if (Index < 0)
		return FString::Printf(TEXT("Wrong number of the match.\n"));

	FString Text = TEXT("");
	int32 Team1;
	int32 Team2;
	FString MatchResult;

	int32 MatchStatus = Matches[Index].Get<2>();

	switch (MatchStatus) {
	case -1:
		MatchResult = FString::Printf(TEXT("The match isn't over yet."));
		break;
	case -2:
		MatchResult = FString::Printf(TEXT("The match was skipped."));
		break;
	default:
		MatchResult = FString::Printf(TEXT("ID\'%d\' won the match."), Members[MatchStatus]);
		break;
	}

	Team1 = Matches[Index].Get<0>() != -1 ? Members[Matches[Index].Get<0>()] : Members[Matches[Index].Get<1>()];
	Team2 = Matches[Index].Get<1>() != -1 ? Members[Matches[Index].Get<1>()] : Members[Matches[Index].Get<0>()];

	Text += FString::Printf(TEXT("Match %d: \'ID%d\' vs \'ID%d.\' Result: %s\n"), Index, Team1, Team2, *MatchResult);

	return Text;
}

void RR::SetWinnersManually(TArray<int32> Winner)
{
	if (Winner.Num() != Matches.Num())
		return; //FString::Printf(TEXT("Array have to be size equals %d.\n"), Matches.Num());

	//FString Text = TEXT("");
	int32 TeamIndex1;
	int32 TeamIndex2;
	for (int32 i = 0; i < Matches.Num(); i++)
	{
		TeamIndex1 = Matches[i].Get<0>();
		TeamIndex2 = Matches[i].Get<1>();

		if ((TeamIndex1 == -1 || TeamIndex2 == -1) ||
			(MembersStatusMap[Members[TeamIndex1]] == 0 || MembersStatusMap[Members[TeamIndex2]] == 0))
		{
			Matches[i].Get<2>() = -2;

			//Text += FString::Printf(TEXT("Match %d: skip.\n"), (i + 1));
			continue;
		}

		if (Winner[i] == 0)
		{
			WinsCountMap[Members[TeamIndex1]]++;
			Matches[i].Get<2>() = Matches[i].Get<0>();

			//Text += FString::Printf(TEXT("Match %d: player '%s' won the match!\n"), (i + 1), *(Team1));
		}
		else if (Winner[i] == 1)
		{
			WinsCountMap[Members[TeamIndex2]]++;
			Matches[i].Get<2>() = Matches[i].Get<1>();

			//Text += FString::Printf(TEXT("Match %d: player '%s' won the match!\n"), (i + 1), *(Team2));
		}
	}

	//return Text;
}

void RR::SetWinnersRandomly()
{
	//FString Text = TEXT("");
	int32 TeamIndex1;
	int32 TeamIndex2;
	for (int32 i = 0; i < Matches.Num(); i++)
	{
		TeamIndex1 = Matches[i].Get<0>();
		TeamIndex2 = Matches[i].Get<1>();

		if ((TeamIndex1 == -1 || TeamIndex2 == -1) ||
			(MembersStatusMap[Members[TeamIndex1]] == 0 || MembersStatusMap[Members[TeamIndex2]] == 0))
		{
			Matches[i].Get<2>() = -2;

			//Text += FString::Printf(TEXT("Match %d: skip.\n"), (i + 1));
			continue;
		}

		if (FMath::FRandRange(0.0f, 1.0f) < 0.5f)
		{
			WinsCountMap[Members[TeamIndex1]]++;
			Matches[i].Get<2>() = Matches[i].Get<0>();

			//Text += FString::Printf(TEXT("Match %d: player '%s' won the match!\n"), (i + 1), *(Team1));
		}
		else
		{
			WinsCountMap[Members[TeamIndex2]]++;
			Matches[i].Get<2>() = Matches[i].Get<1>();

			//Text += FString::Printf(TEXT("Match %d: player '%s' won the match!\n"), (i + 1), *(Team2));
		}
	}

	//return Text;
}

void RR::SetWinnersRandomlyWithRating()
{
	//FString Text = TEXT("");
	int32 TeamIndex1;
	int32 TeamIndex2;
	for (int32 i = 0; i < Matches.Num(); i++)
	{
		TeamIndex1 = Matches[i].Get<0>();
		TeamIndex2 = Matches[i].Get<1>();

		if ((TeamIndex1 == -1 || TeamIndex2 == -1) ||
			(MembersStatusMap[Members[TeamIndex1]] == 0 || MembersStatusMap[Members[TeamIndex2]] == 0))
		{
			Matches[i].Get<2>() = -2;

			//Text += FString::Printf(TEXT("Match %d: skip.\n"), (i + 1));
			continue;
		}

		float Chance1 = (float)RatingPoints[Matches[i].Get<0>()] / (RatingPoints[Matches[i].Get<0>()] + RatingPoints[Matches[i].Get<1>()]);
		//float Chance2 = (float)Members[Matches[i].Get<1>()].Get<1>() / (Members[Matches[i].Get<0>()].Get<1>() + Members[Matches[i].Get<1>()].Get<1>());

		if (FMath::FRandRange(0.0f, 1.0f) < Chance1)
		{
			WinsCountMap[Members[TeamIndex1]]++;
			Matches[i].Get<2>() = Matches[i].Get<0>();

			//Text += FString::Printf(TEXT("Match %d: player '%s' won the match!\n"), (i + 1), *(Team1));
		}
		else
		{
			WinsCountMap[Members[TeamIndex2]]++;
			Matches[i].Get<2>() = Matches[i].Get<1>();

			//Text += FString::Printf(TEXT("Match %d: player '%s' won the match!\n"), (i + 1), *(Team2));
		}
	}

	//return Text;
}

void RR::SetAllRatingPoints(TArray<int32> NewRatingPoints)
{
	for (int i = 0; i < NewRatingPoints.Num(); i++)
	{
		RatingPoints[i] = NewRatingPoints[i];
	}
}

void RR::SetRatingPointsByIndex(int32 Index, int32 NewRatingPoints)
{
	RatingPoints[Index] = NewRatingPoints;
}

int32 RR::GetMatchesCount()
{
	return Matches.Num();
}

FString RR::ChooseWinner()
{
	GetWinStatistics();

	FirstPlace.Empty();
	int32 Index = 0;

	FirstPlace.Add(MembersPlace[Index]);
	//while ((Index + 1) < MembersPlace.Num() &&
	//	MembersPlace[Index].Get<0>() == MembersPlace[Index + 1].Get<0>())
	//{
	//	++Index;
	//	FirstPlace.Add(MembersPlace[Index]);
	//}

	//if (FirstPlace.Num() == 1)
	//{
		return FString::Printf(TEXT("Winner is Member \'ID %d\'\n"), FirstPlace[0].Get<1>());
	/*}
	else
	{
		FString Text = FString::Printf(TEXT("We need Extra Matches.\n"));

		TArray<int32> NewMembers;
		for (const TTuple<int32, int32>& Member : FirstPlace)
			NewMembers.Add(Member.Get<1>());

		RR ExtraTournament(NewMembers);
		ExtraTournament.GenerateRoundMethod();
		ExtraTournament.SetWinnersRandomly();

		Text += ExtraTournament.GetAllMatchesInfo();
		Text += ExtraTournament.ChooseWinner();

		for (const int32& Member : NewMembers)
			WinsCountMap[Member] += ExtraTournament.WinsCountMap[Member];

		return Text;
	}*/
}

bool RR::IsOnePersonOnFirstPlace()
{
	GetWinStatistics();

	FirstPlace.Empty();
	int32 Index = 0;

	FirstPlace.Add(MembersPlace[Index]);
	while ((Index + 1) < MembersPlace.Num() &&
		MembersPlace[Index].Get<0>() == MembersPlace[Index + 1].Get<0>())
	{
		++Index;
		FirstPlace.Add(MembersPlace[Index]);
	}

	if (FirstPlace.Num() == 1)
	{
		return true;
	}
	return false;
}

FString RR::GenerateExtraMatches()
{
	FString Text = FString::Printf(TEXT("We need Extra Matches.\n"));

	TArray<int32> NewMembers;
	for (const TTuple<int32, int32>& Member : FirstPlace)
		NewMembers.Add(Member.Get<1>());

	RR ExtraTournament(NewMembers);
	ExtraTournament.GenerateRoundMethod();
	ExtraTournament.SetWinnersRandomly();

	Text += ExtraTournament.GetAllMatchesInfo();

	for (const int32& Member : NewMembers)
		WinsCountMap[Member] += ExtraTournament.WinsCountMap[Member];

	return Text;
}

bool RR::LoadJson(const FString& FileName)
{
	FString FullPathContent = FPaths::ProjectContentDir() + FileName;
	FString JsonStr;

	if (!FPlatformFileManager::Get().GetPlatformFile().FileExists(*FullPathContent))
	{
		return false;
	}

	FFileHelper::LoadFileToString(JsonStr, *FullPathContent);
	TSharedRef<TJsonReader<TCHAR>> JsonReader = TJsonReaderFactory<TCHAR>::Create(JsonStr);
	TSharedPtr<FJsonObject> JsonObject = MakeShareable(new FJsonObject);
	FJsonSerializer::Deserialize(JsonReader, JsonObject);

	JsonUtils::LoadIntArray(JsonObject, Members, "members");
	JsonUtils::LoadMapArray(JsonObject, RatingMap, "ratingMap", "first", "second");
	JsonUtils::LoadMapArray(JsonObject, MembersStatusMap, "membersStatusMap", "first", "second");

	JsonUtils::LoadIntArray(JsonObject, MembersIndex, "membersIndex");
	JsonUtils::LoadTripleTupleArray(JsonObject, Matches, "matches", "first", "second", "third");
	JsonUtils::LoadMapArray(JsonObject, WinsCountMap, "winsCountMap", "first", "second");

	return false;// todo: change
}

bool RR::SaveJson(const FString& FileName)
{
	FRRTournamentStruct TournamentStruct;

	for (const TTuple<int32, int32, int32 >& Match : this->Matches)
		UE_LOG(LogTemp, Warning, TEXT("%d %d %d\n"), Match.Get<0>(), Match.Get<1>(), Match.Get<2>());

	TArray<FTripleTuple> MatchesNested;
	for (const TTuple<int32, int32, int32 >& Match : Matches)
	{
		FTripleTuple NestedTuple;

		NestedTuple.first = Match.Get<0>();
		NestedTuple.second = Match.Get<1>();
		NestedTuple.third = Match.Get<2>();

		MatchesNested.Add(NestedTuple);
	}

	TournamentStruct.Members = Members;
	TournamentStruct.RatingMap = JsonUtils::GetArrayFromMap(RatingMap);
	TournamentStruct.MembersStatusMap = JsonUtils::GetArrayFromMap(MembersStatusMap);

	TournamentStruct.MembersIndex = MembersIndex;
	TournamentStruct.Matches = MatchesNested;
	TournamentStruct.WinsCountMap = JsonUtils::GetArrayFromMap(WinsCountMap);

	FString FullPathContent = FPaths::ProjectContentDir() + FileName;
	FString JsonStr;

	FJsonObjectConverter::UStructToJsonObjectString(TournamentStruct, JsonStr);
	FFileHelper::SaveStringToFile(*JsonStr, *FullPathContent);

	return false;
}
