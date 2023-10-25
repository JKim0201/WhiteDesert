#include "PlayerCharacter.h"
#include "LogInUserWidget.h"
#include "DataBaseActorComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"

void APlayerCharacter::MoveToInGame(void)
{
	FLatentActionInfo lfai;
	UGameplayStatics::LoadStreamLevel(this, "/Game/Blueprints/Levels/WhiteDesert", true, true, lfai);
	LoginWidget->RemoveFromViewport();
	//LoginWidget->Destruct();

	SetActorLocation(FVector(0, 0, 100));
	GetMesh()->SetVisibility(true);
	GetCapsuleComponent()->SetGenerateOverlapEvents(true);
	GetCharacterMovement()->Activate();
	GetMesh()->Activate();
	GetCapsuleComponent()->Activate();
}

APlayerCharacter::APlayerCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	UWorld* World = GetWorld();
	if (World)
	{	
		APlayerController* PC = World->GetFirstPlayerController();
		if (PC)
			PC->bShowMouseCursor = true;
		static ConstructorHelpers::FClassFinder<ULogInUserWidget>Widget(TEXT("/Game/Blueprints/Widgets/WBP_LogIn"));
		LoginWidget = CreateWidget<ULogInUserWidget>(PC, Widget.Class);
		if (LoginWidget)
			LoginWidget->AddToViewport();
	}

	DataBaseComponent = CreateDefaultSubobject<UDataBaseActorComponent>("DataBaseComponent");
	Camera = CreateDefaultSubobject<UCameraComponent>("CameraComponent");
	SpringArm = CreateDefaultSubobject<USpringArmComponent>("SpringArmComponent");
	SpringArm->SetupAttachment(RootComponent);
	Camera->SetupAttachment(SpringArm);
}


void APlayerCharacter::Authenticate(FText* id, FText* pwd)
{
	DataBaseComponent->Authenticate(id, pwd);
}

void APlayerCharacter::ToggleLoginButton(bool on) const
{
	if (LoginWidget)
		LoginWidget->ToggleLoginButton(on);	
}

void APlayerCharacter::SetUserID(const int uid)
{
	UserID = uid;
}


void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();	

	GetMesh()->SetVisibility(false);
	GetCapsuleComponent()->SetGenerateOverlapEvents(false);
	GetCharacterMovement()->Deactivate();
	GetMesh()->Deactivate();
	GetCapsuleComponent()->Deactivate();
}

void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

