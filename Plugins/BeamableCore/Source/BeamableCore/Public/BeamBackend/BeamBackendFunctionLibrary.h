// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BeamRequestContext.h"

#include "BeamBackendFunctionLibrary.generated.h"

UCLASS(BlueprintType)
class UBeamBackendFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
public:
	/**
	 * @brief Whether or not the given request was successful.
	 * @param Context The context to check.
	 * @return TRUE If successful. False if not successful OR if InFlight. 
	 */
	UFUNCTION(BlueprintPure, Category="Beam")
	static bool WasSuccess(const FBeamRequestContext& Context);

	/**
	 * @brief Whether or not the given request was not successful.
	 * @param Context The context to check.
	 * @return TRUE If NOT successful. False if successful OR if InFlight.
	 */
	UFUNCTION(BlueprintPure, Category="Beam")
	static bool WasError(const FBeamRequestContext& Context);

	/**
	 * @brief This will tell the BeamBackend to ignore the result of this request if it was sent but has not returned yet.
	 * If the request was not sent, it'll simply discard the unsent request instead.
	 * 
	 * @param Context The RequestContext of the request you wish to cancel.
	 */
	UFUNCTION(BlueprintCallable, Category="Beam")
	static void CancelRequest(const FBeamRequestContext& Context);

	/**
	 * @brief This will check and see if the request was cancelled and is awaiting cancellation.
	 * This does not track inactive request ids (that have been discard and/or completed). This is only valid while a
	 * request is in-fact in flight and during it's callback executions.
	 *
	 * @param Context The RequestContext of the request.	 
	 */
	UFUNCTION(BlueprintPure, Category="Beam")
	static bool IsRequestCancelled(const FBeamRequestContext& Context);

	/**
	 * @brief Gets the number of times this request failed.
	 * Can be used to change UI in order to allow users to cancel out of a popup after a certain amount of retries, for example.
	 * 
	 * @param Context The RequestContext of the request.
	 * @return The number of times this request has failed.
	 */
	UFUNCTION(BlueprintPure, Category="Beam")
	static int GetRequestFailureCount(const FBeamRequestContext& Context);
};
