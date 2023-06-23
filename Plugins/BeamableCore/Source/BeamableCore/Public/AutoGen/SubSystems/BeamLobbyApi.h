

#pragma once

#include "CoreMinimal.h"
#include "BeamBackend/BeamBackend.h"
#include "BeamBackend/ResponseCache/BeamResponseCache.h"
#include "RequestTracker/BeamRequestTracker.h"

#include "BeamableCore/Public/AutoGen/SubSystems/Lobby/GetLobbiesRequest.h"
#include "BeamableCore/Public/AutoGen/SubSystems/Lobby/PostLobbiesRequest.h"
#include "BeamableCore/Public/AutoGen/SubSystems/Lobby/GetLobbyRequest.h"
#include "BeamableCore/Public/AutoGen/SubSystems/Lobby/PutLobbyRequest.h"
#include "BeamableCore/Public/AutoGen/SubSystems/Lobby/DeleteLobbyRequest.h"
#include "BeamableCore/Public/AutoGen/SubSystems/Lobby/PutPasscodeRequest.h"
#include "BeamableCore/Public/AutoGen/SubSystems/Lobby/ApiLobbyPutMetadataRequest.h"
#include "BeamableCore/Public/AutoGen/SubSystems/Lobby/PutTagsRequest.h"
#include "BeamableCore/Public/AutoGen/SubSystems/Lobby/DeleteTagsRequest.h"

#include "BeamLobbyApi.generated.h"


/**
 * Subsystem containing request calls for the Lobby service.
 */
