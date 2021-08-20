// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/LostArcUIInventory.h"
#include "UI/LostArcUIInventorySlot.h"
#include "Character/LostArcCharacter.h"
#include "Player/LostArcInventoryComponent.h"


void ULostArcUIInventory::NativeConstruct()
{
	for (int i = 0; i < 16; i++)
	{
		InventorySlot.Add(Cast<ULostArcUIInventorySlot>(GetWidgetFromName(FName(FString::Printf(TEXT("BPInventory_Slot_%d"), i)))));
	}

	auto Character = Cast<ALostArcCharacter>(GetOwningPlayerPawn());
	Character->InventoryCompoennt->InventorySlotUpdate.AddUObject(this, &ULostArcUIInventory::InventorySlotConstruct);
}

void ULostArcUIInventory::BeginDestroy()
{
	Super::BeginDestroy();
	InventorySlot.Empty();
}

void ULostArcUIInventory::InventorySlotConstruct(int32 SlotIndex)
{
	auto Character = Cast<ALostArcCharacter>(GetOwningPlayerPawn());

	InventorySlot[SlotIndex]->Item = Character->InventoryCompoennt->GetSlotItem(SlotIndex);

	if (InventorySlot[SlotIndex]->Item != nullptr)
	{
		InventorySlot[SlotIndex]->BindItemDelegate();
	}
}

void ULostArcUIInventory::UpdateItemQuantity(int32 SlotIndex)
{
	if (InventorySlot[SlotIndex]->Item != nullptr)
	{
		InventorySlot[SlotIndex]->UpdateItemQuantity();
	}
}
