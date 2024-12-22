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
	//通过标签激活
	bool TryActivateAbilitiesByTag(const FGameplayTagContainer& GameplayTagContainer, bool bAllowRemoteActivation = true);

	//通过UGameplayAbility及子类激活
	bool TryActivateAbilityByClass(TSubclassOf<UGameplayAbility> InAbilityToActivate, bool bAllowRemoteActivation = true);

	//通过句柄激活
	bool TryActivateAbility(FGameplayAbilitySpecHandle AbilityToActivate, bool bAllowRemoteActivation = true);

	//通过事件触发
	bool TriggerAbilityFromGameplayEvent(FGameplayAbilitySpecHandle AbilityToTrigger, FGameplayAbilityActorInfo* ActorInfo, FGameplayTag Tag, const FGameplayEventData* Payload, UAbilitySystemComponent& Component);

	//一次性激活
	FGameplayAbilitySpecHandle GiveAbilityAndActivateOnce(const FGameplayAbilitySpec& AbilitySpec);

	/** 取消指定能力. */
	void CancelAbility(UGameplayAbility* Ability);

	/** 取消FGameplayAbilitySpecHandle指定的能力*/
	void CancelAbilityHandle(const FGameplayAbilitySpecHandle& AbilityHandle);

	/** 取消指定标签的所有能力，不会取消那些忽略实例*/
	void CancelAbilities(const FGameplayTagContainer* WithTags = nullptr, const FGameplayTagContainer* WithoutTags = nullptr, UGameplayAbility* Ignore = nullptr);

	/** 除了忽略实例外，取消所有技能*/
	void CancelAllAbilities(UGameplayAbility* Ignore = nullptr);

	/** 取消所有，并杀死任何残留的实例化能力 */
	virtual void DestroyActiveState();


	bool CharacterAbilitiesGiven;
};
