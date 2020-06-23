// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Components/StaticMeshComponent.h"
#include "MoveComponent.generated.h"

class APlanet;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class GRAVITATION_API UMoveComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UMoveComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	FORCEINLINE const float GetSpeed() const { return Speed; }
	FORCEINLINE void SetSpeed(const float speed);

	FORCEINLINE const float GetAccel() const { return Accel; }
	FORCEINLINE void SetAccel(const float accel) { Accel = accel; }

private:
	UPROPERTY(Category = Gameplay, EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	float Speed;

	UPROPERTY(Category = Gameplay, EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	float Accel;

	UPROPERTY(Category = Gameplay, EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	FVector Velocity;

	void SimulateGravitation(const float DeltaTime);
	void SimulateGravitationWithActor(APlanet* Influencer, const float dt);
};
