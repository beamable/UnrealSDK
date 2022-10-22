

#pragma once

#include "CoreMinimal.h"
#include "BeamBackend/BeamBackend.h"

#include "Auth/GetTokenRequest.h"
#include "Auth/AuthenticateRequest.h"
#include "Auth/GetTokenListRequest.h"
#include "Auth/PutTokenRevokeRequest.h"

#include "BeamAuthApi.generated.h"


/**
 * Subsystem containing request calls for the Auth service.
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
	 * @brief Private implementation that all overloaded BP UFunctions call.	  
	 */
	void BP_GetTokenImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, FBeamConnectivity& ConnectivityStatus, UGetTokenRequest* RequestData,
	                                const FOnGetTokenSuccess& OnSuccess, const FOnGetTokenError& OnError, const FOnGetTokenComplete& OnComplete,
	                                int64& OutRequestId) const;
	/**
	 * @brief Overload version for binding lambdas when in C++ land. Prefer the BP version whenever possible, this is here mostly for quick experimentation purposes.	 
	 */
	void CPP_GetTokenImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, FBeamConnectivity& ConnectivityStatus, UGetTokenRequest* RequestData,
	                                 const FOnGetTokenFullResponse& Handler) const;

		
	/**
	 * @brief Private implementation that all overloaded BP UFunctions call.	  
	 */
	void BP_AuthenticateImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, FBeamConnectivity& ConnectivityStatus, UAuthenticateRequest* RequestData,
	                                const FOnAuthenticateSuccess& OnSuccess, const FOnAuthenticateError& OnError, const FOnAuthenticateComplete& OnComplete,
	                                int64& OutRequestId) const;
	/**
	 * @brief Overload version for binding lambdas when in C++ land. Prefer the BP version whenever possible, this is here mostly for quick experimentation purposes.	 
	 */
	void CPP_AuthenticateImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, FBeamConnectivity& ConnectivityStatus, UAuthenticateRequest* RequestData,
	                                 const FOnAuthenticateFullResponse& Handler) const;


	
	/**
	 * @brief Private implementation for requests that require authentication that all overloaded BP UFunctions call.	  
	 */
	void BP_GetTokenListImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, const FBeamAuthToken& AuthToken, FBeamConnectivity& ConnectivityStatus, UGetTokenListRequest* RequestData,
	                  const FOnGetTokenListSuccess& OnSuccess, const FOnGetTokenListError& OnError, const FOnGetTokenListComplete& OnComplete, int64& OutRequestId) const;
	/**
	 * @brief Overload version for binding lambdas when in C++ land. Prefer the BP version whenever possible, this is here mostly for quick experimentation purposes.	 
	 */
	void CPP_GetTokenListImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, const FBeamAuthToken& AuthToken, FBeamConnectivity& ConnectivityStatus, UGetTokenListRequest* RequestData,
	                   const FOnGetTokenListFullResponse& Handler) const;
		
	/**
	 * @brief Private implementation for requests that require authentication that all overloaded BP UFunctions call.	  
	 */
	void BP_PutTokenRevokeImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, const FBeamAuthToken& AuthToken, FBeamConnectivity& ConnectivityStatus, UPutTokenRevokeRequest* RequestData,
	                  const FOnPutTokenRevokeSuccess& OnSuccess, const FOnPutTokenRevokeError& OnError, const FOnPutTokenRevokeComplete& OnComplete, int64& OutRequestId) const;
	/**
	 * @brief Overload version for binding lambdas when in C++ land. Prefer the BP version whenever possible, this is here mostly for quick experimentation purposes.	 
	 */
	void CPP_PutTokenRevokeImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, const FBeamAuthToken& AuthToken, FBeamConnectivity& ConnectivityStatus, UPutTokenRevokeRequest* RequestData,
	                   const FOnPutTokenRevokeFullResponse& Handler) const;

