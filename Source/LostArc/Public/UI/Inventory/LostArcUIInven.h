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

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (BindWidget, AllowPrivateAccess = true))
	class ULostArcUITabs* TitleBorder;

protected:
	virtual void NativeConstruct() override;
	virtual void BeginDestroy() override;
	
private:
	UPROPERTY()
	TArray<class ULostArcUISlotBase*> InvenSlot;

	UPROPERTY()
	class ALostArcPlayerCharacter* OwnerCharacter;
};
