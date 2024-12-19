// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "AbilitySystemInterface.h"
#include "Abilities/GameplayAbility.h"
#include "AbilitySystem/AuraAttributeSet.h"
#include "AbilitySystem/AuraAbilitySystemComponent.h"
#include "AuraPlayerState.generated.h"

/**
 * 
 */
UCLASS()
class OWERSHIPROLES_API AAuraPlayerState : public APlayerState, public IAbilitySystemInterface
{
	GENERATED_BODY()
public:
	AAuraPlayerState();
    //获取AbilitySystem,继承IAbilitySystemInterface接口,重写函数
    virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
    //获取AttributeSet
    UAttributeSet* GetAttributeSet() const { return AttributeSet; }

    //获取Ability
    UGameplayAbility* GetAbility() const { return Ability; }
protected:
    //GAS系统
    UPROPERTY()
    TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent;
    UPROPERTY()
    TObjectPtr<UAttributeSet> AttributeSet;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Abilities")
    TObjectPtr<UGameplayAbility> Ability;
};
