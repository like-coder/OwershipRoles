// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTask.h"
#include "Delegates/DelegateCombinations.h"
#include "AuraGameplayTask.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FMyTwoParamDelegate, float, FirstParamName, int32, SecondParamName);
/**
 * 
 */
UCLASS()
class OWERSHIPROLES_API UAuraGameplayTask : public UGameplayTask
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintCallable, Category = "Ability|Tasks", meta = (DisplayName = "ExecuteMyTask", HidePin = "OwningAbility",
		DefaultToSelf = "OwningAbility", BlueprintInternalUseOnly = "TRUE"))
	static UAuraGameplayTask* CreateMyTask(TScriptInterface<IGameplayTaskOwnerInterface> OwningAbility, FName TaskInstanceName);

	virtual void Activate() override;

	UPROPERTY(BlueprintAssignable)
	FMyTwoParamDelegate OnCalled;

};
