#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "DataBaseActorComponent.generated.h"

class APlayerCharacter;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class WHITEDESERT_API UDataBaseActorComponent : public UActorComponent
{
	GENERATED_BODY()

	FSocket* Socket;
	bool AuthenticationRequestSent;
	bool SignedIn;
	TSharedPtr <FInternetAddr> Address;
	APlayerCharacter* Owner;

	void Connect(void);
	void CreateSocket(void);
	void CloseSocket(void);
	void HandleAuthenticationRequest(void);
public:	
	UDataBaseActorComponent();
	~UDataBaseActorComponent();

	void Authenticate(FText* id, FText* pwd);
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
protected:
	virtual void BeginPlay() override;

		
};
