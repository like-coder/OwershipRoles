// Fill out your copyright notice in the Description page of Project Settings.


#include "AuraPlayerState.h"

AAuraPlayerState::AAuraPlayerState()
{
    //���������¿ͻ��˵�Ƶ��
    NetUpdateFrequency = 100.f;
    //��ʼ���������AbilitySystemComponent
    AbilitySystemComponent = CreateDefaultSubobject<UAuraAbilitySystemComponent>("AbilitySystemComponent");
    //��������˸���,���������״̬����Ϊ�����绷���´ӷ�����ͬ�����ͻ���
    AbilitySystemComponent->SetIsReplicated(true);
    //��ʼ���������AttributeSet
    AttributeSet = CreateDefaultSubobject<UAuraAttributeSet>("AttributeSet");
    //����˸��Ƶķ�ʽ(Full:������Ϸ/�������ǿ�����Ķ�����Ϸ��MOBA��, Mixed:��ҿ��Ƶ�Actors, Minimal:AI)
    AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Mixed);
}

UAbilitySystemComponent* AAuraPlayerState::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}
