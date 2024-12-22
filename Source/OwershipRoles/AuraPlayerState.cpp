// Fill out your copyright notice in the Description page of Project Settings.


#include "AuraPlayerState.h"

AAuraPlayerState::AAuraPlayerState()
{
    //服务器更新客户端的频率
    NetUpdateFrequency = 100.f;
    //初始化敌人类的AbilitySystemComponent
    AbilitySystemComponent = CreateDefaultSubobject<UAuraAbilitySystemComponent>("AbilitySystemComponent");
    //开启服务端复制,将该组件的状态和行为在网络环境下从服务器同步到客户端
    AbilitySystemComponent->SetIsReplicated(true);
    //初始化敌人类的AttributeSet
    AttributeSet = CreateDefaultSubobject<UAuraAttributeSet>("AttributeSet");
    //服务端复制的方式(Full:单人游戏/与服务器强关联的多人游戏（MOBA）, Mixed:玩家控制的Actors, Minimal:AI)
    AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Mixed);
}

UAbilitySystemComponent* AAuraPlayerState::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}
