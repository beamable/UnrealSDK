

#pragma once

#include "CoreMinimal.h"
#include "BeamBackend/BeamBackend.h"

#include "Cloudsaving/GetCloudsavingRequest.h"
#include "Cloudsaving/PostDataReplaceRequest.h"
#include "Cloudsaving/DeleteDataRequest.h"
#include "Cloudsaving/PostDataDownloadURLRequest.h"
#include "Cloudsaving/GetDataMetadataRequest.h"
#include "Cloudsaving/PostDataDownloadURLFromPortalRequest.h"
#include "Cloudsaving/PutDataMoveRequest.h"
#include "Cloudsaving/PutDataMoveFromPortalRequest.h"
#include "Cloudsaving/PostDataUploadURLFromPortalRequest.h"
#include "Cloudsaving/PutDataCommitManifestRequest.h"
#include "Cloudsaving/PostDataUploadURLRequest.h"

#include "BeamCloudsavingApi.generated.h"


/**
 * Subsystem containing request calls for the Cloudsaving service.
 */
UCLASS(BlueprintType)
class BEAMABLECORE_API UBeamCloudsavingApi : public UEngineSubsystem
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
	void BP_GetCloudsavingImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, FBeamConnectivity& ConnectivityStatus, UGetCloudsavingRequest* RequestData,
	                                const FOnGetCloudsavingSuccess& OnSuccess, const FOnGetCloudsavingError& OnError, const FOnGetCloudsavingComplete& OnComplete,
	                                int64& OutRequestId) const;
	/**
	 * @brief Overload version for binding lambdas when in C++ land. Prefer the BP version whenever possible, this is here mostly for quick experimentation purposes.	 
	 */
	void CPP_GetCloudsavingImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, FBeamConnectivity& ConnectivityStatus, UGetCloudsavingRequest* RequestData,
	                                 const FOnGetCloudsavingFullResponse& Handler) const;


	
	/**
	 * @brief Private implementation for requests that require authentication that all overloaded BP UFunctions call.	  
	 */
	void BP_PostDataReplaceImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, const FBeamAuthToken& AuthToken, FBeamConnectivity& ConnectivityStatus, UPostDataReplaceRequest* RequestData,
	                  const FOnPostDataReplaceSuccess& OnSuccess, const FOnPostDataReplaceError& OnError, const FOnPostDataReplaceComplete& OnComplete, int64& OutRequestId) const;
	/**
	 * @brief Overload version for binding lambdas when in C++ land. Prefer the BP version whenever possible, this is here mostly for quick experimentation purposes.	 
	 */
	void CPP_PostDataReplaceImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, const FBeamAuthToken& AuthToken, FBeamConnectivity& ConnectivityStatus, UPostDataReplaceRequest* RequestData,
	                   const FOnPostDataReplaceFullResponse& Handler) const;
		
	/**
	 * @brief Private implementation for requests that require authentication that all overloaded BP UFunctions call.	  
	 */
	void BP_DeleteDataImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, const FBeamAuthToken& AuthToken, FBeamConnectivity& ConnectivityStatus, UDeleteDataRequest* RequestData,
	                  const FOnDeleteDataSuccess& OnSuccess, const FOnDeleteDataError& OnError, const FOnDeleteDataComplete& OnComplete, int64& OutRequestId) const;
	/**
	 * @brief Overload version for binding lambdas when in C++ land. Prefer the BP version whenever possible, this is here mostly for quick experimentation purposes.	 
	 */
	void CPP_DeleteDataImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, const FBeamAuthToken& AuthToken, FBeamConnectivity& ConnectivityStatus, UDeleteDataRequest* RequestData,
	                   const FOnDeleteDataFullResponse& Handler) const;
		
	/**
	 * @brief Private implementation for requests that require authentication that all overloaded BP UFunctions call.	  
	 */
	void BP_PostDataDownloadURLImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, const FBeamAuthToken& AuthToken, FBeamConnectivity& ConnectivityStatus, UPostDataDownloadURLRequest* RequestData,
	                  const FOnPostDataDownloadURLSuccess& OnSuccess, const FOnPostDataDownloadURLError& OnError, const FOnPostDataDownloadURLComplete& OnComplete, int64& OutRequestId) const;
	/**
	 * @brief Overload version for binding lambdas when in C++ land. Prefer the BP version whenever possible, this is here mostly for quick experimentation purposes.	 
	 */
	void CPP_PostDataDownloadURLImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, const FBeamAuthToken& AuthToken, FBeamConnectivity& ConnectivityStatus, UPostDataDownloadURLRequest* RequestData,
	                   const FOnPostDataDownloadURLFullResponse& Handler) const;
		
	/**
	 * @brief Private implementation for requests that require authentication that all overloaded BP UFunctions call.	  
	 */
	void BP_GetDataMetadataImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, const FBeamAuthToken& AuthToken, FBeamConnectivity& ConnectivityStatus, UGetDataMetadataRequest* RequestData,
	                  const FOnGetDataMetadataSuccess& OnSuccess, const FOnGetDataMetadataError& OnError, const FOnGetDataMetadataComplete& OnComplete, int64& OutRequestId) const;
	/**
	 * @brief Overload version for binding lambdas when in C++ land. Prefer the BP version whenever possible, this is here mostly for quick experimentation purposes.	 
	 */
	void CPP_GetDataMetadataImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, const FBeamAuthToken& AuthToken, FBeamConnectivity& ConnectivityStatus, UGetDataMetadataRequest* RequestData,
	                   const FOnGetDataMetadataFullResponse& Handler) const;
		
	/**
	 * @brief Private implementation for requests that require authentication that all overloaded BP UFunctions call.	  
	 */
	void BP_PostDataDownloadURLFromPortalImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, const FBeamAuthToken& AuthToken, FBeamConnectivity& ConnectivityStatus, UPostDataDownloadURLFromPortalRequest* RequestData,
	                  const FOnPostDataDownloadURLFromPortalSuccess& OnSuccess, const FOnPostDataDownloadURLFromPortalError& OnError, const FOnPostDataDownloadURLFromPortalComplete& OnComplete, int64& OutRequestId) const;
	/**
	 * @brief Overload version for binding lambdas when in C++ land. Prefer the BP version whenever possible, this is here mostly for quick experimentation purposes.	 
	 */
	void CPP_PostDataDownloadURLFromPortalImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, const FBeamAuthToken& AuthToken, FBeamConnectivity& ConnectivityStatus, UPostDataDownloadURLFromPortalRequest* RequestData,
	                   const FOnPostDataDownloadURLFromPortalFullResponse& Handler) const;
		
	/**
	 * @brief Private implementation for requests that require authentication that all overloaded BP UFunctions call.	  
	 */
	void BP_PutDataMoveImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, const FBeamAuthToken& AuthToken, FBeamConnectivity& ConnectivityStatus, UPutDataMoveRequest* RequestData,
	                  const FOnPutDataMoveSuccess& OnSuccess, const FOnPutDataMoveError& OnError, const FOnPutDataMoveComplete& OnComplete, int64& OutRequestId) const;
	/**
	 * @brief Overload version for binding lambdas when in C++ land. Prefer the BP version whenever possible, this is here mostly for quick experimentation purposes.	 
	 */
	void CPP_PutDataMoveImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, const FBeamAuthToken& AuthToken, FBeamConnectivity& ConnectivityStatus, UPutDataMoveRequest* RequestData,
	                   const FOnPutDataMoveFullResponse& Handler) const;
		
	/**
	 * @brief Private implementation for requests that require authentication that all overloaded BP UFunctions call.	  
	 */
	void BP_PutDataMoveFromPortalImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, const FBeamAuthToken& AuthToken, FBeamConnectivity& ConnectivityStatus, UPutDataMoveFromPortalRequest* RequestData,
	                  const FOnPutDataMoveFromPortalSuccess& OnSuccess, const FOnPutDataMoveFromPortalError& OnError, const FOnPutDataMoveFromPortalComplete& OnComplete, int64& OutRequestId) const;
	/**
	 * @brief Overload version for binding lambdas when in C++ land. Prefer the BP version whenever possible, this is here mostly for quick experimentation purposes.	 
	 */
	void CPP_PutDataMoveFromPortalImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, const FBeamAuthToken& AuthToken, FBeamConnectivity& ConnectivityStatus, UPutDataMoveFromPortalRequest* RequestData,
	                   const FOnPutDataMoveFromPortalFullResponse& Handler) const;
		
	/**
	 * @brief Private implementation for requests that require authentication that all overloaded BP UFunctions call.	  
	 */
	void BP_PostDataUploadURLFromPortalImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, const FBeamAuthToken& AuthToken, FBeamConnectivity& ConnectivityStatus, UPostDataUploadURLFromPortalRequest* RequestData,
	                  const FOnPostDataUploadURLFromPortalSuccess& OnSuccess, const FOnPostDataUploadURLFromPortalError& OnError, const FOnPostDataUploadURLFromPortalComplete& OnComplete, int64& OutRequestId) const;
	/**
	 * @brief Overload version for binding lambdas when in C++ land. Prefer the BP version whenever possible, this is here mostly for quick experimentation purposes.	 
	 */
	void CPP_PostDataUploadURLFromPortalImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, const FBeamAuthToken& AuthToken, FBeamConnectivity& ConnectivityStatus, UPostDataUploadURLFromPortalRequest* RequestData,
	                   const FOnPostDataUploadURLFromPortalFullResponse& Handler) const;
		
	/**
	 * @brief Private implementation for requests that require authentication that all overloaded BP UFunctions call.	  
	 */
	void BP_PutDataCommitManifestImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, const FBeamAuthToken& AuthToken, FBeamConnectivity& ConnectivityStatus, UPutDataCommitManifestRequest* RequestData,
	                  const FOnPutDataCommitManifestSuccess& OnSuccess, const FOnPutDataCommitManifestError& OnError, const FOnPutDataCommitManifestComplete& OnComplete, int64& OutRequestId) const;
	/**
	 * @brief Overload version for binding lambdas when in C++ land. Prefer the BP version whenever possible, this is here mostly for quick experimentation purposes.	 
	 */
	void CPP_PutDataCommitManifestImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, const FBeamAuthToken& AuthToken, FBeamConnectivity& ConnectivityStatus, UPutDataCommitManifestRequest* RequestData,
	                   const FOnPutDataCommitManifestFullResponse& Handler) const;
		
	/**
	 * @brief Private implementation for requests that require authentication that all overloaded BP UFunctions call.	  
	 */
	void BP_PostDataUploadURLImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, const FBeamAuthToken& AuthToken, FBeamConnectivity& ConnectivityStatus, UPostDataUploadURLRequest* RequestData,
	                  const FOnPostDataUploadURLSuccess& OnSuccess, const FOnPostDataUploadURLError& OnError, const FOnPostDataUploadURLComplete& OnComplete, int64& OutRequestId) const;
	/**
	 * @brief Overload version for binding lambdas when in C++ land. Prefer the BP version whenever possible, this is here mostly for quick experimentation purposes.	 
	 */
	void CPP_PostDataUploadURLImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, const FBeamAuthToken& AuthToken, FBeamConnectivity& ConnectivityStatus, UPostDataUploadURLRequest* RequestData,
	                   const FOnPostDataUploadURLFullResponse& Handler) const;

