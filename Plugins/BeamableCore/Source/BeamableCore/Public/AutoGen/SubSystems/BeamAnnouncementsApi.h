

#pragma once

#include "CoreMinimal.h"
#include "BeamBackend.h"

#include "Announcements/GetListTagsRequest.h"
#include "Announcements/BasicAnnouncementsGetListRequest.h"
#include "Announcements/BasicAnnouncementsGetSearchRequest.h"
#include "Announcements/GetListDefinitionsRequest.h"
#include "Announcements/PostAnnouncementsRequest.h"
#include "Announcements/BasicAnnouncementsDeleteAnnouncementsRequest.h"
#include "Announcements/BasicAnnouncementsGetContentRequest.h"
#include "Announcements/PutReadRequest.h"
#include "Announcements/ObjectAnnouncementsPostClaimRequest.h"
#include "Announcements/GetRawRequest.h"
#include "Announcements/GetAnnouncementsRequest.h"
#include "Announcements/ObjectAnnouncementsDeleteAnnouncementsRequest.h"

#include "BeamAnnouncementsApi.generated.h"


/**
 * Subsystem containing request calls for the Announcements service.
 */
UCLASS(BlueprintType)
class BEAMABLECORE_API UBeamAnnouncementsApi : public UEngineSubsystem
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
	void BP_GetListTagsImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, const FBeamAuthToken& AuthToken, FBeamConnectivity& ConnectivityStatus, UGetListTagsRequest* RequestData,
	                  const FOnGetListTagsSuccess& OnSuccess, const FOnGetListTagsError& OnError, const FOnGetListTagsComplete& OnComplete, int64& OutRequestId) const;
	/**
	 * @brief Overload version for binding lambdas when in C++ land. Prefer the BP version whenever possible, this is here mostly for quick experimentation purposes.	 
	 */
	void CPP_GetListTagsImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, const FBeamAuthToken& AuthToken, FBeamConnectivity& ConnectivityStatus, UGetListTagsRequest* RequestData,
	                   const FOnGetListTagsFullResponse& Handler) const;
		
	/**
	 * @brief Private implementation for requests that require authentication that all overloaded BP UFunctions call.	  
	 */
	void BP_GetListImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, const FBeamAuthToken& AuthToken, FBeamConnectivity& ConnectivityStatus, UBasicAnnouncementsGetListRequest* RequestData,
	                  const FOnBasicAnnouncementsGetListSuccess& OnSuccess, const FOnBasicAnnouncementsGetListError& OnError, const FOnBasicAnnouncementsGetListComplete& OnComplete, int64& OutRequestId) const;
	/**
	 * @brief Overload version for binding lambdas when in C++ land. Prefer the BP version whenever possible, this is here mostly for quick experimentation purposes.	 
	 */
	void CPP_GetListImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, const FBeamAuthToken& AuthToken, FBeamConnectivity& ConnectivityStatus, UBasicAnnouncementsGetListRequest* RequestData,
	                   const FOnBasicAnnouncementsGetListFullResponse& Handler) const;
		
	/**
	 * @brief Private implementation for requests that require authentication that all overloaded BP UFunctions call.	  
	 */
	void BP_GetSearchImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, const FBeamAuthToken& AuthToken, FBeamConnectivity& ConnectivityStatus, UBasicAnnouncementsGetSearchRequest* RequestData,
	                  const FOnBasicAnnouncementsGetSearchSuccess& OnSuccess, const FOnBasicAnnouncementsGetSearchError& OnError, const FOnBasicAnnouncementsGetSearchComplete& OnComplete, int64& OutRequestId) const;
	/**
	 * @brief Overload version for binding lambdas when in C++ land. Prefer the BP version whenever possible, this is here mostly for quick experimentation purposes.	 
	 */
	void CPP_GetSearchImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, const FBeamAuthToken& AuthToken, FBeamConnectivity& ConnectivityStatus, UBasicAnnouncementsGetSearchRequest* RequestData,
	                   const FOnBasicAnnouncementsGetSearchFullResponse& Handler) const;
		
	/**
	 * @brief Private implementation for requests that require authentication that all overloaded BP UFunctions call.	  
	 */
	void BP_GetListDefinitionsImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, const FBeamAuthToken& AuthToken, FBeamConnectivity& ConnectivityStatus, UGetListDefinitionsRequest* RequestData,
	                  const FOnGetListDefinitionsSuccess& OnSuccess, const FOnGetListDefinitionsError& OnError, const FOnGetListDefinitionsComplete& OnComplete, int64& OutRequestId) const;
	/**
	 * @brief Overload version for binding lambdas when in C++ land. Prefer the BP version whenever possible, this is here mostly for quick experimentation purposes.	 
	 */
	void CPP_GetListDefinitionsImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, const FBeamAuthToken& AuthToken, FBeamConnectivity& ConnectivityStatus, UGetListDefinitionsRequest* RequestData,
	                   const FOnGetListDefinitionsFullResponse& Handler) const;
		
	/**
	 * @brief Private implementation for requests that require authentication that all overloaded BP UFunctions call.	  
	 */
	void BP_PostAnnouncementsImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, const FBeamAuthToken& AuthToken, FBeamConnectivity& ConnectivityStatus, UPostAnnouncementsRequest* RequestData,
	                  const FOnPostAnnouncementsSuccess& OnSuccess, const FOnPostAnnouncementsError& OnError, const FOnPostAnnouncementsComplete& OnComplete, int64& OutRequestId) const;
	/**
	 * @brief Overload version for binding lambdas when in C++ land. Prefer the BP version whenever possible, this is here mostly for quick experimentation purposes.	 
	 */
	void CPP_PostAnnouncementsImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, const FBeamAuthToken& AuthToken, FBeamConnectivity& ConnectivityStatus, UPostAnnouncementsRequest* RequestData,
	                   const FOnPostAnnouncementsFullResponse& Handler) const;
		
	/**
	 * @brief Private implementation for requests that require authentication that all overloaded BP UFunctions call.	  
	 */
	void BP_BasicAnnouncementsDeleteAnnouncementsImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, const FBeamAuthToken& AuthToken, FBeamConnectivity& ConnectivityStatus, UBasicAnnouncementsDeleteAnnouncementsRequest* RequestData,
	                  const FOnBasicAnnouncementsDeleteAnnouncementsSuccess& OnSuccess, const FOnBasicAnnouncementsDeleteAnnouncementsError& OnError, const FOnBasicAnnouncementsDeleteAnnouncementsComplete& OnComplete, int64& OutRequestId) const;
	/**
	 * @brief Overload version for binding lambdas when in C++ land. Prefer the BP version whenever possible, this is here mostly for quick experimentation purposes.	 
	 */
	void CPP_BasicAnnouncementsDeleteAnnouncementsImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, const FBeamAuthToken& AuthToken, FBeamConnectivity& ConnectivityStatus, UBasicAnnouncementsDeleteAnnouncementsRequest* RequestData,
	                   const FOnBasicAnnouncementsDeleteAnnouncementsFullResponse& Handler) const;
		
	/**
	 * @brief Private implementation for requests that require authentication that all overloaded BP UFunctions call.	  
	 */
	void BP_GetContentImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, const FBeamAuthToken& AuthToken, FBeamConnectivity& ConnectivityStatus, UBasicAnnouncementsGetContentRequest* RequestData,
	                  const FOnBasicAnnouncementsGetContentSuccess& OnSuccess, const FOnBasicAnnouncementsGetContentError& OnError, const FOnBasicAnnouncementsGetContentComplete& OnComplete, int64& OutRequestId) const;
	/**
	 * @brief Overload version for binding lambdas when in C++ land. Prefer the BP version whenever possible, this is here mostly for quick experimentation purposes.	 
	 */
	void CPP_GetContentImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, const FBeamAuthToken& AuthToken, FBeamConnectivity& ConnectivityStatus, UBasicAnnouncementsGetContentRequest* RequestData,
	                   const FOnBasicAnnouncementsGetContentFullResponse& Handler) const;
		
	/**
	 * @brief Private implementation for requests that require authentication that all overloaded BP UFunctions call.	  
	 */
	void BP_PutReadImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, const FBeamAuthToken& AuthToken, FBeamConnectivity& ConnectivityStatus, UPutReadRequest* RequestData,
	                  const FOnPutReadSuccess& OnSuccess, const FOnPutReadError& OnError, const FOnPutReadComplete& OnComplete, int64& OutRequestId) const;
	/**
	 * @brief Overload version for binding lambdas when in C++ land. Prefer the BP version whenever possible, this is here mostly for quick experimentation purposes.	 
	 */
	void CPP_PutReadImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, const FBeamAuthToken& AuthToken, FBeamConnectivity& ConnectivityStatus, UPutReadRequest* RequestData,
	                   const FOnPutReadFullResponse& Handler) const;
		
	/**
	 * @brief Private implementation for requests that require authentication that all overloaded BP UFunctions call.	  
	 */
	void BP_PostClaimImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, const FBeamAuthToken& AuthToken, FBeamConnectivity& ConnectivityStatus, UObjectAnnouncementsPostClaimRequest* RequestData,
	                  const FOnObjectAnnouncementsPostClaimSuccess& OnSuccess, const FOnObjectAnnouncementsPostClaimError& OnError, const FOnObjectAnnouncementsPostClaimComplete& OnComplete, int64& OutRequestId) const;
	/**
	 * @brief Overload version for binding lambdas when in C++ land. Prefer the BP version whenever possible, this is here mostly for quick experimentation purposes.	 
	 */
	void CPP_PostClaimImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, const FBeamAuthToken& AuthToken, FBeamConnectivity& ConnectivityStatus, UObjectAnnouncementsPostClaimRequest* RequestData,
	                   const FOnObjectAnnouncementsPostClaimFullResponse& Handler) const;
		
	/**
	 * @brief Private implementation for requests that require authentication that all overloaded BP UFunctions call.	  
	 */
	void BP_GetRawImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, const FBeamAuthToken& AuthToken, FBeamConnectivity& ConnectivityStatus, UGetRawRequest* RequestData,
	                  const FOnGetRawSuccess& OnSuccess, const FOnGetRawError& OnError, const FOnGetRawComplete& OnComplete, int64& OutRequestId) const;
	/**
	 * @brief Overload version for binding lambdas when in C++ land. Prefer the BP version whenever possible, this is here mostly for quick experimentation purposes.	 
	 */
	void CPP_GetRawImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, const FBeamAuthToken& AuthToken, FBeamConnectivity& ConnectivityStatus, UGetRawRequest* RequestData,
	                   const FOnGetRawFullResponse& Handler) const;
		
	/**
	 * @brief Private implementation for requests that require authentication that all overloaded BP UFunctions call.	  
	 */
	void BP_GetAnnouncementsImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, const FBeamAuthToken& AuthToken, FBeamConnectivity& ConnectivityStatus, UGetAnnouncementsRequest* RequestData,
	                  const FOnGetAnnouncementsSuccess& OnSuccess, const FOnGetAnnouncementsError& OnError, const FOnGetAnnouncementsComplete& OnComplete, int64& OutRequestId) const;
	/**
	 * @brief Overload version for binding lambdas when in C++ land. Prefer the BP version whenever possible, this is here mostly for quick experimentation purposes.	 
	 */
	void CPP_GetAnnouncementsImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, const FBeamAuthToken& AuthToken, FBeamConnectivity& ConnectivityStatus, UGetAnnouncementsRequest* RequestData,
	                   const FOnGetAnnouncementsFullResponse& Handler) const;
		
	/**
	 * @brief Private implementation for requests that require authentication that all overloaded BP UFunctions call.	  
	 */
	void BP_ObjectAnnouncementsDeleteAnnouncementsImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, const FBeamAuthToken& AuthToken, FBeamConnectivity& ConnectivityStatus, UObjectAnnouncementsDeleteAnnouncementsRequest* RequestData,
	                  const FOnObjectAnnouncementsDeleteAnnouncementsSuccess& OnSuccess, const FOnObjectAnnouncementsDeleteAnnouncementsError& OnError, const FOnObjectAnnouncementsDeleteAnnouncementsComplete& OnComplete, int64& OutRequestId) const;
	/**
	 * @brief Overload version for binding lambdas when in C++ land. Prefer the BP version whenever possible, this is here mostly for quick experimentation purposes.	 
	 */
	void CPP_ObjectAnnouncementsDeleteAnnouncementsImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, const FBeamAuthToken& AuthToken, FBeamConnectivity& ConnectivityStatus, UObjectAnnouncementsDeleteAnnouncementsRequest* RequestData,
	                   const FOnObjectAnnouncementsDeleteAnnouncementsFullResponse& Handler) const;

