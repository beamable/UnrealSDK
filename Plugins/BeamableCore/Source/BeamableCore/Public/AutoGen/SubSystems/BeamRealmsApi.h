

#pragma once

#include "CoreMinimal.h"
#include "BeamBackend/BeamBackend.h"

#include "Realms/GetCustomerAliasAvailableRequest.h"
#include "Realms/GetProjectRequest.h"
#include "Realms/PostCustomerRequest.h"
#include "Realms/GetIsCustomerRequest.h"
#include "Realms/GetCustomersRequest.h"
#include "Realms/PostProjectBeamableRequest.h"
#include "Realms/PostProjectRequest.h"
#include "Realms/PutProjectRequest.h"
#include "Realms/DeleteProjectRequest.h"
#include "Realms/GetGamesRequest.h"
#include "Realms/GetConfigRequest.h"
#include "Realms/PutConfigRequest.h"
#include "Realms/PutProjectRenameRequest.h"
#include "Realms/GetPlansRequest.h"
#include "Realms/PostPlansRequest.h"
#include "Realms/GetCustomerRequest.h"
#include "Realms/GetLaunchMessageRequest.h"
#include "Realms/PostLaunchMessageRequest.h"
#include "Realms/DeleteLaunchMessageRequest.h"
#include "Realms/GetAdminCustomerRequest.h"
#include "Realms/GetGameRequest.h"
#include "Realms/BasicRealmsPostGameRequest.h"
#include "Realms/PutGameRequest.h"
#include "Realms/GetProjectPromoteRequest.h"
#include "Realms/PostProjectPromoteRequest.h"
#include "Realms/GetPromotionRequest.h"
#include "Realms/PostPromotionRequest.h"

#include "BeamRealmsApi.generated.h"


/**
 * Subsystem containing request calls for the Realms service.
 */
UCLASS(NotBlueprintType)
class BEAMABLECORE_API UBeamRealmsApi : public UEngineSubsystem
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
	void BP_GetCustomerAliasAvailableImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, FBeamConnectivity& ConnectivityStatus, UGetCustomerAliasAvailableRequest* RequestData,
	                                const FOnGetCustomerAliasAvailableSuccess& OnSuccess, const FOnGetCustomerAliasAvailableError& OnError, const FOnGetCustomerAliasAvailableComplete& OnComplete,
	                                int64& OutRequestId) const;
	/**
	 * @brief Overload version for binding lambdas when in C++ land. Prefer the BP version whenever possible, this is here mostly for quick experimentation purposes.	 
	 */
	void CPP_GetCustomerAliasAvailableImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, FBeamConnectivity& ConnectivityStatus, UGetCustomerAliasAvailableRequest* RequestData,
	                                 const FOnGetCustomerAliasAvailableFullResponse& Handler) const;

		
	/**
	 * @brief Private implementation that all overloaded BP UFunctions call.	  
	 */
	void BP_GetProjectImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, FBeamConnectivity& ConnectivityStatus, UGetProjectRequest* RequestData,
	                                const FOnGetProjectSuccess& OnSuccess, const FOnGetProjectError& OnError, const FOnGetProjectComplete& OnComplete,
	                                int64& OutRequestId) const;
	/**
	 * @brief Overload version for binding lambdas when in C++ land. Prefer the BP version whenever possible, this is here mostly for quick experimentation purposes.	 
	 */
	void CPP_GetProjectImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, FBeamConnectivity& ConnectivityStatus, UGetProjectRequest* RequestData,
	                                 const FOnGetProjectFullResponse& Handler) const;

		
	/**
	 * @brief Private implementation that all overloaded BP UFunctions call.	  
	 */
	void BP_PostCustomerImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, FBeamConnectivity& ConnectivityStatus, UPostCustomerRequest* RequestData,
	                                const FOnPostCustomerSuccess& OnSuccess, const FOnPostCustomerError& OnError, const FOnPostCustomerComplete& OnComplete,
	                                int64& OutRequestId) const;
	/**
	 * @brief Overload version for binding lambdas when in C++ land. Prefer the BP version whenever possible, this is here mostly for quick experimentation purposes.	 
	 */
	void CPP_PostCustomerImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, FBeamConnectivity& ConnectivityStatus, UPostCustomerRequest* RequestData,
	                                 const FOnPostCustomerFullResponse& Handler) const;

		
	/**
	 * @brief Private implementation that all overloaded BP UFunctions call.	  
	 */
	void BP_GetIsCustomerImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, FBeamConnectivity& ConnectivityStatus, UGetIsCustomerRequest* RequestData,
	                                const FOnGetIsCustomerSuccess& OnSuccess, const FOnGetIsCustomerError& OnError, const FOnGetIsCustomerComplete& OnComplete,
	                                int64& OutRequestId) const;
	/**
	 * @brief Overload version for binding lambdas when in C++ land. Prefer the BP version whenever possible, this is here mostly for quick experimentation purposes.	 
	 */
	void CPP_GetIsCustomerImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, FBeamConnectivity& ConnectivityStatus, UGetIsCustomerRequest* RequestData,
	                                 const FOnGetIsCustomerFullResponse& Handler) const;

		
	/**
	 * @brief Private implementation that all overloaded BP UFunctions call.	  
	 */
	void BP_GetCustomersImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, FBeamConnectivity& ConnectivityStatus, UGetCustomersRequest* RequestData,
	                                const FOnGetCustomersSuccess& OnSuccess, const FOnGetCustomersError& OnError, const FOnGetCustomersComplete& OnComplete,
	                                int64& OutRequestId) const;
	/**
	 * @brief Overload version for binding lambdas when in C++ land. Prefer the BP version whenever possible, this is here mostly for quick experimentation purposes.	 
	 */
	void CPP_GetCustomersImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, FBeamConnectivity& ConnectivityStatus, UGetCustomersRequest* RequestData,
	                                 const FOnGetCustomersFullResponse& Handler) const;


	
	/**
	 * @brief Private implementation for requests that require authentication that all overloaded BP UFunctions call.	  
	 */
	void BP_PostProjectBeamableImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, const FBeamAuthToken& AuthToken, FBeamConnectivity& ConnectivityStatus, UPostProjectBeamableRequest* RequestData,
	                  const FOnPostProjectBeamableSuccess& OnSuccess, const FOnPostProjectBeamableError& OnError, const FOnPostProjectBeamableComplete& OnComplete, int64& OutRequestId) const;
	/**
	 * @brief Overload version for binding lambdas when in C++ land. Prefer the BP version whenever possible, this is here mostly for quick experimentation purposes.	 
	 */
	void CPP_PostProjectBeamableImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, const FBeamAuthToken& AuthToken, FBeamConnectivity& ConnectivityStatus, UPostProjectBeamableRequest* RequestData,
	                   const FOnPostProjectBeamableFullResponse& Handler) const;
		
	/**
	 * @brief Private implementation for requests that require authentication that all overloaded BP UFunctions call.	  
	 */
	void BP_PostProjectImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, const FBeamAuthToken& AuthToken, FBeamConnectivity& ConnectivityStatus, UPostProjectRequest* RequestData,
	                  const FOnPostProjectSuccess& OnSuccess, const FOnPostProjectError& OnError, const FOnPostProjectComplete& OnComplete, int64& OutRequestId) const;
	/**
	 * @brief Overload version for binding lambdas when in C++ land. Prefer the BP version whenever possible, this is here mostly for quick experimentation purposes.	 
	 */
	void CPP_PostProjectImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, const FBeamAuthToken& AuthToken, FBeamConnectivity& ConnectivityStatus, UPostProjectRequest* RequestData,
	                   const FOnPostProjectFullResponse& Handler) const;
		
	/**
	 * @brief Private implementation for requests that require authentication that all overloaded BP UFunctions call.	  
	 */
	void BP_PutProjectImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, const FBeamAuthToken& AuthToken, FBeamConnectivity& ConnectivityStatus, UPutProjectRequest* RequestData,
	                  const FOnPutProjectSuccess& OnSuccess, const FOnPutProjectError& OnError, const FOnPutProjectComplete& OnComplete, int64& OutRequestId) const;
	/**
	 * @brief Overload version for binding lambdas when in C++ land. Prefer the BP version whenever possible, this is here mostly for quick experimentation purposes.	 
	 */
	void CPP_PutProjectImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, const FBeamAuthToken& AuthToken, FBeamConnectivity& ConnectivityStatus, UPutProjectRequest* RequestData,
	                   const FOnPutProjectFullResponse& Handler) const;
		
	/**
	 * @brief Private implementation for requests that require authentication that all overloaded BP UFunctions call.	  
	 */
	void BP_DeleteProjectImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, const FBeamAuthToken& AuthToken, FBeamConnectivity& ConnectivityStatus, UDeleteProjectRequest* RequestData,
	                  const FOnDeleteProjectSuccess& OnSuccess, const FOnDeleteProjectError& OnError, const FOnDeleteProjectComplete& OnComplete, int64& OutRequestId) const;
	/**
	 * @brief Overload version for binding lambdas when in C++ land. Prefer the BP version whenever possible, this is here mostly for quick experimentation purposes.	 
	 */
	void CPP_DeleteProjectImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, const FBeamAuthToken& AuthToken, FBeamConnectivity& ConnectivityStatus, UDeleteProjectRequest* RequestData,
	                   const FOnDeleteProjectFullResponse& Handler) const;
		
	/**
	 * @brief Private implementation for requests that require authentication that all overloaded BP UFunctions call.	  
	 */
	void BP_GetGamesImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, const FBeamAuthToken& AuthToken, FBeamConnectivity& ConnectivityStatus, UGetGamesRequest* RequestData,
	                  const FOnGetGamesSuccess& OnSuccess, const FOnGetGamesError& OnError, const FOnGetGamesComplete& OnComplete, int64& OutRequestId) const;
	/**
	 * @brief Overload version for binding lambdas when in C++ land. Prefer the BP version whenever possible, this is here mostly for quick experimentation purposes.	 
	 */
	void CPP_GetGamesImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, const FBeamAuthToken& AuthToken, FBeamConnectivity& ConnectivityStatus, UGetGamesRequest* RequestData,
	                   const FOnGetGamesFullResponse& Handler) const;
		
	/**
	 * @brief Private implementation for requests that require authentication that all overloaded BP UFunctions call.	  
	 */
	void BP_GetConfigImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, const FBeamAuthToken& AuthToken, FBeamConnectivity& ConnectivityStatus, UGetConfigRequest* RequestData,
	                  const FOnGetConfigSuccess& OnSuccess, const FOnGetConfigError& OnError, const FOnGetConfigComplete& OnComplete, int64& OutRequestId) const;
	/**
	 * @brief Overload version for binding lambdas when in C++ land. Prefer the BP version whenever possible, this is here mostly for quick experimentation purposes.	 
	 */
	void CPP_GetConfigImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, const FBeamAuthToken& AuthToken, FBeamConnectivity& ConnectivityStatus, UGetConfigRequest* RequestData,
	                   const FOnGetConfigFullResponse& Handler) const;
		
	/**
	 * @brief Private implementation for requests that require authentication that all overloaded BP UFunctions call.	  
	 */
	void BP_PutConfigImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, const FBeamAuthToken& AuthToken, FBeamConnectivity& ConnectivityStatus, UPutConfigRequest* RequestData,
	                  const FOnPutConfigSuccess& OnSuccess, const FOnPutConfigError& OnError, const FOnPutConfigComplete& OnComplete, int64& OutRequestId) const;
	/**
	 * @brief Overload version for binding lambdas when in C++ land. Prefer the BP version whenever possible, this is here mostly for quick experimentation purposes.	 
	 */
	void CPP_PutConfigImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, const FBeamAuthToken& AuthToken, FBeamConnectivity& ConnectivityStatus, UPutConfigRequest* RequestData,
	                   const FOnPutConfigFullResponse& Handler) const;
		
	/**
	 * @brief Private implementation for requests that require authentication that all overloaded BP UFunctions call.	  
	 */
	void BP_PutProjectRenameImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, const FBeamAuthToken& AuthToken, FBeamConnectivity& ConnectivityStatus, UPutProjectRenameRequest* RequestData,
	                  const FOnPutProjectRenameSuccess& OnSuccess, const FOnPutProjectRenameError& OnError, const FOnPutProjectRenameComplete& OnComplete, int64& OutRequestId) const;
	/**
	 * @brief Overload version for binding lambdas when in C++ land. Prefer the BP version whenever possible, this is here mostly for quick experimentation purposes.	 
	 */
	void CPP_PutProjectRenameImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, const FBeamAuthToken& AuthToken, FBeamConnectivity& ConnectivityStatus, UPutProjectRenameRequest* RequestData,
	                   const FOnPutProjectRenameFullResponse& Handler) const;
		
	/**
	 * @brief Private implementation for requests that require authentication that all overloaded BP UFunctions call.	  
	 */
	void BP_GetPlansImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, const FBeamAuthToken& AuthToken, FBeamConnectivity& ConnectivityStatus, UGetPlansRequest* RequestData,
	                  const FOnGetPlansSuccess& OnSuccess, const FOnGetPlansError& OnError, const FOnGetPlansComplete& OnComplete, int64& OutRequestId) const;
	/**
	 * @brief Overload version for binding lambdas when in C++ land. Prefer the BP version whenever possible, this is here mostly for quick experimentation purposes.	 
	 */
	void CPP_GetPlansImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, const FBeamAuthToken& AuthToken, FBeamConnectivity& ConnectivityStatus, UGetPlansRequest* RequestData,
	                   const FOnGetPlansFullResponse& Handler) const;
		
	/**
	 * @brief Private implementation for requests that require authentication that all overloaded BP UFunctions call.	  
	 */
	void BP_PostPlansImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, const FBeamAuthToken& AuthToken, FBeamConnectivity& ConnectivityStatus, UPostPlansRequest* RequestData,
	                  const FOnPostPlansSuccess& OnSuccess, const FOnPostPlansError& OnError, const FOnPostPlansComplete& OnComplete, int64& OutRequestId) const;
	/**
	 * @brief Overload version for binding lambdas when in C++ land. Prefer the BP version whenever possible, this is here mostly for quick experimentation purposes.	 
	 */
	void CPP_PostPlansImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, const FBeamAuthToken& AuthToken, FBeamConnectivity& ConnectivityStatus, UPostPlansRequest* RequestData,
	                   const FOnPostPlansFullResponse& Handler) const;
		
	/**
	 * @brief Private implementation for requests that require authentication that all overloaded BP UFunctions call.	  
	 */
	void BP_GetCustomerImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, const FBeamAuthToken& AuthToken, FBeamConnectivity& ConnectivityStatus, UGetCustomerRequest* RequestData,
	                  const FOnGetCustomerSuccess& OnSuccess, const FOnGetCustomerError& OnError, const FOnGetCustomerComplete& OnComplete, int64& OutRequestId) const;
	/**
	 * @brief Overload version for binding lambdas when in C++ land. Prefer the BP version whenever possible, this is here mostly for quick experimentation purposes.	 
	 */
	void CPP_GetCustomerImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, const FBeamAuthToken& AuthToken, FBeamConnectivity& ConnectivityStatus, UGetCustomerRequest* RequestData,
	                   const FOnGetCustomerFullResponse& Handler) const;
		
	/**
	 * @brief Private implementation for requests that require authentication that all overloaded BP UFunctions call.	  
	 */
	void BP_GetLaunchMessageImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, const FBeamAuthToken& AuthToken, FBeamConnectivity& ConnectivityStatus, UGetLaunchMessageRequest* RequestData,
	                  const FOnGetLaunchMessageSuccess& OnSuccess, const FOnGetLaunchMessageError& OnError, const FOnGetLaunchMessageComplete& OnComplete, int64& OutRequestId) const;
	/**
	 * @brief Overload version for binding lambdas when in C++ land. Prefer the BP version whenever possible, this is here mostly for quick experimentation purposes.	 
	 */
	void CPP_GetLaunchMessageImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, const FBeamAuthToken& AuthToken, FBeamConnectivity& ConnectivityStatus, UGetLaunchMessageRequest* RequestData,
	                   const FOnGetLaunchMessageFullResponse& Handler) const;
		
	/**
	 * @brief Private implementation for requests that require authentication that all overloaded BP UFunctions call.	  
	 */
	void BP_PostLaunchMessageImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, const FBeamAuthToken& AuthToken, FBeamConnectivity& ConnectivityStatus, UPostLaunchMessageRequest* RequestData,
	                  const FOnPostLaunchMessageSuccess& OnSuccess, const FOnPostLaunchMessageError& OnError, const FOnPostLaunchMessageComplete& OnComplete, int64& OutRequestId) const;
	/**
	 * @brief Overload version for binding lambdas when in C++ land. Prefer the BP version whenever possible, this is here mostly for quick experimentation purposes.	 
	 */
	void CPP_PostLaunchMessageImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, const FBeamAuthToken& AuthToken, FBeamConnectivity& ConnectivityStatus, UPostLaunchMessageRequest* RequestData,
	                   const FOnPostLaunchMessageFullResponse& Handler) const;
		
	/**
	 * @brief Private implementation for requests that require authentication that all overloaded BP UFunctions call.	  
	 */
	void BP_DeleteLaunchMessageImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, const FBeamAuthToken& AuthToken, FBeamConnectivity& ConnectivityStatus, UDeleteLaunchMessageRequest* RequestData,
	                  const FOnDeleteLaunchMessageSuccess& OnSuccess, const FOnDeleteLaunchMessageError& OnError, const FOnDeleteLaunchMessageComplete& OnComplete, int64& OutRequestId) const;
	/**
	 * @brief Overload version for binding lambdas when in C++ land. Prefer the BP version whenever possible, this is here mostly for quick experimentation purposes.	 
	 */
	void CPP_DeleteLaunchMessageImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, const FBeamAuthToken& AuthToken, FBeamConnectivity& ConnectivityStatus, UDeleteLaunchMessageRequest* RequestData,
	                   const FOnDeleteLaunchMessageFullResponse& Handler) const;
		
	/**
	 * @brief Private implementation for requests that require authentication that all overloaded BP UFunctions call.	  
	 */
	void BP_GetAdminCustomerImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, const FBeamAuthToken& AuthToken, FBeamConnectivity& ConnectivityStatus, UGetAdminCustomerRequest* RequestData,
	                  const FOnGetAdminCustomerSuccess& OnSuccess, const FOnGetAdminCustomerError& OnError, const FOnGetAdminCustomerComplete& OnComplete, int64& OutRequestId) const;
	/**
	 * @brief Overload version for binding lambdas when in C++ land. Prefer the BP version whenever possible, this is here mostly for quick experimentation purposes.	 
	 */
	void CPP_GetAdminCustomerImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, const FBeamAuthToken& AuthToken, FBeamConnectivity& ConnectivityStatus, UGetAdminCustomerRequest* RequestData,
	                   const FOnGetAdminCustomerFullResponse& Handler) const;
		
	/**
	 * @brief Private implementation for requests that require authentication that all overloaded BP UFunctions call.	  
	 */
	void BP_GetGameImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, const FBeamAuthToken& AuthToken, FBeamConnectivity& ConnectivityStatus, UGetGameRequest* RequestData,
	                  const FOnGetGameSuccess& OnSuccess, const FOnGetGameError& OnError, const FOnGetGameComplete& OnComplete, int64& OutRequestId) const;
	/**
	 * @brief Overload version for binding lambdas when in C++ land. Prefer the BP version whenever possible, this is here mostly for quick experimentation purposes.	 
	 */
	void CPP_GetGameImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, const FBeamAuthToken& AuthToken, FBeamConnectivity& ConnectivityStatus, UGetGameRequest* RequestData,
	                   const FOnGetGameFullResponse& Handler) const;
		
	/**
	 * @brief Private implementation for requests that require authentication that all overloaded BP UFunctions call.	  
	 */
	void BP_PostGameImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, const FBeamAuthToken& AuthToken, FBeamConnectivity& ConnectivityStatus, UBasicRealmsPostGameRequest* RequestData,
	                  const FOnBasicRealmsPostGameSuccess& OnSuccess, const FOnBasicRealmsPostGameError& OnError, const FOnBasicRealmsPostGameComplete& OnComplete, int64& OutRequestId) const;
	/**
	 * @brief Overload version for binding lambdas when in C++ land. Prefer the BP version whenever possible, this is here mostly for quick experimentation purposes.	 
	 */
	void CPP_PostGameImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, const FBeamAuthToken& AuthToken, FBeamConnectivity& ConnectivityStatus, UBasicRealmsPostGameRequest* RequestData,
	                   const FOnBasicRealmsPostGameFullResponse& Handler) const;
		
	/**
	 * @brief Private implementation for requests that require authentication that all overloaded BP UFunctions call.	  
	 */
	void BP_PutGameImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, const FBeamAuthToken& AuthToken, FBeamConnectivity& ConnectivityStatus, UPutGameRequest* RequestData,
	                  const FOnPutGameSuccess& OnSuccess, const FOnPutGameError& OnError, const FOnPutGameComplete& OnComplete, int64& OutRequestId) const;
	/**
	 * @brief Overload version for binding lambdas when in C++ land. Prefer the BP version whenever possible, this is here mostly for quick experimentation purposes.	 
	 */
	void CPP_PutGameImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, const FBeamAuthToken& AuthToken, FBeamConnectivity& ConnectivityStatus, UPutGameRequest* RequestData,
	                   const FOnPutGameFullResponse& Handler) const;
		
	/**
	 * @brief Private implementation for requests that require authentication that all overloaded BP UFunctions call.	  
	 */
	void BP_GetProjectPromoteImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, const FBeamAuthToken& AuthToken, FBeamConnectivity& ConnectivityStatus, UGetProjectPromoteRequest* RequestData,
	                  const FOnGetProjectPromoteSuccess& OnSuccess, const FOnGetProjectPromoteError& OnError, const FOnGetProjectPromoteComplete& OnComplete, int64& OutRequestId) const;
	/**
	 * @brief Overload version for binding lambdas when in C++ land. Prefer the BP version whenever possible, this is here mostly for quick experimentation purposes.	 
	 */
	void CPP_GetProjectPromoteImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, const FBeamAuthToken& AuthToken, FBeamConnectivity& ConnectivityStatus, UGetProjectPromoteRequest* RequestData,
	                   const FOnGetProjectPromoteFullResponse& Handler) const;
		
	/**
	 * @brief Private implementation for requests that require authentication that all overloaded BP UFunctions call.	  
	 */
	void BP_PostProjectPromoteImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, const FBeamAuthToken& AuthToken, FBeamConnectivity& ConnectivityStatus, UPostProjectPromoteRequest* RequestData,
	                  const FOnPostProjectPromoteSuccess& OnSuccess, const FOnPostProjectPromoteError& OnError, const FOnPostProjectPromoteComplete& OnComplete, int64& OutRequestId) const;
	/**
	 * @brief Overload version for binding lambdas when in C++ land. Prefer the BP version whenever possible, this is here mostly for quick experimentation purposes.	 
	 */
	void CPP_PostProjectPromoteImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, const FBeamAuthToken& AuthToken, FBeamConnectivity& ConnectivityStatus, UPostProjectPromoteRequest* RequestData,
	                   const FOnPostProjectPromoteFullResponse& Handler) const;
		
	/**
	 * @brief Private implementation for requests that require authentication that all overloaded BP UFunctions call.	  
	 */
	void BP_GetPromotionImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, const FBeamAuthToken& AuthToken, FBeamConnectivity& ConnectivityStatus, UGetPromotionRequest* RequestData,
	                  const FOnGetPromotionSuccess& OnSuccess, const FOnGetPromotionError& OnError, const FOnGetPromotionComplete& OnComplete, int64& OutRequestId) const;
	/**
	 * @brief Overload version for binding lambdas when in C++ land. Prefer the BP version whenever possible, this is here mostly for quick experimentation purposes.	 
	 */
	void CPP_GetPromotionImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, const FBeamAuthToken& AuthToken, FBeamConnectivity& ConnectivityStatus, UGetPromotionRequest* RequestData,
	                   const FOnGetPromotionFullResponse& Handler) const;
		
	/**
	 * @brief Private implementation for requests that require authentication that all overloaded BP UFunctions call.	  
	 */
	void BP_PostPromotionImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, const FBeamAuthToken& AuthToken, FBeamConnectivity& ConnectivityStatus, UPostPromotionRequest* RequestData,
	                  const FOnPostPromotionSuccess& OnSuccess, const FOnPostPromotionError& OnError, const FOnPostPromotionComplete& OnComplete, int64& OutRequestId) const;
	/**
	 * @brief Overload version for binding lambdas when in C++ land. Prefer the BP version whenever possible, this is here mostly for quick experimentation purposes.	 
	 */
	void CPP_PostPromotionImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, const FBeamAuthToken& AuthToken, FBeamConnectivity& ConnectivityStatus, UPostPromotionRequest* RequestData,
	                   const FOnPostPromotionFullResponse& Handler) const;

