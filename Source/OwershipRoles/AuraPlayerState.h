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
    UAuraAttributeSet* GetAttributeSet() const { return AttributeSet; }
protected:
    //GAS系统
    UPROPERTY()
	TObjectPtr<UAuraAbilitySystemComponent> AbilitySystemComponent;
	UPROPERTY()
	TObjectPtr<UAuraAttributeSet> AttributeSet;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Abilities")
    TObjectPtr<UGameplayAbility> Ability;
};
