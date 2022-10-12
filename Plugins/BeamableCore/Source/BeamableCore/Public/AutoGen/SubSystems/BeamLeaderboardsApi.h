

#pragma once

#include "CoreMinimal.h"
#include "BeamBackend.h"

#include "Leaderboards/GetRanksRequest.h"
#include "Leaderboards/GetMatchesRequest.h"
#include "Leaderboards/PutEntryRequest.h"
#include "Leaderboards/GetViewRequest.h"
#include "Leaderboards/BasicLeaderboardsGetListRequest.h"
#include "Leaderboards/GetPlayerRequest.h"
#include "Leaderboards/BasicLeaderboardsGetAssignmentRequest.h"
#include "Leaderboards/GetUidRequest.h"
#include "Leaderboards/DeleteEntriesRequest.h"
#include "Leaderboards/GetMembershipRequest.h"
#include "Leaderboards/GetPartitionRequest.h"
#include "Leaderboards/GetFriendsRequest.h"
#include "Leaderboards/PostLeaderboardsRequest.h"
#include "Leaderboards/DeleteLeaderboardsRequest.h"
#include "Leaderboards/ObjectLeaderboardsGetAssignmentRequest.h"
#include "Leaderboards/DeleteAssignmentRequest.h"
#include "Leaderboards/DeleteEntryRequest.h"
#include "Leaderboards/PutFreezeRequest.h"
#include "Leaderboards/GetDetailsRequest.h"
#include "Leaderboards/PutSwapRequest.h"

#include "BeamLeaderboardsApi.generated.h"


/**
 * Subsystem containing request calls for the Leaderboards service.
 */