public:
	
	/** Used by a helper blueprint node so that you can easily chain requests in BP-land. */
	UFUNCTION(BlueprintPure, BlueprintInternalUseOnly)
	static UBeamAuthApi* GetSelf() { return GEngine->GetEngineSubsystem<UBeamAuthApi>(); }

	
	/**
	 * @brief Makes a request to the Get /basic/auth/token endpoint of the Auth Service.
	 *
	 * PREFER THE UFUNCTION OVERLOAD AS OPPOSED TO THIS. THIS MAINLY EXISTS TO ALLOW LAMBDA BINDING THE HANDLER.
	 * (Dynamic delegates do not allow for that so... we autogen this one to make experimenting in CPP a bit faster and for whenever you need to capture variables).
	 * 
	 * @param Request The Request UObject. All (de)serialized data the request data creates is tied to the lifecycle of this object.
	 * @param Handler A callback that defines how to handle success, error and completion. 
	 */
	void CPP_GetToken(UGetTokenRequest* Request, const FOnGetTokenFullResponse& Handler) const;

		
	/**
	 * @brief Makes a request to the Post /basic/auth/token endpoint of the Auth Service.
	 *
	 * PREFER THE UFUNCTION OVERLOAD AS OPPOSED TO THIS. THIS MAINLY EXISTS TO ALLOW LAMBDA BINDING THE HANDLER.
	 * (Dynamic delegates do not allow for that so... we autogen this one to make experimenting in CPP a bit faster and for whenever you need to capture variables).
	 * 
	 * @param Request The Request UObject. All (de)serialized data the request data creates is tied to the lifecycle of this object.
	 * @param Handler A callback that defines how to handle success, error and completion. 
	 */
	void CPP_Authenticate(UAuthenticateRequest* Request, const FOnAuthenticateFullResponse& Handler) const;


	
	/**
	 * @brief Makes an authenticated request to the Get /basic/auth/token/list endpoint of the Auth Service.
	 *
	 * PREFER THE UFUNCTION OVERLOAD AS OPPOSED TO THIS. THIS MAINLY EXISTS TO ALLOW LAMBDA BINDING THE HANDLER.
	 * (Dynamic delegates do not allow for that so... we autogen this one to make experimenting in CPP a bit faster).
	 * 
	 * @param UserSlot The Authenticated User Slot that is making this request.
	 * @param Request The Request UObject. All (de)serialized data the request data creates is tied to the lifecycle of this object.
	 * @param Handler A callback that defines how to handle success, error and completion. 
	 */
	void CPP_GetTokenList(const FUserSlot& UserSlot, UGetTokenListRequest* Request, const FOnGetTokenListFullResponse& Handler) const;

		
	/**
	 * @brief Makes an authenticated request to the Put /basic/auth/token/revoke endpoint of the Auth Service.
	 *
	 * PREFER THE UFUNCTION OVERLOAD AS OPPOSED TO THIS. THIS MAINLY EXISTS TO ALLOW LAMBDA BINDING THE HANDLER.
	 * (Dynamic delegates do not allow for that so... we autogen this one to make experimenting in CPP a bit faster).
	 * 
	 * @param UserSlot The Authenticated User Slot that is making this request.
	 * @param Request The Request UObject. All (de)serialized data the request data creates is tied to the lifecycle of this object.
	 * @param Handler A callback that defines how to handle success, error and completion. 
	 */
	void CPP_PutTokenRevoke(const FUserSlot& UserSlot, UPutTokenRevokeRequest* Request, const FOnPutTokenRevokeFullResponse& Handler) const;


	
	/**
	 * @brief Makes a request to the Get /basic/auth/token endpoint of the Auth Service.
	 *
	 * @param Request The Request UObject. All (de)serialized data the request data creates is tied to the lifecycle of this object.
	 * @param OnSuccess What to do if the requests receives a successful response.
	 * @param OnError What to do if the request receives an error response.
	 * @param OnComplete What to after either OnSuccess or OnError have finished executing.
	 * @param OutRequestId The Request Id -- used to query information about the request or to cancel it while it's in flight. 
	 */
	UFUNCTION(BlueprintCallable, Category="Beam|APIs|Auth", meta=(AutoCreateRefTerm="OnSuccess,OnError,OnComplete"))
	void GetToken(UGetTokenRequest* Request, const FOnGetTokenSuccess& OnSuccess, const FOnGetTokenError& OnError, const FOnGetTokenComplete& OnComplete,
								 int64& OutRequestId);

		
	/**
	 * @brief Makes a request to the Post /basic/auth/token endpoint of the Auth Service.
	 *
	 * @param Request The Request UObject. All (de)serialized data the request data creates is tied to the lifecycle of this object.
	 * @param OnSuccess What to do if the requests receives a successful response.
	 * @param OnError What to do if the request receives an error response.
	 * @param OnComplete What to after either OnSuccess or OnError have finished executing.
	 * @param OutRequestId The Request Id -- used to query information about the request or to cancel it while it's in flight. 
	 */
	UFUNCTION(BlueprintCallable, Category="Beam|APIs|Auth", meta=(AutoCreateRefTerm="OnSuccess,OnError,OnComplete"))
	void Authenticate(UAuthenticateRequest* Request, const FOnAuthenticateSuccess& OnSuccess, const FOnAuthenticateError& OnError, const FOnAuthenticateComplete& OnComplete,
								 int64& OutRequestId);


	
	/**
	 * @brief Makes an authenticated request to the Get /basic/auth/token/list endpoint of the Auth Service.
	 *
	 * @param UserSlot The authenticated UserSlot with the user making the request. 
	 * @param Request The Request UObject. All (de)serialized data the request data creates is tied to the lifecycle of this object.
	 * @param OnSuccess What to do if the requests receives a successful response.
	 * @param OnError What to do if the request receives an error response.
	 * @param OnComplete What to after either OnSuccess or OnError have finished executing.
	 * @param OutRequestId The Request Id -- used to query information about the request or to cancel it while it's in flight. 
	 */
	UFUNCTION(BlueprintCallable, Category="Beam|APIs|Auth", meta=(AutoCreateRefTerm="UserSlot,OnSuccess,OnError,OnComplete"))
	void GetTokenList(const FUserSlot& UserSlot, UGetTokenListRequest* Request, const FOnGetTokenListSuccess& OnSuccess, const FOnGetTokenListError& OnError, const FOnGetTokenListComplete& OnComplete, int64& OutRequestId);

		
	/**
	 * @brief Makes an authenticated request to the Put /basic/auth/token/revoke endpoint of the Auth Service.
	 *
	 * @param UserSlot The authenticated UserSlot with the user making the request. 
	 * @param Request The Request UObject. All (de)serialized data the request data creates is tied to the lifecycle of this object.
	 * @param OnSuccess What to do if the requests receives a successful response.
	 * @param OnError What to do if the request receives an error response.
	 * @param OnComplete What to after either OnSuccess or OnError have finished executing.
	 * @param OutRequestId The Request Id -- used to query information about the request or to cancel it while it's in flight. 
	 */
	UFUNCTION(BlueprintCallable, Category="Beam|APIs|Auth", meta=(AutoCreateRefTerm="UserSlot,OnSuccess,OnError,OnComplete"))
	void PutTokenRevoke(const FUserSlot& UserSlot, UPutTokenRevokeRequest* Request, const FOnPutTokenRevokeSuccess& OnSuccess, const FOnPutTokenRevokeError& OnError, const FOnPutTokenRevokeComplete& OnComplete, int64& OutRequestId);
	
};
