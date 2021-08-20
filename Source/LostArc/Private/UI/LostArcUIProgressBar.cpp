// Fill out your copyright notice in the Description page of Project Settings.

#include "UI/LostArcUIProgressBar.h"
#include "Character/LostArcCharacter.h"
#include "Component/LostArcCharacterStatComponent.h"
#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"

void ULostArcUIProgressBar::NativeConstruct()
{
	Super::NativeConstruct();
	auto Character = GetOwningPlayerPawn<ALostArcCharacter>();

	ProgressBar->SetFillColorAndOpacity(FLinearColor(BarColor.R, BarColor.G, BarColor.B));
	ProgressBar->SetRenderShear(BarShearValue);
	ProgressBar->SetRenderScale(BarRenderScale);

	CurrentText->SetText(FText::AsNumber(Character->StatComponent->GetCurrnetAttributeValue(BarType)));
	MaxText->SetText(FText::AsNumber(Character->StatComponent->GetMaxAttributeValue(BarType)));

	Character->StatComponent->OnProgressBarChanged.AddUObject(this, &ULostArcUIProgressBar::UpdateProgressBar);

	if (BarType == EXP)
	{
		CurrentText->SetVisibility(ESlateVisibility::Hidden);
		SlashText->SetVisibility(ESlateVisibility::Hidden);
		MaxText->SetVisibility(ESlateVisibility::Hidden);
	}
}

void ULostArcUIProgressBar::UpdateProgressBar(EAttributeType OwnerType)
{
	if (BarType == OwnerType)
	{
		auto Character = Cast<ALostArcCharacter>(GetOwningPlayerPawn());

		CurrentText->SetText(FText::AsNumber(Character->StatComponent->GetCurrnetAttributeValue(BarType)));
		MaxText->SetText(FText::AsNumber(Character->StatComponent->GetMaxAttributeValue(BarType)));
		ProgressBar->SetPercent(Character->StatComponent->GetCurrentAttributeRatio(BarType));
	}
}