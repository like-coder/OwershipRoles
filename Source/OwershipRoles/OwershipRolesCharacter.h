// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Logging/LogMacros.h"
#include "MyEnum.h"
#include "AuraPlayerState.h"
#include "AbilitySystem/AuraAttributeSet.h"
#include "AbilitySystem/AuraAbilitySystemComponent.h"
#include "OwershipRolesCharacter.generated.h"

class USpringArmComponent;
class UCameraComponent;
class UInputMappingContext;
class UInputAction;
struct FInputActionValue;

DECLARE_LOG_CATEGORY_EXTERN(LogTemplateCharacter, Log, All);

UCLASS(config=Game)
class AOwershipRolesCharacter : public ACharacter, public IAbilitySystemInterface
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

	/**************Learn GAS*******************/
	//��һ�� Pawn ��һ���µ� Controller �ӹ�ʱ�Ļص�����
	virtual void PossessedBy(AController* NewController) override;
	//�� PlayerState �ڿͻ�����ͨ�����縴�Ʒ����仯ʱ,OnRep_PlayerState �����ᱻ�Զ�����,����Ҫ���ڴ��� PlayerState ���µĻص�
	// PlayerState ��ʼ��ʱҲ����øú���
	virtual void OnRep_PlayerState() override;
	void InitAbilityActorInfo();
	//��ȡAbilitySystem,�̳�IAbilitySystemInterface�ӿ�,��д����
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;

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
	UAnimMontage* FireAnimMontage;				//���Ŷ���
	UPROPERTY(EditDefaultsOnly, Category = "RPC Character")
	USoundBase* NoAmmoSound;					//����û�ӵ�������
	UPROPERTY(EditDefaultsOnly, Category = "RPC Character")
	USoundBase* ReloadSound;					//����û�ӵ�������
	UFUNCTION(Server, Reliable, WithValidation, Category = "RPC Character")
	void ServerFire();							//���ڴ����ɿ�fwq����
	UFUNCTION(NetMulticast, Unreliable, Category = "RPC Character")
	void MulticastFire();						//���ڴ������ɿ�khd���𶯻�
	UFUNCTION(Client, Unreliable, Category = "RPC Character")
	void CilentPlaySound2D(USoundBase* sound);	//���ڴ������ɿ�khd��������
	UFUNCTION(Server, Reliable, WithValidation, Category = "RPC Character")
	void ServerReload();						//���ڴ����ɿ�fwq����
	UFUNCTION(NetMulticast, Unreliable, Category = "RPC Character")
	void MulticastReload();						//���ڴ������ɿ�khd����

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


	/**************Learn GAS*******************/
	UPROPERTY()
	TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent;
	UPROPERTY()
	TObjectPtr<UAttributeSet> AttributeSet;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Abilities")
	TObjectPtr<class UGameplayAbility> Ability;
};

