

#pragma once

#include "CoreMinimal.h"
#include "BeamBackend/BeamBackend.h"
#include "BeamBackend/ResponseCache/BeamResponseCache.h"
#include "RequestTracker/BeamRequestTracker.h"

#include "BeamableCore/Public/AutoGen/SubSystems/Party/PostPartiesRequest.h"
#include "BeamableCore/Public/AutoGen/SubSystems/Party/ApiPartyPutMetadataByIdRequest.h"
#include "BeamableCore/Public/AutoGen/SubSystems/Party/GetPartyRequest.h"
#include "BeamableCore/Public/AutoGen/SubSystems/Party/PutPartyRequest.h"
#include "BeamableCore/Public/AutoGen/SubSystems/Party/PutPromoteRequest.h"
#include "BeamableCore/Public/AutoGen/SubSystems/Party/ApiPartyPostInviteByIdRequest.h"
#include "BeamableCore/Public/AutoGen/SubSystems/Party/DeleteInviteRequest.h"
#include "BeamableCore/Public/AutoGen/SubSystems/Party/DeleteMembersRequest.h"
#include "BeamableCore/Public/AutoGen/SubSystems/Party/GetPartiesRequest.h"
#include "BeamableCore/Public/AutoGen/SubSystems/Party/DeletePartiesRequest.h"
#include "BeamableCore/Public/AutoGen/SubSystems/Party/GetPartiesInvitesRequest.h"
#include "BeamableCore/Public/AutoGen/SubSystems/Party/GetPartyInvitesRequest.h"

#include "BeamPartyApi.generated.h"


/**
 * Subsystem containing request calls for the Party service.
 */
