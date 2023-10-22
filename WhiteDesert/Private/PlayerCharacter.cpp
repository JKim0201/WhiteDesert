// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCharacter.h"
#include "LogInUserWidget.h"
#include "DataBaseActorComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
APlayerCharacter::APlayerCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
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
	LoginWidget->ToggleLoginButton(on);
}


void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

