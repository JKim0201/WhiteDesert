#include "DataBaseActorComponent.h"
#include "networking.h"
#include "PlayerCharacter.h"

void UDataBaseActorComponent::Connect(void)
{
	if (Socket->GetConnectionState() != SCS_Connected)
		Socket->Connect(*Address);
}

UDataBaseActorComponent::UDataBaseActorComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
	Socket = FTcpSocketBuilder(TEXT("TcpSocket"));
	ISocketSubsystem* SocketSubsystem = ISocketSubsystem::Get();

	FIPv4Address IPAddress;
	FIPv4Address::Parse(FString("192.168.1.66"), IPAddress);
	FIPv4Endpoint EndPoint(IPAddress, (uint16)9997);

	Address = ISocketSubsystem::Get()->CreateInternetAddr();
	Address->SetIp(EndPoint.Address.Value);
	Address->SetPort(EndPoint.Port);

	Connect();
}

void UDataBaseActorComponent::Authenticate(FText* id, FText* pwd)
{
	FString SEmailPassword = id->ToString() + "/" + pwd->ToString();
	char* SendBuffer = TCHAR_TO_ANSI(*SEmailPassword);

	int32 SendBufferSize = 0;
	if (Socket->Send((uint8*)SendBuffer, SEmailPassword.Len() + 1, SendBufferSize))
	{
		if (SendBufferSize > 0)
		{
			requestSent = true;
		}
	}
}

void UDataBaseActorComponent::BeginPlay()
{
	APlayerCharacter* PC = Cast<APlayerCharacter>(GetOwner());
	bool NotConnected = Socket->GetConnectionState() != SCS_Connected;
	PC->ToggleLoginButton(!NotConnected);	
}

void UDataBaseActorComponent::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
	if (Socket)
		Socket->Close();

	delete Socket;
	Socket = nullptr;
}

void UDataBaseActorComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (requestSent)
	{
		const int32 BUFFER_SIZE = 256;
		uint8 RecvBuffer[BUFFER_SIZE];
		int32 RecvBufferSize = 0;
		if (Socket->Recv(RecvBuffer, BUFFER_SIZE, RecvBufferSize))
		{
			if (RecvBufferSize > 0)
			{
				requestSent = false;
				FString UserId = UTF8_TO_TCHAR(RecvBuffer);
				UE_LOG(LogTemp, Warning, TEXT("%s"), *UserId);
			}
		}
	}
}

