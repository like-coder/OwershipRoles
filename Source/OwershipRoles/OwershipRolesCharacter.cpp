// Copyright Epic Games, Inc. All Rights Reserved.

#include "OwershipRolesCharacter.h"
#include "Engine/LocalPlayer.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/Controller.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputActionValue.h"
#include "OwershipRoles.h"
#include "Kismet/GameplayStatics.h"
#include "Net/UnrealNetwork.h"

DEFINE_LOG_CATEGORY(LogTemplateCharacter);

//////////////////////////////////////////////////////////////////////////
// AOwershipRolesCharacter

AOwershipRolesCharacter::AOwershipRolesCharacter()
{
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);
		
	// Don't rotate when the controller rotates. Let that just affect the camera.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Character moves in the direction of input...	
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 500.0f, 0.0f); // ...at this rotation rate

	// Note: For faster iteration times these variables, and many more, can be tweaked in the Character Blueprint
	// instead of recompiling to adjust them
	GetCharacterMovement()->JumpZVelocity = 700.f;
	GetCharacterMovement()->AirControl = 0.35f;
	GetCharacterMovement()->MaxWalkSpeed = 500.f;
	GetCharacterMovement()->MinAnalogWalkSpeed = 20.f;
	GetCharacterMovement()->BrakingDecelerationWalking = 2000.f;
	GetCharacterMovement()->BrakingDecelerationFalling = 1500.0f;

	// Create a camera boom (pulls in towards the player if there is a collision)
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 400.0f; // The camera follows at this distance behind the character	
	CameraBoom->bUsePawnControlRotation = true; // Rotate the arm based on the controller

	// Create a follow camera
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName); // Attach the camera to the end of the boom and let the boom adjust to match the controller orientation
	FollowCamera->bUsePawnControlRotation = false; // Camera does not rotate relative to arm

	// Note: The skeletal mesh and anim blueprint references on the Mesh component (inherited from Character) 
	// are set in the derived blueprint asset named ThirdPersonCharacter (to avoid direct content references in C++)
	PrimaryActorTick.bCanEverTick = true;
}

void AOwershipRolesCharacter::BeginPlay()
{
	// Call the base class  
	Super::BeginPlay();

	//Add Input Mapping Context
	if (APlayerController* PlayerController = Cast<APlayerController>(Controller))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(DefaultMappingContext, 0);
		}
	}
}

void AOwershipRolesCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//TestReplicate();
	TestRPCCharacter();
}

//////////////////////////////////////////////////////////////////////////
// Input

void AOwershipRolesCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	// Set up action bindings
	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent)) {
		
		// Jumping
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Started, this, &ACharacter::Jump);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ACharacter::StopJumping);

		// Moving
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AOwershipRolesCharacter::Move);

		// Looking
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &AOwershipRolesCharacter::Look);
	}
	else
	{
		UE_LOG(LogTemplateCharacter, Error, TEXT("'%s' Failed to find an Enhanced Input component! This template is built to use the Enhanced Input system. If you intend to use the legacy system, then you will need to update this C++ file."), *GetNameSafe(this));
	}
	PlayerInputComponent->BindAction("Fire", IE_Pressed, this, &AOwershipRolesCharacter::ServerFire);
	PlayerInputComponent->BindAction("Reload", IE_Pressed, this, &AOwershipRolesCharacter::ServerReload);
}

void AOwershipRolesCharacter::Move(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D MovementVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// find out which way is forward
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get forward vector
		const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	
		// get right vector 
		const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

		// add movement 
		AddMovementInput(ForwardDirection, MovementVector.Y);
		AddMovementInput(RightDirection, MovementVector.X);
	}
}

void AOwershipRolesCharacter::Look(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D LookAxisVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// add yaw and pitch input to controller
		AddControllerYawInput(LookAxisVector.X);
		AddControllerPitchInput(LookAxisVector.Y);
	}
}

void AOwershipRolesCharacter::TestOwnership()
{
	FString LocalRoleStr = ROLE_TO_STRING(GetLocalRole());
	FString RemoteRoleStr = ROLE_TO_STRING(GetRemoteRole());
	FString OwnerStr = GetOwner() ? GetOwner()->GetName() : TEXT("No Owner");
	FString ConnectionStr = GetNetConnection() ? TEXT("Valid Connection") : TEXT("Invalid Connection");
	FString Values = FString::Printf(TEXT("LocalRole = %s\nRemoteRole = %s\nOwner = %s\nConnection = %s"), *LocalRoleStr, *RemoteRoleStr, *OwnerStr, *ConnectionStr);

	DrawDebugString(GetWorld(), GetActorLocation(), Values, nullptr, FColor::White, 0.0f, true);
}

void AOwershipRolesCharacter::TestReplicate()
{
	if (HasAuthority())
	{
		A++;
		B++;
	}

	FString Values = FString::Printf(TEXT("A = %.2f		B = %d"), A, B);
	DrawDebugString(GetWorld(), GetActorLocation(), Values, nullptr, FColor::White, 0.0f, true);
}

void AOwershipRolesCharacter::TestRPCCharacter()
{
	FString AmmoNumString = FString::Printf(TEXT("Ammo = %d"), Ammo);
	DrawDebugString(GetWorld(), GetActorLocation(), AmmoNumString, nullptr, FColor::White, 0.f, true);
}

void AOwershipRolesCharacter::OnRepNotify_B()
{
	FString string = FString::Printf(TEXT("B was changed by the server and is now %d!"), B);
	GEngine->AddOnScreenDebugMessage(-1, 0.0f, FColor::Red, string);
}

void AOwershipRolesCharacter::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(AOwershipRolesCharacter, A);
	DOREPLIFETIME(AOwershipRolesCharacter, Ammo);
	DOREPLIFETIME_CONDITION(AOwershipRolesCharacter, B, COND_OwnerOnly);
}


/*****************17.01Project*******************/
bool AOwershipRolesCharacter::ServerFire_Validate()
{
	return true;
}


void AOwershipRolesCharacter::ServerFire_Implementation()
{
	//判断上一次开火计时器是否活跃，否则终止该函数
	if (GetWorldTimerManager().IsTimerActive(FireTimer))
	{
		return;
	}
	

	if (Ammo == 0)
	{
		//判断是否有弹药
		CilentPlaySound2D(NoAmmoSound);
		return;
	}

	Ammo--;
	GetWorldTimerManager().SetTimer(FireTimer, 1.0f, false);
	MulticastFire();			//调用开火多播，使客户端播放开火动画
}

void AOwershipRolesCharacter::MulticastFire_Implementation()
{
	if (FireAnimMontage->IsValidLowLevel())
	{
		PlayAnimMontage(FireAnimMontage);
	}
}

void AOwershipRolesCharacter::CilentPlaySound2D_Implementation(USoundBase* sound)
{
	if (NoAmmoSound->IsValidLowLevel())
	{
		UGameplayStatics::PlaySound2D(GetWorld(), sound);
	}
}

bool AOwershipRolesCharacter::ServerReload_Validate()
{
	return true;
}

void AOwershipRolesCharacter::ServerReload_Implementation()
{
	//判断子弹数量是否满的，若不是则换弹
	if (Ammo == 5)
	{
		return;
	}

	MulticastReload();
	Ammo = 5;
}

void AOwershipRolesCharacter::MulticastReload_Implementation()
{
	if (ReloadSound->IsValidLowLevel())
	{
		UGameplayStatics::PlaySound2D(GetWorld(), ReloadSound);
	}
}