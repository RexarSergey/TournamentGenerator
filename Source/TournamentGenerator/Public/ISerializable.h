// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

/**
 * 
 */
class TOURNAMENTGENERATOR_API ISerializable
{
public:

	virtual bool LoadJson(const FString& FileName) = 0;
	virtual bool SaveJson(const FString& FileName) = 0;

	~ISerializable();
};
