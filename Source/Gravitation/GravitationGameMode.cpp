// Copyright Epic Games, Inc. All Rights Reserved.

#include "GravitationGameMode.h"
#include "GravitationPawn.h"

AGravitationGameMode::AGravitationGameMode()
{
	// set default pawn class to our character class
	DefaultPawnClass = AGravitationPawn::StaticClass();
}