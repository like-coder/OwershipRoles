// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Logging/LogMacros.h"
#include "MyEnum.h"
#include "OwershipRolesCharacter.generated.h"

class USpringArmComponent;
class UCameraComponent;
class UInputMappingContext;
class UInputAction;
struct FInputActionValue;

DECLARE_LOG_CATEGORY_EXTERN(LogTemplateCharacter, Log, All);

UCLASS(config=Game)
class AOwershipRolesCharacter : public ACharacter
{
	GENERATED_BODY()

	/** Camera boom positioning the camera behind the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	USpringArmComponent* CameraBoom;

	/** Follow camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	UCameraComponent* FollowCamera;
	
	/** MappingContext */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputMappingContext* DefaultMappingContext;

	/** Jump Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* JumpAction;

	/** Move Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* MoveAction;

	/** Look Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* LookAction;

public:
	AOwershipRolesCharacter();
	void TestOwnership();
	void TestReplicate();
	void TestRPCCharacter();
	void TestEnum();

protected:

	/** Called for movement input */
	void Move(const FInputActionValue& Value);

	/** Called for looking input */
	void Look(const FInputActionValue& Value);
			

protected:
	// APawn interface
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
	// To add mapping context
	virtual void BeginPlay();

	virtual void Tick(float DeltaTime) override;

public:
	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	/** Returns FollowCamera subobject **/
	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }

protected:
	/**********17.01Project*******************/
	FTimerHandle FireTimer;
	UPROPERTY(Replicated)
	int32 Ammo = 5;
	UPROPERTY(EditDefaultsOnly, Category = "RPC Character")
	UAnimMontage* FireAnimMontage;				//播放动画
	UPROPERTY(EditDefaultsOnly, Category = "RPC Character")
	USoundBase* NoAmmoSound;					//播放没子弹的声音
	UPROPERTY(EditDefaultsOnly, Category = "RPC Character")
	USoundBase* ReloadSound;					//播放没子弹的声音
	UFUNCTION(Server, Reliable, WithValidation, Category = "RPC Character")
	void ServerFire();							//用于触发可靠fwq开火
	UFUNCTION(NetMulticast, Unreliable, Category = "RPC Character")
	void MulticastFire();						//用于触发不可靠khd开火动画
	UFUNCTION(Client, Unreliable, Category = "RPC Character")
	void CilentPlaySound2D(USoundBase* sound);	//用于触发不可靠khd开火声音
	UFUNCTION(Server, Reliable, WithValidation, Category = "RPC Character")
	void ServerReload();						//用于触发可靠fwq换弹
	UFUNCTION(NetMulticast, Unreliable, Category = "RPC Character")
	void MulticastReload();						//用于触发不可靠khd换弹

	/**********17.03Project*******************/
	UPROPERTY(BlueprintReadOnly, Category = "Enumerations Character")
	EWeaponType Weapon;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Enumerations Character")
	TArray<int32> Ammos;

	void Pistol();
	void Shotgun();
	void RocketLauncher();

	/*****16.04Project******/
	UPROPERTY(Replicated)
	float A = 100.f;

	UPROPERTY(ReplicatedUsing = OnRepNotify_B)
	int32 B;

	UFUNCTION()
	void OnRepNotify_B();
};

