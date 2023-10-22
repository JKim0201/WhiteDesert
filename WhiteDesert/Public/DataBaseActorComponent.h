#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "DataBaseActorComponent.generated.h"




UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class WHITEDESERT_API UDataBaseActorComponent : public UActorComponent
{
	GENERATED_BODY()

	FSocket* Socket;
	bool requestSent;
	TSharedPtr <FInternetAddr> Address;

	void Connect(void);
public:	
	UDataBaseActorComponent();

	void Authenticate(FText* id, FText* pwd);
	

protected:
	virtual void BeginPlay() override;

	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
public:	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
};
