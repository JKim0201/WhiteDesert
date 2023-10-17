// Copyright Epic Games, Inc. All Rights Reserved.

#include "WhiteDesertGameMode.h"
#include "WhiteDesertCharacter.h"
#include "UObject/ConstructorHelpers.h"
#include "Screen/LogInScreen.h"

AWhiteDesertGameMode::AWhiteDesertGameMode()
{
	// set default pawn class to our Blueprinted character
	/*static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}*/

	
}

void AWhiteDesertGameMode::BeginPlay()
{
	GetWorld()->SpawnActor<ALogInScreen>(ALogInScreen::StaticClass());
}
