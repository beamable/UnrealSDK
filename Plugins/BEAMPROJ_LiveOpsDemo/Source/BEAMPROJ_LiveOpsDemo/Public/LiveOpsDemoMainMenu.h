// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Runtime/BeamLevelSubsystem.h"
#include "Subsystems/Inventory/BeamInventorySubsystem.h"
#include "Subsystems/Stats/BeamStatsSubsystem.h"
#include "AutoGen/SubSystems/BeamLiveOpsDemoMsApi.h"
#include "LiveOpsDemoMainMenu.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FDelegate_Simple);

/**
 * 
 */
UCLASS()
class BEAMPROJ_LIVEOPSDEMO_API ULiveOpsDemoMainMenu : public UBeamLevelSubsystem
{
	GENERATED_BODY()

	FDelegateHandle OnBeamableReadyHandle;

	virtual FString GetSpecificLevelName() const override { return FString(TEXT("LiveOpsDemo")); }

public:
	UPROPERTY()
	UBeamRuntime* Runtime;

	UPROPERTY()
	UBeamStatsSubsystem* Stats;

	UPROPERTY()
	UBeamInventorySubsystem* Inventory;


	UPROPERTY(BlueprintAssignable)
	FDelegate_Simple OnLiveOpsDemoReady;

	UPROPERTY(BlueprintAssignable)
	FDelegate_Simple OnSampleStatUpdated;

	UPROPERTY(BlueprintAssignable)
	FDelegate_Simple OnInventoryItemsUpdated;
	
	UPROPERTY()
	UBeamLiveOpsDemoMsApi *LiveOpsMS;

	int64 CurrentSampleStatValue  = 1;

protected:
	virtual void Deinitialize() override
	{
		Super::Deinitialize();
		Runtime->CPP_UnregisterOnReady(OnBeamableReadyHandle);
	}

	virtual void OnWorldBeginPlay(UWorld& InWorld) override
	{
		const auto GI = InWorld.GetGameInstance();
		Runtime = GI->GetSubsystem<UBeamRuntime>();
		Stats = GI->GetSubsystem<UBeamStatsSubsystem>();
		Inventory = GI->GetSubsystem<UBeamInventorySubsystem>();
		LiveOpsMS = GEngine->GetEngineSubsystem<UBeamLiveOpsDemoMsApi>();

		Inventory->OnInventoryRefreshedCode.AddUObject(this,&ULiveOpsDemoMainMenu::OnInventoryRefreshed);
		
		const auto OnReady = FRuntimeStateChangedHandlerCode::CreateUObject(this, &ThisClass::OnBeamableReady);
		OnBeamableReadyHandle = Runtime->CPP_RegisterOnReady(OnReady);
	}

	void OnBeamableReady()
	{
		const auto UserSlot = GetDefault<UBeamCoreSettings>()->GetOwnerPlayerSlot();
		
		FBeamRealmUser UserData;
		if (Runtime->UserSlotSystem->GetUserDataAtSlot(UserSlot, UserData, this))
		{
			TMap<FString, FString> empty;
			ULiveOpsDemoMsPrepareNewPlayerRequest* request =
				ULiveOpsDemoMsPrepareNewPlayerRequest::Make(UserData.GamerTag.AsLong,this, empty);
			
			const auto Handler = FOnLiveOpsDemoMsPrepareNewPlayerFullResponse::CreateLambda(
				[this](FBeamFullResponse<ULiveOpsDemoMsPrepareNewPlayerRequest*, ULiveOpsDemoMsPrepareNewPlayerResponse*> Resp)
				{
					if (Resp.SuccessData)
					{
						OnLiveOpsDemoReady.Broadcast();
						UE_LOG(LogTemp, Display, TEXT("Payer initial data was set successfully"));
					}
				});
			FBeamRequestContext Ctx;
			LiveOpsMS->CPP_PrepareNewPlayer(UserSlot,request,Handler,Ctx,{},this);

			
		}
	}
	UFUNCTION()
	void OnInventoryRefreshed(FBeamGamerTag GamerTag, FUserSlot UserSlot)
	{
		OnInventoryItemsUpdated.Broadcast();
	}
	UFUNCTION(BlueprintCallable)
	void GetInventoryData(int64 &GemsCount,int64 &CoinsCount,TArray<FBeamItemState> &SampleItems)
	{
		const auto UserSlot = GetDefault<UBeamCoreSettings>()->GetOwnerPlayerSlot();
		FBeamRealmUser UserData;
		if (Runtime->UserSlotSystem->GetUserDataAtSlot(UserSlot, UserData, this))
		{
			FString GemsID = "currency.gems";
			FString CoinsID = "currency.coins";
			
			Inventory->TryGetCurrencyAmountByGamerTag(UserData.GamerTag,GemsID,GemsCount);
			Inventory->TryGetCurrencyAmountByGamerTag(UserData.GamerTag,CoinsID,CoinsCount);
			
			TArray<FBeamItemState> AllItems;
			Inventory->TryGetAllItemsByGamerTag(UserData.GamerTag,AllItems);

			for (auto ItemState : AllItems)
			{
				if (ItemState.ContentId.AsString == "items.sample_item")
				{
					SampleItems.Add(ItemState);
				}
			}
		}
		
	}

