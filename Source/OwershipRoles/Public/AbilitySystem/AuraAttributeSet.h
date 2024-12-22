// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "GameplayEffectExtension.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystemComponent.h"
#include "AuraAttributeSet.generated.h"

#define ATTRIBUTE_ACCESSORS(ClassName, PropertyName) \
GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName) \
GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName) \
GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName) \
GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)

//�ܹ���PostGameplayEffectExecute�л�ȡ������Ϣ���ŵ�һ���ṹ���з����ȡ
USTRUCT()
struct FEffectProperties
{
    GENERATED_BODY()
    FEffectProperties() {}
    FGameplayEffectContextHandle EffectContextHandle;
    //Source �������Effect�Ǵ��ĸ�Actor�ͷŵ�,Target��������(ӵ�и�AttributeSet�Ľ�ɫ)

    UPROPERTY()
    UAbilitySystemComponent* SourceASC = nullptr;
    UPROPERTY()
    AActor* SourceAvatarActor = nullptr;
    UPROPERTY()
    AController* SourceController = nullptr;
    UPROPERTY()
    ACharacter* SourceCharacter = nullptr;
    UPROPERTY()
    UAbilitySystemComponent* TargetASC = nullptr;
    UPROPERTY()
    AActor* TargetAvatarActor = nullptr;
    UPROPERTY()
    AController* TargetController = nullptr;
    UPROPERTY()
    ACharacter* TargetCharacter = nullptr;
};

/**
 * 
 */
UCLASS()
class OWERSHIPROLES_API UAuraAttributeSet : public UAttributeSet
{
	GENERATED_BODY()

public:
	UAuraAttributeSet();

	//ָ����Щ������Ҫ�ڷ������Ϳͻ���֮��ͬ����������ÿ�����Եĸ���������Replication Condition��
	virtual void GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const override;

	//�����������Ҫ������ǿ��ִ��ĳЩԼ������򣬱�������ĳ�����Ե�ֵ��һ���ض���Χ��
	virtual void PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue);

    //��GameplayEffect�����ʱ�Ļص�
    virtual void PostGameplayEffectExecute(const struct FGameplayEffectModCallbackData& Data) override;

	//ReplicatedUsingΪ��������޸�Health��ֵʱ�Ļص���ӵ��Replicated����ʱ����ֵ��ӷ������Զ����Ƶ��ͻ���
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_Health, Category = "Vital Attributes")
	FGameplayAttributeData Health;
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_MaxHealth, Category = "Vital Attributes")
	FGameplayAttributeData MaxHealth;

	//����ֵ�����Է�����
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, Health);
	//�������ֵ�����Է�����
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, MaxHealth);

	UFUNCTION()
	void OnRep_Health(const FGameplayAttributeData& OldHealth) const;
	UFUNCTION()
	void OnRep_MaxHealth(const FGameplayAttributeData& OldMaxHealth) const;

private:
    //��PostGameplayEffectExecute��Data�л�ȡ���е�����,����ContextHandle,Actor,Character�ȵ�
    void SetEffectProperties(const FGameplayEffectModCallbackData& Data, FEffectProperties& Props);

};
