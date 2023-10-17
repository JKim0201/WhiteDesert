// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "LogInScreen.generated.h"

class ULogInUserWidget;

UCLASS()
class WHITEDESERT_API ALogInScreen : public AActor
{
	GENERATED_BODY()
	
	UPROPERTY()
	UUserWidget* UserWidget;
public:	
	ALogInScreen();


protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

};
