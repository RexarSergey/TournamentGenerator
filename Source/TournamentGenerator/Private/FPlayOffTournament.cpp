// Fill out your copyright notice in the Description page of Project Settings.



#include "FPlayOffTournament.h"


FPlayOffTournament::FPlayOffTournament() : BaseClass()
{
	int64 DateInSeconds = FDateTime::Now().ToUnixTimestamp();
	s.Initialize(DateInSeconds);
}

FPlayOffTournament::FPlayOffTournament(const TArray<int32>& TournamentMembers) : BaseClass(TournamentMembers)
{
	int64 DateInSeconds = FDateTime::Now().ToUnixTimestamp();
	s.Initialize(DateInSeconds);
}

FPlayOffTournament::FPlayOffTournament(const TArray<int32>& TournamentMembers, const TArray<int32>& TournamentMembersRating) : BaseClass(TournamentMembers, TournamentMembersRating)
{
	int64 DateInSeconds = FDateTime::Now().ToUnixTimestamp();
	s.Initialize(DateInSeconds);
}

FPlayOffTournament::~FPlayOffTournament()
{
}

void FPlayOffTournament::GenerateTournament()
{
	StageCount = 0;
	CurrentStageIndex = 0;
	StageWinners.Empty();
	CurrentStage.Empty();
	CurrentStageMembers.Empty();
	TournamentInfo.Empty();
	RoundMap.Empty();
	switch (GenerationType)
	{
	case Random:
	{
		GenerateRandomTournament();
		break;
	}
	case WorstAgainstBest:
	{
		GenerateWorstAgainstBestTournament();
		break;
	}
	case Directly:
	{
		GenerateDirectTournament();
		break;
	}
	}
}

void FPlayOffTournament::PrintTournamentInfo()
{
	for (int32 i = 0; i < TournamentInfo.Num(); ++i)
	{
		UE_LOG(LogTemp, Warning, TEXT("Stage %d\n"), i);
		for (int32 j = 0; j < TournamentInfo[i].Num(); ++j)
		{
			UE_LOG(LogTemp, Warning, TEXT("%d vs %d, winner: %d\n"), TournamentInfo[i][j].Get<0>(), TournamentInfo[i][j].Get<1>(), TournamentInfo[i][j].Get<2>());
		}
		UE_LOG(LogTemp, Warning, TEXT("\n\n"));
	}
}

void FPlayOffTournament::ChooseWinner(const int32& Round, const int32& Winner)
{
	if (Winner == 0)
	{
		ChooseWinner(CurrentStage[Round].Get<0>());
	}
	else if (Winner == 1)
	{
		ChooseWinner(CurrentStage[Round].Get<1>());
	}
}

void FPlayOffTournament::ChooseWinner(const int32& WinnerId)
{
	if (RoundMap.Contains(WinnerId) && MembersStatusMap[WinnerId] == Active)
	{
		if (CurrentStage[RoundMap[WinnerId]].Get<0>() == WinnerId)
		{
			CurrentStage[RoundMap[WinnerId]].Get<2>() = 0;
		}
		else
		{
			CurrentStage[RoundMap[WinnerId]].Get<2>() = 1;
		}
	}
}

