

#pragma once

#include "CoreMinimal.h"
#include "BeamBackend.h"

#include "Mail/GetTemplateRequest.h"
#include "Mail/BasicMailGetMailRequest.h"
#include "Mail/GetDetailRequest.h"
#include "Mail/GetCategoriesRequest.h"
#include "Mail/ObjectMailPostSearchRequest.h"
#include "Mail/PutBulkRequest.h"
#include "Mail/PutAcceptManyRequest.h"
#include "Mail/ObjectMailGetMailRequest.h"
#include "Mail/ObjectMailPutMailRequest.h"
#include "Mail/PutAttachmentsRequest.h"
#include "Mail/BasicMailPutMailRequest.h"
#include "Mail/BasicMailPostBulkRequest.h"
#include "Mail/ObjectMailPostBulkRequest.h"
#include "Mail/PostMailRequest.h"

#include "BeamMailApi.generated.h"


/**
 * Subsystem containing request calls for the Mail service.
 */
UCLASS(BlueprintType)
class BEAMABLECORE_API UBeamMailApi : public UEngineSubsystem
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
	void BP_GetTemplateImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, FBeamConnectivity& ConnectivityStatus, UGetTemplateRequest* RequestData,
	                                const FOnGetTemplateSuccess& OnSuccess, const FOnGetTemplateError& OnError, const FOnGetTemplateComplete& OnComplete,
	                                int64& OutRequestId) const;
	/**
	 * @brief Overload version for binding lambdas when in C++ land. Prefer the BP version whenever possible, this is here mostly for quick experimentation purposes.	 
	 */
	void CPP_GetTemplateImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, FBeamConnectivity& ConnectivityStatus, UGetTemplateRequest* RequestData,
	                                 const FOnGetTemplateFullResponse& Handler) const;

		
	/**
	 * @brief Private implementation that all overloaded BP UFunctions call.	  
	 */
	void BP_BasicMailGetMailImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, FBeamConnectivity& ConnectivityStatus, UBasicMailGetMailRequest* RequestData,
	                                const FOnBasicMailGetMailSuccess& OnSuccess, const FOnBasicMailGetMailError& OnError, const FOnBasicMailGetMailComplete& OnComplete,
	                                int64& OutRequestId) const;
	/**
	 * @brief Overload version for binding lambdas when in C++ land. Prefer the BP version whenever possible, this is here mostly for quick experimentation purposes.	 
	 */
	void CPP_BasicMailGetMailImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, FBeamConnectivity& ConnectivityStatus, UBasicMailGetMailRequest* RequestData,
	                                 const FOnBasicMailGetMailFullResponse& Handler) const;

		
	/**
	 * @brief Private implementation that all overloaded BP UFunctions call.	  
	 */
	void BP_GetDetailImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, FBeamConnectivity& ConnectivityStatus, UGetDetailRequest* RequestData,
	                                const FOnGetDetailSuccess& OnSuccess, const FOnGetDetailError& OnError, const FOnGetDetailComplete& OnComplete,
	                                int64& OutRequestId) const;
	/**
	 * @brief Overload version for binding lambdas when in C++ land. Prefer the BP version whenever possible, this is here mostly for quick experimentation purposes.	 
	 */
	void CPP_GetDetailImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, FBeamConnectivity& ConnectivityStatus, UGetDetailRequest* RequestData,
	                                 const FOnGetDetailFullResponse& Handler) const;

		
	/**
	 * @brief Private implementation that all overloaded BP UFunctions call.	  
	 */
	void BP_GetCategoriesImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, FBeamConnectivity& ConnectivityStatus, UGetCategoriesRequest* RequestData,
	                                const FOnGetCategoriesSuccess& OnSuccess, const FOnGetCategoriesError& OnError, const FOnGetCategoriesComplete& OnComplete,
	                                int64& OutRequestId) const;
	/**
	 * @brief Overload version for binding lambdas when in C++ land. Prefer the BP version whenever possible, this is here mostly for quick experimentation purposes.	 
	 */
	void CPP_GetCategoriesImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, FBeamConnectivity& ConnectivityStatus, UGetCategoriesRequest* RequestData,
	                                 const FOnGetCategoriesFullResponse& Handler) const;

		
	/**
	 * @brief Private implementation that all overloaded BP UFunctions call.	  
	 */
	void BP_PostSearchImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, FBeamConnectivity& ConnectivityStatus, UObjectMailPostSearchRequest* RequestData,
	                                const FOnObjectMailPostSearchSuccess& OnSuccess, const FOnObjectMailPostSearchError& OnError, const FOnObjectMailPostSearchComplete& OnComplete,
	                                int64& OutRequestId) const;
	/**
	 * @brief Overload version for binding lambdas when in C++ land. Prefer the BP version whenever possible, this is here mostly for quick experimentation purposes.	 
	 */
	void CPP_PostSearchImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, FBeamConnectivity& ConnectivityStatus, UObjectMailPostSearchRequest* RequestData,
	                                 const FOnObjectMailPostSearchFullResponse& Handler) const;

		
	/**
	 * @brief Private implementation that all overloaded BP UFunctions call.	  
	 */
	void BP_PutBulkImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, FBeamConnectivity& ConnectivityStatus, UPutBulkRequest* RequestData,
	                                const FOnPutBulkSuccess& OnSuccess, const FOnPutBulkError& OnError, const FOnPutBulkComplete& OnComplete,
	                                int64& OutRequestId) const;
	/**
	 * @brief Overload version for binding lambdas when in C++ land. Prefer the BP version whenever possible, this is here mostly for quick experimentation purposes.	 
	 */
	void CPP_PutBulkImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, FBeamConnectivity& ConnectivityStatus, UPutBulkRequest* RequestData,
	                                 const FOnPutBulkFullResponse& Handler) const;

		
	/**
	 * @brief Private implementation that all overloaded BP UFunctions call.	  
	 */
	void BP_PutAcceptManyImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, FBeamConnectivity& ConnectivityStatus, UPutAcceptManyRequest* RequestData,
	                                const FOnPutAcceptManySuccess& OnSuccess, const FOnPutAcceptManyError& OnError, const FOnPutAcceptManyComplete& OnComplete,
	                                int64& OutRequestId) const;
	/**
	 * @brief Overload version for binding lambdas when in C++ land. Prefer the BP version whenever possible, this is here mostly for quick experimentation purposes.	 
	 */
	void CPP_PutAcceptManyImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, FBeamConnectivity& ConnectivityStatus, UPutAcceptManyRequest* RequestData,
	                                 const FOnPutAcceptManyFullResponse& Handler) const;

		
	/**
	 * @brief Private implementation that all overloaded BP UFunctions call.	  
	 */
	void BP_ObjectMailGetMailImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, FBeamConnectivity& ConnectivityStatus, UObjectMailGetMailRequest* RequestData,
	                                const FOnObjectMailGetMailSuccess& OnSuccess, const FOnObjectMailGetMailError& OnError, const FOnObjectMailGetMailComplete& OnComplete,
	                                int64& OutRequestId) const;
	/**
	 * @brief Overload version for binding lambdas when in C++ land. Prefer the BP version whenever possible, this is here mostly for quick experimentation purposes.	 
	 */
	void CPP_ObjectMailGetMailImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, FBeamConnectivity& ConnectivityStatus, UObjectMailGetMailRequest* RequestData,
	                                 const FOnObjectMailGetMailFullResponse& Handler) const;

		
	/**
	 * @brief Private implementation that all overloaded BP UFunctions call.	  
	 */
	void BP_ObjectMailPutMailImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, FBeamConnectivity& ConnectivityStatus, UObjectMailPutMailRequest* RequestData,
	                                const FOnObjectMailPutMailSuccess& OnSuccess, const FOnObjectMailPutMailError& OnError, const FOnObjectMailPutMailComplete& OnComplete,
	                                int64& OutRequestId) const;
	/**
	 * @brief Overload version for binding lambdas when in C++ land. Prefer the BP version whenever possible, this is here mostly for quick experimentation purposes.	 
	 */
	void CPP_ObjectMailPutMailImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, FBeamConnectivity& ConnectivityStatus, UObjectMailPutMailRequest* RequestData,
	                                 const FOnObjectMailPutMailFullResponse& Handler) const;


	
	/**
	 * @brief Private implementation for requests that require authentication that all overloaded BP UFunctions call.	  
	 */
	void BP_PutAttachmentsImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, const FBeamAuthToken& AuthToken, FBeamConnectivity& ConnectivityStatus, UPutAttachmentsRequest* RequestData,
	                  const FOnPutAttachmentsSuccess& OnSuccess, const FOnPutAttachmentsError& OnError, const FOnPutAttachmentsComplete& OnComplete, int64& OutRequestId) const;
	/**
	 * @brief Overload version for binding lambdas when in C++ land. Prefer the BP version whenever possible, this is here mostly for quick experimentation purposes.	 
	 */
	void CPP_PutAttachmentsImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, const FBeamAuthToken& AuthToken, FBeamConnectivity& ConnectivityStatus, UPutAttachmentsRequest* RequestData,
	                   const FOnPutAttachmentsFullResponse& Handler) const;
		
	/**
	 * @brief Private implementation for requests that require authentication that all overloaded BP UFunctions call.	  
	 */
	void BP_BasicMailPutMailImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, const FBeamAuthToken& AuthToken, FBeamConnectivity& ConnectivityStatus, UBasicMailPutMailRequest* RequestData,
	                  const FOnBasicMailPutMailSuccess& OnSuccess, const FOnBasicMailPutMailError& OnError, const FOnBasicMailPutMailComplete& OnComplete, int64& OutRequestId) const;
	/**
	 * @brief Overload version for binding lambdas when in C++ land. Prefer the BP version whenever possible, this is here mostly for quick experimentation purposes.	 
	 */
	void CPP_BasicMailPutMailImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, const FBeamAuthToken& AuthToken, FBeamConnectivity& ConnectivityStatus, UBasicMailPutMailRequest* RequestData,
	                   const FOnBasicMailPutMailFullResponse& Handler) const;
		
	/**
	 * @brief Private implementation for requests that require authentication that all overloaded BP UFunctions call.	  
	 */
	void BP_BasicMailPostBulkImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, const FBeamAuthToken& AuthToken, FBeamConnectivity& ConnectivityStatus, UBasicMailPostBulkRequest* RequestData,
	                  const FOnBasicMailPostBulkSuccess& OnSuccess, const FOnBasicMailPostBulkError& OnError, const FOnBasicMailPostBulkComplete& OnComplete, int64& OutRequestId) const;
	/**
	 * @brief Overload version for binding lambdas when in C++ land. Prefer the BP version whenever possible, this is here mostly for quick experimentation purposes.	 
	 */
	void CPP_BasicMailPostBulkImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, const FBeamAuthToken& AuthToken, FBeamConnectivity& ConnectivityStatus, UBasicMailPostBulkRequest* RequestData,
	                   const FOnBasicMailPostBulkFullResponse& Handler) const;
		
	/**
	 * @brief Private implementation for requests that require authentication that all overloaded BP UFunctions call.	  
	 */
	void BP_ObjectMailPostBulkImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, const FBeamAuthToken& AuthToken, FBeamConnectivity& ConnectivityStatus, UObjectMailPostBulkRequest* RequestData,
	                  const FOnObjectMailPostBulkSuccess& OnSuccess, const FOnObjectMailPostBulkError& OnError, const FOnObjectMailPostBulkComplete& OnComplete, int64& OutRequestId) const;
	/**
	 * @brief Overload version for binding lambdas when in C++ land. Prefer the BP version whenever possible, this is here mostly for quick experimentation purposes.	 
	 */
	void CPP_ObjectMailPostBulkImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, const FBeamAuthToken& AuthToken, FBeamConnectivity& ConnectivityStatus, UObjectMailPostBulkRequest* RequestData,
	                   const FOnObjectMailPostBulkFullResponse& Handler) const;
		
	/**
	 * @brief Private implementation for requests that require authentication that all overloaded BP UFunctions call.	  
	 */
	void BP_PostMailImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, const FBeamAuthToken& AuthToken, FBeamConnectivity& ConnectivityStatus, UPostMailRequest* RequestData,
	                  const FOnPostMailSuccess& OnSuccess, const FOnPostMailError& OnError, const FOnPostMailComplete& OnComplete, int64& OutRequestId) const;
	/**
	 * @brief Overload version for binding lambdas when in C++ land. Prefer the BP version whenever possible, this is here mostly for quick experimentation purposes.	 
	 */
	void CPP_PostMailImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, const FBeamAuthToken& AuthToken, FBeamConnectivity& ConnectivityStatus, UPostMailRequest* RequestData,
	                   const FOnPostMailFullResponse& Handler) const;