UCLASS(BlueprintType)
class BEAMABLECORE_API UBeamLeaderboardsApi : public UEngineSubsystem
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
	void BP_GetRanksImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, FBeamConnectivity& ConnectivityStatus, UGetRanksRequest* RequestData,
	                                const FOnGetRanksSuccess& OnSuccess, const FOnGetRanksError& OnError, const FOnGetRanksComplete& OnComplete,
	                                int64& OutRequestId) const;
	/**
	 * @brief Overload version for binding lambdas when in C++ land. Prefer the BP version whenever possible, this is here mostly for quick experimentation purposes.	 
	 */
	void CPP_GetRanksImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, FBeamConnectivity& ConnectivityStatus, UGetRanksRequest* RequestData,
	                                 const FOnGetRanksFullResponse& Handler) const;

		
	/**
	 * @brief Private implementation that all overloaded BP UFunctions call.	  
	 */
	void BP_GetMatchesImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, FBeamConnectivity& ConnectivityStatus, UGetMatchesRequest* RequestData,
	                                const FOnGetMatchesSuccess& OnSuccess, const FOnGetMatchesError& OnError, const FOnGetMatchesComplete& OnComplete,
	                                int64& OutRequestId) const;
	/**
	 * @brief Overload version for binding lambdas when in C++ land. Prefer the BP version whenever possible, this is here mostly for quick experimentation purposes.	 
	 */
	void CPP_GetMatchesImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, FBeamConnectivity& ConnectivityStatus, UGetMatchesRequest* RequestData,
	                                 const FOnGetMatchesFullResponse& Handler) const;

		
	/**
	 * @brief Private implementation that all overloaded BP UFunctions call.	  
	 */
	void BP_PutEntryImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, FBeamConnectivity& ConnectivityStatus, UPutEntryRequest* RequestData,
	                                const FOnPutEntrySuccess& OnSuccess, const FOnPutEntryError& OnError, const FOnPutEntryComplete& OnComplete,
	                                int64& OutRequestId) const;
	/**
	 * @brief Overload version for binding lambdas when in C++ land. Prefer the BP version whenever possible, this is here mostly for quick experimentation purposes.	 
	 */
	void CPP_PutEntryImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, FBeamConnectivity& ConnectivityStatus, UPutEntryRequest* RequestData,
	                                 const FOnPutEntryFullResponse& Handler) const;

		
	/**
	 * @brief Private implementation that all overloaded BP UFunctions call.	  
	 */
	void BP_GetViewImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, FBeamConnectivity& ConnectivityStatus, UGetViewRequest* RequestData,
	                                const FOnGetViewSuccess& OnSuccess, const FOnGetViewError& OnError, const FOnGetViewComplete& OnComplete,
	                                int64& OutRequestId) const;
	/**
	 * @brief Overload version for binding lambdas when in C++ land. Prefer the BP version whenever possible, this is here mostly for quick experimentation purposes.	 
	 */
	void CPP_GetViewImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, FBeamConnectivity& ConnectivityStatus, UGetViewRequest* RequestData,
	                                 const FOnGetViewFullResponse& Handler) const;


	
	/**
	 * @brief Private implementation for requests that require authentication that all overloaded BP UFunctions call.	  
	 */
	void BP_GetListImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, const FBeamAuthToken& AuthToken, FBeamConnectivity& ConnectivityStatus, UBasicLeaderboardsGetListRequest* RequestData,
	                  const FOnBasicLeaderboardsGetListSuccess& OnSuccess, const FOnBasicLeaderboardsGetListError& OnError, const FOnBasicLeaderboardsGetListComplete& OnComplete, int64& OutRequestId) const;
	/**
	 * @brief Overload version for binding lambdas when in C++ land. Prefer the BP version whenever possible, this is here mostly for quick experimentation purposes.	 
	 */
	void CPP_GetListImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, const FBeamAuthToken& AuthToken, FBeamConnectivity& ConnectivityStatus, UBasicLeaderboardsGetListRequest* RequestData,
	                   const FOnBasicLeaderboardsGetListFullResponse& Handler) const;
		
	/**
	 * @brief Private implementation for requests that require authentication that all overloaded BP UFunctions call.	  
	 */
	void BP_GetPlayerImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, const FBeamAuthToken& AuthToken, FBeamConnectivity& ConnectivityStatus, UGetPlayerRequest* RequestData,
	                  const FOnGetPlayerSuccess& OnSuccess, const FOnGetPlayerError& OnError, const FOnGetPlayerComplete& OnComplete, int64& OutRequestId) const;
	/**
	 * @brief Overload version for binding lambdas when in C++ land. Prefer the BP version whenever possible, this is here mostly for quick experimentation purposes.	 
	 */
	void CPP_GetPlayerImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, const FBeamAuthToken& AuthToken, FBeamConnectivity& ConnectivityStatus, UGetPlayerRequest* RequestData,
	                   const FOnGetPlayerFullResponse& Handler) const;
		
	/**
	 * @brief Private implementation for requests that require authentication that all overloaded BP UFunctions call.	  
	 */
	void BP_BasicLeaderboardsGetAssignmentImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, const FBeamAuthToken& AuthToken, FBeamConnectivity& ConnectivityStatus, UBasicLeaderboardsGetAssignmentRequest* RequestData,
	                  const FOnBasicLeaderboardsGetAssignmentSuccess& OnSuccess, const FOnBasicLeaderboardsGetAssignmentError& OnError, const FOnBasicLeaderboardsGetAssignmentComplete& OnComplete, int64& OutRequestId) const;
	/**
	 * @brief Overload version for binding lambdas when in C++ land. Prefer the BP version whenever possible, this is here mostly for quick experimentation purposes.	 
	 */
	void CPP_BasicLeaderboardsGetAssignmentImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, const FBeamAuthToken& AuthToken, FBeamConnectivity& ConnectivityStatus, UBasicLeaderboardsGetAssignmentRequest* RequestData,
	                   const FOnBasicLeaderboardsGetAssignmentFullResponse& Handler) const;
		
	/**
	 * @brief Private implementation for requests that require authentication that all overloaded BP UFunctions call.	  
	 */
	void BP_GetUidImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, const FBeamAuthToken& AuthToken, FBeamConnectivity& ConnectivityStatus, UGetUidRequest* RequestData,
	                  const FOnGetUidSuccess& OnSuccess, const FOnGetUidError& OnError, const FOnGetUidComplete& OnComplete, int64& OutRequestId) const;
	/**
	 * @brief Overload version for binding lambdas when in C++ land. Prefer the BP version whenever possible, this is here mostly for quick experimentation purposes.	 
	 */
	void CPP_GetUidImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, const FBeamAuthToken& AuthToken, FBeamConnectivity& ConnectivityStatus, UGetUidRequest* RequestData,
	                   const FOnGetUidFullResponse& Handler) const;
		
	/**
	 * @brief Private implementation for requests that require authentication that all overloaded BP UFunctions call.	  
	 */
	void BP_DeleteEntriesImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, const FBeamAuthToken& AuthToken, FBeamConnectivity& ConnectivityStatus, UDeleteEntriesRequest* RequestData,
	                  const FOnDeleteEntriesSuccess& OnSuccess, const FOnDeleteEntriesError& OnError, const FOnDeleteEntriesComplete& OnComplete, int64& OutRequestId) const;
	/**
	 * @brief Overload version for binding lambdas when in C++ land. Prefer the BP version whenever possible, this is here mostly for quick experimentation purposes.	 
	 */
	void CPP_DeleteEntriesImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, const FBeamAuthToken& AuthToken, FBeamConnectivity& ConnectivityStatus, UDeleteEntriesRequest* RequestData,
	                   const FOnDeleteEntriesFullResponse& Handler) const;
		
	/**
	 * @brief Private implementation for requests that require authentication that all overloaded BP UFunctions call.	  
	 */
	void BP_GetMembershipImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, const FBeamAuthToken& AuthToken, FBeamConnectivity& ConnectivityStatus, UGetMembershipRequest* RequestData,
	                  const FOnGetMembershipSuccess& OnSuccess, const FOnGetMembershipError& OnError, const FOnGetMembershipComplete& OnComplete, int64& OutRequestId) const;
	/**
	 * @brief Overload version for binding lambdas when in C++ land. Prefer the BP version whenever possible, this is here mostly for quick experimentation purposes.	 
	 */
	void CPP_GetMembershipImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, const FBeamAuthToken& AuthToken, FBeamConnectivity& ConnectivityStatus, UGetMembershipRequest* RequestData,
	                   const FOnGetMembershipFullResponse& Handler) const;
		
	/**
	 * @brief Private implementation for requests that require authentication that all overloaded BP UFunctions call.	  
	 */
	void BP_GetPartitionImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, const FBeamAuthToken& AuthToken, FBeamConnectivity& ConnectivityStatus, UGetPartitionRequest* RequestData,
	                  const FOnGetPartitionSuccess& OnSuccess, const FOnGetPartitionError& OnError, const FOnGetPartitionComplete& OnComplete, int64& OutRequestId) const;
	/**
	 * @brief Overload version for binding lambdas when in C++ land. Prefer the BP version whenever possible, this is here mostly for quick experimentation purposes.	 
	 */
	void CPP_GetPartitionImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, const FBeamAuthToken& AuthToken, FBeamConnectivity& ConnectivityStatus, UGetPartitionRequest* RequestData,
	                   const FOnGetPartitionFullResponse& Handler) const;
		
	/**
	 * @brief Private implementation for requests that require authentication that all overloaded BP UFunctions call.	  
	 */
	void BP_GetFriendsImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, const FBeamAuthToken& AuthToken, FBeamConnectivity& ConnectivityStatus, UGetFriendsRequest* RequestData,
	                  const FOnGetFriendsSuccess& OnSuccess, const FOnGetFriendsError& OnError, const FOnGetFriendsComplete& OnComplete, int64& OutRequestId) const;
	/**
	 * @brief Overload version for binding lambdas when in C++ land. Prefer the BP version whenever possible, this is here mostly for quick experimentation purposes.	 
	 */
	void CPP_GetFriendsImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, const FBeamAuthToken& AuthToken, FBeamConnectivity& ConnectivityStatus, UGetFriendsRequest* RequestData,
	                   const FOnGetFriendsFullResponse& Handler) const;
		
	/**
	 * @brief Private implementation for requests that require authentication that all overloaded BP UFunctions call.	  
	 */
	void BP_PostLeaderboardsImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, const FBeamAuthToken& AuthToken, FBeamConnectivity& ConnectivityStatus, UPostLeaderboardsRequest* RequestData,
	                  const FOnPostLeaderboardsSuccess& OnSuccess, const FOnPostLeaderboardsError& OnError, const FOnPostLeaderboardsComplete& OnComplete, int64& OutRequestId) const;
	/**
	 * @brief Overload version for binding lambdas when in C++ land. Prefer the BP version whenever possible, this is here mostly for quick experimentation purposes.	 
	 */
	void CPP_PostLeaderboardsImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, const FBeamAuthToken& AuthToken, FBeamConnectivity& ConnectivityStatus, UPostLeaderboardsRequest* RequestData,
	                   const FOnPostLeaderboardsFullResponse& Handler) const;
		
	/**
	 * @brief Private implementation for requests that require authentication that all overloaded BP UFunctions call.	  
	 */
	void BP_DeleteLeaderboardsImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, const FBeamAuthToken& AuthToken, FBeamConnectivity& ConnectivityStatus, UDeleteLeaderboardsRequest* RequestData,
	                  const FOnDeleteLeaderboardsSuccess& OnSuccess, const FOnDeleteLeaderboardsError& OnError, const FOnDeleteLeaderboardsComplete& OnComplete, int64& OutRequestId) const;
	/**
	 * @brief Overload version for binding lambdas when in C++ land. Prefer the BP version whenever possible, this is here mostly for quick experimentation purposes.	 
	 */
	void CPP_DeleteLeaderboardsImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, const FBeamAuthToken& AuthToken, FBeamConnectivity& ConnectivityStatus, UDeleteLeaderboardsRequest* RequestData,
	                   const FOnDeleteLeaderboardsFullResponse& Handler) const;
		
	/**
	 * @brief Private implementation for requests that require authentication that all overloaded BP UFunctions call.	  
	 */
	void BP_ObjectLeaderboardsGetAssignmentImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, const FBeamAuthToken& AuthToken, FBeamConnectivity& ConnectivityStatus, UObjectLeaderboardsGetAssignmentRequest* RequestData,
	                  const FOnObjectLeaderboardsGetAssignmentSuccess& OnSuccess, const FOnObjectLeaderboardsGetAssignmentError& OnError, const FOnObjectLeaderboardsGetAssignmentComplete& OnComplete, int64& OutRequestId) const;
	/**
	 * @brief Overload version for binding lambdas when in C++ land. Prefer the BP version whenever possible, this is here mostly for quick experimentation purposes.	 
	 */
	void CPP_ObjectLeaderboardsGetAssignmentImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, const FBeamAuthToken& AuthToken, FBeamConnectivity& ConnectivityStatus, UObjectLeaderboardsGetAssignmentRequest* RequestData,
	                   const FOnObjectLeaderboardsGetAssignmentFullResponse& Handler) const;
		
	/**
	 * @brief Private implementation for requests that require authentication that all overloaded BP UFunctions call.	  
	 */
	void BP_DeleteAssignmentImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, const FBeamAuthToken& AuthToken, FBeamConnectivity& ConnectivityStatus, UDeleteAssignmentRequest* RequestData,
	                  const FOnDeleteAssignmentSuccess& OnSuccess, const FOnDeleteAssignmentError& OnError, const FOnDeleteAssignmentComplete& OnComplete, int64& OutRequestId) const;
	/**
	 * @brief Overload version for binding lambdas when in C++ land. Prefer the BP version whenever possible, this is here mostly for quick experimentation purposes.	 
	 */
	void CPP_DeleteAssignmentImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, const FBeamAuthToken& AuthToken, FBeamConnectivity& ConnectivityStatus, UDeleteAssignmentRequest* RequestData,
	                   const FOnDeleteAssignmentFullResponse& Handler) const;
		
	/**
	 * @brief Private implementation for requests that require authentication that all overloaded BP UFunctions call.	  
	 */
	void BP_DeleteEntryImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, const FBeamAuthToken& AuthToken, FBeamConnectivity& ConnectivityStatus, UDeleteEntryRequest* RequestData,
	                  const FOnDeleteEntrySuccess& OnSuccess, const FOnDeleteEntryError& OnError, const FOnDeleteEntryComplete& OnComplete, int64& OutRequestId) const;
	/**
	 * @brief Overload version for binding lambdas when in C++ land. Prefer the BP version whenever possible, this is here mostly for quick experimentation purposes.	 
	 */
	void CPP_DeleteEntryImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, const FBeamAuthToken& AuthToken, FBeamConnectivity& ConnectivityStatus, UDeleteEntryRequest* RequestData,
	                   const FOnDeleteEntryFullResponse& Handler) const;
		
	/**
	 * @brief Private implementation for requests that require authentication that all overloaded BP UFunctions call.	  
	 */
	void BP_PutFreezeImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, const FBeamAuthToken& AuthToken, FBeamConnectivity& ConnectivityStatus, UPutFreezeRequest* RequestData,
	                  const FOnPutFreezeSuccess& OnSuccess, const FOnPutFreezeError& OnError, const FOnPutFreezeComplete& OnComplete, int64& OutRequestId) const;
	/**
	 * @brief Overload version for binding lambdas when in C++ land. Prefer the BP version whenever possible, this is here mostly for quick experimentation purposes.	 
	 */
	void CPP_PutFreezeImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, const FBeamAuthToken& AuthToken, FBeamConnectivity& ConnectivityStatus, UPutFreezeRequest* RequestData,
	                   const FOnPutFreezeFullResponse& Handler) const;
		
	/**
	 * @brief Private implementation for requests that require authentication that all overloaded BP UFunctions call.	  
	 */
	void BP_GetDetailsImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, const FBeamAuthToken& AuthToken, FBeamConnectivity& ConnectivityStatus, UGetDetailsRequest* RequestData,
	                  const FOnGetDetailsSuccess& OnSuccess, const FOnGetDetailsError& OnError, const FOnGetDetailsComplete& OnComplete, int64& OutRequestId) const;
	/**
	 * @brief Overload version for binding lambdas when in C++ land. Prefer the BP version whenever possible, this is here mostly for quick experimentation purposes.	 
	 */
	void CPP_GetDetailsImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, const FBeamAuthToken& AuthToken, FBeamConnectivity& ConnectivityStatus, UGetDetailsRequest* RequestData,
	                   const FOnGetDetailsFullResponse& Handler) const;
		
	/**
	 * @brief Private implementation for requests that require authentication that all overloaded BP UFunctions call.	  
	 */
	void BP_PutSwapImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, const FBeamAuthToken& AuthToken, FBeamConnectivity& ConnectivityStatus, UPutSwapRequest* RequestData,
	                  const FOnPutSwapSuccess& OnSuccess, const FOnPutSwapError& OnError, const FOnPutSwapComplete& OnComplete, int64& OutRequestId) const;
	/**
	 * @brief Overload version for binding lambdas when in C++ land. Prefer the BP version whenever possible, this is here mostly for quick experimentation purposes.	 
	 */
	void CPP_PutSwapImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, const FBeamAuthToken& AuthToken, FBeamConnectivity& ConnectivityStatus, UPutSwapRequest* RequestData,
	                   const FOnPutSwapFullResponse& Handler) const;

