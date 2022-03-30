// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AnimInstances/MonsterBaseAnimInstance.h"
#include "BossMonsterAnimInstance.generated.h"

UCLASS()
class LOSTARC_API UBossMonsterAnimInstance : public UMonsterBaseAnimInstance
{
	GENERATED_BODY()
	
public:
	UBossMonsterAnimInstance();
	virtual void PlayAttackMontage() override;
	TArray<UAnimMontage*> GetBossBasicAttackMontages();
	int32 GetBasicAttackStep();

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Montage, Meta = (AllowPrviateAccess = true))
	TArray<UAnimMontage*> BossBasicAttackMontages;
};
