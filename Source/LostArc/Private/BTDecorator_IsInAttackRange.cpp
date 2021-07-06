// Fill out your copyright notice in the Description page of Project Settings.

#include "BTDecorator_IsInAttackRange.h"
#include "CorpseAIController.h"
#include "LostArcCharacter.h"
#include "BehaviorTree/BlackboardComponent.h"

UBTDecorator_IsInAttackRange::UBTDecorator_IsInAttackRange()
{
	NodeName = TEXT("CanAttack");
}

bool UBTDecorator_IsInAttackRange::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
	bool bResult = Super::CalculateRawConditionValue(OwnerComp, NodeMemory);

	auto ControllingPawn = OwnerComp.GetAIOwner()->GetPawn();
	if (ControllingPawn == nullptr) return false;

	auto Target = Cast<ALostArcCharacter>(OwnerComp.GetBlackboardComponent()->GetValueAsObject(ACorpseAIController::TargetKey));
	if (Target == nullptr) return false;

	bResult = (Target->GetDistanceTo(ControllingPawn) <= 200.0f); 
	return bResult;
}
