// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AutoGen/SubSystems/BeamRealmsApi.h"
#include "AutoGen/SubSystems/BeamStatsApi.h"
#include "BeamNotifications/BeamNotifications.h"
#include "BeamBackend/SemanticTypes/BeamStatsTypeLibrary.h"
#include "Runtime/BeamRuntimeSubsystem.h"
#include "MyGamePlayerStatsSubsystem.generated.h"

/**
 * 
 */
UCLASS()
class BEAMABLEUNREAL_API UMyGamePlayerStatsSubsystem : public UBeamRuntimeSubsystem
{
	GENERATED_BODY()

	const FString Stat_CurrentScore = TEXT("CurrentScore");

	UPROPERTY()
	UBeamUserSlots* UserSlots;
	UPROPERTY()
	UBeamStatsApi* StatsApi;
	FBeamWebSocketHandle Handle;

public:
	virtual void Initialize(FSubsystemCollectionBase& Collection) override
	{
		Super::Initialize(Collection);
		UserSlots = GEngine->GetEngineSubsystem<UBeamUserSlots>();
		StatsApi = GEngine->GetEngineSubsystem<UBeamStatsApi>();
	}

	virtual void OnPostUserSignedIn_Implementation(const FUserSlot& UserSlot, const FBeamRealmUser& BeamRealmUser, const bool bIsOwnerUserFirstAuth, FBeamOperationHandle& ResultOp) override
	{
		const auto RequestTracker = GEngine->GetEngineSubsystem<UBeamRequestTracker>();
		
		const auto Slot = FUserSlot{TEXT("Player0")};

		const auto OpHandler = FBeamOperationEventHandlerCode::CreateLambda([](FBeamOperationEvent Evt)
		{						
		});
		const auto Op = RequestTracker->CPP_BeginOperation({Slot}, GetName(), OpHandler);
		
		FBeamRealmUser User;
		if (UserSlots->GetUserDataAtSlot(Slot, User, this))
		{
			const auto StatsType = UBeamStatsTypeLibrary::MakeStatsType(Client, Private, User.GamerTag);
			const auto Req = UGetClientRequest::Make(StatsType, FOptionalString(TEXT("test_stats")), GetTransientPackage(), {});
			const auto Handler = FOnGetClientFullResponse::CreateUObject(this, &UMyGamePlayerStatsSubsystem::OnGetUpdatedStats, Op);
			FBeamRequestContext Ctx;
			StatsApi->CPP_GetClient(Slot, Req, Handler, Ctx, Op, this);
			UE_LOG(LogTemp, Warning, TEXT("Gettings stats..."))			
		}

		ResultOp = Op;
	}	
	
	void OnGetUpdatedStats(FGetClientFullResponse Response, FBeamOperationHandle Op)
	{
		const auto RequestTracker = GEngine->GetEngineSubsystem<UBeamRequestTracker>();

		UE_LOG(LogTemp, Warning, TEXT("Response arrived..."))
		if (Response.State == RS_Error)
		{
			// Info: Handle errors
			const auto ErrorData = Response.ErrorData;
			RequestTracker->TriggerOperationError(Op, Response.ErrorData.message);
			return;
		}

		if (Response.State == RS_Cancelled)
		{
			// Info: In cases where you allow user cancellation, do whatever you need to do to ignore the response and get the state correct after the user pressed 'cancel' somewhere in the UI.
			const auto Context = Response.Context;
			RequestTracker->TriggerOperationCancelled(Op, TEXT(""));
			return;
		}

		// Info: Handle success case. Here I'm just printing out the stats
		const auto SuccessData = Response.SuccessData;
		const auto UserId = *SuccessData->Id.AsString;
		for (const auto& StatKvp : SuccessData->Stats)
		{
			UE_LOG(LogTemp, Warning, TEXT("Player %s - [%s = %s]"), UserId, *StatKvp.Key, *StatKvp.Value)
		}
		RequestTracker->TriggerOperationSuccess(Op, TEXT(""));
	}
};