public:
	
	/** Used by a helper blueprint node so that you can easily chain requests in BP-land. */
	UFUNCTION(BlueprintPure, BlueprintInternalUseOnly)
	static UBeamLeaderboardsApi* GetSelf() { return GEngine->GetEngineSubsystem<UBeamLeaderboardsApi>(); }

	
	/**
	 * @brief Makes a request to the Get /object/leaderboards/{objectId}/ranks endpoint of the Leaderboards Service.
	 *
	 * PREFER THE UFUNCTION OVERLOAD AS OPPOSED TO THIS. THIS MAINLY EXISTS TO ALLOW LAMBDA BINDING THE HANDLER.
	 * (Dynamic delegates do not allow for that so... we autogen this one to make experimenting in CPP a bit faster and for whenever you need to capture variables).
	 * 
	 * @param Request The Request UObject. All (de)serialized data the request data creates is tied to the lifecycle of this object.
	 * @param Handler A callback that defines how to handle success, error and completion. 
	 */
	void CPP_GetRanks(UGetRanksRequest* Request, const FOnGetRanksFullResponse& Handler) const;

		
	/**
	 * @brief Makes a request to the Get /object/leaderboards/{objectId}/matches endpoint of the Leaderboards Service.
	 *
	 * PREFER THE UFUNCTION OVERLOAD AS OPPOSED TO THIS. THIS MAINLY EXISTS TO ALLOW LAMBDA BINDING THE HANDLER.
	 * (Dynamic delegates do not allow for that so... we autogen this one to make experimenting in CPP a bit faster and for whenever you need to capture variables).
	 * 
	 * @param Request The Request UObject. All (de)serialized data the request data creates is tied to the lifecycle of this object.
	 * @param Handler A callback that defines how to handle success, error and completion. 
	 */
	void CPP_GetMatches(UGetMatchesRequest* Request, const FOnGetMatchesFullResponse& Handler) const;

		
	/**
	 * @brief Makes a request to the Put /object/leaderboards/{objectId}/entry endpoint of the Leaderboards Service.
	 *
	 * PREFER THE UFUNCTION OVERLOAD AS OPPOSED TO THIS. THIS MAINLY EXISTS TO ALLOW LAMBDA BINDING THE HANDLER.
	 * (Dynamic delegates do not allow for that so... we autogen this one to make experimenting in CPP a bit faster and for whenever you need to capture variables).
	 * 
	 * @param Request The Request UObject. All (de)serialized data the request data creates is tied to the lifecycle of this object.
	 * @param Handler A callback that defines how to handle success, error and completion. 
	 */
	void CPP_PutEntry(UPutEntryRequest* Request, const FOnPutEntryFullResponse& Handler) const;

		
	/**
	 * @brief Makes a request to the Get /object/leaderboards/{objectId}/view endpoint of the Leaderboards Service.
	 *
	 * PREFER THE UFUNCTION OVERLOAD AS OPPOSED TO THIS. THIS MAINLY EXISTS TO ALLOW LAMBDA BINDING THE HANDLER.
	 * (Dynamic delegates do not allow for that so... we autogen this one to make experimenting in CPP a bit faster and for whenever you need to capture variables).
	 * 
	 * @param Request The Request UObject. All (de)serialized data the request data creates is tied to the lifecycle of this object.
	 * @param Handler A callback that defines how to handle success, error and completion. 
	 */
	void CPP_GetView(UGetViewRequest* Request, const FOnGetViewFullResponse& Handler) const;


	
	/**
	 * @brief Makes an authenticated request to the Get /basic/leaderboards/list endpoint of the Leaderboards Service.
	 *
	 * PREFER THE UFUNCTION OVERLOAD AS OPPOSED TO THIS. THIS MAINLY EXISTS TO ALLOW LAMBDA BINDING THE HANDLER.
	 * (Dynamic delegates do not allow for that so... we autogen this one to make experimenting in CPP a bit faster).
	 * 
	 * @param UserSlot The Authenticated User Slot that is making this request.
	 * @param Request The Request UObject. All (de)serialized data the request data creates is tied to the lifecycle of this object.
	 * @param Handler A callback that defines how to handle success, error and completion. 
	 */
	void CPP_GetList(const FUserSlot& UserSlot, UBasicLeaderboardsGetListRequest* Request, const FOnBasicLeaderboardsGetListFullResponse& Handler) const;

		
	/**
	 * @brief Makes an authenticated request to the Get /basic/leaderboards/player endpoint of the Leaderboards Service.
	 *
	 * PREFER THE UFUNCTION OVERLOAD AS OPPOSED TO THIS. THIS MAINLY EXISTS TO ALLOW LAMBDA BINDING THE HANDLER.
	 * (Dynamic delegates do not allow for that so... we autogen this one to make experimenting in CPP a bit faster).
	 * 
	 * @param UserSlot The Authenticated User Slot that is making this request.
	 * @param Request The Request UObject. All (de)serialized data the request data creates is tied to the lifecycle of this object.
	 * @param Handler A callback that defines how to handle success, error and completion. 
	 */
	void CPP_GetPlayer(const FUserSlot& UserSlot, UGetPlayerRequest* Request, const FOnGetPlayerFullResponse& Handler) const;

		
	/**
	 * @brief Makes an authenticated request to the Get /basic/leaderboards/assignment endpoint of the Leaderboards Service.
	 *
	 * PREFER THE UFUNCTION OVERLOAD AS OPPOSED TO THIS. THIS MAINLY EXISTS TO ALLOW LAMBDA BINDING THE HANDLER.
	 * (Dynamic delegates do not allow for that so... we autogen this one to make experimenting in CPP a bit faster).
	 * 
	 * @param UserSlot The Authenticated User Slot that is making this request.
	 * @param Request The Request UObject. All (de)serialized data the request data creates is tied to the lifecycle of this object.
	 * @param Handler A callback that defines how to handle success, error and completion. 
	 */
	void CPP_BasicLeaderboardsGetAssignment(const FUserSlot& UserSlot, UBasicLeaderboardsGetAssignmentRequest* Request, const FOnBasicLeaderboardsGetAssignmentFullResponse& Handler) const;

		
	/**
	 * @brief Makes an authenticated request to the Get /basic/leaderboards/uid endpoint of the Leaderboards Service.
	 *
	 * PREFER THE UFUNCTION OVERLOAD AS OPPOSED TO THIS. THIS MAINLY EXISTS TO ALLOW LAMBDA BINDING THE HANDLER.
	 * (Dynamic delegates do not allow for that so... we autogen this one to make experimenting in CPP a bit faster).
	 * 
	 * @param UserSlot The Authenticated User Slot that is making this request.
	 * @param Request The Request UObject. All (de)serialized data the request data creates is tied to the lifecycle of this object.
	 * @param Handler A callback that defines how to handle success, error and completion. 
	 */
	void CPP_GetUid(const FUserSlot& UserSlot, UGetUidRequest* Request, const FOnGetUidFullResponse& Handler) const;

		
	/**
	 * @brief Makes an authenticated request to the Delete /object/leaderboards/{objectId}/entries endpoint of the Leaderboards Service.
	 *
	 * PREFER THE UFUNCTION OVERLOAD AS OPPOSED TO THIS. THIS MAINLY EXISTS TO ALLOW LAMBDA BINDING THE HANDLER.
	 * (Dynamic delegates do not allow for that so... we autogen this one to make experimenting in CPP a bit faster).
	 * 
	 * @param UserSlot The Authenticated User Slot that is making this request.
	 * @param Request The Request UObject. All (de)serialized data the request data creates is tied to the lifecycle of this object.
	 * @param Handler A callback that defines how to handle success, error and completion. 
	 */
	void CPP_DeleteEntries(const FUserSlot& UserSlot, UDeleteEntriesRequest* Request, const FOnDeleteEntriesFullResponse& Handler) const;

		
	/**
	 * @brief Makes an authenticated request to the Get /object/leaderboards/{objectId}/membership endpoint of the Leaderboards Service.
	 *
	 * PREFER THE UFUNCTION OVERLOAD AS OPPOSED TO THIS. THIS MAINLY EXISTS TO ALLOW LAMBDA BINDING THE HANDLER.
	 * (Dynamic delegates do not allow for that so... we autogen this one to make experimenting in CPP a bit faster).
	 * 
	 * @param UserSlot The Authenticated User Slot that is making this request.
	 * @param Request The Request UObject. All (de)serialized data the request data creates is tied to the lifecycle of this object.
	 * @param Handler A callback that defines how to handle success, error and completion. 
	 */
	void CPP_GetMembership(const FUserSlot& UserSlot, UGetMembershipRequest* Request, const FOnGetMembershipFullResponse& Handler) const;

		
	/**
	 * @brief Makes an authenticated request to the Get /object/leaderboards/{objectId}/partition endpoint of the Leaderboards Service.
	 *
	 * PREFER THE UFUNCTION OVERLOAD AS OPPOSED TO THIS. THIS MAINLY EXISTS TO ALLOW LAMBDA BINDING THE HANDLER.
	 * (Dynamic delegates do not allow for that so... we autogen this one to make experimenting in CPP a bit faster).
	 * 
	 * @param UserSlot The Authenticated User Slot that is making this request.
	 * @param Request The Request UObject. All (de)serialized data the request data creates is tied to the lifecycle of this object.
	 * @param Handler A callback that defines how to handle success, error and completion. 
	 */
	void CPP_GetPartition(const FUserSlot& UserSlot, UGetPartitionRequest* Request, const FOnGetPartitionFullResponse& Handler) const;

		
	/**
	 * @brief Makes an authenticated request to the Get /object/leaderboards/{objectId}/friends endpoint of the Leaderboards Service.
	 *
	 * PREFER THE UFUNCTION OVERLOAD AS OPPOSED TO THIS. THIS MAINLY EXISTS TO ALLOW LAMBDA BINDING THE HANDLER.
	 * (Dynamic delegates do not allow for that so... we autogen this one to make experimenting in CPP a bit faster).
	 * 
	 * @param UserSlot The Authenticated User Slot that is making this request.
	 * @param Request The Request UObject. All (de)serialized data the request data creates is tied to the lifecycle of this object.
	 * @param Handler A callback that defines how to handle success, error and completion. 
	 */
	void CPP_GetFriends(const FUserSlot& UserSlot, UGetFriendsRequest* Request, const FOnGetFriendsFullResponse& Handler) const;

		
	/**
	 * @brief Makes an authenticated request to the Post /object/leaderboards/{objectId}/ endpoint of the Leaderboards Service.
	 *
	 * PREFER THE UFUNCTION OVERLOAD AS OPPOSED TO THIS. THIS MAINLY EXISTS TO ALLOW LAMBDA BINDING THE HANDLER.
	 * (Dynamic delegates do not allow for that so... we autogen this one to make experimenting in CPP a bit faster).
	 * 
	 * @param UserSlot The Authenticated User Slot that is making this request.
	 * @param Request The Request UObject. All (de)serialized data the request data creates is tied to the lifecycle of this object.
	 * @param Handler A callback that defines how to handle success, error and completion. 
	 */
	void CPP_PostLeaderboards(const FUserSlot& UserSlot, UPostLeaderboardsRequest* Request, const FOnPostLeaderboardsFullResponse& Handler) const;

		
	/**
	 * @brief Makes an authenticated request to the Delete /object/leaderboards/{objectId}/ endpoint of the Leaderboards Service.
	 *
	 * PREFER THE UFUNCTION OVERLOAD AS OPPOSED TO THIS. THIS MAINLY EXISTS TO ALLOW LAMBDA BINDING THE HANDLER.
	 * (Dynamic delegates do not allow for that so... we autogen this one to make experimenting in CPP a bit faster).
	 * 
	 * @param UserSlot The Authenticated User Slot that is making this request.
	 * @param Request The Request UObject. All (de)serialized data the request data creates is tied to the lifecycle of this object.
	 * @param Handler A callback that defines how to handle success, error and completion. 
	 */
	void CPP_DeleteLeaderboards(const FUserSlot& UserSlot, UDeleteLeaderboardsRequest* Request, const FOnDeleteLeaderboardsFullResponse& Handler) const;

		
	/**
	 * @brief Makes an authenticated request to the Get /object/leaderboards/{objectId}/assignment endpoint of the Leaderboards Service.
	 *
	 * PREFER THE UFUNCTION OVERLOAD AS OPPOSED TO THIS. THIS MAINLY EXISTS TO ALLOW LAMBDA BINDING THE HANDLER.
	 * (Dynamic delegates do not allow for that so... we autogen this one to make experimenting in CPP a bit faster).
	 * 
	 * @param UserSlot The Authenticated User Slot that is making this request.
	 * @param Request The Request UObject. All (de)serialized data the request data creates is tied to the lifecycle of this object.
	 * @param Handler A callback that defines how to handle success, error and completion. 
	 */
	void CPP_ObjectLeaderboardsGetAssignment(const FUserSlot& UserSlot, UObjectLeaderboardsGetAssignmentRequest* Request, const FOnObjectLeaderboardsGetAssignmentFullResponse& Handler) const;

		
	/**
	 * @brief Makes an authenticated request to the Delete /object/leaderboards/{objectId}/assignment endpoint of the Leaderboards Service.
	 *
	 * PREFER THE UFUNCTION OVERLOAD AS OPPOSED TO THIS. THIS MAINLY EXISTS TO ALLOW LAMBDA BINDING THE HANDLER.
	 * (Dynamic delegates do not allow for that so... we autogen this one to make experimenting in CPP a bit faster).
	 * 
	 * @param UserSlot The Authenticated User Slot that is making this request.
	 * @param Request The Request UObject. All (de)serialized data the request data creates is tied to the lifecycle of this object.
	 * @param Handler A callback that defines how to handle success, error and completion. 
	 */
	void CPP_DeleteAssignment(const FUserSlot& UserSlot, UDeleteAssignmentRequest* Request, const FOnDeleteAssignmentFullResponse& Handler) const;

		
	/**
	 * @brief Makes an authenticated request to the Delete /object/leaderboards/{objectId}/entry endpoint of the Leaderboards Service.
	 *
	 * PREFER THE UFUNCTION OVERLOAD AS OPPOSED TO THIS. THIS MAINLY EXISTS TO ALLOW LAMBDA BINDING THE HANDLER.
	 * (Dynamic delegates do not allow for that so... we autogen this one to make experimenting in CPP a bit faster).
	 * 
	 * @param UserSlot The Authenticated User Slot that is making this request.
	 * @param Request The Request UObject. All (de)serialized data the request data creates is tied to the lifecycle of this object.
	 * @param Handler A callback that defines how to handle success, error and completion. 
	 */
	void CPP_DeleteEntry(const FUserSlot& UserSlot, UDeleteEntryRequest* Request, const FOnDeleteEntryFullResponse& Handler) const;

		
	/**
	 * @brief Makes an authenticated request to the Put /object/leaderboards/{objectId}/freeze endpoint of the Leaderboards Service.
	 *
	 * PREFER THE UFUNCTION OVERLOAD AS OPPOSED TO THIS. THIS MAINLY EXISTS TO ALLOW LAMBDA BINDING THE HANDLER.
	 * (Dynamic delegates do not allow for that so... we autogen this one to make experimenting in CPP a bit faster).
	 * 
	 * @param UserSlot The Authenticated User Slot that is making this request.
	 * @param Request The Request UObject. All (de)serialized data the request data creates is tied to the lifecycle of this object.
	 * @param Handler A callback that defines how to handle success, error and completion. 
	 */
	void CPP_PutFreeze(const FUserSlot& UserSlot, UPutFreezeRequest* Request, const FOnPutFreezeFullResponse& Handler) const;

		
	/**
	 * @brief Makes an authenticated request to the Get /object/leaderboards/{objectId}/details endpoint of the Leaderboards Service.
	 *
	 * PREFER THE UFUNCTION OVERLOAD AS OPPOSED TO THIS. THIS MAINLY EXISTS TO ALLOW LAMBDA BINDING THE HANDLER.
	 * (Dynamic delegates do not allow for that so... we autogen this one to make experimenting in CPP a bit faster).
	 * 
	 * @param UserSlot The Authenticated User Slot that is making this request.
	 * @param Request The Request UObject. All (de)serialized data the request data creates is tied to the lifecycle of this object.
	 * @param Handler A callback that defines how to handle success, error and completion. 
	 */
	void CPP_GetDetails(const FUserSlot& UserSlot, UGetDetailsRequest* Request, const FOnGetDetailsFullResponse& Handler) const;

		
	/**
	 * @brief Makes an authenticated request to the Put /object/leaderboards/{objectId}/swap endpoint of the Leaderboards Service.
	 *
	 * PREFER THE UFUNCTION OVERLOAD AS OPPOSED TO THIS. THIS MAINLY EXISTS TO ALLOW LAMBDA BINDING THE HANDLER.
	 * (Dynamic delegates do not allow for that so... we autogen this one to make experimenting in CPP a bit faster).
	 * 
	 * @param UserSlot The Authenticated User Slot that is making this request.
	 * @param Request The Request UObject. All (de)serialized data the request data creates is tied to the lifecycle of this object.
	 * @param Handler A callback that defines how to handle success, error and completion. 
	 */
	void CPP_PutSwap(const FUserSlot& UserSlot, UPutSwapRequest* Request, const FOnPutSwapFullResponse& Handler) const;


	
	/**
	 * @brief Makes a request to the Get /object/leaderboards/{objectId}/ranks endpoint of the Leaderboards Service.
	 *
	 * @param Request The Request UObject. All (de)serialized data the request data creates is tied to the lifecycle of this object.
	 * @param OnSuccess What to do if the requests receives a successful response.
	 * @param OnError What to do if the request receives an error response.
	 * @param OnComplete What to after either OnSuccess or OnError have finished executing.
	 * @param OutRequestId The Request Id -- used to query information about the request or to cancel it while it's in flight. 
	 */
	UFUNCTION(BlueprintCallable, Category="Beam|APIs|Leaderboards", meta=(AutoCreateRefTerm="OnSuccess,OnError,OnComplete"))
	void GetRanks(UGetRanksRequest* Request, const FOnGetRanksSuccess& OnSuccess, const FOnGetRanksError& OnError, const FOnGetRanksComplete& OnComplete,
								 int64& OutRequestId);

		
	/**
	 * @brief Makes a request to the Get /object/leaderboards/{objectId}/matches endpoint of the Leaderboards Service.
	 *
	 * @param Request The Request UObject. All (de)serialized data the request data creates is tied to the lifecycle of this object.
	 * @param OnSuccess What to do if the requests receives a successful response.
	 * @param OnError What to do if the request receives an error response.
	 * @param OnComplete What to after either OnSuccess or OnError have finished executing.
	 * @param OutRequestId The Request Id -- used to query information about the request or to cancel it while it's in flight. 
	 */
	UFUNCTION(BlueprintCallable, Category="Beam|APIs|Leaderboards", meta=(AutoCreateRefTerm="OnSuccess,OnError,OnComplete"))
	void GetMatches(UGetMatchesRequest* Request, const FOnGetMatchesSuccess& OnSuccess, const FOnGetMatchesError& OnError, const FOnGetMatchesComplete& OnComplete,
								 int64& OutRequestId);

		
	/**
	 * @brief Makes a request to the Put /object/leaderboards/{objectId}/entry endpoint of the Leaderboards Service.
	 *
	 * @param Request The Request UObject. All (de)serialized data the request data creates is tied to the lifecycle of this object.
	 * @param OnSuccess What to do if the requests receives a successful response.
	 * @param OnError What to do if the request receives an error response.
	 * @param OnComplete What to after either OnSuccess or OnError have finished executing.
	 * @param OutRequestId The Request Id -- used to query information about the request or to cancel it while it's in flight. 
	 */
	UFUNCTION(BlueprintCallable, Category="Beam|APIs|Leaderboards", meta=(AutoCreateRefTerm="OnSuccess,OnError,OnComplete"))
	void PutEntry(UPutEntryRequest* Request, const FOnPutEntrySuccess& OnSuccess, const FOnPutEntryError& OnError, const FOnPutEntryComplete& OnComplete,
								 int64& OutRequestId);

		
	/**
	 * @brief Makes a request to the Get /object/leaderboards/{objectId}/view endpoint of the Leaderboards Service.
	 *
	 * @param Request The Request UObject. All (de)serialized data the request data creates is tied to the lifecycle of this object.
	 * @param OnSuccess What to do if the requests receives a successful response.
	 * @param OnError What to do if the request receives an error response.
	 * @param OnComplete What to after either OnSuccess or OnError have finished executing.
	 * @param OutRequestId The Request Id -- used to query information about the request or to cancel it while it's in flight. 
	 */
	UFUNCTION(BlueprintCallable, Category="Beam|APIs|Leaderboards", meta=(AutoCreateRefTerm="OnSuccess,OnError,OnComplete"))
	void GetView(UGetViewRequest* Request, const FOnGetViewSuccess& OnSuccess, const FOnGetViewError& OnError, const FOnGetViewComplete& OnComplete,
								 int64& OutRequestId);


	
	/**
	 * @brief Makes an authenticated request to the Get /basic/leaderboards/list endpoint of the Leaderboards Service.
	 *
	 * @param UserSlot The authenticated UserSlot with the user making the request. 
	 * @param Request The Request UObject. All (de)serialized data the request data creates is tied to the lifecycle of this object.
	 * @param OnSuccess What to do if the requests receives a successful response.
	 * @param OnError What to do if the request receives an error response.
	 * @param OnComplete What to after either OnSuccess or OnError have finished executing.
	 * @param OutRequestId The Request Id -- used to query information about the request or to cancel it while it's in flight. 
	 */
	UFUNCTION(BlueprintCallable, Category="Beam|APIs|Leaderboards", meta=(AutoCreateRefTerm="UserSlot,OnSuccess,OnError,OnComplete"))
	void GetList(const FUserSlot& UserSlot, UBasicLeaderboardsGetListRequest* Request, const FOnBasicLeaderboardsGetListSuccess& OnSuccess, const FOnBasicLeaderboardsGetListError& OnError, const FOnBasicLeaderboardsGetListComplete& OnComplete, int64& OutRequestId);

		
	/**
	 * @brief Makes an authenticated request to the Get /basic/leaderboards/player endpoint of the Leaderboards Service.
	 *
	 * @param UserSlot The authenticated UserSlot with the user making the request. 
	 * @param Request The Request UObject. All (de)serialized data the request data creates is tied to the lifecycle of this object.
	 * @param OnSuccess What to do if the requests receives a successful response.
	 * @param OnError What to do if the request receives an error response.
	 * @param OnComplete What to after either OnSuccess or OnError have finished executing.
	 * @param OutRequestId The Request Id -- used to query information about the request or to cancel it while it's in flight. 
	 */
	UFUNCTION(BlueprintCallable, Category="Beam|APIs|Leaderboards", meta=(AutoCreateRefTerm="UserSlot,OnSuccess,OnError,OnComplete"))
	void GetPlayer(const FUserSlot& UserSlot, UGetPlayerRequest* Request, const FOnGetPlayerSuccess& OnSuccess, const FOnGetPlayerError& OnError, const FOnGetPlayerComplete& OnComplete, int64& OutRequestId);

		
	/**
	 * @brief Makes an authenticated request to the Get /basic/leaderboards/assignment endpoint of the Leaderboards Service.
	 *
	 * @param UserSlot The authenticated UserSlot with the user making the request. 
	 * @param Request The Request UObject. All (de)serialized data the request data creates is tied to the lifecycle of this object.
	 * @param OnSuccess What to do if the requests receives a successful response.
	 * @param OnError What to do if the request receives an error response.
	 * @param OnComplete What to after either OnSuccess or OnError have finished executing.
	 * @param OutRequestId The Request Id -- used to query information about the request or to cancel it while it's in flight. 
	 */
	UFUNCTION(BlueprintCallable, Category="Beam|APIs|Leaderboards", meta=(AutoCreateRefTerm="UserSlot,OnSuccess,OnError,OnComplete"))
	void BasicLeaderboardsGetAssignment(const FUserSlot& UserSlot, UBasicLeaderboardsGetAssignmentRequest* Request, const FOnBasicLeaderboardsGetAssignmentSuccess& OnSuccess, const FOnBasicLeaderboardsGetAssignmentError& OnError, const FOnBasicLeaderboardsGetAssignmentComplete& OnComplete, int64& OutRequestId);

		
	/**
	 * @brief Makes an authenticated request to the Get /basic/leaderboards/uid endpoint of the Leaderboards Service.
	 *
	 * @param UserSlot The authenticated UserSlot with the user making the request. 
	 * @param Request The Request UObject. All (de)serialized data the request data creates is tied to the lifecycle of this object.
	 * @param OnSuccess What to do if the requests receives a successful response.
	 * @param OnError What to do if the request receives an error response.
	 * @param OnComplete What to after either OnSuccess or OnError have finished executing.
	 * @param OutRequestId The Request Id -- used to query information about the request or to cancel it while it's in flight. 
	 */
	UFUNCTION(BlueprintCallable, Category="Beam|APIs|Leaderboards", meta=(AutoCreateRefTerm="UserSlot,OnSuccess,OnError,OnComplete"))
	void GetUid(const FUserSlot& UserSlot, UGetUidRequest* Request, const FOnGetUidSuccess& OnSuccess, const FOnGetUidError& OnError, const FOnGetUidComplete& OnComplete, int64& OutRequestId);

		
	/**
	 * @brief Makes an authenticated request to the Delete /object/leaderboards/{objectId}/entries endpoint of the Leaderboards Service.
	 *
	 * @param UserSlot The authenticated UserSlot with the user making the request. 
	 * @param Request The Request UObject. All (de)serialized data the request data creates is tied to the lifecycle of this object.
	 * @param OnSuccess What to do if the requests receives a successful response.
	 * @param OnError What to do if the request receives an error response.
	 * @param OnComplete What to after either OnSuccess or OnError have finished executing.
	 * @param OutRequestId The Request Id -- used to query information about the request or to cancel it while it's in flight. 
	 */
	UFUNCTION(BlueprintCallable, Category="Beam|APIs|Leaderboards", meta=(AutoCreateRefTerm="UserSlot,OnSuccess,OnError,OnComplete"))
	void DeleteEntries(const FUserSlot& UserSlot, UDeleteEntriesRequest* Request, const FOnDeleteEntriesSuccess& OnSuccess, const FOnDeleteEntriesError& OnError, const FOnDeleteEntriesComplete& OnComplete, int64& OutRequestId);

		
	/**
	 * @brief Makes an authenticated request to the Get /object/leaderboards/{objectId}/membership endpoint of the Leaderboards Service.
	 *
	 * @param UserSlot The authenticated UserSlot with the user making the request. 
	 * @param Request The Request UObject. All (de)serialized data the request data creates is tied to the lifecycle of this object.
	 * @param OnSuccess What to do if the requests receives a successful response.
	 * @param OnError What to do if the request receives an error response.
	 * @param OnComplete What to after either OnSuccess or OnError have finished executing.
	 * @param OutRequestId The Request Id -- used to query information about the request or to cancel it while it's in flight. 
	 */
	UFUNCTION(BlueprintCallable, Category="Beam|APIs|Leaderboards", meta=(AutoCreateRefTerm="UserSlot,OnSuccess,OnError,OnComplete"))
	void GetMembership(const FUserSlot& UserSlot, UGetMembershipRequest* Request, const FOnGetMembershipSuccess& OnSuccess, const FOnGetMembershipError& OnError, const FOnGetMembershipComplete& OnComplete, int64& OutRequestId);

		
	/**
	 * @brief Makes an authenticated request to the Get /object/leaderboards/{objectId}/partition endpoint of the Leaderboards Service.
	 *
	 * @param UserSlot The authenticated UserSlot with the user making the request. 
	 * @param Request The Request UObject. All (de)serialized data the request data creates is tied to the lifecycle of this object.
	 * @param OnSuccess What to do if the requests receives a successful response.
	 * @param OnError What to do if the request receives an error response.
	 * @param OnComplete What to after either OnSuccess or OnError have finished executing.
	 * @param OutRequestId The Request Id -- used to query information about the request or to cancel it while it's in flight. 
	 */
	UFUNCTION(BlueprintCallable, Category="Beam|APIs|Leaderboards", meta=(AutoCreateRefTerm="UserSlot,OnSuccess,OnError,OnComplete"))
	void GetPartition(const FUserSlot& UserSlot, UGetPartitionRequest* Request, const FOnGetPartitionSuccess& OnSuccess, const FOnGetPartitionError& OnError, const FOnGetPartitionComplete& OnComplete, int64& OutRequestId);

		
	/**
	 * @brief Makes an authenticated request to the Get /object/leaderboards/{objectId}/friends endpoint of the Leaderboards Service.
	 *
	 * @param UserSlot The authenticated UserSlot with the user making the request. 
	 * @param Request The Request UObject. All (de)serialized data the request data creates is tied to the lifecycle of this object.
	 * @param OnSuccess What to do if the requests receives a successful response.
	 * @param OnError What to do if the request receives an error response.
	 * @param OnComplete What to after either OnSuccess or OnError have finished executing.
	 * @param OutRequestId The Request Id -- used to query information about the request or to cancel it while it's in flight. 
	 */
	UFUNCTION(BlueprintCallable, Category="Beam|APIs|Leaderboards", meta=(AutoCreateRefTerm="UserSlot,OnSuccess,OnError,OnComplete"))
	void GetFriends(const FUserSlot& UserSlot, UGetFriendsRequest* Request, const FOnGetFriendsSuccess& OnSuccess, const FOnGetFriendsError& OnError, const FOnGetFriendsComplete& OnComplete, int64& OutRequestId);

		
	/**
	 * @brief Makes an authenticated request to the Post /object/leaderboards/{objectId}/ endpoint of the Leaderboards Service.
	 *
	 * @param UserSlot The authenticated UserSlot with the user making the request. 
	 * @param Request The Request UObject. All (de)serialized data the request data creates is tied to the lifecycle of this object.
	 * @param OnSuccess What to do if the requests receives a successful response.
	 * @param OnError What to do if the request receives an error response.
	 * @param OnComplete What to after either OnSuccess or OnError have finished executing.
	 * @param OutRequestId The Request Id -- used to query information about the request or to cancel it while it's in flight. 
	 */
	UFUNCTION(BlueprintCallable, Category="Beam|APIs|Leaderboards", meta=(AutoCreateRefTerm="UserSlot,OnSuccess,OnError,OnComplete"))
	void PostLeaderboards(const FUserSlot& UserSlot, UPostLeaderboardsRequest* Request, const FOnPostLeaderboardsSuccess& OnSuccess, const FOnPostLeaderboardsError& OnError, const FOnPostLeaderboardsComplete& OnComplete, int64& OutRequestId);

		
	/**
	 * @brief Makes an authenticated request to the Delete /object/leaderboards/{objectId}/ endpoint of the Leaderboards Service.
	 *
	 * @param UserSlot The authenticated UserSlot with the user making the request. 
	 * @param Request The Request UObject. All (de)serialized data the request data creates is tied to the lifecycle of this object.
	 * @param OnSuccess What to do if the requests receives a successful response.
	 * @param OnError What to do if the request receives an error response.
	 * @param OnComplete What to after either OnSuccess or OnError have finished executing.
	 * @param OutRequestId The Request Id -- used to query information about the request or to cancel it while it's in flight. 
	 */
	UFUNCTION(BlueprintCallable, Category="Beam|APIs|Leaderboards", meta=(AutoCreateRefTerm="UserSlot,OnSuccess,OnError,OnComplete"))
	void DeleteLeaderboards(const FUserSlot& UserSlot, UDeleteLeaderboardsRequest* Request, const FOnDeleteLeaderboardsSuccess& OnSuccess, const FOnDeleteLeaderboardsError& OnError, const FOnDeleteLeaderboardsComplete& OnComplete, int64& OutRequestId);

		
	/**
	 * @brief Makes an authenticated request to the Get /object/leaderboards/{objectId}/assignment endpoint of the Leaderboards Service.
	 *
	 * @param UserSlot The authenticated UserSlot with the user making the request. 
	 * @param Request The Request UObject. All (de)serialized data the request data creates is tied to the lifecycle of this object.
	 * @param OnSuccess What to do if the requests receives a successful response.
	 * @param OnError What to do if the request receives an error response.
	 * @param OnComplete What to after either OnSuccess or OnError have finished executing.
	 * @param OutRequestId The Request Id -- used to query information about the request or to cancel it while it's in flight. 
	 */
	UFUNCTION(BlueprintCallable, Category="Beam|APIs|Leaderboards", meta=(AutoCreateRefTerm="UserSlot,OnSuccess,OnError,OnComplete"))
	void ObjectLeaderboardsGetAssignment(const FUserSlot& UserSlot, UObjectLeaderboardsGetAssignmentRequest* Request, const FOnObjectLeaderboardsGetAssignmentSuccess& OnSuccess, const FOnObjectLeaderboardsGetAssignmentError& OnError, const FOnObjectLeaderboardsGetAssignmentComplete& OnComplete, int64& OutRequestId);

		
	/**
	 * @brief Makes an authenticated request to the Delete /object/leaderboards/{objectId}/assignment endpoint of the Leaderboards Service.
	 *
	 * @param UserSlot The authenticated UserSlot with the user making the request. 
	 * @param Request The Request UObject. All (de)serialized data the request data creates is tied to the lifecycle of this object.
	 * @param OnSuccess What to do if the requests receives a successful response.
	 * @param OnError What to do if the request receives an error response.
	 * @param OnComplete What to after either OnSuccess or OnError have finished executing.
	 * @param OutRequestId The Request Id -- used to query information about the request or to cancel it while it's in flight. 
	 */
	UFUNCTION(BlueprintCallable, Category="Beam|APIs|Leaderboards", meta=(AutoCreateRefTerm="UserSlot,OnSuccess,OnError,OnComplete"))
	void DeleteAssignment(const FUserSlot& UserSlot, UDeleteAssignmentRequest* Request, const FOnDeleteAssignmentSuccess& OnSuccess, const FOnDeleteAssignmentError& OnError, const FOnDeleteAssignmentComplete& OnComplete, int64& OutRequestId);

		
	/**
	 * @brief Makes an authenticated request to the Delete /object/leaderboards/{objectId}/entry endpoint of the Leaderboards Service.
	 *
	 * @param UserSlot The authenticated UserSlot with the user making the request. 
	 * @param Request The Request UObject. All (de)serialized data the request data creates is tied to the lifecycle of this object.
	 * @param OnSuccess What to do if the requests receives a successful response.
	 * @param OnError What to do if the request receives an error response.
	 * @param OnComplete What to after either OnSuccess or OnError have finished executing.
	 * @param OutRequestId The Request Id -- used to query information about the request or to cancel it while it's in flight. 
	 */
	UFUNCTION(BlueprintCallable, Category="Beam|APIs|Leaderboards", meta=(AutoCreateRefTerm="UserSlot,OnSuccess,OnError,OnComplete"))
	void DeleteEntry(const FUserSlot& UserSlot, UDeleteEntryRequest* Request, const FOnDeleteEntrySuccess& OnSuccess, const FOnDeleteEntryError& OnError, const FOnDeleteEntryComplete& OnComplete, int64& OutRequestId);

		
	/**
	 * @brief Makes an authenticated request to the Put /object/leaderboards/{objectId}/freeze endpoint of the Leaderboards Service.
	 *
	 * @param UserSlot The authenticated UserSlot with the user making the request. 
	 * @param Request The Request UObject. All (de)serialized data the request data creates is tied to the lifecycle of this object.
	 * @param OnSuccess What to do if the requests receives a successful response.
	 * @param OnError What to do if the request receives an error response.
	 * @param OnComplete What to after either OnSuccess or OnError have finished executing.
	 * @param OutRequestId The Request Id -- used to query information about the request or to cancel it while it's in flight. 
	 */
	UFUNCTION(BlueprintCallable, Category="Beam|APIs|Leaderboards", meta=(AutoCreateRefTerm="UserSlot,OnSuccess,OnError,OnComplete"))
	void PutFreeze(const FUserSlot& UserSlot, UPutFreezeRequest* Request, const FOnPutFreezeSuccess& OnSuccess, const FOnPutFreezeError& OnError, const FOnPutFreezeComplete& OnComplete, int64& OutRequestId);

		
	/**
	 * @brief Makes an authenticated request to the Get /object/leaderboards/{objectId}/details endpoint of the Leaderboards Service.
	 *
	 * @param UserSlot The authenticated UserSlot with the user making the request. 
	 * @param Request The Request UObject. All (de)serialized data the request data creates is tied to the lifecycle of this object.
	 * @param OnSuccess What to do if the requests receives a successful response.
	 * @param OnError What to do if the request receives an error response.
	 * @param OnComplete What to after either OnSuccess or OnError have finished executing.
	 * @param OutRequestId The Request Id -- used to query information about the request or to cancel it while it's in flight. 
	 */
	UFUNCTION(BlueprintCallable, Category="Beam|APIs|Leaderboards", meta=(AutoCreateRefTerm="UserSlot,OnSuccess,OnError,OnComplete"))
	void GetDetails(const FUserSlot& UserSlot, UGetDetailsRequest* Request, const FOnGetDetailsSuccess& OnSuccess, const FOnGetDetailsError& OnError, const FOnGetDetailsComplete& OnComplete, int64& OutRequestId);

		
	/**
	 * @brief Makes an authenticated request to the Put /object/leaderboards/{objectId}/swap endpoint of the Leaderboards Service.
	 *
	 * @param UserSlot The authenticated UserSlot with the user making the request. 
	 * @param Request The Request UObject. All (de)serialized data the request data creates is tied to the lifecycle of this object.
	 * @param OnSuccess What to do if the requests receives a successful response.
	 * @param OnError What to do if the request receives an error response.
	 * @param OnComplete What to after either OnSuccess or OnError have finished executing.
	 * @param OutRequestId The Request Id -- used to query information about the request or to cancel it while it's in flight. 
	 */
	UFUNCTION(BlueprintCallable, Category="Beam|APIs|Leaderboards", meta=(AutoCreateRefTerm="UserSlot,OnSuccess,OnError,OnComplete"))
	void PutSwap(const FUserSlot& UserSlot, UPutSwapRequest* Request, const FOnPutSwapSuccess& OnSuccess, const FOnPutSwapError& OnError, const FOnPutSwapComplete& OnComplete, int64& OutRequestId);
	
};
