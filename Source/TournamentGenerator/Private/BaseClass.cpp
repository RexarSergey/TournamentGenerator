// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseClass.h"

//BaseClass::BaseClass(TArray<TTuple<FString, int32>> Info)
//{
//	Members = Info;
//}

BaseClass::BaseClass()
{
}

BaseClass::BaseClass(const TArray<int32>& Members)
{
	this->Members = Members;

	for (int32 i = 0; i < Members.Num(); i++)
	{
		MembersStatusMap.Add(Members[i], 1);
	}
}

BaseClass::BaseClass(const TArray<int32>& Members, const TArray<int32>& RaitingPoints) : BaseClass(Members)
{
	this->RatingPoints = RaitingPoints;

	for (int32 i = 0; i < Members.Num(); i++)
	{
		RatingMap.Add(Members[i], RaitingPoints[i]);
		MembersStatusMap.Add(Members[i], 1);
	}
}

BaseClass::~BaseClass()
{
}
