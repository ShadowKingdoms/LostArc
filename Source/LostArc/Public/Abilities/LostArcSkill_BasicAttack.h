// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/LostArcSkillBase.h"
#include "LostArcSkill_BasicAttack.generated.h"

/**
 * 
 */
UCLASS()
class LOSTARC_API ULostArcSkill_BasicAttack : public ULostArcSkillBase
{
	GENERATED_BODY()
	
public:
	ULostArcSkill_BasicAttack(const FObjectInitializer& ObjectInitializer);
	virtual bool Use(ALostArcCharacter* Character) override;
	virtual bool AbilityStateCheck(ALostArcCharacter* Character) override;
	void BasicAttackNextComboCheck(ALostArcCharacter* Character);
	void BasicAttackEndComboState();
	bool GetBasicAttacking() { return bBasicAttacking; }
	void SetBasicAttacking(bool bAttack) { bBasicAttacking = bAttack; }

private:
	bool bBasicAttacking;
	bool bCanNextCombo;
	bool bIsComboInputOn;
	int32 CurrentCombo;
	int32 MaxCombo;

	void BasicAttackStartComboState();
};
