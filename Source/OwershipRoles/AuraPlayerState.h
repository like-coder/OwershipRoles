// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "AbilitySystemInterface.h"
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
    //��ȡAbilitySystem,�̳�IAbilitySystemInterface�ӿ�,��д����
    virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
    //��ȡAttributeSet
    UAttributeSet* GetAttributeSet() const { return AttributeSet; }
protected:
    //GASϵͳ
    UPROPERTY()
    TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent;
    UPROPERTY()
    TObjectPtr<UAttributeSet> AttributeSet;
};