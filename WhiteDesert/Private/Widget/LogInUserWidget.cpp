// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/LogInUserWidget.h"
#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"
#include "DB.h"
#include "Components/EditableText.h"

void ULogInUserWidget::NativeConstruct()
{
	if (ButtonLogIn)
		ButtonLogIn->OnClicked.AddDynamic(this, &ULogInUserWidget::OnButtonLogInClicked);
}

void ULogInUserWidget::OnButtonLogInClicked()
{
	if (EditableTextID && EditableTextPassword)
	{
		AActor* db = UGameplayStatics::GetActorOfClass(GetWorld(), ADB::StaticClass());
		if (db)
		{
			FText ID = EditableTextID->GetText();
			FText PWD = EditableTextPassword->GetText();
			ADB* DB = Cast<ADB>(db);
			DB->Authenticate(&ID,&PWD);
		}
	}
}
