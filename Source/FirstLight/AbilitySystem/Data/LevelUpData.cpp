// Fill out your copyright notice in the Description page of Project Settings.


#include "LevelUpData.h"

int32 ULevelUpData::FindLevelForXP(int32 XP)
{
	int32 Level = 1;
	bool bSearching = true;
	while (bSearching)
	{
		if (LevelUpData.Num() - 1 <= Level) return Level;

		if (XP >= LevelUpData[Level].NextLevelXPRequirement)
		{
			++Level;
		}
		else
		{
			bSearching = false;
		}
	}
	return Level;
}