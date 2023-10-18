// Fill out your copyright notice in the Description page of Project Settings.


#include "DB.h"
#include "networking.h"

// Sets default values
ADB::ADB()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void ADB::BeginPlay()
{
	Super::BeginPlay();

	FIPv4Address IPAddress;
	FIPv4Address::Parse(FString("192.168.1.66"), IPAddress);
	//FIPv4Address::Parse(FString("127.0.0.1"), IPAddress);
	FIPv4Endpoint EndPoint(IPAddress, (uint16)9997);

	ISocketSubsystem* SocketSubsystem = ISocketSubsystem::Get();
	if (SocketSubsystem)
	{
		Socket = FTcpSocketBuilder(TEXT("TcpSocket")).AsReusable();
		if (Socket)
		{
			TSharedPtr<FInternetAddr> InternetAddress = ISocketSubsystem::Get()->CreateInternetAddr();
			InternetAddress->SetIp(IPAddress.Value);
			InternetAddress->SetPort((int32)9997);

			if (Socket->Connect(*InternetAddress))
			{
				UE_LOG(LogTemp, Warning, TEXT("connected"));
			}					
		}
	}	
}



// Called every frame
void ADB::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ADB::Destroyed()
{
	if (Socket)
		Socket->Close();
}

