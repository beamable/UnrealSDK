

#pragma once

#include "CoreMinimal.h"
#include "BeamBackend.h"

#include "Groups/PostKickRequest.h"
#include "Groups/DeleteMemberRequest.h"
#include "Groups/ObjectGroupsGetGroupsRequest.h"
#include "Groups/PutGroupsRequest.h"
#include "Groups/DeleteGroupsRequest.h"
#include "Groups/ObjectGroupsPutRoleRequest.h"
#include "Groups/PostApplyRequest.h"
#include "Groups/PostDonationsRequest.h"
#include "Groups/PutDonationsRequest.h"
#include "Groups/PutDonationsClaimRequest.h"
#include "Groups/PostInviteRequest.h"
#include "Groups/PostPetitionRequest.h"

#include "BeamGroupsApi.generated.h"


/**
 * Subsystem containing request calls for the Groups service.
 */
UCLASS(BlueprintType)
class BEAMABLECORE_API UBeamGroupsApi : public UEngineSubsystem
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
	void BP_PostKickImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, FBeamConnectivity& ConnectivityStatus, UPostKickRequest* RequestData,
	                                const FOnPostKickSuccess& OnSuccess, const FOnPostKickError& OnError, const FOnPostKickComplete& OnComplete,
	                                int64& OutRequestId) const;
	/**
	 * @brief Overload version for binding lambdas when in C++ land. Prefer the BP version whenever possible, this is here mostly for quick experimentation purposes.	 
	 */
	void CPP_PostKickImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, FBeamConnectivity& ConnectivityStatus, UPostKickRequest* RequestData,
	                                 const FOnPostKickFullResponse& Handler) const;

		
	/**
	 * @brief Private implementation that all overloaded BP UFunctions call.	  
	 */
	void BP_DeleteMemberImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, FBeamConnectivity& ConnectivityStatus, UDeleteMemberRequest* RequestData,
	                                const FOnDeleteMemberSuccess& OnSuccess, const FOnDeleteMemberError& OnError, const FOnDeleteMemberComplete& OnComplete,
	                                int64& OutRequestId) const;
	/**
	 * @brief Overload version for binding lambdas when in C++ land. Prefer the BP version whenever possible, this is here mostly for quick experimentation purposes.	 
	 */
	void CPP_DeleteMemberImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, FBeamConnectivity& ConnectivityStatus, UDeleteMemberRequest* RequestData,
	                                 const FOnDeleteMemberFullResponse& Handler) const;

		
	/**
	 * @brief Private implementation that all overloaded BP UFunctions call.	  
	 */
	void BP_GetGroupsImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, FBeamConnectivity& ConnectivityStatus, UObjectGroupsGetGroupsRequest* RequestData,
	                                const FOnObjectGroupsGetGroupsSuccess& OnSuccess, const FOnObjectGroupsGetGroupsError& OnError, const FOnObjectGroupsGetGroupsComplete& OnComplete,
	                                int64& OutRequestId) const;
	/**
	 * @brief Overload version for binding lambdas when in C++ land. Prefer the BP version whenever possible, this is here mostly for quick experimentation purposes.	 
	 */
	void CPP_GetGroupsImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, FBeamConnectivity& ConnectivityStatus, UObjectGroupsGetGroupsRequest* RequestData,
	                                 const FOnObjectGroupsGetGroupsFullResponse& Handler) const;

		
	/**
	 * @brief Private implementation that all overloaded BP UFunctions call.	  
	 */
	void BP_PutGroupsImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, FBeamConnectivity& ConnectivityStatus, UPutGroupsRequest* RequestData,
	                                const FOnPutGroupsSuccess& OnSuccess, const FOnPutGroupsError& OnError, const FOnPutGroupsComplete& OnComplete,
	                                int64& OutRequestId) const;
	/**
	 * @brief Overload version for binding lambdas when in C++ land. Prefer the BP version whenever possible, this is here mostly for quick experimentation purposes.	 
	 */
	void CPP_PutGroupsImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, FBeamConnectivity& ConnectivityStatus, UPutGroupsRequest* RequestData,
	                                 const FOnPutGroupsFullResponse& Handler) const;

		
	/**
	 * @brief Private implementation that all overloaded BP UFunctions call.	  
	 */
	void BP_DeleteGroupsImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, FBeamConnectivity& ConnectivityStatus, UDeleteGroupsRequest* RequestData,
	                                const FOnDeleteGroupsSuccess& OnSuccess, const FOnDeleteGroupsError& OnError, const FOnDeleteGroupsComplete& OnComplete,
	                                int64& OutRequestId) const;
	/**
	 * @brief Overload version for binding lambdas when in C++ land. Prefer the BP version whenever possible, this is here mostly for quick experimentation purposes.	 
	 */
	void CPP_DeleteGroupsImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, FBeamConnectivity& ConnectivityStatus, UDeleteGroupsRequest* RequestData,
	                                 const FOnDeleteGroupsFullResponse& Handler) const;


	
	/**
	 * @brief Private implementation for requests that require authentication that all overloaded BP UFunctions call.	  
	 */
	void BP_PutRoleImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, const FBeamAuthToken& AuthToken, FBeamConnectivity& ConnectivityStatus, UObjectGroupsPutRoleRequest* RequestData,
	                  const FOnObjectGroupsPutRoleSuccess& OnSuccess, const FOnObjectGroupsPutRoleError& OnError, const FOnObjectGroupsPutRoleComplete& OnComplete, int64& OutRequestId) const;
	/**
	 * @brief Overload version for binding lambdas when in C++ land. Prefer the BP version whenever possible, this is here mostly for quick experimentation purposes.	 
	 */
	void CPP_PutRoleImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, const FBeamAuthToken& AuthToken, FBeamConnectivity& ConnectivityStatus, UObjectGroupsPutRoleRequest* RequestData,
	                   const FOnObjectGroupsPutRoleFullResponse& Handler) const;
		
	/**
	 * @brief Private implementation for requests that require authentication that all overloaded BP UFunctions call.	  
	 */
	void BP_PostApplyImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, const FBeamAuthToken& AuthToken, FBeamConnectivity& ConnectivityStatus, UPostApplyRequest* RequestData,
	                  const FOnPostApplySuccess& OnSuccess, const FOnPostApplyError& OnError, const FOnPostApplyComplete& OnComplete, int64& OutRequestId) const;
	/**
	 * @brief Overload version for binding lambdas when in C++ land. Prefer the BP version whenever possible, this is here mostly for quick experimentation purposes.	 
	 */
	void CPP_PostApplyImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, const FBeamAuthToken& AuthToken, FBeamConnectivity& ConnectivityStatus, UPostApplyRequest* RequestData,
	                   const FOnPostApplyFullResponse& Handler) const;
		
	/**
	 * @brief Private implementation for requests that require authentication that all overloaded BP UFunctions call.	  
	 */
	void BP_PostDonationsImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, const FBeamAuthToken& AuthToken, FBeamConnectivity& ConnectivityStatus, UPostDonationsRequest* RequestData,
	                  const FOnPostDonationsSuccess& OnSuccess, const FOnPostDonationsError& OnError, const FOnPostDonationsComplete& OnComplete, int64& OutRequestId) const;
	/**
	 * @brief Overload version for binding lambdas when in C++ land. Prefer the BP version whenever possible, this is here mostly for quick experimentation purposes.	 
	 */
	void CPP_PostDonationsImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, const FBeamAuthToken& AuthToken, FBeamConnectivity& ConnectivityStatus, UPostDonationsRequest* RequestData,
	                   const FOnPostDonationsFullResponse& Handler) const;
		
	/**
	 * @brief Private implementation for requests that require authentication that all overloaded BP UFunctions call.	  
	 */
	void BP_PutDonationsImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, const FBeamAuthToken& AuthToken, FBeamConnectivity& ConnectivityStatus, UPutDonationsRequest* RequestData,
	                  const FOnPutDonationsSuccess& OnSuccess, const FOnPutDonationsError& OnError, const FOnPutDonationsComplete& OnComplete, int64& OutRequestId) const;
	/**
	 * @brief Overload version for binding lambdas when in C++ land. Prefer the BP version whenever possible, this is here mostly for quick experimentation purposes.	 
	 */
	void CPP_PutDonationsImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, const FBeamAuthToken& AuthToken, FBeamConnectivity& ConnectivityStatus, UPutDonationsRequest* RequestData,
	                   const FOnPutDonationsFullResponse& Handler) const;
		
	/**
	 * @brief Private implementation for requests that require authentication that all overloaded BP UFunctions call.	  
	 */
	void BP_PutDonationsClaimImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, const FBeamAuthToken& AuthToken, FBeamConnectivity& ConnectivityStatus, UPutDonationsClaimRequest* RequestData,
	                  const FOnPutDonationsClaimSuccess& OnSuccess, const FOnPutDonationsClaimError& OnError, const FOnPutDonationsClaimComplete& OnComplete, int64& OutRequestId) const;
	/**
	 * @brief Overload version for binding lambdas when in C++ land. Prefer the BP version whenever possible, this is here mostly for quick experimentation purposes.	 
	 */
	void CPP_PutDonationsClaimImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, const FBeamAuthToken& AuthToken, FBeamConnectivity& ConnectivityStatus, UPutDonationsClaimRequest* RequestData,
	                   const FOnPutDonationsClaimFullResponse& Handler) const;
		
	/**
	 * @brief Private implementation for requests that require authentication that all overloaded BP UFunctions call.	  
	 */
	void BP_PostInviteImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, const FBeamAuthToken& AuthToken, FBeamConnectivity& ConnectivityStatus, UPostInviteRequest* RequestData,
	                  const FOnPostInviteSuccess& OnSuccess, const FOnPostInviteError& OnError, const FOnPostInviteComplete& OnComplete, int64& OutRequestId) const;
	/**
	 * @brief Overload version for binding lambdas when in C++ land. Prefer the BP version whenever possible, this is here mostly for quick experimentation purposes.	 
	 */
	void CPP_PostInviteImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, const FBeamAuthToken& AuthToken, FBeamConnectivity& ConnectivityStatus, UPostInviteRequest* RequestData,
	                   const FOnPostInviteFullResponse& Handler) const;
		
	/**
	 * @brief Private implementation for requests that require authentication that all overloaded BP UFunctions call.	  
	 */
	void BP_PostPetitionImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, const FBeamAuthToken& AuthToken, FBeamConnectivity& ConnectivityStatus, UPostPetitionRequest* RequestData,
	                  const FOnPostPetitionSuccess& OnSuccess, const FOnPostPetitionError& OnError, const FOnPostPetitionComplete& OnComplete, int64& OutRequestId) const;
	/**
	 * @brief Overload version for binding lambdas when in C++ land. Prefer the BP version whenever possible, this is here mostly for quick experimentation purposes.	 
	 */
	void CPP_PostPetitionImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, const FBeamAuthToken& AuthToken, FBeamConnectivity& ConnectivityStatus, UPostPetitionRequest* RequestData,
	                   const FOnPostPetitionFullResponse& Handler) const;

