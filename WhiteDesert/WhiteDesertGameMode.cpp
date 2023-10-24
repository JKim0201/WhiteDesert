#include "WhiteDesertGameMode.h"
#include "PlayerCharacter.h"
#include "Kismet/GameplayStatics.h"


AWhiteDesertGameMode::AWhiteDesertGameMode()
{
	static ConstructorHelpers::FClassFinder<ACharacter>BPPlayerCharacterClass(TEXT("/Game/Blueprints/Characters/BP_PlayerCharacter"));
	if (BPPlayerCharacterClass.Class != NULL)
		DefaultPawnClass = BPPlayerCharacterClass.Class;
}