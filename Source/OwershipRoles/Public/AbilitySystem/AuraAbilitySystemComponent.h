// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "AuraAbilitySystemComponent.generated.h"

/**
 * 
 */
UCLASS()
class OWERSHIPROLES_API UAuraAbilitySystemComponent : public UAbilitySystemComponent
{
	GENERATED_BODY()
public:
	UAuraAbilitySystemComponent();
	//ͨ����ǩ����
	bool TryActivateAbilitiesByTag(const FGameplayTagContainer& GameplayTagContainer, bool bAllowRemoteActivation = true);

	//ͨ��UGameplayAbility�����༤��
	bool TryActivateAbilityByClass(TSubclassOf<UGameplayAbility> InAbilityToActivate, bool bAllowRemoteActivation = true);

	//ͨ���������
	bool TryActivateAbility(FGameplayAbilitySpecHandle AbilityToActivate, bool bAllowRemoteActivation = true);

	//ͨ���¼�����
	bool TriggerAbilityFromGameplayEvent(FGameplayAbilitySpecHandle AbilityToTrigger, FGameplayAbilityActorInfo* ActorInfo, FGameplayTag Tag, const FGameplayEventData* Payload, UAbilitySystemComponent& Component);

	//һ���Լ���
	FGameplayAbilitySpecHandle GiveAbilityAndActivateOnce(const FGameplayAbilitySpec& AbilitySpec);

	/** ȡ��ָ������. */
	void CancelAbility(UGameplayAbility* Ability);

	/** ȡ��FGameplayAbilitySpecHandleָ��������*/
	void CancelAbilityHandle(const FGameplayAbilitySpecHandle& AbilityHandle);

	/** ȡ��ָ����ǩ����������������ȡ����Щ����ʵ��*/
	void CancelAbilities(const FGameplayTagContainer* WithTags = nullptr, const FGameplayTagContainer* WithoutTags = nullptr, UGameplayAbility* Ignore = nullptr);

	/** ���˺���ʵ���⣬ȡ�����м���*/
	void CancelAllAbilities(UGameplayAbility* Ignore = nullptr);

	/** ȡ�����У���ɱ���κβ�����ʵ�������� */
	virtual void DestroyActiveState();


	bool CharacterAbilitiesGiven;
};