bool FPlayOffTournament::NextStage()
{
	if (StageCount <= 0)
	{
		return false;
	}

	int32 WinnersCount = 0;
	for (TTuple<int32, int32, int32>& m : CurrentStage)
	{
		int32 FirstPlayer = m.Get<0>();
		int32 SecondPlayer = m.Get<1>();
		if (m.Get<2>() != 0 && m.Get<2>() != 1 && MembersStatusMap[FirstPlayer] == Active && MembersStatusMap[SecondPlayer] == Active)
		{
			return false;
		}
		if (MembersStatusMap[FirstPlayer] == Active || MembersStatusMap[SecondPlayer] == Active)
		{
			WinnersCount++;
		}
	}


	int32 NewStageCount = 0;
	while ((1 << NewStageCount) < WinnersCount)
	{
		++NewStageCount;
	}
	int32 NumberOfLucky = (1 << NewStageCount) - WinnersCount;

	TArray<int32> Winners;
	TournamentInfo.Add(CurrentStage);
	TArray<TTuple<int32, int32, int32>> NewStage;
	RoundMap.Empty();

	if (NewStageCount > 0) {
		for (int32 i = 0; i < NumberOfLucky;)
		{
			if (CurrentStage[i].Get<2>() == -1)
			{
				continue;
			}
			TTuple<int32, int32, int32> NewMatch = CreateMatchFromWinners(CurrentStage[i], CurrentStage[i]);
			RoundMap.Add(NewMatch.Get<0>(), NewStage.Num());
			Winners.Add(NewMatch.Get<0>());
			NewStage.Add(NewMatch);
			i++;
		}

		for (int32 i = NumberOfLucky; i < CurrentStage.Num();)
		{
			if (CurrentStage[i].Get<2>() == -1)
			{
				i++;
				continue;
			}
			int32 j = i + 1;
			while (CurrentStage[j].Get<2>() == -1)
			{
				j++;
			}
			TTuple<int32, int32, int32> NewMatch = CreateMatchFromWinners(CurrentStage[i], CurrentStage[j]);
			RoundMap.Add(NewMatch.Get<0>(), NewStage.Num());
			RoundMap.Add(NewMatch.Get<1>(), NewStage.Num());
			Winners.Add(NewMatch.Get<0>());
			Winners.Add(NewMatch.Get<1>());
			NewStage.Add(NewMatch);
			i = j + 1;
		}
	}
	else
	{
		if (CurrentStage[0].Get<2>() == 1)
		{
			Winners.Add(CurrentStage[0].Get<1>());
		}
		else if (CurrentStage[0].Get<2>() == 0)
		{
			Winners.Add(CurrentStage[0].Get<0>());
		}
	}
	CurrentStageMembers = TArray<int32>(Winners);
	StageWinners.Add(Winners);
	CurrentStage = NewStage;
	StageCount = NewStageCount;
	++CurrentStageIndex;
	return true;
}

void FPlayOffTournament::RandomizeWinners()
{
	while (StageCount > 0)
	{
		for (int i = 0; i < CurrentStage.Num(); ++i)
		{
			ChooseWinner(i, s.FRand() < 0.5f ? 0 : 1);

		}
		NextStage();
	}
}

TArray<int32> FPlayOffTournament::GetWinnersId(const int32& Stage)
{
	if (Stage >= StageWinners.Num())
	{
		return TArray<int32>();
	}
	return StageWinners[Stage];
}

TArray<int32> FPlayOffTournament::GetMembers()
{
	return Members;
}

TArray<int32> FPlayOffTournament::GetCurrentStageMembers()
{
	return CurrentStageMembers;
}

TArray<TTuple<int32, int32, int32>> FPlayOffTournament::GetCurrentStage()
{
	return CurrentStage;
}

TTuple<int32, int32, int32> FPlayOffTournament::GetMatchByIndex(const int32& MatchIndex)
{
	return CurrentStage[MatchIndex];
}

int32 FPlayOffTournament::GetCurrentStageIndex()
{
	return CurrentStageIndex;
}

int32 FPlayOffTournament::GetMatchCount()
{
	return CurrentStage.Num();
}

bool FPlayOffTournament::IsTournamentFinished()
{
	return StageCount == 0;
}


void FPlayOffTournament::ShuffleTArray(TArray<int32>& Arr)
{
	for (int32 i = Arr.Num() - 1; i > 0; --i)
	{
		int32 j = FMath::Floor(s.FRand() * (i + 1));
		Arr.Swap(i, j);
	}
}

TTuple<int32, int32, int32> FPlayOffTournament::CreateMatchFromWinners(const TTuple<int32, int32, int32>& Match1, const TTuple<int32, int32, int32>& Match2)
{
	TTuple<int32, int32, int32> NewMatch;
	NewMatch.Get<0>() = Match1.Get<2>() ? Match1.Get<1>() : Match1.Get<0>();
	NewMatch.Get<1>() = Match2.Get<2>() ? Match2.Get<1>() : Match2.Get<0>();
	return NewMatch;
}