public:
	
	/** Used by a helper blueprint node so that you can easily chain requests in BP-land. */
	UFUNCTION(BlueprintPure, BlueprintInternalUseOnly)
	static UBeamGroupsApi* GetSelf() { return GEngine->GetEngineSubsystem<UBeamGroupsApi>(); }

	
	/**
	 * @brief Makes a request to the Post /object/groups/{objectId}/kick endpoint of the Groups Service.
	 *
	 * PREFER THE UFUNCTION OVERLOAD AS OPPOSED TO THIS. THIS MAINLY EXISTS TO ALLOW LAMBDA BINDING THE HANDLER.
	 * (Dynamic delegates do not allow for that so... we autogen this one to make experimenting in CPP a bit faster and for whenever you need to capture variables).
	 * 
	 * @param Request The Request UObject. All (de)serialized data the request data creates is tied to the lifecycle of this object.
	 * @param Handler A callback that defines how to handle success, error and completion. 
	 */
	void CPP_PostKick(UPostKickRequest* Request, const FOnPostKickFullResponse& Handler) const;

		
	/**
	 * @brief Makes a request to the Delete /object/groups/{objectId}/member endpoint of the Groups Service.
	 *
	 * PREFER THE UFUNCTION OVERLOAD AS OPPOSED TO THIS. THIS MAINLY EXISTS TO ALLOW LAMBDA BINDING THE HANDLER.
	 * (Dynamic delegates do not allow for that so... we autogen this one to make experimenting in CPP a bit faster and for whenever you need to capture variables).
	 * 
	 * @param Request The Request UObject. All (de)serialized data the request data creates is tied to the lifecycle of this object.
	 * @param Handler A callback that defines how to handle success, error and completion. 
	 */
	void CPP_DeleteMember(UDeleteMemberRequest* Request, const FOnDeleteMemberFullResponse& Handler) const;

		
	/**
	 * @brief Makes a request to the Get /object/groups/{objectId}/ endpoint of the Groups Service.
	 *
	 * PREFER THE UFUNCTION OVERLOAD AS OPPOSED TO THIS. THIS MAINLY EXISTS TO ALLOW LAMBDA BINDING THE HANDLER.
	 * (Dynamic delegates do not allow for that so... we autogen this one to make experimenting in CPP a bit faster and for whenever you need to capture variables).
	 * 
	 * @param Request The Request UObject. All (de)serialized data the request data creates is tied to the lifecycle of this object.
	 * @param Handler A callback that defines how to handle success, error and completion. 
	 */
	void CPP_GetGroups(UObjectGroupsGetGroupsRequest* Request, const FOnObjectGroupsGetGroupsFullResponse& Handler) const;

		
	/**
	 * @brief Makes a request to the Put /object/groups/{objectId}/ endpoint of the Groups Service.
	 *
	 * PREFER THE UFUNCTION OVERLOAD AS OPPOSED TO THIS. THIS MAINLY EXISTS TO ALLOW LAMBDA BINDING THE HANDLER.
	 * (Dynamic delegates do not allow for that so... we autogen this one to make experimenting in CPP a bit faster and for whenever you need to capture variables).
	 * 
	 * @param Request The Request UObject. All (de)serialized data the request data creates is tied to the lifecycle of this object.
	 * @param Handler A callback that defines how to handle success, error and completion. 
	 */
	void CPP_PutGroups(UPutGroupsRequest* Request, const FOnPutGroupsFullResponse& Handler) const;

		
	/**
	 * @brief Makes a request to the Delete /object/groups/{objectId}/ endpoint of the Groups Service.
	 *
	 * PREFER THE UFUNCTION OVERLOAD AS OPPOSED TO THIS. THIS MAINLY EXISTS TO ALLOW LAMBDA BINDING THE HANDLER.
	 * (Dynamic delegates do not allow for that so... we autogen this one to make experimenting in CPP a bit faster and for whenever you need to capture variables).
	 * 
	 * @param Request The Request UObject. All (de)serialized data the request data creates is tied to the lifecycle of this object.
	 * @param Handler A callback that defines how to handle success, error and completion. 
	 */
	void CPP_DeleteGroups(UDeleteGroupsRequest* Request, const FOnDeleteGroupsFullResponse& Handler) const;


	
	/**
	 * @brief Makes an authenticated request to the Put /object/groups/{objectId}/role endpoint of the Groups Service.
	 *
	 * PREFER THE UFUNCTION OVERLOAD AS OPPOSED TO THIS. THIS MAINLY EXISTS TO ALLOW LAMBDA BINDING THE HANDLER.
	 * (Dynamic delegates do not allow for that so... we autogen this one to make experimenting in CPP a bit faster).
	 * 
	 * @param UserSlot The Authenticated User Slot that is making this request.
	 * @param Request The Request UObject. All (de)serialized data the request data creates is tied to the lifecycle of this object.
	 * @param Handler A callback that defines how to handle success, error and completion. 
	 */
	void CPP_PutRole(const FUserSlot& UserSlot, UObjectGroupsPutRoleRequest* Request, const FOnObjectGroupsPutRoleFullResponse& Handler) const;

		
	/**
	 * @brief Makes an authenticated request to the Post /object/groups/{objectId}/apply endpoint of the Groups Service.
	 *
	 * PREFER THE UFUNCTION OVERLOAD AS OPPOSED TO THIS. THIS MAINLY EXISTS TO ALLOW LAMBDA BINDING THE HANDLER.
	 * (Dynamic delegates do not allow for that so... we autogen this one to make experimenting in CPP a bit faster).
	 * 
	 * @param UserSlot The Authenticated User Slot that is making this request.
	 * @param Request The Request UObject. All (de)serialized data the request data creates is tied to the lifecycle of this object.
	 * @param Handler A callback that defines how to handle success, error and completion. 
	 */
	void CPP_PostApply(const FUserSlot& UserSlot, UPostApplyRequest* Request, const FOnPostApplyFullResponse& Handler) const;

		
	/**
	 * @brief Makes an authenticated request to the Post /object/groups/{objectId}/donations endpoint of the Groups Service.
	 *
	 * PREFER THE UFUNCTION OVERLOAD AS OPPOSED TO THIS. THIS MAINLY EXISTS TO ALLOW LAMBDA BINDING THE HANDLER.
	 * (Dynamic delegates do not allow for that so... we autogen this one to make experimenting in CPP a bit faster).
	 * 
	 * @param UserSlot The Authenticated User Slot that is making this request.
	 * @param Request The Request UObject. All (de)serialized data the request data creates is tied to the lifecycle of this object.
	 * @param Handler A callback that defines how to handle success, error and completion. 
	 */
	void CPP_PostDonations(const FUserSlot& UserSlot, UPostDonationsRequest* Request, const FOnPostDonationsFullResponse& Handler) const;

		
	/**
	 * @brief Makes an authenticated request to the Put /object/groups/{objectId}/donations endpoint of the Groups Service.
	 *
	 * PREFER THE UFUNCTION OVERLOAD AS OPPOSED TO THIS. THIS MAINLY EXISTS TO ALLOW LAMBDA BINDING THE HANDLER.
	 * (Dynamic delegates do not allow for that so... we autogen this one to make experimenting in CPP a bit faster).
	 * 
	 * @param UserSlot The Authenticated User Slot that is making this request.
	 * @param Request The Request UObject. All (de)serialized data the request data creates is tied to the lifecycle of this object.
	 * @param Handler A callback that defines how to handle success, error and completion. 
	 */
	void CPP_PutDonations(const FUserSlot& UserSlot, UPutDonationsRequest* Request, const FOnPutDonationsFullResponse& Handler) const;

		
	/**
	 * @brief Makes an authenticated request to the Put /object/groups/{objectId}/donations/claim endpoint of the Groups Service.
	 *
	 * PREFER THE UFUNCTION OVERLOAD AS OPPOSED TO THIS. THIS MAINLY EXISTS TO ALLOW LAMBDA BINDING THE HANDLER.
	 * (Dynamic delegates do not allow for that so... we autogen this one to make experimenting in CPP a bit faster).
	 * 
	 * @param UserSlot The Authenticated User Slot that is making this request.
	 * @param Request The Request UObject. All (de)serialized data the request data creates is tied to the lifecycle of this object.
	 * @param Handler A callback that defines how to handle success, error and completion. 
	 */
	void CPP_PutDonationsClaim(const FUserSlot& UserSlot, UPutDonationsClaimRequest* Request, const FOnPutDonationsClaimFullResponse& Handler) const;

		
	/**
	 * @brief Makes an authenticated request to the Post /object/groups/{objectId}/invite endpoint of the Groups Service.
	 *
	 * PREFER THE UFUNCTION OVERLOAD AS OPPOSED TO THIS. THIS MAINLY EXISTS TO ALLOW LAMBDA BINDING THE HANDLER.
	 * (Dynamic delegates do not allow for that so... we autogen this one to make experimenting in CPP a bit faster).
	 * 
	 * @param UserSlot The Authenticated User Slot that is making this request.
	 * @param Request The Request UObject. All (de)serialized data the request data creates is tied to the lifecycle of this object.
	 * @param Handler A callback that defines how to handle success, error and completion. 
	 */
	void CPP_PostInvite(const FUserSlot& UserSlot, UPostInviteRequest* Request, const FOnPostInviteFullResponse& Handler) const;

		
	/**
	 * @brief Makes an authenticated request to the Post /object/groups/{objectId}/petition endpoint of the Groups Service.
	 *
	 * PREFER THE UFUNCTION OVERLOAD AS OPPOSED TO THIS. THIS MAINLY EXISTS TO ALLOW LAMBDA BINDING THE HANDLER.
	 * (Dynamic delegates do not allow for that so... we autogen this one to make experimenting in CPP a bit faster).
	 * 
	 * @param UserSlot The Authenticated User Slot that is making this request.
	 * @param Request The Request UObject. All (de)serialized data the request data creates is tied to the lifecycle of this object.
	 * @param Handler A callback that defines how to handle success, error and completion. 
	 */
	void CPP_PostPetition(const FUserSlot& UserSlot, UPostPetitionRequest* Request, const FOnPostPetitionFullResponse& Handler) const;


	
	/**
	 * @brief Makes a request to the Post /object/groups/{objectId}/kick endpoint of the Groups Service.
	 *
	 * @param Request The Request UObject. All (de)serialized data the request data creates is tied to the lifecycle of this object.
	 * @param OnSuccess What to do if the requests receives a successful response.
	 * @param OnError What to do if the request receives an error response.
	 * @param OnComplete What to after either OnSuccess or OnError have finished executing.
	 * @param OutRequestId The Request Id -- used to query information about the request or to cancel it while it's in flight. 
	 */
	UFUNCTION(BlueprintCallable, Category="Beam|APIs|Groups", meta=(AutoCreateRefTerm="OnSuccess,OnError,OnComplete"))
	void PostKick(UPostKickRequest* Request, const FOnPostKickSuccess& OnSuccess, const FOnPostKickError& OnError, const FOnPostKickComplete& OnComplete,
								 int64& OutRequestId);

		
	/**
	 * @brief Makes a request to the Delete /object/groups/{objectId}/member endpoint of the Groups Service.
	 *
	 * @param Request The Request UObject. All (de)serialized data the request data creates is tied to the lifecycle of this object.
	 * @param OnSuccess What to do if the requests receives a successful response.
	 * @param OnError What to do if the request receives an error response.
	 * @param OnComplete What to after either OnSuccess or OnError have finished executing.
	 * @param OutRequestId The Request Id -- used to query information about the request or to cancel it while it's in flight. 
	 */
	UFUNCTION(BlueprintCallable, Category="Beam|APIs|Groups", meta=(AutoCreateRefTerm="OnSuccess,OnError,OnComplete"))
	void DeleteMember(UDeleteMemberRequest* Request, const FOnDeleteMemberSuccess& OnSuccess, const FOnDeleteMemberError& OnError, const FOnDeleteMemberComplete& OnComplete,
								 int64& OutRequestId);

		
	/**
	 * @brief Makes a request to the Get /object/groups/{objectId}/ endpoint of the Groups Service.
	 *
	 * @param Request The Request UObject. All (de)serialized data the request data creates is tied to the lifecycle of this object.
	 * @param OnSuccess What to do if the requests receives a successful response.
	 * @param OnError What to do if the request receives an error response.
	 * @param OnComplete What to after either OnSuccess or OnError have finished executing.
	 * @param OutRequestId The Request Id -- used to query information about the request or to cancel it while it's in flight. 
	 */
	UFUNCTION(BlueprintCallable, Category="Beam|APIs|Groups", meta=(AutoCreateRefTerm="OnSuccess,OnError,OnComplete"))
	void GetGroups(UObjectGroupsGetGroupsRequest* Request, const FOnObjectGroupsGetGroupsSuccess& OnSuccess, const FOnObjectGroupsGetGroupsError& OnError, const FOnObjectGroupsGetGroupsComplete& OnComplete,
								 int64& OutRequestId);

		
	/**
	 * @brief Makes a request to the Put /object/groups/{objectId}/ endpoint of the Groups Service.
	 *
	 * @param Request The Request UObject. All (de)serialized data the request data creates is tied to the lifecycle of this object.
	 * @param OnSuccess What to do if the requests receives a successful response.
	 * @param OnError What to do if the request receives an error response.
	 * @param OnComplete What to after either OnSuccess or OnError have finished executing.
	 * @param OutRequestId The Request Id -- used to query information about the request or to cancel it while it's in flight. 
	 */
	UFUNCTION(BlueprintCallable, Category="Beam|APIs|Groups", meta=(AutoCreateRefTerm="OnSuccess,OnError,OnComplete"))
	void PutGroups(UPutGroupsRequest* Request, const FOnPutGroupsSuccess& OnSuccess, const FOnPutGroupsError& OnError, const FOnPutGroupsComplete& OnComplete,
								 int64& OutRequestId);

		
	/**
	 * @brief Makes a request to the Delete /object/groups/{objectId}/ endpoint of the Groups Service.
	 *
	 * @param Request The Request UObject. All (de)serialized data the request data creates is tied to the lifecycle of this object.
	 * @param OnSuccess What to do if the requests receives a successful response.
	 * @param OnError What to do if the request receives an error response.
	 * @param OnComplete What to after either OnSuccess or OnError have finished executing.
	 * @param OutRequestId The Request Id -- used to query information about the request or to cancel it while it's in flight. 
	 */
	UFUNCTION(BlueprintCallable, Category="Beam|APIs|Groups", meta=(AutoCreateRefTerm="OnSuccess,OnError,OnComplete"))
	void DeleteGroups(UDeleteGroupsRequest* Request, const FOnDeleteGroupsSuccess& OnSuccess, const FOnDeleteGroupsError& OnError, const FOnDeleteGroupsComplete& OnComplete,
								 int64& OutRequestId);


	
	/**
	 * @brief Makes an authenticated request to the Put /object/groups/{objectId}/role endpoint of the Groups Service.
	 *
	 * @param UserSlot The authenticated UserSlot with the user making the request. 
	 * @param Request The Request UObject. All (de)serialized data the request data creates is tied to the lifecycle of this object.
	 * @param OnSuccess What to do if the requests receives a successful response.
	 * @param OnError What to do if the request receives an error response.
	 * @param OnComplete What to after either OnSuccess or OnError have finished executing.
	 * @param OutRequestId The Request Id -- used to query information about the request or to cancel it while it's in flight. 
	 */
	UFUNCTION(BlueprintCallable, Category="Beam|APIs|Groups", meta=(AutoCreateRefTerm="UserSlot,OnSuccess,OnError,OnComplete"))
	void PutRole(const FUserSlot& UserSlot, UObjectGroupsPutRoleRequest* Request, const FOnObjectGroupsPutRoleSuccess& OnSuccess, const FOnObjectGroupsPutRoleError& OnError, const FOnObjectGroupsPutRoleComplete& OnComplete, int64& OutRequestId);

		
	/**
	 * @brief Makes an authenticated request to the Post /object/groups/{objectId}/apply endpoint of the Groups Service.
	 *
	 * @param UserSlot The authenticated UserSlot with the user making the request. 
	 * @param Request The Request UObject. All (de)serialized data the request data creates is tied to the lifecycle of this object.
	 * @param OnSuccess What to do if the requests receives a successful response.
	 * @param OnError What to do if the request receives an error response.
	 * @param OnComplete What to after either OnSuccess or OnError have finished executing.
	 * @param OutRequestId The Request Id -- used to query information about the request or to cancel it while it's in flight. 
	 */
	UFUNCTION(BlueprintCallable, Category="Beam|APIs|Groups", meta=(AutoCreateRefTerm="UserSlot,OnSuccess,OnError,OnComplete"))
	void PostApply(const FUserSlot& UserSlot, UPostApplyRequest* Request, const FOnPostApplySuccess& OnSuccess, const FOnPostApplyError& OnError, const FOnPostApplyComplete& OnComplete, int64& OutRequestId);

		
	/**
	 * @brief Makes an authenticated request to the Post /object/groups/{objectId}/donations endpoint of the Groups Service.
	 *
	 * @param UserSlot The authenticated UserSlot with the user making the request. 
	 * @param Request The Request UObject. All (de)serialized data the request data creates is tied to the lifecycle of this object.
	 * @param OnSuccess What to do if the requests receives a successful response.
	 * @param OnError What to do if the request receives an error response.
	 * @param OnComplete What to after either OnSuccess or OnError have finished executing.
	 * @param OutRequestId The Request Id -- used to query information about the request or to cancel it while it's in flight. 
	 */
	UFUNCTION(BlueprintCallable, Category="Beam|APIs|Groups", meta=(AutoCreateRefTerm="UserSlot,OnSuccess,OnError,OnComplete"))
	void PostDonations(const FUserSlot& UserSlot, UPostDonationsRequest* Request, const FOnPostDonationsSuccess& OnSuccess, const FOnPostDonationsError& OnError, const FOnPostDonationsComplete& OnComplete, int64& OutRequestId);

		
	/**
	 * @brief Makes an authenticated request to the Put /object/groups/{objectId}/donations endpoint of the Groups Service.
	 *
	 * @param UserSlot The authenticated UserSlot with the user making the request. 
	 * @param Request The Request UObject. All (de)serialized data the request data creates is tied to the lifecycle of this object.
	 * @param OnSuccess What to do if the requests receives a successful response.
	 * @param OnError What to do if the request receives an error response.
	 * @param OnComplete What to after either OnSuccess or OnError have finished executing.
	 * @param OutRequestId The Request Id -- used to query information about the request or to cancel it while it's in flight. 
	 */
	UFUNCTION(BlueprintCallable, Category="Beam|APIs|Groups", meta=(AutoCreateRefTerm="UserSlot,OnSuccess,OnError,OnComplete"))
	void PutDonations(const FUserSlot& UserSlot, UPutDonationsRequest* Request, const FOnPutDonationsSuccess& OnSuccess, const FOnPutDonationsError& OnError, const FOnPutDonationsComplete& OnComplete, int64& OutRequestId);

		
	/**
	 * @brief Makes an authenticated request to the Put /object/groups/{objectId}/donations/claim endpoint of the Groups Service.
	 *
	 * @param UserSlot The authenticated UserSlot with the user making the request. 
	 * @param Request The Request UObject. All (de)serialized data the request data creates is tied to the lifecycle of this object.
	 * @param OnSuccess What to do if the requests receives a successful response.
	 * @param OnError What to do if the request receives an error response.
	 * @param OnComplete What to after either OnSuccess or OnError have finished executing.
	 * @param OutRequestId The Request Id -- used to query information about the request or to cancel it while it's in flight. 
	 */
	UFUNCTION(BlueprintCallable, Category="Beam|APIs|Groups", meta=(AutoCreateRefTerm="UserSlot,OnSuccess,OnError,OnComplete"))
	void PutDonationsClaim(const FUserSlot& UserSlot, UPutDonationsClaimRequest* Request, const FOnPutDonationsClaimSuccess& OnSuccess, const FOnPutDonationsClaimError& OnError, const FOnPutDonationsClaimComplete& OnComplete, int64& OutRequestId);

		
	/**
	 * @brief Makes an authenticated request to the Post /object/groups/{objectId}/invite endpoint of the Groups Service.
	 *
	 * @param UserSlot The authenticated UserSlot with the user making the request. 
	 * @param Request The Request UObject. All (de)serialized data the request data creates is tied to the lifecycle of this object.
	 * @param OnSuccess What to do if the requests receives a successful response.
	 * @param OnError What to do if the request receives an error response.
	 * @param OnComplete What to after either OnSuccess or OnError have finished executing.
	 * @param OutRequestId The Request Id -- used to query information about the request or to cancel it while it's in flight. 
	 */
	UFUNCTION(BlueprintCallable, Category="Beam|APIs|Groups", meta=(AutoCreateRefTerm="UserSlot,OnSuccess,OnError,OnComplete"))
	void PostInvite(const FUserSlot& UserSlot, UPostInviteRequest* Request, const FOnPostInviteSuccess& OnSuccess, const FOnPostInviteError& OnError, const FOnPostInviteComplete& OnComplete, int64& OutRequestId);

		
	/**
	 * @brief Makes an authenticated request to the Post /object/groups/{objectId}/petition endpoint of the Groups Service.
	 *
	 * @param UserSlot The authenticated UserSlot with the user making the request. 
	 * @param Request The Request UObject. All (de)serialized data the request data creates is tied to the lifecycle of this object.
	 * @param OnSuccess What to do if the requests receives a successful response.
	 * @param OnError What to do if the request receives an error response.
	 * @param OnComplete What to after either OnSuccess or OnError have finished executing.
	 * @param OutRequestId The Request Id -- used to query information about the request or to cancel it while it's in flight. 
	 */
	UFUNCTION(BlueprintCallable, Category="Beam|APIs|Groups", meta=(AutoCreateRefTerm="UserSlot,OnSuccess,OnError,OnComplete"))
	void PostPetition(const FUserSlot& UserSlot, UPostPetitionRequest* Request, const FOnPostPetitionSuccess& OnSuccess, const FOnPostPetitionError& OnError, const FOnPostPetitionComplete& OnComplete, int64& OutRequestId);
	
};
