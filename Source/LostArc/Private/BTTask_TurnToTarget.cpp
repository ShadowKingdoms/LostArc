// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_TurnToTarget.h"
#include "CorpseAIController.h"
#include "CorpseCharacter.h"
#include "LostArcCharacter.h"
#include "BehaviorTree/BlackboardComponent.h"

UBTTask_TurnToTarget::UBTTask_TurnToTarget()
{
	NodeName = TEXT("Trun");
}

EBTNodeResult::Type UBTTask_TurnToTarget::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	EBTNodeResult::Type Result = Super::ExecuteTask(OwnerComp, NodeMemory);

	auto CorpseCharacter = Cast<ACorpseCharacter>(OwnerComp.GetAIOwner()->GetPawn());
	if (CorpseCharacter == nullptr) return EBTNodeResult::Failed;

	auto Target = Cast<ALostArcCharacter>(OwnerComp.GetBlackboardComponent()->GetValueAsObject(ACorpseAIController::TargetKey));
	if (Target == nullptr) return EBTNodeResult::Failed;

	FVector LookVector = Target->GetActorLocation() - CorpseCharacter->GetActorLocation();
	LookVector.Z = 0.0f;
	FRotator TargetRot = FRotationMatrix::MakeFromX(LookVector).Rotator();
	CorpseCharacter->SetActorRotation(FMath::RInterpTo(CorpseCharacter->GetActorRotation(), TargetRot, GetWorld()->GetDeltaSeconds(), 2.0f));

	return EBTNodeResult::Succeeded;
}
