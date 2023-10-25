// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "PlayerCharacter.generated.h"

class ULogInUserWidget;
class UDataBaseActorComponent;
class UCameraComponent;
class USpringArmComponent;

UCLASS()
class WHITEDESERT_API APlayerCharacter : public ACharacter
{
	GENERATED_BODY()

	UPROPERTY()
	ULogInUserWidget* LoginWidget;
	
	UPROPERTY()
	UDataBaseActorComponent* DataBaseComponent;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	UCameraComponent* Camera;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	USpringArmComponent* SpringArm;

	UPROPERTY()
	int UserID;

public:
	APlayerCharacter();

	void Authenticate(FText* id, FText* pwd);
	void ToggleLoginButton(bool on) const;
	void SetUserID(const int uid);
	void MoveToInGame(void);
protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
