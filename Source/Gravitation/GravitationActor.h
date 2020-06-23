#pragma once

#include "CoreMinimal.h"
#include "MoveComponent.h"

class GravitationActor
{
public:
	GravitationActor();
	
protected:
	UPROPERTY(Category = Camera, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class UMoveComponent* MoveComponent;
};