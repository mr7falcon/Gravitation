// Copyright Epic Games, Inc. All Rights Reserved.

#include "GravitationPawn.h"
#include "TimerManager.h"
#include "UObject/ConstructorHelpers.h"
#include "Camera/CameraComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Engine/CollisionProfile.h"
#include "Engine/StaticMesh.h"
#include "Kismet/GameplayStatics.h"

const FName AGravitationPawn::MoveForwardBinding("MoveForward");

AGravitationPawn::AGravitationPawn()
	: MoveForwardAccel(300.f),
	  MoveBackAccel(300.f)
{	
	static ConstructorHelpers::FObjectFinder<UStaticMesh> ShipMesh(TEXT("/Game/TwinStick/Meshes/TwinStickUFO.TwinStickUFO"));
	// Create the mesh component
	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ShipMesh"));
	RootComponent = MeshComponent;
	MeshComponent->SetCollisionProfileName(UCollisionProfile::Pawn_ProfileName);
	MeshComponent->SetStaticMesh(ShipMesh.Object);
	
	// Create a camera boom...
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->SetUsingAbsoluteRotation(true); // Don't want arm to rotate when ship does
	CameraBoom->TargetArmLength = 2500.f;
	CameraBoom->SetRelativeRotation(FRotator(-80.f, 0.f, 0.f));
	CameraBoom->bDoCollisionTest = false; // Don't want to pull camera in when it collides with level

	// Create a camera...
	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("TopDownCamera"));
	CameraComponent->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	CameraComponent->bUsePawnControlRotation = false;	// Camera does not rotate relative to arm

	ShipMoveComponent = CreateDefaultSubobject<UMoveComponent>(TEXT("ShipMovement"));
	ShipMoveComponent->SetSpeed(500.f);
}

void AGravitationPawn::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	// set up gameplay key bindings
	if (PlayerInputComponent)
	{
		PlayerInputComponent->BindAxis(MoveForwardBinding);
	}
}

void AGravitationPawn::Tick(float DeltaSeconds)
{
	//Using for acceleration
	const float ForwardValue = GetInputAxisValue(MoveForwardBinding);
	if (ForwardValue > 0.f)
	{
		ShipMoveComponent->SetAccel(MoveForwardAccel);
	}
	else if (ForwardValue < 0.f)
	{
		ShipMoveComponent->SetAccel(-MoveBackAccel);
	}
}