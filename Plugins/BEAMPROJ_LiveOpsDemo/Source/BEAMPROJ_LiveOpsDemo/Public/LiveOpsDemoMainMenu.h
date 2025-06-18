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
class BEAMPROJ_LIVEOPSDEMO_API ULiveOpsDemoMainMenu : public UBeamRuntimeSubsystem
{
	GENERATED_BODY()

public:
	UPROPERTY()
	UBeamStatsSubsystem* Stats;

	UPROPERTY()
	UBeamInventorySubsystem* Inventory;


	UPROPERTY(BlueprintAssignable)
	FDelegate_Simple OnSampleStatUpdated;

	UPROPERTY()
	UBeamLiveOpsDemoMSApi* LiveOpsMS;

	int64 CurrentSampleStatValue;

protected:
	virtual void Initialize(FSubsystemCollectionBase& Collection) override
	{
		Super::Initialize(Collection);
		Stats = Collection.InitializeDependency<UBeamStatsSubsystem>();
		Inventory = Collection.InitializeDependency<UBeamInventorySubsystem>();
		LiveOpsMS = GEngine->GetEngineSubsystem<UBeamLiveOpsDemoMSApi>();
	}

	/**
	 * Whenever a user signs in, we manually call our microservice's ULive endpoint 
	 */
	virtual void OnUserSignedIn_Implementation(const FUserSlot& UserSlot, const FBeamRealmUser& BeamRealmUser, const bool bIsOwnerUserAuth, FBeamOperationHandle& ResultOp) override
	{
		// Create an operation that you return to Beamable
		// This operation is now part of the Login flow; this means that if this operation fails your login will fail.
		// It also means that when the login is completed successfully, this operation is guaranteed to have run correctly so you can read this system's local state.
		ResultOp = Runtime->RequestTrackerSystem->CPP_BeginOperation({UserSlot}, GetName(), {});

		// Get the data for the signed-in user.
		FBeamRealmUser UserData;
		if (Runtime->UserSlotSystem->GetUserDataAtSlot(UserSlot, UserData, this))
		{
			TMap<FString, FString> Empty;

			// Prepare the request to the microservice and the handler.
			const auto Request = ULiveOpsDemoMSGetSampleStatRequest::Make(UserData.GamerTag.AsLong, this, Empty);
			const auto Handler = FOnLiveOpsDemoMSGetSampleStatFullResponse::CreateLambda(
				[this, ResultOp](FLiveOpsDemoMSGetSampleStatFullResponse Resp)
				{
					if (Resp.SuccessData)
					{
						CurrentSampleStatValue = Resp.SuccessData->Value;
						OnSampleStatUpdated.Broadcast();
						Runtime->RequestTrackerSystem->TriggerOperationSuccess(ResultOp, {});
					}
					else
					{
						Runtime->RequestTrackerSystem->TriggerOperationError(ResultOp, Resp.ErrorData.message);
					}
				});

			// Make the request
			FBeamRequestContext Ctx;
			LiveOpsMS->CPP_GetSampleStat(UserSlot, Request, Handler, Ctx, ResultOp, this);
		}
		else
		{
			Runtime->RequestTrackerSystem->TriggerOperationError(ResultOp, TEXT("NO_SIGNED_IN_USER"));
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
			const auto Request = ULiveOpsDemoMSIncrementStatRequest::Make(UserData.GamerTag.AsLong, this, Empty);
			const auto Handler = FOnLiveOpsDemoMSIncrementStatFullResponse::CreateLambda(
				[this, UserData](FBeamFullResponse<ULiveOpsDemoMSIncrementStatRequest*, ULiveOpsDemoMSIncrementStatResponse*> Resp)
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
	int64 GetSampleStat() const
	{
		return CurrentSampleStatValue;
	}

	UFUNCTION(BlueprintCallable)
	void UpgradeItem(int64 ItemInstanceID)
	{
		const auto UserSlot = GetDefault<UBeamCoreSettings>()->GetOwnerPlayerSlot();

		// Get the player's data so we can call our microservice
		FBeamRealmUser UserData;
		if (Runtime->UserSlotSystem->GetUserDataAtSlot(UserSlot, UserData, this))
		{
			// Prepare the request
			TMap<FString, FString> Empty;
			const auto Request = ULiveOpsDemoMSUpgradeItemRequest::Make(UserData.GamerTag.AsLong, ItemInstanceID, this, Empty);

			// Make the request
			// For this request, you don't need a handler since our UBeamInventorySubsystem implementation will receive a notification that this item
			// was modified, refresh itself and then broadcast a multicast delegate our UI blueprints bind to so they refresh themselves.
			FBeamRequestContext Ctx;
			LiveOpsMS->CPP_UpgradeItem(UserSlot, Request, {}, Ctx, {}, this);
		}
	}
};