UCLASS(NotBlueprintType)
class BEAMABLECORE_API UBeamPartyApi : public UEngineSubsystem
{
private:
	GENERATED_BODY()
	/** @brief Initializes the auto-increment Id */
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
	void BP_PostPartiesImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, const FBeamAuthToken& AuthToken, UPostPartiesRequest* RequestData,
	                  const FOnPostPartiesSuccess& OnSuccess, const FOnPostPartiesError& OnError, const FOnPostPartiesComplete& OnComplete, 
					  int64& OutRequestId, FBeamOperationHandle OpHandle = FBeamOperationHandle(), const UObject* CallingContext = nullptr) const;
	/**
	 * @brief Overload version for binding lambdas when in C++ land. Prefer the BP version whenever possible, this is here mostly for quick experimentation purposes.	 
	 */
	void CPP_PostPartiesImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, const FBeamAuthToken& AuthToken, UPostPartiesRequest* RequestData,
	                   const FOnPostPartiesFullResponse& Handler, int64& OutRequestId, FBeamOperationHandle OpHandle = FBeamOperationHandle(), const UObject* CallingContext = nullptr) const;
		
	/**
	 * @brief Private implementation for requests that require authentication that all overloaded BP UFunctions call.	  
	 */
	void BP_PutMetadataImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, const FBeamAuthToken& AuthToken, UApiPartyPutMetadataByIdRequest* RequestData,
	                  const FOnApiPartyPutMetadataByIdSuccess& OnSuccess, const FOnApiPartyPutMetadataByIdError& OnError, const FOnApiPartyPutMetadataByIdComplete& OnComplete, 
					  int64& OutRequestId, FBeamOperationHandle OpHandle = FBeamOperationHandle(), const UObject* CallingContext = nullptr) const;
	/**
	 * @brief Overload version for binding lambdas when in C++ land. Prefer the BP version whenever possible, this is here mostly for quick experimentation purposes.	 
	 */
	void CPP_PutMetadataImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, const FBeamAuthToken& AuthToken, UApiPartyPutMetadataByIdRequest* RequestData,
	                   const FOnApiPartyPutMetadataByIdFullResponse& Handler, int64& OutRequestId, FBeamOperationHandle OpHandle = FBeamOperationHandle(), const UObject* CallingContext = nullptr) const;
		
	/**
	 * @brief Private implementation for requests that require authentication that all overloaded BP UFunctions call.	  
	 */
	void BP_GetPartyImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, const FBeamAuthToken& AuthToken, UGetPartyRequest* RequestData,
	                  const FOnGetPartySuccess& OnSuccess, const FOnGetPartyError& OnError, const FOnGetPartyComplete& OnComplete, 
					  int64& OutRequestId, FBeamOperationHandle OpHandle = FBeamOperationHandle(), const UObject* CallingContext = nullptr) const;
	/**
	 * @brief Overload version for binding lambdas when in C++ land. Prefer the BP version whenever possible, this is here mostly for quick experimentation purposes.	 
	 */
	void CPP_GetPartyImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, const FBeamAuthToken& AuthToken, UGetPartyRequest* RequestData,
	                   const FOnGetPartyFullResponse& Handler, int64& OutRequestId, FBeamOperationHandle OpHandle = FBeamOperationHandle(), const UObject* CallingContext = nullptr) const;
		
	/**
	 * @brief Private implementation for requests that require authentication that all overloaded BP UFunctions call.	  
	 */
	void BP_PutPartyImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, const FBeamAuthToken& AuthToken, UPutPartyRequest* RequestData,
	                  const FOnPutPartySuccess& OnSuccess, const FOnPutPartyError& OnError, const FOnPutPartyComplete& OnComplete, 
					  int64& OutRequestId, FBeamOperationHandle OpHandle = FBeamOperationHandle(), const UObject* CallingContext = nullptr) const;
	/**
	 * @brief Overload version for binding lambdas when in C++ land. Prefer the BP version whenever possible, this is here mostly for quick experimentation purposes.	 
	 */
	void CPP_PutPartyImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, const FBeamAuthToken& AuthToken, UPutPartyRequest* RequestData,
	                   const FOnPutPartyFullResponse& Handler, int64& OutRequestId, FBeamOperationHandle OpHandle = FBeamOperationHandle(), const UObject* CallingContext = nullptr) const;
		
	/**
	 * @brief Private implementation for requests that require authentication that all overloaded BP UFunctions call.	  
	 */
	void BP_PutPromoteImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, const FBeamAuthToken& AuthToken, UPutPromoteRequest* RequestData,
	                  const FOnPutPromoteSuccess& OnSuccess, const FOnPutPromoteError& OnError, const FOnPutPromoteComplete& OnComplete, 
					  int64& OutRequestId, FBeamOperationHandle OpHandle = FBeamOperationHandle(), const UObject* CallingContext = nullptr) const;
	/**
	 * @brief Overload version for binding lambdas when in C++ land. Prefer the BP version whenever possible, this is here mostly for quick experimentation purposes.	 
	 */
	void CPP_PutPromoteImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, const FBeamAuthToken& AuthToken, UPutPromoteRequest* RequestData,
	                   const FOnPutPromoteFullResponse& Handler, int64& OutRequestId, FBeamOperationHandle OpHandle = FBeamOperationHandle(), const UObject* CallingContext = nullptr) const;
		
	/**
	 * @brief Private implementation for requests that require authentication that all overloaded BP UFunctions call.	  
	 */
	void BP_PostInviteImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, const FBeamAuthToken& AuthToken, UApiPartyPostInviteByIdRequest* RequestData,
	                  const FOnApiPartyPostInviteByIdSuccess& OnSuccess, const FOnApiPartyPostInviteByIdError& OnError, const FOnApiPartyPostInviteByIdComplete& OnComplete, 
					  int64& OutRequestId, FBeamOperationHandle OpHandle = FBeamOperationHandle(), const UObject* CallingContext = nullptr) const;
	/**
	 * @brief Overload version for binding lambdas when in C++ land. Prefer the BP version whenever possible, this is here mostly for quick experimentation purposes.	 
	 */
	void CPP_PostInviteImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, const FBeamAuthToken& AuthToken, UApiPartyPostInviteByIdRequest* RequestData,
	                   const FOnApiPartyPostInviteByIdFullResponse& Handler, int64& OutRequestId, FBeamOperationHandle OpHandle = FBeamOperationHandle(), const UObject* CallingContext = nullptr) const;
		
	/**
	 * @brief Private implementation for requests that require authentication that all overloaded BP UFunctions call.	  
	 */
	void BP_DeleteInviteImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, const FBeamAuthToken& AuthToken, UDeleteInviteRequest* RequestData,
	                  const FOnDeleteInviteSuccess& OnSuccess, const FOnDeleteInviteError& OnError, const FOnDeleteInviteComplete& OnComplete, 
					  int64& OutRequestId, FBeamOperationHandle OpHandle = FBeamOperationHandle(), const UObject* CallingContext = nullptr) const;
	/**
	 * @brief Overload version for binding lambdas when in C++ land. Prefer the BP version whenever possible, this is here mostly for quick experimentation purposes.	 
	 */
	void CPP_DeleteInviteImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, const FBeamAuthToken& AuthToken, UDeleteInviteRequest* RequestData,
	                   const FOnDeleteInviteFullResponse& Handler, int64& OutRequestId, FBeamOperationHandle OpHandle = FBeamOperationHandle(), const UObject* CallingContext = nullptr) const;
		
	/**
	 * @brief Private implementation for requests that require authentication that all overloaded BP UFunctions call.	  
	 */
	void BP_DeleteMembersImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, const FBeamAuthToken& AuthToken, UDeleteMembersRequest* RequestData,
	                  const FOnDeleteMembersSuccess& OnSuccess, const FOnDeleteMembersError& OnError, const FOnDeleteMembersComplete& OnComplete, 
					  int64& OutRequestId, FBeamOperationHandle OpHandle = FBeamOperationHandle(), const UObject* CallingContext = nullptr) const;
	/**
	 * @brief Overload version for binding lambdas when in C++ land. Prefer the BP version whenever possible, this is here mostly for quick experimentation purposes.	 
	 */
	void CPP_DeleteMembersImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, const FBeamAuthToken& AuthToken, UDeleteMembersRequest* RequestData,
	                   const FOnDeleteMembersFullResponse& Handler, int64& OutRequestId, FBeamOperationHandle OpHandle = FBeamOperationHandle(), const UObject* CallingContext = nullptr) const;
		
	/**
	 * @brief Private implementation for requests that require authentication that all overloaded BP UFunctions call.	  
	 */
	void BP_GetPartiesImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, const FBeamAuthToken& AuthToken, UGetPartiesRequest* RequestData,
	                  const FOnGetPartiesSuccess& OnSuccess, const FOnGetPartiesError& OnError, const FOnGetPartiesComplete& OnComplete, 
					  int64& OutRequestId, FBeamOperationHandle OpHandle = FBeamOperationHandle(), const UObject* CallingContext = nullptr) const;
	/**
	 * @brief Overload version for binding lambdas when in C++ land. Prefer the BP version whenever possible, this is here mostly for quick experimentation purposes.	 
	 */
	void CPP_GetPartiesImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, const FBeamAuthToken& AuthToken, UGetPartiesRequest* RequestData,
	                   const FOnGetPartiesFullResponse& Handler, int64& OutRequestId, FBeamOperationHandle OpHandle = FBeamOperationHandle(), const UObject* CallingContext = nullptr) const;
		
	/**
	 * @brief Private implementation for requests that require authentication that all overloaded BP UFunctions call.	  
	 */
	void BP_DeletePartiesImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, const FBeamAuthToken& AuthToken, UDeletePartiesRequest* RequestData,
	                  const FOnDeletePartiesSuccess& OnSuccess, const FOnDeletePartiesError& OnError, const FOnDeletePartiesComplete& OnComplete, 
					  int64& OutRequestId, FBeamOperationHandle OpHandle = FBeamOperationHandle(), const UObject* CallingContext = nullptr) const;
	/**
	 * @brief Overload version for binding lambdas when in C++ land. Prefer the BP version whenever possible, this is here mostly for quick experimentation purposes.	 
	 */
	void CPP_DeletePartiesImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, const FBeamAuthToken& AuthToken, UDeletePartiesRequest* RequestData,
	                   const FOnDeletePartiesFullResponse& Handler, int64& OutRequestId, FBeamOperationHandle OpHandle = FBeamOperationHandle(), const UObject* CallingContext = nullptr) const;
		
	/**
	 * @brief Private implementation for requests that require authentication that all overloaded BP UFunctions call.	  
	 */
	void BP_GetPartiesInvitesImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, const FBeamAuthToken& AuthToken, UGetPartiesInvitesRequest* RequestData,
	                  const FOnGetPartiesInvitesSuccess& OnSuccess, const FOnGetPartiesInvitesError& OnError, const FOnGetPartiesInvitesComplete& OnComplete, 
					  int64& OutRequestId, FBeamOperationHandle OpHandle = FBeamOperationHandle(), const UObject* CallingContext = nullptr) const;
	/**
	 * @brief Overload version for binding lambdas when in C++ land. Prefer the BP version whenever possible, this is here mostly for quick experimentation purposes.	 
	 */
	void CPP_GetPartiesInvitesImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, const FBeamAuthToken& AuthToken, UGetPartiesInvitesRequest* RequestData,
	                   const FOnGetPartiesInvitesFullResponse& Handler, int64& OutRequestId, FBeamOperationHandle OpHandle = FBeamOperationHandle(), const UObject* CallingContext = nullptr) const;
		
	/**
	 * @brief Private implementation for requests that require authentication that all overloaded BP UFunctions call.	  
	 */
	void BP_GetPartyInvitesImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, const FBeamAuthToken& AuthToken, UGetPartyInvitesRequest* RequestData,
	                  const FOnGetPartyInvitesSuccess& OnSuccess, const FOnGetPartyInvitesError& OnError, const FOnGetPartyInvitesComplete& OnComplete, 
					  int64& OutRequestId, FBeamOperationHandle OpHandle = FBeamOperationHandle(), const UObject* CallingContext = nullptr) const;
	/**
	 * @brief Overload version for binding lambdas when in C++ land. Prefer the BP version whenever possible, this is here mostly for quick experimentation purposes.	 
	 */
	void CPP_GetPartyInvitesImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, const FBeamAuthToken& AuthToken, UGetPartyInvitesRequest* RequestData,
	                   const FOnGetPartyInvitesFullResponse& Handler, int64& OutRequestId, FBeamOperationHandle OpHandle = FBeamOperationHandle(), const UObject* CallingContext = nullptr) const;

