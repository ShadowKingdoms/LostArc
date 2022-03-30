// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/MonsterCharacterBase.h"
#include "AnimInstances/MonsterBaseAnimInstance.h"
#include "Components/CapsuleComponent.h"
#include "Controller/MonsterBaseAIController.h"
#include "GameFramework/CharacterMovementComponent.h"

// Sets default values
AMonsterCharacterBase::AMonsterCharacterBase()
{
	PrimaryActorTick.bCanEverTick = true;
	GetCapsuleComponent()->SetCollisionProfileName(TEXT("Monster"));

	AIControllerClass = AMonsterBaseAIController::StaticClass();
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;

	bUseControllerRotationYaw = false;
	GetCharacterMovement()->bUseControllerDesiredRotation = false;
	GetCharacterMovement()->bOrientRotationToMovement = true;
}

void AMonsterCharacterBase::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	MonsterAnim = Cast<UMonsterBaseAnimInstance>(GetMesh()->GetAnimInstance());
	if (MonsterAnim != nullptr)
	{
		MonsterAnim->OnMontageEnded.AddDynamic(this, &AMonsterCharacterBase::OnAttackMontageEnded);
		MonsterAnim->OnMonsterAttackHitCheck.AddUObject(this, &AMonsterCharacterBase::MonsterAttackHitCheck);
	}
}

// Called when the game starts or when spawned
void AMonsterCharacterBase::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AMonsterCharacterBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AMonsterCharacterBase::MonsterAttack()
{
}

void AMonsterCharacterBase::MonsterAttackHitCheck()
{
}

float AMonsterCharacterBase::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	return Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
}

void AMonsterCharacterBase::OnAttackMontageEnded(UAnimMontage* Montage, bool bInterrupted)
{
	if (Montage->IsValidSectionName(TEXT("Attack"))) 
	{
		OnAttackEnd.Broadcast();
	}
}

