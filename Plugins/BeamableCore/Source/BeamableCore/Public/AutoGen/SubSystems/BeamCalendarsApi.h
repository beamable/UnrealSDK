

#pragma once

#include "CoreMinimal.h"
#include "BeamBackend/BeamBackend.h"

#include "Calendars/ObjectCalendarsPostClaimRequest.h"
#include "Calendars/GetCalendarsRequest.h"

#include "BeamCalendarsApi.generated.h"


/**
 * Subsystem containing request calls for the Calendars service.
 */
UCLASS(NotBlueprintType)
class BEAMABLECORE_API UBeamCalendarsApi : public UEngineSubsystem
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
	void BP_PostClaimImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, FBeamConnectivity& ConnectivityStatus, UObjectCalendarsPostClaimRequest* RequestData,
	                                const FOnObjectCalendarsPostClaimSuccess& OnSuccess, const FOnObjectCalendarsPostClaimError& OnError, const FOnObjectCalendarsPostClaimComplete& OnComplete,
	                                int64& OutRequestId) const;
	/**
	 * @brief Overload version for binding lambdas when in C++ land. Prefer the BP version whenever possible, this is here mostly for quick experimentation purposes.	 
	 */
	void CPP_PostClaimImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, FBeamConnectivity& ConnectivityStatus, UObjectCalendarsPostClaimRequest* RequestData,
	                                 const FOnObjectCalendarsPostClaimFullResponse& Handler) const;

		
	/**
	 * @brief Private implementation that all overloaded BP UFunctions call.	  
	 */
	void BP_GetCalendarsImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, FBeamConnectivity& ConnectivityStatus, UGetCalendarsRequest* RequestData,
	                                const FOnGetCalendarsSuccess& OnSuccess, const FOnGetCalendarsError& OnError, const FOnGetCalendarsComplete& OnComplete,
	                                int64& OutRequestId) const;
	/**
	 * @brief Overload version for binding lambdas when in C++ land. Prefer the BP version whenever possible, this is here mostly for quick experimentation purposes.	 
	 */
	void CPP_GetCalendarsImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, FBeamConnectivity& ConnectivityStatus, UGetCalendarsRequest* RequestData,
	                                 const FOnGetCalendarsFullResponse& Handler) const;


	

