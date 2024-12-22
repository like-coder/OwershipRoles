// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../MyEnum.h"
#include "../AuraPlayerState.h"
#include "Abilities/GameplayAbility.h"
#include "AureGameplayAbility.generated.h"

/**
 * 
 */
UCLASS()
class OWERSHIPROLES_API UAureGameplayAbility : public UGameplayAbility
{
	GENERATED_BODY()
public:
	UAureGameplayAbility();

	virtual void OnAvatarSet(const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilitySpec& Spec) override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Ability")
	int AbilityLevel = 1;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Ability")
	AbilityInput AbilityInputID = AbilityInput::UseAbility1;

	bool ActivateAbilityOnGranted;
};
