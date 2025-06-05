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
	FDelegate_Simple OnLiveOpsErrorConnecting;

	UPROPERTY(BlueprintAssignable)
	FDelegate_Simple OnSampleStatUpdated;

	UPROPERTY(BlueprintAssignable)
	FDelegate_Simple OnInventoryItemsUpdated;

	UPROPERTY()
	UBeamLiveOpsDemoMSApi* LiveOpsMS;

	int64 CurrentSampleStatValue = 1;

protected:
	virtual void Deinitialize() override
	{
		Super::Deinitialize();
	}

	virtual void OnWorldBeginPlay(UWorld& InWorld) override
	{
		const auto GI = InWorld.GetGameInstance();
		Runtime = GI->GetSubsystem<UBeamRuntime>();
		Stats = GI->GetSubsystem<UBeamStatsSubsystem>();
		Inventory = GI->GetSubsystem<UBeamInventorySubsystem>();
		LiveOpsMS = GEngine->GetEngineSubsystem<UBeamLiveOpsDemoMSApi>();

		Inventory->OnInventoryRefreshedCode.AddUObject(this, &ULiveOpsDemoMainMenu::OnInventoryRefreshed);

		FUserStateChangedHandler UserReadyHandler;
		FRuntimeError SDKInitializationErrorHandler;
		UserReadyHandler.BindDynamic(this, &ULiveOpsDemoMainMenu::OnBeamableUserReady);
		SDKInitializationErrorHandler.BindDynamic(this, &ULiveOpsDemoMainMenu::OnBeamableError);

		Runtime->InitSDKWithFrictionlessLogin(UserReadyHandler, SDKInitializationErrorHandler, SDKInitializationErrorHandler, {});
	}

	UFUNCTION()
	void OnBeamableError(FString ErrorMessage)
	{
		OnLiveOpsErrorConnecting.Broadcast();
	}

	UFUNCTION()
	void OnBeamableUserReady(const FUserSlot& UserSlot)
	{
		OnLiveOpsDemoReady.Broadcast();
	}

	UFUNCTION()
	void OnInventoryRefreshed(FBeamGamerTag GamerTag, FUserSlot UserSlot)
	{
		OnInventoryItemsUpdated.Broadcast();
	}

	UFUNCTION(BlueprintCallable)
	void GetInventoryData(int64& GemsCount, int64& CoinsCount, TArray<FBeamItemState>& SampleItems)
	{
		const auto UserSlot = GetDefault<UBeamCoreSettings>()->GetOwnerPlayerSlot();
		FBeamRealmUser UserData;
		if (Runtime->UserSlotSystem->GetUserDataAtSlot(UserSlot, UserData, this))
		{
			FString GemsID = "currency.gems";
			FString CoinsID = "currency.coins";

			Inventory->TryGetCurrencyAmountByGamerTag(UserData.GamerTag, GemsID, GemsCount);
			Inventory->TryGetCurrencyAmountByGamerTag(UserData.GamerTag, CoinsID, CoinsCount);

			TArray<FBeamItemState> AllItems;
			Inventory->TryGetAllItemsByGamerTag(UserData.GamerTag, AllItems);

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
			ULiveOpsDemoMSIncrementStatRequest* Request =
				ULiveOpsDemoMSIncrementStatRequest::Make(UserData.GamerTag.AsLong, this, Empty);

			const auto Handler = FOnLiveOpsDemoMSIncrementStatFullResponse::CreateLambda(
				[this,UserData](FBeamFullResponse<ULiveOpsDemoMSIncrementStatRequest*, ULiveOpsDemoMSIncrementStatResponse*> Resp)
				{
					if (Resp.SuccessData)
					{
						CurrentSampleStatValue++;
						OnSampleStatUpdated.Broadcast();
					}
				});
			FBeamRequestContext Ctx;
			LiveOpsMS->CPP_IncrementStat(UserSlot, Request, Handler, Ctx, {}, this);
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

		FBeamRealmUser UserData;
		if (Runtime->UserSlotSystem->GetUserDataAtSlot(UserSlot, UserData, this))
		{
			TMap<FString, FString> Empty;
			ULiveOpsDemoMSUpgradeItemRequest* Request =
				ULiveOpsDemoMSUpgradeItemRequest::Make(UserData.GamerTag.AsLong, ItemInstanceID, this, Empty);

			const auto Handler = FOnLiveOpsDemoMSUpgradeItemFullResponse::CreateLambda(
				[this,UserData](FBeamFullResponse<ULiveOpsDemoMSUpgradeItemRequest*, ULiveOpsDemoMSUpgradeItemResponse*> Resp)
				{
					if (Resp.SuccessData)
					{
						OnInventoryItemsUpdated.Broadcast();
					}
				});
			FBeamRequestContext Ctx;
			LiveOpsMS->CPP_UpgradeItem(UserSlot, Request, Handler, Ctx, {}, this);
		}
	}
};
