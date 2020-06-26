// Copyright Epic Games, Inc. All Rights Reserved.

#include "GravitationGameMode.h"
#include "Engine/Public/EngineUtils.h"

AGravitationGameMode::AGravitationGameMode()
{
	PrimaryActorTick.bCanEverTick = true;
	// set default pawn class to our character class
	DefaultPawnClass = AGravitationPawn::StaticClass();
}

void AGravitationGameMode::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	UWorld* World = GetWorld();
	if (!World) return;

	APlayerController* Player = World->GetPlayerControllerIterator()->Get();
	if (!Player) return;

	AGravitationPawn* Pawn = static_cast<AGravitationPawn*>(Player->GetPawn());
	if (!Pawn) return;

	for (TActorIterator<ABlackHole> it(World); it; ++it)
	{
		if (ABlackHole* BlackHole = *it)
		{
			if (IsInBlackHole(Pawn, BlackHole))
			{
				Pawn->EnablePlayerInput(false);
				return;
			}
		}
	}

	Pawn->EnablePlayerInput(true);
}

bool AGravitationGameMode::IsInBlackHole(AGravitationPawn* Pawn, ABlackHole* BlackHole)
{
	if (!Pawn || !BlackHole) return false;

	UStaticMeshComponent* PawnMesh = static_cast<UStaticMeshComponent*>(Pawn->GetRootComponent());
	UStaticMeshComponent* BlackHoleMesh = static_cast<UStaticMeshComponent*>(BlackHole->GetRootComponent());
	if (!PawnMesh || !BlackHoleMesh) return false;

	const FVector& PawnPos = PawnMesh->GetCenterOfMass();
	const FVector& BlackHolePos = BlackHoleMesh->GetCenterOfMass();
	
	const float EventHorizon = BlackHole->GetEventHorizon();
	const FVector diff = PawnPos - BlackHolePos;

	return diff.Size() <= EventHorizon;
}