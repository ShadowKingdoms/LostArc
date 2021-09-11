// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Component/LostArcCharacterInterface.h"
#include "LostArcInventoryComponent.generated.h"

DECLARE_MULTICAST_DELEGATE_OneParam(FOnInvenSlotUpdateDelegate, int32)

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class LOSTARC_API ULostArcInventoryComponent : public UActorComponent, public ILostArcCharacterInterface
{
	GENERATED_BODY()
	
public:
	FOnInvenSlotUpdateDelegate InvenSlotUpdate;
	
	ULostArcInventoryComponent();
	virtual void UseAbility(int32 SlotIndex) override;
	virtual void SwappingSlot(int32 OwnerIndex, int32 DistIndex, UActorComponent* OwnerComponent = nullptr) override;
	virtual bool SetAbility(ULostArcAbilityBase* OwnerAbility, int32 SlotIndex = -1) override;
	virtual ULostArcAbilityBase* GetAbility(int32 SlotIndex, bool bTrans = false) override;

	void AddPickupItem(FString ItemName, int32 ItemCount = 1);

protected:
	static constexpr int32 MaxItemSlot = 16;
	virtual void InitializeComponent() override;
	virtual void BeginPlay() override;
	virtual void EndPlay(EEndPlayReason::Type EndPlayReason) override;

private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Item, meta = (AllowPrivateAccess = true))
	TArray<TSubclassOf<class ULostArcItemBase>> ItemClass;

	TMap<FString, TSubclassOf<class ULostArcItemBase>> ItemTable;

	TArray<class ULostArcItemBase*> InventorySlot;
};