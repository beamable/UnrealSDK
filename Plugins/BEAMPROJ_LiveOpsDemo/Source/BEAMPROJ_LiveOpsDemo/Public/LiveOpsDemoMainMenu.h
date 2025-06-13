// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Runtime/BeamLevelSubsystem.h"
#include "Subsystems/Inventory/BeamInventorySubsystem.h"
#include "Subsystems/Stats/BeamStatsSubsystem.h"
#include "AutoGen/SubSystems/BeamLiveOpsDemoMsApi.h"
#include "LiveOpsDemoMainMenu.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FDelegate_Simple);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FOnReceiveTwoFactorChallenge, FUserSlot, UserSlot, FString, DecodedChallenge, UBeamMultiFactorLoginData*, ChallengeSolution);

/**
 * 
 */
UCLASS()
class BEAMPROJ_LIVEOPSDEMO_API ULiveOpsDemoMainMenu : public UBeamLevelSubsystem
{
	GENERATED_BODY()

	FDelegateHandle OnBeamableReadyHandle;

	FString GetSuiMicroserviceName() const { return TEXT("SuiFederation"); }
	FString GetSuiIdentityName() const { return TEXT("SuiIdentity"); }
	FString GetSuiExternalIdentityName() const { return TEXT("SuiExternalIdentity"); }

	virtual FString GetSpecificLevelName() const override { return FString(TEXT("LiveOpsDemo")); }

public:
	UPROPERTY()
	UBeamRuntime* Runtime;

	UPROPERTY()
	UBeamStatsSubsystem* Stats;

	UPROPERTY()
	UBeamInventorySubsystem* Inventory;

	UPROPERTY()
	UBeamLiveOpsDemoMSApi* LiveOpsMS;

	UPROPERTY()
	UBeamAccountsApi* AccountApi;

	UPROPERTY(BlueprintReadOnly)
	FString SuiWalletId;

	UPROPERTY(BlueprintReadOnly)
	FString SuiWalletIdExternal;


	FUserSlot OwnerUserSlot;
	int64 CurrentSampleStatValue = 1;

protected:
	virtual void Deinitialize() override
	{
		Super::Deinitialize();
	}

	virtual void OnWorldBeginPlay(UWorld& InWorld) override
	{
		const auto GI = InWorld.GetGameInstance();

		// Cache all GameInstance Subsystems we'll need.
		Runtime = GI->GetSubsystem<UBeamRuntime>();
		Stats = GI->GetSubsystem<UBeamStatsSubsystem>();
		Inventory = GI->GetSubsystem<UBeamInventorySubsystem>();
		LiveOpsMS = GEngine->GetEngineSubsystem<UBeamLiveOpsDemoMSApi>();
		AccountApi = GEngine->GetEngineSubsystem<UBeamAccountsApi>();

		// Cache the OwnerUserSlot that'll hold the user for this demo
		OwnerUserSlot = GetDefault<UBeamCoreSettings>()->GetOwnerPlayerSlot();

		// Initialize the SDK
		FBeamRuntimeHandler OnSdkInitHandler;
		FRuntimeError OnSdkInitErrorHandler;
	}

	UFUNCTION(BlueprintCallable)
	void UpgradeItem(int64 ItemInstanceID)
	{
		TArray<FBeamItemState> AllItems;
		if (Inventory->TryGetAllItems(OwnerUserSlot, AllItems))
		{
			// Find the item with the given id.
			const auto ItemIdx = AllItems.Find(FBeamItemState{{}, ItemInstanceID});
			if (ItemIdx != INDEX_NONE)
			{
				FBeamItemState Item = AllItems[ItemIdx];

				// Increment the current item level
				const auto CurrLevelStr = Item.Properties.Find(TEXT("itemLevel"));
				if (CurrLevelStr)
				{
					int64 NewLevel;
					FDefaultValueHelper::ParseInt64(*CurrLevelStr, NewLevel);
					NewLevel += 1;
					Item.Properties[TEXT("itemLevel")] = FString::Printf(TEXT("%lld"), NewLevel);
				}

				// Modify the item
				FBeamInventoryUpdateCommand Cmds;
				Inventory->BeginInventoryUpdate(OwnerUserSlot, Cmds, true);
				Inventory->PrepareModifyItem(OwnerUserSlot, Item);
				Inventory->CPP_CommitInventoryUpdateOperation(OwnerUserSlot, FBeamOperationEventHandlerCode::CreateLambda([this](FBeamOperationEvent Evt)
				{
					// Once the modification is done, update the UI.
					// OnInventoryItemsUpdated.Broadcast();
				}));
			}
		}
	}
};
