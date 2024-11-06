#pragma once

#include "CoreMinimal.h"
#include "BeamBackend/BeamBackend.h"
#include "BeamBackend/ResponseCache/BeamResponseCache.h"
#include "RequestTracker/BeamRequestTracker.h"

#include "BeamGenericApi.generated.h"


/**
 * Subsystem containing request calls for the Auth service.
 */
UCLASS(NotBlueprintType)
class BEAMABLECORE_API UBeamGenericApi : public UEngineSubsystem
{
private:
	GENERATED_BODY()
	/** @brief Initializes the auto-increment Id and binds the ExecuteRequestDelegate to DefaultExecuteRequestImpl  */
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;

	/** Cleans up the system.  */
	virtual void Deinitialize() override;

	UPROPERTY()
	UBeamBackend* Backend;

	UPROPERTY()
	UBeamRequestTracker* RequestTracker;

	UPROPERTY()
	UBeamResponseCache* ResponseCache;

public:
	
	/**
	 * @brief Creates and executes a request that does not target a Beamable server. This request is automatically retried based on the given RetryConfig.
	 * This is basically a way to integrate calls to non-Beamable routes with Operations, Waits and our Retry System. 
	 * 
	 * @param RequestData An instance of the request type.
	 * @param Handler A callback to handle the full response of this request. To handle success/error/retry, read from the TBeamFullResponse data.	 	 	 
	 * @param OpHandle A handle to the operation that depends on this request.
	 * @param CallingContext A UObject that defines a context for the caller. Used to support multiple PIE sessions and read-only request cache.
	 *
	 * @return The FBeamRequestContext for this request.
	 */
	FBeamRequestContext CPP_ExecuteNonBeamRequest(UGenericBeamRequest* RequestData, const FOnGenericBeamRequestFullResponse& Handler, const FBeamOperationHandle OpHandle, const UObject* CallingContext) const;
};
