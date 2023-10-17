// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "WhiteDesertGameMode.generated.h"

UCLASS(minimalapi)
class AWhiteDesertGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	AWhiteDesertGameMode();
protected:
	virtual void BeginPlay() override;
};



