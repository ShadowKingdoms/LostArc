// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "LostArcCharacterAbilityBase.generated.h"

DECLARE_MULTICAST_DELEGATE_OneParam(FOnAbilityCDDelegate, bool);

UCLASS()
class LOSTARC_API ULostArcCharacterAbilityBase : public UObject
{
	GENERATED_BODY()
	
public:	
	virtual void ConstructAbility(float mana, float cooldown, float factor);
	virtual void Use(class ALostArcCharacter* Character);
	virtual void HitCheck(class ALostArcCharacter* Character);
	virtual bool AbilityStatusCheck(class ALostArcCharacter* Character);
	void CharacterRotatetoCursor(class ALostArcCharacter* Character);

public:
	UPROPERTY()
	float CoolDown;

	UPROPERTY()
	float ManaCost;

	UPROPERTY()
	float Damage_Factor;

	bool bAbilityNowAvailable;
	bool bAbilityNowCD;

	static bool bAnimationRunning;
	FTimerHandle AbilityCoolDownTimer;

	FOnAbilityCDDelegate OnAbilityhasCD;

protected:
	TPair<FCollisionQueryParams, TArray<FHitResult>> HitResultProperty;
};
