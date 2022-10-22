

#pragma once

#include "CoreMinimal.h"
#include "BeamBackend/BeamBackend.h"

#include "Push/BasicPushPostRegisterRequest.h"
#include "Push/PostSendRequest.h"

#include "BeamPushApi.generated.h"


/**
 * Subsystem containing request calls for the Push service.
 */
UCLASS(BlueprintType)
class BEAMABLECORE_API UBeamPushApi : public UEngineSubsystem
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
	 * @brief Private implementation for requests that require authentication that all overloaded BP UFunctions call.	  
	 */
	void BP_PostRegisterImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, const FBeamAuthToken& AuthToken, FBeamConnectivity& ConnectivityStatus, UBasicPushPostRegisterRequest* RequestData,
	                  const FOnBasicPushPostRegisterSuccess& OnSuccess, const FOnBasicPushPostRegisterError& OnError, const FOnBasicPushPostRegisterComplete& OnComplete, int64& OutRequestId) const;
	/**
	 * @brief Overload version for binding lambdas when in C++ land. Prefer the BP version whenever possible, this is here mostly for quick experimentation purposes.	 
	 */
	void CPP_PostRegisterImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, const FBeamAuthToken& AuthToken, FBeamConnectivity& ConnectivityStatus, UBasicPushPostRegisterRequest* RequestData,
	                   const FOnBasicPushPostRegisterFullResponse& Handler) const;
		
	/**
	 * @brief Private implementation for requests that require authentication that all overloaded BP UFunctions call.	  
	 */
	void BP_PostSendImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, const FBeamAuthToken& AuthToken, FBeamConnectivity& ConnectivityStatus, UPostSendRequest* RequestData,
	                  const FOnPostSendSuccess& OnSuccess, const FOnPostSendError& OnError, const FOnPostSendComplete& OnComplete, int64& OutRequestId) const;
	/**
	 * @brief Overload version for binding lambdas when in C++ land. Prefer the BP version whenever possible, this is here mostly for quick experimentation purposes.	 
	 */
	void CPP_PostSendImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, const FBeamAuthToken& AuthToken, FBeamConnectivity& ConnectivityStatus, UPostSendRequest* RequestData,
	                   const FOnPostSendFullResponse& Handler) const;

public:
	
	/** Used by a helper blueprint node so that you can easily chain requests in BP-land. */
	UFUNCTION(BlueprintPure, BlueprintInternalUseOnly)
	static UBeamPushApi* GetSelf() { return GEngine->GetEngineSubsystem<UBeamPushApi>(); }

	

	
	/**
	 * @brief Makes an authenticated request to the Post /basic/push/register endpoint of the Push Service.
	 *
	 * PREFER THE UFUNCTION OVERLOAD AS OPPOSED TO THIS. THIS MAINLY EXISTS TO ALLOW LAMBDA BINDING THE HANDLER.
	 * (Dynamic delegates do not allow for that so... we autogen this one to make experimenting in CPP a bit faster).
	 * 
	 * @param UserSlot The Authenticated User Slot that is making this request.
	 * @param Request The Request UObject. All (de)serialized data the request data creates is tied to the lifecycle of this object.
	 * @param Handler A callback that defines how to handle success, error and completion. 
	 */
	void CPP_PostRegister(const FUserSlot& UserSlot, UBasicPushPostRegisterRequest* Request, const FOnBasicPushPostRegisterFullResponse& Handler) const;

		
	/**
	 * @brief Makes an authenticated request to the Post /basic/push/send endpoint of the Push Service.
	 *
	 * PREFER THE UFUNCTION OVERLOAD AS OPPOSED TO THIS. THIS MAINLY EXISTS TO ALLOW LAMBDA BINDING THE HANDLER.
	 * (Dynamic delegates do not allow for that so... we autogen this one to make experimenting in CPP a bit faster).
	 * 
	 * @param UserSlot The Authenticated User Slot that is making this request.
	 * @param Request The Request UObject. All (de)serialized data the request data creates is tied to the lifecycle of this object.
	 * @param Handler A callback that defines how to handle success, error and completion. 
	 */
	void CPP_PostSend(const FUserSlot& UserSlot, UPostSendRequest* Request, const FOnPostSendFullResponse& Handler) const;


	

	
	/**
	 * @brief Makes an authenticated request to the Post /basic/push/register endpoint of the Push Service.
	 *
	 * @param UserSlot The authenticated UserSlot with the user making the request. 
	 * @param Request The Request UObject. All (de)serialized data the request data creates is tied to the lifecycle of this object.
	 * @param OnSuccess What to do if the requests receives a successful response.
	 * @param OnError What to do if the request receives an error response.
	 * @param OnComplete What to after either OnSuccess or OnError have finished executing.
	 * @param OutRequestId The Request Id -- used to query information about the request or to cancel it while it's in flight. 
	 */
	UFUNCTION(BlueprintCallable, Category="Beam|APIs|Push", meta=(AutoCreateRefTerm="UserSlot,OnSuccess,OnError,OnComplete"))
	void PostRegister(const FUserSlot& UserSlot, UBasicPushPostRegisterRequest* Request, const FOnBasicPushPostRegisterSuccess& OnSuccess, const FOnBasicPushPostRegisterError& OnError, const FOnBasicPushPostRegisterComplete& OnComplete, int64& OutRequestId);

		
	/**
	 * @brief Makes an authenticated request to the Post /basic/push/send endpoint of the Push Service.
	 *
	 * @param UserSlot The authenticated UserSlot with the user making the request. 
	 * @param Request The Request UObject. All (de)serialized data the request data creates is tied to the lifecycle of this object.
	 * @param OnSuccess What to do if the requests receives a successful response.
	 * @param OnError What to do if the request receives an error response.
	 * @param OnComplete What to after either OnSuccess or OnError have finished executing.
	 * @param OutRequestId The Request Id -- used to query information about the request or to cancel it while it's in flight. 
	 */
	UFUNCTION(BlueprintCallable, Category="Beam|APIs|Push", meta=(AutoCreateRefTerm="UserSlot,OnSuccess,OnError,OnComplete"))
	void PostSend(const FUserSlot& UserSlot, UPostSendRequest* Request, const FOnPostSendSuccess& OnSuccess, const FOnPostSendError& OnError, const FOnPostSendComplete& OnComplete, int64& OutRequestId);
	
};