void FPlayOffTournament::SetGenerator(const EPlayOffTournamentGenerator& Generator)
{
	GenerationType = Generator;
}


void FPlayOffTournament::SetMemberStatus(const int32& MemberId, const MemberStatus& Status)
{
	if (MembersStatusMap[MemberId] == NotActive && Status == Active)
	{
		CurrentStage[RoundMap[MemberId]].Get<2>() = -1;
	}
	MembersStatusMap[MemberId] = Status;
	int32 FirstPlayer = CurrentStage[RoundMap[MemberId]].Get<0>();
	int32 SecondPlayer = CurrentStage[RoundMap[MemberId]].Get<1>();
	if (MembersStatusMap[FirstPlayer] == NotActive && MembersStatusMap[SecondPlayer] == NotActive)
	{
		CurrentStage[RoundMap[MemberId]].Get<2>() = -1;
	}
	if (MembersStatusMap[FirstPlayer] == NotActive && MembersStatusMap[SecondPlayer] == Active)
	{
		ChooseWinner(SecondPlayer);
	}
	if (MembersStatusMap[FirstPlayer] == Active && MembersStatusMap[SecondPlayer] == NotActive)
	{
		ChooseWinner(FirstPlayer);
	}
}


void FPlayOffTournament::GenerateRandomTournament()
{
	ShuffleTArray(Members);
	GenerateDirectTournament();
}


void FPlayOffTournament::GenerateWorstAgainstBestTournament()
{
	if (Members.Num() == 0)
	{
		return;
	}
	while ((1 << StageCount) < Members.Num())
	{
		++StageCount;
	}
	int32 NumberOfLucky = (1 << StageCount) - Members.Num();

	Members.Sort([&, TMap(RatingMap)](const int32& lhs, const int32& rhs){
		return RatingMap[lhs] > RatingMap[rhs];
	});
	for (int32 i = 0; i < (1 << (StageCount - 1)); ++i)
	{
		CurrentStage.Add(TTuple<int32, int32, int32>(-1, -1, -1));
	}

	for (int32 i = 0; i < NumberOfLucky; ++i)
	{
		if (i % 2 == 0)
		{
			CurrentStage[i / 2] = TTuple<int32, int32, int32>(Members[i], Members[i], 0);
			RoundMap.Add(Members[i], i / 2);
		}
		else
		{
			CurrentStage[CurrentStage.Num() - i / 2 - 1] = TTuple<int32, int32, int32>(Members[i], Members[i], 0);
			RoundMap.Add(Members[i], CurrentStage.Num() - i / 2 - 1);
		}
	}
	int32 worst = Members.Num() - 1;
	int32 best = NumberOfLucky;
	while (best < worst)
	{
		if (best % 2 == 0)
		{
			CurrentStage[best / 2] = TTuple<int32, int32, int32>(Members[best], Members[worst], -1);
			RoundMap.Add(Members[best], best / 2);
			RoundMap.Add(Members[worst], best / 2);
		}
		else
		{
			CurrentStage[CurrentStage.Num() - best / 2 - 1] = TTuple<int32, int32, int32>(Members[best], Members[worst], -1);
			RoundMap.Add(Members[best], CurrentStage.Num() - best / 2 - 1);
			RoundMap.Add(Members[worst], CurrentStage.Num() - best / 2 - 1);
		}
		CurrentStageMembers.Add(Members[best]);
		CurrentStageMembers.Add(Members[worst]);
		--worst;
		++best;
	}
}

void FPlayOffTournament::GenerateDirectTournament()
{
	if (Members.Num() == 0)
	{
		return;
	}
	while ((1 << StageCount) < Members.Num())
	{
		++StageCount;
	}
	int32 NumberOfLucky = (1 << StageCount) - Members.Num();
	for (int32 i = 0; i < NumberOfLucky; ++i)
	{
		CurrentStage.Add(TTuple<int32, int32, int32>(Members[i], Members[i], 0));
		RoundMap.Add(Members[i], i);
	}
	for (int32 i = NumberOfLucky; i < Members.Num() - 1; i += 2)
	{
		RoundMap.Add(Members[i], CurrentStage.Num());
		RoundMap.Add(Members[i + 1], CurrentStage.Num());
		CurrentStageMembers.Add(Members[i]);
		CurrentStageMembers.Add(Members[i + 1]);
		CurrentStage.Add(TTuple<int32, int32, int32>(Members[i], Members[i + 1], -1));
	}
}


