

#pragma once

#include "CoreMinimal.h"
#include "BeamBackend/BeamBackend.h"
#include "BeamBackend/ResponseCache/BeamResponseCache.h"
#include "RequestTracker/BeamRequestTracker.h"

#include "BeamableUnrealMicroserviceClients/Public/AutoGen/SubSystems/BeamballMs/BeamballMsCreateMatchResultRequest.h"
#include "BeamBackend/BeamMicroserviceClientSubsystem.h"

#include "BeamBeamballMsApi.generated.h"


/**
 * Subsystem containing request calls for the BeamballMs service.
 */
UCLASS(NotBlueprintType)
class BEAMABLEUNREALMICROSERVICECLIENTS_API UBeamBeamballMsApi : public UBeamMicroserviceClientSubsystem
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

	
	/**
	 * @brief Private implementation that all overloaded BP UFunctions call.	  
	 */
	void BP_CreateMatchResultImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, UBeamballMsCreateMatchResultRequest* RequestData,
	                                const FOnBeamballMsCreateMatchResultSuccess& OnSuccess, const FOnBeamballMsCreateMatchResultError& OnError, const FOnBeamballMsCreateMatchResultComplete& OnComplete,
	                                int64& OutRequestId, FBeamOperationHandle OpHandle = FBeamOperationHandle(), const UObject* CallingContext = nullptr) const;
	/**
	 * @brief Overload version for binding lambdas when in C++ land. Prefer the BP version whenever possible, this is here mostly for quick experimentation purposes.	 
	 */
	void CPP_CreateMatchResultImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, UBeamballMsCreateMatchResultRequest* RequestData,
	                                 const FOnBeamballMsCreateMatchResultFullResponse& Handler, int64& OutRequestId, FBeamOperationHandle OpHandle = FBeamOperationHandle(), const UObject* CallingContext = nullptr) const;


	

public:
	
	/** Used by a helper blueprint node so that you can easily chain requests in BP-land. */
	UFUNCTION(BlueprintPure, BlueprintInternalUseOnly)
	static UBeamBeamballMsApi* GetSelf() { return GEngine->GetEngineSubsystem<UBeamBeamballMsApi>(); }

	
	/**
	 * @brief Makes a request to the Post /CreateMatchResult endpoint of the BeamballMs Service.
	 *
	 * PREFER THE UFUNCTION OVERLOAD AS OPPOSED TO THIS. THIS MAINLY EXISTS TO ALLOW LAMBDA BINDING THE HANDLER.
	 * (Dynamic delegates do not allow for that so... we autogen this one to make experimenting in CPP a bit faster and for whenever you need to capture variables).
	 * 
	 * @param Request The Request UObject. All (de)serialized data the request data creates is tied to the lifecycle of this object.
	 * @param Handler A callback that defines how to handle success, error and completion.
     * @param OutRequestContext The Request Context associated with this request -- used to query information about the request or to cancel it while it's in flight.
	 * @param OpHandle When made as part of an Operation, you can pass this in and it'll register the request with the operation automatically.
	 * @param CallingContext A UObject managed by the UWorld that's making the request. Used to support multiple PIEs (see UBeamUserSlot::GetNamespacedSlotId) and read-only RequestCaches. 
	 */
	void CPP_CreateMatchResult(UBeamballMsCreateMatchResultRequest* Request, const FOnBeamballMsCreateMatchResultFullResponse& Handler, FBeamRequestContext& OutRequestContext, FBeamOperationHandle OpHandle = FBeamOperationHandle(), const UObject* CallingContext = nullptr) const;


	

	
	/**
	 * @brief Makes a request to the Post /CreateMatchResult endpoint of the BeamballMs Service.
	 *
	 * @param Request The Request UObject. All (de)serialized data the request data creates is tied to the lifecycle of this object.
	 * @param OnSuccess What to do if the requests receives a successful response.
	 * @param OnError What to do if the request receives an error response.
	 * @param OnComplete What to after either OnSuccess or OnError have finished executing.
	 * @param OutRequestContext The Request Context associated with this request -- used to query information about the request or to cancel it while it's in flight.
	 * @param CallingContext A UObject managed by the UWorld that's making the request. Used to support multiple PIEs (see UBeamUserSlot::GetNamespacedSlotId) and read-only RequestCaches. 
	 */
	UFUNCTION(BlueprintCallable, BlueprintInternalUseOnly, Category="Beam|BeamballMs|Utils|Make/Break", meta=(DefaultToSelf="CallingContext", AdvancedDisplay="OpHandle,CallingContext", AutoCreateRefTerm="OnSuccess,OnError,OnComplete,OpHandle", BeamFlowFunction))
	void CreateMatchResult(UBeamballMsCreateMatchResultRequest* Request, const FOnBeamballMsCreateMatchResultSuccess& OnSuccess, const FOnBeamballMsCreateMatchResultError& OnError, const FOnBeamballMsCreateMatchResultComplete& OnComplete, FBeamRequestContext& OutRequestContext, FBeamOperationHandle OpHandle = FBeamOperationHandle(), const UObject* CallingContext = nullptr);


	
};