public:
	
	/** Used by a helper blueprint node so that you can easily chain requests in BP-land. */
	UFUNCTION(BlueprintPure, BlueprintInternalUseOnly)
	static UBeamCalendarsApi* GetSelf() { return GEngine->GetEngineSubsystem<UBeamCalendarsApi>(); }

	
	/**
	 * @brief Makes a request to the Post /object/calendars/{objectId}/claim endpoint of the Calendars Service.
	 *
	 * PREFER THE UFUNCTION OVERLOAD AS OPPOSED TO THIS. THIS MAINLY EXISTS TO ALLOW LAMBDA BINDING THE HANDLER.
	 * (Dynamic delegates do not allow for that so... we autogen this one to make experimenting in CPP a bit faster and for whenever you need to capture variables).
	 * 
	 * @param Request The Request UObject. All (de)serialized data the request data creates is tied to the lifecycle of this object.
	 * @param Handler A callback that defines how to handle success, error and completion. 
	 */
	void CPP_PostClaim(UObjectCalendarsPostClaimRequest* Request, const FOnObjectCalendarsPostClaimFullResponse& Handler) const;

		
	/**
	 * @brief Makes a request to the Get /object/calendars/{objectId}/ endpoint of the Calendars Service.
	 *
	 * PREFER THE UFUNCTION OVERLOAD AS OPPOSED TO THIS. THIS MAINLY EXISTS TO ALLOW LAMBDA BINDING THE HANDLER.
	 * (Dynamic delegates do not allow for that so... we autogen this one to make experimenting in CPP a bit faster and for whenever you need to capture variables).
	 * 
	 * @param Request The Request UObject. All (de)serialized data the request data creates is tied to the lifecycle of this object.
	 * @param Handler A callback that defines how to handle success, error and completion. 
	 */
	void CPP_GetCalendars(UGetCalendarsRequest* Request, const FOnGetCalendarsFullResponse& Handler) const;


	

	
	/**
	 * @brief Makes a request to the Post /object/calendars/{objectId}/claim endpoint of the Calendars Service.
	 *
	 * @param Request The Request UObject. All (de)serialized data the request data creates is tied to the lifecycle of this object.
	 * @param OnSuccess What to do if the requests receives a successful response.
	 * @param OnError What to do if the request receives an error response.
	 * @param OnComplete What to after either OnSuccess or OnError have finished executing.
	 * @param OutRequestContext The Request Context associated with this request -- used to query information about the request or to cancel it while it's in flight. 
	 */
	UFUNCTION(BlueprintCallable, BlueprintInternalUseOnly, Category="Beam|Backend|Calendars", meta=(AutoCreateRefTerm="OnSuccess,OnError,OnComplete", BeamFlowStart))
	void PostClaim(UObjectCalendarsPostClaimRequest* Request, const FOnObjectCalendarsPostClaimSuccess& OnSuccess, const FOnObjectCalendarsPostClaimError& OnError, const FOnObjectCalendarsPostClaimComplete& OnComplete, FBeamRequestContext& OutRequestContext);

		
	/**
	 * @brief Makes a request to the Get /object/calendars/{objectId}/ endpoint of the Calendars Service.
	 *
	 * @param Request The Request UObject. All (de)serialized data the request data creates is tied to the lifecycle of this object.
	 * @param OnSuccess What to do if the requests receives a successful response.
	 * @param OnError What to do if the request receives an error response.
	 * @param OnComplete What to after either OnSuccess or OnError have finished executing.
	 * @param OutRequestContext The Request Context associated with this request -- used to query information about the request or to cancel it while it's in flight. 
	 */
	UFUNCTION(BlueprintCallable, BlueprintInternalUseOnly, Category="Beam|Backend|Calendars", meta=(AutoCreateRefTerm="OnSuccess,OnError,OnComplete", BeamFlowStart))
	void GetCalendars(UGetCalendarsRequest* Request, const FOnGetCalendarsSuccess& OnSuccess, const FOnGetCalendarsError& OnError, const FOnGetCalendarsComplete& OnComplete, FBeamRequestContext& OutRequestContext);


		

	
	/**
	 * @brief Makes a request to the Post /object/calendars/{objectId}/claim endpoint of the Calendars Service.
	 *	 
	 * @param RetryConfig The retry config for this specific request. 
	 * @param Request The Request UObject. All (de)serialized data the request data creates is tied to the lifecycle of this object.
	 * @param OnSuccess What to do if the requests receives a successful response.
	 * @param OnError What to do if the request receives an error response.
	 * @param OnComplete What to after either OnSuccess or OnError have finished executing.
	 * @param OutRequestContext The Request Context -- used to query information about the request or to cancel it while it's in flight. 
	 */
	UFUNCTION(BlueprintCallable, BlueprintInternalUseOnly, Category="Beam|Backend|Calendars", meta=(AutoCreateRefTerm="OnSuccess,OnError,OnComplete", BeamFlowStart))
	void PostClaimWithRetry(const FBeamRetryConfig& RetryConfig, UObjectCalendarsPostClaimRequest* Request, const FOnObjectCalendarsPostClaimSuccess& OnSuccess, const FOnObjectCalendarsPostClaimError& OnError, const FOnObjectCalendarsPostClaimComplete& OnComplete, FBeamRequestContext& OutRequestContext);
		
	/**
	 * @brief Makes a request to the Get /object/calendars/{objectId}/ endpoint of the Calendars Service.
	 *	 
	 * @param RetryConfig The retry config for this specific request. 
	 * @param Request The Request UObject. All (de)serialized data the request data creates is tied to the lifecycle of this object.
	 * @param OnSuccess What to do if the requests receives a successful response.
	 * @param OnError What to do if the request receives an error response.
	 * @param OnComplete What to after either OnSuccess or OnError have finished executing.
	 * @param OutRequestContext The Request Context -- used to query information about the request or to cancel it while it's in flight. 
	 */
	UFUNCTION(BlueprintCallable, BlueprintInternalUseOnly, Category="Beam|Backend|Calendars", meta=(AutoCreateRefTerm="OnSuccess,OnError,OnComplete", BeamFlowStart))
	void GetCalendarsWithRetry(const FBeamRetryConfig& RetryConfig, UGetCalendarsRequest* Request, const FOnGetCalendarsSuccess& OnSuccess, const FOnGetCalendarsError& OnError, const FOnGetCalendarsComplete& OnComplete, FBeamRequestContext& OutRequestContext);

	
};
