// Fill out your copyright notice in the Description page of Project Settings.


#include "Screen/LogInScreen.h"
#include "Widget/LogInUserWidget.h"

ALogInScreen::ALogInScreen()
{
	PrimaryActorTick.bCanEverTick = false;
	UWorld* World = GetWorld();
	if (World)
	{
		APlayerController* PlayerController = World->GetFirstPlayerController();
		if (PlayerController)
		{
			static ConstructorHelpers::FClassFinder<ULogInUserWidget>Widget(TEXT("/Game/Blueprints/WBP_LogIn"));
			UserWidget = CreateWidget<ULogInUserWidget>(PlayerController, Widget.Class);
			if (UserWidget)
				UserWidget->AddToViewport();
		}

		PlayerController->bShowMouseCursor = true;
	}

}

void ALogInScreen::BeginPlay()
{
	Super::BeginPlay();
	
}


void ALogInScreen::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

