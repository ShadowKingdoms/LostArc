// Fill out your copyright notice in the Description page of Project Settings.

#include "UI/Quick/LostArcUIQuickSlot.h"
#include "Abilities/Items/Equip/LostArcItemEquipBase.h"
#include "Abilities/Items/Potion/LostArcItemPotionBase.h"
#include "Abilities/Skill/LostArcSkillBase.h"
#include "Blueprint/WidgetBlueprintLibrary.h"
#include "Component/LostArcCharacterInterface.h"
#include "Component/LostArcQuickSlotComponent.h"
#include "Controller/LostArcPlayerController.h"
#include "UI/LostArcUIMainHUD.h"

void ULostArcUIQuickSlot::NativeConstruct()
{
	Super::NativeConstruct();
	
	SlotType = ESlotType::Quick;
	Text_Key->SetText(KeyName);
}

bool ULostArcUIQuickSlot::NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation)
{
	auto OwnerDrag = Cast<ULostArcUISlotDrag>(InOperation);
	if(OwnerDrag == nullptr) return false;
	if(SlotData && GetOwningPlayer()->GetWorldTimerManager().IsTimerActive(SlotData->AbilityCDProperty.Key)) return false;

	switch (QuickSlotType)
	{
		case EQuickSlotType::Ability:
		break;

		case EQuickSlotType::Potion:
		
		ILostArcCharacterInterface * Interface = Cast<ILostArcCharacterInterface>(OwnerDrag->SlotComponent);
		if(Cast<ULostArcItemEquipBase>(Interface->GetAbility(OwnerDrag->SlotIndex))) return false;
		
		if(OwnerDrag->SlotType == ESlotType::Inven)
		{
			auto OwnerItem = Cast<ULostArcItemBase>(Interface->GetAbility(OwnerDrag->SlotIndex));
			RefreshSlotData(OwnerItem);
			
			RefIndex = OwnerDrag->SlotIndex;
			ItemQuantityHandle = OwnerItem->QuantityUpdate.AddUObject(this, &ULostArcUIQuickSlot::UpdateQuantity);
			Text_Quantity->SetText(FText::AsNumber(FMath::FloorToInt(OwnerItem->GetItemQuantity())));
			Text_Quantity->SetVisibility(ESlateVisibility::Visible);
			Cast<ALostArcCharacter>(GetOwningPlayerPawn())->QuickSlotComponent->QuickSlot[SlotIndex] = Interface->GetAbility(OwnerDrag->SlotIndex); // 컴포넌트에 데이터 복사
		}
		
		if(OwnerDrag->SlotType == ESlotType::Quick)
		{
			if(OwnerDrag->SlotIndex == SlotIndex) return false;
			
			auto OwnerItem = Cast<ULostArcItemBase>(Interface->GetAbility(OwnerDrag->SlotIndex,true));
			Cast<ALostArcPlayerController>(GetOwningPlayer())->MainHUD->BP_Quick->ClearQuickSlot(OwnerDrag->SlotIndex);
			RefreshSlotData(OwnerItem);
			
			RefIndex = OwnerDrag->SlotIndex;
			ItemQuantityHandle = OwnerItem->QuantityUpdate.AddUObject(this, &ULostArcUIQuickSlot::UpdateQuantity);
			Text_Quantity->SetText(FText::AsNumber(FMath::FloorToInt(OwnerItem->GetItemQuantity())));
			Text_Quantity->SetVisibility(ESlateVisibility::Visible);
			Cast<ALostArcCharacter>(GetOwningPlayerPawn())->QuickSlotComponent->QuickSlot[SlotIndex] = OwnerItem;
		}
		break;
	}
	// 퀵 슬롯끼리 교환하려면 결국엔 QuickComponent에서 SappingSlot 오버라이딩이 필요
	return false;
}

void ULostArcUIQuickSlot::RefreshSlotData(ULostArcAbilityBase* NewData)
{
	if(SlotData != nullptr)
	{
		UnBindSlotData();
	}
	
	Super::RefreshSlotData(NewData);
	
	UpdateQuantity();
}

void ULostArcUIQuickSlot::UnBindSlotData()
{
	Super::UnBindSlotData();
	
	auto SlotItem = Cast<ULostArcItemBase>(SlotData);
	if (SlotItem != nullptr)
	{
		SlotItem->QuantityUpdate.Remove(ItemQuantityHandle);
	}
}

void ULostArcUIQuickSlot::UpdateQuantity()
{
	if (SlotData != nullptr) 
	{
		if(FMath::FloorToInt(Cast<ULostArcItemBase>(SlotData)->GetItemQuantity()) <=0) // 삭제해도 계속 남아있음(수정필요)
		{
			Cast<ALostArcCharacter>(GetOwningPlayerPawn())->QuickSlotComponent->QuickSlot[SlotIndex] = nullptr;
			// 인벤토리 슬롯의 인덱스 추적은 불가
			Text_Quantity->SetVisibility(ESlateVisibility::Hidden);
			Image_Icon->SetVisibility(ESlateVisibility::Hidden);
			UnBindSlotData();
			SlotData = nullptr;
		}
		else
		{
			Text_Quantity->SetText(FText::AsNumber(FMath::FloorToInt(Cast<ULostArcItemBase>(SlotData)->GetItemQuantity())));
		}
	}
}

void ULostArcUIQuickSlot::ClearSlotData()
{
	Text_Quantity->SetVisibility(ESlateVisibility::Hidden);
	Image_Icon->SetVisibility(ESlateVisibility::Hidden);
	Image_CD->SetVisibility(ESlateVisibility::Hidden);

	SlotData->AbilityCDProperty.Value.Remove(AbilityCDHandle); // 엔진에 등록된 AbilityCDHandle 델리게이트 핸들을 삭제
	SlotData = nullptr;
}
