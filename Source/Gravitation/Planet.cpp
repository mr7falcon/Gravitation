// Fill out your copyright notice in the Description page of Project Settings.


#include "Planet.h"
#include "Engine/CollisionProfile.h"

APlanet::APlanet()
	: ActiveGraviRadius(0.f),
	  InvertedGravitation(false)
{
	PrimaryActorTick.bCanEverTick = true;

	static ConstructorHelpers::FObjectFinder<UStaticMesh> PlanetMesh(TEXT("/Game/Geometry/Meshes/Sphere.Sphere"));
	if (!PlanetMesh.Succeeded()) return;
	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PlanetMesh"));
	RootComponent = MeshComponent;
	MeshComponent->SetCollisionProfileName(UCollisionProfile::BlockAll_ProfileName);
	MeshComponent->SetStaticMesh(PlanetMesh.Object);

	PlanetMoveComponent = CreateDefaultSubobject<UMoveComponent>(TEXT("PlanetMovement"));

	static ConstructorHelpers::FObjectFinder<UStaticMesh> ActiveRadiusMesh(TEXT("/Game/Geometry/Meshes/Plane.Plane"));
	if (!ActiveRadiusMesh.Succeeded()) return;
	GraviRadiusComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PlanetActiveGravitationRadius"));
	GraviRadiusComponent->SetupAttachment(RootComponent);
	GraviRadiusComponent->SetStaticMesh(ActiveRadiusMesh.Object);
	GraviRadiusComponent->SetCollisionProfileName(UCollisionProfile::NoCollision_ProfileName);

	static ConstructorHelpers::FObjectFinder<UMaterialInterface> ActiveRadiusMaterial(TEXT("/Game/Geometry/Materials/GraviRadCircle.GraviRadCircle"));
	if (!ActiveRadiusMaterial.Succeeded()) return;
	GraviRadiusComponent->SetMaterial(0, ActiveRadiusMaterial.Object);
}

void APlanet::BeginPlay()
{
	Super::BeginPlay();
	
	if (MeshComponent && GraviRadiusComponent)
	{
		FVector Origin, Extent;
		GetActorBounds(true, Origin, Extent);
		const float radius = fmax(0.001f, Extent.Y);

		const float scale = ActiveGraviRadius / radius;
		GraviRadiusComponent->SetRelativeScale3D(FVector(scale, scale, 0.f));

		UMaterialInstanceDynamic* MI = UMaterialInstanceDynamic::Create(GraviRadiusComponent->GetMaterial(0), this);
		const float relativeRad = 0.5f;
		MI->SetScalarParameterValue(TEXT("InnerRadius"), radius / ActiveGraviRadius * relativeRad);
		MI->SetScalarParameterValue(TEXT("OuterRadius"), relativeRad);
		const float c1 = MeshComponent->GetMass();
		const float c2 = 255.f - abs(c1);
		const FVector color = InvertedGravitation ? FVector(0.f, c2, c1) : FVector(c1, c2, 0.f);
		MI->SetVectorParameterValue(TEXT("Color"), color);
		GraviRadiusComponent->SetMaterial(0, MI);
	}
}

void APlanet::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}