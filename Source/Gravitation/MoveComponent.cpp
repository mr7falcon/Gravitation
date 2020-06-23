// Fill out your copyright notice in the Description page of Project Settings.


#include "MoveComponent.h"
#include "Planet.h"
#include "Engine/Public/EngineUtils.h"

// Sets default values for this component's properties
UMoveComponent::UMoveComponent()
	: Speed(0.f),
	  Accel(0.f),
	  Velocity(0.f, 0.f, 0.f)
{
	PrimaryComponentTick.bCanEverTick = true;
}


// Called when the game starts
void UMoveComponent::BeginPlay()
{
	Super::BeginPlay();
}


// Called every frame
void UMoveComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	AActor* Owner = GetOwner();
	if (!Owner) return;

	const float diff = Accel * DeltaTime;
	Velocity += Owner->GetActorForwardVector() * diff;

	SimulateGravitation(DeltaTime);

	const FVector Movement = Velocity * DeltaTime;

	// If non-zero size, move this actor
	if (Movement.SizeSquared() > 0.f)
	{
		if (USceneComponent* RootComponent = Owner->GetRootComponent())
		{
			const FRotator NewRotation = Movement.Rotation();
			RootComponent->MoveComponent(Movement, NewRotation, true);
		}
	}
}

void UMoveComponent::SimulateGravitationWithActor(APlanet* Influencer, const float dt)
{
	AActor* Owner = GetOwner();
	if (!Owner || !Influencer || Owner == Influencer) return;

	UStaticMeshComponent* OwnerMesh = static_cast<UStaticMeshComponent*>(Owner->GetRootComponent());
	UStaticMeshComponent* InfluencerMesh = static_cast<UStaticMeshComponent*>(Influencer->GetRootComponent());
	if (!OwnerMesh || !InfluencerMesh) return;

	const FVector& p1 = OwnerMesh->GetCenterOfMass();
	const FVector& p2 = InfluencerMesh->GetCenterOfMass();

	const float m2 = InfluencerMesh->GetMass();

	static const float RAD_MIN = 0.1f;
	static const float G = 20000000.f;

	const FVector2D dpos(p2 - p1);
	const float rsqd = dpos.SizeSquared();
	if (rsqd < RAD_MIN) return;
	
	const float r = sqrt(rsqd);
	const float rmax = Influencer->GetActiveRadius();
	if (r > rmax) return;

	const float a = m2 / rsqd * G;
	const FVector2D dvel = a * dpos / r * dt;
	Velocity.X += dvel.X;
	Velocity.Y += dvel.Y;
}

void UMoveComponent::SimulateGravitation(const float DeltaTime)
{
	UWorld* World = GetWorld();
	if (!World) return;

	for (TActorIterator<APlanet> it(World); it; ++it)
	{
		if (APlanet* Planet = *it)
		{
			SimulateGravitationWithActor(Planet, DeltaTime);
		}
	}
}

void UMoveComponent::SetSpeed(const float speed)
{
	Speed = speed;

	if (AActor* Owner = GetOwner())
	{
		Velocity = Owner->GetActorForwardVector() * Speed;
	}
}