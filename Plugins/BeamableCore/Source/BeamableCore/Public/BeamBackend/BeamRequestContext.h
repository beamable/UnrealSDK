// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "BeamBackend/BeamRealmHandle.h"
#include "BeamBackend/BeamRetryConfig.h"
#include "UserSlots/UserSlot.h"

#include "BeamRequestContext.generated.h"


UENUM()
enum EBeamAsyncStatus { AS_None = 0, AS_InFlight, AS_Completed };


USTRUCT(BlueprintType)
struct FBeamRequestContext
{
	GENERATED_BODY()

	/**
	 * @brief A per-session unique identifier (counts requests from 0 every session) for this request. Never persist this value.  
	 */
	UPROPERTY(BlueprintReadOnly)
	int64 RequestId = -1;

	/**
	 * @brief The retry configuration used for this request.
	 * By default, it's the one found at Project Settings > Beamable Core.
	 */
	UPROPERTY(BlueprintReadOnly)
	FBeamRetryConfig RetryConfiguration;

	/**
	 * @brief The realm handle (which realm --- normally, between dev/staging/prod, but can be any realm) that you are targeting.
	 * If you are making the request with a user slot, this will always target the realm on which that user was authenticated unless specified otherwise. 
	 */
	UPROPERTY(BlueprintReadOnly)
	FBeamRealmHandle Handle;

	/**
	 * @brief The response code (only available in OnSuccess/OnError/OnComplete). In the synchronous flow, is always -1.
	 */
	UPROPERTY(BlueprintReadOnly)
	int32 ResponseCode = -1;

	/**
	 * @brief The this request was made with --- only exists for requests that are made with one.
	 */
	UPROPERTY(BlueprintReadOnly)
	FUserSlot UserSlot;


	/**
	 * @brief Used to keep track of the request and when it can be cleared.
	 */
	EBeamAsyncStatus BeamStatus;

	FBeamRequestContext() = default;

	explicit FBeamRequestContext(int64 RequestId)
		: RequestId(RequestId), RetryConfiguration(), ResponseCode(-1), BeamStatus(AS_None)
	{
	}

	explicit FBeamRequestContext(int64 RequestId, const FBeamRetryConfig& RetryConfiguration, const FBeamRealmHandle& Handle, int32 ResponseCode, const FUserSlot& UserSlot,
	                             EBeamAsyncStatus BeamStatus)
		: RequestId(RequestId),
		  RetryConfiguration(RetryConfiguration),
		  Handle(Handle),
		  ResponseCode(ResponseCode),
		  UserSlot(UserSlot),
		  BeamStatus(BeamStatus)
	{
	}

	friend bool operator==(const FBeamRequestContext& Lhs, const FBeamRequestContext& RHS)
	{
		return Lhs.RequestId == RHS.RequestId;
	}

	friend bool operator!=(const FBeamRequestContext& Lhs, const FBeamRequestContext& RHS)
	{
		return !(Lhs == RHS);
	}
};

FORCEINLINE uint32 GetTypeHash(const FBeamRequestContext& Context) { return GetTypeHash(Context.RequestId); }
