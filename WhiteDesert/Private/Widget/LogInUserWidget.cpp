// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/LogInUserWidget.h"
#include "Components/Button.h"


void ULogInUserWidget::NativeConstruct()
{
	if (ButtonLogIn)
		ButtonLogIn->OnClicked.AddDynamic(this, &ULogInUserWidget::OnButtonLogInClicked);
}

void ULogInUserWidget::OnButtonLogInClicked()
{
	
	if (EditableTextID && EditableTextPassword)
	{
		UE_LOG(LogTemp, Warning, TEXT("hi"));
	}
}
