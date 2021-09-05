// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "LostArcUIInven.generated.h"

UCLASS()
class LOSTARC_API ULostArcUIInven : public UUserWidget
{
	GENERATED_BODY()

public:
	void RefreshSlot(int32 Index);
	
protected:
	virtual void NativeConstruct() override;
	virtual void BeginDestroy() override;
	
private:
	UPROPERTY(meta = (AllowPrivateAccess = true))
	TArray<class ULostArcUISlotBase*> InvenSlot;

	class ALostArcCharacter* OwnerCharacter;
};
