// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Runtime/BeamLevelSubsystem.h"
#include "Subsystems/Inventory/BeamInventorySubsystem.h"
#include "Subsystems/Stats/BeamStatsSubsystem.h"
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

		const auto OnReady = FRuntimeStateChangedHandlerCode::CreateUObject(this, &ThisClass::OnBeamableReady);
		OnBeamableReadyHandle = Runtime->CPP_RegisterOnReady(OnReady);
	}

	void OnBeamableReady()
	{
		const auto UserSlot = GetDefault<UBeamCoreSettings>()->GetOwnerPlayerSlot();

		const auto StatHandler = FBeamOperationEventHandlerCode::CreateLambda([this](FBeamOperationEvent Evt)
		{
			if (Evt.EventType == OET_SUCCESS)
			{
				UE_LOG(LogTemp, Warning, TEXT("Successfully initialized my_sample_stat to 1"));
				OnLiveOpsDemoReady.Broadcast();
			}
		});
		Stats->CPP_SetStatOperation(UserSlot, TEXT("my_sample_stat"), TEXT("1"), StatHandler);
	}

	UFUNCTION(BlueprintCallable)
	void IncrementSampleStat()
	{
		const auto UserSlot = GetDefault<UBeamCoreSettings>()->GetOwnerPlayerSlot();
		FBeamRealmUser UserData;
		if (Runtime->UserSlotSystem->GetUserDataAtSlot(UserSlot, UserData, this))
		{
			const auto StatType = UBeamStatsTypeLibrary::MakeStatsType(Client, Public, UserData.GamerTag);

			const auto PlayerStatsState = Stats->PlayerStatCache.FindChecked(StatType);
			const auto StatStr = PlayerStatsState->StringStats.FindChecked(TEXT("my_sample_stat"));

			int64 OldVal;
			if (FDefaultValueHelper::ParseInt64(StatStr, OldVal))
			{
				const auto NewVal = FString::Printf(TEXT("%llu"), OldVal + 1);
				const auto StatHandler = FBeamOperationEventHandlerCode::CreateLambda([this, NewVal](FBeamOperationEvent Evt)
				{
					UE_LOG(LogTemp, Warning, TEXT("Successfully incremented my_sample_stat: %s"), *NewVal)
					if (Evt.EventType == OET_SUCCESS)
					{
						OnSampleStatUpdated.Broadcast();
					}
				});
				Stats->CPP_SetStatOperation(UserSlot, "my_sample_stat", NewVal, StatHandler);
			}
		}
	}

	UFUNCTION(BlueprintCallable)
	int64 GetSampleStat()
	{
		const auto UserSlot = GetDefault<UBeamCoreSettings>()->GetOwnerPlayerSlot();
		FBeamRealmUser UserData;
		if (Runtime->UserSlotSystem->GetUserDataAtSlot(UserSlot, UserData, this))
		{
			const auto StatType = UBeamStatsTypeLibrary::MakeStatsType(Client, Public, UserData.GamerTag);

			const auto PlayerStatsState = Stats->PlayerStatCache.FindChecked(StatType);
			const auto StatStr = PlayerStatsState->StringStats.FindChecked(TEXT("my_sample_stat"));

			int64 OldVal;
			if (FDefaultValueHelper::ParseInt64(StatStr, OldVal))
			{
				return OldVal;
			}
		}

		return -1;
	}
};