public:
	
	/** Used by a helper blueprint node so that you can easily chain requests in BP-land. */
	UFUNCTION(BlueprintPure, BlueprintInternalUseOnly)
	static UBeamAnnouncementsApi* GetSelf() { return GEngine->GetEngineSubsystem<UBeamAnnouncementsApi>(); }

	

	
	/**
	 * @brief Makes an authenticated request to the Get /basic/announcements/list/tags endpoint of the Announcements Service.
	 *
	 * PREFER THE UFUNCTION OVERLOAD AS OPPOSED TO THIS. THIS MAINLY EXISTS TO ALLOW LAMBDA BINDING THE HANDLER.
	 * (Dynamic delegates do not allow for that so... we autogen this one to make experimenting in CPP a bit faster).
	 * 
	 * @param UserSlot The Authenticated User Slot that is making this request.
	 * @param Request The Request UObject. All (de)serialized data the request data creates is tied to the lifecycle of this object.
	 * @param Handler A callback that defines how to handle success, error and completion. 
	 */
	void CPP_GetListTags(const FUserSlot& UserSlot, UGetListTagsRequest* Request, const FOnGetListTagsFullResponse& Handler) const;

		
	/**
	 * @brief Makes an authenticated request to the Get /basic/announcements/list endpoint of the Announcements Service.
	 *
	 * PREFER THE UFUNCTION OVERLOAD AS OPPOSED TO THIS. THIS MAINLY EXISTS TO ALLOW LAMBDA BINDING THE HANDLER.
	 * (Dynamic delegates do not allow for that so... we autogen this one to make experimenting in CPP a bit faster).
	 * 
	 * @param UserSlot The Authenticated User Slot that is making this request.
	 * @param Request The Request UObject. All (de)serialized data the request data creates is tied to the lifecycle of this object.
	 * @param Handler A callback that defines how to handle success, error and completion. 
	 */
	void CPP_GetList(const FUserSlot& UserSlot, UBasicAnnouncementsGetListRequest* Request, const FOnBasicAnnouncementsGetListFullResponse& Handler) const;

		
	/**
	 * @brief Makes an authenticated request to the Get /basic/announcements/search endpoint of the Announcements Service.
	 *
	 * PREFER THE UFUNCTION OVERLOAD AS OPPOSED TO THIS. THIS MAINLY EXISTS TO ALLOW LAMBDA BINDING THE HANDLER.
	 * (Dynamic delegates do not allow for that so... we autogen this one to make experimenting in CPP a bit faster).
	 * 
	 * @param UserSlot The Authenticated User Slot that is making this request.
	 * @param Request The Request UObject. All (de)serialized data the request data creates is tied to the lifecycle of this object.
	 * @param Handler A callback that defines how to handle success, error and completion. 
	 */
	void CPP_GetSearch(const FUserSlot& UserSlot, UBasicAnnouncementsGetSearchRequest* Request, const FOnBasicAnnouncementsGetSearchFullResponse& Handler) const;

		
	/**
	 * @brief Makes an authenticated request to the Get /basic/announcements/list/definitions endpoint of the Announcements Service.
	 *
	 * PREFER THE UFUNCTION OVERLOAD AS OPPOSED TO THIS. THIS MAINLY EXISTS TO ALLOW LAMBDA BINDING THE HANDLER.
	 * (Dynamic delegates do not allow for that so... we autogen this one to make experimenting in CPP a bit faster).
	 * 
	 * @param UserSlot The Authenticated User Slot that is making this request.
	 * @param Request The Request UObject. All (de)serialized data the request data creates is tied to the lifecycle of this object.
	 * @param Handler A callback that defines how to handle success, error and completion. 
	 */
	void CPP_GetListDefinitions(const FUserSlot& UserSlot, UGetListDefinitionsRequest* Request, const FOnGetListDefinitionsFullResponse& Handler) const;

		
	/**
	 * @brief Makes an authenticated request to the Post /basic/announcements/ endpoint of the Announcements Service.
	 *
	 * PREFER THE UFUNCTION OVERLOAD AS OPPOSED TO THIS. THIS MAINLY EXISTS TO ALLOW LAMBDA BINDING THE HANDLER.
	 * (Dynamic delegates do not allow for that so... we autogen this one to make experimenting in CPP a bit faster).
	 * 
	 * @param UserSlot The Authenticated User Slot that is making this request.
	 * @param Request The Request UObject. All (de)serialized data the request data creates is tied to the lifecycle of this object.
	 * @param Handler A callback that defines how to handle success, error and completion. 
	 */
	void CPP_PostAnnouncements(const FUserSlot& UserSlot, UPostAnnouncementsRequest* Request, const FOnPostAnnouncementsFullResponse& Handler) const;

		
	/**
	 * @brief Makes an authenticated request to the Delete /basic/announcements/ endpoint of the Announcements Service.
	 *
	 * PREFER THE UFUNCTION OVERLOAD AS OPPOSED TO THIS. THIS MAINLY EXISTS TO ALLOW LAMBDA BINDING THE HANDLER.
	 * (Dynamic delegates do not allow for that so... we autogen this one to make experimenting in CPP a bit faster).
	 * 
	 * @param UserSlot The Authenticated User Slot that is making this request.
	 * @param Request The Request UObject. All (de)serialized data the request data creates is tied to the lifecycle of this object.
	 * @param Handler A callback that defines how to handle success, error and completion. 
	 */
	void CPP_BasicAnnouncementsDeleteAnnouncements(const FUserSlot& UserSlot, UBasicAnnouncementsDeleteAnnouncementsRequest* Request, const FOnBasicAnnouncementsDeleteAnnouncementsFullResponse& Handler) const;

		
	/**
	 * @brief Makes an authenticated request to the Get /basic/announcements/content endpoint of the Announcements Service.
	 *
	 * PREFER THE UFUNCTION OVERLOAD AS OPPOSED TO THIS. THIS MAINLY EXISTS TO ALLOW LAMBDA BINDING THE HANDLER.
	 * (Dynamic delegates do not allow for that so... we autogen this one to make experimenting in CPP a bit faster).
	 * 
	 * @param UserSlot The Authenticated User Slot that is making this request.
	 * @param Request The Request UObject. All (de)serialized data the request data creates is tied to the lifecycle of this object.
	 * @param Handler A callback that defines how to handle success, error and completion. 
	 */
	void CPP_GetContent(const FUserSlot& UserSlot, UBasicAnnouncementsGetContentRequest* Request, const FOnBasicAnnouncementsGetContentFullResponse& Handler) const;

		
	/**
	 * @brief Makes an authenticated request to the Put /object/announcements/{objectId}/read endpoint of the Announcements Service.
	 *
	 * PREFER THE UFUNCTION OVERLOAD AS OPPOSED TO THIS. THIS MAINLY EXISTS TO ALLOW LAMBDA BINDING THE HANDLER.
	 * (Dynamic delegates do not allow for that so... we autogen this one to make experimenting in CPP a bit faster).
	 * 
	 * @param UserSlot The Authenticated User Slot that is making this request.
	 * @param Request The Request UObject. All (de)serialized data the request data creates is tied to the lifecycle of this object.
	 * @param Handler A callback that defines how to handle success, error and completion. 
	 */
	void CPP_PutRead(const FUserSlot& UserSlot, UPutReadRequest* Request, const FOnPutReadFullResponse& Handler) const;

		
	/**
	 * @brief Makes an authenticated request to the Post /object/announcements/{objectId}/claim endpoint of the Announcements Service.
	 *
	 * PREFER THE UFUNCTION OVERLOAD AS OPPOSED TO THIS. THIS MAINLY EXISTS TO ALLOW LAMBDA BINDING THE HANDLER.
	 * (Dynamic delegates do not allow for that so... we autogen this one to make experimenting in CPP a bit faster).
	 * 
	 * @param UserSlot The Authenticated User Slot that is making this request.
	 * @param Request The Request UObject. All (de)serialized data the request data creates is tied to the lifecycle of this object.
	 * @param Handler A callback that defines how to handle success, error and completion. 
	 */
	void CPP_PostClaim(const FUserSlot& UserSlot, UObjectAnnouncementsPostClaimRequest* Request, const FOnObjectAnnouncementsPostClaimFullResponse& Handler) const;

		
	/**
	 * @brief Makes an authenticated request to the Get /object/announcements/{objectId}/raw endpoint of the Announcements Service.
	 *
	 * PREFER THE UFUNCTION OVERLOAD AS OPPOSED TO THIS. THIS MAINLY EXISTS TO ALLOW LAMBDA BINDING THE HANDLER.
	 * (Dynamic delegates do not allow for that so... we autogen this one to make experimenting in CPP a bit faster).
	 * 
	 * @param UserSlot The Authenticated User Slot that is making this request.
	 * @param Request The Request UObject. All (de)serialized data the request data creates is tied to the lifecycle of this object.
	 * @param Handler A callback that defines how to handle success, error and completion. 
	 */
	void CPP_GetRaw(const FUserSlot& UserSlot, UGetRawRequest* Request, const FOnGetRawFullResponse& Handler) const;

		
	/**
	 * @brief Makes an authenticated request to the Get /object/announcements/{objectId}/ endpoint of the Announcements Service.
	 *
	 * PREFER THE UFUNCTION OVERLOAD AS OPPOSED TO THIS. THIS MAINLY EXISTS TO ALLOW LAMBDA BINDING THE HANDLER.
	 * (Dynamic delegates do not allow for that so... we autogen this one to make experimenting in CPP a bit faster).
	 * 
	 * @param UserSlot The Authenticated User Slot that is making this request.
	 * @param Request The Request UObject. All (de)serialized data the request data creates is tied to the lifecycle of this object.
	 * @param Handler A callback that defines how to handle success, error and completion. 
	 */
	void CPP_GetAnnouncements(const FUserSlot& UserSlot, UGetAnnouncementsRequest* Request, const FOnGetAnnouncementsFullResponse& Handler) const;

		
	/**
	 * @brief Makes an authenticated request to the Delete /object/announcements/{objectId}/ endpoint of the Announcements Service.
	 *
	 * PREFER THE UFUNCTION OVERLOAD AS OPPOSED TO THIS. THIS MAINLY EXISTS TO ALLOW LAMBDA BINDING THE HANDLER.
	 * (Dynamic delegates do not allow for that so... we autogen this one to make experimenting in CPP a bit faster).
	 * 
	 * @param UserSlot The Authenticated User Slot that is making this request.
	 * @param Request The Request UObject. All (de)serialized data the request data creates is tied to the lifecycle of this object.
	 * @param Handler A callback that defines how to handle success, error and completion. 
	 */
	void CPP_ObjectAnnouncementsDeleteAnnouncements(const FUserSlot& UserSlot, UObjectAnnouncementsDeleteAnnouncementsRequest* Request, const FOnObjectAnnouncementsDeleteAnnouncementsFullResponse& Handler) const;


	

	
	/**
	 * @brief Makes an authenticated request to the Get /basic/announcements/list/tags endpoint of the Announcements Service.
	 *
	 * @param UserSlot The authenticated UserSlot with the user making the request. 
	 * @param Request The Request UObject. All (de)serialized data the request data creates is tied to the lifecycle of this object.
	 * @param OnSuccess What to do if the requests receives a successful response.
	 * @param OnError What to do if the request receives an error response.
	 * @param OnComplete What to after either OnSuccess or OnError have finished executing.
	 * @param OutRequestId The Request Id -- used to query information about the request or to cancel it while it's in flight. 
	 */
	UFUNCTION(BlueprintCallable, Category="Beam|APIs|Announcements", meta=(AutoCreateRefTerm="UserSlot,OnSuccess,OnError,OnComplete"))
	void GetListTags(const FUserSlot& UserSlot, UGetListTagsRequest* Request, const FOnGetListTagsSuccess& OnSuccess, const FOnGetListTagsError& OnError, const FOnGetListTagsComplete& OnComplete, int64& OutRequestId);

		
	/**
	 * @brief Makes an authenticated request to the Get /basic/announcements/list endpoint of the Announcements Service.
	 *
	 * @param UserSlot The authenticated UserSlot with the user making the request. 
	 * @param Request The Request UObject. All (de)serialized data the request data creates is tied to the lifecycle of this object.
	 * @param OnSuccess What to do if the requests receives a successful response.
	 * @param OnError What to do if the request receives an error response.
	 * @param OnComplete What to after either OnSuccess or OnError have finished executing.
	 * @param OutRequestId The Request Id -- used to query information about the request or to cancel it while it's in flight. 
	 */
	UFUNCTION(BlueprintCallable, Category="Beam|APIs|Announcements", meta=(AutoCreateRefTerm="UserSlot,OnSuccess,OnError,OnComplete"))
	void GetList(const FUserSlot& UserSlot, UBasicAnnouncementsGetListRequest* Request, const FOnBasicAnnouncementsGetListSuccess& OnSuccess, const FOnBasicAnnouncementsGetListError& OnError, const FOnBasicAnnouncementsGetListComplete& OnComplete, int64& OutRequestId);

		
	/**
	 * @brief Makes an authenticated request to the Get /basic/announcements/search endpoint of the Announcements Service.
	 *
	 * @param UserSlot The authenticated UserSlot with the user making the request. 
	 * @param Request The Request UObject. All (de)serialized data the request data creates is tied to the lifecycle of this object.
	 * @param OnSuccess What to do if the requests receives a successful response.
	 * @param OnError What to do if the request receives an error response.
	 * @param OnComplete What to after either OnSuccess or OnError have finished executing.
	 * @param OutRequestId The Request Id -- used to query information about the request or to cancel it while it's in flight. 
	 */
	UFUNCTION(BlueprintCallable, Category="Beam|APIs|Announcements", meta=(AutoCreateRefTerm="UserSlot,OnSuccess,OnError,OnComplete"))
	void GetSearch(const FUserSlot& UserSlot, UBasicAnnouncementsGetSearchRequest* Request, const FOnBasicAnnouncementsGetSearchSuccess& OnSuccess, const FOnBasicAnnouncementsGetSearchError& OnError, const FOnBasicAnnouncementsGetSearchComplete& OnComplete, int64& OutRequestId);

		
	/**
	 * @brief Makes an authenticated request to the Get /basic/announcements/list/definitions endpoint of the Announcements Service.
	 *
	 * @param UserSlot The authenticated UserSlot with the user making the request. 
	 * @param Request The Request UObject. All (de)serialized data the request data creates is tied to the lifecycle of this object.
	 * @param OnSuccess What to do if the requests receives a successful response.
	 * @param OnError What to do if the request receives an error response.
	 * @param OnComplete What to after either OnSuccess or OnError have finished executing.
	 * @param OutRequestId The Request Id -- used to query information about the request or to cancel it while it's in flight. 
	 */
	UFUNCTION(BlueprintCallable, Category="Beam|APIs|Announcements", meta=(AutoCreateRefTerm="UserSlot,OnSuccess,OnError,OnComplete"))
	void GetListDefinitions(const FUserSlot& UserSlot, UGetListDefinitionsRequest* Request, const FOnGetListDefinitionsSuccess& OnSuccess, const FOnGetListDefinitionsError& OnError, const FOnGetListDefinitionsComplete& OnComplete, int64& OutRequestId);

		
	/**
	 * @brief Makes an authenticated request to the Post /basic/announcements/ endpoint of the Announcements Service.
	 *
	 * @param UserSlot The authenticated UserSlot with the user making the request. 
	 * @param Request The Request UObject. All (de)serialized data the request data creates is tied to the lifecycle of this object.
	 * @param OnSuccess What to do if the requests receives a successful response.
	 * @param OnError What to do if the request receives an error response.
	 * @param OnComplete What to after either OnSuccess or OnError have finished executing.
	 * @param OutRequestId The Request Id -- used to query information about the request or to cancel it while it's in flight. 
	 */
	UFUNCTION(BlueprintCallable, Category="Beam|APIs|Announcements", meta=(AutoCreateRefTerm="UserSlot,OnSuccess,OnError,OnComplete"))
	void PostAnnouncements(const FUserSlot& UserSlot, UPostAnnouncementsRequest* Request, const FOnPostAnnouncementsSuccess& OnSuccess, const FOnPostAnnouncementsError& OnError, const FOnPostAnnouncementsComplete& OnComplete, int64& OutRequestId);

		
	/**
	 * @brief Makes an authenticated request to the Delete /basic/announcements/ endpoint of the Announcements Service.
	 *
	 * @param UserSlot The authenticated UserSlot with the user making the request. 
	 * @param Request The Request UObject. All (de)serialized data the request data creates is tied to the lifecycle of this object.
	 * @param OnSuccess What to do if the requests receives a successful response.
	 * @param OnError What to do if the request receives an error response.
	 * @param OnComplete What to after either OnSuccess or OnError have finished executing.
	 * @param OutRequestId The Request Id -- used to query information about the request or to cancel it while it's in flight. 
	 */
	UFUNCTION(BlueprintCallable, Category="Beam|APIs|Announcements", meta=(AutoCreateRefTerm="UserSlot,OnSuccess,OnError,OnComplete"))
	void BasicAnnouncementsDeleteAnnouncements(const FUserSlot& UserSlot, UBasicAnnouncementsDeleteAnnouncementsRequest* Request, const FOnBasicAnnouncementsDeleteAnnouncementsSuccess& OnSuccess, const FOnBasicAnnouncementsDeleteAnnouncementsError& OnError, const FOnBasicAnnouncementsDeleteAnnouncementsComplete& OnComplete, int64& OutRequestId);

		
	/**
	 * @brief Makes an authenticated request to the Get /basic/announcements/content endpoint of the Announcements Service.
	 *
	 * @param UserSlot The authenticated UserSlot with the user making the request. 
	 * @param Request The Request UObject. All (de)serialized data the request data creates is tied to the lifecycle of this object.
	 * @param OnSuccess What to do if the requests receives a successful response.
	 * @param OnError What to do if the request receives an error response.
	 * @param OnComplete What to after either OnSuccess or OnError have finished executing.
	 * @param OutRequestId The Request Id -- used to query information about the request or to cancel it while it's in flight. 
	 */
	UFUNCTION(BlueprintCallable, Category="Beam|APIs|Announcements", meta=(AutoCreateRefTerm="UserSlot,OnSuccess,OnError,OnComplete"))
	void GetContent(const FUserSlot& UserSlot, UBasicAnnouncementsGetContentRequest* Request, const FOnBasicAnnouncementsGetContentSuccess& OnSuccess, const FOnBasicAnnouncementsGetContentError& OnError, const FOnBasicAnnouncementsGetContentComplete& OnComplete, int64& OutRequestId);

		
	/**
	 * @brief Makes an authenticated request to the Put /object/announcements/{objectId}/read endpoint of the Announcements Service.
	 *
	 * @param UserSlot The authenticated UserSlot with the user making the request. 
	 * @param Request The Request UObject. All (de)serialized data the request data creates is tied to the lifecycle of this object.
	 * @param OnSuccess What to do if the requests receives a successful response.
	 * @param OnError What to do if the request receives an error response.
	 * @param OnComplete What to after either OnSuccess or OnError have finished executing.
	 * @param OutRequestId The Request Id -- used to query information about the request or to cancel it while it's in flight. 
	 */
	UFUNCTION(BlueprintCallable, Category="Beam|APIs|Announcements", meta=(AutoCreateRefTerm="UserSlot,OnSuccess,OnError,OnComplete"))
	void PutRead(const FUserSlot& UserSlot, UPutReadRequest* Request, const FOnPutReadSuccess& OnSuccess, const FOnPutReadError& OnError, const FOnPutReadComplete& OnComplete, int64& OutRequestId);

		
	/**
	 * @brief Makes an authenticated request to the Post /object/announcements/{objectId}/claim endpoint of the Announcements Service.
	 *
	 * @param UserSlot The authenticated UserSlot with the user making the request. 
	 * @param Request The Request UObject. All (de)serialized data the request data creates is tied to the lifecycle of this object.
	 * @param OnSuccess What to do if the requests receives a successful response.
	 * @param OnError What to do if the request receives an error response.
	 * @param OnComplete What to after either OnSuccess or OnError have finished executing.
	 * @param OutRequestId The Request Id -- used to query information about the request or to cancel it while it's in flight. 
	 */
	UFUNCTION(BlueprintCallable, Category="Beam|APIs|Announcements", meta=(AutoCreateRefTerm="UserSlot,OnSuccess,OnError,OnComplete"))
	void PostClaim(const FUserSlot& UserSlot, UObjectAnnouncementsPostClaimRequest* Request, const FOnObjectAnnouncementsPostClaimSuccess& OnSuccess, const FOnObjectAnnouncementsPostClaimError& OnError, const FOnObjectAnnouncementsPostClaimComplete& OnComplete, int64& OutRequestId);

		
	/**
	 * @brief Makes an authenticated request to the Get /object/announcements/{objectId}/raw endpoint of the Announcements Service.
	 *
	 * @param UserSlot The authenticated UserSlot with the user making the request. 
	 * @param Request The Request UObject. All (de)serialized data the request data creates is tied to the lifecycle of this object.
	 * @param OnSuccess What to do if the requests receives a successful response.
	 * @param OnError What to do if the request receives an error response.
	 * @param OnComplete What to after either OnSuccess or OnError have finished executing.
	 * @param OutRequestId The Request Id -- used to query information about the request or to cancel it while it's in flight. 
	 */
	UFUNCTION(BlueprintCallable, Category="Beam|APIs|Announcements", meta=(AutoCreateRefTerm="UserSlot,OnSuccess,OnError,OnComplete"))
	void GetRaw(const FUserSlot& UserSlot, UGetRawRequest* Request, const FOnGetRawSuccess& OnSuccess, const FOnGetRawError& OnError, const FOnGetRawComplete& OnComplete, int64& OutRequestId);

		
	/**
	 * @brief Makes an authenticated request to the Get /object/announcements/{objectId}/ endpoint of the Announcements Service.
	 *
	 * @param UserSlot The authenticated UserSlot with the user making the request. 
	 * @param Request The Request UObject. All (de)serialized data the request data creates is tied to the lifecycle of this object.
	 * @param OnSuccess What to do if the requests receives a successful response.
	 * @param OnError What to do if the request receives an error response.
	 * @param OnComplete What to after either OnSuccess or OnError have finished executing.
	 * @param OutRequestId The Request Id -- used to query information about the request or to cancel it while it's in flight. 
	 */
	UFUNCTION(BlueprintCallable, Category="Beam|APIs|Announcements", meta=(AutoCreateRefTerm="UserSlot,OnSuccess,OnError,OnComplete"))
	void GetAnnouncements(const FUserSlot& UserSlot, UGetAnnouncementsRequest* Request, const FOnGetAnnouncementsSuccess& OnSuccess, const FOnGetAnnouncementsError& OnError, const FOnGetAnnouncementsComplete& OnComplete, int64& OutRequestId);

		
	/**
	 * @brief Makes an authenticated request to the Delete /object/announcements/{objectId}/ endpoint of the Announcements Service.
	 *
	 * @param UserSlot The authenticated UserSlot with the user making the request. 
	 * @param Request The Request UObject. All (de)serialized data the request data creates is tied to the lifecycle of this object.
	 * @param OnSuccess What to do if the requests receives a successful response.
	 * @param OnError What to do if the request receives an error response.
	 * @param OnComplete What to after either OnSuccess or OnError have finished executing.
	 * @param OutRequestId The Request Id -- used to query information about the request or to cancel it while it's in flight. 
	 */
	UFUNCTION(BlueprintCallable, Category="Beam|APIs|Announcements", meta=(AutoCreateRefTerm="UserSlot,OnSuccess,OnError,OnComplete"))
	void ObjectAnnouncementsDeleteAnnouncements(const FUserSlot& UserSlot, UObjectAnnouncementsDeleteAnnouncementsRequest* Request, const FOnObjectAnnouncementsDeleteAnnouncementsSuccess& OnSuccess, const FOnObjectAnnouncementsDeleteAnnouncementsError& OnError, const FOnObjectAnnouncementsDeleteAnnouncementsComplete& OnComplete, int64& OutRequestId);
	
};
