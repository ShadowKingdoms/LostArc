// Fill out your copyright notice in the Description page of Project Settings.


#include "Abilities/LostArcCharacterAbilityBase.h"
#include "Character/LostArcCharacter.h"
#include "Player/LostArcCharacterStatComponent.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"

bool ULostArcCharacterAbilityBase::bAnimationRunning = false;

void ULostArcCharacterAbilityBase::ConstructAbility(float mana, float cooldown, float ratio)
{
	ManaCost = mana;
	CoolDown = cooldown;
	Damage_Ratio = ratio;
	bAbilityNowCD = false;
}

void ULostArcCharacterAbilityBase::Use(ALostArcCharacter* Character)
{
	bAbilityAvailable = AbilityStatusCheck(Character);

	if (bAbilityAvailable)
	{
		CharacterRotatetoCursor(Character);
		Character->GetWorldTimerManager().SetTimer(AbilityCoolDownTimer, FTimerDelegate::CreateLambda([=]() {bAbilityNowCD = false; }), CoolDown, false);
		Character->StatComponent->SetMP(Character->StatComponent->GetMP() - ManaCost);
		bAbilityNowCD = true;
		bAnimationRunning = true;
	}
}

void ULostArcCharacterAbilityBase::HitCheck(ALostArcCharacter* Character)
{
}

bool ULostArcCharacterAbilityBase::AbilityStatusCheck(ALostArcCharacter* Character)
{
	if (bAbilityNowCD)
	{
		UE_LOG(LogTemp, Warning, TEXT("CoolDown Left is : %f"), Character->GetWorldTimerManager().GetTimerRemaining(AbilityCoolDownTimer));
		return false;
	}
	if (Character->StatComponent->GetMP() < ManaCost)
	{
		UE_LOG(LogTemp, Warning, TEXT("Current Mana is : %f"), Character->StatComponent->GetMP());
		return false;
	}
	if (bAnimationRunning)
	{
		return false;
	}
	return true;
}

void ULostArcCharacterAbilityBase::CharacterRotatetoCursor(ALostArcCharacter* Character)
{
	FHitResult Hit;
	Cast<APlayerController>(Character->GetController())->GetHitResultUnderCursor(ECC_Visibility, false, Hit);
	float ang = FMath::Atan2(Hit.ImpactPoint.Y - Character->GetActorLocation().Y, Hit.ImpactPoint.X - Character->GetActorLocation().X) * 180 / PI;
	if (ang < 0) ang += 360;
	
	Character->SetActorRelativeRotation(FRotator(0.0f, ang, 0.0f));
	UAIBlueprintHelperLibrary::SimpleMoveToActor(Character->GetController(), Character);
}

