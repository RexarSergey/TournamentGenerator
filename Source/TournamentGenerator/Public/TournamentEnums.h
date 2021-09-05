// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

/**
 *
 */
UENUM(BlueprintType)
enum EPlayOffTournamentGenerator
{
	Random                   UMETA(DisplayName = "Random"),
	WorstAgainstBest    UMETA(DisplayName = "WorstAgainstBest"),
	Directly					 UMETA(DisplayName = "Directly")
};

UENUM(BlueprintType)
enum MemberStatus
{
	NotActive  = 0     UMETA(DisplayName = "NotActive"),
	Active					 UMETA(DisplayName = "Active")
};

UENUM()
enum GenerationMethod
{
	RoundMethod     UMETA(DisplayName = "RoundMethod"),
	BergerTables		UMETA(DisplayName = "BergerTables"),
};

UENUM()
enum RandomizeMethod
{
	MethodManualy						UMETA(DisplayName = "Manualy"),
	MethodRandomly					UMETA(DisplayName = "Randomly"),
	MethodRandomlyWithRank   UMETA(DisplayName = "RandomlyWithRank"),
};

UENUM()
enum WinChooser
{
	ChooserFirst								UMETA(DisplayName = "FirstTeamWon"),
	ChooserSecond							UMETA(DisplayName = "SecondTeamWon"),
	ChooserRandomly						UMETA(DisplayName = "ChooseWinnerRandomly"),
	ChooserRandomlyWithRank		UMETA(DisplayName = "ChooseWinnerRandomlyWithRank"),
};
