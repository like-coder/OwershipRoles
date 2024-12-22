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

UENUM(BlueprintType)
enum class AbilityInput : uint8
{
	UseAbility1 UMETA(DisplayName = "Use Spell 1"), //This maps the first ability(input ID should be 0 in int) to the action mapping(which you define in the project settings) by the name of "UseAbility1". "Use Spell 1" is the blueprint name of the element.
	UseAbility2 UMETA(DisplayName = "Use Spell 2"), //Maps ability 2(input ID 1) to action mapping UseAbility2. "Use Spell 2" is mostly used for when the enum is a blueprint variable.
	UseAbility3 UMETA(DisplayName = "Use Spell 3"),
	UseAbility4 UMETA(DisplayName = "Use Spell 4"),
	WeaponAbility UMETA(DisplayName = "Use Weapon"), //This finally maps the fifth ability(here designated to be your weaponability, or auto-attack, or whatever) to action mapping "WeaponAbility".

	//You may also do something like define an enum element name that is not actually mapped to an input, for example if you have a passive ability that isn't supposed to have an input. This isn't usually necessary though as you usually grant abilities via input ID,
	//which can be negative while enums cannot. In fact, a constant called "INDEX_NONE" exists for the exact purpose of rendering an input as unavailable, and it's simply defined as -1.
	//Because abilities are granted by input ID, which is an int, you may use enum elements to describe the ID anyway however, because enums are fancily dressed up ints.
};

UENUM(BlueprintType)
//在Overlap开始时还是结束时应用Effect效果
enum class EEffectApplicationPolicy : uint8
{
	ApplyOnOverlap,
	ApplyOnEndOverlap,
	DoNotApply
};

//在Overlap结束时是否移除Effect效果（无限时长的Effect）
UENUM(BlueprintType)
enum class EEffectRemovalPolicy : uint8
{
	RemoveOnEndOverlap,
	DoNotRemove
};