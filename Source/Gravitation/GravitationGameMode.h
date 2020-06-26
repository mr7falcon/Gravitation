// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "GravitationPawn.h"
#include "BlackHole.h"
#include "GravitationGameMode.generated.h"

UCLASS(MinimalAPI)
class AGravitationGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	AGravitationGameMode();

	virtual void Tick(float DeltaTime) override;

private:
	bool IsInBlackHole(AGravitationPawn* Pawn, ABlackHole* BlackHole);
};