public:
	
	/** Used by a helper blueprint node so that you can easily chain requests in BP-land. */
	UFUNCTION(BlueprintPure, BlueprintInternalUseOnly)
	static UBeamMailApi* GetSelf() { return GEngine->GetEngineSubsystem<UBeamMailApi>(); }

	
	/**
	 * @brief Makes a request to the Get /basic/mail/template endpoint of the Mail Service.
	 *
	 * PREFER THE UFUNCTION OVERLOAD AS OPPOSED TO THIS. THIS MAINLY EXISTS TO ALLOW LAMBDA BINDING THE HANDLER.
	 * (Dynamic delegates do not allow for that so... we autogen this one to make experimenting in CPP a bit faster and for whenever you need to capture variables).
	 * 
	 * @param Request The Request UObject. All (de)serialized data the request data creates is tied to the lifecycle of this object.
	 * @param Handler A callback that defines how to handle success, error and completion. 
	 */
	void CPP_GetTemplate(UGetTemplateRequest* Request, const FOnGetTemplateFullResponse& Handler) const;

		
	/**
	 * @brief Makes a request to the Get /basic/mail/ endpoint of the Mail Service.
	 *
	 * PREFER THE UFUNCTION OVERLOAD AS OPPOSED TO THIS. THIS MAINLY EXISTS TO ALLOW LAMBDA BINDING THE HANDLER.
	 * (Dynamic delegates do not allow for that so... we autogen this one to make experimenting in CPP a bit faster and for whenever you need to capture variables).
	 * 
	 * @param Request The Request UObject. All (de)serialized data the request data creates is tied to the lifecycle of this object.
	 * @param Handler A callback that defines how to handle success, error and completion. 
	 */
	void CPP_BasicMailGetMail(UBasicMailGetMailRequest* Request, const FOnBasicMailGetMailFullResponse& Handler) const;

		
	/**
	 * @brief Makes a request to the Get /object/mail/{objectId}/detail endpoint of the Mail Service.
	 *
	 * PREFER THE UFUNCTION OVERLOAD AS OPPOSED TO THIS. THIS MAINLY EXISTS TO ALLOW LAMBDA BINDING THE HANDLER.
	 * (Dynamic delegates do not allow for that so... we autogen this one to make experimenting in CPP a bit faster and for whenever you need to capture variables).
	 * 
	 * @param Request The Request UObject. All (de)serialized data the request data creates is tied to the lifecycle of this object.
	 * @param Handler A callback that defines how to handle success, error and completion. 
	 */
	void CPP_GetDetail(UGetDetailRequest* Request, const FOnGetDetailFullResponse& Handler) const;

		
	/**
	 * @brief Makes a request to the Get /object/mail/{objectId}/categories endpoint of the Mail Service.
	 *
	 * PREFER THE UFUNCTION OVERLOAD AS OPPOSED TO THIS. THIS MAINLY EXISTS TO ALLOW LAMBDA BINDING THE HANDLER.
	 * (Dynamic delegates do not allow for that so... we autogen this one to make experimenting in CPP a bit faster and for whenever you need to capture variables).
	 * 
	 * @param Request The Request UObject. All (de)serialized data the request data creates is tied to the lifecycle of this object.
	 * @param Handler A callback that defines how to handle success, error and completion. 
	 */
	void CPP_GetCategories(UGetCategoriesRequest* Request, const FOnGetCategoriesFullResponse& Handler) const;

		
	/**
	 * @brief Makes a request to the Post /object/mail/{objectId}/search endpoint of the Mail Service.
	 *
	 * PREFER THE UFUNCTION OVERLOAD AS OPPOSED TO THIS. THIS MAINLY EXISTS TO ALLOW LAMBDA BINDING THE HANDLER.
	 * (Dynamic delegates do not allow for that so... we autogen this one to make experimenting in CPP a bit faster and for whenever you need to capture variables).
	 * 
	 * @param Request The Request UObject. All (de)serialized data the request data creates is tied to the lifecycle of this object.
	 * @param Handler A callback that defines how to handle success, error and completion. 
	 */
	void CPP_PostSearch(UObjectMailPostSearchRequest* Request, const FOnObjectMailPostSearchFullResponse& Handler) const;

		
	/**
	 * @brief Makes a request to the Put /object/mail/{objectId}/bulk endpoint of the Mail Service.
	 *
	 * PREFER THE UFUNCTION OVERLOAD AS OPPOSED TO THIS. THIS MAINLY EXISTS TO ALLOW LAMBDA BINDING THE HANDLER.
	 * (Dynamic delegates do not allow for that so... we autogen this one to make experimenting in CPP a bit faster and for whenever you need to capture variables).
	 * 
	 * @param Request The Request UObject. All (de)serialized data the request data creates is tied to the lifecycle of this object.
	 * @param Handler A callback that defines how to handle success, error and completion. 
	 */
	void CPP_PutBulk(UPutBulkRequest* Request, const FOnPutBulkFullResponse& Handler) const;

		
	/**
	 * @brief Makes a request to the Put /object/mail/{objectId}/accept/many endpoint of the Mail Service.
	 *
	 * PREFER THE UFUNCTION OVERLOAD AS OPPOSED TO THIS. THIS MAINLY EXISTS TO ALLOW LAMBDA BINDING THE HANDLER.
	 * (Dynamic delegates do not allow for that so... we autogen this one to make experimenting in CPP a bit faster and for whenever you need to capture variables).
	 * 
	 * @param Request The Request UObject. All (de)serialized data the request data creates is tied to the lifecycle of this object.
	 * @param Handler A callback that defines how to handle success, error and completion. 
	 */
	void CPP_PutAcceptMany(UPutAcceptManyRequest* Request, const FOnPutAcceptManyFullResponse& Handler) const;

		
	/**
	 * @brief Makes a request to the Get /object/mail/{objectId}/ endpoint of the Mail Service.
	 *
	 * PREFER THE UFUNCTION OVERLOAD AS OPPOSED TO THIS. THIS MAINLY EXISTS TO ALLOW LAMBDA BINDING THE HANDLER.
	 * (Dynamic delegates do not allow for that so... we autogen this one to make experimenting in CPP a bit faster and for whenever you need to capture variables).
	 * 
	 * @param Request The Request UObject. All (de)serialized data the request data creates is tied to the lifecycle of this object.
	 * @param Handler A callback that defines how to handle success, error and completion. 
	 */
	void CPP_ObjectMailGetMail(UObjectMailGetMailRequest* Request, const FOnObjectMailGetMailFullResponse& Handler) const;

		
	/**
	 * @brief Makes a request to the Put /object/mail/{objectId}/ endpoint of the Mail Service.
	 *
	 * PREFER THE UFUNCTION OVERLOAD AS OPPOSED TO THIS. THIS MAINLY EXISTS TO ALLOW LAMBDA BINDING THE HANDLER.
	 * (Dynamic delegates do not allow for that so... we autogen this one to make experimenting in CPP a bit faster and for whenever you need to capture variables).
	 * 
	 * @param Request The Request UObject. All (de)serialized data the request data creates is tied to the lifecycle of this object.
	 * @param Handler A callback that defines how to handle success, error and completion. 
	 */
	void CPP_ObjectMailPutMail(UObjectMailPutMailRequest* Request, const FOnObjectMailPutMailFullResponse& Handler) const;


	
	/**
	 * @brief Makes an authenticated request to the Put /basic/mail/attachments endpoint of the Mail Service.
	 *
	 * PREFER THE UFUNCTION OVERLOAD AS OPPOSED TO THIS. THIS MAINLY EXISTS TO ALLOW LAMBDA BINDING THE HANDLER.
	 * (Dynamic delegates do not allow for that so... we autogen this one to make experimenting in CPP a bit faster).
	 * 
	 * @param UserSlot The Authenticated User Slot that is making this request.
	 * @param Request The Request UObject. All (de)serialized data the request data creates is tied to the lifecycle of this object.
	 * @param Handler A callback that defines how to handle success, error and completion. 
	 */
	void CPP_PutAttachments(const FUserSlot& UserSlot, UPutAttachmentsRequest* Request, const FOnPutAttachmentsFullResponse& Handler) const;

		
	/**
	 * @brief Makes an authenticated request to the Put /basic/mail/ endpoint of the Mail Service.
	 *
	 * PREFER THE UFUNCTION OVERLOAD AS OPPOSED TO THIS. THIS MAINLY EXISTS TO ALLOW LAMBDA BINDING THE HANDLER.
	 * (Dynamic delegates do not allow for that so... we autogen this one to make experimenting in CPP a bit faster).
	 * 
	 * @param UserSlot The Authenticated User Slot that is making this request.
	 * @param Request The Request UObject. All (de)serialized data the request data creates is tied to the lifecycle of this object.
	 * @param Handler A callback that defines how to handle success, error and completion. 
	 */
	void CPP_BasicMailPutMail(const FUserSlot& UserSlot, UBasicMailPutMailRequest* Request, const FOnBasicMailPutMailFullResponse& Handler) const;

		
	/**
	 * @brief Makes an authenticated request to the Post /basic/mail/bulk endpoint of the Mail Service.
	 *
	 * PREFER THE UFUNCTION OVERLOAD AS OPPOSED TO THIS. THIS MAINLY EXISTS TO ALLOW LAMBDA BINDING THE HANDLER.
	 * (Dynamic delegates do not allow for that so... we autogen this one to make experimenting in CPP a bit faster).
	 * 
	 * @param UserSlot The Authenticated User Slot that is making this request.
	 * @param Request The Request UObject. All (de)serialized data the request data creates is tied to the lifecycle of this object.
	 * @param Handler A callback that defines how to handle success, error and completion. 
	 */
	void CPP_BasicMailPostBulk(const FUserSlot& UserSlot, UBasicMailPostBulkRequest* Request, const FOnBasicMailPostBulkFullResponse& Handler) const;

		
	/**
	 * @brief Makes an authenticated request to the Post /object/mail/{objectId}/bulk endpoint of the Mail Service.
	 *
	 * PREFER THE UFUNCTION OVERLOAD AS OPPOSED TO THIS. THIS MAINLY EXISTS TO ALLOW LAMBDA BINDING THE HANDLER.
	 * (Dynamic delegates do not allow for that so... we autogen this one to make experimenting in CPP a bit faster).
	 * 
	 * @param UserSlot The Authenticated User Slot that is making this request.
	 * @param Request The Request UObject. All (de)serialized data the request data creates is tied to the lifecycle of this object.
	 * @param Handler A callback that defines how to handle success, error and completion. 
	 */
	void CPP_ObjectMailPostBulk(const FUserSlot& UserSlot, UObjectMailPostBulkRequest* Request, const FOnObjectMailPostBulkFullResponse& Handler) const;

		
	/**
	 * @brief Makes an authenticated request to the Post /object/mail/{objectId}/ endpoint of the Mail Service.
	 *
	 * PREFER THE UFUNCTION OVERLOAD AS OPPOSED TO THIS. THIS MAINLY EXISTS TO ALLOW LAMBDA BINDING THE HANDLER.
	 * (Dynamic delegates do not allow for that so... we autogen this one to make experimenting in CPP a bit faster).
	 * 
	 * @param UserSlot The Authenticated User Slot that is making this request.
	 * @param Request The Request UObject. All (de)serialized data the request data creates is tied to the lifecycle of this object.
	 * @param Handler A callback that defines how to handle success, error and completion. 
	 */
	void CPP_PostMail(const FUserSlot& UserSlot, UPostMailRequest* Request, const FOnPostMailFullResponse& Handler) const;


	
	/**
	 * @brief Makes a request to the Get /basic/mail/template endpoint of the Mail Service.
	 *
	 * @param Request The Request UObject. All (de)serialized data the request data creates is tied to the lifecycle of this object.
	 * @param OnSuccess What to do if the requests receives a successful response.
	 * @param OnError What to do if the request receives an error response.
	 * @param OnComplete What to after either OnSuccess or OnError have finished executing.
	 * @param OutRequestId The Request Id -- used to query information about the request or to cancel it while it's in flight. 
	 */
	UFUNCTION(BlueprintCallable, Category="Beam|APIs|Mail", meta=(AutoCreateRefTerm="OnSuccess,OnError,OnComplete"))
	void GetTemplate(UGetTemplateRequest* Request, const FOnGetTemplateSuccess& OnSuccess, const FOnGetTemplateError& OnError, const FOnGetTemplateComplete& OnComplete,
								 int64& OutRequestId);

		
	/**
	 * @brief Makes a request to the Get /basic/mail/ endpoint of the Mail Service.
	 *
	 * @param Request The Request UObject. All (de)serialized data the request data creates is tied to the lifecycle of this object.
	 * @param OnSuccess What to do if the requests receives a successful response.
	 * @param OnError What to do if the request receives an error response.
	 * @param OnComplete What to after either OnSuccess or OnError have finished executing.
	 * @param OutRequestId The Request Id -- used to query information about the request or to cancel it while it's in flight. 
	 */
	UFUNCTION(BlueprintCallable, Category="Beam|APIs|Mail", meta=(AutoCreateRefTerm="OnSuccess,OnError,OnComplete"))
	void BasicMailGetMail(UBasicMailGetMailRequest* Request, const FOnBasicMailGetMailSuccess& OnSuccess, const FOnBasicMailGetMailError& OnError, const FOnBasicMailGetMailComplete& OnComplete,
								 int64& OutRequestId);

		
	/**
	 * @brief Makes a request to the Get /object/mail/{objectId}/detail endpoint of the Mail Service.
	 *
	 * @param Request The Request UObject. All (de)serialized data the request data creates is tied to the lifecycle of this object.
	 * @param OnSuccess What to do if the requests receives a successful response.
	 * @param OnError What to do if the request receives an error response.
	 * @param OnComplete What to after either OnSuccess or OnError have finished executing.
	 * @param OutRequestId The Request Id -- used to query information about the request or to cancel it while it's in flight. 
	 */
	UFUNCTION(BlueprintCallable, Category="Beam|APIs|Mail", meta=(AutoCreateRefTerm="OnSuccess,OnError,OnComplete"))
	void GetDetail(UGetDetailRequest* Request, const FOnGetDetailSuccess& OnSuccess, const FOnGetDetailError& OnError, const FOnGetDetailComplete& OnComplete,
								 int64& OutRequestId);

		
	/**
	 * @brief Makes a request to the Get /object/mail/{objectId}/categories endpoint of the Mail Service.
	 *
	 * @param Request The Request UObject. All (de)serialized data the request data creates is tied to the lifecycle of this object.
	 * @param OnSuccess What to do if the requests receives a successful response.
	 * @param OnError What to do if the request receives an error response.
	 * @param OnComplete What to after either OnSuccess or OnError have finished executing.
	 * @param OutRequestId The Request Id -- used to query information about the request or to cancel it while it's in flight. 
	 */
	UFUNCTION(BlueprintCallable, Category="Beam|APIs|Mail", meta=(AutoCreateRefTerm="OnSuccess,OnError,OnComplete"))
	void GetCategories(UGetCategoriesRequest* Request, const FOnGetCategoriesSuccess& OnSuccess, const FOnGetCategoriesError& OnError, const FOnGetCategoriesComplete& OnComplete,
								 int64& OutRequestId);

		
	/**
	 * @brief Makes a request to the Post /object/mail/{objectId}/search endpoint of the Mail Service.
	 *
	 * @param Request The Request UObject. All (de)serialized data the request data creates is tied to the lifecycle of this object.
	 * @param OnSuccess What to do if the requests receives a successful response.
	 * @param OnError What to do if the request receives an error response.
	 * @param OnComplete What to after either OnSuccess or OnError have finished executing.
	 * @param OutRequestId The Request Id -- used to query information about the request or to cancel it while it's in flight. 
	 */
	UFUNCTION(BlueprintCallable, Category="Beam|APIs|Mail", meta=(AutoCreateRefTerm="OnSuccess,OnError,OnComplete"))
	void PostSearch(UObjectMailPostSearchRequest* Request, const FOnObjectMailPostSearchSuccess& OnSuccess, const FOnObjectMailPostSearchError& OnError, const FOnObjectMailPostSearchComplete& OnComplete,
								 int64& OutRequestId);

		
	/**
	 * @brief Makes a request to the Put /object/mail/{objectId}/bulk endpoint of the Mail Service.
	 *
	 * @param Request The Request UObject. All (de)serialized data the request data creates is tied to the lifecycle of this object.
	 * @param OnSuccess What to do if the requests receives a successful response.
	 * @param OnError What to do if the request receives an error response.
	 * @param OnComplete What to after either OnSuccess or OnError have finished executing.
	 * @param OutRequestId The Request Id -- used to query information about the request or to cancel it while it's in flight. 
	 */
	UFUNCTION(BlueprintCallable, Category="Beam|APIs|Mail", meta=(AutoCreateRefTerm="OnSuccess,OnError,OnComplete"))
	void PutBulk(UPutBulkRequest* Request, const FOnPutBulkSuccess& OnSuccess, const FOnPutBulkError& OnError, const FOnPutBulkComplete& OnComplete,
								 int64& OutRequestId);

		
	/**
	 * @brief Makes a request to the Put /object/mail/{objectId}/accept/many endpoint of the Mail Service.
	 *
	 * @param Request The Request UObject. All (de)serialized data the request data creates is tied to the lifecycle of this object.
	 * @param OnSuccess What to do if the requests receives a successful response.
	 * @param OnError What to do if the request receives an error response.
	 * @param OnComplete What to after either OnSuccess or OnError have finished executing.
	 * @param OutRequestId The Request Id -- used to query information about the request or to cancel it while it's in flight. 
	 */
	UFUNCTION(BlueprintCallable, Category="Beam|APIs|Mail", meta=(AutoCreateRefTerm="OnSuccess,OnError,OnComplete"))
	void PutAcceptMany(UPutAcceptManyRequest* Request, const FOnPutAcceptManySuccess& OnSuccess, const FOnPutAcceptManyError& OnError, const FOnPutAcceptManyComplete& OnComplete,
								 int64& OutRequestId);

		
	/**
	 * @brief Makes a request to the Get /object/mail/{objectId}/ endpoint of the Mail Service.
	 *
	 * @param Request The Request UObject. All (de)serialized data the request data creates is tied to the lifecycle of this object.
	 * @param OnSuccess What to do if the requests receives a successful response.
	 * @param OnError What to do if the request receives an error response.
	 * @param OnComplete What to after either OnSuccess or OnError have finished executing.
	 * @param OutRequestId The Request Id -- used to query information about the request or to cancel it while it's in flight. 
	 */
	UFUNCTION(BlueprintCallable, Category="Beam|APIs|Mail", meta=(AutoCreateRefTerm="OnSuccess,OnError,OnComplete"))
	void ObjectMailGetMail(UObjectMailGetMailRequest* Request, const FOnObjectMailGetMailSuccess& OnSuccess, const FOnObjectMailGetMailError& OnError, const FOnObjectMailGetMailComplete& OnComplete,
								 int64& OutRequestId);

		
	/**
	 * @brief Makes a request to the Put /object/mail/{objectId}/ endpoint of the Mail Service.
	 *
	 * @param Request The Request UObject. All (de)serialized data the request data creates is tied to the lifecycle of this object.
	 * @param OnSuccess What to do if the requests receives a successful response.
	 * @param OnError What to do if the request receives an error response.
	 * @param OnComplete What to after either OnSuccess or OnError have finished executing.
	 * @param OutRequestId The Request Id -- used to query information about the request or to cancel it while it's in flight. 
	 */
	UFUNCTION(BlueprintCallable, Category="Beam|APIs|Mail", meta=(AutoCreateRefTerm="OnSuccess,OnError,OnComplete"))
	void ObjectMailPutMail(UObjectMailPutMailRequest* Request, const FOnObjectMailPutMailSuccess& OnSuccess, const FOnObjectMailPutMailError& OnError, const FOnObjectMailPutMailComplete& OnComplete,
								 int64& OutRequestId);


	
	/**
	 * @brief Makes an authenticated request to the Put /basic/mail/attachments endpoint of the Mail Service.
	 *
	 * @param UserSlot The authenticated UserSlot with the user making the request. 
	 * @param Request The Request UObject. All (de)serialized data the request data creates is tied to the lifecycle of this object.
	 * @param OnSuccess What to do if the requests receives a successful response.
	 * @param OnError What to do if the request receives an error response.
	 * @param OnComplete What to after either OnSuccess or OnError have finished executing.
	 * @param OutRequestId The Request Id -- used to query information about the request or to cancel it while it's in flight. 
	 */
	UFUNCTION(BlueprintCallable, Category="Beam|APIs|Mail", meta=(AutoCreateRefTerm="UserSlot,OnSuccess,OnError,OnComplete"))
	void PutAttachments(const FUserSlot& UserSlot, UPutAttachmentsRequest* Request, const FOnPutAttachmentsSuccess& OnSuccess, const FOnPutAttachmentsError& OnError, const FOnPutAttachmentsComplete& OnComplete, int64& OutRequestId);

		
	/**
	 * @brief Makes an authenticated request to the Put /basic/mail/ endpoint of the Mail Service.
	 *
	 * @param UserSlot The authenticated UserSlot with the user making the request. 
	 * @param Request The Request UObject. All (de)serialized data the request data creates is tied to the lifecycle of this object.
	 * @param OnSuccess What to do if the requests receives a successful response.
	 * @param OnError What to do if the request receives an error response.
	 * @param OnComplete What to after either OnSuccess or OnError have finished executing.
	 * @param OutRequestId The Request Id -- used to query information about the request or to cancel it while it's in flight. 
	 */
	UFUNCTION(BlueprintCallable, Category="Beam|APIs|Mail", meta=(AutoCreateRefTerm="UserSlot,OnSuccess,OnError,OnComplete"))
	void BasicMailPutMail(const FUserSlot& UserSlot, UBasicMailPutMailRequest* Request, const FOnBasicMailPutMailSuccess& OnSuccess, const FOnBasicMailPutMailError& OnError, const FOnBasicMailPutMailComplete& OnComplete, int64& OutRequestId);

		
	/**
	 * @brief Makes an authenticated request to the Post /basic/mail/bulk endpoint of the Mail Service.
	 *
	 * @param UserSlot The authenticated UserSlot with the user making the request. 
	 * @param Request The Request UObject. All (de)serialized data the request data creates is tied to the lifecycle of this object.
	 * @param OnSuccess What to do if the requests receives a successful response.
	 * @param OnError What to do if the request receives an error response.
	 * @param OnComplete What to after either OnSuccess or OnError have finished executing.
	 * @param OutRequestId The Request Id -- used to query information about the request or to cancel it while it's in flight. 
	 */
	UFUNCTION(BlueprintCallable, Category="Beam|APIs|Mail", meta=(AutoCreateRefTerm="UserSlot,OnSuccess,OnError,OnComplete"))
	void BasicMailPostBulk(const FUserSlot& UserSlot, UBasicMailPostBulkRequest* Request, const FOnBasicMailPostBulkSuccess& OnSuccess, const FOnBasicMailPostBulkError& OnError, const FOnBasicMailPostBulkComplete& OnComplete, int64& OutRequestId);

		
	/**
	 * @brief Makes an authenticated request to the Post /object/mail/{objectId}/bulk endpoint of the Mail Service.
	 *
	 * @param UserSlot The authenticated UserSlot with the user making the request. 
	 * @param Request The Request UObject. All (de)serialized data the request data creates is tied to the lifecycle of this object.
	 * @param OnSuccess What to do if the requests receives a successful response.
	 * @param OnError What to do if the request receives an error response.
	 * @param OnComplete What to after either OnSuccess or OnError have finished executing.
	 * @param OutRequestId The Request Id -- used to query information about the request or to cancel it while it's in flight. 
	 */
	UFUNCTION(BlueprintCallable, Category="Beam|APIs|Mail", meta=(AutoCreateRefTerm="UserSlot,OnSuccess,OnError,OnComplete"))
	void ObjectMailPostBulk(const FUserSlot& UserSlot, UObjectMailPostBulkRequest* Request, const FOnObjectMailPostBulkSuccess& OnSuccess, const FOnObjectMailPostBulkError& OnError, const FOnObjectMailPostBulkComplete& OnComplete, int64& OutRequestId);

		
	/**
	 * @brief Makes an authenticated request to the Post /object/mail/{objectId}/ endpoint of the Mail Service.
	 *
	 * @param UserSlot The authenticated UserSlot with the user making the request. 
	 * @param Request The Request UObject. All (de)serialized data the request data creates is tied to the lifecycle of this object.
	 * @param OnSuccess What to do if the requests receives a successful response.
	 * @param OnError What to do if the request receives an error response.
	 * @param OnComplete What to after either OnSuccess or OnError have finished executing.
	 * @param OutRequestId The Request Id -- used to query information about the request or to cancel it while it's in flight. 
	 */
	UFUNCTION(BlueprintCallable, Category="Beam|APIs|Mail", meta=(AutoCreateRefTerm="UserSlot,OnSuccess,OnError,OnComplete"))
	void PostMail(const FUserSlot& UserSlot, UPostMailRequest* Request, const FOnPostMailSuccess& OnSuccess, const FOnPostMailError& OnError, const FOnPostMailComplete& OnComplete, int64& OutRequestId);
	
};
