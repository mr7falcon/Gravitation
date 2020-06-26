// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "MoveComponent.h"
#include "GravitationPawn.generated.h"

UCLASS(Blueprintable)
class AGravitationPawn : public APawn
{
	GENERATED_BODY()

	/** The camera */
	UPROPERTY(Category = Camera, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* CameraComponent;

	/** Camera boom positioning the camera above the character */
	UPROPERTY(Category = Camera, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;

	UPROPERTY(Category = Movement, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	UMoveComponent* ShipMoveComponent;

	UPROPERTY(Category = Mesh, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* MeshComponent;

public:
	AGravitationPawn();

	// Begin Actor Interface
	virtual void Tick(float DeltaSeconds) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* InputComponent) override;
	
	// Static names for axis bindings
	static const FName MoveForwardBinding;

	FORCEINLINE void EnablePlayerInput(bool enable) { InputEnabled = enable; }

private:
	UPROPERTY(Category = Attributes, EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	float MoveForwardAccel;

	UPROPERTY(Category = Attributes, EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	float MoveBackAccel;

	bool InputEnabled;
};

