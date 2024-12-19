// Fill out your copyright notice in the Description page of Project Settings.

#include "AbilitySystem/AuraAttributeSet.h"
#include "Net/UnrealNetwork.h"

UAuraAttributeSet::UAuraAttributeSet()
{
    InitHealth(100.f);
    InitMaxHealth(100.0f);
}

void UAuraAttributeSet::GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
    //��������Health�ڷ������Ͽ��Ա�Replicate,����ΪNone,Always Replicate
    //�������һ������,��Ĭ��ֵΪREPNOTIFY_OnChanged,Ҳ���ǵ������Ը���ʱ��Replicate
    DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet, Health, COND_None, REPNOTIFY_Always);
}

void UAuraAttributeSet::OnRep_Health(const FGameplayAttributeData& OldHealth) const
{
    //֪ͨ����ϵͳ��������Replicateһ�����ԣ�����OldHealthΪ�˺����ع�
    GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet, Health, OldHealth);
}

void UAuraAttributeSet::OnRep_MaxHealth(const FGameplayAttributeData& OldMaxHealth) const
{
    GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet, Health, OldMaxHealth);
}


