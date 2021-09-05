// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/Items/Equip/LostArcItemEquipBase.h"
#include "LostArcItemEquip_Ring.generated.h"

/**
 * 
 */
UCLASS()
class LOSTARC_API ULostArcItemEquip_Ring : public ULostArcItemEquipBase
{
	GENERATED_BODY()
	
public:
	ULostArcItemEquip_Ring(const FObjectInitializer& ObjectInitializer);
	virtual bool Use(ALostArcCharacter* Character) override;
	virtual bool Equip(ALostArcCharacter* Character, int32 SlotIndex) override;
	virtual void Dismount(ALostArcCharacter* Character) override;
};
