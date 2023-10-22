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

public:
	// Sets default values for this character's properties
	APlayerCharacter();

	void Authenticate(FText* id, FText* pwd);
	void ToggleLoginButton(bool on) const;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
