// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "CoreMinimal.h"
#include "MoveComponent.h"
#include "Planet.generated.h"

UCLASS()
class GRAVITATION_API APlanet : public AActor
{
	GENERATED_BODY()

protected:
	UPROPERTY(Category = Mesh, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class UStaticMeshComponent* MeshComponent;

	UPROPERTY(Category = Movement, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	UMoveComponent* PlanetMoveComponent;

	UPROPERTY(Category = Mesh, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class UStaticMeshComponent* GraviRadiusComponent;

public:	
	// Sets default values for this actor's properties
	APlanet();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	FORCEINLINE const float GetActiveRadius() const { return ActiveGraviRadius; }

	FORCEINLINE bool IsGravitationInverted() const { return InvertedGravitation; }

protected:

	UPROPERTY(Category = Attributes, EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	float ActiveGraviRadius;

	bool InvertedGravitation;
};
