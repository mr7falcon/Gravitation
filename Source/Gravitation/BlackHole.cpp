// Fill out your copyright notice in the Description page of Project Settings.


#include "BlackHole.h"
#include "Engine/CollisionProfile.h"

ABlackHole::ABlackHole()
	: APlanet(),
	  EventHorizon(0.f)
{
	static ConstructorHelpers::FObjectFinder<UStaticMesh> EventHorizonMesh(TEXT("/Game/Geometry/Meshes/Plane.Plane"));
	if (!EventHorizonMesh.Succeeded()) return;
	EventHorizonComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BlackHoleEventHorizonRadius"));
	EventHorizonComponent->SetupAttachment(RootComponent);
	EventHorizonComponent->SetStaticMesh(EventHorizonMesh.Object);
	EventHorizonComponent->SetCollisionProfileName(UCollisionProfile::NoCollision_ProfileName);

	static ConstructorHelpers::FObjectFinder<UMaterialInterface> EventHorizonMaterial(TEXT("/Game/Geometry/Materials/GraviRadCircle.GraviRadCircle"));
	if (!EventHorizonMaterial.Succeeded()) return;
	EventHorizonComponent->SetMaterial(0, EventHorizonMaterial.Object);
}

void ABlackHole::BeginPlay()
{
	APlanet::BeginPlay();

	if (EventHorizonComponent)
	{
		FVector Origin, Extent;
		GetActorBounds(true, Origin, Extent);
		const float radius = fmax(0.001f, Extent.Y);

		const float scale = EventHorizon / radius;
		EventHorizonComponent->SetRelativeScale3D(FVector(scale, scale, 0.f));

		UMaterialInstanceDynamic* MI = UMaterialInstanceDynamic::Create(EventHorizonComponent->GetMaterial(0), this);
		const float relativeRad = 0.5f;
		MI->SetScalarParameterValue(TEXT("InnerRadius"), radius / EventHorizon * relativeRad);
		MI->SetScalarParameterValue(TEXT("OuterRadius"), relativeRad);
		const FVector color = FVector(0.f, 255.f, 255.f);
		MI->SetVectorParameterValue(TEXT("Color"), color);
		EventHorizonComponent->SetMaterial(0, MI);
	}
}

void ABlackHole::Tick(float DeltaTime)
{
	APlanet::Tick(DeltaTime);
}
