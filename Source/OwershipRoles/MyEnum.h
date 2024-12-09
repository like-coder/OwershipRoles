#pragma once
#include "CoreMinimal.h"

#define ENUM_TO_INT32(Value) static_cast<int32>(Value)
#define ENUM_TO_FSTRING(Enum, Value) FindObject<UEnum>(ANY_PACKAGE, TEXT(Enum), true)->GetDisplayNameTextByIndex(ENUM_TO_INT32(Value)).ToString()

UENUM(BlueprintType)
enum class EWeaponType : uint8
{
	Pistol UMETA(DisplayName = "Glock 19"),
	Shotgun UMETA(DisplayName = "Winchester M1897"),
	RocketLauncher UMETA(DisplayName = "RPG"),
	Max
};

UENUM(BlueprintType)
enum class EAmmoType : uint8
{
	Bullets UMETA(DisplayName = "9mm Bullets"),
	Shells UMETA(DisplayName = "12 Gauge Shotgun Shells"),
	Rockets UMETA(DisplayName = "RPG Rockets"),
	Max
};
