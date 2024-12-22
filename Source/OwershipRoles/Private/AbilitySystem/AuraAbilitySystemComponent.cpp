// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/AuraAbilitySystemComponent.h"

UAuraAbilitySystemComponent::UAuraAbilitySystemComponent()
{
	CharacterAbilitiesGiven = false;
}

bool UAuraAbilitySystemComponent::TryActivateAbilitiesByTag(const FGameplayTagContainer& GameplayTagContainer, bool bAllowRemoteActivation)
{
	return false;
}

bool UAuraAbilitySystemComponent::TryActivateAbilityByClass(TSubclassOf<UGameplayAbility> InAbilityToActivate, bool bAllowRemoteActivation)
{
	return false;
}

bool UAuraAbilitySystemComponent::TryActivateAbility(FGameplayAbilitySpecHandle AbilityToActivate, bool bAllowRemoteActivation)
{
	return false;
}

bool UAuraAbilitySystemComponent::TriggerAbilityFromGameplayEvent(FGameplayAbilitySpecHandle AbilityToTrigger, FGameplayAbilityActorInfo* ActorInfo, FGameplayTag Tag, const FGameplayEventData* Payload, UAbilitySystemComponent& Component)
{
	return false;
}

FGameplayAbilitySpecHandle UAuraAbilitySystemComponent::GiveAbilityAndActivateOnce(const FGameplayAbilitySpec& AbilitySpec)
{
	return FGameplayAbilitySpecHandle();
}

void UAuraAbilitySystemComponent::CancelAbility(UGameplayAbility* Ability)
{
}

void UAuraAbilitySystemComponent::CancelAbilityHandle(const FGameplayAbilitySpecHandle& AbilityHandle)
{
}

void UAuraAbilitySystemComponent::CancelAbilities(const FGameplayTagContainer* WithTags, const FGameplayTagContainer* WithoutTags, UGameplayAbility* Ignore)
{
}

void UAuraAbilitySystemComponent::CancelAllAbilities(UGameplayAbility* Ignore)
{
}

void UAuraAbilitySystemComponent::DestroyActiveState()
{
}
