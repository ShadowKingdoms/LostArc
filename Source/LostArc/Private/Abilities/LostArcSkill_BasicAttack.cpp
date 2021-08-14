// Fill out your copyright notice in the Description page of Project Settings.


#include "Abilities/LostArcSkill_BasicAttack.h"

ULostArcSkill_BasicAttack::ULostArcSkill_BasicAttack(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	CoolDown = 0.f;
	ManaCost = 0.f;
	SkillRatio = 0.5f;
	SkillRadius.Key = 200.0f;
	SkillRadius.Value = 90.f;
	bBasicAttacking = false;
	CurrentCombo = 0;
	MaxCombo = 3;
}

bool ULostArcSkill_BasicAttack::Use(ALostArcCharacter* Character)
{
	if (bBasicAttacking) // keep the combo and waiting for animation
	{
		check(FMath::IsWithinInclusive<int32>(CurrentCombo, 1, MaxCombo));
		if (bCanNextCombo) {
			bIsComboInputOn = true;
		}
	}
	else				// first attack
	{
		if (AbilityStateCheck(Character))
		{
			check(CurrentCombo == 0);
			BasicAttackStartComboState();
			CharacterRotatetoCursor(Character);

			Character->AnimInstance->Montage_Play(Character->AnimInstance->BasicAttack_Montage, 1.0f);
			bBasicAttacking = true;
			bAnimationRunning = true;
		}
	}
	return true;
}

bool ULostArcSkill_BasicAttack::AbilityStateCheck(ALostArcCharacter* Character)
{
	if (bAnimationRunning)
	{
		return false;
	}
	return true;
}

void ULostArcSkill_BasicAttack::BasicAttackStartComboState()
{
	bCanNextCombo = true;
	bIsComboInputOn = false;
	check(FMath::IsWithinInclusive<int32>(CurrentCombo, 0, MaxCombo - 1));
	CurrentCombo = FMath::Clamp<int32>(CurrentCombo + 1, 1, MaxCombo);
}

void ULostArcSkill_BasicAttack::BasicAttackEndComboState()
{
	bCanNextCombo = false;
	bIsComboInputOn = false;
	CurrentCombo = 0;
}

void ULostArcSkill_BasicAttack::BasicAttackNextComboCheck(ALostArcCharacter* Character)
{
	if (bIsComboInputOn)
	{
		BasicAttackStartComboState();
		Character->AnimInstance->JumpToBasicAttackMontageSection(CurrentCombo);
	}
}