UCLASS(NotBlueprintType)
class BEAMABLECORE_API UBeamLobbyApi : public UEngineSubsystem
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
	 * @brief Private implementation for requests that require authentication that all overloaded BP UFunctions call.	  
	 */
	void BP_GetLobbiesImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, const FBeamAuthToken& AuthToken, FBeamConnectivity& ConnectivityStatus, UGetLobbiesRequest* RequestData,
	                  const FOnGetLobbiesSuccess& OnSuccess, const FOnGetLobbiesError& OnError, const FOnGetLobbiesComplete& OnComplete, 
					  int64& OutRequestId, FBeamOperationHandle OpHandle = FBeamOperationHandle(), const UObject* CallingContext = nullptr) const;
	/**
	 * @brief Overload version for binding lambdas when in C++ land. Prefer the BP version whenever possible, this is here mostly for quick experimentation purposes.	 
	 */
	void CPP_GetLobbiesImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, const FBeamAuthToken& AuthToken, FBeamConnectivity& ConnectivityStatus, UGetLobbiesRequest* RequestData,
	                   const FOnGetLobbiesFullResponse& Handler, int64& OutRequestId, FBeamOperationHandle OpHandle = FBeamOperationHandle(), const UObject* CallingContext = nullptr) const;
		
	/**
	 * @brief Private implementation for requests that require authentication that all overloaded BP UFunctions call.	  
	 */
	void BP_PostLobbiesImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, const FBeamAuthToken& AuthToken, FBeamConnectivity& ConnectivityStatus, UPostLobbiesRequest* RequestData,
	                  const FOnPostLobbiesSuccess& OnSuccess, const FOnPostLobbiesError& OnError, const FOnPostLobbiesComplete& OnComplete, 
					  int64& OutRequestId, FBeamOperationHandle OpHandle = FBeamOperationHandle(), const UObject* CallingContext = nullptr) const;
	/**
	 * @brief Overload version for binding lambdas when in C++ land. Prefer the BP version whenever possible, this is here mostly for quick experimentation purposes.	 
	 */
	void CPP_PostLobbiesImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, const FBeamAuthToken& AuthToken, FBeamConnectivity& ConnectivityStatus, UPostLobbiesRequest* RequestData,
	                   const FOnPostLobbiesFullResponse& Handler, int64& OutRequestId, FBeamOperationHandle OpHandle = FBeamOperationHandle(), const UObject* CallingContext = nullptr) const;
		
	/**
	 * @brief Private implementation for requests that require authentication that all overloaded BP UFunctions call.	  
	 */
	void BP_GetLobbyImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, const FBeamAuthToken& AuthToken, FBeamConnectivity& ConnectivityStatus, UGetLobbyRequest* RequestData,
	                  const FOnGetLobbySuccess& OnSuccess, const FOnGetLobbyError& OnError, const FOnGetLobbyComplete& OnComplete, 
					  int64& OutRequestId, FBeamOperationHandle OpHandle = FBeamOperationHandle(), const UObject* CallingContext = nullptr) const;
	/**
	 * @brief Overload version for binding lambdas when in C++ land. Prefer the BP version whenever possible, this is here mostly for quick experimentation purposes.	 
	 */
	void CPP_GetLobbyImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, const FBeamAuthToken& AuthToken, FBeamConnectivity& ConnectivityStatus, UGetLobbyRequest* RequestData,
	                   const FOnGetLobbyFullResponse& Handler, int64& OutRequestId, FBeamOperationHandle OpHandle = FBeamOperationHandle(), const UObject* CallingContext = nullptr) const;
		
	/**
	 * @brief Private implementation for requests that require authentication that all overloaded BP UFunctions call.	  
	 */
	void BP_PutLobbyImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, const FBeamAuthToken& AuthToken, FBeamConnectivity& ConnectivityStatus, UPutLobbyRequest* RequestData,
	                  const FOnPutLobbySuccess& OnSuccess, const FOnPutLobbyError& OnError, const FOnPutLobbyComplete& OnComplete, 
					  int64& OutRequestId, FBeamOperationHandle OpHandle = FBeamOperationHandle(), const UObject* CallingContext = nullptr) const;
	/**
	 * @brief Overload version for binding lambdas when in C++ land. Prefer the BP version whenever possible, this is here mostly for quick experimentation purposes.	 
	 */
	void CPP_PutLobbyImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, const FBeamAuthToken& AuthToken, FBeamConnectivity& ConnectivityStatus, UPutLobbyRequest* RequestData,
	                   const FOnPutLobbyFullResponse& Handler, int64& OutRequestId, FBeamOperationHandle OpHandle = FBeamOperationHandle(), const UObject* CallingContext = nullptr) const;
		
	/**
	 * @brief Private implementation for requests that require authentication that all overloaded BP UFunctions call.	  
	 */
	void BP_DeleteLobbyImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, const FBeamAuthToken& AuthToken, FBeamConnectivity& ConnectivityStatus, UDeleteLobbyRequest* RequestData,
	                  const FOnDeleteLobbySuccess& OnSuccess, const FOnDeleteLobbyError& OnError, const FOnDeleteLobbyComplete& OnComplete, 
					  int64& OutRequestId, FBeamOperationHandle OpHandle = FBeamOperationHandle(), const UObject* CallingContext = nullptr) const;
	/**
	 * @brief Overload version for binding lambdas when in C++ land. Prefer the BP version whenever possible, this is here mostly for quick experimentation purposes.	 
	 */
	void CPP_DeleteLobbyImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, const FBeamAuthToken& AuthToken, FBeamConnectivity& ConnectivityStatus, UDeleteLobbyRequest* RequestData,
	                   const FOnDeleteLobbyFullResponse& Handler, int64& OutRequestId, FBeamOperationHandle OpHandle = FBeamOperationHandle(), const UObject* CallingContext = nullptr) const;
		
	/**
	 * @brief Private implementation for requests that require authentication that all overloaded BP UFunctions call.	  
	 */
	void BP_PutPasscodeImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, const FBeamAuthToken& AuthToken, FBeamConnectivity& ConnectivityStatus, UPutPasscodeRequest* RequestData,
	                  const FOnPutPasscodeSuccess& OnSuccess, const FOnPutPasscodeError& OnError, const FOnPutPasscodeComplete& OnComplete, 
					  int64& OutRequestId, FBeamOperationHandle OpHandle = FBeamOperationHandle(), const UObject* CallingContext = nullptr) const;
	/**
	 * @brief Overload version for binding lambdas when in C++ land. Prefer the BP version whenever possible, this is here mostly for quick experimentation purposes.	 
	 */
	void CPP_PutPasscodeImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, const FBeamAuthToken& AuthToken, FBeamConnectivity& ConnectivityStatus, UPutPasscodeRequest* RequestData,
	                   const FOnPutPasscodeFullResponse& Handler, int64& OutRequestId, FBeamOperationHandle OpHandle = FBeamOperationHandle(), const UObject* CallingContext = nullptr) const;
		
	/**
	 * @brief Private implementation for requests that require authentication that all overloaded BP UFunctions call.	  
	 */
	void BP_PutMetadataImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, const FBeamAuthToken& AuthToken, FBeamConnectivity& ConnectivityStatus, UApiLobbyPutMetadataRequest* RequestData,
	                  const FOnApiLobbyPutMetadataSuccess& OnSuccess, const FOnApiLobbyPutMetadataError& OnError, const FOnApiLobbyPutMetadataComplete& OnComplete, 
					  int64& OutRequestId, FBeamOperationHandle OpHandle = FBeamOperationHandle(), const UObject* CallingContext = nullptr) const;
	/**
	 * @brief Overload version for binding lambdas when in C++ land. Prefer the BP version whenever possible, this is here mostly for quick experimentation purposes.	 
	 */
	void CPP_PutMetadataImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, const FBeamAuthToken& AuthToken, FBeamConnectivity& ConnectivityStatus, UApiLobbyPutMetadataRequest* RequestData,
	                   const FOnApiLobbyPutMetadataFullResponse& Handler, int64& OutRequestId, FBeamOperationHandle OpHandle = FBeamOperationHandle(), const UObject* CallingContext = nullptr) const;
		
	/**
	 * @brief Private implementation for requests that require authentication that all overloaded BP UFunctions call.	  
	 */
	void BP_PutTagsImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, const FBeamAuthToken& AuthToken, FBeamConnectivity& ConnectivityStatus, UPutTagsRequest* RequestData,
	                  const FOnPutTagsSuccess& OnSuccess, const FOnPutTagsError& OnError, const FOnPutTagsComplete& OnComplete, 
					  int64& OutRequestId, FBeamOperationHandle OpHandle = FBeamOperationHandle(), const UObject* CallingContext = nullptr) const;
	/**
	 * @brief Overload version for binding lambdas when in C++ land. Prefer the BP version whenever possible, this is here mostly for quick experimentation purposes.	 
	 */
	void CPP_PutTagsImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, const FBeamAuthToken& AuthToken, FBeamConnectivity& ConnectivityStatus, UPutTagsRequest* RequestData,
	                   const FOnPutTagsFullResponse& Handler, int64& OutRequestId, FBeamOperationHandle OpHandle = FBeamOperationHandle(), const UObject* CallingContext = nullptr) const;
		
	/**
	 * @brief Private implementation for requests that require authentication that all overloaded BP UFunctions call.	  
	 */
	void BP_DeleteTagsImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, const FBeamAuthToken& AuthToken, FBeamConnectivity& ConnectivityStatus, UDeleteTagsRequest* RequestData,
	                  const FOnDeleteTagsSuccess& OnSuccess, const FOnDeleteTagsError& OnError, const FOnDeleteTagsComplete& OnComplete, 
					  int64& OutRequestId, FBeamOperationHandle OpHandle = FBeamOperationHandle(), const UObject* CallingContext = nullptr) const;
	/**
	 * @brief Overload version for binding lambdas when in C++ land. Prefer the BP version whenever possible, this is here mostly for quick experimentation purposes.	 
	 */
	void CPP_DeleteTagsImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, const FBeamAuthToken& AuthToken, FBeamConnectivity& ConnectivityStatus, UDeleteTagsRequest* RequestData,
	                   const FOnDeleteTagsFullResponse& Handler, int64& OutRequestId, FBeamOperationHandle OpHandle = FBeamOperationHandle(), const UObject* CallingContext = nullptr) const;

