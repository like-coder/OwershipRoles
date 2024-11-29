// Fill out your copyright notice in the Description page of Project Settings.


#include "OwnershipTestActor.h"
#include "OwershipRoles.h"
#include "OwershipRolesCharacter.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AOwnershipTestActor::AOwnershipTestActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	bReplicates = true;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	RootComponent = Mesh;
}

// Called every frame
void AOwnershipTestActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	TestOwnership();
}

void AOwnershipTestActor::TestOwnership()
{
	DrawDebugSphere(GetWorld(), GetActorLocation(), OwnershipRadius, 32, FColor::Yellow);

	//fwq特定的功能
	if (HasAuthority())
	{
		AActor* NextOwner = nullptr;
		float MinDistance = OwnershipRadius;
		TArray<AActor*> AActors;
		UGameplayStatics::GetAllActorsOfClass(this, AOwershipRolesCharacter::StaticClass(), AActors);

		for (AActor* actor : AActors)
		{
			float distacne = GetDistanceTo(actor);

			if (distacne <= MinDistance)
			{
				MinDistance = distacne;
				NextOwner = actor;
			}
		}

		if (GetOwner() != NextOwner)
		{
			SetOwner(NextOwner);
		}
	}
	FString LocalRoleStr = ROLE_TO_STRING(GetLocalRole());
	FString RemoteRoleStr = ROLE_TO_STRING(GetRemoteRole());
	FString OwnerStr = GetOwner() ? GetOwner()->GetName() : TEXT("No Owner");
	FString ConnectionStr = GetNetConnection() ? TEXT("Valid Connection") : TEXT("Invalid Connection");
	FString Values = FString::Printf(TEXT("LocalRole = %s\nRemoteRole = %s\nOwner = %s\nConnection = %s"), *LocalRoleStr, *RemoteRoleStr, *OwnerStr, *ConnectionStr);

	DrawDebugString(GetWorld(), GetActorLocation(), Values, nullptr, FColor::White, 0.0f, true);
}
