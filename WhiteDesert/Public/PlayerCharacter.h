// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "PlayerCharacter.generated.h"

class ULogInUserWidget;
class UDataBaseActorComponent;

UCLASS()
class WHITEDESERT_API APlayerCharacter : public ACharacter
{
	GENERATED_BODY()

	ULogInUserWidget* LoginWidget;

	UDataBaseActorComponent* DataBaseComponent;

	int UserID;
public:
	APlayerCharacter();

	void Authenticate(FText* id, FText* pwd);
	void ToggleLoginButton(bool on) const;
	void SetUserID(const int uid);
protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
