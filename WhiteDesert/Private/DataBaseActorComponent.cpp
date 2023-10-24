#include "DataBaseActorComponent.h"
#include "networking.h"
#include "PlayerCharacter.h"


UDataBaseActorComponent::UDataBaseActorComponent()
	:AuthenticationRequestSent(false),
	SignedIn(false)
{
	PrimaryComponentTick.bCanEverTick = true;

	CreateSocket();

	FIPv4Address IPAddress;
	FIPv4Address::Parse(FString("192.168.1.66"), IPAddress);
	FIPv4Endpoint EndPoint(IPAddress, (uint16)9997);

	Address = ISocketSubsystem::Get()->CreateInternetAddr();
	Address->SetIp(EndPoint.Address.Value);
	Address->SetPort(EndPoint.Port);
}

UDataBaseActorComponent::~UDataBaseActorComponent()
{
	CloseSocket();
}

void UDataBaseActorComponent::BeginPlay()
{
	Super::BeginPlay();

	Socket->Connect(*Address);
	Owner = Cast<APlayerCharacter>(GetOwner());
	bool NotConnected = Socket->GetConnectionState() != SCS_Connected;
	Owner->ToggleLoginButton(!NotConnected);
}

void UDataBaseActorComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (!SignedIn)
	{
		HandleAuthenticationRequest();
		Connect();
	}
}

void UDataBaseActorComponent::Connect(void)
{
	ESocketConnectionState state = Socket->GetConnectionState();
	// even if there is no connection, previously connected socket state remain as connected
	if (state == SCS_Connected)
	{
		const int32 BUFFER_SIZE = 256;
		uint8 RecvBuffer[BUFFER_SIZE];
		int32 RecvBufferSize = 0;
		// Check if connection is still alive by type of error. 
		Socket->Recv(RecvBuffer, BUFFER_SIZE, RecvBufferSize);	
		ESocketErrors error = ISocketSubsystem::Get()->GetLastErrorCode();
		// still in connection
		if (SE_EWOULDBLOCK == error)
			Owner->ToggleLoginButton(true);
		// disconnected
		else
		{
			CreateSocket();
			Socket->Connect(*Address);
			Owner->ToggleLoginButton(false);
		}
	}
	else
	{
		Socket->Connect(*Address);	
		Owner->ToggleLoginButton(false);
	}

}

void UDataBaseActorComponent::CreateSocket(void)
{
	// reset socket before create
	CloseSocket();
	Socket = FTcpSocketBuilder(TEXT("TcpSocket")).AsReusable();
	ISocketSubsystem* SocketSubsystem = ISocketSubsystem::Get();
}

void UDataBaseActorComponent::CloseSocket(void)
{
	if (Socket)
	{
		Socket->Close();

		delete Socket;
		Socket = nullptr;
	}
}

void UDataBaseActorComponent::HandleAuthenticationRequest(void)
{
	if (AuthenticationRequestSent)
	{
		const int32 BUFFER_SIZE = 256;
		uint8 RecvBuffer[BUFFER_SIZE];
		int32 RecvBufferSize = 0;
		if (Socket->Recv(RecvBuffer, BUFFER_SIZE, RecvBufferSize))
		{
			if (RecvBufferSize > 0)
			{
				AuthenticationRequestSent = false;
				FString UserId = UTF8_TO_TCHAR(RecvBuffer);
				int iUserId = FCString::Atoi(*UserId);
				// userid of 0 means no match found
				if (iUserId == 0)
				{
					UE_LOG(LogTemp, Warning, TEXT("%s"), *UserId);
				}
				else
				{
					Owner->SetUserID(iUserId);
					Owner->ToggleLoginButton(false);
					SignedIn = true;
					// prepare for game and move on
					Owner->MoveToInGame();
				}
				
			}
		}
	}
}

void UDataBaseActorComponent::Authenticate(FText* id, FText* pwd)
{
	FString SEmailPassword = id->ToString() + "/" + pwd->ToString();
	char* SendBuffer = TCHAR_TO_ANSI(*SEmailPassword);

	int32 SendBufferSize = 0;
	if (Socket->Send((uint8*)SendBuffer, SEmailPassword.Len() + 1, SendBufferSize))
		if (SendBufferSize > 0)
			AuthenticationRequestSent = true;
}



