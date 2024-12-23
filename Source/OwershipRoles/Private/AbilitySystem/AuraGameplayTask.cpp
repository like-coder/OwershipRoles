// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/AuraGameplayTask.h"

UAuraGameplayTask* UAuraGameplayTask::CreateMyTask(TScriptInterface<IGameplayTaskOwnerInterface> OwningAbility, FName TaskInstanceName)
{
	UAuraGameplayTask* Instance = NewTask<UAuraGameplayTask>(OwningAbility, TaskInstanceName);

	return Instance;
}

void UAuraGameplayTask::Activate()
{
	OnCalled.Broadcast(500.f, 42);
}