public:
	
	/** Used by a helper blueprint node so that you can easily chain requests in BP-land. */
	UFUNCTION(BlueprintPure, BlueprintInternalUseOnly)
	static UBeamRealmsApi* GetSelf() { return GEngine->GetEngineSubsystem<UBeamRealmsApi>(); }

	
	/**
	 * @brief Makes a request to the Get /basic/realms/customer/alias/available endpoint of the Realms Service.
	 *
	 * PREFER THE UFUNCTION OVERLOAD AS OPPOSED TO THIS. THIS MAINLY EXISTS TO ALLOW LAMBDA BINDING THE HANDLER.
	 * (Dynamic delegates do not allow for that so... we autogen this one to make experimenting in CPP a bit faster and for whenever you need to capture variables).
	 * 
	 * @param Request The Request UObject. All (de)serialized data the request data creates is tied to the lifecycle of this object.
	 * @param Handler A callback that defines how to handle success, error and completion. 
	 */
	void CPP_GetCustomerAliasAvailable(UGetCustomerAliasAvailableRequest* Request, const FOnGetCustomerAliasAvailableFullResponse& Handler) const;

		
	/**
	 * @brief Makes a request to the Get /basic/realms/project endpoint of the Realms Service.
	 *
	 * PREFER THE UFUNCTION OVERLOAD AS OPPOSED TO THIS. THIS MAINLY EXISTS TO ALLOW LAMBDA BINDING THE HANDLER.
	 * (Dynamic delegates do not allow for that so... we autogen this one to make experimenting in CPP a bit faster and for whenever you need to capture variables).
	 * 
	 * @param Request The Request UObject. All (de)serialized data the request data creates is tied to the lifecycle of this object.
	 * @param Handler A callback that defines how to handle success, error and completion. 
	 */
	void CPP_GetProject(UGetProjectRequest* Request, const FOnGetProjectFullResponse& Handler) const;

		
	/**
	 * @brief Makes a request to the Post /basic/realms/customer endpoint of the Realms Service.
	 *
	 * PREFER THE UFUNCTION OVERLOAD AS OPPOSED TO THIS. THIS MAINLY EXISTS TO ALLOW LAMBDA BINDING THE HANDLER.
	 * (Dynamic delegates do not allow for that so... we autogen this one to make experimenting in CPP a bit faster and for whenever you need to capture variables).
	 * 
	 * @param Request The Request UObject. All (de)serialized data the request data creates is tied to the lifecycle of this object.
	 * @param Handler A callback that defines how to handle success, error and completion. 
	 */
	void CPP_PostCustomer(UPostCustomerRequest* Request, const FOnPostCustomerFullResponse& Handler) const;

		
	/**
	 * @brief Makes a request to the Get /basic/realms/is-customer endpoint of the Realms Service.
	 *
	 * PREFER THE UFUNCTION OVERLOAD AS OPPOSED TO THIS. THIS MAINLY EXISTS TO ALLOW LAMBDA BINDING THE HANDLER.
	 * (Dynamic delegates do not allow for that so... we autogen this one to make experimenting in CPP a bit faster and for whenever you need to capture variables).
	 * 
	 * @param Request The Request UObject. All (de)serialized data the request data creates is tied to the lifecycle of this object.
	 * @param Handler A callback that defines how to handle success, error and completion. 
	 */
	void CPP_GetIsCustomer(UGetIsCustomerRequest* Request, const FOnGetIsCustomerFullResponse& Handler) const;

		
	/**
	 * @brief Makes a request to the Get /basic/realms/customers endpoint of the Realms Service.
	 *
	 * PREFER THE UFUNCTION OVERLOAD AS OPPOSED TO THIS. THIS MAINLY EXISTS TO ALLOW LAMBDA BINDING THE HANDLER.
	 * (Dynamic delegates do not allow for that so... we autogen this one to make experimenting in CPP a bit faster and for whenever you need to capture variables).
	 * 
	 * @param Request The Request UObject. All (de)serialized data the request data creates is tied to the lifecycle of this object.
	 * @param Handler A callback that defines how to handle success, error and completion. 
	 */
	void CPP_GetCustomers(UGetCustomersRequest* Request, const FOnGetCustomersFullResponse& Handler) const;


	
	/**
	 * @brief Makes an authenticated request to the Post /basic/realms/project/beamable endpoint of the Realms Service.
	 *
	 * PREFER THE UFUNCTION OVERLOAD AS OPPOSED TO THIS. THIS MAINLY EXISTS TO ALLOW LAMBDA BINDING THE HANDLER.
	 * (Dynamic delegates do not allow for that so... we autogen this one to make experimenting in CPP a bit faster).
	 * 
	 * @param UserSlot The Authenticated User Slot that is making this request.
	 * @param Request The Request UObject. All (de)serialized data the request data creates is tied to the lifecycle of this object.
	 * @param Handler A callback that defines how to handle success, error and completion. 
	 */
	void CPP_PostProjectBeamable(const FUserSlot& UserSlot, UPostProjectBeamableRequest* Request, const FOnPostProjectBeamableFullResponse& Handler) const;

		
	/**
	 * @brief Makes an authenticated request to the Post /basic/realms/project endpoint of the Realms Service.
	 *
	 * PREFER THE UFUNCTION OVERLOAD AS OPPOSED TO THIS. THIS MAINLY EXISTS TO ALLOW LAMBDA BINDING THE HANDLER.
	 * (Dynamic delegates do not allow for that so... we autogen this one to make experimenting in CPP a bit faster).
	 * 
	 * @param UserSlot The Authenticated User Slot that is making this request.
	 * @param Request The Request UObject. All (de)serialized data the request data creates is tied to the lifecycle of this object.
	 * @param Handler A callback that defines how to handle success, error and completion. 
	 */
	void CPP_PostProject(const FUserSlot& UserSlot, UPostProjectRequest* Request, const FOnPostProjectFullResponse& Handler) const;

		
	/**
	 * @brief Makes an authenticated request to the Put /basic/realms/project endpoint of the Realms Service.
	 *
	 * PREFER THE UFUNCTION OVERLOAD AS OPPOSED TO THIS. THIS MAINLY EXISTS TO ALLOW LAMBDA BINDING THE HANDLER.
	 * (Dynamic delegates do not allow for that so... we autogen this one to make experimenting in CPP a bit faster).
	 * 
	 * @param UserSlot The Authenticated User Slot that is making this request.
	 * @param Request The Request UObject. All (de)serialized data the request data creates is tied to the lifecycle of this object.
	 * @param Handler A callback that defines how to handle success, error and completion. 
	 */
	void CPP_PutProject(const FUserSlot& UserSlot, UPutProjectRequest* Request, const FOnPutProjectFullResponse& Handler) const;

		
	/**
	 * @brief Makes an authenticated request to the Delete /basic/realms/project endpoint of the Realms Service.
	 *
	 * PREFER THE UFUNCTION OVERLOAD AS OPPOSED TO THIS. THIS MAINLY EXISTS TO ALLOW LAMBDA BINDING THE HANDLER.
	 * (Dynamic delegates do not allow for that so... we autogen this one to make experimenting in CPP a bit faster).
	 * 
	 * @param UserSlot The Authenticated User Slot that is making this request.
	 * @param Request The Request UObject. All (de)serialized data the request data creates is tied to the lifecycle of this object.
	 * @param Handler A callback that defines how to handle success, error and completion. 
	 */
	void CPP_DeleteProject(const FUserSlot& UserSlot, UDeleteProjectRequest* Request, const FOnDeleteProjectFullResponse& Handler) const;

		
	/**
	 * @brief Makes an authenticated request to the Get /basic/realms/games endpoint of the Realms Service.
	 *
	 * PREFER THE UFUNCTION OVERLOAD AS OPPOSED TO THIS. THIS MAINLY EXISTS TO ALLOW LAMBDA BINDING THE HANDLER.
	 * (Dynamic delegates do not allow for that so... we autogen this one to make experimenting in CPP a bit faster).
	 * 
	 * @param UserSlot The Authenticated User Slot that is making this request.
	 * @param Request The Request UObject. All (de)serialized data the request data creates is tied to the lifecycle of this object.
	 * @param Handler A callback that defines how to handle success, error and completion. 
	 */
	void CPP_GetGames(const FUserSlot& UserSlot, UGetGamesRequest* Request, const FOnGetGamesFullResponse& Handler) const;

		
	/**
	 * @brief Makes an authenticated request to the Get /basic/realms/config endpoint of the Realms Service.
	 *
	 * PREFER THE UFUNCTION OVERLOAD AS OPPOSED TO THIS. THIS MAINLY EXISTS TO ALLOW LAMBDA BINDING THE HANDLER.
	 * (Dynamic delegates do not allow for that so... we autogen this one to make experimenting in CPP a bit faster).
	 * 
	 * @param UserSlot The Authenticated User Slot that is making this request.
	 * @param Request The Request UObject. All (de)serialized data the request data creates is tied to the lifecycle of this object.
	 * @param Handler A callback that defines how to handle success, error and completion. 
	 */
	void CPP_GetConfig(const FUserSlot& UserSlot, UGetConfigRequest* Request, const FOnGetConfigFullResponse& Handler) const;

		
	/**
	 * @brief Makes an authenticated request to the Put /basic/realms/config endpoint of the Realms Service.
	 *
	 * PREFER THE UFUNCTION OVERLOAD AS OPPOSED TO THIS. THIS MAINLY EXISTS TO ALLOW LAMBDA BINDING THE HANDLER.
	 * (Dynamic delegates do not allow for that so... we autogen this one to make experimenting in CPP a bit faster).
	 * 
	 * @param UserSlot The Authenticated User Slot that is making this request.
	 * @param Request The Request UObject. All (de)serialized data the request data creates is tied to the lifecycle of this object.
	 * @param Handler A callback that defines how to handle success, error and completion. 
	 */
	void CPP_PutConfig(const FUserSlot& UserSlot, UPutConfigRequest* Request, const FOnPutConfigFullResponse& Handler) const;

		
	/**
	 * @brief Makes an authenticated request to the Put /basic/realms/project/rename endpoint of the Realms Service.
	 *
	 * PREFER THE UFUNCTION OVERLOAD AS OPPOSED TO THIS. THIS MAINLY EXISTS TO ALLOW LAMBDA BINDING THE HANDLER.
	 * (Dynamic delegates do not allow for that so... we autogen this one to make experimenting in CPP a bit faster).
	 * 
	 * @param UserSlot The Authenticated User Slot that is making this request.
	 * @param Request The Request UObject. All (de)serialized data the request data creates is tied to the lifecycle of this object.
	 * @param Handler A callback that defines how to handle success, error and completion. 
	 */
	void CPP_PutProjectRename(const FUserSlot& UserSlot, UPutProjectRenameRequest* Request, const FOnPutProjectRenameFullResponse& Handler) const;

		
	/**
	 * @brief Makes an authenticated request to the Get /basic/realms/plans endpoint of the Realms Service.
	 *
	 * PREFER THE UFUNCTION OVERLOAD AS OPPOSED TO THIS. THIS MAINLY EXISTS TO ALLOW LAMBDA BINDING THE HANDLER.
	 * (Dynamic delegates do not allow for that so... we autogen this one to make experimenting in CPP a bit faster).
	 * 
	 * @param UserSlot The Authenticated User Slot that is making this request.
	 * @param Request The Request UObject. All (de)serialized data the request data creates is tied to the lifecycle of this object.
	 * @param Handler A callback that defines how to handle success, error and completion. 
	 */
	void CPP_GetPlans(const FUserSlot& UserSlot, UGetPlansRequest* Request, const FOnGetPlansFullResponse& Handler) const;

		
	/**
	 * @brief Makes an authenticated request to the Post /basic/realms/plans endpoint of the Realms Service.
	 *
	 * PREFER THE UFUNCTION OVERLOAD AS OPPOSED TO THIS. THIS MAINLY EXISTS TO ALLOW LAMBDA BINDING THE HANDLER.
	 * (Dynamic delegates do not allow for that so... we autogen this one to make experimenting in CPP a bit faster).
	 * 
	 * @param UserSlot The Authenticated User Slot that is making this request.
	 * @param Request The Request UObject. All (de)serialized data the request data creates is tied to the lifecycle of this object.
	 * @param Handler A callback that defines how to handle success, error and completion. 
	 */
	void CPP_PostPlans(const FUserSlot& UserSlot, UPostPlansRequest* Request, const FOnPostPlansFullResponse& Handler) const;

		
	/**
	 * @brief Makes an authenticated request to the Get /basic/realms/customer endpoint of the Realms Service.
	 *
	 * PREFER THE UFUNCTION OVERLOAD AS OPPOSED TO THIS. THIS MAINLY EXISTS TO ALLOW LAMBDA BINDING THE HANDLER.
	 * (Dynamic delegates do not allow for that so... we autogen this one to make experimenting in CPP a bit faster).
	 * 
	 * @param UserSlot The Authenticated User Slot that is making this request.
	 * @param Request The Request UObject. All (de)serialized data the request data creates is tied to the lifecycle of this object.
	 * @param Handler A callback that defines how to handle success, error and completion. 
	 */
	void CPP_GetCustomer(const FUserSlot& UserSlot, UGetCustomerRequest* Request, const FOnGetCustomerFullResponse& Handler) const;

		
	/**
	 * @brief Makes an authenticated request to the Get /basic/realms/launch-message endpoint of the Realms Service.
	 *
	 * PREFER THE UFUNCTION OVERLOAD AS OPPOSED TO THIS. THIS MAINLY EXISTS TO ALLOW LAMBDA BINDING THE HANDLER.
	 * (Dynamic delegates do not allow for that so... we autogen this one to make experimenting in CPP a bit faster).
	 * 
	 * @param UserSlot The Authenticated User Slot that is making this request.
	 * @param Request The Request UObject. All (de)serialized data the request data creates is tied to the lifecycle of this object.
	 * @param Handler A callback that defines how to handle success, error and completion. 
	 */
	void CPP_GetLaunchMessage(const FUserSlot& UserSlot, UGetLaunchMessageRequest* Request, const FOnGetLaunchMessageFullResponse& Handler) const;

		
	/**
	 * @brief Makes an authenticated request to the Post /basic/realms/launch-message endpoint of the Realms Service.
	 *
	 * PREFER THE UFUNCTION OVERLOAD AS OPPOSED TO THIS. THIS MAINLY EXISTS TO ALLOW LAMBDA BINDING THE HANDLER.
	 * (Dynamic delegates do not allow for that so... we autogen this one to make experimenting in CPP a bit faster).
	 * 
	 * @param UserSlot The Authenticated User Slot that is making this request.
	 * @param Request The Request UObject. All (de)serialized data the request data creates is tied to the lifecycle of this object.
	 * @param Handler A callback that defines how to handle success, error and completion. 
	 */
	void CPP_PostLaunchMessage(const FUserSlot& UserSlot, UPostLaunchMessageRequest* Request, const FOnPostLaunchMessageFullResponse& Handler) const;

		
	/**
	 * @brief Makes an authenticated request to the Delete /basic/realms/launch-message endpoint of the Realms Service.
	 *
	 * PREFER THE UFUNCTION OVERLOAD AS OPPOSED TO THIS. THIS MAINLY EXISTS TO ALLOW LAMBDA BINDING THE HANDLER.
	 * (Dynamic delegates do not allow for that so... we autogen this one to make experimenting in CPP a bit faster).
	 * 
	 * @param UserSlot The Authenticated User Slot that is making this request.
	 * @param Request The Request UObject. All (de)serialized data the request data creates is tied to the lifecycle of this object.
	 * @param Handler A callback that defines how to handle success, error and completion. 
	 */
	void CPP_DeleteLaunchMessage(const FUserSlot& UserSlot, UDeleteLaunchMessageRequest* Request, const FOnDeleteLaunchMessageFullResponse& Handler) const;

		
	/**
	 * @brief Makes an authenticated request to the Get /basic/realms/admin/customer endpoint of the Realms Service.
	 *
	 * PREFER THE UFUNCTION OVERLOAD AS OPPOSED TO THIS. THIS MAINLY EXISTS TO ALLOW LAMBDA BINDING THE HANDLER.
	 * (Dynamic delegates do not allow for that so... we autogen this one to make experimenting in CPP a bit faster).
	 * 
	 * @param UserSlot The Authenticated User Slot that is making this request.
	 * @param Request The Request UObject. All (de)serialized data the request data creates is tied to the lifecycle of this object.
	 * @param Handler A callback that defines how to handle success, error and completion. 
	 */
	void CPP_GetAdminCustomer(const FUserSlot& UserSlot, UGetAdminCustomerRequest* Request, const FOnGetAdminCustomerFullResponse& Handler) const;

		
	/**
	 * @brief Makes an authenticated request to the Get /basic/realms/game endpoint of the Realms Service.
	 *
	 * PREFER THE UFUNCTION OVERLOAD AS OPPOSED TO THIS. THIS MAINLY EXISTS TO ALLOW LAMBDA BINDING THE HANDLER.
	 * (Dynamic delegates do not allow for that so... we autogen this one to make experimenting in CPP a bit faster).
	 * 
	 * @param UserSlot The Authenticated User Slot that is making this request.
	 * @param Request The Request UObject. All (de)serialized data the request data creates is tied to the lifecycle of this object.
	 * @param Handler A callback that defines how to handle success, error and completion. 
	 */
	void CPP_GetGame(const FUserSlot& UserSlot, UGetGameRequest* Request, const FOnGetGameFullResponse& Handler) const;

		
	/**
	 * @brief Makes an authenticated request to the Post /basic/realms/game endpoint of the Realms Service.
	 *
	 * PREFER THE UFUNCTION OVERLOAD AS OPPOSED TO THIS. THIS MAINLY EXISTS TO ALLOW LAMBDA BINDING THE HANDLER.
	 * (Dynamic delegates do not allow for that so... we autogen this one to make experimenting in CPP a bit faster).
	 * 
	 * @param UserSlot The Authenticated User Slot that is making this request.
	 * @param Request The Request UObject. All (de)serialized data the request data creates is tied to the lifecycle of this object.
	 * @param Handler A callback that defines how to handle success, error and completion. 
	 */
	void CPP_PostGame(const FUserSlot& UserSlot, UBasicRealmsPostGameRequest* Request, const FOnBasicRealmsPostGameFullResponse& Handler) const;

		
	/**
	 * @brief Makes an authenticated request to the Put /basic/realms/game endpoint of the Realms Service.
	 *
	 * PREFER THE UFUNCTION OVERLOAD AS OPPOSED TO THIS. THIS MAINLY EXISTS TO ALLOW LAMBDA BINDING THE HANDLER.
	 * (Dynamic delegates do not allow for that so... we autogen this one to make experimenting in CPP a bit faster).
	 * 
	 * @param UserSlot The Authenticated User Slot that is making this request.
	 * @param Request The Request UObject. All (de)serialized data the request data creates is tied to the lifecycle of this object.
	 * @param Handler A callback that defines how to handle success, error and completion. 
	 */
	void CPP_PutGame(const FUserSlot& UserSlot, UPutGameRequest* Request, const FOnPutGameFullResponse& Handler) const;

		
	/**
	 * @brief Makes an authenticated request to the Get /basic/realms/project/promote endpoint of the Realms Service.
	 *
	 * PREFER THE UFUNCTION OVERLOAD AS OPPOSED TO THIS. THIS MAINLY EXISTS TO ALLOW LAMBDA BINDING THE HANDLER.
	 * (Dynamic delegates do not allow for that so... we autogen this one to make experimenting in CPP a bit faster).
	 * 
	 * @param UserSlot The Authenticated User Slot that is making this request.
	 * @param Request The Request UObject. All (de)serialized data the request data creates is tied to the lifecycle of this object.
	 * @param Handler A callback that defines how to handle success, error and completion. 
	 */
	void CPP_GetProjectPromote(const FUserSlot& UserSlot, UGetProjectPromoteRequest* Request, const FOnGetProjectPromoteFullResponse& Handler) const;

		
	/**
	 * @brief Makes an authenticated request to the Post /basic/realms/project/promote endpoint of the Realms Service.
	 *
	 * PREFER THE UFUNCTION OVERLOAD AS OPPOSED TO THIS. THIS MAINLY EXISTS TO ALLOW LAMBDA BINDING THE HANDLER.
	 * (Dynamic delegates do not allow for that so... we autogen this one to make experimenting in CPP a bit faster).
	 * 
	 * @param UserSlot The Authenticated User Slot that is making this request.
	 * @param Request The Request UObject. All (de)serialized data the request data creates is tied to the lifecycle of this object.
	 * @param Handler A callback that defines how to handle success, error and completion. 
	 */
	void CPP_PostProjectPromote(const FUserSlot& UserSlot, UPostProjectPromoteRequest* Request, const FOnPostProjectPromoteFullResponse& Handler) const;

		
	/**
	 * @brief Makes an authenticated request to the Get /basic/realms/promotion endpoint of the Realms Service.
	 *
	 * PREFER THE UFUNCTION OVERLOAD AS OPPOSED TO THIS. THIS MAINLY EXISTS TO ALLOW LAMBDA BINDING THE HANDLER.
	 * (Dynamic delegates do not allow for that so... we autogen this one to make experimenting in CPP a bit faster).
	 * 
	 * @param UserSlot The Authenticated User Slot that is making this request.
	 * @param Request The Request UObject. All (de)serialized data the request data creates is tied to the lifecycle of this object.
	 * @param Handler A callback that defines how to handle success, error and completion. 
	 */
	void CPP_GetPromotion(const FUserSlot& UserSlot, UGetPromotionRequest* Request, const FOnGetPromotionFullResponse& Handler) const;

		
	/**
	 * @brief Makes an authenticated request to the Post /basic/realms/promotion endpoint of the Realms Service.
	 *
	 * PREFER THE UFUNCTION OVERLOAD AS OPPOSED TO THIS. THIS MAINLY EXISTS TO ALLOW LAMBDA BINDING THE HANDLER.
	 * (Dynamic delegates do not allow for that so... we autogen this one to make experimenting in CPP a bit faster).
	 * 
	 * @param UserSlot The Authenticated User Slot that is making this request.
	 * @param Request The Request UObject. All (de)serialized data the request data creates is tied to the lifecycle of this object.
	 * @param Handler A callback that defines how to handle success, error and completion. 
	 */
	void CPP_PostPromotion(const FUserSlot& UserSlot, UPostPromotionRequest* Request, const FOnPostPromotionFullResponse& Handler) const;


	
	/**
	 * @brief Makes a request to the Get /basic/realms/customer/alias/available endpoint of the Realms Service.
	 *
	 * @param Request The Request UObject. All (de)serialized data the request data creates is tied to the lifecycle of this object.
	 * @param OnSuccess What to do if the requests receives a successful response.
	 * @param OnError What to do if the request receives an error response.
	 * @param OnComplete What to after either OnSuccess or OnError have finished executing.
	 * @param OutRequestContext The Request Context associated with this request -- used to query information about the request or to cancel it while it's in flight. 
	 */
	UFUNCTION(BlueprintCallable, BlueprintInternalUseOnly, Category="Beam|Backend|Realms", meta=(AutoCreateRefTerm="OnSuccess,OnError,OnComplete", BeamFlowStart))
	void GetCustomerAliasAvailable(UGetCustomerAliasAvailableRequest* Request, const FOnGetCustomerAliasAvailableSuccess& OnSuccess, const FOnGetCustomerAliasAvailableError& OnError, const FOnGetCustomerAliasAvailableComplete& OnComplete, FBeamRequestContext& OutRequestContext);

		
	/**
	 * @brief Makes a request to the Get /basic/realms/project endpoint of the Realms Service.
	 *
	 * @param Request The Request UObject. All (de)serialized data the request data creates is tied to the lifecycle of this object.
	 * @param OnSuccess What to do if the requests receives a successful response.
	 * @param OnError What to do if the request receives an error response.
	 * @param OnComplete What to after either OnSuccess or OnError have finished executing.
	 * @param OutRequestContext The Request Context associated with this request -- used to query information about the request or to cancel it while it's in flight. 
	 */
	UFUNCTION(BlueprintCallable, BlueprintInternalUseOnly, Category="Beam|Backend|Realms", meta=(AutoCreateRefTerm="OnSuccess,OnError,OnComplete", BeamFlowStart))
	void GetProject(UGetProjectRequest* Request, const FOnGetProjectSuccess& OnSuccess, const FOnGetProjectError& OnError, const FOnGetProjectComplete& OnComplete, FBeamRequestContext& OutRequestContext);

		
	/**
	 * @brief Makes a request to the Post /basic/realms/customer endpoint of the Realms Service.
	 *
	 * @param Request The Request UObject. All (de)serialized data the request data creates is tied to the lifecycle of this object.
	 * @param OnSuccess What to do if the requests receives a successful response.
	 * @param OnError What to do if the request receives an error response.
	 * @param OnComplete What to after either OnSuccess or OnError have finished executing.
	 * @param OutRequestContext The Request Context associated with this request -- used to query information about the request or to cancel it while it's in flight. 
	 */
	UFUNCTION(BlueprintCallable, BlueprintInternalUseOnly, Category="Beam|Backend|Realms", meta=(AutoCreateRefTerm="OnSuccess,OnError,OnComplete", BeamFlowStart))
	void PostCustomer(UPostCustomerRequest* Request, const FOnPostCustomerSuccess& OnSuccess, const FOnPostCustomerError& OnError, const FOnPostCustomerComplete& OnComplete, FBeamRequestContext& OutRequestContext);

		
	/**
	 * @brief Makes a request to the Get /basic/realms/is-customer endpoint of the Realms Service.
	 *
	 * @param Request The Request UObject. All (de)serialized data the request data creates is tied to the lifecycle of this object.
	 * @param OnSuccess What to do if the requests receives a successful response.
	 * @param OnError What to do if the request receives an error response.
	 * @param OnComplete What to after either OnSuccess or OnError have finished executing.
	 * @param OutRequestContext The Request Context associated with this request -- used to query information about the request or to cancel it while it's in flight. 
	 */
	UFUNCTION(BlueprintCallable, BlueprintInternalUseOnly, Category="Beam|Backend|Realms", meta=(AutoCreateRefTerm="OnSuccess,OnError,OnComplete", BeamFlowStart))
	void GetIsCustomer(UGetIsCustomerRequest* Request, const FOnGetIsCustomerSuccess& OnSuccess, const FOnGetIsCustomerError& OnError, const FOnGetIsCustomerComplete& OnComplete, FBeamRequestContext& OutRequestContext);

		
	/**
	 * @brief Makes a request to the Get /basic/realms/customers endpoint of the Realms Service.
	 *
	 * @param Request The Request UObject. All (de)serialized data the request data creates is tied to the lifecycle of this object.
	 * @param OnSuccess What to do if the requests receives a successful response.
	 * @param OnError What to do if the request receives an error response.
	 * @param OnComplete What to after either OnSuccess or OnError have finished executing.
	 * @param OutRequestContext The Request Context associated with this request -- used to query information about the request or to cancel it while it's in flight. 
	 */
	UFUNCTION(BlueprintCallable, BlueprintInternalUseOnly, Category="Beam|Backend|Realms", meta=(AutoCreateRefTerm="OnSuccess,OnError,OnComplete", BeamFlowStart))
	void GetCustomers(UGetCustomersRequest* Request, const FOnGetCustomersSuccess& OnSuccess, const FOnGetCustomersError& OnError, const FOnGetCustomersComplete& OnComplete, FBeamRequestContext& OutRequestContext);


	
	/**
	 * @brief Makes an authenticated request to the Post /basic/realms/project/beamable endpoint of the Realms Service.
	 *
	 * @param UserSlot The authenticated UserSlot with the user making the request. 
	 * @param Request The Request UObject. All (de)serialized data the request data creates is tied to the lifecycle of this object.
	 * @param OnSuccess What to do if the requests receives a successful response.
	 * @param OnError What to do if the request receives an error response.
	 * @param OnComplete What to after either OnSuccess or OnError have finished executing.
	 * @param OutRequestContext The Request Context associated with this request -- used to query information about the request or to cancel it while it's in flight. 
	 */
	UFUNCTION(BlueprintCallable, BlueprintInternalUseOnly, Category="Beam|Backend|Realms", meta=(AutoCreateRefTerm="UserSlot,OnSuccess,OnError,OnComplete", BeamFlowStart))
	void PostProjectBeamable(FUserSlot UserSlot, UPostProjectBeamableRequest* Request, const FOnPostProjectBeamableSuccess& OnSuccess, const FOnPostProjectBeamableError& OnError, const FOnPostProjectBeamableComplete& OnComplete, FBeamRequestContext& OutRequestContext);

		
	/**
	 * @brief Makes an authenticated request to the Post /basic/realms/project endpoint of the Realms Service.
	 *
	 * @param UserSlot The authenticated UserSlot with the user making the request. 
	 * @param Request The Request UObject. All (de)serialized data the request data creates is tied to the lifecycle of this object.
	 * @param OnSuccess What to do if the requests receives a successful response.
	 * @param OnError What to do if the request receives an error response.
	 * @param OnComplete What to after either OnSuccess or OnError have finished executing.
	 * @param OutRequestContext The Request Context associated with this request -- used to query information about the request or to cancel it while it's in flight. 
	 */
	UFUNCTION(BlueprintCallable, BlueprintInternalUseOnly, Category="Beam|Backend|Realms", meta=(AutoCreateRefTerm="UserSlot,OnSuccess,OnError,OnComplete", BeamFlowStart))
	void PostProject(FUserSlot UserSlot, UPostProjectRequest* Request, const FOnPostProjectSuccess& OnSuccess, const FOnPostProjectError& OnError, const FOnPostProjectComplete& OnComplete, FBeamRequestContext& OutRequestContext);

		
	/**
	 * @brief Makes an authenticated request to the Put /basic/realms/project endpoint of the Realms Service.
	 *
	 * @param UserSlot The authenticated UserSlot with the user making the request. 
	 * @param Request The Request UObject. All (de)serialized data the request data creates is tied to the lifecycle of this object.
	 * @param OnSuccess What to do if the requests receives a successful response.
	 * @param OnError What to do if the request receives an error response.
	 * @param OnComplete What to after either OnSuccess or OnError have finished executing.
	 * @param OutRequestContext The Request Context associated with this request -- used to query information about the request or to cancel it while it's in flight. 
	 */
	UFUNCTION(BlueprintCallable, BlueprintInternalUseOnly, Category="Beam|Backend|Realms", meta=(AutoCreateRefTerm="UserSlot,OnSuccess,OnError,OnComplete", BeamFlowStart))
	void PutProject(FUserSlot UserSlot, UPutProjectRequest* Request, const FOnPutProjectSuccess& OnSuccess, const FOnPutProjectError& OnError, const FOnPutProjectComplete& OnComplete, FBeamRequestContext& OutRequestContext);

		
	/**
	 * @brief Makes an authenticated request to the Delete /basic/realms/project endpoint of the Realms Service.
	 *
	 * @param UserSlot The authenticated UserSlot with the user making the request. 
	 * @param Request The Request UObject. All (de)serialized data the request data creates is tied to the lifecycle of this object.
	 * @param OnSuccess What to do if the requests receives a successful response.
	 * @param OnError What to do if the request receives an error response.
	 * @param OnComplete What to after either OnSuccess or OnError have finished executing.
	 * @param OutRequestContext The Request Context associated with this request -- used to query information about the request or to cancel it while it's in flight. 
	 */
	UFUNCTION(BlueprintCallable, BlueprintInternalUseOnly, Category="Beam|Backend|Realms", meta=(AutoCreateRefTerm="UserSlot,OnSuccess,OnError,OnComplete", BeamFlowStart))
	void DeleteProject(FUserSlot UserSlot, UDeleteProjectRequest* Request, const FOnDeleteProjectSuccess& OnSuccess, const FOnDeleteProjectError& OnError, const FOnDeleteProjectComplete& OnComplete, FBeamRequestContext& OutRequestContext);

		
	/**
	 * @brief Makes an authenticated request to the Get /basic/realms/games endpoint of the Realms Service.
	 *
	 * @param UserSlot The authenticated UserSlot with the user making the request. 
	 * @param Request The Request UObject. All (de)serialized data the request data creates is tied to the lifecycle of this object.
	 * @param OnSuccess What to do if the requests receives a successful response.
	 * @param OnError What to do if the request receives an error response.
	 * @param OnComplete What to after either OnSuccess or OnError have finished executing.
	 * @param OutRequestContext The Request Context associated with this request -- used to query information about the request or to cancel it while it's in flight. 
	 */
	UFUNCTION(BlueprintCallable, BlueprintInternalUseOnly, Category="Beam|Backend|Realms", meta=(AutoCreateRefTerm="UserSlot,OnSuccess,OnError,OnComplete", BeamFlowStart))
	void GetGames(FUserSlot UserSlot, UGetGamesRequest* Request, const FOnGetGamesSuccess& OnSuccess, const FOnGetGamesError& OnError, const FOnGetGamesComplete& OnComplete, FBeamRequestContext& OutRequestContext);

		
	/**
	 * @brief Makes an authenticated request to the Get /basic/realms/config endpoint of the Realms Service.
	 *
	 * @param UserSlot The authenticated UserSlot with the user making the request. 
	 * @param Request The Request UObject. All (de)serialized data the request data creates is tied to the lifecycle of this object.
	 * @param OnSuccess What to do if the requests receives a successful response.
	 * @param OnError What to do if the request receives an error response.
	 * @param OnComplete What to after either OnSuccess or OnError have finished executing.
	 * @param OutRequestContext The Request Context associated with this request -- used to query information about the request or to cancel it while it's in flight. 
	 */
	UFUNCTION(BlueprintCallable, BlueprintInternalUseOnly, Category="Beam|Backend|Realms", meta=(AutoCreateRefTerm="UserSlot,OnSuccess,OnError,OnComplete", BeamFlowStart))
	void GetConfig(FUserSlot UserSlot, UGetConfigRequest* Request, const FOnGetConfigSuccess& OnSuccess, const FOnGetConfigError& OnError, const FOnGetConfigComplete& OnComplete, FBeamRequestContext& OutRequestContext);

		
	/**
	 * @brief Makes an authenticated request to the Put /basic/realms/config endpoint of the Realms Service.
	 *
	 * @param UserSlot The authenticated UserSlot with the user making the request. 
	 * @param Request The Request UObject. All (de)serialized data the request data creates is tied to the lifecycle of this object.
	 * @param OnSuccess What to do if the requests receives a successful response.
	 * @param OnError What to do if the request receives an error response.
	 * @param OnComplete What to after either OnSuccess or OnError have finished executing.
	 * @param OutRequestContext The Request Context associated with this request -- used to query information about the request or to cancel it while it's in flight. 
	 */
	UFUNCTION(BlueprintCallable, BlueprintInternalUseOnly, Category="Beam|Backend|Realms", meta=(AutoCreateRefTerm="UserSlot,OnSuccess,OnError,OnComplete", BeamFlowStart))
	void PutConfig(FUserSlot UserSlot, UPutConfigRequest* Request, const FOnPutConfigSuccess& OnSuccess, const FOnPutConfigError& OnError, const FOnPutConfigComplete& OnComplete, FBeamRequestContext& OutRequestContext);

		
	/**
	 * @brief Makes an authenticated request to the Put /basic/realms/project/rename endpoint of the Realms Service.
	 *
	 * @param UserSlot The authenticated UserSlot with the user making the request. 
	 * @param Request The Request UObject. All (de)serialized data the request data creates is tied to the lifecycle of this object.
	 * @param OnSuccess What to do if the requests receives a successful response.
	 * @param OnError What to do if the request receives an error response.
	 * @param OnComplete What to after either OnSuccess or OnError have finished executing.
	 * @param OutRequestContext The Request Context associated with this request -- used to query information about the request or to cancel it while it's in flight. 
	 */
	UFUNCTION(BlueprintCallable, BlueprintInternalUseOnly, Category="Beam|Backend|Realms", meta=(AutoCreateRefTerm="UserSlot,OnSuccess,OnError,OnComplete", BeamFlowStart))
	void PutProjectRename(FUserSlot UserSlot, UPutProjectRenameRequest* Request, const FOnPutProjectRenameSuccess& OnSuccess, const FOnPutProjectRenameError& OnError, const FOnPutProjectRenameComplete& OnComplete, FBeamRequestContext& OutRequestContext);

		
	/**
	 * @brief Makes an authenticated request to the Get /basic/realms/plans endpoint of the Realms Service.
	 *
	 * @param UserSlot The authenticated UserSlot with the user making the request. 
	 * @param Request The Request UObject. All (de)serialized data the request data creates is tied to the lifecycle of this object.
	 * @param OnSuccess What to do if the requests receives a successful response.
	 * @param OnError What to do if the request receives an error response.
	 * @param OnComplete What to after either OnSuccess or OnError have finished executing.
	 * @param OutRequestContext The Request Context associated with this request -- used to query information about the request or to cancel it while it's in flight. 
	 */
	UFUNCTION(BlueprintCallable, BlueprintInternalUseOnly, Category="Beam|Backend|Realms", meta=(AutoCreateRefTerm="UserSlot,OnSuccess,OnError,OnComplete", BeamFlowStart))
	void GetPlans(FUserSlot UserSlot, UGetPlansRequest* Request, const FOnGetPlansSuccess& OnSuccess, const FOnGetPlansError& OnError, const FOnGetPlansComplete& OnComplete, FBeamRequestContext& OutRequestContext);

		
	/**
	 * @brief Makes an authenticated request to the Post /basic/realms/plans endpoint of the Realms Service.
	 *
	 * @param UserSlot The authenticated UserSlot with the user making the request. 
	 * @param Request The Request UObject. All (de)serialized data the request data creates is tied to the lifecycle of this object.
	 * @param OnSuccess What to do if the requests receives a successful response.
	 * @param OnError What to do if the request receives an error response.
	 * @param OnComplete What to after either OnSuccess or OnError have finished executing.
	 * @param OutRequestContext The Request Context associated with this request -- used to query information about the request or to cancel it while it's in flight. 
	 */
	UFUNCTION(BlueprintCallable, BlueprintInternalUseOnly, Category="Beam|Backend|Realms", meta=(AutoCreateRefTerm="UserSlot,OnSuccess,OnError,OnComplete", BeamFlowStart))
	void PostPlans(FUserSlot UserSlot, UPostPlansRequest* Request, const FOnPostPlansSuccess& OnSuccess, const FOnPostPlansError& OnError, const FOnPostPlansComplete& OnComplete, FBeamRequestContext& OutRequestContext);

		
	/**
	 * @brief Makes an authenticated request to the Get /basic/realms/customer endpoint of the Realms Service.
	 *
	 * @param UserSlot The authenticated UserSlot with the user making the request. 
	 * @param Request The Request UObject. All (de)serialized data the request data creates is tied to the lifecycle of this object.
	 * @param OnSuccess What to do if the requests receives a successful response.
	 * @param OnError What to do if the request receives an error response.
	 * @param OnComplete What to after either OnSuccess or OnError have finished executing.
	 * @param OutRequestContext The Request Context associated with this request -- used to query information about the request or to cancel it while it's in flight. 
	 */
	UFUNCTION(BlueprintCallable, BlueprintInternalUseOnly, Category="Beam|Backend|Realms", meta=(AutoCreateRefTerm="UserSlot,OnSuccess,OnError,OnComplete", BeamFlowStart))
	void GetCustomer(FUserSlot UserSlot, UGetCustomerRequest* Request, const FOnGetCustomerSuccess& OnSuccess, const FOnGetCustomerError& OnError, const FOnGetCustomerComplete& OnComplete, FBeamRequestContext& OutRequestContext);

		
	/**
	 * @brief Makes an authenticated request to the Get /basic/realms/launch-message endpoint of the Realms Service.
	 *
	 * @param UserSlot The authenticated UserSlot with the user making the request. 
	 * @param Request The Request UObject. All (de)serialized data the request data creates is tied to the lifecycle of this object.
	 * @param OnSuccess What to do if the requests receives a successful response.
	 * @param OnError What to do if the request receives an error response.
	 * @param OnComplete What to after either OnSuccess or OnError have finished executing.
	 * @param OutRequestContext The Request Context associated with this request -- used to query information about the request or to cancel it while it's in flight. 
	 */
	UFUNCTION(BlueprintCallable, BlueprintInternalUseOnly, Category="Beam|Backend|Realms", meta=(AutoCreateRefTerm="UserSlot,OnSuccess,OnError,OnComplete", BeamFlowStart))
	void GetLaunchMessage(FUserSlot UserSlot, UGetLaunchMessageRequest* Request, const FOnGetLaunchMessageSuccess& OnSuccess, const FOnGetLaunchMessageError& OnError, const FOnGetLaunchMessageComplete& OnComplete, FBeamRequestContext& OutRequestContext);

		
	/**
	 * @brief Makes an authenticated request to the Post /basic/realms/launch-message endpoint of the Realms Service.
	 *
	 * @param UserSlot The authenticated UserSlot with the user making the request. 
	 * @param Request The Request UObject. All (de)serialized data the request data creates is tied to the lifecycle of this object.
	 * @param OnSuccess What to do if the requests receives a successful response.
	 * @param OnError What to do if the request receives an error response.
	 * @param OnComplete What to after either OnSuccess or OnError have finished executing.
	 * @param OutRequestContext The Request Context associated with this request -- used to query information about the request or to cancel it while it's in flight. 
	 */
	UFUNCTION(BlueprintCallable, BlueprintInternalUseOnly, Category="Beam|Backend|Realms", meta=(AutoCreateRefTerm="UserSlot,OnSuccess,OnError,OnComplete", BeamFlowStart))
	void PostLaunchMessage(FUserSlot UserSlot, UPostLaunchMessageRequest* Request, const FOnPostLaunchMessageSuccess& OnSuccess, const FOnPostLaunchMessageError& OnError, const FOnPostLaunchMessageComplete& OnComplete, FBeamRequestContext& OutRequestContext);

		
	/**
	 * @brief Makes an authenticated request to the Delete /basic/realms/launch-message endpoint of the Realms Service.
	 *
	 * @param UserSlot The authenticated UserSlot with the user making the request. 
	 * @param Request The Request UObject. All (de)serialized data the request data creates is tied to the lifecycle of this object.
	 * @param OnSuccess What to do if the requests receives a successful response.
	 * @param OnError What to do if the request receives an error response.
	 * @param OnComplete What to after either OnSuccess or OnError have finished executing.
	 * @param OutRequestContext The Request Context associated with this request -- used to query information about the request or to cancel it while it's in flight. 
	 */
	UFUNCTION(BlueprintCallable, BlueprintInternalUseOnly, Category="Beam|Backend|Realms", meta=(AutoCreateRefTerm="UserSlot,OnSuccess,OnError,OnComplete", BeamFlowStart))
	void DeleteLaunchMessage(FUserSlot UserSlot, UDeleteLaunchMessageRequest* Request, const FOnDeleteLaunchMessageSuccess& OnSuccess, const FOnDeleteLaunchMessageError& OnError, const FOnDeleteLaunchMessageComplete& OnComplete, FBeamRequestContext& OutRequestContext);

		
	/**
	 * @brief Makes an authenticated request to the Get /basic/realms/admin/customer endpoint of the Realms Service.
	 *
	 * @param UserSlot The authenticated UserSlot with the user making the request. 
	 * @param Request The Request UObject. All (de)serialized data the request data creates is tied to the lifecycle of this object.
	 * @param OnSuccess What to do if the requests receives a successful response.
	 * @param OnError What to do if the request receives an error response.
	 * @param OnComplete What to after either OnSuccess or OnError have finished executing.
	 * @param OutRequestContext The Request Context associated with this request -- used to query information about the request or to cancel it while it's in flight. 
	 */
	UFUNCTION(BlueprintCallable, BlueprintInternalUseOnly, Category="Beam|Backend|Realms", meta=(AutoCreateRefTerm="UserSlot,OnSuccess,OnError,OnComplete", BeamFlowStart))
	void GetAdminCustomer(FUserSlot UserSlot, UGetAdminCustomerRequest* Request, const FOnGetAdminCustomerSuccess& OnSuccess, const FOnGetAdminCustomerError& OnError, const FOnGetAdminCustomerComplete& OnComplete, FBeamRequestContext& OutRequestContext);

		
	/**
	 * @brief Makes an authenticated request to the Get /basic/realms/game endpoint of the Realms Service.
	 *
	 * @param UserSlot The authenticated UserSlot with the user making the request. 
	 * @param Request The Request UObject. All (de)serialized data the request data creates is tied to the lifecycle of this object.
	 * @param OnSuccess What to do if the requests receives a successful response.
	 * @param OnError What to do if the request receives an error response.
	 * @param OnComplete What to after either OnSuccess or OnError have finished executing.
	 * @param OutRequestContext The Request Context associated with this request -- used to query information about the request or to cancel it while it's in flight. 
	 */
	UFUNCTION(BlueprintCallable, BlueprintInternalUseOnly, Category="Beam|Backend|Realms", meta=(AutoCreateRefTerm="UserSlot,OnSuccess,OnError,OnComplete", BeamFlowStart))
	void GetGame(FUserSlot UserSlot, UGetGameRequest* Request, const FOnGetGameSuccess& OnSuccess, const FOnGetGameError& OnError, const FOnGetGameComplete& OnComplete, FBeamRequestContext& OutRequestContext);

		
	/**
	 * @brief Makes an authenticated request to the Post /basic/realms/game endpoint of the Realms Service.
	 *
	 * @param UserSlot The authenticated UserSlot with the user making the request. 
	 * @param Request The Request UObject. All (de)serialized data the request data creates is tied to the lifecycle of this object.
	 * @param OnSuccess What to do if the requests receives a successful response.
	 * @param OnError What to do if the request receives an error response.
	 * @param OnComplete What to after either OnSuccess or OnError have finished executing.
	 * @param OutRequestContext The Request Context associated with this request -- used to query information about the request or to cancel it while it's in flight. 
	 */
	UFUNCTION(BlueprintCallable, BlueprintInternalUseOnly, Category="Beam|Backend|Realms", meta=(AutoCreateRefTerm="UserSlot,OnSuccess,OnError,OnComplete", BeamFlowStart))
	void PostGame(FUserSlot UserSlot, UBasicRealmsPostGameRequest* Request, const FOnBasicRealmsPostGameSuccess& OnSuccess, const FOnBasicRealmsPostGameError& OnError, const FOnBasicRealmsPostGameComplete& OnComplete, FBeamRequestContext& OutRequestContext);

		
	/**
	 * @brief Makes an authenticated request to the Put /basic/realms/game endpoint of the Realms Service.
	 *
	 * @param UserSlot The authenticated UserSlot with the user making the request. 
	 * @param Request The Request UObject. All (de)serialized data the request data creates is tied to the lifecycle of this object.
	 * @param OnSuccess What to do if the requests receives a successful response.
	 * @param OnError What to do if the request receives an error response.
	 * @param OnComplete What to after either OnSuccess or OnError have finished executing.
	 * @param OutRequestContext The Request Context associated with this request -- used to query information about the request or to cancel it while it's in flight. 
	 */
	UFUNCTION(BlueprintCallable, BlueprintInternalUseOnly, Category="Beam|Backend|Realms", meta=(AutoCreateRefTerm="UserSlot,OnSuccess,OnError,OnComplete", BeamFlowStart))
	void PutGame(FUserSlot UserSlot, UPutGameRequest* Request, const FOnPutGameSuccess& OnSuccess, const FOnPutGameError& OnError, const FOnPutGameComplete& OnComplete, FBeamRequestContext& OutRequestContext);

		
	/**
	 * @brief Makes an authenticated request to the Get /basic/realms/project/promote endpoint of the Realms Service.
	 *
	 * @param UserSlot The authenticated UserSlot with the user making the request. 
	 * @param Request The Request UObject. All (de)serialized data the request data creates is tied to the lifecycle of this object.
	 * @param OnSuccess What to do if the requests receives a successful response.
	 * @param OnError What to do if the request receives an error response.
	 * @param OnComplete What to after either OnSuccess or OnError have finished executing.
	 * @param OutRequestContext The Request Context associated with this request -- used to query information about the request or to cancel it while it's in flight. 
	 */
	UFUNCTION(BlueprintCallable, BlueprintInternalUseOnly, Category="Beam|Backend|Realms", meta=(AutoCreateRefTerm="UserSlot,OnSuccess,OnError,OnComplete", BeamFlowStart))
	void GetProjectPromote(FUserSlot UserSlot, UGetProjectPromoteRequest* Request, const FOnGetProjectPromoteSuccess& OnSuccess, const FOnGetProjectPromoteError& OnError, const FOnGetProjectPromoteComplete& OnComplete, FBeamRequestContext& OutRequestContext);

		
	/**
	 * @brief Makes an authenticated request to the Post /basic/realms/project/promote endpoint of the Realms Service.
	 *
	 * @param UserSlot The authenticated UserSlot with the user making the request. 
	 * @param Request The Request UObject. All (de)serialized data the request data creates is tied to the lifecycle of this object.
	 * @param OnSuccess What to do if the requests receives a successful response.
	 * @param OnError What to do if the request receives an error response.
	 * @param OnComplete What to after either OnSuccess or OnError have finished executing.
	 * @param OutRequestContext The Request Context associated with this request -- used to query information about the request or to cancel it while it's in flight. 
	 */
	UFUNCTION(BlueprintCallable, BlueprintInternalUseOnly, Category="Beam|Backend|Realms", meta=(AutoCreateRefTerm="UserSlot,OnSuccess,OnError,OnComplete", BeamFlowStart))
	void PostProjectPromote(FUserSlot UserSlot, UPostProjectPromoteRequest* Request, const FOnPostProjectPromoteSuccess& OnSuccess, const FOnPostProjectPromoteError& OnError, const FOnPostProjectPromoteComplete& OnComplete, FBeamRequestContext& OutRequestContext);

		
	/**
	 * @brief Makes an authenticated request to the Get /basic/realms/promotion endpoint of the Realms Service.
	 *
	 * @param UserSlot The authenticated UserSlot with the user making the request. 
	 * @param Request The Request UObject. All (de)serialized data the request data creates is tied to the lifecycle of this object.
	 * @param OnSuccess What to do if the requests receives a successful response.
	 * @param OnError What to do if the request receives an error response.
	 * @param OnComplete What to after either OnSuccess or OnError have finished executing.
	 * @param OutRequestContext The Request Context associated with this request -- used to query information about the request or to cancel it while it's in flight. 
	 */
	UFUNCTION(BlueprintCallable, BlueprintInternalUseOnly, Category="Beam|Backend|Realms", meta=(AutoCreateRefTerm="UserSlot,OnSuccess,OnError,OnComplete", BeamFlowStart))
	void GetPromotion(FUserSlot UserSlot, UGetPromotionRequest* Request, const FOnGetPromotionSuccess& OnSuccess, const FOnGetPromotionError& OnError, const FOnGetPromotionComplete& OnComplete, FBeamRequestContext& OutRequestContext);

		
	/**
	 * @brief Makes an authenticated request to the Post /basic/realms/promotion endpoint of the Realms Service.
	 *
	 * @param UserSlot The authenticated UserSlot with the user making the request. 
	 * @param Request The Request UObject. All (de)serialized data the request data creates is tied to the lifecycle of this object.
	 * @param OnSuccess What to do if the requests receives a successful response.
	 * @param OnError What to do if the request receives an error response.
	 * @param OnComplete What to after either OnSuccess or OnError have finished executing.
	 * @param OutRequestContext The Request Context associated with this request -- used to query information about the request or to cancel it while it's in flight. 
	 */
	UFUNCTION(BlueprintCallable, BlueprintInternalUseOnly, Category="Beam|Backend|Realms", meta=(AutoCreateRefTerm="UserSlot,OnSuccess,OnError,OnComplete", BeamFlowStart))
	void PostPromotion(FUserSlot UserSlot, UPostPromotionRequest* Request, const FOnPostPromotionSuccess& OnSuccess, const FOnPostPromotionError& OnError, const FOnPostPromotionComplete& OnComplete, FBeamRequestContext& OutRequestContext);
	

	
	/**
	 * @brief Makes a request to the Get /basic/realms/customer/alias/available endpoint of the Realms Service.
	 *	 
	 * @param RetryConfig The retry config for this specific request. 
	 * @param Request The Request UObject. All (de)serialized data the request data creates is tied to the lifecycle of this object.
	 * @param OnSuccess What to do if the requests receives a successful response.
	 * @param OnError What to do if the request receives an error response.
	 * @param OnComplete What to after either OnSuccess or OnError have finished executing.
	 * @param OutRequestContext The Request Context -- used to query information about the request or to cancel it while it's in flight. 
	 */
	UFUNCTION(BlueprintCallable, BlueprintInternalUseOnly, Category="Beam|Backend|Realms", meta=(AutoCreateRefTerm="OnSuccess,OnError,OnComplete", BeamFlowStart))
	void GetCustomerAliasAvailableWithRetry(const FBeamRetryConfig& RetryConfig, UGetCustomerAliasAvailableRequest* Request, const FOnGetCustomerAliasAvailableSuccess& OnSuccess, const FOnGetCustomerAliasAvailableError& OnError, const FOnGetCustomerAliasAvailableComplete& OnComplete, FBeamRequestContext& OutRequestContext);
		
	/**
	 * @brief Makes a request to the Get /basic/realms/project endpoint of the Realms Service.
	 *	 
	 * @param RetryConfig The retry config for this specific request. 
	 * @param Request The Request UObject. All (de)serialized data the request data creates is tied to the lifecycle of this object.
	 * @param OnSuccess What to do if the requests receives a successful response.
	 * @param OnError What to do if the request receives an error response.
	 * @param OnComplete What to after either OnSuccess or OnError have finished executing.
	 * @param OutRequestContext The Request Context -- used to query information about the request or to cancel it while it's in flight. 
	 */
	UFUNCTION(BlueprintCallable, BlueprintInternalUseOnly, Category="Beam|Backend|Realms", meta=(AutoCreateRefTerm="OnSuccess,OnError,OnComplete", BeamFlowStart))
	void GetProjectWithRetry(const FBeamRetryConfig& RetryConfig, UGetProjectRequest* Request, const FOnGetProjectSuccess& OnSuccess, const FOnGetProjectError& OnError, const FOnGetProjectComplete& OnComplete, FBeamRequestContext& OutRequestContext);
		
	/**
	 * @brief Makes a request to the Post /basic/realms/customer endpoint of the Realms Service.
	 *	 
	 * @param RetryConfig The retry config for this specific request. 
	 * @param Request The Request UObject. All (de)serialized data the request data creates is tied to the lifecycle of this object.
	 * @param OnSuccess What to do if the requests receives a successful response.
	 * @param OnError What to do if the request receives an error response.
	 * @param OnComplete What to after either OnSuccess or OnError have finished executing.
	 * @param OutRequestContext The Request Context -- used to query information about the request or to cancel it while it's in flight. 
	 */
	UFUNCTION(BlueprintCallable, BlueprintInternalUseOnly, Category="Beam|Backend|Realms", meta=(AutoCreateRefTerm="OnSuccess,OnError,OnComplete", BeamFlowStart))
	void PostCustomerWithRetry(const FBeamRetryConfig& RetryConfig, UPostCustomerRequest* Request, const FOnPostCustomerSuccess& OnSuccess, const FOnPostCustomerError& OnError, const FOnPostCustomerComplete& OnComplete, FBeamRequestContext& OutRequestContext);
		
	/**
	 * @brief Makes a request to the Get /basic/realms/is-customer endpoint of the Realms Service.
	 *	 
	 * @param RetryConfig The retry config for this specific request. 
	 * @param Request The Request UObject. All (de)serialized data the request data creates is tied to the lifecycle of this object.
	 * @param OnSuccess What to do if the requests receives a successful response.
	 * @param OnError What to do if the request receives an error response.
	 * @param OnComplete What to after either OnSuccess or OnError have finished executing.
	 * @param OutRequestContext The Request Context -- used to query information about the request or to cancel it while it's in flight. 
	 */
	UFUNCTION(BlueprintCallable, BlueprintInternalUseOnly, Category="Beam|Backend|Realms", meta=(AutoCreateRefTerm="OnSuccess,OnError,OnComplete", BeamFlowStart))
	void GetIsCustomerWithRetry(const FBeamRetryConfig& RetryConfig, UGetIsCustomerRequest* Request, const FOnGetIsCustomerSuccess& OnSuccess, const FOnGetIsCustomerError& OnError, const FOnGetIsCustomerComplete& OnComplete, FBeamRequestContext& OutRequestContext);
		
	/**
	 * @brief Makes a request to the Get /basic/realms/customers endpoint of the Realms Service.
	 *	 
	 * @param RetryConfig The retry config for this specific request. 
	 * @param Request The Request UObject. All (de)serialized data the request data creates is tied to the lifecycle of this object.
	 * @param OnSuccess What to do if the requests receives a successful response.
	 * @param OnError What to do if the request receives an error response.
	 * @param OnComplete What to after either OnSuccess or OnError have finished executing.
	 * @param OutRequestContext The Request Context -- used to query information about the request or to cancel it while it's in flight. 
	 */
	UFUNCTION(BlueprintCallable, BlueprintInternalUseOnly, Category="Beam|Backend|Realms", meta=(AutoCreateRefTerm="OnSuccess,OnError,OnComplete", BeamFlowStart))
	void GetCustomersWithRetry(const FBeamRetryConfig& RetryConfig, UGetCustomersRequest* Request, const FOnGetCustomersSuccess& OnSuccess, const FOnGetCustomersError& OnError, const FOnGetCustomersComplete& OnComplete, FBeamRequestContext& OutRequestContext);

	
	/**
	 * @brief Makes an authenticated request to the Post /basic/realms/project/beamable endpoint of the Realms Service.
	 *
	 * @param UserSlot The authenticated UserSlot with the user making the request.
	 * @param RetryConfig The retry config for this specific request. 
	 * @param Request The Request UObject. All (de)serialized data the request data creates is tied to the lifecycle of this object.
	 * @param OnSuccess What to do if the requests receives a successful response.
	 * @param OnError What to do if the request receives an error response.
	 * @param OnComplete What to after either OnSuccess or OnError have finished executing.
	 * @param OutRequestContext The Request Context -- used to query information about the request or to cancel it while it's in flight. 
	 */
	UFUNCTION(BlueprintCallable, BlueprintInternalUseOnly, Category="Beam|Backend|Realms", meta=(AutoCreateRefTerm="UserSlot,OnSuccess,OnError,OnComplete", BeamFlowStart))
	void PostProjectBeamableWithRetry(FUserSlot UserSlot, const FBeamRetryConfig& RetryConfig, UPostProjectBeamableRequest* Request, const FOnPostProjectBeamableSuccess& OnSuccess, const FOnPostProjectBeamableError& OnError, const FOnPostProjectBeamableComplete& OnComplete, FBeamRequestContext& OutRequestContext);
		
	/**
	 * @brief Makes an authenticated request to the Post /basic/realms/project endpoint of the Realms Service.
	 *
	 * @param UserSlot The authenticated UserSlot with the user making the request.
	 * @param RetryConfig The retry config for this specific request. 
	 * @param Request The Request UObject. All (de)serialized data the request data creates is tied to the lifecycle of this object.
	 * @param OnSuccess What to do if the requests receives a successful response.
	 * @param OnError What to do if the request receives an error response.
	 * @param OnComplete What to after either OnSuccess or OnError have finished executing.
	 * @param OutRequestContext The Request Context -- used to query information about the request or to cancel it while it's in flight. 
	 */
	UFUNCTION(BlueprintCallable, BlueprintInternalUseOnly, Category="Beam|Backend|Realms", meta=(AutoCreateRefTerm="UserSlot,OnSuccess,OnError,OnComplete", BeamFlowStart))
	void PostProjectWithRetry(FUserSlot UserSlot, const FBeamRetryConfig& RetryConfig, UPostProjectRequest* Request, const FOnPostProjectSuccess& OnSuccess, const FOnPostProjectError& OnError, const FOnPostProjectComplete& OnComplete, FBeamRequestContext& OutRequestContext);
		
	/**
	 * @brief Makes an authenticated request to the Put /basic/realms/project endpoint of the Realms Service.
	 *
	 * @param UserSlot The authenticated UserSlot with the user making the request.
	 * @param RetryConfig The retry config for this specific request. 
	 * @param Request The Request UObject. All (de)serialized data the request data creates is tied to the lifecycle of this object.
	 * @param OnSuccess What to do if the requests receives a successful response.
	 * @param OnError What to do if the request receives an error response.
	 * @param OnComplete What to after either OnSuccess or OnError have finished executing.
	 * @param OutRequestContext The Request Context -- used to query information about the request or to cancel it while it's in flight. 
	 */
	UFUNCTION(BlueprintCallable, BlueprintInternalUseOnly, Category="Beam|Backend|Realms", meta=(AutoCreateRefTerm="UserSlot,OnSuccess,OnError,OnComplete", BeamFlowStart))
	void PutProjectWithRetry(FUserSlot UserSlot, const FBeamRetryConfig& RetryConfig, UPutProjectRequest* Request, const FOnPutProjectSuccess& OnSuccess, const FOnPutProjectError& OnError, const FOnPutProjectComplete& OnComplete, FBeamRequestContext& OutRequestContext);
		
	/**
	 * @brief Makes an authenticated request to the Delete /basic/realms/project endpoint of the Realms Service.
	 *
	 * @param UserSlot The authenticated UserSlot with the user making the request.
	 * @param RetryConfig The retry config for this specific request. 
	 * @param Request The Request UObject. All (de)serialized data the request data creates is tied to the lifecycle of this object.
	 * @param OnSuccess What to do if the requests receives a successful response.
	 * @param OnError What to do if the request receives an error response.
	 * @param OnComplete What to after either OnSuccess or OnError have finished executing.
	 * @param OutRequestContext The Request Context -- used to query information about the request or to cancel it while it's in flight. 
	 */
	UFUNCTION(BlueprintCallable, BlueprintInternalUseOnly, Category="Beam|Backend|Realms", meta=(AutoCreateRefTerm="UserSlot,OnSuccess,OnError,OnComplete", BeamFlowStart))
	void DeleteProjectWithRetry(FUserSlot UserSlot, const FBeamRetryConfig& RetryConfig, UDeleteProjectRequest* Request, const FOnDeleteProjectSuccess& OnSuccess, const FOnDeleteProjectError& OnError, const FOnDeleteProjectComplete& OnComplete, FBeamRequestContext& OutRequestContext);
		
	/**
	 * @brief Makes an authenticated request to the Get /basic/realms/games endpoint of the Realms Service.
	 *
	 * @param UserSlot The authenticated UserSlot with the user making the request.
	 * @param RetryConfig The retry config for this specific request. 
	 * @param Request The Request UObject. All (de)serialized data the request data creates is tied to the lifecycle of this object.
	 * @param OnSuccess What to do if the requests receives a successful response.
	 * @param OnError What to do if the request receives an error response.
	 * @param OnComplete What to after either OnSuccess or OnError have finished executing.
	 * @param OutRequestContext The Request Context -- used to query information about the request or to cancel it while it's in flight. 
	 */
	UFUNCTION(BlueprintCallable, BlueprintInternalUseOnly, Category="Beam|Backend|Realms", meta=(AutoCreateRefTerm="UserSlot,OnSuccess,OnError,OnComplete", BeamFlowStart))
	void GetGamesWithRetry(FUserSlot UserSlot, const FBeamRetryConfig& RetryConfig, UGetGamesRequest* Request, const FOnGetGamesSuccess& OnSuccess, const FOnGetGamesError& OnError, const FOnGetGamesComplete& OnComplete, FBeamRequestContext& OutRequestContext);
		
	/**
	 * @brief Makes an authenticated request to the Get /basic/realms/config endpoint of the Realms Service.
	 *
	 * @param UserSlot The authenticated UserSlot with the user making the request.
	 * @param RetryConfig The retry config for this specific request. 
	 * @param Request The Request UObject. All (de)serialized data the request data creates is tied to the lifecycle of this object.
	 * @param OnSuccess What to do if the requests receives a successful response.
	 * @param OnError What to do if the request receives an error response.
	 * @param OnComplete What to after either OnSuccess or OnError have finished executing.
	 * @param OutRequestContext The Request Context -- used to query information about the request or to cancel it while it's in flight. 
	 */
	UFUNCTION(BlueprintCallable, BlueprintInternalUseOnly, Category="Beam|Backend|Realms", meta=(AutoCreateRefTerm="UserSlot,OnSuccess,OnError,OnComplete", BeamFlowStart))
	void GetConfigWithRetry(FUserSlot UserSlot, const FBeamRetryConfig& RetryConfig, UGetConfigRequest* Request, const FOnGetConfigSuccess& OnSuccess, const FOnGetConfigError& OnError, const FOnGetConfigComplete& OnComplete, FBeamRequestContext& OutRequestContext);
		
	/**
	 * @brief Makes an authenticated request to the Put /basic/realms/config endpoint of the Realms Service.
	 *
	 * @param UserSlot The authenticated UserSlot with the user making the request.
	 * @param RetryConfig The retry config for this specific request. 
	 * @param Request The Request UObject. All (de)serialized data the request data creates is tied to the lifecycle of this object.
	 * @param OnSuccess What to do if the requests receives a successful response.
	 * @param OnError What to do if the request receives an error response.
	 * @param OnComplete What to after either OnSuccess or OnError have finished executing.
	 * @param OutRequestContext The Request Context -- used to query information about the request or to cancel it while it's in flight. 
	 */
	UFUNCTION(BlueprintCallable, BlueprintInternalUseOnly, Category="Beam|Backend|Realms", meta=(AutoCreateRefTerm="UserSlot,OnSuccess,OnError,OnComplete", BeamFlowStart))
	void PutConfigWithRetry(FUserSlot UserSlot, const FBeamRetryConfig& RetryConfig, UPutConfigRequest* Request, const FOnPutConfigSuccess& OnSuccess, const FOnPutConfigError& OnError, const FOnPutConfigComplete& OnComplete, FBeamRequestContext& OutRequestContext);
		
	/**
	 * @brief Makes an authenticated request to the Put /basic/realms/project/rename endpoint of the Realms Service.
	 *
	 * @param UserSlot The authenticated UserSlot with the user making the request.
	 * @param RetryConfig The retry config for this specific request. 
	 * @param Request The Request UObject. All (de)serialized data the request data creates is tied to the lifecycle of this object.
	 * @param OnSuccess What to do if the requests receives a successful response.
	 * @param OnError What to do if the request receives an error response.
	 * @param OnComplete What to after either OnSuccess or OnError have finished executing.
	 * @param OutRequestContext The Request Context -- used to query information about the request or to cancel it while it's in flight. 
	 */
	UFUNCTION(BlueprintCallable, BlueprintInternalUseOnly, Category="Beam|Backend|Realms", meta=(AutoCreateRefTerm="UserSlot,OnSuccess,OnError,OnComplete", BeamFlowStart))
	void PutProjectRenameWithRetry(FUserSlot UserSlot, const FBeamRetryConfig& RetryConfig, UPutProjectRenameRequest* Request, const FOnPutProjectRenameSuccess& OnSuccess, const FOnPutProjectRenameError& OnError, const FOnPutProjectRenameComplete& OnComplete, FBeamRequestContext& OutRequestContext);
		
	/**
	 * @brief Makes an authenticated request to the Get /basic/realms/plans endpoint of the Realms Service.
	 *
	 * @param UserSlot The authenticated UserSlot with the user making the request.
	 * @param RetryConfig The retry config for this specific request. 
	 * @param Request The Request UObject. All (de)serialized data the request data creates is tied to the lifecycle of this object.
	 * @param OnSuccess What to do if the requests receives a successful response.
	 * @param OnError What to do if the request receives an error response.
	 * @param OnComplete What to after either OnSuccess or OnError have finished executing.
	 * @param OutRequestContext The Request Context -- used to query information about the request or to cancel it while it's in flight. 
	 */
	UFUNCTION(BlueprintCallable, BlueprintInternalUseOnly, Category="Beam|Backend|Realms", meta=(AutoCreateRefTerm="UserSlot,OnSuccess,OnError,OnComplete", BeamFlowStart))
	void GetPlansWithRetry(FUserSlot UserSlot, const FBeamRetryConfig& RetryConfig, UGetPlansRequest* Request, const FOnGetPlansSuccess& OnSuccess, const FOnGetPlansError& OnError, const FOnGetPlansComplete& OnComplete, FBeamRequestContext& OutRequestContext);
		
	/**
	 * @brief Makes an authenticated request to the Post /basic/realms/plans endpoint of the Realms Service.
	 *
	 * @param UserSlot The authenticated UserSlot with the user making the request.
	 * @param RetryConfig The retry config for this specific request. 
	 * @param Request The Request UObject. All (de)serialized data the request data creates is tied to the lifecycle of this object.
	 * @param OnSuccess What to do if the requests receives a successful response.
	 * @param OnError What to do if the request receives an error response.
	 * @param OnComplete What to after either OnSuccess or OnError have finished executing.
	 * @param OutRequestContext The Request Context -- used to query information about the request or to cancel it while it's in flight. 
	 */
	UFUNCTION(BlueprintCallable, BlueprintInternalUseOnly, Category="Beam|Backend|Realms", meta=(AutoCreateRefTerm="UserSlot,OnSuccess,OnError,OnComplete", BeamFlowStart))
	void PostPlansWithRetry(FUserSlot UserSlot, const FBeamRetryConfig& RetryConfig, UPostPlansRequest* Request, const FOnPostPlansSuccess& OnSuccess, const FOnPostPlansError& OnError, const FOnPostPlansComplete& OnComplete, FBeamRequestContext& OutRequestContext);
		
	/**
	 * @brief Makes an authenticated request to the Get /basic/realms/customer endpoint of the Realms Service.
	 *
	 * @param UserSlot The authenticated UserSlot with the user making the request.
	 * @param RetryConfig The retry config for this specific request. 
	 * @param Request The Request UObject. All (de)serialized data the request data creates is tied to the lifecycle of this object.
	 * @param OnSuccess What to do if the requests receives a successful response.
	 * @param OnError What to do if the request receives an error response.
	 * @param OnComplete What to after either OnSuccess or OnError have finished executing.
	 * @param OutRequestContext The Request Context -- used to query information about the request or to cancel it while it's in flight. 
	 */
	UFUNCTION(BlueprintCallable, BlueprintInternalUseOnly, Category="Beam|Backend|Realms", meta=(AutoCreateRefTerm="UserSlot,OnSuccess,OnError,OnComplete", BeamFlowStart))
	void GetCustomerWithRetry(FUserSlot UserSlot, const FBeamRetryConfig& RetryConfig, UGetCustomerRequest* Request, const FOnGetCustomerSuccess& OnSuccess, const FOnGetCustomerError& OnError, const FOnGetCustomerComplete& OnComplete, FBeamRequestContext& OutRequestContext);
		
	/**
	 * @brief Makes an authenticated request to the Get /basic/realms/launch-message endpoint of the Realms Service.
	 *
	 * @param UserSlot The authenticated UserSlot with the user making the request.
	 * @param RetryConfig The retry config for this specific request. 
	 * @param Request The Request UObject. All (de)serialized data the request data creates is tied to the lifecycle of this object.
	 * @param OnSuccess What to do if the requests receives a successful response.
	 * @param OnError What to do if the request receives an error response.
	 * @param OnComplete What to after either OnSuccess or OnError have finished executing.
	 * @param OutRequestContext The Request Context -- used to query information about the request or to cancel it while it's in flight. 
	 */
	UFUNCTION(BlueprintCallable, BlueprintInternalUseOnly, Category="Beam|Backend|Realms", meta=(AutoCreateRefTerm="UserSlot,OnSuccess,OnError,OnComplete", BeamFlowStart))
	void GetLaunchMessageWithRetry(FUserSlot UserSlot, const FBeamRetryConfig& RetryConfig, UGetLaunchMessageRequest* Request, const FOnGetLaunchMessageSuccess& OnSuccess, const FOnGetLaunchMessageError& OnError, const FOnGetLaunchMessageComplete& OnComplete, FBeamRequestContext& OutRequestContext);
		
	/**
	 * @brief Makes an authenticated request to the Post /basic/realms/launch-message endpoint of the Realms Service.
	 *
	 * @param UserSlot The authenticated UserSlot with the user making the request.
	 * @param RetryConfig The retry config for this specific request. 
	 * @param Request The Request UObject. All (de)serialized data the request data creates is tied to the lifecycle of this object.
	 * @param OnSuccess What to do if the requests receives a successful response.
	 * @param OnError What to do if the request receives an error response.
	 * @param OnComplete What to after either OnSuccess or OnError have finished executing.
	 * @param OutRequestContext The Request Context -- used to query information about the request or to cancel it while it's in flight. 
	 */
	UFUNCTION(BlueprintCallable, BlueprintInternalUseOnly, Category="Beam|Backend|Realms", meta=(AutoCreateRefTerm="UserSlot,OnSuccess,OnError,OnComplete", BeamFlowStart))
	void PostLaunchMessageWithRetry(FUserSlot UserSlot, const FBeamRetryConfig& RetryConfig, UPostLaunchMessageRequest* Request, const FOnPostLaunchMessageSuccess& OnSuccess, const FOnPostLaunchMessageError& OnError, const FOnPostLaunchMessageComplete& OnComplete, FBeamRequestContext& OutRequestContext);
		
	/**
	 * @brief Makes an authenticated request to the Delete /basic/realms/launch-message endpoint of the Realms Service.
	 *
	 * @param UserSlot The authenticated UserSlot with the user making the request.
	 * @param RetryConfig The retry config for this specific request. 
	 * @param Request The Request UObject. All (de)serialized data the request data creates is tied to the lifecycle of this object.
	 * @param OnSuccess What to do if the requests receives a successful response.
	 * @param OnError What to do if the request receives an error response.
	 * @param OnComplete What to after either OnSuccess or OnError have finished executing.
	 * @param OutRequestContext The Request Context -- used to query information about the request or to cancel it while it's in flight. 
	 */
	UFUNCTION(BlueprintCallable, BlueprintInternalUseOnly, Category="Beam|Backend|Realms", meta=(AutoCreateRefTerm="UserSlot,OnSuccess,OnError,OnComplete", BeamFlowStart))
	void DeleteLaunchMessageWithRetry(FUserSlot UserSlot, const FBeamRetryConfig& RetryConfig, UDeleteLaunchMessageRequest* Request, const FOnDeleteLaunchMessageSuccess& OnSuccess, const FOnDeleteLaunchMessageError& OnError, const FOnDeleteLaunchMessageComplete& OnComplete, FBeamRequestContext& OutRequestContext);
		
	/**
	 * @brief Makes an authenticated request to the Get /basic/realms/admin/customer endpoint of the Realms Service.
	 *
	 * @param UserSlot The authenticated UserSlot with the user making the request.
	 * @param RetryConfig The retry config for this specific request. 
	 * @param Request The Request UObject. All (de)serialized data the request data creates is tied to the lifecycle of this object.
	 * @param OnSuccess What to do if the requests receives a successful response.
	 * @param OnError What to do if the request receives an error response.
	 * @param OnComplete What to after either OnSuccess or OnError have finished executing.
	 * @param OutRequestContext The Request Context -- used to query information about the request or to cancel it while it's in flight. 
	 */
	UFUNCTION(BlueprintCallable, BlueprintInternalUseOnly, Category="Beam|Backend|Realms", meta=(AutoCreateRefTerm="UserSlot,OnSuccess,OnError,OnComplete", BeamFlowStart))
	void GetAdminCustomerWithRetry(FUserSlot UserSlot, const FBeamRetryConfig& RetryConfig, UGetAdminCustomerRequest* Request, const FOnGetAdminCustomerSuccess& OnSuccess, const FOnGetAdminCustomerError& OnError, const FOnGetAdminCustomerComplete& OnComplete, FBeamRequestContext& OutRequestContext);
		
	/**
	 * @brief Makes an authenticated request to the Get /basic/realms/game endpoint of the Realms Service.
	 *
	 * @param UserSlot The authenticated UserSlot with the user making the request.
	 * @param RetryConfig The retry config for this specific request. 
	 * @param Request The Request UObject. All (de)serialized data the request data creates is tied to the lifecycle of this object.
	 * @param OnSuccess What to do if the requests receives a successful response.
	 * @param OnError What to do if the request receives an error response.
	 * @param OnComplete What to after either OnSuccess or OnError have finished executing.
	 * @param OutRequestContext The Request Context -- used to query information about the request or to cancel it while it's in flight. 
	 */
	UFUNCTION(BlueprintCallable, BlueprintInternalUseOnly, Category="Beam|Backend|Realms", meta=(AutoCreateRefTerm="UserSlot,OnSuccess,OnError,OnComplete", BeamFlowStart))
	void GetGameWithRetry(FUserSlot UserSlot, const FBeamRetryConfig& RetryConfig, UGetGameRequest* Request, const FOnGetGameSuccess& OnSuccess, const FOnGetGameError& OnError, const FOnGetGameComplete& OnComplete, FBeamRequestContext& OutRequestContext);
		
	/**
	 * @brief Makes an authenticated request to the Post /basic/realms/game endpoint of the Realms Service.
	 *
	 * @param UserSlot The authenticated UserSlot with the user making the request.
	 * @param RetryConfig The retry config for this specific request. 
	 * @param Request The Request UObject. All (de)serialized data the request data creates is tied to the lifecycle of this object.
	 * @param OnSuccess What to do if the requests receives a successful response.
	 * @param OnError What to do if the request receives an error response.
	 * @param OnComplete What to after either OnSuccess or OnError have finished executing.
	 * @param OutRequestContext The Request Context -- used to query information about the request or to cancel it while it's in flight. 
	 */
	UFUNCTION(BlueprintCallable, BlueprintInternalUseOnly, Category="Beam|Backend|Realms", meta=(AutoCreateRefTerm="UserSlot,OnSuccess,OnError,OnComplete", BeamFlowStart))
	void PostGameWithRetry(FUserSlot UserSlot, const FBeamRetryConfig& RetryConfig, UBasicRealmsPostGameRequest* Request, const FOnBasicRealmsPostGameSuccess& OnSuccess, const FOnBasicRealmsPostGameError& OnError, const FOnBasicRealmsPostGameComplete& OnComplete, FBeamRequestContext& OutRequestContext);
		
	/**
	 * @brief Makes an authenticated request to the Put /basic/realms/game endpoint of the Realms Service.
	 *
	 * @param UserSlot The authenticated UserSlot with the user making the request.
	 * @param RetryConfig The retry config for this specific request. 
	 * @param Request The Request UObject. All (de)serialized data the request data creates is tied to the lifecycle of this object.
	 * @param OnSuccess What to do if the requests receives a successful response.
	 * @param OnError What to do if the request receives an error response.
	 * @param OnComplete What to after either OnSuccess or OnError have finished executing.
	 * @param OutRequestContext The Request Context -- used to query information about the request or to cancel it while it's in flight. 
	 */
	UFUNCTION(BlueprintCallable, BlueprintInternalUseOnly, Category="Beam|Backend|Realms", meta=(AutoCreateRefTerm="UserSlot,OnSuccess,OnError,OnComplete", BeamFlowStart))
	void PutGameWithRetry(FUserSlot UserSlot, const FBeamRetryConfig& RetryConfig, UPutGameRequest* Request, const FOnPutGameSuccess& OnSuccess, const FOnPutGameError& OnError, const FOnPutGameComplete& OnComplete, FBeamRequestContext& OutRequestContext);
		
	/**
	 * @brief Makes an authenticated request to the Get /basic/realms/project/promote endpoint of the Realms Service.
	 *
	 * @param UserSlot The authenticated UserSlot with the user making the request.
	 * @param RetryConfig The retry config for this specific request. 
	 * @param Request The Request UObject. All (de)serialized data the request data creates is tied to the lifecycle of this object.
	 * @param OnSuccess What to do if the requests receives a successful response.
	 * @param OnError What to do if the request receives an error response.
	 * @param OnComplete What to after either OnSuccess or OnError have finished executing.
	 * @param OutRequestContext The Request Context -- used to query information about the request or to cancel it while it's in flight. 
	 */
	UFUNCTION(BlueprintCallable, BlueprintInternalUseOnly, Category="Beam|Backend|Realms", meta=(AutoCreateRefTerm="UserSlot,OnSuccess,OnError,OnComplete", BeamFlowStart))
	void GetProjectPromoteWithRetry(FUserSlot UserSlot, const FBeamRetryConfig& RetryConfig, UGetProjectPromoteRequest* Request, const FOnGetProjectPromoteSuccess& OnSuccess, const FOnGetProjectPromoteError& OnError, const FOnGetProjectPromoteComplete& OnComplete, FBeamRequestContext& OutRequestContext);
		
	/**
	 * @brief Makes an authenticated request to the Post /basic/realms/project/promote endpoint of the Realms Service.
	 *
	 * @param UserSlot The authenticated UserSlot with the user making the request.
	 * @param RetryConfig The retry config for this specific request. 
	 * @param Request The Request UObject. All (de)serialized data the request data creates is tied to the lifecycle of this object.
	 * @param OnSuccess What to do if the requests receives a successful response.
	 * @param OnError What to do if the request receives an error response.
	 * @param OnComplete What to after either OnSuccess or OnError have finished executing.
	 * @param OutRequestContext The Request Context -- used to query information about the request or to cancel it while it's in flight. 
	 */
	UFUNCTION(BlueprintCallable, BlueprintInternalUseOnly, Category="Beam|Backend|Realms", meta=(AutoCreateRefTerm="UserSlot,OnSuccess,OnError,OnComplete", BeamFlowStart))
	void PostProjectPromoteWithRetry(FUserSlot UserSlot, const FBeamRetryConfig& RetryConfig, UPostProjectPromoteRequest* Request, const FOnPostProjectPromoteSuccess& OnSuccess, const FOnPostProjectPromoteError& OnError, const FOnPostProjectPromoteComplete& OnComplete, FBeamRequestContext& OutRequestContext);
		
	/**
	 * @brief Makes an authenticated request to the Get /basic/realms/promotion endpoint of the Realms Service.
	 *
	 * @param UserSlot The authenticated UserSlot with the user making the request.
	 * @param RetryConfig The retry config for this specific request. 
	 * @param Request The Request UObject. All (de)serialized data the request data creates is tied to the lifecycle of this object.
	 * @param OnSuccess What to do if the requests receives a successful response.
	 * @param OnError What to do if the request receives an error response.
	 * @param OnComplete What to after either OnSuccess or OnError have finished executing.
	 * @param OutRequestContext The Request Context -- used to query information about the request or to cancel it while it's in flight. 
	 */
	UFUNCTION(BlueprintCallable, BlueprintInternalUseOnly, Category="Beam|Backend|Realms", meta=(AutoCreateRefTerm="UserSlot,OnSuccess,OnError,OnComplete", BeamFlowStart))
	void GetPromotionWithRetry(FUserSlot UserSlot, const FBeamRetryConfig& RetryConfig, UGetPromotionRequest* Request, const FOnGetPromotionSuccess& OnSuccess, const FOnGetPromotionError& OnError, const FOnGetPromotionComplete& OnComplete, FBeamRequestContext& OutRequestContext);
		
	/**
	 * @brief Makes an authenticated request to the Post /basic/realms/promotion endpoint of the Realms Service.
	 *
	 * @param UserSlot The authenticated UserSlot with the user making the request.
	 * @param RetryConfig The retry config for this specific request. 
	 * @param Request The Request UObject. All (de)serialized data the request data creates is tied to the lifecycle of this object.
	 * @param OnSuccess What to do if the requests receives a successful response.
	 * @param OnError What to do if the request receives an error response.
	 * @param OnComplete What to after either OnSuccess or OnError have finished executing.
	 * @param OutRequestContext The Request Context -- used to query information about the request or to cancel it while it's in flight. 
	 */
	UFUNCTION(BlueprintCallable, BlueprintInternalUseOnly, Category="Beam|Backend|Realms", meta=(AutoCreateRefTerm="UserSlot,OnSuccess,OnError,OnComplete", BeamFlowStart))
	void PostPromotionWithRetry(FUserSlot UserSlot, const FBeamRetryConfig& RetryConfig, UPostPromotionRequest* Request, const FOnPostPromotionSuccess& OnSuccess, const FOnPostPromotionError& OnError, const FOnPostPromotionComplete& OnComplete, FBeamRequestContext& OutRequestContext);
};
