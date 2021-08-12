// Fill out your copyright notice in the Description page of Project Settings.

#include "Player/LostArcCharacterStatComponent.h"
#include "UI/LostArcUIProgressBar.h"
#include "Kismet/GameplayStatics.h"

ULostArcCharacterStatComponent::ULostArcCharacterStatComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
	bWantsInitializeComponent = true;
	IncreasedManaRegeneration = 5.0f;
}

void ULostArcCharacterStatComponent::InitializeComponent()
{
	Super::InitializeComponent();

	CurrentLevel = 5;
	SetCurrentLevel(CurrentLevel);
}

void ULostArcCharacterStatComponent::BeginPlay()
{
	Super::BeginPlay();

	ManaRegenerationTimerDelegate.BindUFunction(this, FName("ManaRegenerationPerSecond"), IncreasedManaRegeneration);
	GetOwner()->GetWorldTimerManager().SetTimer(ManaRegenerationTimerHandle, ManaRegenerationTimerDelegate, 2.0f, true);
}

void ULostArcCharacterStatComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

float ULostArcCharacterStatComponent::GetCurrnetAttributeValue(EAttributeType Type)
{
	switch (Type)
	{
	case HP:
		return CurrentHP;
		break;
	case MP:
		return CurrentMP;
		break;
	case ATK:
		return CurrentStatData->Attack;
		break;
	case DEF:
		return CurrentStatData->Defense;
		break;
	case EXP:
		return CurrentEXP;
		break;
	case LVL:
		return CurrentLevel;
		break;
	default:
		break;
	}
	return NULL;
}

float ULostArcCharacterStatComponent::GetMaxAttributeValue(EAttributeType Type)
{
	switch (Type)
	{
	case HP:
		return CurrentStatData->Maxhp;
		break;
	case MP:
		return CurrentStatData->Maxmp;
		break;
	case EXP:
		return CurrentStatData->Nextexp;
		break;
	default:
		break;
	}
	return NULL;
}

float ULostArcCharacterStatComponent::GetCurrentAttributeRatio(EAttributeType Type)
{
	switch (Type)
	{
	case HP:
		return CurrentStatData->Maxhp < KINDA_SMALL_NUMBER ? 0.0f : (CurrentHP / CurrentStatData->Maxhp);
		break;
	case MP:
		return CurrentStatData->Maxmp < KINDA_SMALL_NUMBER ? 0.0f : (CurrentMP / CurrentStatData->Maxmp);
		break;
	case EXP:
		return CurrentStatData->Nextexp < KINDA_SMALL_NUMBER ? 0.0f : (CurrentEXP / CurrentStatData->Nextexp);
		break;
	default:
		break;
	}
	return NULL;
}

void ULostArcCharacterStatComponent::SetCurrentAttributeValue(EAttributeType Type, float Value)
{
	switch (Type)
	{
	case HP:
		CurrentHP = Value;
		OnProgressBarChanged.Broadcast(Type);

		if (CurrentHP < KINDA_SMALL_NUMBER)
		{
			CurrentHP = 0.0f;
			OnHPIsZero.Broadcast();
		}
		break;
	case MP:
		CurrentMP = Value;
		OnProgressBarChanged.Broadcast(Type);
		break;
	case EXP:
		SetCurrentAttributeValueToInt32(Type, FMath::FloorToInt(Value));
		break;
	case LVL:
		SetCurrentAttributeValueToInt32(Type, FMath::FloorToInt(Value));
		break;
	default:
		break;
	}
}

void ULostArcCharacterStatComponent::SetCurrentAttributeValueToInt32(EAttributeType Type, int32 Value)
{
	switch (Type)
	{
	case EXP:
		CurrentEXP = Value;
		OnProgressBarChanged.Broadcast(Type);
		break;
	case LVL:
		SetCurrentLevel(Value);
		break;
	default:
		break;
	}
}

void ULostArcCharacterStatComponent::SetCurrentLevel(int32 NewLevel)
{
	auto ArcGameInstance = Cast<ULostArcGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));

	if (ArcGameInstance != nullptr)
	{
		CurrentStatData = ArcGameInstance->GetArcCharacterData(NewLevel);
		if (CurrentStatData != nullptr)
		{
			CurrentLevel = NewLevel;
			SetCurrentAttributeValue(EAttributeType::HP, CurrentStatData->Maxhp);
			SetCurrentAttributeValue(EAttributeType::MP, CurrentStatData->Maxmp);
			OnProgressBarChanged.Broadcast(EAttributeType::HP);
			OnProgressBarChanged.Broadcast(EAttributeType::MP);
		}
	}
}

void ULostArcCharacterStatComponent::SetDamage(float NewDamage)
{
	SetCurrentAttributeValue(EAttributeType::HP, FMath::Clamp<float>(CurrentHP - NewDamage, 0.0f, CurrentStatData->Maxhp));
}

void ULostArcCharacterStatComponent::ManaRegenerationPerSecond(float Amount)
{
	SetCurrentAttributeValue(EAttributeType::MP, FMath::Clamp<float>(CurrentMP + Amount, 0, CurrentStatData->Maxmp));
}