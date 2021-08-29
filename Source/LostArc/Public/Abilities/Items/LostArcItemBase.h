// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/LostArcAbilityBase.h"
#include "LostArcItemBase.generated.h"

/**
 * 
 */

DECLARE_MULTICAST_DELEGATE(FOnItemQuantityUpdateDelegate);

UENUM(BlueprintType)
enum EItemType
{
	ITEM_Equip UMETA(DisplayName = "Equip"),
	ITEM_Potion UMETA(DisplayName = "Potion"),
	ITEM_None  UMETA(DisplayName = "None")
};

UCLASS()
class LOSTARC_API ULostArcItemBase : public ULostArcAbilityBase
{
	GENERATED_BODY()
	
public:
	UTexture2D* BgTexture2D;
	UTexture2D* ItemTexture2D;
	
	FOnItemQuantityUpdateDelegate ItemQuantityUpdate;
	
public:
	virtual bool Use(ALostArcCharacter* Character) override;
	virtual bool AbilityStateCheck(ALostArcCharacter* Character) override;
	bool IsConsumable() const;

	int32 GetItemQuantity() { return ItemQuantity; }
	void SetItemQuantity(int32 Count);
	UTexture2D* GetItemTexture2D() { return ItemTexture2D; }
	UTexture2D* GetBgTexture2D() { return BgTexture2D; }

protected:
	int32 MaxCount;
	int32 ItemQuantity;
	EItemType ItemType;
};
