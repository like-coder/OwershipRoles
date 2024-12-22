// Fill out your copyright notice in the Description page of Project Settings.


#include "Actor/AuraEffectActor.h"
#include "AbilitySystemBlueprintLibrary.h"

// Sets default values
AAuraEffectActor::AAuraEffectActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
    SetRootComponent(CreateDefaultSubobject<USceneComponent>("SceneRoot"));
}

// Called when the game starts or when spawned
void AAuraEffectActor::BeginPlay()
{
	Super::BeginPlay();
    
}

void AAuraEffectActor::ApplyEffectToTarget(AActor* Target, TSubclassOf<UGameplayEffect> GameplayEffectClass)
{
    //��������ǹ��߿�,���Ի�ȡʵ����IAbilitySystem�ӿڵ�Actor��AbilitySystem
    UAbilitySystemComponent* TargetASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(Target);
    if (!TargetASC) return;
    //����Ƿ�Class��Ϊnull
    check(GameplayEffectClass)
        //��ȡASC��EffectContext
        FGameplayEffectContextHandle EffectContextHandle = TargetASC->MakeEffectContext();
    //ΪContextHandle���Դ���������Ч��������ߣ�
    EffectContextHandle.AddSourceObject(this);
    //����һ��Spec
    FGameplayEffectSpecHandle EffectSpecHandle = TargetASC->MakeOutgoingSpec(GameplayEffectClass, ActorLevel, EffectContextHandle);
    //ΪTarget���Ч��,Ȼ���ȡFActiveGameplayEffectHandle 
    FActiveGameplayEffectHandle ActiveEffectHandle = TargetASC->ApplyGameplayEffectSpecToSelf(*EffectSpecHandle.Data.Get());
    //������EffectΪ����ʱ������,�ҵ�ǰ����ʱ�����policyΪRemovedOnEndOverlap,
    //����Ҫ�洢ActiveEffectHandle,�Ա����ɾ��
    bool bIsInfinite = false;
    if (EffectSpecHandle.Data->Def.Get()->DurationPolicy == EGameplayEffectDurationType::Infinite)
    {
        bIsInfinite = true;
    }
    if (bIsInfinite && InfiniteEffectRemovalPolicy == EEffectRemovalPolicy::RemoveOnEndOverlap)
    {
        ActiveEffectHandles.Add(ActiveEffectHandle, TargetASC);
    }
}

void AAuraEffectActor::OnOverlap(AActor* TargetActor)
{
    if (InstantEffectApplicationPolicy == EEffectApplicationPolicy::ApplyOnOverlap)
    {
        ApplyEffectToTarget(TargetActor, InstantGameplayEffectClass);
    }
    if (DurationEffectApplicationPolicy == EEffectApplicationPolicy::ApplyOnOverlap)
    {
        ApplyEffectToTarget(TargetActor, DurationGameplayEffectClass);
    }
    if (InfiniteEffectApplicationPolicy == EEffectApplicationPolicy::ApplyOnOverlap)
    {
        ApplyEffectToTarget(TargetActor, InfiniteGameplayEffectClass);
    }
}

void AAuraEffectActor::OnEndOverlap(AActor* TargetActor)
{
    if (InstantEffectApplicationPolicy == EEffectApplicationPolicy::ApplyOnEndOverlap)
    {
        ApplyEffectToTarget(TargetActor, InstantGameplayEffectClass);
    }
    if (DurationEffectApplicationPolicy == EEffectApplicationPolicy::ApplyOnEndOverlap)
    {
        ApplyEffectToTarget(TargetActor, DurationGameplayEffectClass);
    }
    if (InfiniteEffectApplicationPolicy == EEffectApplicationPolicy::ApplyOnEndOverlap)
    {
        ApplyEffectToTarget(TargetActor, InfiniteGameplayEffectClass);
    }
    if (InfiniteEffectRemovalPolicy == EEffectRemovalPolicy::RemoveOnEndOverlap)
    {
        //ȥ��InfiniteEffect
        UAbilitySystemComponent* TargetASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(TargetActor);
        TArray<FActiveGameplayEffectHandle> RemovedKeys;
        for (auto& ActiveEffectHandle : ActiveEffectHandles)
        {
            if (TargetASC == ActiveEffectHandle.Value)
            {
                TargetASC->RemoveActiveGameplayEffect(ActiveEffectHandle.Key, 1);
                RemovedKeys.Add(ActiveEffectHandle.Key);
            }
        }

        for (auto& Key : RemovedKeys)
        {
            ActiveEffectHandles.Remove(Key);
        }
    }
}

// Called every frame
void AAuraEffectActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

