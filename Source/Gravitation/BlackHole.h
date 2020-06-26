// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Planet.h"
#include "BlackHole.generated.h"

/**
 * 
 */
UCLASS()
class GRAVITATION_API ABlackHole : public APlanet
{
	GENERATED_BODY()

	UPROPERTY(Category = Mesh, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class UStaticMeshComponent* EventHorizonComponent;
		
public:
	ABlackHole();

	virtual void Tick(float DeltaTime) override;

	FORCEINLINE float GetEventHorizon() const { return EventHorizon; }

protected:
	virtual void BeginPlay() override;
	
private:

	UPROPERTY(Category = Attributes, EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	float EventHorizon;
};
