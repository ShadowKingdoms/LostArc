// Fill out your copyright notice in the Description page of Project Settings.

#include "AnimInstances/BossMonsterAnimInstance.h"

#include "Character/BossMonsterCharacter.h"

UBossMonsterAnimInstance::UBossMonsterAnimInstance()
{
	BossBasicAttackMontages.Init(NULL, 3);
}

void UBossMonsterAnimInstance::PlayAttackMontage()
{
	auto Number = FMath::RandRange(0, GetBasicAttackStep() - 1);
	Montage_Play(BossBasicAttackMontages[Number], 1.f);
}

int32 UBossMonsterAnimInstance::GetBasicAttackStep()
{
	return BossBasicAttackMontages.Num();
}

void UBossMonsterAnimInstance::AnimNotify_MonsterJumpCheck()
{
	auto BossMonster = Cast<ABossMonsterCharacter>(GetOwningActor());
	BossMonster->MonsterJumpEffect();
}

void UBossMonsterAnimInstance::AnimNotify_Skill_2_EffectCheck()
{
    auto BossMonster = Cast<ABossMonsterCharacter>(GetOwningActor());
	BossMonster->MonsterMeteorEffect();
}

void UBossMonsterAnimInstance::AnimNotify_Skill_3_EffectCheck()
{
	auto BossMonster = Cast<ABossMonsterCharacter>(GetOwningActor());
	BossMonster->MonsterBreathEffect();
}

TArray<UAnimMontage*> UBossMonsterAnimInstance::GetBossBasicAttackMontages()
{
	return BossBasicAttackMontages;
}
