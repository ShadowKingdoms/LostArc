// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Inventory/LostArcUIInven.h"
#include "UI/Inventory/LostArcUIInvenSlot.h"
#include "Character/LostArcCharacter.h"
#include "Component/LostArcInventoryComponent.h"

void ULostArcUIInven::NativeConstruct()
{
	Super::NativeConstruct();
	OwnerCharacter = Cast<ALostArcCharacter>(GetOwningPlayerPawn());

	for (int i = 0; i < 16; i++)
	{
		InvenSlot.Add(Cast<ULostArcUIInvenSlot>(GetWidgetFromName(FName(FString::Printf(TEXT("BP_InvenSlot_%d"), i))))); 
		InvenSlot[i]->SetSlotIndex(i);
	}

	OwnerCharacter->InventoryComponent->InvenSlotUpdate.AddUObject(this, &ULostArcUIInven::RefreshSlot);
}

void ULostArcUIInven::BeginDestroy()
{
	Super::BeginDestroy();
	InvenSlot.Empty();
}

void ULostArcUIInven::RefreshSlot(int32 Index)
{
	InvenSlot[Index]->RefreshSlotData(Cast<ULostArcAbilityBase>(OwnerCharacter->InventoryComponent->GetAbility(Index)));
}

void ULostArcUIInven::EnableInventory()
{
	bEnable = !bEnable;

	if(bEnable)
	{
		this->SetVisibility(ESlateVisibility::Visible);
	}

	else
	{
		this->SetVisibility(ESlateVisibility::Hidden);
	}
}

FReply ULostArcUIInven::NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	return Super::NativeOnMouseButtonDown(InGeometry, InMouseEvent);
}
