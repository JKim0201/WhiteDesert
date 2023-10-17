// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "LogInUserWidget.generated.h"


class UButton;
class UTextBlock;
class UEditableText;
/**
 * 
 */
UCLASS()
class WHITEDESERT_API ULogInUserWidget : public UUserWidget
{
	GENERATED_BODY()

	UPROPERTY(meta = (BindWidget))
	UButton* ButtonLogIn;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* TextLogIn;

	UPROPERTY(meta = (BindWidget))
	UEditableText* EditableTextID;

	UPROPERTY(meta = (BindWidget))
	UEditableText* EditableTextPassword;

	void NativeConstruct() override;

protected:
	UFUNCTION()
	void OnButtonLogInClicked();
};