public:
	
	/** Used by a helper blueprint node so that you can easily chain requests in BP-land. */
	UFUNCTION(BlueprintPure, BlueprintInternalUseOnly)
	static UBeamCloudsavingApi* GetSelf() { return GEngine->GetEngineSubsystem<UBeamCloudsavingApi>(); }

	
	/**
	 * @brief Makes a request to the Get /basic/cloudsaving/ endpoint of the Cloudsaving Service.
	 *
	 * PREFER THE UFUNCTION OVERLOAD AS OPPOSED TO THIS. THIS MAINLY EXISTS TO ALLOW LAMBDA BINDING THE HANDLER.
	 * (Dynamic delegates do not allow for that so... we autogen this one to make experimenting in CPP a bit faster and for whenever you need to capture variables).
	 * 
	 * @param Request The Request UObject. All (de)serialized data the request data creates is tied to the lifecycle of this object.
	 * @param Handler A callback that defines how to handle success, error and completion. 
	 */
	void CPP_GetCloudsaving(UGetCloudsavingRequest* Request, const FOnGetCloudsavingFullResponse& Handler) const;


	
	/**
	 * @brief Makes an authenticated request to the Post /basic/cloudsaving/data/replace endpoint of the Cloudsaving Service.
	 *
	 * PREFER THE UFUNCTION OVERLOAD AS OPPOSED TO THIS. THIS MAINLY EXISTS TO ALLOW LAMBDA BINDING THE HANDLER.
	 * (Dynamic delegates do not allow for that so... we autogen this one to make experimenting in CPP a bit faster).
	 * 
	 * @param UserSlot The Authenticated User Slot that is making this request.
	 * @param Request The Request UObject. All (de)serialized data the request data creates is tied to the lifecycle of this object.
	 * @param Handler A callback that defines how to handle success, error and completion. 
	 */
	void CPP_PostDataReplace(const FUserSlot& UserSlot, UPostDataReplaceRequest* Request, const FOnPostDataReplaceFullResponse& Handler) const;

		
	/**
	 * @brief Makes an authenticated request to the Delete /basic/cloudsaving/data endpoint of the Cloudsaving Service.
	 *
	 * PREFER THE UFUNCTION OVERLOAD AS OPPOSED TO THIS. THIS MAINLY EXISTS TO ALLOW LAMBDA BINDING THE HANDLER.
	 * (Dynamic delegates do not allow for that so... we autogen this one to make experimenting in CPP a bit faster).
	 * 
	 * @param UserSlot The Authenticated User Slot that is making this request.
	 * @param Request The Request UObject. All (de)serialized data the request data creates is tied to the lifecycle of this object.
	 * @param Handler A callback that defines how to handle success, error and completion. 
	 */
	void CPP_DeleteData(const FUserSlot& UserSlot, UDeleteDataRequest* Request, const FOnDeleteDataFullResponse& Handler) const;

		
	/**
	 * @brief Makes an authenticated request to the Post /basic/cloudsaving/data/downloadURL endpoint of the Cloudsaving Service.
	 *
	 * PREFER THE UFUNCTION OVERLOAD AS OPPOSED TO THIS. THIS MAINLY EXISTS TO ALLOW LAMBDA BINDING THE HANDLER.
	 * (Dynamic delegates do not allow for that so... we autogen this one to make experimenting in CPP a bit faster).
	 * 
	 * @param UserSlot The Authenticated User Slot that is making this request.
	 * @param Request The Request UObject. All (de)serialized data the request data creates is tied to the lifecycle of this object.
	 * @param Handler A callback that defines how to handle success, error and completion. 
	 */
	void CPP_PostDataDownloadURL(const FUserSlot& UserSlot, UPostDataDownloadURLRequest* Request, const FOnPostDataDownloadURLFullResponse& Handler) const;

		
	/**
	 * @brief Makes an authenticated request to the Get /basic/cloudsaving/data/metadata endpoint of the Cloudsaving Service.
	 *
	 * PREFER THE UFUNCTION OVERLOAD AS OPPOSED TO THIS. THIS MAINLY EXISTS TO ALLOW LAMBDA BINDING THE HANDLER.
	 * (Dynamic delegates do not allow for that so... we autogen this one to make experimenting in CPP a bit faster).
	 * 
	 * @param UserSlot The Authenticated User Slot that is making this request.
	 * @param Request The Request UObject. All (de)serialized data the request data creates is tied to the lifecycle of this object.
	 * @param Handler A callback that defines how to handle success, error and completion. 
	 */
	void CPP_GetDataMetadata(const FUserSlot& UserSlot, UGetDataMetadataRequest* Request, const FOnGetDataMetadataFullResponse& Handler) const;

		
	/**
	 * @brief Makes an authenticated request to the Post /basic/cloudsaving/data/downloadURLFromPortal endpoint of the Cloudsaving Service.
	 *
	 * PREFER THE UFUNCTION OVERLOAD AS OPPOSED TO THIS. THIS MAINLY EXISTS TO ALLOW LAMBDA BINDING THE HANDLER.
	 * (Dynamic delegates do not allow for that so... we autogen this one to make experimenting in CPP a bit faster).
	 * 
	 * @param UserSlot The Authenticated User Slot that is making this request.
	 * @param Request The Request UObject. All (de)serialized data the request data creates is tied to the lifecycle of this object.
	 * @param Handler A callback that defines how to handle success, error and completion. 
	 */
	void CPP_PostDataDownloadURLFromPortal(const FUserSlot& UserSlot, UPostDataDownloadURLFromPortalRequest* Request, const FOnPostDataDownloadURLFromPortalFullResponse& Handler) const;

		
	/**
	 * @brief Makes an authenticated request to the Put /basic/cloudsaving/data/move endpoint of the Cloudsaving Service.
	 *
	 * PREFER THE UFUNCTION OVERLOAD AS OPPOSED TO THIS. THIS MAINLY EXISTS TO ALLOW LAMBDA BINDING THE HANDLER.
	 * (Dynamic delegates do not allow for that so... we autogen this one to make experimenting in CPP a bit faster).
	 * 
	 * @param UserSlot The Authenticated User Slot that is making this request.
	 * @param Request The Request UObject. All (de)serialized data the request data creates is tied to the lifecycle of this object.
	 * @param Handler A callback that defines how to handle success, error and completion. 
	 */
	void CPP_PutDataMove(const FUserSlot& UserSlot, UPutDataMoveRequest* Request, const FOnPutDataMoveFullResponse& Handler) const;

		
	/**
	 * @brief Makes an authenticated request to the Put /basic/cloudsaving/data/moveFromPortal endpoint of the Cloudsaving Service.
	 *
	 * PREFER THE UFUNCTION OVERLOAD AS OPPOSED TO THIS. THIS MAINLY EXISTS TO ALLOW LAMBDA BINDING THE HANDLER.
	 * (Dynamic delegates do not allow for that so... we autogen this one to make experimenting in CPP a bit faster).
	 * 
	 * @param UserSlot The Authenticated User Slot that is making this request.
	 * @param Request The Request UObject. All (de)serialized data the request data creates is tied to the lifecycle of this object.
	 * @param Handler A callback that defines how to handle success, error and completion. 
	 */
	void CPP_PutDataMoveFromPortal(const FUserSlot& UserSlot, UPutDataMoveFromPortalRequest* Request, const FOnPutDataMoveFromPortalFullResponse& Handler) const;

		
	/**
	 * @brief Makes an authenticated request to the Post /basic/cloudsaving/data/uploadURLFromPortal endpoint of the Cloudsaving Service.
	 *
	 * PREFER THE UFUNCTION OVERLOAD AS OPPOSED TO THIS. THIS MAINLY EXISTS TO ALLOW LAMBDA BINDING THE HANDLER.
	 * (Dynamic delegates do not allow for that so... we autogen this one to make experimenting in CPP a bit faster).
	 * 
	 * @param UserSlot The Authenticated User Slot that is making this request.
	 * @param Request The Request UObject. All (de)serialized data the request data creates is tied to the lifecycle of this object.
	 * @param Handler A callback that defines how to handle success, error and completion. 
	 */
	void CPP_PostDataUploadURLFromPortal(const FUserSlot& UserSlot, UPostDataUploadURLFromPortalRequest* Request, const FOnPostDataUploadURLFromPortalFullResponse& Handler) const;

		
	/**
	 * @brief Makes an authenticated request to the Put /basic/cloudsaving/data/commitManifest endpoint of the Cloudsaving Service.
	 *
	 * PREFER THE UFUNCTION OVERLOAD AS OPPOSED TO THIS. THIS MAINLY EXISTS TO ALLOW LAMBDA BINDING THE HANDLER.
	 * (Dynamic delegates do not allow for that so... we autogen this one to make experimenting in CPP a bit faster).
	 * 
	 * @param UserSlot The Authenticated User Slot that is making this request.
	 * @param Request The Request UObject. All (de)serialized data the request data creates is tied to the lifecycle of this object.
	 * @param Handler A callback that defines how to handle success, error and completion. 
	 */
	void CPP_PutDataCommitManifest(const FUserSlot& UserSlot, UPutDataCommitManifestRequest* Request, const FOnPutDataCommitManifestFullResponse& Handler) const;

		
	/**
	 * @brief Makes an authenticated request to the Post /basic/cloudsaving/data/uploadURL endpoint of the Cloudsaving Service.
	 *
	 * PREFER THE UFUNCTION OVERLOAD AS OPPOSED TO THIS. THIS MAINLY EXISTS TO ALLOW LAMBDA BINDING THE HANDLER.
	 * (Dynamic delegates do not allow for that so... we autogen this one to make experimenting in CPP a bit faster).
	 * 
	 * @param UserSlot The Authenticated User Slot that is making this request.
	 * @param Request The Request UObject. All (de)serialized data the request data creates is tied to the lifecycle of this object.
	 * @param Handler A callback that defines how to handle success, error and completion. 
	 */
	void CPP_PostDataUploadURL(const FUserSlot& UserSlot, UPostDataUploadURLRequest* Request, const FOnPostDataUploadURLFullResponse& Handler) const;


	
	/**
	 * @brief Makes a request to the Get /basic/cloudsaving/ endpoint of the Cloudsaving Service.
	 *
	 * @param Request The Request UObject. All (de)serialized data the request data creates is tied to the lifecycle of this object.
	 * @param OnSuccess What to do if the requests receives a successful response.
	 * @param OnError What to do if the request receives an error response.
	 * @param OnComplete What to after either OnSuccess or OnError have finished executing.
	 * @param OutRequestId The Request Id -- used to query information about the request or to cancel it while it's in flight. 
	 */
	UFUNCTION(BlueprintCallable, Category="Beam|APIs|Cloudsaving", meta=(AutoCreateRefTerm="OnSuccess,OnError,OnComplete"))
	void GetCloudsaving(UGetCloudsavingRequest* Request, const FOnGetCloudsavingSuccess& OnSuccess, const FOnGetCloudsavingError& OnError, const FOnGetCloudsavingComplete& OnComplete,
								 int64& OutRequestId);


	
	/**
	 * @brief Makes an authenticated request to the Post /basic/cloudsaving/data/replace endpoint of the Cloudsaving Service.
	 *
	 * @param UserSlot The authenticated UserSlot with the user making the request. 
	 * @param Request The Request UObject. All (de)serialized data the request data creates is tied to the lifecycle of this object.
	 * @param OnSuccess What to do if the requests receives a successful response.
	 * @param OnError What to do if the request receives an error response.
	 * @param OnComplete What to after either OnSuccess or OnError have finished executing.
	 * @param OutRequestId The Request Id -- used to query information about the request or to cancel it while it's in flight. 
	 */
	UFUNCTION(BlueprintCallable, Category="Beam|APIs|Cloudsaving", meta=(AutoCreateRefTerm="UserSlot,OnSuccess,OnError,OnComplete"))
	void PostDataReplace(const FUserSlot& UserSlot, UPostDataReplaceRequest* Request, const FOnPostDataReplaceSuccess& OnSuccess, const FOnPostDataReplaceError& OnError, const FOnPostDataReplaceComplete& OnComplete, int64& OutRequestId);

		
	/**
	 * @brief Makes an authenticated request to the Delete /basic/cloudsaving/data endpoint of the Cloudsaving Service.
	 *
	 * @param UserSlot The authenticated UserSlot with the user making the request. 
	 * @param Request The Request UObject. All (de)serialized data the request data creates is tied to the lifecycle of this object.
	 * @param OnSuccess What to do if the requests receives a successful response.
	 * @param OnError What to do if the request receives an error response.
	 * @param OnComplete What to after either OnSuccess or OnError have finished executing.
	 * @param OutRequestId The Request Id -- used to query information about the request or to cancel it while it's in flight. 
	 */
	UFUNCTION(BlueprintCallable, Category="Beam|APIs|Cloudsaving", meta=(AutoCreateRefTerm="UserSlot,OnSuccess,OnError,OnComplete"))
	void DeleteData(const FUserSlot& UserSlot, UDeleteDataRequest* Request, const FOnDeleteDataSuccess& OnSuccess, const FOnDeleteDataError& OnError, const FOnDeleteDataComplete& OnComplete, int64& OutRequestId);

		
	/**
	 * @brief Makes an authenticated request to the Post /basic/cloudsaving/data/downloadURL endpoint of the Cloudsaving Service.
	 *
	 * @param UserSlot The authenticated UserSlot with the user making the request. 
	 * @param Request The Request UObject. All (de)serialized data the request data creates is tied to the lifecycle of this object.
	 * @param OnSuccess What to do if the requests receives a successful response.
	 * @param OnError What to do if the request receives an error response.
	 * @param OnComplete What to after either OnSuccess or OnError have finished executing.
	 * @param OutRequestId The Request Id -- used to query information about the request or to cancel it while it's in flight. 
	 */
	UFUNCTION(BlueprintCallable, Category="Beam|APIs|Cloudsaving", meta=(AutoCreateRefTerm="UserSlot,OnSuccess,OnError,OnComplete"))
	void PostDataDownloadURL(const FUserSlot& UserSlot, UPostDataDownloadURLRequest* Request, const FOnPostDataDownloadURLSuccess& OnSuccess, const FOnPostDataDownloadURLError& OnError, const FOnPostDataDownloadURLComplete& OnComplete, int64& OutRequestId);

		
	/**
	 * @brief Makes an authenticated request to the Get /basic/cloudsaving/data/metadata endpoint of the Cloudsaving Service.
	 *
	 * @param UserSlot The authenticated UserSlot with the user making the request. 
	 * @param Request The Request UObject. All (de)serialized data the request data creates is tied to the lifecycle of this object.
	 * @param OnSuccess What to do if the requests receives a successful response.
	 * @param OnError What to do if the request receives an error response.
	 * @param OnComplete What to after either OnSuccess or OnError have finished executing.
	 * @param OutRequestId The Request Id -- used to query information about the request or to cancel it while it's in flight. 
	 */
	UFUNCTION(BlueprintCallable, Category="Beam|APIs|Cloudsaving", meta=(AutoCreateRefTerm="UserSlot,OnSuccess,OnError,OnComplete"))
	void GetDataMetadata(const FUserSlot& UserSlot, UGetDataMetadataRequest* Request, const FOnGetDataMetadataSuccess& OnSuccess, const FOnGetDataMetadataError& OnError, const FOnGetDataMetadataComplete& OnComplete, int64& OutRequestId);

		
	/**
	 * @brief Makes an authenticated request to the Post /basic/cloudsaving/data/downloadURLFromPortal endpoint of the Cloudsaving Service.
	 *
	 * @param UserSlot The authenticated UserSlot with the user making the request. 
	 * @param Request The Request UObject. All (de)serialized data the request data creates is tied to the lifecycle of this object.
	 * @param OnSuccess What to do if the requests receives a successful response.
	 * @param OnError What to do if the request receives an error response.
	 * @param OnComplete What to after either OnSuccess or OnError have finished executing.
	 * @param OutRequestId The Request Id -- used to query information about the request or to cancel it while it's in flight. 
	 */
	UFUNCTION(BlueprintCallable, Category="Beam|APIs|Cloudsaving", meta=(AutoCreateRefTerm="UserSlot,OnSuccess,OnError,OnComplete"))
	void PostDataDownloadURLFromPortal(const FUserSlot& UserSlot, UPostDataDownloadURLFromPortalRequest* Request, const FOnPostDataDownloadURLFromPortalSuccess& OnSuccess, const FOnPostDataDownloadURLFromPortalError& OnError, const FOnPostDataDownloadURLFromPortalComplete& OnComplete, int64& OutRequestId);

		
	/**
	 * @brief Makes an authenticated request to the Put /basic/cloudsaving/data/move endpoint of the Cloudsaving Service.
	 *
	 * @param UserSlot The authenticated UserSlot with the user making the request. 
	 * @param Request The Request UObject. All (de)serialized data the request data creates is tied to the lifecycle of this object.
	 * @param OnSuccess What to do if the requests receives a successful response.
	 * @param OnError What to do if the request receives an error response.
	 * @param OnComplete What to after either OnSuccess or OnError have finished executing.
	 * @param OutRequestId The Request Id -- used to query information about the request or to cancel it while it's in flight. 
	 */
	UFUNCTION(BlueprintCallable, Category="Beam|APIs|Cloudsaving", meta=(AutoCreateRefTerm="UserSlot,OnSuccess,OnError,OnComplete"))
	void PutDataMove(const FUserSlot& UserSlot, UPutDataMoveRequest* Request, const FOnPutDataMoveSuccess& OnSuccess, const FOnPutDataMoveError& OnError, const FOnPutDataMoveComplete& OnComplete, int64& OutRequestId);

		
	/**
	 * @brief Makes an authenticated request to the Put /basic/cloudsaving/data/moveFromPortal endpoint of the Cloudsaving Service.
	 *
	 * @param UserSlot The authenticated UserSlot with the user making the request. 
	 * @param Request The Request UObject. All (de)serialized data the request data creates is tied to the lifecycle of this object.
	 * @param OnSuccess What to do if the requests receives a successful response.
	 * @param OnError What to do if the request receives an error response.
	 * @param OnComplete What to after either OnSuccess or OnError have finished executing.
	 * @param OutRequestId The Request Id -- used to query information about the request or to cancel it while it's in flight. 
	 */
	UFUNCTION(BlueprintCallable, Category="Beam|APIs|Cloudsaving", meta=(AutoCreateRefTerm="UserSlot,OnSuccess,OnError,OnComplete"))
	void PutDataMoveFromPortal(const FUserSlot& UserSlot, UPutDataMoveFromPortalRequest* Request, const FOnPutDataMoveFromPortalSuccess& OnSuccess, const FOnPutDataMoveFromPortalError& OnError, const FOnPutDataMoveFromPortalComplete& OnComplete, int64& OutRequestId);

		
	/**
	 * @brief Makes an authenticated request to the Post /basic/cloudsaving/data/uploadURLFromPortal endpoint of the Cloudsaving Service.
	 *
	 * @param UserSlot The authenticated UserSlot with the user making the request. 
	 * @param Request The Request UObject. All (de)serialized data the request data creates is tied to the lifecycle of this object.
	 * @param OnSuccess What to do if the requests receives a successful response.
	 * @param OnError What to do if the request receives an error response.
	 * @param OnComplete What to after either OnSuccess or OnError have finished executing.
	 * @param OutRequestId The Request Id -- used to query information about the request or to cancel it while it's in flight. 
	 */
	UFUNCTION(BlueprintCallable, Category="Beam|APIs|Cloudsaving", meta=(AutoCreateRefTerm="UserSlot,OnSuccess,OnError,OnComplete"))
	void PostDataUploadURLFromPortal(const FUserSlot& UserSlot, UPostDataUploadURLFromPortalRequest* Request, const FOnPostDataUploadURLFromPortalSuccess& OnSuccess, const FOnPostDataUploadURLFromPortalError& OnError, const FOnPostDataUploadURLFromPortalComplete& OnComplete, int64& OutRequestId);

		
	/**
	 * @brief Makes an authenticated request to the Put /basic/cloudsaving/data/commitManifest endpoint of the Cloudsaving Service.
	 *
	 * @param UserSlot The authenticated UserSlot with the user making the request. 
	 * @param Request The Request UObject. All (de)serialized data the request data creates is tied to the lifecycle of this object.
	 * @param OnSuccess What to do if the requests receives a successful response.
	 * @param OnError What to do if the request receives an error response.
	 * @param OnComplete What to after either OnSuccess or OnError have finished executing.
	 * @param OutRequestId The Request Id -- used to query information about the request or to cancel it while it's in flight. 
	 */
	UFUNCTION(BlueprintCallable, Category="Beam|APIs|Cloudsaving", meta=(AutoCreateRefTerm="UserSlot,OnSuccess,OnError,OnComplete"))
	void PutDataCommitManifest(const FUserSlot& UserSlot, UPutDataCommitManifestRequest* Request, const FOnPutDataCommitManifestSuccess& OnSuccess, const FOnPutDataCommitManifestError& OnError, const FOnPutDataCommitManifestComplete& OnComplete, int64& OutRequestId);

		
	/**
	 * @brief Makes an authenticated request to the Post /basic/cloudsaving/data/uploadURL endpoint of the Cloudsaving Service.
	 *
	 * @param UserSlot The authenticated UserSlot with the user making the request. 
	 * @param Request The Request UObject. All (de)serialized data the request data creates is tied to the lifecycle of this object.
	 * @param OnSuccess What to do if the requests receives a successful response.
	 * @param OnError What to do if the request receives an error response.
	 * @param OnComplete What to after either OnSuccess or OnError have finished executing.
	 * @param OutRequestId The Request Id -- used to query information about the request or to cancel it while it's in flight. 
	 */
	UFUNCTION(BlueprintCallable, Category="Beam|APIs|Cloudsaving", meta=(AutoCreateRefTerm="UserSlot,OnSuccess,OnError,OnComplete"))
	void PostDataUploadURL(const FUserSlot& UserSlot, UPostDataUploadURLRequest* Request, const FOnPostDataUploadURLSuccess& OnSuccess, const FOnPostDataUploadURLError& OnError, const FOnPostDataUploadURLComplete& OnComplete, int64& OutRequestId);
	
};
