// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/LostArcUIMainHUD.h"

#include "Components/PanelWidget.h"
#include "UI/LostArcUIProgressBar.h"

void ULostArcUIMainHUD::NativePreConstruct()
{
	Super::NativePreConstruct();
	Visibility = ESlateVisibility::Visible;
}

void ULostArcUIMainHUD::NativeConstruct()
{
	Super::NativeConstruct();
}

void ULostArcUIMainHUD::EnableWidget(ESlotType EType)
{
	switch (EType)
	{
	case ESlotType::Inven:
		BP_Inven->GetVisibility() == ESlateVisibility::Visible ? BP_Inven->SetVisibility(ESlateVisibility::Hidden) : BP_Inven->SetVisibility(ESlateVisibility::Visible); 
		break;

	case ESlotType::Equip:
		BP_Equip->GetVisibility() == ESlateVisibility::Visible ? BP_Equip->SetVisibility(ESlateVisibility::Hidden) : BP_Equip->SetVisibility(ESlateVisibility::Visible); 
		break;

	default:
		break;
	}
}

bool ULostArcUIMainHUD::NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation)
{
	Super::NativeOnDrop(InGeometry, InDragDropEvent, InOperation);
	
	ULostArcUISlotDrag* WidgetDD = Cast<ULostArcUISlotDrag>(InOperation);
	if (WidgetDD == nullptr || WidgetDD->SlotType != ESlotType::TitleTab) return false;
	
	// 생성된 위젯 표시
	BP_Inven = Cast<ULostArcUIInven>(WidgetDD->WidgetToDrag);
	BP_Inven->AddToViewport(1);
	
	//FVector2D NewPosition = InGeometry.LocalToAbsolute(InGeometry.GetAbsolutePosition()) - WidgetDD->MouseOffset;
	BP_Inven->SetPositionInViewport(InGeometry.AbsoluteToLocal(InDragDropEvent.GetScreenSpacePosition() - WidgetDD->MouseOffset), false);
	UE_LOG(LogTemp, Warning, TEXT("Target Offset : X: %f, Y: %f"), InDragDropEvent.GetScreenSpacePosition().X, InDragDropEvent.GetScreenSpacePosition().Y);
	// UE_LOG(LogTemp, Warning, TEXT("%s"), *FString(WidgetDD->WidgetToDrag->GetParent()->GetFullName()));
	
	return true;
}
