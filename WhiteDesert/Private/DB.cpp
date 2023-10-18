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
			else
			{
				UE_LOG(LogTemp, Warning, TEXT("connect failed"));
			}
		}
	}	
}



// Called every frame
void ADB::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

const bool ADB::Authenticate(FText* id, FText* pwd) const
{
	//send
	if (!Socket || Socket->GetConnectionState() != SCS_Connected)
		return false;


	FString a = id->ToString() + "/" + pwd->ToString();
	char * data = TCHAR_TO_ANSI(*a);
	
	int32 sent = sizeof(uint8) * a.Len() + 1;
	if (Socket->Send((uint8*)data, a.Len() + 1, sent))
	{
		UE_LOG(LogTemp, Warning, TEXT("sent"));
	}

	
	return true;
}

void ADB::Destroyed()
{
	if (Socket)
	{
		if (Socket->Close())
		{
			UE_LOG(LogTemp, Warning, TEXT("closed"));
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("not closed"));
		}

	}
	delete Socket;
	Socket = nullptr;
}

void ADB::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
	if (Socket)
	{
		if (Socket->Close())
		{
			UE_LOG(LogTemp, Warning, TEXT("closed"));
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("not closed"));
		}

	}
	delete Socket;
	Socket = nullptr;

}

