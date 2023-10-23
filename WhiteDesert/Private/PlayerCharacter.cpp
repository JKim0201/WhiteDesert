#include "PlayerCharacter.h"
#include "LogInUserWidget.h"
#include "DataBaseActorComponent.h"
#include "Kismet/GameplayStatics.h"

APlayerCharacter::APlayerCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	UWorld* World = GetWorld();
	if (World)
	{	
		APlayerController* PC = World->GetFirstPlayerController();
		PC->bShowMouseCursor = true;
		static ConstructorHelpers::FClassFinder<ULogInUserWidget>Widget(TEXT("/Game/Blueprints/Widgets/WBP_LogIn"));
		LoginWidget = CreateWidget<ULogInUserWidget>(PC, Widget.Class);
		if (LoginWidget)
			LoginWidget->AddToViewport();
	}

	DataBaseComponent = CreateDefaultSubobject<UDataBaseActorComponent>(TEXT("DataBaseComponent"));
}

void APlayerCharacter::Authenticate(FText* id, FText* pwd)
{
	DataBaseComponent->Authenticate(id, pwd);
}

void APlayerCharacter::ToggleLoginButton(bool on) const
{
	if (LoginWidget)
		LoginWidget->ToggleLoginButton(on);	
}

void APlayerCharacter::SetUserID(const int uid)
{
	UserID = uid;
}


void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
}

void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