public:
	
	/** Used by a helper blueprint node so that you can easily chain requests in BP-land. */
	UFUNCTION(BlueprintPure, BlueprintInternalUseOnly)
	static UBeamLobbyApi* GetSelf() { return GEngine->GetEngineSubsystem<UBeamLobbyApi>(); }

	

	
	/**
	 * @brief Makes an authenticated request to the Get /api/lobbies endpoint of the Lobby Service.
	 *
	 * PREFER THE UFUNCTION OVERLOAD AS OPPOSED TO THIS. THIS MAINLY EXISTS TO ALLOW LAMBDA BINDING THE HANDLER.
	 * (Dynamic delegates do not allow for that so... we autogen this one to make experimenting in CPP a bit faster).
	 * 
	 * @param UserSlot The Authenticated User Slot that is making this request.
	 * @param Request The Request UObject. All (de)serialized data the request data creates is tied to the lifecycle of this object.
	 * @param Handler A callback that defines how to handle success, error and completion.
     * @param OutRequestContext The Request Context associated with this request -- used to query information about the request or to cancel it while it's in flight.
	 * @param OpHandle When made as part of an Operation, you can pass this in and it'll register the request with the operation automatically.
	 * @param CallingContext A UObject managed by the UWorld that's making the request. Used to support multiple PIEs (see UBeamUserSlot::GetNamespacedSlotId) and read-only RequestCaches. 
	 */
	void CPP_GetLobbies(const FUserSlot& UserSlot, UGetLobbiesRequest* Request, const FOnGetLobbiesFullResponse& Handler, FBeamRequestContext& OutRequestContext, FBeamOperationHandle OpHandle = FBeamOperationHandle(), const UObject* CallingContext = nullptr) const;

		
	/**
	 * @brief Makes an authenticated request to the Post /api/lobbies endpoint of the Lobby Service.
	 *
	 * PREFER THE UFUNCTION OVERLOAD AS OPPOSED TO THIS. THIS MAINLY EXISTS TO ALLOW LAMBDA BINDING THE HANDLER.
	 * (Dynamic delegates do not allow for that so... we autogen this one to make experimenting in CPP a bit faster).
	 * 
	 * @param UserSlot The Authenticated User Slot that is making this request.
	 * @param Request The Request UObject. All (de)serialized data the request data creates is tied to the lifecycle of this object.
	 * @param Handler A callback that defines how to handle success, error and completion.
     * @param OutRequestContext The Request Context associated with this request -- used to query information about the request or to cancel it while it's in flight.
	 * @param OpHandle When made as part of an Operation, you can pass this in and it'll register the request with the operation automatically.
	 * @param CallingContext A UObject managed by the UWorld that's making the request. Used to support multiple PIEs (see UBeamUserSlot::GetNamespacedSlotId) and read-only RequestCaches. 
	 */
	void CPP_PostLobbies(const FUserSlot& UserSlot, UPostLobbiesRequest* Request, const FOnPostLobbiesFullResponse& Handler, FBeamRequestContext& OutRequestContext, FBeamOperationHandle OpHandle = FBeamOperationHandle(), const UObject* CallingContext = nullptr) const;

		
	/**
	 * @brief Makes an authenticated request to the Get /api/lobbies/{id} endpoint of the Lobby Service.
	 *
	 * PREFER THE UFUNCTION OVERLOAD AS OPPOSED TO THIS. THIS MAINLY EXISTS TO ALLOW LAMBDA BINDING THE HANDLER.
	 * (Dynamic delegates do not allow for that so... we autogen this one to make experimenting in CPP a bit faster).
	 * 
	 * @param UserSlot The Authenticated User Slot that is making this request.
	 * @param Request The Request UObject. All (de)serialized data the request data creates is tied to the lifecycle of this object.
	 * @param Handler A callback that defines how to handle success, error and completion.
     * @param OutRequestContext The Request Context associated with this request -- used to query information about the request or to cancel it while it's in flight.
	 * @param OpHandle When made as part of an Operation, you can pass this in and it'll register the request with the operation automatically.
	 * @param CallingContext A UObject managed by the UWorld that's making the request. Used to support multiple PIEs (see UBeamUserSlot::GetNamespacedSlotId) and read-only RequestCaches. 
	 */
	void CPP_GetLobby(const FUserSlot& UserSlot, UGetLobbyRequest* Request, const FOnGetLobbyFullResponse& Handler, FBeamRequestContext& OutRequestContext, FBeamOperationHandle OpHandle = FBeamOperationHandle(), const UObject* CallingContext = nullptr) const;

		
	/**
	 * @brief Makes an authenticated request to the Put /api/lobbies/{id} endpoint of the Lobby Service.
	 *
	 * PREFER THE UFUNCTION OVERLOAD AS OPPOSED TO THIS. THIS MAINLY EXISTS TO ALLOW LAMBDA BINDING THE HANDLER.
	 * (Dynamic delegates do not allow for that so... we autogen this one to make experimenting in CPP a bit faster).
	 * 
	 * @param UserSlot The Authenticated User Slot that is making this request.
	 * @param Request The Request UObject. All (de)serialized data the request data creates is tied to the lifecycle of this object.
	 * @param Handler A callback that defines how to handle success, error and completion.
     * @param OutRequestContext The Request Context associated with this request -- used to query information about the request or to cancel it while it's in flight.
	 * @param OpHandle When made as part of an Operation, you can pass this in and it'll register the request with the operation automatically.
	 * @param CallingContext A UObject managed by the UWorld that's making the request. Used to support multiple PIEs (see UBeamUserSlot::GetNamespacedSlotId) and read-only RequestCaches. 
	 */
	void CPP_PutLobby(const FUserSlot& UserSlot, UPutLobbyRequest* Request, const FOnPutLobbyFullResponse& Handler, FBeamRequestContext& OutRequestContext, FBeamOperationHandle OpHandle = FBeamOperationHandle(), const UObject* CallingContext = nullptr) const;

		
	/**
	 * @brief Makes an authenticated request to the Delete /api/lobbies/{id} endpoint of the Lobby Service.
	 *
	 * PREFER THE UFUNCTION OVERLOAD AS OPPOSED TO THIS. THIS MAINLY EXISTS TO ALLOW LAMBDA BINDING THE HANDLER.
	 * (Dynamic delegates do not allow for that so... we autogen this one to make experimenting in CPP a bit faster).
	 * 
	 * @param UserSlot The Authenticated User Slot that is making this request.
	 * @param Request The Request UObject. All (de)serialized data the request data creates is tied to the lifecycle of this object.
	 * @param Handler A callback that defines how to handle success, error and completion.
     * @param OutRequestContext The Request Context associated with this request -- used to query information about the request or to cancel it while it's in flight.
	 * @param OpHandle When made as part of an Operation, you can pass this in and it'll register the request with the operation automatically.
	 * @param CallingContext A UObject managed by the UWorld that's making the request. Used to support multiple PIEs (see UBeamUserSlot::GetNamespacedSlotId) and read-only RequestCaches. 
	 */
	void CPP_DeleteLobby(const FUserSlot& UserSlot, UDeleteLobbyRequest* Request, const FOnDeleteLobbyFullResponse& Handler, FBeamRequestContext& OutRequestContext, FBeamOperationHandle OpHandle = FBeamOperationHandle(), const UObject* CallingContext = nullptr) const;

		
	/**
	 * @brief Makes an authenticated request to the Put /api/lobbies/passcode endpoint of the Lobby Service.
	 *
	 * PREFER THE UFUNCTION OVERLOAD AS OPPOSED TO THIS. THIS MAINLY EXISTS TO ALLOW LAMBDA BINDING THE HANDLER.
	 * (Dynamic delegates do not allow for that so... we autogen this one to make experimenting in CPP a bit faster).
	 * 
	 * @param UserSlot The Authenticated User Slot that is making this request.
	 * @param Request The Request UObject. All (de)serialized data the request data creates is tied to the lifecycle of this object.
	 * @param Handler A callback that defines how to handle success, error and completion.
     * @param OutRequestContext The Request Context associated with this request -- used to query information about the request or to cancel it while it's in flight.
	 * @param OpHandle When made as part of an Operation, you can pass this in and it'll register the request with the operation automatically.
	 * @param CallingContext A UObject managed by the UWorld that's making the request. Used to support multiple PIEs (see UBeamUserSlot::GetNamespacedSlotId) and read-only RequestCaches. 
	 */
	void CPP_PutPasscode(const FUserSlot& UserSlot, UPutPasscodeRequest* Request, const FOnPutPasscodeFullResponse& Handler, FBeamRequestContext& OutRequestContext, FBeamOperationHandle OpHandle = FBeamOperationHandle(), const UObject* CallingContext = nullptr) const;

		
	/**
	 * @brief Makes an authenticated request to the Put /api/lobbies/{id}/metadata endpoint of the Lobby Service.
	 *
	 * PREFER THE UFUNCTION OVERLOAD AS OPPOSED TO THIS. THIS MAINLY EXISTS TO ALLOW LAMBDA BINDING THE HANDLER.
	 * (Dynamic delegates do not allow for that so... we autogen this one to make experimenting in CPP a bit faster).
	 * 
	 * @param UserSlot The Authenticated User Slot that is making this request.
	 * @param Request The Request UObject. All (de)serialized data the request data creates is tied to the lifecycle of this object.
	 * @param Handler A callback that defines how to handle success, error and completion.
     * @param OutRequestContext The Request Context associated with this request -- used to query information about the request or to cancel it while it's in flight.
	 * @param OpHandle When made as part of an Operation, you can pass this in and it'll register the request with the operation automatically.
	 * @param CallingContext A UObject managed by the UWorld that's making the request. Used to support multiple PIEs (see UBeamUserSlot::GetNamespacedSlotId) and read-only RequestCaches. 
	 */
	void CPP_PutMetadata(const FUserSlot& UserSlot, UApiLobbyPutMetadataRequest* Request, const FOnApiLobbyPutMetadataFullResponse& Handler, FBeamRequestContext& OutRequestContext, FBeamOperationHandle OpHandle = FBeamOperationHandle(), const UObject* CallingContext = nullptr) const;

		
	/**
	 * @brief Makes an authenticated request to the Put /api/lobbies/{id}/tags endpoint of the Lobby Service.
	 *
	 * PREFER THE UFUNCTION OVERLOAD AS OPPOSED TO THIS. THIS MAINLY EXISTS TO ALLOW LAMBDA BINDING THE HANDLER.
	 * (Dynamic delegates do not allow for that so... we autogen this one to make experimenting in CPP a bit faster).
	 * 
	 * @param UserSlot The Authenticated User Slot that is making this request.
	 * @param Request The Request UObject. All (de)serialized data the request data creates is tied to the lifecycle of this object.
	 * @param Handler A callback that defines how to handle success, error and completion.
     * @param OutRequestContext The Request Context associated with this request -- used to query information about the request or to cancel it while it's in flight.
	 * @param OpHandle When made as part of an Operation, you can pass this in and it'll register the request with the operation automatically.
	 * @param CallingContext A UObject managed by the UWorld that's making the request. Used to support multiple PIEs (see UBeamUserSlot::GetNamespacedSlotId) and read-only RequestCaches. 
	 */
	void CPP_PutTags(const FUserSlot& UserSlot, UPutTagsRequest* Request, const FOnPutTagsFullResponse& Handler, FBeamRequestContext& OutRequestContext, FBeamOperationHandle OpHandle = FBeamOperationHandle(), const UObject* CallingContext = nullptr) const;

		
	/**
	 * @brief Makes an authenticated request to the Delete /api/lobbies/{id}/tags endpoint of the Lobby Service.
	 *
	 * PREFER THE UFUNCTION OVERLOAD AS OPPOSED TO THIS. THIS MAINLY EXISTS TO ALLOW LAMBDA BINDING THE HANDLER.
	 * (Dynamic delegates do not allow for that so... we autogen this one to make experimenting in CPP a bit faster).
	 * 
	 * @param UserSlot The Authenticated User Slot that is making this request.
	 * @param Request The Request UObject. All (de)serialized data the request data creates is tied to the lifecycle of this object.
	 * @param Handler A callback that defines how to handle success, error and completion.
     * @param OutRequestContext The Request Context associated with this request -- used to query information about the request or to cancel it while it's in flight.
	 * @param OpHandle When made as part of an Operation, you can pass this in and it'll register the request with the operation automatically.
	 * @param CallingContext A UObject managed by the UWorld that's making the request. Used to support multiple PIEs (see UBeamUserSlot::GetNamespacedSlotId) and read-only RequestCaches. 
	 */
	void CPP_DeleteTags(const FUserSlot& UserSlot, UDeleteTagsRequest* Request, const FOnDeleteTagsFullResponse& Handler, FBeamRequestContext& OutRequestContext, FBeamOperationHandle OpHandle = FBeamOperationHandle(), const UObject* CallingContext = nullptr) const;


	

	
	/**
	 * @brief Makes an authenticated request to the Get /api/lobbies endpoint of the Lobby Service.
	 *
	 * @param UserSlot The authenticated UserSlot with the user making the request. 
	 * @param Request The Request UObject. All (de)serialized data the request data creates is tied to the lifecycle of this object.
	 * @param OnSuccess What to do if the requests receives a successful response.
	 * @param OnError What to do if the request receives an error response.
	 * @param OnComplete What to after either OnSuccess or OnError have finished executing.
	 * @param OutRequestContext The Request Context associated with this request -- used to query information about the request or to cancel it while it's in flight.
	 * @param CallingContext A UObject managed by the UWorld that's making the request. Used to support multiple PIEs (see UBeamUserSlot::GetNamespacedSlotId) and read-only RequestCaches.
	 */
	UFUNCTION(BlueprintCallable, BlueprintInternalUseOnly, Category="Beam|Backend|Lobby", meta=(DefaultToSelf="CallingContext", AdvancedDisplay="OpHandle,CallingContext",AutoCreateRefTerm="UserSlot,OnSuccess,OnError,OnComplete,OpHandle", BeamFlowFunction))
	void GetLobbies(FUserSlot UserSlot, UGetLobbiesRequest* Request, const FOnGetLobbiesSuccess& OnSuccess, const FOnGetLobbiesError& OnError, const FOnGetLobbiesComplete& OnComplete, FBeamRequestContext& OutRequestContext, FBeamOperationHandle OpHandle = FBeamOperationHandle(), const UObject* CallingContext = nullptr);

		
	/**
	 * @brief Makes an authenticated request to the Post /api/lobbies endpoint of the Lobby Service.
	 *
	 * @param UserSlot The authenticated UserSlot with the user making the request. 
	 * @param Request The Request UObject. All (de)serialized data the request data creates is tied to the lifecycle of this object.
	 * @param OnSuccess What to do if the requests receives a successful response.
	 * @param OnError What to do if the request receives an error response.
	 * @param OnComplete What to after either OnSuccess or OnError have finished executing.
	 * @param OutRequestContext The Request Context associated with this request -- used to query information about the request or to cancel it while it's in flight.
	 * @param CallingContext A UObject managed by the UWorld that's making the request. Used to support multiple PIEs (see UBeamUserSlot::GetNamespacedSlotId) and read-only RequestCaches.
	 */
	UFUNCTION(BlueprintCallable, BlueprintInternalUseOnly, Category="Beam|Backend|Lobby", meta=(DefaultToSelf="CallingContext", AdvancedDisplay="OpHandle,CallingContext",AutoCreateRefTerm="UserSlot,OnSuccess,OnError,OnComplete,OpHandle", BeamFlowFunction))
	void PostLobbies(FUserSlot UserSlot, UPostLobbiesRequest* Request, const FOnPostLobbiesSuccess& OnSuccess, const FOnPostLobbiesError& OnError, const FOnPostLobbiesComplete& OnComplete, FBeamRequestContext& OutRequestContext, FBeamOperationHandle OpHandle = FBeamOperationHandle(), const UObject* CallingContext = nullptr);

		
	/**
	 * @brief Makes an authenticated request to the Get /api/lobbies/{id} endpoint of the Lobby Service.
	 *
	 * @param UserSlot The authenticated UserSlot with the user making the request. 
	 * @param Request The Request UObject. All (de)serialized data the request data creates is tied to the lifecycle of this object.
	 * @param OnSuccess What to do if the requests receives a successful response.
	 * @param OnError What to do if the request receives an error response.
	 * @param OnComplete What to after either OnSuccess or OnError have finished executing.
	 * @param OutRequestContext The Request Context associated with this request -- used to query information about the request or to cancel it while it's in flight.
	 * @param CallingContext A UObject managed by the UWorld that's making the request. Used to support multiple PIEs (see UBeamUserSlot::GetNamespacedSlotId) and read-only RequestCaches.
	 */
	UFUNCTION(BlueprintCallable, BlueprintInternalUseOnly, Category="Beam|Backend|Lobby", meta=(DefaultToSelf="CallingContext", AdvancedDisplay="OpHandle,CallingContext",AutoCreateRefTerm="UserSlot,OnSuccess,OnError,OnComplete,OpHandle", BeamFlowFunction))
	void GetLobby(FUserSlot UserSlot, UGetLobbyRequest* Request, const FOnGetLobbySuccess& OnSuccess, const FOnGetLobbyError& OnError, const FOnGetLobbyComplete& OnComplete, FBeamRequestContext& OutRequestContext, FBeamOperationHandle OpHandle = FBeamOperationHandle(), const UObject* CallingContext = nullptr);

		
	/**
	 * @brief Makes an authenticated request to the Put /api/lobbies/{id} endpoint of the Lobby Service.
	 *
	 * @param UserSlot The authenticated UserSlot with the user making the request. 
	 * @param Request The Request UObject. All (de)serialized data the request data creates is tied to the lifecycle of this object.
	 * @param OnSuccess What to do if the requests receives a successful response.
	 * @param OnError What to do if the request receives an error response.
	 * @param OnComplete What to after either OnSuccess or OnError have finished executing.
	 * @param OutRequestContext The Request Context associated with this request -- used to query information about the request or to cancel it while it's in flight.
	 * @param CallingContext A UObject managed by the UWorld that's making the request. Used to support multiple PIEs (see UBeamUserSlot::GetNamespacedSlotId) and read-only RequestCaches.
	 */
	UFUNCTION(BlueprintCallable, BlueprintInternalUseOnly, Category="Beam|Backend|Lobby", meta=(DefaultToSelf="CallingContext", AdvancedDisplay="OpHandle,CallingContext",AutoCreateRefTerm="UserSlot,OnSuccess,OnError,OnComplete,OpHandle", BeamFlowFunction))
	void PutLobby(FUserSlot UserSlot, UPutLobbyRequest* Request, const FOnPutLobbySuccess& OnSuccess, const FOnPutLobbyError& OnError, const FOnPutLobbyComplete& OnComplete, FBeamRequestContext& OutRequestContext, FBeamOperationHandle OpHandle = FBeamOperationHandle(), const UObject* CallingContext = nullptr);

		
	/**
	 * @brief Makes an authenticated request to the Delete /api/lobbies/{id} endpoint of the Lobby Service.
	 *
	 * @param UserSlot The authenticated UserSlot with the user making the request. 
	 * @param Request The Request UObject. All (de)serialized data the request data creates is tied to the lifecycle of this object.
	 * @param OnSuccess What to do if the requests receives a successful response.
	 * @param OnError What to do if the request receives an error response.
	 * @param OnComplete What to after either OnSuccess or OnError have finished executing.
	 * @param OutRequestContext The Request Context associated with this request -- used to query information about the request or to cancel it while it's in flight.
	 * @param CallingContext A UObject managed by the UWorld that's making the request. Used to support multiple PIEs (see UBeamUserSlot::GetNamespacedSlotId) and read-only RequestCaches.
	 */
	UFUNCTION(BlueprintCallable, BlueprintInternalUseOnly, Category="Beam|Backend|Lobby", meta=(DefaultToSelf="CallingContext", AdvancedDisplay="OpHandle,CallingContext",AutoCreateRefTerm="UserSlot,OnSuccess,OnError,OnComplete,OpHandle", BeamFlowFunction))
	void DeleteLobby(FUserSlot UserSlot, UDeleteLobbyRequest* Request, const FOnDeleteLobbySuccess& OnSuccess, const FOnDeleteLobbyError& OnError, const FOnDeleteLobbyComplete& OnComplete, FBeamRequestContext& OutRequestContext, FBeamOperationHandle OpHandle = FBeamOperationHandle(), const UObject* CallingContext = nullptr);

		
	/**
	 * @brief Makes an authenticated request to the Put /api/lobbies/passcode endpoint of the Lobby Service.
	 *
	 * @param UserSlot The authenticated UserSlot with the user making the request. 
	 * @param Request The Request UObject. All (de)serialized data the request data creates is tied to the lifecycle of this object.
	 * @param OnSuccess What to do if the requests receives a successful response.
	 * @param OnError What to do if the request receives an error response.
	 * @param OnComplete What to after either OnSuccess or OnError have finished executing.
	 * @param OutRequestContext The Request Context associated with this request -- used to query information about the request or to cancel it while it's in flight.
	 * @param CallingContext A UObject managed by the UWorld that's making the request. Used to support multiple PIEs (see UBeamUserSlot::GetNamespacedSlotId) and read-only RequestCaches.
	 */
	UFUNCTION(BlueprintCallable, BlueprintInternalUseOnly, Category="Beam|Backend|Lobby", meta=(DefaultToSelf="CallingContext", AdvancedDisplay="OpHandle,CallingContext",AutoCreateRefTerm="UserSlot,OnSuccess,OnError,OnComplete,OpHandle", BeamFlowFunction))
	void PutPasscode(FUserSlot UserSlot, UPutPasscodeRequest* Request, const FOnPutPasscodeSuccess& OnSuccess, const FOnPutPasscodeError& OnError, const FOnPutPasscodeComplete& OnComplete, FBeamRequestContext& OutRequestContext, FBeamOperationHandle OpHandle = FBeamOperationHandle(), const UObject* CallingContext = nullptr);

		
	/**
	 * @brief Makes an authenticated request to the Put /api/lobbies/{id}/metadata endpoint of the Lobby Service.
	 *
	 * @param UserSlot The authenticated UserSlot with the user making the request. 
	 * @param Request The Request UObject. All (de)serialized data the request data creates is tied to the lifecycle of this object.
	 * @param OnSuccess What to do if the requests receives a successful response.
	 * @param OnError What to do if the request receives an error response.
	 * @param OnComplete What to after either OnSuccess or OnError have finished executing.
	 * @param OutRequestContext The Request Context associated with this request -- used to query information about the request or to cancel it while it's in flight.
	 * @param CallingContext A UObject managed by the UWorld that's making the request. Used to support multiple PIEs (see UBeamUserSlot::GetNamespacedSlotId) and read-only RequestCaches.
	 */
	UFUNCTION(BlueprintCallable, BlueprintInternalUseOnly, Category="Beam|Backend|Lobby", meta=(DefaultToSelf="CallingContext", AdvancedDisplay="OpHandle,CallingContext",AutoCreateRefTerm="UserSlot,OnSuccess,OnError,OnComplete,OpHandle", BeamFlowFunction))
	void PutMetadata(FUserSlot UserSlot, UApiLobbyPutMetadataRequest* Request, const FOnApiLobbyPutMetadataSuccess& OnSuccess, const FOnApiLobbyPutMetadataError& OnError, const FOnApiLobbyPutMetadataComplete& OnComplete, FBeamRequestContext& OutRequestContext, FBeamOperationHandle OpHandle = FBeamOperationHandle(), const UObject* CallingContext = nullptr);

		
	/**
	 * @brief Makes an authenticated request to the Put /api/lobbies/{id}/tags endpoint of the Lobby Service.
	 *
	 * @param UserSlot The authenticated UserSlot with the user making the request. 
	 * @param Request The Request UObject. All (de)serialized data the request data creates is tied to the lifecycle of this object.
	 * @param OnSuccess What to do if the requests receives a successful response.
	 * @param OnError What to do if the request receives an error response.
	 * @param OnComplete What to after either OnSuccess or OnError have finished executing.
	 * @param OutRequestContext The Request Context associated with this request -- used to query information about the request or to cancel it while it's in flight.
	 * @param CallingContext A UObject managed by the UWorld that's making the request. Used to support multiple PIEs (see UBeamUserSlot::GetNamespacedSlotId) and read-only RequestCaches.
	 */
	UFUNCTION(BlueprintCallable, BlueprintInternalUseOnly, Category="Beam|Backend|Lobby", meta=(DefaultToSelf="CallingContext", AdvancedDisplay="OpHandle,CallingContext",AutoCreateRefTerm="UserSlot,OnSuccess,OnError,OnComplete,OpHandle", BeamFlowFunction))
	void PutTags(FUserSlot UserSlot, UPutTagsRequest* Request, const FOnPutTagsSuccess& OnSuccess, const FOnPutTagsError& OnError, const FOnPutTagsComplete& OnComplete, FBeamRequestContext& OutRequestContext, FBeamOperationHandle OpHandle = FBeamOperationHandle(), const UObject* CallingContext = nullptr);

		
	/**
	 * @brief Makes an authenticated request to the Delete /api/lobbies/{id}/tags endpoint of the Lobby Service.
	 *
	 * @param UserSlot The authenticated UserSlot with the user making the request. 
	 * @param Request The Request UObject. All (de)serialized data the request data creates is tied to the lifecycle of this object.
	 * @param OnSuccess What to do if the requests receives a successful response.
	 * @param OnError What to do if the request receives an error response.
	 * @param OnComplete What to after either OnSuccess or OnError have finished executing.
	 * @param OutRequestContext The Request Context associated with this request -- used to query information about the request or to cancel it while it's in flight.
	 * @param CallingContext A UObject managed by the UWorld that's making the request. Used to support multiple PIEs (see UBeamUserSlot::GetNamespacedSlotId) and read-only RequestCaches.
	 */
	UFUNCTION(BlueprintCallable, BlueprintInternalUseOnly, Category="Beam|Backend|Lobby", meta=(DefaultToSelf="CallingContext", AdvancedDisplay="OpHandle,CallingContext",AutoCreateRefTerm="UserSlot,OnSuccess,OnError,OnComplete,OpHandle", BeamFlowFunction))
	void DeleteTags(FUserSlot UserSlot, UDeleteTagsRequest* Request, const FOnDeleteTagsSuccess& OnSuccess, const FOnDeleteTagsError& OnError, const FOnDeleteTagsComplete& OnComplete, FBeamRequestContext& OutRequestContext, FBeamOperationHandle OpHandle = FBeamOperationHandle(), const UObject* CallingContext = nullptr);

};
