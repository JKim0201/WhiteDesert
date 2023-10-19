// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DB.generated.h"


UCLASS()
class WHITEDESERT_API ADB : public AActor
{
	GENERATED_BODY()

	FSocket* Socket;
	bool requestSent;
public:	
	// Sets default values for this actor's properties
	ADB();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void Destroyed() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	void Authenticate(FText* id, FText* pwd);

};
