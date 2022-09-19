// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BeamBackend.h"
#include "BeamAuthApiModels.h"

/** Injection - Includes **/

#include "BeamAuthApi.generated.h"


/**
 * 
 */
UCLASS(BlueprintType)
class BEAMABLECORE_API UBeamAuthApi : public UEngineSubsystem
{
private:
	GENERATED_BODY()
	/** @brief Initializes the auto-increment Id and binds the ExecuteRequestDelegate to DefaultExecuteRequestImpl  */
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;

	/** Cleans up the system.  */
	virtual void Deinitialize() override;

	UPROPERTY()
	UBeamBackend* Backend;

	/**
	 * @brief Overload version for use with blueprints that take all parameters.	  
	 */
	void BP_RegisterCustomerRequest(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, const FRegisterCustomerRequest& RequestData, FBeamConnectivity& ConnectivityStatus,
	                                const FOnRegisterCustomerSuccess& OnSuccess, const FOnRegisterCustomerError& OnError, const FOnRegisterCustomerComplete& OnComplete,
	                                int64& OutRequestId) const;

	void BP_MeRequest(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, const FBeamAuthToken& AuthToken, const FMeRequest& RequestData, FBeamConnectivity& ConnectivityStatus,
	                  const FOnMeSuccess& OnSuccess, const FOnMeError& OnError, const FOnMeComplete& OnComplete, int64& OutRequestId) const;


	/**
	 * @brief 
	 * @param TargetRealm The realm we are making this request into.
	 * @param RetryConfig The Retry config for this request.	 
	 * @param ConnectivityStatus TODO	 
	 * @param RequestData The RegisterCustomerRequest data so that we can make the request.
	 * @param Handler The success/error handler for this request.	 
	 */
	void CPP_RegisterCustomerRequest(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, FBeamConnectivity& ConnectivityStatus,
	                                 const FRegisterCustomerRequest& RequestData,
	                                 const FOnRegisterCustomerFullResponse& Handler) const;

	void CPP_MeRequest(const FBeamRealmHandle& TargetRealm,
	                   const FBeamRetryConfig& RetryConfig,
	                   const FBeamAuthToken& AuthToken,
	                   FBeamConnectivity& ConnectivityStatus,
	                   const FMeRequest& RequestData,
	                   const FOnMeFullResponse& Handler) const;

public:
	UFUNCTION(BlueprintPure, BlueprintInternalUseOnly)
	static UBeamAuthApi* GetSelf() { return GEngine->GetEngineSubsystem<UBeamAuthApi>(); }


	/**
	 * @brief Registers a new customer with Beamable.
	 *
	 * PREFER THE UFUNCTION OVERLOAD AS OPPOSED TO THIS. THIS MAINLY EXISTS TO ALLOW LAMBDA BINDING THE HANDLER.
	 * (Dynamic delegates do not allow for that so... we autogen this one to make experimenting in CPP a bit faster).
	 * 
	 * @param Request The Customer Request. 
	 * @param Handler A callback that defines how to handle success, error and completion. 
	 */
	void CPP_RegisterCustomerRequest(const FRegisterCustomerRequest& Request, const FOnRegisterCustomerFullResponse& Handler) const;


	/**	 
	 * \copydoc CPP_RegisterCustomerRequest	  
	 */
	UFUNCTION(BlueprintCallable, Category="Beam|APIs|Auth", meta=(AutoCreateRefTerm="OnSuccess,OnError,OnComplete"))
	void RegisterCustomerRequest(const FRegisterCustomerRequest& Request,
	                             const FOnRegisterCustomerSuccess& OnSuccess,
	                             const FOnRegisterCustomerError& OnError,
	                             const FOnRegisterCustomerComplete& OnComplete,
	                             int64& OutRequestId);


	/**
	 * @brief Register a customer using the given request context.
	 * 
	 * @param RequestContext The BeamRequestContext to use to send out the request.
	 * @param RequestData The RegisterCustomerRequest data so that we can make the request.
	 * @param OnSuccess What to do if we successfully make the request.
	 * @param OnError What to do if we fail the request.
	 * @param OnComplete What to do after either OnSuccess or OnError have run.
	 * @param OutRequestId The Request Id -- used to query information about the request or to cancel it. 
	 */
	UFUNCTION(BlueprintCallable, Category="Beam|APIs|Auth", meta=(AutoCreateRefTerm="OnSuccess,OnError,OnComplete"))
	void RegisterCustomerWithContext(const FBeamRequestContext& RequestContext, const FRegisterCustomerRequest& RequestData,
	                                 const FOnRegisterCustomerSuccess& OnSuccess, const FOnRegisterCustomerError& OnError, const FOnRegisterCustomerComplete& OnComplete,
	                                 int64& OutRequestId);


	UFUNCTION(BlueprintCallable, Category="Beam|APIs|Auth", meta=(AutoCreateRefTerm="OnSuccess,OnError,OnComplete"))
	void MeRequest(const FString& UserSlotId, const FMeRequest& RequestData,
	               const FOnMeSuccess& OnSuccess, const FOnMeError& OnError, const FOnMeComplete& OnComplete, int64& OutRequestId);

	/**
	 * @brief Registers a new customer with Beamable.
	 *
	 * PREFER THE UFUNCTION OVERLOAD AS OPPOSED TO THIS. THIS MAINLY EXISTS TO ALLOW LAMBDA BINDING THE HANDLER.
	 * (Dynamic delegates do not allow for that so... we autogen this one to make experimenting in CPP a bit faster).
	 * 
	 * @param UserSlotId The Authenticated User Slot that is making this request.
	 * @param Request The Request Data. 
	 * @param Handler A callback that defines how to handle success, error and completion. 
	 */
	void CPP_MeRequest(const FString& UserSlotId, const FMeRequest& Request, const FOnMeFullResponse& Handler) const;

	/**
	 * @brief 
	 * @param UserSlotId The authenticated UserSlot with the user making the request.
	 * @param RetryConfig The retry config to make this request with.
	 * @param RequestData The FMeRequest data so we can make the request
	 * @param OnSuccess What to do if we successfully make the request.
	 * @param OnError What to do if we fail the request
	 * @param OnComplete What to do after either OnSuccess or OnError have run. 
	 * @param OutRequestId The Request Id -- used to query information about the request or to cancel it.
	 */
	UFUNCTION(BlueprintCallable, Category="Beam|APIs|Auth", meta=(AutoCreateRefTerm="OnSuccess,OnError,OnComplete"))
	void MeRequestWithRetry(const FString& UserSlotId, const FBeamRetryConfig RetryConfig, const FMeRequest& RequestData,
	                        const FOnMeSuccess& OnSuccess, const FOnMeError& OnError, const FOnMeComplete& OnComplete, int64& OutRequestId);
};