	UFUNCTION(BlueprintCallable)
	void IncrementSampleStat()
	{
		const auto UserSlot = GetDefault<UBeamCoreSettings>()->GetOwnerPlayerSlot();
		
		FBeamRealmUser UserData;
		if (Runtime->UserSlotSystem->GetUserDataAtSlot(UserSlot, UserData, this))
		{
			TMap<FString, FString> Empty;
			ULiveOpsDemoMsIncrementStatRequest* Request =
				ULiveOpsDemoMsIncrementStatRequest::Make(UserData.GamerTag.AsLong,this, Empty);
			
			const auto Handler = FOnLiveOpsDemoMsIncrementStatFullResponse::CreateLambda(
				[this,UserData](FBeamFullResponse<ULiveOpsDemoMsIncrementStatRequest*, ULiveOpsDemoMsIncrementStatResponse*> Resp)
				{
					if (Resp.SuccessData)
					{
						CurrentSampleStatValue++;
						OnSampleStatUpdated.Broadcast();
					}
				});
			FBeamRequestContext Ctx;
			LiveOpsMS->CPP_IncrementStat(UserSlot,Request,Handler,Ctx,{},this);
		}
		
	}

	UFUNCTION(BlueprintCallable)
	int64 GetSampleStat()
	{
		return CurrentSampleStatValue;
	}
	
	UFUNCTION(BlueprintCallable)
	void UpgradeItem(int64 ItemInstanceID)
	{
	
		const auto UserSlot = GetDefault<UBeamCoreSettings>()->GetOwnerPlayerSlot();
		Inventory->CPP_FetchAllInventoryOperation(UserSlot,{});
		FBeamRealmUser UserData;
		if (Runtime->UserSlotSystem->GetUserDataAtSlot(UserSlot, UserData, this))
		{
			TMap<FString, FString> Empty;
			ULiveOpsDemoMsUpgradeItemRequest* Request =
				ULiveOpsDemoMsUpgradeItemRequest::Make(UserData.GamerTag.AsLong,ItemInstanceID,this, Empty);
			
			const auto Handler = FOnLiveOpsDemoMsUpgradeItemFullResponse::CreateLambda(
				[this,UserData](FBeamFullResponse<ULiveOpsDemoMsUpgradeItemRequest*, ULiveOpsDemoMsUpgradeItemResponse*> Resp)
				{
					UE_LOG(LogTemp, Display, TEXT("call succeeded"));
					int i =0;
					if (Resp.SuccessData)
					{
						OnInventoryItemsUpdated.Broadcast();
					}
				});
			FBeamRequestContext Ctx;
			LiveOpsMS->CPP_UpgradeItem(UserSlot,Request,Handler,Ctx,{},this);
		}
	}
	

};
