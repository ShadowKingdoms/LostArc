// Fill out your copyright notice in the Description page of Project Settings.

#include "Abilities/Skill/LostArcSkill_5.h"

#include "Component/LostArcCharacterAbilityComponent.h"


ULostArcSkill_5::ULostArcSkill_5(const FObjectInitializer& ObjectInitializer)
{
	CoolDown = 10.f;
	ManaCost = 30.f;
	SkillRatio = 1.f;
	Skill_Type = EAbilityType::RangedSpell_1;
	Name = "Skill_5";
	
	static ConstructorHelpers::FObjectFinder<UBlueprint> BP_ICE_ATK(TEXT("Blueprint'/Game/Luos8Elements/Blueprints/Ice/BP_4E_Ice_Atk_Unit.BP_4E_Ice_Atk_Unit'"));
	if (BP_ICE_ATK.Object)
	{
		SpawnActor = (UClass*)BP_ICE_ATK.Object->GeneratedClass;
	}

	static ConstructorHelpers::FObjectFinder<UBlueprint> BP_CIRCLE_5(TEXT("Blueprint'/Game/UI/Ability/BP_MagicCircle_Skill_5.BP_MagicCircle_Skill_5'"));
	if (BP_CIRCLE_5.Object)
	{
		CircleActor = (UClass*)BP_CIRCLE_5.Object->GeneratedClass;
	}
}

bool ULostArcSkill_5::Use(ALostArcPlayerCharacter* Character)
{
	if(Super::Use(Character))
	{
		Character->AnimInstance->Montage_Play(Character->AnimInstance->PlayerRangedSkill_1_Montage, 1.f);
		
		FHitResult TraceHitResult;
		auto PController = Character->GetNetOwningPlayer()->GetPlayerController(GetWorld());
		PController->GetHitResultUnderCursor(ECC_Visibility, true, TraceHitResult);
		auto SpawnLocation = FVector(TraceHitResult.Location.X, TraceHitResult.Location.Y, TraceHitResult.Location.Z + 1000.f);

		FTransform Transform;
		Transform.SetLocation(SpawnLocation);
		Transform.SetRotation(FQuat(0.f,0.f,0.f,0.f));
		Transform.SetScale3D(FVector(1.f,1.f,1.f));
		
		SkileActor = GetWorld()->SpawnActor<AActor>(SpawnActor, Transform);
		
		return true;
	}

	return false;
}