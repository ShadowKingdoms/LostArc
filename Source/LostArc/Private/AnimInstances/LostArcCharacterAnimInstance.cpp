// Fill out your copyright notice in the Description page of Project Settings.

#include "AnimInstances/LostArcCharacterAnimInstance.h"
#include "Player/LostArcCharacterAbilityComponent.h"

void ULostArcCharacterAnimInstance::AnimNotify_Next_BasicAttackCheck()
{
	OnNextBasicAttackCheck.Broadcast();
}

void ULostArcCharacterAnimInstance::AnimNotify_BasicAttack_HitCheck()
{
	OnMeleeSkillHitCheck.Broadcast(EAbilityType::BasicAttack);
}

void ULostArcCharacterAnimInstance::AnimNotify_MeleeSkill_1_HitCheck()
{
	OnMeleeSkillHitCheck.Broadcast(EAbilityType::MeleeSkill_1);
}

void ULostArcCharacterAnimInstance::AnimNotify_MeleeSkill_2_HitCheck()
{
	OnMeleeSkillHitCheck.Broadcast(EAbilityType::MeleeSkill_2);
}

void ULostArcCharacterAnimInstance::AnimNotify_MeleeSkill_3_HitCheck()
{
	OnMeleeSkillHitCheck.Broadcast(EAbilityType::MeleeSkill_3);
}

void ULostArcCharacterAnimInstance::AnimNotify_MeleeSkill_4_HitCheck()
{
	OnMeleeSkillHitCheck.Broadcast(EAbilityType::MeleeSkill_4);
}

void ULostArcCharacterAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	auto Pawn = TryGetPawnOwner();
	if (!::IsValid(Pawn)) return;
}

void ULostArcCharacterAnimInstance::JumpToBasicAttackMontageSection(int32 NewSection)
{
	//Montage_JumpToSectionsEnd(TEXT("Skill_A")); // 현재 몽타주 애니메이션을 즉각 중단한다.
	Montage_JumpToSection(FName(*FString::Printf(TEXT("BasicAttack_%d"), NewSection)), BasicAttack_Montage);
}