bool FPlayOffTournament::LoadJson(const FString& FileName)
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

	CurrentStageIndex = JsonObject->GetIntegerField("currentStageIndex");
	UE_LOG(LogTemp, Warning, TEXT("CurrentStageIndex: %d\n"), JsonObject->GetIntegerField("currentStageIndex"));

	StageCount = JsonObject->GetIntegerField("stageCount");
	UE_LOG(LogTemp, Warning, TEXT("StageCount: %d\n"), JsonObject->GetIntegerField("stageCount"));

	JsonUtils::LoadIntArray(JsonObject, CurrentStageMembers, "currentStageMembers");
	JsonUtils::LoadTripleTupleArray(JsonObject, CurrentStage, "currentStage", "first", "second", "third");
	JsonUtils::LoadNestedIntArray(JsonObject, StageWinners, "stageWinners", "intArr");
	JsonUtils::LoadNestedTripleTupleArray(JsonObject, TournamentInfo, "tournamentInfo", "tripleTupleArr", "first", "second", "third");
	JsonUtils::LoadMapArray(JsonObject, RoundMap, "roundMap", "first", "second");
	JsonUtils::LoadMapArray(JsonObject, MembersStatusMap, "membersStatusMap", "first", "second");
	JsonUtils::LoadMapArray(JsonObject, RatingMap, "ratingMap", "first", "second");

	return false; //todo delete
}


bool FPlayOffTournament::SaveJson(const FString& FileName)
{
	FPlayOffTournamentStruct TournamentStruct;
	TArray<FIntArray> StageWinnersNested;
	for (const TArray<int32>& arr : StageWinners)
	{
		FIntArray NestedArr;
		NestedArr.IntArr = arr;
		StageWinnersNested.Add(NestedArr);
	}

	TArray<FTripleTuple> CurrentStageNested;
	for (const TTuple<int32, int32, int32 >& t : CurrentStage)
	{
		FTripleTuple NestedTuple;

		NestedTuple.first = t.Get<0>();
		NestedTuple.second = t.Get<1>();
		NestedTuple.third = t.Get<2>();
		CurrentStageNested.Add(NestedTuple);
	}

	TArray<FTripleTupleArray> TournamentInfoNested;
	for (const TArray<TTuple<int32, int32, int32>>& arr : TournamentInfo)
	{
		FTripleTupleArray TripleTupleArrayNested;
		for (const TTuple<int32, int32, int32>& t : arr)
		{
			FTripleTuple NestedTuple;
			NestedTuple.first = t.Get<0>();
			NestedTuple.second = t.Get<1>();
			NestedTuple.third = t.Get<2>();
			TripleTupleArrayNested.TripleTupleArr.Add(NestedTuple);
		}
		TournamentInfoNested.Add(TripleTupleArrayNested);
	}

	TournamentStruct.Members = Members;
	TournamentStruct.CurrentStageIndex = CurrentStageIndex;
	TournamentStruct.StageCount = StageCount;
	TournamentStruct.CurrentStageMembers = CurrentStageMembers;
	TournamentStruct.CurrentStage = CurrentStageNested;
	TournamentStruct.StageWinners = StageWinnersNested;
	TournamentStruct.TournamentInfo = TournamentInfoNested;
	TournamentStruct.RoundMap = JsonUtils::GetArrayFromMap(RoundMap);
	TournamentStruct.MembersStatusMap = JsonUtils::GetArrayFromMap(MembersStatusMap);
	TournamentStruct.RatingMap = JsonUtils::GetArrayFromMap(RatingMap);

	FString FullPathContent = FPaths::ProjectContentDir() + FileName;
	FString JsonStr;

	FJsonObjectConverter::UStructToJsonObjectString(TournamentStruct, JsonStr);
	FFileHelper::SaveStringToFile(*JsonStr, *FullPathContent);
	return false;
}
