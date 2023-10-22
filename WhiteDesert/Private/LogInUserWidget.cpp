// Fill out your copyright notice in the Description page of Project Settings.


#include "LogInUserWidget.h"
#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"
#include "Components/EditableText.h"
#include "Components/TextBlock.h"
#include "PlayerCharacter.h"


void ULogInUserWidget::NativeConstruct()
{
	if (ButtonLogIn)
		ButtonLogIn->OnClicked.AddDynamic(this, &ULogInUserWidget::OnButtonLogInClicked);
}

void ULogInUserWidget::ToggleLoginButton(bool on)
{
	if (on)
	{
		TextLogIn->SetText(FText::FromString("Log in"));
		ButtonLogIn->SetIsEnabled(true);
	}
	else
	{
		TextLogIn->SetText(FText::FromString("Waiting for connection"));
		ButtonLogIn->SetIsEnabled(false);
	}
}

void ULogInUserWidget::OnButtonLogInClicked()
{
	FText ID = EditableTextID->GetText();
	FText PWD = EditableTextPassword->GetText();

	Cast<APlayerCharacter>(GetOwningPlayerPawn())->Authenticate(&ID, &PWD);
}