public:
	
	/** Used by a helper blueprint node so that you can easily chain requests in BP-land. */
	UFUNCTION(BlueprintPure, BlueprintInternalUseOnly)
	static UBeamPartyApi* GetSelf() { return GEngine->GetEngineSubsystem<UBeamPartyApi>(); }

	

	
	/**
	 * @brief Makes an authenticated request to the Post /api/parties endpoint of the Party Service.
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
	void CPP_PostParties(const FUserSlot& UserSlot, UPostPartiesRequest* Request, const FOnPostPartiesFullResponse& Handler, FBeamRequestContext& OutRequestContext, FBeamOperationHandle OpHandle = FBeamOperationHandle(), const UObject* CallingContext = nullptr) const;

		
	/**
	 * @brief Makes an authenticated request to the Put /api/parties/{id}/metadata endpoint of the Party Service.
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
	void CPP_PutMetadata(const FUserSlot& UserSlot, UApiPartyPutMetadataByIdRequest* Request, const FOnApiPartyPutMetadataByIdFullResponse& Handler, FBeamRequestContext& OutRequestContext, FBeamOperationHandle OpHandle = FBeamOperationHandle(), const UObject* CallingContext = nullptr) const;

		
	/**
	 * @brief Makes an authenticated request to the Get /api/parties/{id} endpoint of the Party Service.
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
	void CPP_GetParty(const FUserSlot& UserSlot, UGetPartyRequest* Request, const FOnGetPartyFullResponse& Handler, FBeamRequestContext& OutRequestContext, FBeamOperationHandle OpHandle = FBeamOperationHandle(), const UObject* CallingContext = nullptr) const;

		
	/**
	 * @brief Makes an authenticated request to the Put /api/parties/{id} endpoint of the Party Service.
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
	void CPP_PutParty(const FUserSlot& UserSlot, UPutPartyRequest* Request, const FOnPutPartyFullResponse& Handler, FBeamRequestContext& OutRequestContext, FBeamOperationHandle OpHandle = FBeamOperationHandle(), const UObject* CallingContext = nullptr) const;

		
	/**
	 * @brief Makes an authenticated request to the Put /api/parties/{id}/promote endpoint of the Party Service.
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
	void CPP_PutPromote(const FUserSlot& UserSlot, UPutPromoteRequest* Request, const FOnPutPromoteFullResponse& Handler, FBeamRequestContext& OutRequestContext, FBeamOperationHandle OpHandle = FBeamOperationHandle(), const UObject* CallingContext = nullptr) const;

		
	/**
	 * @brief Makes an authenticated request to the Post /api/parties/{id}/invite endpoint of the Party Service.
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
	void CPP_PostInvite(const FUserSlot& UserSlot, UApiPartyPostInviteByIdRequest* Request, const FOnApiPartyPostInviteByIdFullResponse& Handler, FBeamRequestContext& OutRequestContext, FBeamOperationHandle OpHandle = FBeamOperationHandle(), const UObject* CallingContext = nullptr) const;

		
	/**
	 * @brief Makes an authenticated request to the Delete /api/parties/{id}/invite endpoint of the Party Service.
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
	void CPP_DeleteInvite(const FUserSlot& UserSlot, UDeleteInviteRequest* Request, const FOnDeleteInviteFullResponse& Handler, FBeamRequestContext& OutRequestContext, FBeamOperationHandle OpHandle = FBeamOperationHandle(), const UObject* CallingContext = nullptr) const;

		
	/**
	 * @brief Makes an authenticated request to the Delete /api/parties/{id}/members endpoint of the Party Service.
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
	void CPP_DeleteMembers(const FUserSlot& UserSlot, UDeleteMembersRequest* Request, const FOnDeleteMembersFullResponse& Handler, FBeamRequestContext& OutRequestContext, FBeamOperationHandle OpHandle = FBeamOperationHandle(), const UObject* CallingContext = nullptr) const;

		
	/**
	 * @brief Makes an authenticated request to the Get /api/players/{playerId}/parties endpoint of the Party Service.
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
	void CPP_GetParties(const FUserSlot& UserSlot, UGetPartiesRequest* Request, const FOnGetPartiesFullResponse& Handler, FBeamRequestContext& OutRequestContext, FBeamOperationHandle OpHandle = FBeamOperationHandle(), const UObject* CallingContext = nullptr) const;

		
	/**
	 * @brief Makes an authenticated request to the Delete /api/players/{playerId}/parties endpoint of the Party Service.
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
	void CPP_DeleteParties(const FUserSlot& UserSlot, UDeletePartiesRequest* Request, const FOnDeletePartiesFullResponse& Handler, FBeamRequestContext& OutRequestContext, FBeamOperationHandle OpHandle = FBeamOperationHandle(), const UObject* CallingContext = nullptr) const;

		
	/**
	 * @brief Makes an authenticated request to the Get /api/players/{playerId}/parties/invites endpoint of the Party Service.
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
	void CPP_GetPartiesInvites(const FUserSlot& UserSlot, UGetPartiesInvitesRequest* Request, const FOnGetPartiesInvitesFullResponse& Handler, FBeamRequestContext& OutRequestContext, FBeamOperationHandle OpHandle = FBeamOperationHandle(), const UObject* CallingContext = nullptr) const;

		
	/**
	 * @brief Makes an authenticated request to the Get /api/players/{playerId}/party/invites endpoint of the Party Service.
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
	void CPP_GetPartyInvites(const FUserSlot& UserSlot, UGetPartyInvitesRequest* Request, const FOnGetPartyInvitesFullResponse& Handler, FBeamRequestContext& OutRequestContext, FBeamOperationHandle OpHandle = FBeamOperationHandle(), const UObject* CallingContext = nullptr) const;


	

	
	/**
	 * @brief Makes an authenticated request to the Post /api/parties endpoint of the Party Service.
	 *
	 * @param UserSlot The authenticated UserSlot with the user making the request. 
	 * @param Request The Request UObject. All (de)serialized data the request data creates is tied to the lifecycle of this object.
	 * @param OnSuccess What to do if the requests receives a successful response.
	 * @param OnError What to do if the request receives an error response.
	 * @param OnComplete What to after either OnSuccess or OnError have finished executing.
	 * @param OutRequestContext The Request Context associated with this request -- used to query information about the request or to cancel it while it's in flight.
	 * @param CallingContext A UObject managed by the UWorld that's making the request. Used to support multiple PIEs (see UBeamUserSlot::GetNamespacedSlotId) and read-only RequestCaches.
	 */
	UFUNCTION(BlueprintCallable, BlueprintInternalUseOnly, Category="Beam|Party|Utils|Make/Break", meta=(DefaultToSelf="CallingContext", AdvancedDisplay="OpHandle,CallingContext",AutoCreateRefTerm="UserSlot,OnSuccess,OnError,OnComplete,OpHandle", BeamFlowFunction))
	void PostParties(FUserSlot UserSlot, UPostPartiesRequest* Request, const FOnPostPartiesSuccess& OnSuccess, const FOnPostPartiesError& OnError, const FOnPostPartiesComplete& OnComplete, FBeamRequestContext& OutRequestContext, FBeamOperationHandle OpHandle = FBeamOperationHandle(), const UObject* CallingContext = nullptr);

		
	/**
	 * @brief Makes an authenticated request to the Put /api/parties/{id}/metadata endpoint of the Party Service.
	 *
	 * @param UserSlot The authenticated UserSlot with the user making the request. 
	 * @param Request The Request UObject. All (de)serialized data the request data creates is tied to the lifecycle of this object.
	 * @param OnSuccess What to do if the requests receives a successful response.
	 * @param OnError What to do if the request receives an error response.
	 * @param OnComplete What to after either OnSuccess or OnError have finished executing.
	 * @param OutRequestContext The Request Context associated with this request -- used to query information about the request or to cancel it while it's in flight.
	 * @param CallingContext A UObject managed by the UWorld that's making the request. Used to support multiple PIEs (see UBeamUserSlot::GetNamespacedSlotId) and read-only RequestCaches.
	 */
	UFUNCTION(BlueprintCallable, BlueprintInternalUseOnly, Category="Beam|Party|Utils|Make/Break", meta=(DefaultToSelf="CallingContext", AdvancedDisplay="OpHandle,CallingContext",AutoCreateRefTerm="UserSlot,OnSuccess,OnError,OnComplete,OpHandle", BeamFlowFunction))
	void PutMetadata(FUserSlot UserSlot, UApiPartyPutMetadataByIdRequest* Request, const FOnApiPartyPutMetadataByIdSuccess& OnSuccess, const FOnApiPartyPutMetadataByIdError& OnError, const FOnApiPartyPutMetadataByIdComplete& OnComplete, FBeamRequestContext& OutRequestContext, FBeamOperationHandle OpHandle = FBeamOperationHandle(), const UObject* CallingContext = nullptr);

		
	/**
	 * @brief Makes an authenticated request to the Get /api/parties/{id} endpoint of the Party Service.
	 *
	 * @param UserSlot The authenticated UserSlot with the user making the request. 
	 * @param Request The Request UObject. All (de)serialized data the request data creates is tied to the lifecycle of this object.
	 * @param OnSuccess What to do if the requests receives a successful response.
	 * @param OnError What to do if the request receives an error response.
	 * @param OnComplete What to after either OnSuccess or OnError have finished executing.
	 * @param OutRequestContext The Request Context associated with this request -- used to query information about the request or to cancel it while it's in flight.
	 * @param CallingContext A UObject managed by the UWorld that's making the request. Used to support multiple PIEs (see UBeamUserSlot::GetNamespacedSlotId) and read-only RequestCaches.
	 */
	UFUNCTION(BlueprintCallable, BlueprintInternalUseOnly, Category="Beam|Party|Utils|Make/Break", meta=(DefaultToSelf="CallingContext", AdvancedDisplay="OpHandle,CallingContext",AutoCreateRefTerm="UserSlot,OnSuccess,OnError,OnComplete,OpHandle", BeamFlowFunction))
	void GetParty(FUserSlot UserSlot, UGetPartyRequest* Request, const FOnGetPartySuccess& OnSuccess, const FOnGetPartyError& OnError, const FOnGetPartyComplete& OnComplete, FBeamRequestContext& OutRequestContext, FBeamOperationHandle OpHandle = FBeamOperationHandle(), const UObject* CallingContext = nullptr);

		
	/**
	 * @brief Makes an authenticated request to the Put /api/parties/{id} endpoint of the Party Service.
	 *
	 * @param UserSlot The authenticated UserSlot with the user making the request. 
	 * @param Request The Request UObject. All (de)serialized data the request data creates is tied to the lifecycle of this object.
	 * @param OnSuccess What to do if the requests receives a successful response.
	 * @param OnError What to do if the request receives an error response.
	 * @param OnComplete What to after either OnSuccess or OnError have finished executing.
	 * @param OutRequestContext The Request Context associated with this request -- used to query information about the request or to cancel it while it's in flight.
	 * @param CallingContext A UObject managed by the UWorld that's making the request. Used to support multiple PIEs (see UBeamUserSlot::GetNamespacedSlotId) and read-only RequestCaches.
	 */
	UFUNCTION(BlueprintCallable, BlueprintInternalUseOnly, Category="Beam|Party|Utils|Make/Break", meta=(DefaultToSelf="CallingContext", AdvancedDisplay="OpHandle,CallingContext",AutoCreateRefTerm="UserSlot,OnSuccess,OnError,OnComplete,OpHandle", BeamFlowFunction))
	void PutParty(FUserSlot UserSlot, UPutPartyRequest* Request, const FOnPutPartySuccess& OnSuccess, const FOnPutPartyError& OnError, const FOnPutPartyComplete& OnComplete, FBeamRequestContext& OutRequestContext, FBeamOperationHandle OpHandle = FBeamOperationHandle(), const UObject* CallingContext = nullptr);

		
	/**
	 * @brief Makes an authenticated request to the Put /api/parties/{id}/promote endpoint of the Party Service.
	 *
	 * @param UserSlot The authenticated UserSlot with the user making the request. 
	 * @param Request The Request UObject. All (de)serialized data the request data creates is tied to the lifecycle of this object.
	 * @param OnSuccess What to do if the requests receives a successful response.
	 * @param OnError What to do if the request receives an error response.
	 * @param OnComplete What to after either OnSuccess or OnError have finished executing.
	 * @param OutRequestContext The Request Context associated with this request -- used to query information about the request or to cancel it while it's in flight.
	 * @param CallingContext A UObject managed by the UWorld that's making the request. Used to support multiple PIEs (see UBeamUserSlot::GetNamespacedSlotId) and read-only RequestCaches.
	 */
	UFUNCTION(BlueprintCallable, BlueprintInternalUseOnly, Category="Beam|Party|Utils|Make/Break", meta=(DefaultToSelf="CallingContext", AdvancedDisplay="OpHandle,CallingContext",AutoCreateRefTerm="UserSlot,OnSuccess,OnError,OnComplete,OpHandle", BeamFlowFunction))
	void PutPromote(FUserSlot UserSlot, UPutPromoteRequest* Request, const FOnPutPromoteSuccess& OnSuccess, const FOnPutPromoteError& OnError, const FOnPutPromoteComplete& OnComplete, FBeamRequestContext& OutRequestContext, FBeamOperationHandle OpHandle = FBeamOperationHandle(), const UObject* CallingContext = nullptr);

		
	/**
	 * @brief Makes an authenticated request to the Post /api/parties/{id}/invite endpoint of the Party Service.
	 *
	 * @param UserSlot The authenticated UserSlot with the user making the request. 
	 * @param Request The Request UObject. All (de)serialized data the request data creates is tied to the lifecycle of this object.
	 * @param OnSuccess What to do if the requests receives a successful response.
	 * @param OnError What to do if the request receives an error response.
	 * @param OnComplete What to after either OnSuccess or OnError have finished executing.
	 * @param OutRequestContext The Request Context associated with this request -- used to query information about the request or to cancel it while it's in flight.
	 * @param CallingContext A UObject managed by the UWorld that's making the request. Used to support multiple PIEs (see UBeamUserSlot::GetNamespacedSlotId) and read-only RequestCaches.
	 */
	UFUNCTION(BlueprintCallable, BlueprintInternalUseOnly, Category="Beam|Party|Utils|Make/Break", meta=(DefaultToSelf="CallingContext", AdvancedDisplay="OpHandle,CallingContext",AutoCreateRefTerm="UserSlot,OnSuccess,OnError,OnComplete,OpHandle", BeamFlowFunction))
	void PostInvite(FUserSlot UserSlot, UApiPartyPostInviteByIdRequest* Request, const FOnApiPartyPostInviteByIdSuccess& OnSuccess, const FOnApiPartyPostInviteByIdError& OnError, const FOnApiPartyPostInviteByIdComplete& OnComplete, FBeamRequestContext& OutRequestContext, FBeamOperationHandle OpHandle = FBeamOperationHandle(), const UObject* CallingContext = nullptr);

		
	/**
	 * @brief Makes an authenticated request to the Delete /api/parties/{id}/invite endpoint of the Party Service.
	 *
	 * @param UserSlot The authenticated UserSlot with the user making the request. 
	 * @param Request The Request UObject. All (de)serialized data the request data creates is tied to the lifecycle of this object.
	 * @param OnSuccess What to do if the requests receives a successful response.
	 * @param OnError What to do if the request receives an error response.
	 * @param OnComplete What to after either OnSuccess or OnError have finished executing.
	 * @param OutRequestContext The Request Context associated with this request -- used to query information about the request or to cancel it while it's in flight.
	 * @param CallingContext A UObject managed by the UWorld that's making the request. Used to support multiple PIEs (see UBeamUserSlot::GetNamespacedSlotId) and read-only RequestCaches.
	 */
	UFUNCTION(BlueprintCallable, BlueprintInternalUseOnly, Category="Beam|Party|Utils|Make/Break", meta=(DefaultToSelf="CallingContext", AdvancedDisplay="OpHandle,CallingContext",AutoCreateRefTerm="UserSlot,OnSuccess,OnError,OnComplete,OpHandle", BeamFlowFunction))
	void DeleteInvite(FUserSlot UserSlot, UDeleteInviteRequest* Request, const FOnDeleteInviteSuccess& OnSuccess, const FOnDeleteInviteError& OnError, const FOnDeleteInviteComplete& OnComplete, FBeamRequestContext& OutRequestContext, FBeamOperationHandle OpHandle = FBeamOperationHandle(), const UObject* CallingContext = nullptr);

		
	/**
	 * @brief Makes an authenticated request to the Delete /api/parties/{id}/members endpoint of the Party Service.
	 *
	 * @param UserSlot The authenticated UserSlot with the user making the request. 
	 * @param Request The Request UObject. All (de)serialized data the request data creates is tied to the lifecycle of this object.
	 * @param OnSuccess What to do if the requests receives a successful response.
	 * @param OnError What to do if the request receives an error response.
	 * @param OnComplete What to after either OnSuccess or OnError have finished executing.
	 * @param OutRequestContext The Request Context associated with this request -- used to query information about the request or to cancel it while it's in flight.
	 * @param CallingContext A UObject managed by the UWorld that's making the request. Used to support multiple PIEs (see UBeamUserSlot::GetNamespacedSlotId) and read-only RequestCaches.
	 */
	UFUNCTION(BlueprintCallable, BlueprintInternalUseOnly, Category="Beam|Party|Utils|Make/Break", meta=(DefaultToSelf="CallingContext", AdvancedDisplay="OpHandle,CallingContext",AutoCreateRefTerm="UserSlot,OnSuccess,OnError,OnComplete,OpHandle", BeamFlowFunction))
	void DeleteMembers(FUserSlot UserSlot, UDeleteMembersRequest* Request, const FOnDeleteMembersSuccess& OnSuccess, const FOnDeleteMembersError& OnError, const FOnDeleteMembersComplete& OnComplete, FBeamRequestContext& OutRequestContext, FBeamOperationHandle OpHandle = FBeamOperationHandle(), const UObject* CallingContext = nullptr);

		
	/**
	 * @brief Makes an authenticated request to the Get /api/players/{playerId}/parties endpoint of the Party Service.
	 *
	 * @param UserSlot The authenticated UserSlot with the user making the request. 
	 * @param Request The Request UObject. All (de)serialized data the request data creates is tied to the lifecycle of this object.
	 * @param OnSuccess What to do if the requests receives a successful response.
	 * @param OnError What to do if the request receives an error response.
	 * @param OnComplete What to after either OnSuccess or OnError have finished executing.
	 * @param OutRequestContext The Request Context associated with this request -- used to query information about the request or to cancel it while it's in flight.
	 * @param CallingContext A UObject managed by the UWorld that's making the request. Used to support multiple PIEs (see UBeamUserSlot::GetNamespacedSlotId) and read-only RequestCaches.
	 */
	UFUNCTION(BlueprintCallable, BlueprintInternalUseOnly, Category="Beam|Party|Utils|Make/Break", meta=(DefaultToSelf="CallingContext", AdvancedDisplay="OpHandle,CallingContext",AutoCreateRefTerm="UserSlot,OnSuccess,OnError,OnComplete,OpHandle", BeamFlowFunction))
	void GetParties(FUserSlot UserSlot, UGetPartiesRequest* Request, const FOnGetPartiesSuccess& OnSuccess, const FOnGetPartiesError& OnError, const FOnGetPartiesComplete& OnComplete, FBeamRequestContext& OutRequestContext, FBeamOperationHandle OpHandle = FBeamOperationHandle(), const UObject* CallingContext = nullptr);

		
	/**
	 * @brief Makes an authenticated request to the Delete /api/players/{playerId}/parties endpoint of the Party Service.
	 *
	 * @param UserSlot The authenticated UserSlot with the user making the request. 
	 * @param Request The Request UObject. All (de)serialized data the request data creates is tied to the lifecycle of this object.
	 * @param OnSuccess What to do if the requests receives a successful response.
	 * @param OnError What to do if the request receives an error response.
	 * @param OnComplete What to after either OnSuccess or OnError have finished executing.
	 * @param OutRequestContext The Request Context associated with this request -- used to query information about the request or to cancel it while it's in flight.
	 * @param CallingContext A UObject managed by the UWorld that's making the request. Used to support multiple PIEs (see UBeamUserSlot::GetNamespacedSlotId) and read-only RequestCaches.
	 */
	UFUNCTION(BlueprintCallable, BlueprintInternalUseOnly, Category="Beam|Party|Utils|Make/Break", meta=(DefaultToSelf="CallingContext", AdvancedDisplay="OpHandle,CallingContext",AutoCreateRefTerm="UserSlot,OnSuccess,OnError,OnComplete,OpHandle", BeamFlowFunction))
	void DeleteParties(FUserSlot UserSlot, UDeletePartiesRequest* Request, const FOnDeletePartiesSuccess& OnSuccess, const FOnDeletePartiesError& OnError, const FOnDeletePartiesComplete& OnComplete, FBeamRequestContext& OutRequestContext, FBeamOperationHandle OpHandle = FBeamOperationHandle(), const UObject* CallingContext = nullptr);

		
	/**
	 * @brief Makes an authenticated request to the Get /api/players/{playerId}/parties/invites endpoint of the Party Service.
	 *
	 * @param UserSlot The authenticated UserSlot with the user making the request. 
	 * @param Request The Request UObject. All (de)serialized data the request data creates is tied to the lifecycle of this object.
	 * @param OnSuccess What to do if the requests receives a successful response.
	 * @param OnError What to do if the request receives an error response.
	 * @param OnComplete What to after either OnSuccess or OnError have finished executing.
	 * @param OutRequestContext The Request Context associated with this request -- used to query information about the request or to cancel it while it's in flight.
	 * @param CallingContext A UObject managed by the UWorld that's making the request. Used to support multiple PIEs (see UBeamUserSlot::GetNamespacedSlotId) and read-only RequestCaches.
	 */
	UFUNCTION(BlueprintCallable, BlueprintInternalUseOnly, Category="Beam|Party|Utils|Make/Break", meta=(DefaultToSelf="CallingContext", AdvancedDisplay="OpHandle,CallingContext",AutoCreateRefTerm="UserSlot,OnSuccess,OnError,OnComplete,OpHandle", BeamFlowFunction))
	void GetPartiesInvites(FUserSlot UserSlot, UGetPartiesInvitesRequest* Request, const FOnGetPartiesInvitesSuccess& OnSuccess, const FOnGetPartiesInvitesError& OnError, const FOnGetPartiesInvitesComplete& OnComplete, FBeamRequestContext& OutRequestContext, FBeamOperationHandle OpHandle = FBeamOperationHandle(), const UObject* CallingContext = nullptr);

		
	/**
	 * @brief Makes an authenticated request to the Get /api/players/{playerId}/party/invites endpoint of the Party Service.
	 *
	 * @param UserSlot The authenticated UserSlot with the user making the request. 
	 * @param Request The Request UObject. All (de)serialized data the request data creates is tied to the lifecycle of this object.
	 * @param OnSuccess What to do if the requests receives a successful response.
	 * @param OnError What to do if the request receives an error response.
	 * @param OnComplete What to after either OnSuccess or OnError have finished executing.
	 * @param OutRequestContext The Request Context associated with this request -- used to query information about the request or to cancel it while it's in flight.
	 * @param CallingContext A UObject managed by the UWorld that's making the request. Used to support multiple PIEs (see UBeamUserSlot::GetNamespacedSlotId) and read-only RequestCaches.
	 */
	UFUNCTION(BlueprintCallable, BlueprintInternalUseOnly, Category="Beam|Party|Utils|Make/Break", meta=(DefaultToSelf="CallingContext", AdvancedDisplay="OpHandle,CallingContext",AutoCreateRefTerm="UserSlot,OnSuccess,OnError,OnComplete,OpHandle", BeamFlowFunction))
	void GetPartyInvites(FUserSlot UserSlot, UGetPartyInvitesRequest* Request, const FOnGetPartyInvitesSuccess& OnSuccess, const FOnGetPartyInvitesError& OnError, const FOnGetPartyInvitesComplete& OnComplete, FBeamRequestContext& OutRequestContext, FBeamOperationHandle OpHandle = FBeamOperationHandle(), const UObject* CallingContext = nullptr);

};
