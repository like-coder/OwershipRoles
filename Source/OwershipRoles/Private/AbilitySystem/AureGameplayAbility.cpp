// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/AureGameplayAbility.h"

UAureGameplayAbility::UAureGameplayAbility()
{
	ActivateAbilityOnGranted = true;
}

void UAureGameplayAbility::OnAvatarSet(const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilitySpec& Spec)
{
	Super::OnAvatarSet(ActorInfo, Spec);

	if (ActivateAbilityOnGranted)
	{
		//bool ActivatedAbility = ActorInfo->AbilitySystemComponent->TryActivateAbility(Spec.Handle, false);
	}
}
