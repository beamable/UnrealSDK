

#pragma once

#include "CoreMinimal.h"
#include "BeamBackend.h"

#include "Accounts/GetGetPersonallyIdentifiableInformationRequest.h"
#include "Accounts/GetAvailableThirdPartyRequest.h"
#include "Accounts/PostPasswordUpdateInitRequest.h"
#include "Accounts/GetAvailableDeviceIdRequest.h"
#include "Accounts/GetAvailableRequest.h"
#include "Accounts/PostPasswordUpdateConfirmRequest.h"
#include "Accounts/GetAvailableRolesRequest.h"
#include "Accounts/DeleteMeDeviceRequest.h"
#include "Accounts/BasicAccountsGetMeRequest.h"
#include "Accounts/PutMeRequest.h"
#include "Accounts/DeleteMeThirdPartyRequest.h"
#include "Accounts/BasicAccountsGetSearchRequest.h"
#include "Accounts/PostEmailUpdateInitRequest.h"
#include "Accounts/PostEmailUpdateConfirmRequest.h"
#include "Accounts/PostAdminAdminUserRequest.h"
#include "Accounts/BasicAccountsPostRegisterRequest.h"
#include "Accounts/GetAdminMeRequest.h"
#include "Accounts/GetAdminAdminUsersRequest.h"
#include "Accounts/GetFindRequest.h"
#include "Accounts/PutAdminEmailRequest.h"
#include "Accounts/GetRoleReportRequest.h"
#include "Accounts/ObjectAccountsPutRoleRequest.h"
#include "Accounts/DeleteRoleRequest.h"
#include "Accounts/PutAdminScopeRequest.h"
#include "Accounts/DeleteAdminScopeRequest.h"
#include "Accounts/PutAdminThirdPartyRequest.h"
#include "Accounts/DeleteAdminThirdPartyRequest.h"
#include "Accounts/PutAccountsRequest.h"
#include "Accounts/DeleteAdminForgetRequest.h"

#include "BeamAccountsApi.generated.h"


/**
 * Subsystem containing request calls for the Accounts service.
 */
UCLASS(BlueprintType)
class BEAMABLECORE_API UBeamAccountsApi : public UEngineSubsystem
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
	void BP_GetGetPersonallyIdentifiableInformationImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, FBeamConnectivity& ConnectivityStatus, UGetGetPersonallyIdentifiableInformationRequest* RequestData,
	                                const FOnGetGetPersonallyIdentifiableInformationSuccess& OnSuccess, const FOnGetGetPersonallyIdentifiableInformationError& OnError, const FOnGetGetPersonallyIdentifiableInformationComplete& OnComplete,
	                                int64& OutRequestId) const;
	/**
	 * @brief Overload version for binding lambdas when in C++ land. Prefer the BP version whenever possible, this is here mostly for quick experimentation purposes.	 
	 */
	void CPP_GetGetPersonallyIdentifiableInformationImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, FBeamConnectivity& ConnectivityStatus, UGetGetPersonallyIdentifiableInformationRequest* RequestData,
	                                 const FOnGetGetPersonallyIdentifiableInformationFullResponse& Handler) const;

		
	/**
	 * @brief Private implementation that all overloaded BP UFunctions call.	  
	 */
	void BP_GetAvailableThirdPartyImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, FBeamConnectivity& ConnectivityStatus, UGetAvailableThirdPartyRequest* RequestData,
	                                const FOnGetAvailableThirdPartySuccess& OnSuccess, const FOnGetAvailableThirdPartyError& OnError, const FOnGetAvailableThirdPartyComplete& OnComplete,
	                                int64& OutRequestId) const;
	/**
	 * @brief Overload version for binding lambdas when in C++ land. Prefer the BP version whenever possible, this is here mostly for quick experimentation purposes.	 
	 */
	void CPP_GetAvailableThirdPartyImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, FBeamConnectivity& ConnectivityStatus, UGetAvailableThirdPartyRequest* RequestData,
	                                 const FOnGetAvailableThirdPartyFullResponse& Handler) const;

		
	/**
	 * @brief Private implementation that all overloaded BP UFunctions call.	  
	 */
	void BP_PostPasswordUpdateInitImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, FBeamConnectivity& ConnectivityStatus, UPostPasswordUpdateInitRequest* RequestData,
	                                const FOnPostPasswordUpdateInitSuccess& OnSuccess, const FOnPostPasswordUpdateInitError& OnError, const FOnPostPasswordUpdateInitComplete& OnComplete,
	                                int64& OutRequestId) const;
	/**
	 * @brief Overload version for binding lambdas when in C++ land. Prefer the BP version whenever possible, this is here mostly for quick experimentation purposes.	 
	 */
	void CPP_PostPasswordUpdateInitImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, FBeamConnectivity& ConnectivityStatus, UPostPasswordUpdateInitRequest* RequestData,
	                                 const FOnPostPasswordUpdateInitFullResponse& Handler) const;

		
	/**
	 * @brief Private implementation that all overloaded BP UFunctions call.	  
	 */
	void BP_GetAvailableDeviceIdImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, FBeamConnectivity& ConnectivityStatus, UGetAvailableDeviceIdRequest* RequestData,
	                                const FOnGetAvailableDeviceIdSuccess& OnSuccess, const FOnGetAvailableDeviceIdError& OnError, const FOnGetAvailableDeviceIdComplete& OnComplete,
	                                int64& OutRequestId) const;
	/**
	 * @brief Overload version for binding lambdas when in C++ land. Prefer the BP version whenever possible, this is here mostly for quick experimentation purposes.	 
	 */
	void CPP_GetAvailableDeviceIdImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, FBeamConnectivity& ConnectivityStatus, UGetAvailableDeviceIdRequest* RequestData,
	                                 const FOnGetAvailableDeviceIdFullResponse& Handler) const;

		
	/**
	 * @brief Private implementation that all overloaded BP UFunctions call.	  
	 */
	void BP_GetAvailableImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, FBeamConnectivity& ConnectivityStatus, UGetAvailableRequest* RequestData,
	                                const FOnGetAvailableSuccess& OnSuccess, const FOnGetAvailableError& OnError, const FOnGetAvailableComplete& OnComplete,
	                                int64& OutRequestId) const;
	/**
	 * @brief Overload version for binding lambdas when in C++ land. Prefer the BP version whenever possible, this is here mostly for quick experimentation purposes.	 
	 */
	void CPP_GetAvailableImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, FBeamConnectivity& ConnectivityStatus, UGetAvailableRequest* RequestData,
	                                 const FOnGetAvailableFullResponse& Handler) const;

		
	/**
	 * @brief Private implementation that all overloaded BP UFunctions call.	  
	 */
	void BP_PostPasswordUpdateConfirmImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, FBeamConnectivity& ConnectivityStatus, UPostPasswordUpdateConfirmRequest* RequestData,
	                                const FOnPostPasswordUpdateConfirmSuccess& OnSuccess, const FOnPostPasswordUpdateConfirmError& OnError, const FOnPostPasswordUpdateConfirmComplete& OnComplete,
	                                int64& OutRequestId) const;
	/**
	 * @brief Overload version for binding lambdas when in C++ land. Prefer the BP version whenever possible, this is here mostly for quick experimentation purposes.	 
	 */
	void CPP_PostPasswordUpdateConfirmImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, FBeamConnectivity& ConnectivityStatus, UPostPasswordUpdateConfirmRequest* RequestData,
	                                 const FOnPostPasswordUpdateConfirmFullResponse& Handler) const;

		
	/**
	 * @brief Private implementation that all overloaded BP UFunctions call.	  
	 */
	void BP_GetAvailableRolesImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, FBeamConnectivity& ConnectivityStatus, UGetAvailableRolesRequest* RequestData,
	                                const FOnGetAvailableRolesSuccess& OnSuccess, const FOnGetAvailableRolesError& OnError, const FOnGetAvailableRolesComplete& OnComplete,
	                                int64& OutRequestId) const;
	/**
	 * @brief Overload version for binding lambdas when in C++ land. Prefer the BP version whenever possible, this is here mostly for quick experimentation purposes.	 
	 */
	void CPP_GetAvailableRolesImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, FBeamConnectivity& ConnectivityStatus, UGetAvailableRolesRequest* RequestData,
	                                 const FOnGetAvailableRolesFullResponse& Handler) const;


	
	/**
	 * @brief Private implementation for requests that require authentication that all overloaded BP UFunctions call.	  
	 */
	void BP_DeleteMeDeviceImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, const FBeamAuthToken& AuthToken, FBeamConnectivity& ConnectivityStatus, UDeleteMeDeviceRequest* RequestData,
	                  const FOnDeleteMeDeviceSuccess& OnSuccess, const FOnDeleteMeDeviceError& OnError, const FOnDeleteMeDeviceComplete& OnComplete, int64& OutRequestId) const;
	/**
	 * @brief Overload version for binding lambdas when in C++ land. Prefer the BP version whenever possible, this is here mostly for quick experimentation purposes.	 
	 */
	void CPP_DeleteMeDeviceImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, const FBeamAuthToken& AuthToken, FBeamConnectivity& ConnectivityStatus, UDeleteMeDeviceRequest* RequestData,
	                   const FOnDeleteMeDeviceFullResponse& Handler) const;
		
	/**
	 * @brief Private implementation for requests that require authentication that all overloaded BP UFunctions call.	  
	 */
	void BP_GetMeImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, const FBeamAuthToken& AuthToken, FBeamConnectivity& ConnectivityStatus, UBasicAccountsGetMeRequest* RequestData,
	                  const FOnBasicAccountsGetMeSuccess& OnSuccess, const FOnBasicAccountsGetMeError& OnError, const FOnBasicAccountsGetMeComplete& OnComplete, int64& OutRequestId) const;
	/**
	 * @brief Overload version for binding lambdas when in C++ land. Prefer the BP version whenever possible, this is here mostly for quick experimentation purposes.	 
	 */
	void CPP_GetMeImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, const FBeamAuthToken& AuthToken, FBeamConnectivity& ConnectivityStatus, UBasicAccountsGetMeRequest* RequestData,
	                   const FOnBasicAccountsGetMeFullResponse& Handler) const;
		
	/**
	 * @brief Private implementation for requests that require authentication that all overloaded BP UFunctions call.	  
	 */
	void BP_PutMeImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, const FBeamAuthToken& AuthToken, FBeamConnectivity& ConnectivityStatus, UPutMeRequest* RequestData,
	                  const FOnPutMeSuccess& OnSuccess, const FOnPutMeError& OnError, const FOnPutMeComplete& OnComplete, int64& OutRequestId) const;
	/**
	 * @brief Overload version for binding lambdas when in C++ land. Prefer the BP version whenever possible, this is here mostly for quick experimentation purposes.	 
	 */
	void CPP_PutMeImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, const FBeamAuthToken& AuthToken, FBeamConnectivity& ConnectivityStatus, UPutMeRequest* RequestData,
	                   const FOnPutMeFullResponse& Handler) const;
		
	/**
	 * @brief Private implementation for requests that require authentication that all overloaded BP UFunctions call.	  
	 */
	void BP_DeleteMeThirdPartyImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, const FBeamAuthToken& AuthToken, FBeamConnectivity& ConnectivityStatus, UDeleteMeThirdPartyRequest* RequestData,
	                  const FOnDeleteMeThirdPartySuccess& OnSuccess, const FOnDeleteMeThirdPartyError& OnError, const FOnDeleteMeThirdPartyComplete& OnComplete, int64& OutRequestId) const;
	/**
	 * @brief Overload version for binding lambdas when in C++ land. Prefer the BP version whenever possible, this is here mostly for quick experimentation purposes.	 
	 */
	void CPP_DeleteMeThirdPartyImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, const FBeamAuthToken& AuthToken, FBeamConnectivity& ConnectivityStatus, UDeleteMeThirdPartyRequest* RequestData,
	                   const FOnDeleteMeThirdPartyFullResponse& Handler) const;
		
	/**
	 * @brief Private implementation for requests that require authentication that all overloaded BP UFunctions call.	  
	 */
	void BP_GetSearchImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, const FBeamAuthToken& AuthToken, FBeamConnectivity& ConnectivityStatus, UBasicAccountsGetSearchRequest* RequestData,
	                  const FOnBasicAccountsGetSearchSuccess& OnSuccess, const FOnBasicAccountsGetSearchError& OnError, const FOnBasicAccountsGetSearchComplete& OnComplete, int64& OutRequestId) const;
	/**
	 * @brief Overload version for binding lambdas when in C++ land. Prefer the BP version whenever possible, this is here mostly for quick experimentation purposes.	 
	 */
	void CPP_GetSearchImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, const FBeamAuthToken& AuthToken, FBeamConnectivity& ConnectivityStatus, UBasicAccountsGetSearchRequest* RequestData,
	                   const FOnBasicAccountsGetSearchFullResponse& Handler) const;
		
	/**
	 * @brief Private implementation for requests that require authentication that all overloaded BP UFunctions call.	  
	 */
	void BP_PostEmailUpdateInitImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, const FBeamAuthToken& AuthToken, FBeamConnectivity& ConnectivityStatus, UPostEmailUpdateInitRequest* RequestData,
	                  const FOnPostEmailUpdateInitSuccess& OnSuccess, const FOnPostEmailUpdateInitError& OnError, const FOnPostEmailUpdateInitComplete& OnComplete, int64& OutRequestId) const;
	/**
	 * @brief Overload version for binding lambdas when in C++ land. Prefer the BP version whenever possible, this is here mostly for quick experimentation purposes.	 
	 */
	void CPP_PostEmailUpdateInitImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, const FBeamAuthToken& AuthToken, FBeamConnectivity& ConnectivityStatus, UPostEmailUpdateInitRequest* RequestData,
	                   const FOnPostEmailUpdateInitFullResponse& Handler) const;
		
	/**
	 * @brief Private implementation for requests that require authentication that all overloaded BP UFunctions call.	  
	 */
	void BP_PostEmailUpdateConfirmImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, const FBeamAuthToken& AuthToken, FBeamConnectivity& ConnectivityStatus, UPostEmailUpdateConfirmRequest* RequestData,
	                  const FOnPostEmailUpdateConfirmSuccess& OnSuccess, const FOnPostEmailUpdateConfirmError& OnError, const FOnPostEmailUpdateConfirmComplete& OnComplete, int64& OutRequestId) const;
	/**
	 * @brief Overload version for binding lambdas when in C++ land. Prefer the BP version whenever possible, this is here mostly for quick experimentation purposes.	 
	 */
	void CPP_PostEmailUpdateConfirmImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, const FBeamAuthToken& AuthToken, FBeamConnectivity& ConnectivityStatus, UPostEmailUpdateConfirmRequest* RequestData,
	                   const FOnPostEmailUpdateConfirmFullResponse& Handler) const;
		
	/**
	 * @brief Private implementation for requests that require authentication that all overloaded BP UFunctions call.	  
	 */
	void BP_PostAdminAdminUserImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, const FBeamAuthToken& AuthToken, FBeamConnectivity& ConnectivityStatus, UPostAdminAdminUserRequest* RequestData,
	                  const FOnPostAdminAdminUserSuccess& OnSuccess, const FOnPostAdminAdminUserError& OnError, const FOnPostAdminAdminUserComplete& OnComplete, int64& OutRequestId) const;
	/**
	 * @brief Overload version for binding lambdas when in C++ land. Prefer the BP version whenever possible, this is here mostly for quick experimentation purposes.	 
	 */
	void CPP_PostAdminAdminUserImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, const FBeamAuthToken& AuthToken, FBeamConnectivity& ConnectivityStatus, UPostAdminAdminUserRequest* RequestData,
	                   const FOnPostAdminAdminUserFullResponse& Handler) const;
		
	/**
	 * @brief Private implementation for requests that require authentication that all overloaded BP UFunctions call.	  
	 */
	void BP_PostRegisterImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, const FBeamAuthToken& AuthToken, FBeamConnectivity& ConnectivityStatus, UBasicAccountsPostRegisterRequest* RequestData,
	                  const FOnBasicAccountsPostRegisterSuccess& OnSuccess, const FOnBasicAccountsPostRegisterError& OnError, const FOnBasicAccountsPostRegisterComplete& OnComplete, int64& OutRequestId) const;
	/**
	 * @brief Overload version for binding lambdas when in C++ land. Prefer the BP version whenever possible, this is here mostly for quick experimentation purposes.	 
	 */
	void CPP_PostRegisterImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, const FBeamAuthToken& AuthToken, FBeamConnectivity& ConnectivityStatus, UBasicAccountsPostRegisterRequest* RequestData,
	                   const FOnBasicAccountsPostRegisterFullResponse& Handler) const;
		
	/**
	 * @brief Private implementation for requests that require authentication that all overloaded BP UFunctions call.	  
	 */
	void BP_GetAdminMeImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, const FBeamAuthToken& AuthToken, FBeamConnectivity& ConnectivityStatus, UGetAdminMeRequest* RequestData,
	                  const FOnGetAdminMeSuccess& OnSuccess, const FOnGetAdminMeError& OnError, const FOnGetAdminMeComplete& OnComplete, int64& OutRequestId) const;
	/**
	 * @brief Overload version for binding lambdas when in C++ land. Prefer the BP version whenever possible, this is here mostly for quick experimentation purposes.	 
	 */
	void CPP_GetAdminMeImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, const FBeamAuthToken& AuthToken, FBeamConnectivity& ConnectivityStatus, UGetAdminMeRequest* RequestData,
	                   const FOnGetAdminMeFullResponse& Handler) const;
		
	/**
	 * @brief Private implementation for requests that require authentication that all overloaded BP UFunctions call.	  
	 */
	void BP_GetAdminAdminUsersImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, const FBeamAuthToken& AuthToken, FBeamConnectivity& ConnectivityStatus, UGetAdminAdminUsersRequest* RequestData,
	                  const FOnGetAdminAdminUsersSuccess& OnSuccess, const FOnGetAdminAdminUsersError& OnError, const FOnGetAdminAdminUsersComplete& OnComplete, int64& OutRequestId) const;
	/**
	 * @brief Overload version for binding lambdas when in C++ land. Prefer the BP version whenever possible, this is here mostly for quick experimentation purposes.	 
	 */
	void CPP_GetAdminAdminUsersImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, const FBeamAuthToken& AuthToken, FBeamConnectivity& ConnectivityStatus, UGetAdminAdminUsersRequest* RequestData,
	                   const FOnGetAdminAdminUsersFullResponse& Handler) const;
		
	/**
	 * @brief Private implementation for requests that require authentication that all overloaded BP UFunctions call.	  
	 */
	void BP_GetFindImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, const FBeamAuthToken& AuthToken, FBeamConnectivity& ConnectivityStatus, UGetFindRequest* RequestData,
	                  const FOnGetFindSuccess& OnSuccess, const FOnGetFindError& OnError, const FOnGetFindComplete& OnComplete, int64& OutRequestId) const;
	/**
	 * @brief Overload version for binding lambdas when in C++ land. Prefer the BP version whenever possible, this is here mostly for quick experimentation purposes.	 
	 */
	void CPP_GetFindImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, const FBeamAuthToken& AuthToken, FBeamConnectivity& ConnectivityStatus, UGetFindRequest* RequestData,
	                   const FOnGetFindFullResponse& Handler) const;
		
	/**
	 * @brief Private implementation for requests that require authentication that all overloaded BP UFunctions call.	  
	 */
	void BP_PutAdminEmailImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, const FBeamAuthToken& AuthToken, FBeamConnectivity& ConnectivityStatus, UPutAdminEmailRequest* RequestData,
	                  const FOnPutAdminEmailSuccess& OnSuccess, const FOnPutAdminEmailError& OnError, const FOnPutAdminEmailComplete& OnComplete, int64& OutRequestId) const;
	/**
	 * @brief Overload version for binding lambdas when in C++ land. Prefer the BP version whenever possible, this is here mostly for quick experimentation purposes.	 
	 */
	void CPP_PutAdminEmailImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, const FBeamAuthToken& AuthToken, FBeamConnectivity& ConnectivityStatus, UPutAdminEmailRequest* RequestData,
	                   const FOnPutAdminEmailFullResponse& Handler) const;
		
	/**
	 * @brief Private implementation for requests that require authentication that all overloaded BP UFunctions call.	  
	 */
	void BP_GetRoleReportImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, const FBeamAuthToken& AuthToken, FBeamConnectivity& ConnectivityStatus, UGetRoleReportRequest* RequestData,
	                  const FOnGetRoleReportSuccess& OnSuccess, const FOnGetRoleReportError& OnError, const FOnGetRoleReportComplete& OnComplete, int64& OutRequestId) const;
	/**
	 * @brief Overload version for binding lambdas when in C++ land. Prefer the BP version whenever possible, this is here mostly for quick experimentation purposes.	 
	 */
	void CPP_GetRoleReportImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, const FBeamAuthToken& AuthToken, FBeamConnectivity& ConnectivityStatus, UGetRoleReportRequest* RequestData,
	                   const FOnGetRoleReportFullResponse& Handler) const;
		
	/**
	 * @brief Private implementation for requests that require authentication that all overloaded BP UFunctions call.	  
	 */
	void BP_PutRoleImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, const FBeamAuthToken& AuthToken, FBeamConnectivity& ConnectivityStatus, UObjectAccountsPutRoleRequest* RequestData,
	                  const FOnObjectAccountsPutRoleSuccess& OnSuccess, const FOnObjectAccountsPutRoleError& OnError, const FOnObjectAccountsPutRoleComplete& OnComplete, int64& OutRequestId) const;
	/**
	 * @brief Overload version for binding lambdas when in C++ land. Prefer the BP version whenever possible, this is here mostly for quick experimentation purposes.	 
	 */
	void CPP_PutRoleImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, const FBeamAuthToken& AuthToken, FBeamConnectivity& ConnectivityStatus, UObjectAccountsPutRoleRequest* RequestData,
	                   const FOnObjectAccountsPutRoleFullResponse& Handler) const;
		
	/**
	 * @brief Private implementation for requests that require authentication that all overloaded BP UFunctions call.	  
	 */
	void BP_DeleteRoleImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, const FBeamAuthToken& AuthToken, FBeamConnectivity& ConnectivityStatus, UDeleteRoleRequest* RequestData,
	                  const FOnDeleteRoleSuccess& OnSuccess, const FOnDeleteRoleError& OnError, const FOnDeleteRoleComplete& OnComplete, int64& OutRequestId) const;
	/**
	 * @brief Overload version for binding lambdas when in C++ land. Prefer the BP version whenever possible, this is here mostly for quick experimentation purposes.	 
	 */
	void CPP_DeleteRoleImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, const FBeamAuthToken& AuthToken, FBeamConnectivity& ConnectivityStatus, UDeleteRoleRequest* RequestData,
	                   const FOnDeleteRoleFullResponse& Handler) const;
		
	/**
	 * @brief Private implementation for requests that require authentication that all overloaded BP UFunctions call.	  
	 */
	void BP_PutAdminScopeImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, const FBeamAuthToken& AuthToken, FBeamConnectivity& ConnectivityStatus, UPutAdminScopeRequest* RequestData,
	                  const FOnPutAdminScopeSuccess& OnSuccess, const FOnPutAdminScopeError& OnError, const FOnPutAdminScopeComplete& OnComplete, int64& OutRequestId) const;
	/**
	 * @brief Overload version for binding lambdas when in C++ land. Prefer the BP version whenever possible, this is here mostly for quick experimentation purposes.	 
	 */
	void CPP_PutAdminScopeImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, const FBeamAuthToken& AuthToken, FBeamConnectivity& ConnectivityStatus, UPutAdminScopeRequest* RequestData,
	                   const FOnPutAdminScopeFullResponse& Handler) const;
		
	/**
	 * @brief Private implementation for requests that require authentication that all overloaded BP UFunctions call.	  
	 */
	void BP_DeleteAdminScopeImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, const FBeamAuthToken& AuthToken, FBeamConnectivity& ConnectivityStatus, UDeleteAdminScopeRequest* RequestData,
	                  const FOnDeleteAdminScopeSuccess& OnSuccess, const FOnDeleteAdminScopeError& OnError, const FOnDeleteAdminScopeComplete& OnComplete, int64& OutRequestId) const;
	/**
	 * @brief Overload version for binding lambdas when in C++ land. Prefer the BP version whenever possible, this is here mostly for quick experimentation purposes.	 
	 */
	void CPP_DeleteAdminScopeImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, const FBeamAuthToken& AuthToken, FBeamConnectivity& ConnectivityStatus, UDeleteAdminScopeRequest* RequestData,
	                   const FOnDeleteAdminScopeFullResponse& Handler) const;
		
	/**
	 * @brief Private implementation for requests that require authentication that all overloaded BP UFunctions call.	  
	 */
	void BP_PutAdminThirdPartyImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, const FBeamAuthToken& AuthToken, FBeamConnectivity& ConnectivityStatus, UPutAdminThirdPartyRequest* RequestData,
	                  const FOnPutAdminThirdPartySuccess& OnSuccess, const FOnPutAdminThirdPartyError& OnError, const FOnPutAdminThirdPartyComplete& OnComplete, int64& OutRequestId) const;
	/**
	 * @brief Overload version for binding lambdas when in C++ land. Prefer the BP version whenever possible, this is here mostly for quick experimentation purposes.	 
	 */
	void CPP_PutAdminThirdPartyImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, const FBeamAuthToken& AuthToken, FBeamConnectivity& ConnectivityStatus, UPutAdminThirdPartyRequest* RequestData,
	                   const FOnPutAdminThirdPartyFullResponse& Handler) const;
		
	/**
	 * @brief Private implementation for requests that require authentication that all overloaded BP UFunctions call.	  
	 */
	void BP_DeleteAdminThirdPartyImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, const FBeamAuthToken& AuthToken, FBeamConnectivity& ConnectivityStatus, UDeleteAdminThirdPartyRequest* RequestData,
	                  const FOnDeleteAdminThirdPartySuccess& OnSuccess, const FOnDeleteAdminThirdPartyError& OnError, const FOnDeleteAdminThirdPartyComplete& OnComplete, int64& OutRequestId) const;
	/**
	 * @brief Overload version for binding lambdas when in C++ land. Prefer the BP version whenever possible, this is here mostly for quick experimentation purposes.	 
	 */
	void CPP_DeleteAdminThirdPartyImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, const FBeamAuthToken& AuthToken, FBeamConnectivity& ConnectivityStatus, UDeleteAdminThirdPartyRequest* RequestData,
	                   const FOnDeleteAdminThirdPartyFullResponse& Handler) const;
		
	/**
	 * @brief Private implementation for requests that require authentication that all overloaded BP UFunctions call.	  
	 */
	void BP_PutAccountsImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, const FBeamAuthToken& AuthToken, FBeamConnectivity& ConnectivityStatus, UPutAccountsRequest* RequestData,
	                  const FOnPutAccountsSuccess& OnSuccess, const FOnPutAccountsError& OnError, const FOnPutAccountsComplete& OnComplete, int64& OutRequestId) const;
	/**
	 * @brief Overload version for binding lambdas when in C++ land. Prefer the BP version whenever possible, this is here mostly for quick experimentation purposes.	 
	 */
	void CPP_PutAccountsImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, const FBeamAuthToken& AuthToken, FBeamConnectivity& ConnectivityStatus, UPutAccountsRequest* RequestData,
	                   const FOnPutAccountsFullResponse& Handler) const;
		
	/**
	 * @brief Private implementation for requests that require authentication that all overloaded BP UFunctions call.	  
	 */
	void BP_DeleteAdminForgetImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, const FBeamAuthToken& AuthToken, FBeamConnectivity& ConnectivityStatus, UDeleteAdminForgetRequest* RequestData,
	                  const FOnDeleteAdminForgetSuccess& OnSuccess, const FOnDeleteAdminForgetError& OnError, const FOnDeleteAdminForgetComplete& OnComplete, int64& OutRequestId) const;
	/**
	 * @brief Overload version for binding lambdas when in C++ land. Prefer the BP version whenever possible, this is here mostly for quick experimentation purposes.	 
	 */
	void CPP_DeleteAdminForgetImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, const FBeamAuthToken& AuthToken, FBeamConnectivity& ConnectivityStatus, UDeleteAdminForgetRequest* RequestData,
	                   const FOnDeleteAdminForgetFullResponse& Handler) const;

public:
	
	/** Used by a helper blueprint node so that you can easily chain requests in BP-land. */
	UFUNCTION(BlueprintPure, BlueprintInternalUseOnly)
	static UBeamAccountsApi* GetSelf() { return GEngine->GetEngineSubsystem<UBeamAccountsApi>(); }

	
	/**
	 * @brief Makes a request to the Get /basic/accounts/get-personally-identifiable-information endpoint of the Accounts Service.
	 *
	 * PREFER THE UFUNCTION OVERLOAD AS OPPOSED TO THIS. THIS MAINLY EXISTS TO ALLOW LAMBDA BINDING THE HANDLER.
	 * (Dynamic delegates do not allow for that so... we autogen this one to make experimenting in CPP a bit faster and for whenever you need to capture variables).
	 * 
	 * @param Request The Request UObject. All (de)serialized data the request data creates is tied to the lifecycle of this object.
	 * @param Handler A callback that defines how to handle success, error and completion. 
	 */
	void CPP_GetGetPersonallyIdentifiableInformation(UGetGetPersonallyIdentifiableInformationRequest* Request, const FOnGetGetPersonallyIdentifiableInformationFullResponse& Handler) const;

		
	/**
	 * @brief Makes a request to the Get /basic/accounts/available/third-party endpoint of the Accounts Service.
	 *
	 * PREFER THE UFUNCTION OVERLOAD AS OPPOSED TO THIS. THIS MAINLY EXISTS TO ALLOW LAMBDA BINDING THE HANDLER.
	 * (Dynamic delegates do not allow for that so... we autogen this one to make experimenting in CPP a bit faster and for whenever you need to capture variables).
	 * 
	 * @param Request The Request UObject. All (de)serialized data the request data creates is tied to the lifecycle of this object.
	 * @param Handler A callback that defines how to handle success, error and completion. 
	 */
	void CPP_GetAvailableThirdParty(UGetAvailableThirdPartyRequest* Request, const FOnGetAvailableThirdPartyFullResponse& Handler) const;

		
	/**
	 * @brief Makes a request to the Post /basic/accounts/password-update/init endpoint of the Accounts Service.
	 *
	 * PREFER THE UFUNCTION OVERLOAD AS OPPOSED TO THIS. THIS MAINLY EXISTS TO ALLOW LAMBDA BINDING THE HANDLER.
	 * (Dynamic delegates do not allow for that so... we autogen this one to make experimenting in CPP a bit faster and for whenever you need to capture variables).
	 * 
	 * @param Request The Request UObject. All (de)serialized data the request data creates is tied to the lifecycle of this object.
	 * @param Handler A callback that defines how to handle success, error and completion. 
	 */
	void CPP_PostPasswordUpdateInit(UPostPasswordUpdateInitRequest* Request, const FOnPostPasswordUpdateInitFullResponse& Handler) const;

		
	/**
	 * @brief Makes a request to the Get /basic/accounts/available/device-id endpoint of the Accounts Service.
	 *
	 * PREFER THE UFUNCTION OVERLOAD AS OPPOSED TO THIS. THIS MAINLY EXISTS TO ALLOW LAMBDA BINDING THE HANDLER.
	 * (Dynamic delegates do not allow for that so... we autogen this one to make experimenting in CPP a bit faster and for whenever you need to capture variables).
	 * 
	 * @param Request The Request UObject. All (de)serialized data the request data creates is tied to the lifecycle of this object.
	 * @param Handler A callback that defines how to handle success, error and completion. 
	 */
	void CPP_GetAvailableDeviceId(UGetAvailableDeviceIdRequest* Request, const FOnGetAvailableDeviceIdFullResponse& Handler) const;

		
	/**
	 * @brief Makes a request to the Get /basic/accounts/available endpoint of the Accounts Service.
	 *
	 * PREFER THE UFUNCTION OVERLOAD AS OPPOSED TO THIS. THIS MAINLY EXISTS TO ALLOW LAMBDA BINDING THE HANDLER.
	 * (Dynamic delegates do not allow for that so... we autogen this one to make experimenting in CPP a bit faster and for whenever you need to capture variables).
	 * 
	 * @param Request The Request UObject. All (de)serialized data the request data creates is tied to the lifecycle of this object.
	 * @param Handler A callback that defines how to handle success, error and completion. 
	 */
	void CPP_GetAvailable(UGetAvailableRequest* Request, const FOnGetAvailableFullResponse& Handler) const;

		
	/**
	 * @brief Makes a request to the Post /basic/accounts/password-update/confirm endpoint of the Accounts Service.
	 *
	 * PREFER THE UFUNCTION OVERLOAD AS OPPOSED TO THIS. THIS MAINLY EXISTS TO ALLOW LAMBDA BINDING THE HANDLER.
	 * (Dynamic delegates do not allow for that so... we autogen this one to make experimenting in CPP a bit faster and for whenever you need to capture variables).
	 * 
	 * @param Request The Request UObject. All (de)serialized data the request data creates is tied to the lifecycle of this object.
	 * @param Handler A callback that defines how to handle success, error and completion. 
	 */
	void CPP_PostPasswordUpdateConfirm(UPostPasswordUpdateConfirmRequest* Request, const FOnPostPasswordUpdateConfirmFullResponse& Handler) const;

		
	/**
	 * @brief Makes a request to the Get /object/accounts/{objectId}/available-roles endpoint of the Accounts Service.
	 *
	 * PREFER THE UFUNCTION OVERLOAD AS OPPOSED TO THIS. THIS MAINLY EXISTS TO ALLOW LAMBDA BINDING THE HANDLER.
	 * (Dynamic delegates do not allow for that so... we autogen this one to make experimenting in CPP a bit faster and for whenever you need to capture variables).
	 * 
	 * @param Request The Request UObject. All (de)serialized data the request data creates is tied to the lifecycle of this object.
	 * @param Handler A callback that defines how to handle success, error and completion. 
	 */
	void CPP_GetAvailableRoles(UGetAvailableRolesRequest* Request, const FOnGetAvailableRolesFullResponse& Handler) const;


	
	/**
	 * @brief Makes an authenticated request to the Delete /basic/accounts/me/device endpoint of the Accounts Service.
	 *
	 * PREFER THE UFUNCTION OVERLOAD AS OPPOSED TO THIS. THIS MAINLY EXISTS TO ALLOW LAMBDA BINDING THE HANDLER.
	 * (Dynamic delegates do not allow for that so... we autogen this one to make experimenting in CPP a bit faster).
	 * 
	 * @param UserSlot The Authenticated User Slot that is making this request.
	 * @param Request The Request UObject. All (de)serialized data the request data creates is tied to the lifecycle of this object.
	 * @param Handler A callback that defines how to handle success, error and completion. 
	 */
	void CPP_DeleteMeDevice(const FUserSlot& UserSlot, UDeleteMeDeviceRequest* Request, const FOnDeleteMeDeviceFullResponse& Handler) const;

		
	/**
	 * @brief Makes an authenticated request to the Get /basic/accounts/me endpoint of the Accounts Service.
	 *
	 * PREFER THE UFUNCTION OVERLOAD AS OPPOSED TO THIS. THIS MAINLY EXISTS TO ALLOW LAMBDA BINDING THE HANDLER.
	 * (Dynamic delegates do not allow for that so... we autogen this one to make experimenting in CPP a bit faster).
	 * 
	 * @param UserSlot The Authenticated User Slot that is making this request.
	 * @param Request The Request UObject. All (de)serialized data the request data creates is tied to the lifecycle of this object.
	 * @param Handler A callback that defines how to handle success, error and completion. 
	 */
	void CPP_GetMe(const FUserSlot& UserSlot, UBasicAccountsGetMeRequest* Request, const FOnBasicAccountsGetMeFullResponse& Handler) const;

		
	/**
	 * @brief Makes an authenticated request to the Put /basic/accounts/me endpoint of the Accounts Service.
	 *
	 * PREFER THE UFUNCTION OVERLOAD AS OPPOSED TO THIS. THIS MAINLY EXISTS TO ALLOW LAMBDA BINDING THE HANDLER.
	 * (Dynamic delegates do not allow for that so... we autogen this one to make experimenting in CPP a bit faster).
	 * 
	 * @param UserSlot The Authenticated User Slot that is making this request.
	 * @param Request The Request UObject. All (de)serialized data the request data creates is tied to the lifecycle of this object.
	 * @param Handler A callback that defines how to handle success, error and completion. 
	 */
	void CPP_PutMe(const FUserSlot& UserSlot, UPutMeRequest* Request, const FOnPutMeFullResponse& Handler) const;

		
	/**
	 * @brief Makes an authenticated request to the Delete /basic/accounts/me/third-party endpoint of the Accounts Service.
	 *
	 * PREFER THE UFUNCTION OVERLOAD AS OPPOSED TO THIS. THIS MAINLY EXISTS TO ALLOW LAMBDA BINDING THE HANDLER.
	 * (Dynamic delegates do not allow for that so... we autogen this one to make experimenting in CPP a bit faster).
	 * 
	 * @param UserSlot The Authenticated User Slot that is making this request.
	 * @param Request The Request UObject. All (de)serialized data the request data creates is tied to the lifecycle of this object.
	 * @param Handler A callback that defines how to handle success, error and completion. 
	 */
	void CPP_DeleteMeThirdParty(const FUserSlot& UserSlot, UDeleteMeThirdPartyRequest* Request, const FOnDeleteMeThirdPartyFullResponse& Handler) const;

		
	/**
	 * @brief Makes an authenticated request to the Get /basic/accounts/search endpoint of the Accounts Service.
	 *
	 * PREFER THE UFUNCTION OVERLOAD AS OPPOSED TO THIS. THIS MAINLY EXISTS TO ALLOW LAMBDA BINDING THE HANDLER.
	 * (Dynamic delegates do not allow for that so... we autogen this one to make experimenting in CPP a bit faster).
	 * 
	 * @param UserSlot The Authenticated User Slot that is making this request.
	 * @param Request The Request UObject. All (de)serialized data the request data creates is tied to the lifecycle of this object.
	 * @param Handler A callback that defines how to handle success, error and completion. 
	 */
	void CPP_GetSearch(const FUserSlot& UserSlot, UBasicAccountsGetSearchRequest* Request, const FOnBasicAccountsGetSearchFullResponse& Handler) const;

		
	/**
	 * @brief Makes an authenticated request to the Post /basic/accounts/email-update/init endpoint of the Accounts Service.
	 *
	 * PREFER THE UFUNCTION OVERLOAD AS OPPOSED TO THIS. THIS MAINLY EXISTS TO ALLOW LAMBDA BINDING THE HANDLER.
	 * (Dynamic delegates do not allow for that so... we autogen this one to make experimenting in CPP a bit faster).
	 * 
	 * @param UserSlot The Authenticated User Slot that is making this request.
	 * @param Request The Request UObject. All (de)serialized data the request data creates is tied to the lifecycle of this object.
	 * @param Handler A callback that defines how to handle success, error and completion. 
	 */
	void CPP_PostEmailUpdateInit(const FUserSlot& UserSlot, UPostEmailUpdateInitRequest* Request, const FOnPostEmailUpdateInitFullResponse& Handler) const;

		
	/**
	 * @brief Makes an authenticated request to the Post /basic/accounts/email-update/confirm endpoint of the Accounts Service.
	 *
	 * PREFER THE UFUNCTION OVERLOAD AS OPPOSED TO THIS. THIS MAINLY EXISTS TO ALLOW LAMBDA BINDING THE HANDLER.
	 * (Dynamic delegates do not allow for that so... we autogen this one to make experimenting in CPP a bit faster).
	 * 
	 * @param UserSlot The Authenticated User Slot that is making this request.
	 * @param Request The Request UObject. All (de)serialized data the request data creates is tied to the lifecycle of this object.
	 * @param Handler A callback that defines how to handle success, error and completion. 
	 */
	void CPP_PostEmailUpdateConfirm(const FUserSlot& UserSlot, UPostEmailUpdateConfirmRequest* Request, const FOnPostEmailUpdateConfirmFullResponse& Handler) const;

		
	/**
	 * @brief Makes an authenticated request to the Post /basic/accounts/admin/admin-user endpoint of the Accounts Service.
	 *
	 * PREFER THE UFUNCTION OVERLOAD AS OPPOSED TO THIS. THIS MAINLY EXISTS TO ALLOW LAMBDA BINDING THE HANDLER.
	 * (Dynamic delegates do not allow for that so... we autogen this one to make experimenting in CPP a bit faster).
	 * 
	 * @param UserSlot The Authenticated User Slot that is making this request.
	 * @param Request The Request UObject. All (de)serialized data the request data creates is tied to the lifecycle of this object.
	 * @param Handler A callback that defines how to handle success, error and completion. 
	 */
	void CPP_PostAdminAdminUser(const FUserSlot& UserSlot, UPostAdminAdminUserRequest* Request, const FOnPostAdminAdminUserFullResponse& Handler) const;

		
	/**
	 * @brief Makes an authenticated request to the Post /basic/accounts/register endpoint of the Accounts Service.
	 *
	 * PREFER THE UFUNCTION OVERLOAD AS OPPOSED TO THIS. THIS MAINLY EXISTS TO ALLOW LAMBDA BINDING THE HANDLER.
	 * (Dynamic delegates do not allow for that so... we autogen this one to make experimenting in CPP a bit faster).
	 * 
	 * @param UserSlot The Authenticated User Slot that is making this request.
	 * @param Request The Request UObject. All (de)serialized data the request data creates is tied to the lifecycle of this object.
	 * @param Handler A callback that defines how to handle success, error and completion. 
	 */
	void CPP_PostRegister(const FUserSlot& UserSlot, UBasicAccountsPostRegisterRequest* Request, const FOnBasicAccountsPostRegisterFullResponse& Handler) const;

		
	/**
	 * @brief Makes an authenticated request to the Get /basic/accounts/admin/me endpoint of the Accounts Service.
	 *
	 * PREFER THE UFUNCTION OVERLOAD AS OPPOSED TO THIS. THIS MAINLY EXISTS TO ALLOW LAMBDA BINDING THE HANDLER.
	 * (Dynamic delegates do not allow for that so... we autogen this one to make experimenting in CPP a bit faster).
	 * 
	 * @param UserSlot The Authenticated User Slot that is making this request.
	 * @param Request The Request UObject. All (de)serialized data the request data creates is tied to the lifecycle of this object.
	 * @param Handler A callback that defines how to handle success, error and completion. 
	 */
	void CPP_GetAdminMe(const FUserSlot& UserSlot, UGetAdminMeRequest* Request, const FOnGetAdminMeFullResponse& Handler) const;

		
	/**
	 * @brief Makes an authenticated request to the Get /basic/accounts/admin/admin-users endpoint of the Accounts Service.
	 *
	 * PREFER THE UFUNCTION OVERLOAD AS OPPOSED TO THIS. THIS MAINLY EXISTS TO ALLOW LAMBDA BINDING THE HANDLER.
	 * (Dynamic delegates do not allow for that so... we autogen this one to make experimenting in CPP a bit faster).
	 * 
	 * @param UserSlot The Authenticated User Slot that is making this request.
	 * @param Request The Request UObject. All (de)serialized data the request data creates is tied to the lifecycle of this object.
	 * @param Handler A callback that defines how to handle success, error and completion. 
	 */
	void CPP_GetAdminAdminUsers(const FUserSlot& UserSlot, UGetAdminAdminUsersRequest* Request, const FOnGetAdminAdminUsersFullResponse& Handler) const;

		
	/**
	 * @brief Makes an authenticated request to the Get /basic/accounts/find endpoint of the Accounts Service.
	 *
	 * PREFER THE UFUNCTION OVERLOAD AS OPPOSED TO THIS. THIS MAINLY EXISTS TO ALLOW LAMBDA BINDING THE HANDLER.
	 * (Dynamic delegates do not allow for that so... we autogen this one to make experimenting in CPP a bit faster).
	 * 
	 * @param UserSlot The Authenticated User Slot that is making this request.
	 * @param Request The Request UObject. All (de)serialized data the request data creates is tied to the lifecycle of this object.
	 * @param Handler A callback that defines how to handle success, error and completion. 
	 */
	void CPP_GetFind(const FUserSlot& UserSlot, UGetFindRequest* Request, const FOnGetFindFullResponse& Handler) const;

		
	/**
	 * @brief Makes an authenticated request to the Put /object/accounts/{objectId}/admin/email endpoint of the Accounts Service.
	 *
	 * PREFER THE UFUNCTION OVERLOAD AS OPPOSED TO THIS. THIS MAINLY EXISTS TO ALLOW LAMBDA BINDING THE HANDLER.
	 * (Dynamic delegates do not allow for that so... we autogen this one to make experimenting in CPP a bit faster).
	 * 
	 * @param UserSlot The Authenticated User Slot that is making this request.
	 * @param Request The Request UObject. All (de)serialized data the request data creates is tied to the lifecycle of this object.
	 * @param Handler A callback that defines how to handle success, error and completion. 
	 */
	void CPP_PutAdminEmail(const FUserSlot& UserSlot, UPutAdminEmailRequest* Request, const FOnPutAdminEmailFullResponse& Handler) const;

		
	/**
	 * @brief Makes an authenticated request to the Get /object/accounts/{objectId}/role/report endpoint of the Accounts Service.
	 *
	 * PREFER THE UFUNCTION OVERLOAD AS OPPOSED TO THIS. THIS MAINLY EXISTS TO ALLOW LAMBDA BINDING THE HANDLER.
	 * (Dynamic delegates do not allow for that so... we autogen this one to make experimenting in CPP a bit faster).
	 * 
	 * @param UserSlot The Authenticated User Slot that is making this request.
	 * @param Request The Request UObject. All (de)serialized data the request data creates is tied to the lifecycle of this object.
	 * @param Handler A callback that defines how to handle success, error and completion. 
	 */
	void CPP_GetRoleReport(const FUserSlot& UserSlot, UGetRoleReportRequest* Request, const FOnGetRoleReportFullResponse& Handler) const;

		
	/**
	 * @brief Makes an authenticated request to the Put /object/accounts/{objectId}/role endpoint of the Accounts Service.
	 *
	 * PREFER THE UFUNCTION OVERLOAD AS OPPOSED TO THIS. THIS MAINLY EXISTS TO ALLOW LAMBDA BINDING THE HANDLER.
	 * (Dynamic delegates do not allow for that so... we autogen this one to make experimenting in CPP a bit faster).
	 * 
	 * @param UserSlot The Authenticated User Slot that is making this request.
	 * @param Request The Request UObject. All (de)serialized data the request data creates is tied to the lifecycle of this object.
	 * @param Handler A callback that defines how to handle success, error and completion. 
	 */
	void CPP_PutRole(const FUserSlot& UserSlot, UObjectAccountsPutRoleRequest* Request, const FOnObjectAccountsPutRoleFullResponse& Handler) const;

		
	/**
	 * @brief Makes an authenticated request to the Delete /object/accounts/{objectId}/role endpoint of the Accounts Service.
	 *
	 * PREFER THE UFUNCTION OVERLOAD AS OPPOSED TO THIS. THIS MAINLY EXISTS TO ALLOW LAMBDA BINDING THE HANDLER.
	 * (Dynamic delegates do not allow for that so... we autogen this one to make experimenting in CPP a bit faster).
	 * 
	 * @param UserSlot The Authenticated User Slot that is making this request.
	 * @param Request The Request UObject. All (de)serialized data the request data creates is tied to the lifecycle of this object.
	 * @param Handler A callback that defines how to handle success, error and completion. 
	 */
	void CPP_DeleteRole(const FUserSlot& UserSlot, UDeleteRoleRequest* Request, const FOnDeleteRoleFullResponse& Handler) const;

		
	/**
	 * @brief Makes an authenticated request to the Put /object/accounts/{objectId}/admin/scope endpoint of the Accounts Service.
	 *
	 * PREFER THE UFUNCTION OVERLOAD AS OPPOSED TO THIS. THIS MAINLY EXISTS TO ALLOW LAMBDA BINDING THE HANDLER.
	 * (Dynamic delegates do not allow for that so... we autogen this one to make experimenting in CPP a bit faster).
	 * 
	 * @param UserSlot The Authenticated User Slot that is making this request.
	 * @param Request The Request UObject. All (de)serialized data the request data creates is tied to the lifecycle of this object.
	 * @param Handler A callback that defines how to handle success, error and completion. 
	 */
	void CPP_PutAdminScope(const FUserSlot& UserSlot, UPutAdminScopeRequest* Request, const FOnPutAdminScopeFullResponse& Handler) const;

		
	/**
	 * @brief Makes an authenticated request to the Delete /object/accounts/{objectId}/admin/scope endpoint of the Accounts Service.
	 *
	 * PREFER THE UFUNCTION OVERLOAD AS OPPOSED TO THIS. THIS MAINLY EXISTS TO ALLOW LAMBDA BINDING THE HANDLER.
	 * (Dynamic delegates do not allow for that so... we autogen this one to make experimenting in CPP a bit faster).
	 * 
	 * @param UserSlot The Authenticated User Slot that is making this request.
	 * @param Request The Request UObject. All (de)serialized data the request data creates is tied to the lifecycle of this object.
	 * @param Handler A callback that defines how to handle success, error and completion. 
	 */
	void CPP_DeleteAdminScope(const FUserSlot& UserSlot, UDeleteAdminScopeRequest* Request, const FOnDeleteAdminScopeFullResponse& Handler) const;

		
	/**
	 * @brief Makes an authenticated request to the Put /object/accounts/{objectId}/admin/third-party endpoint of the Accounts Service.
	 *
	 * PREFER THE UFUNCTION OVERLOAD AS OPPOSED TO THIS. THIS MAINLY EXISTS TO ALLOW LAMBDA BINDING THE HANDLER.
	 * (Dynamic delegates do not allow for that so... we autogen this one to make experimenting in CPP a bit faster).
	 * 
	 * @param UserSlot The Authenticated User Slot that is making this request.
	 * @param Request The Request UObject. All (de)serialized data the request data creates is tied to the lifecycle of this object.
	 * @param Handler A callback that defines how to handle success, error and completion. 
	 */
	void CPP_PutAdminThirdParty(const FUserSlot& UserSlot, UPutAdminThirdPartyRequest* Request, const FOnPutAdminThirdPartyFullResponse& Handler) const;

		
	/**
	 * @brief Makes an authenticated request to the Delete /object/accounts/{objectId}/admin/third-party endpoint of the Accounts Service.
	 *
	 * PREFER THE UFUNCTION OVERLOAD AS OPPOSED TO THIS. THIS MAINLY EXISTS TO ALLOW LAMBDA BINDING THE HANDLER.
	 * (Dynamic delegates do not allow for that so... we autogen this one to make experimenting in CPP a bit faster).
	 * 
	 * @param UserSlot The Authenticated User Slot that is making this request.
	 * @param Request The Request UObject. All (de)serialized data the request data creates is tied to the lifecycle of this object.
	 * @param Handler A callback that defines how to handle success, error and completion. 
	 */
	void CPP_DeleteAdminThirdParty(const FUserSlot& UserSlot, UDeleteAdminThirdPartyRequest* Request, const FOnDeleteAdminThirdPartyFullResponse& Handler) const;

		
	/**
	 * @brief Makes an authenticated request to the Put /object/accounts/{objectId}/ endpoint of the Accounts Service.
	 *
	 * PREFER THE UFUNCTION OVERLOAD AS OPPOSED TO THIS. THIS MAINLY EXISTS TO ALLOW LAMBDA BINDING THE HANDLER.
	 * (Dynamic delegates do not allow for that so... we autogen this one to make experimenting in CPP a bit faster).
	 * 
	 * @param UserSlot The Authenticated User Slot that is making this request.
	 * @param Request The Request UObject. All (de)serialized data the request data creates is tied to the lifecycle of this object.
	 * @param Handler A callback that defines how to handle success, error and completion. 
	 */
	void CPP_PutAccounts(const FUserSlot& UserSlot, UPutAccountsRequest* Request, const FOnPutAccountsFullResponse& Handler) const;

		
	/**
	 * @brief Makes an authenticated request to the Delete /object/accounts/{objectId}/admin/forget endpoint of the Accounts Service.
	 *
	 * PREFER THE UFUNCTION OVERLOAD AS OPPOSED TO THIS. THIS MAINLY EXISTS TO ALLOW LAMBDA BINDING THE HANDLER.
	 * (Dynamic delegates do not allow for that so... we autogen this one to make experimenting in CPP a bit faster).
	 * 
	 * @param UserSlot The Authenticated User Slot that is making this request.
	 * @param Request The Request UObject. All (de)serialized data the request data creates is tied to the lifecycle of this object.
	 * @param Handler A callback that defines how to handle success, error and completion. 
	 */
	void CPP_DeleteAdminForget(const FUserSlot& UserSlot, UDeleteAdminForgetRequest* Request, const FOnDeleteAdminForgetFullResponse& Handler) const;


	
	/**
	 * @brief Makes a request to the Get /basic/accounts/get-personally-identifiable-information endpoint of the Accounts Service.
	 *
	 * @param Request The Request UObject. All (de)serialized data the request data creates is tied to the lifecycle of this object.
	 * @param OnSuccess What to do if the requests receives a successful response.
	 * @param OnError What to do if the request receives an error response.
	 * @param OnComplete What to after either OnSuccess or OnError have finished executing.
	 * @param OutRequestId The Request Id -- used to query information about the request or to cancel it while it's in flight. 
	 */
	UFUNCTION(BlueprintCallable, Category="Beam|APIs|Accounts", meta=(AutoCreateRefTerm="OnSuccess,OnError,OnComplete"))
	void GetGetPersonallyIdentifiableInformation(UGetGetPersonallyIdentifiableInformationRequest* Request, const FOnGetGetPersonallyIdentifiableInformationSuccess& OnSuccess, const FOnGetGetPersonallyIdentifiableInformationError& OnError, const FOnGetGetPersonallyIdentifiableInformationComplete& OnComplete,
								 int64& OutRequestId);

		
	/**
	 * @brief Makes a request to the Get /basic/accounts/available/third-party endpoint of the Accounts Service.
	 *
	 * @param Request The Request UObject. All (de)serialized data the request data creates is tied to the lifecycle of this object.
	 * @param OnSuccess What to do if the requests receives a successful response.
	 * @param OnError What to do if the request receives an error response.
	 * @param OnComplete What to after either OnSuccess or OnError have finished executing.
	 * @param OutRequestId The Request Id -- used to query information about the request or to cancel it while it's in flight. 
	 */
	UFUNCTION(BlueprintCallable, Category="Beam|APIs|Accounts", meta=(AutoCreateRefTerm="OnSuccess,OnError,OnComplete"))
	void GetAvailableThirdParty(UGetAvailableThirdPartyRequest* Request, const FOnGetAvailableThirdPartySuccess& OnSuccess, const FOnGetAvailableThirdPartyError& OnError, const FOnGetAvailableThirdPartyComplete& OnComplete,
								 int64& OutRequestId);

		
	/**
	 * @brief Makes a request to the Post /basic/accounts/password-update/init endpoint of the Accounts Service.
	 *
	 * @param Request The Request UObject. All (de)serialized data the request data creates is tied to the lifecycle of this object.
	 * @param OnSuccess What to do if the requests receives a successful response.
	 * @param OnError What to do if the request receives an error response.
	 * @param OnComplete What to after either OnSuccess or OnError have finished executing.
	 * @param OutRequestId The Request Id -- used to query information about the request or to cancel it while it's in flight. 
	 */
	UFUNCTION(BlueprintCallable, Category="Beam|APIs|Accounts", meta=(AutoCreateRefTerm="OnSuccess,OnError,OnComplete"))
	void PostPasswordUpdateInit(UPostPasswordUpdateInitRequest* Request, const FOnPostPasswordUpdateInitSuccess& OnSuccess, const FOnPostPasswordUpdateInitError& OnError, const FOnPostPasswordUpdateInitComplete& OnComplete,
								 int64& OutRequestId);

		
	/**
	 * @brief Makes a request to the Get /basic/accounts/available/device-id endpoint of the Accounts Service.
	 *
	 * @param Request The Request UObject. All (de)serialized data the request data creates is tied to the lifecycle of this object.
	 * @param OnSuccess What to do if the requests receives a successful response.
	 * @param OnError What to do if the request receives an error response.
	 * @param OnComplete What to after either OnSuccess or OnError have finished executing.
	 * @param OutRequestId The Request Id -- used to query information about the request or to cancel it while it's in flight. 
	 */
	UFUNCTION(BlueprintCallable, Category="Beam|APIs|Accounts", meta=(AutoCreateRefTerm="OnSuccess,OnError,OnComplete"))
	void GetAvailableDeviceId(UGetAvailableDeviceIdRequest* Request, const FOnGetAvailableDeviceIdSuccess& OnSuccess, const FOnGetAvailableDeviceIdError& OnError, const FOnGetAvailableDeviceIdComplete& OnComplete,
								 int64& OutRequestId);

		
	/**
	 * @brief Makes a request to the Get /basic/accounts/available endpoint of the Accounts Service.
	 *
	 * @param Request The Request UObject. All (de)serialized data the request data creates is tied to the lifecycle of this object.
	 * @param OnSuccess What to do if the requests receives a successful response.
	 * @param OnError What to do if the request receives an error response.
	 * @param OnComplete What to after either OnSuccess or OnError have finished executing.
	 * @param OutRequestId The Request Id -- used to query information about the request or to cancel it while it's in flight. 
	 */
	UFUNCTION(BlueprintCallable, Category="Beam|APIs|Accounts", meta=(AutoCreateRefTerm="OnSuccess,OnError,OnComplete"))
	void GetAvailable(UGetAvailableRequest* Request, const FOnGetAvailableSuccess& OnSuccess, const FOnGetAvailableError& OnError, const FOnGetAvailableComplete& OnComplete,
								 int64& OutRequestId);

		
	/**
	 * @brief Makes a request to the Post /basic/accounts/password-update/confirm endpoint of the Accounts Service.
	 *
	 * @param Request The Request UObject. All (de)serialized data the request data creates is tied to the lifecycle of this object.
	 * @param OnSuccess What to do if the requests receives a successful response.
	 * @param OnError What to do if the request receives an error response.
	 * @param OnComplete What to after either OnSuccess or OnError have finished executing.
	 * @param OutRequestId The Request Id -- used to query information about the request or to cancel it while it's in flight. 
	 */
	UFUNCTION(BlueprintCallable, Category="Beam|APIs|Accounts", meta=(AutoCreateRefTerm="OnSuccess,OnError,OnComplete"))
	void PostPasswordUpdateConfirm(UPostPasswordUpdateConfirmRequest* Request, const FOnPostPasswordUpdateConfirmSuccess& OnSuccess, const FOnPostPasswordUpdateConfirmError& OnError, const FOnPostPasswordUpdateConfirmComplete& OnComplete,
								 int64& OutRequestId);

		
	/**
	 * @brief Makes a request to the Get /object/accounts/{objectId}/available-roles endpoint of the Accounts Service.
	 *
	 * @param Request The Request UObject. All (de)serialized data the request data creates is tied to the lifecycle of this object.
	 * @param OnSuccess What to do if the requests receives a successful response.
	 * @param OnError What to do if the request receives an error response.
	 * @param OnComplete What to after either OnSuccess or OnError have finished executing.
	 * @param OutRequestId The Request Id -- used to query information about the request or to cancel it while it's in flight. 
	 */
	UFUNCTION(BlueprintCallable, Category="Beam|APIs|Accounts", meta=(AutoCreateRefTerm="OnSuccess,OnError,OnComplete"))
	void GetAvailableRoles(UGetAvailableRolesRequest* Request, const FOnGetAvailableRolesSuccess& OnSuccess, const FOnGetAvailableRolesError& OnError, const FOnGetAvailableRolesComplete& OnComplete,
								 int64& OutRequestId);


	
	/**
	 * @brief Makes an authenticated request to the Delete /basic/accounts/me/device endpoint of the Accounts Service.
	 *
	 * @param UserSlot The authenticated UserSlot with the user making the request. 
	 * @param Request The Request UObject. All (de)serialized data the request data creates is tied to the lifecycle of this object.
	 * @param OnSuccess What to do if the requests receives a successful response.
	 * @param OnError What to do if the request receives an error response.
	 * @param OnComplete What to after either OnSuccess or OnError have finished executing.
	 * @param OutRequestId The Request Id -- used to query information about the request or to cancel it while it's in flight. 
	 */
	UFUNCTION(BlueprintCallable, Category="Beam|APIs|Accounts", meta=(AutoCreateRefTerm="UserSlot,OnSuccess,OnError,OnComplete"))
	void DeleteMeDevice(const FUserSlot& UserSlot, UDeleteMeDeviceRequest* Request, const FOnDeleteMeDeviceSuccess& OnSuccess, const FOnDeleteMeDeviceError& OnError, const FOnDeleteMeDeviceComplete& OnComplete, int64& OutRequestId);

		
	/**
	 * @brief Makes an authenticated request to the Get /basic/accounts/me endpoint of the Accounts Service.
	 *
	 * @param UserSlot The authenticated UserSlot with the user making the request. 
	 * @param Request The Request UObject. All (de)serialized data the request data creates is tied to the lifecycle of this object.
	 * @param OnSuccess What to do if the requests receives a successful response.
	 * @param OnError What to do if the request receives an error response.
	 * @param OnComplete What to after either OnSuccess or OnError have finished executing.
	 * @param OutRequestId The Request Id -- used to query information about the request or to cancel it while it's in flight. 
	 */
	UFUNCTION(BlueprintCallable, Category="Beam|APIs|Accounts", meta=(AutoCreateRefTerm="UserSlot,OnSuccess,OnError,OnComplete"))
	void GetMe(const FUserSlot& UserSlot, UBasicAccountsGetMeRequest* Request, const FOnBasicAccountsGetMeSuccess& OnSuccess, const FOnBasicAccountsGetMeError& OnError, const FOnBasicAccountsGetMeComplete& OnComplete, int64& OutRequestId);

		
	/**
	 * @brief Makes an authenticated request to the Put /basic/accounts/me endpoint of the Accounts Service.
	 *
	 * @param UserSlot The authenticated UserSlot with the user making the request. 
	 * @param Request The Request UObject. All (de)serialized data the request data creates is tied to the lifecycle of this object.
	 * @param OnSuccess What to do if the requests receives a successful response.
	 * @param OnError What to do if the request receives an error response.
	 * @param OnComplete What to after either OnSuccess or OnError have finished executing.
	 * @param OutRequestId The Request Id -- used to query information about the request or to cancel it while it's in flight. 
	 */
	UFUNCTION(BlueprintCallable, Category="Beam|APIs|Accounts", meta=(AutoCreateRefTerm="UserSlot,OnSuccess,OnError,OnComplete"))
	void PutMe(const FUserSlot& UserSlot, UPutMeRequest* Request, const FOnPutMeSuccess& OnSuccess, const FOnPutMeError& OnError, const FOnPutMeComplete& OnComplete, int64& OutRequestId);

		
	/**
	 * @brief Makes an authenticated request to the Delete /basic/accounts/me/third-party endpoint of the Accounts Service.
	 *
	 * @param UserSlot The authenticated UserSlot with the user making the request. 
	 * @param Request The Request UObject. All (de)serialized data the request data creates is tied to the lifecycle of this object.
	 * @param OnSuccess What to do if the requests receives a successful response.
	 * @param OnError What to do if the request receives an error response.
	 * @param OnComplete What to after either OnSuccess or OnError have finished executing.
	 * @param OutRequestId The Request Id -- used to query information about the request or to cancel it while it's in flight. 
	 */
	UFUNCTION(BlueprintCallable, Category="Beam|APIs|Accounts", meta=(AutoCreateRefTerm="UserSlot,OnSuccess,OnError,OnComplete"))
	void DeleteMeThirdParty(const FUserSlot& UserSlot, UDeleteMeThirdPartyRequest* Request, const FOnDeleteMeThirdPartySuccess& OnSuccess, const FOnDeleteMeThirdPartyError& OnError, const FOnDeleteMeThirdPartyComplete& OnComplete, int64& OutRequestId);

		
	/**
	 * @brief Makes an authenticated request to the Get /basic/accounts/search endpoint of the Accounts Service.
	 *
	 * @param UserSlot The authenticated UserSlot with the user making the request. 
	 * @param Request The Request UObject. All (de)serialized data the request data creates is tied to the lifecycle of this object.
	 * @param OnSuccess What to do if the requests receives a successful response.
	 * @param OnError What to do if the request receives an error response.
	 * @param OnComplete What to after either OnSuccess or OnError have finished executing.
	 * @param OutRequestId The Request Id -- used to query information about the request or to cancel it while it's in flight. 
	 */
	UFUNCTION(BlueprintCallable, Category="Beam|APIs|Accounts", meta=(AutoCreateRefTerm="UserSlot,OnSuccess,OnError,OnComplete"))
	void GetSearch(const FUserSlot& UserSlot, UBasicAccountsGetSearchRequest* Request, const FOnBasicAccountsGetSearchSuccess& OnSuccess, const FOnBasicAccountsGetSearchError& OnError, const FOnBasicAccountsGetSearchComplete& OnComplete, int64& OutRequestId);

		
	/**
	 * @brief Makes an authenticated request to the Post /basic/accounts/email-update/init endpoint of the Accounts Service.
	 *
	 * @param UserSlot The authenticated UserSlot with the user making the request. 
	 * @param Request The Request UObject. All (de)serialized data the request data creates is tied to the lifecycle of this object.
	 * @param OnSuccess What to do if the requests receives a successful response.
	 * @param OnError What to do if the request receives an error response.
	 * @param OnComplete What to after either OnSuccess or OnError have finished executing.
	 * @param OutRequestId The Request Id -- used to query information about the request or to cancel it while it's in flight. 
	 */
	UFUNCTION(BlueprintCallable, Category="Beam|APIs|Accounts", meta=(AutoCreateRefTerm="UserSlot,OnSuccess,OnError,OnComplete"))
	void PostEmailUpdateInit(const FUserSlot& UserSlot, UPostEmailUpdateInitRequest* Request, const FOnPostEmailUpdateInitSuccess& OnSuccess, const FOnPostEmailUpdateInitError& OnError, const FOnPostEmailUpdateInitComplete& OnComplete, int64& OutRequestId);

		
	/**
	 * @brief Makes an authenticated request to the Post /basic/accounts/email-update/confirm endpoint of the Accounts Service.
	 *
	 * @param UserSlot The authenticated UserSlot with the user making the request. 
	 * @param Request The Request UObject. All (de)serialized data the request data creates is tied to the lifecycle of this object.
	 * @param OnSuccess What to do if the requests receives a successful response.
	 * @param OnError What to do if the request receives an error response.
	 * @param OnComplete What to after either OnSuccess or OnError have finished executing.
	 * @param OutRequestId The Request Id -- used to query information about the request or to cancel it while it's in flight. 
	 */
	UFUNCTION(BlueprintCallable, Category="Beam|APIs|Accounts", meta=(AutoCreateRefTerm="UserSlot,OnSuccess,OnError,OnComplete"))
	void PostEmailUpdateConfirm(const FUserSlot& UserSlot, UPostEmailUpdateConfirmRequest* Request, const FOnPostEmailUpdateConfirmSuccess& OnSuccess, const FOnPostEmailUpdateConfirmError& OnError, const FOnPostEmailUpdateConfirmComplete& OnComplete, int64& OutRequestId);

		
	/**
	 * @brief Makes an authenticated request to the Post /basic/accounts/admin/admin-user endpoint of the Accounts Service.
	 *
	 * @param UserSlot The authenticated UserSlot with the user making the request. 
	 * @param Request The Request UObject. All (de)serialized data the request data creates is tied to the lifecycle of this object.
	 * @param OnSuccess What to do if the requests receives a successful response.
	 * @param OnError What to do if the request receives an error response.
	 * @param OnComplete What to after either OnSuccess or OnError have finished executing.
	 * @param OutRequestId The Request Id -- used to query information about the request or to cancel it while it's in flight. 
	 */
	UFUNCTION(BlueprintCallable, Category="Beam|APIs|Accounts", meta=(AutoCreateRefTerm="UserSlot,OnSuccess,OnError,OnComplete"))
	void PostAdminAdminUser(const FUserSlot& UserSlot, UPostAdminAdminUserRequest* Request, const FOnPostAdminAdminUserSuccess& OnSuccess, const FOnPostAdminAdminUserError& OnError, const FOnPostAdminAdminUserComplete& OnComplete, int64& OutRequestId);

		
	/**
	 * @brief Makes an authenticated request to the Post /basic/accounts/register endpoint of the Accounts Service.
	 *
	 * @param UserSlot The authenticated UserSlot with the user making the request. 
	 * @param Request The Request UObject. All (de)serialized data the request data creates is tied to the lifecycle of this object.
	 * @param OnSuccess What to do if the requests receives a successful response.
	 * @param OnError What to do if the request receives an error response.
	 * @param OnComplete What to after either OnSuccess or OnError have finished executing.
	 * @param OutRequestId The Request Id -- used to query information about the request or to cancel it while it's in flight. 
	 */
	UFUNCTION(BlueprintCallable, Category="Beam|APIs|Accounts", meta=(AutoCreateRefTerm="UserSlot,OnSuccess,OnError,OnComplete"))
	void PostRegister(const FUserSlot& UserSlot, UBasicAccountsPostRegisterRequest* Request, const FOnBasicAccountsPostRegisterSuccess& OnSuccess, const FOnBasicAccountsPostRegisterError& OnError, const FOnBasicAccountsPostRegisterComplete& OnComplete, int64& OutRequestId);

		
	/**
	 * @brief Makes an authenticated request to the Get /basic/accounts/admin/me endpoint of the Accounts Service.
	 *
	 * @param UserSlot The authenticated UserSlot with the user making the request. 
	 * @param Request The Request UObject. All (de)serialized data the request data creates is tied to the lifecycle of this object.
	 * @param OnSuccess What to do if the requests receives a successful response.
	 * @param OnError What to do if the request receives an error response.
	 * @param OnComplete What to after either OnSuccess or OnError have finished executing.
	 * @param OutRequestId The Request Id -- used to query information about the request or to cancel it while it's in flight. 
	 */
	UFUNCTION(BlueprintCallable, Category="Beam|APIs|Accounts", meta=(AutoCreateRefTerm="UserSlot,OnSuccess,OnError,OnComplete"))
	void GetAdminMe(const FUserSlot& UserSlot, UGetAdminMeRequest* Request, const FOnGetAdminMeSuccess& OnSuccess, const FOnGetAdminMeError& OnError, const FOnGetAdminMeComplete& OnComplete, int64& OutRequestId);

		
	/**
	 * @brief Makes an authenticated request to the Get /basic/accounts/admin/admin-users endpoint of the Accounts Service.
	 *
	 * @param UserSlot The authenticated UserSlot with the user making the request. 
	 * @param Request The Request UObject. All (de)serialized data the request data creates is tied to the lifecycle of this object.
	 * @param OnSuccess What to do if the requests receives a successful response.
	 * @param OnError What to do if the request receives an error response.
	 * @param OnComplete What to after either OnSuccess or OnError have finished executing.
	 * @param OutRequestId The Request Id -- used to query information about the request or to cancel it while it's in flight. 
	 */
	UFUNCTION(BlueprintCallable, Category="Beam|APIs|Accounts", meta=(AutoCreateRefTerm="UserSlot,OnSuccess,OnError,OnComplete"))
	void GetAdminAdminUsers(const FUserSlot& UserSlot, UGetAdminAdminUsersRequest* Request, const FOnGetAdminAdminUsersSuccess& OnSuccess, const FOnGetAdminAdminUsersError& OnError, const FOnGetAdminAdminUsersComplete& OnComplete, int64& OutRequestId);

		
	/**
	 * @brief Makes an authenticated request to the Get /basic/accounts/find endpoint of the Accounts Service.
	 *
	 * @param UserSlot The authenticated UserSlot with the user making the request. 
	 * @param Request The Request UObject. All (de)serialized data the request data creates is tied to the lifecycle of this object.
	 * @param OnSuccess What to do if the requests receives a successful response.
	 * @param OnError What to do if the request receives an error response.
	 * @param OnComplete What to after either OnSuccess or OnError have finished executing.
	 * @param OutRequestId The Request Id -- used to query information about the request or to cancel it while it's in flight. 
	 */
	UFUNCTION(BlueprintCallable, Category="Beam|APIs|Accounts", meta=(AutoCreateRefTerm="UserSlot,OnSuccess,OnError,OnComplete"))
	void GetFind(const FUserSlot& UserSlot, UGetFindRequest* Request, const FOnGetFindSuccess& OnSuccess, const FOnGetFindError& OnError, const FOnGetFindComplete& OnComplete, int64& OutRequestId);

		
	/**
	 * @brief Makes an authenticated request to the Put /object/accounts/{objectId}/admin/email endpoint of the Accounts Service.
	 *
	 * @param UserSlot The authenticated UserSlot with the user making the request. 
	 * @param Request The Request UObject. All (de)serialized data the request data creates is tied to the lifecycle of this object.
	 * @param OnSuccess What to do if the requests receives a successful response.
	 * @param OnError What to do if the request receives an error response.
	 * @param OnComplete What to after either OnSuccess or OnError have finished executing.
	 * @param OutRequestId The Request Id -- used to query information about the request or to cancel it while it's in flight. 
	 */
	UFUNCTION(BlueprintCallable, Category="Beam|APIs|Accounts", meta=(AutoCreateRefTerm="UserSlot,OnSuccess,OnError,OnComplete"))
	void PutAdminEmail(const FUserSlot& UserSlot, UPutAdminEmailRequest* Request, const FOnPutAdminEmailSuccess& OnSuccess, const FOnPutAdminEmailError& OnError, const FOnPutAdminEmailComplete& OnComplete, int64& OutRequestId);

		
	/**
	 * @brief Makes an authenticated request to the Get /object/accounts/{objectId}/role/report endpoint of the Accounts Service.
	 *
	 * @param UserSlot The authenticated UserSlot with the user making the request. 
	 * @param Request The Request UObject. All (de)serialized data the request data creates is tied to the lifecycle of this object.
	 * @param OnSuccess What to do if the requests receives a successful response.
	 * @param OnError What to do if the request receives an error response.
	 * @param OnComplete What to after either OnSuccess or OnError have finished executing.
	 * @param OutRequestId The Request Id -- used to query information about the request or to cancel it while it's in flight. 
	 */
	UFUNCTION(BlueprintCallable, Category="Beam|APIs|Accounts", meta=(AutoCreateRefTerm="UserSlot,OnSuccess,OnError,OnComplete"))
	void GetRoleReport(const FUserSlot& UserSlot, UGetRoleReportRequest* Request, const FOnGetRoleReportSuccess& OnSuccess, const FOnGetRoleReportError& OnError, const FOnGetRoleReportComplete& OnComplete, int64& OutRequestId);

		
	/**
	 * @brief Makes an authenticated request to the Put /object/accounts/{objectId}/role endpoint of the Accounts Service.
	 *
	 * @param UserSlot The authenticated UserSlot with the user making the request. 
	 * @param Request The Request UObject. All (de)serialized data the request data creates is tied to the lifecycle of this object.
	 * @param OnSuccess What to do if the requests receives a successful response.
	 * @param OnError What to do if the request receives an error response.
	 * @param OnComplete What to after either OnSuccess or OnError have finished executing.
	 * @param OutRequestId The Request Id -- used to query information about the request or to cancel it while it's in flight. 
	 */
	UFUNCTION(BlueprintCallable, Category="Beam|APIs|Accounts", meta=(AutoCreateRefTerm="UserSlot,OnSuccess,OnError,OnComplete"))
	void PutRole(const FUserSlot& UserSlot, UObjectAccountsPutRoleRequest* Request, const FOnObjectAccountsPutRoleSuccess& OnSuccess, const FOnObjectAccountsPutRoleError& OnError, const FOnObjectAccountsPutRoleComplete& OnComplete, int64& OutRequestId);

		
	/**
	 * @brief Makes an authenticated request to the Delete /object/accounts/{objectId}/role endpoint of the Accounts Service.
	 *
	 * @param UserSlot The authenticated UserSlot with the user making the request. 
	 * @param Request The Request UObject. All (de)serialized data the request data creates is tied to the lifecycle of this object.
	 * @param OnSuccess What to do if the requests receives a successful response.
	 * @param OnError What to do if the request receives an error response.
	 * @param OnComplete What to after either OnSuccess or OnError have finished executing.
	 * @param OutRequestId The Request Id -- used to query information about the request or to cancel it while it's in flight. 
	 */
	UFUNCTION(BlueprintCallable, Category="Beam|APIs|Accounts", meta=(AutoCreateRefTerm="UserSlot,OnSuccess,OnError,OnComplete"))
	void DeleteRole(const FUserSlot& UserSlot, UDeleteRoleRequest* Request, const FOnDeleteRoleSuccess& OnSuccess, const FOnDeleteRoleError& OnError, const FOnDeleteRoleComplete& OnComplete, int64& OutRequestId);

		
	/**
	 * @brief Makes an authenticated request to the Put /object/accounts/{objectId}/admin/scope endpoint of the Accounts Service.
	 *
	 * @param UserSlot The authenticated UserSlot with the user making the request. 
	 * @param Request The Request UObject. All (de)serialized data the request data creates is tied to the lifecycle of this object.
	 * @param OnSuccess What to do if the requests receives a successful response.
	 * @param OnError What to do if the request receives an error response.
	 * @param OnComplete What to after either OnSuccess or OnError have finished executing.
	 * @param OutRequestId The Request Id -- used to query information about the request or to cancel it while it's in flight. 
	 */
	UFUNCTION(BlueprintCallable, Category="Beam|APIs|Accounts", meta=(AutoCreateRefTerm="UserSlot,OnSuccess,OnError,OnComplete"))
	void PutAdminScope(const FUserSlot& UserSlot, UPutAdminScopeRequest* Request, const FOnPutAdminScopeSuccess& OnSuccess, const FOnPutAdminScopeError& OnError, const FOnPutAdminScopeComplete& OnComplete, int64& OutRequestId);

		
	/**
	 * @brief Makes an authenticated request to the Delete /object/accounts/{objectId}/admin/scope endpoint of the Accounts Service.
	 *
	 * @param UserSlot The authenticated UserSlot with the user making the request. 
	 * @param Request The Request UObject. All (de)serialized data the request data creates is tied to the lifecycle of this object.
	 * @param OnSuccess What to do if the requests receives a successful response.
	 * @param OnError What to do if the request receives an error response.
	 * @param OnComplete What to after either OnSuccess or OnError have finished executing.
	 * @param OutRequestId The Request Id -- used to query information about the request or to cancel it while it's in flight. 
	 */
	UFUNCTION(BlueprintCallable, Category="Beam|APIs|Accounts", meta=(AutoCreateRefTerm="UserSlot,OnSuccess,OnError,OnComplete"))
	void DeleteAdminScope(const FUserSlot& UserSlot, UDeleteAdminScopeRequest* Request, const FOnDeleteAdminScopeSuccess& OnSuccess, const FOnDeleteAdminScopeError& OnError, const FOnDeleteAdminScopeComplete& OnComplete, int64& OutRequestId);

		
	/**
	 * @brief Makes an authenticated request to the Put /object/accounts/{objectId}/admin/third-party endpoint of the Accounts Service.
	 *
	 * @param UserSlot The authenticated UserSlot with the user making the request. 
	 * @param Request The Request UObject. All (de)serialized data the request data creates is tied to the lifecycle of this object.
	 * @param OnSuccess What to do if the requests receives a successful response.
	 * @param OnError What to do if the request receives an error response.
	 * @param OnComplete What to after either OnSuccess or OnError have finished executing.
	 * @param OutRequestId The Request Id -- used to query information about the request or to cancel it while it's in flight. 
	 */
	UFUNCTION(BlueprintCallable, Category="Beam|APIs|Accounts", meta=(AutoCreateRefTerm="UserSlot,OnSuccess,OnError,OnComplete"))
	void PutAdminThirdParty(const FUserSlot& UserSlot, UPutAdminThirdPartyRequest* Request, const FOnPutAdminThirdPartySuccess& OnSuccess, const FOnPutAdminThirdPartyError& OnError, const FOnPutAdminThirdPartyComplete& OnComplete, int64& OutRequestId);

		
	/**
	 * @brief Makes an authenticated request to the Delete /object/accounts/{objectId}/admin/third-party endpoint of the Accounts Service.
	 *
	 * @param UserSlot The authenticated UserSlot with the user making the request. 
	 * @param Request The Request UObject. All (de)serialized data the request data creates is tied to the lifecycle of this object.
	 * @param OnSuccess What to do if the requests receives a successful response.
	 * @param OnError What to do if the request receives an error response.
	 * @param OnComplete What to after either OnSuccess or OnError have finished executing.
	 * @param OutRequestId The Request Id -- used to query information about the request or to cancel it while it's in flight. 
	 */
	UFUNCTION(BlueprintCallable, Category="Beam|APIs|Accounts", meta=(AutoCreateRefTerm="UserSlot,OnSuccess,OnError,OnComplete"))
	void DeleteAdminThirdParty(const FUserSlot& UserSlot, UDeleteAdminThirdPartyRequest* Request, const FOnDeleteAdminThirdPartySuccess& OnSuccess, const FOnDeleteAdminThirdPartyError& OnError, const FOnDeleteAdminThirdPartyComplete& OnComplete, int64& OutRequestId);

		
	/**
	 * @brief Makes an authenticated request to the Put /object/accounts/{objectId}/ endpoint of the Accounts Service.
	 *
	 * @param UserSlot The authenticated UserSlot with the user making the request. 
	 * @param Request The Request UObject. All (de)serialized data the request data creates is tied to the lifecycle of this object.
	 * @param OnSuccess What to do if the requests receives a successful response.
	 * @param OnError What to do if the request receives an error response.
	 * @param OnComplete What to after either OnSuccess or OnError have finished executing.
	 * @param OutRequestId The Request Id -- used to query information about the request or to cancel it while it's in flight. 
	 */
	UFUNCTION(BlueprintCallable, Category="Beam|APIs|Accounts", meta=(AutoCreateRefTerm="UserSlot,OnSuccess,OnError,OnComplete"))
	void PutAccounts(const FUserSlot& UserSlot, UPutAccountsRequest* Request, const FOnPutAccountsSuccess& OnSuccess, const FOnPutAccountsError& OnError, const FOnPutAccountsComplete& OnComplete, int64& OutRequestId);

		
	/**
	 * @brief Makes an authenticated request to the Delete /object/accounts/{objectId}/admin/forget endpoint of the Accounts Service.
	 *
	 * @param UserSlot The authenticated UserSlot with the user making the request. 
	 * @param Request The Request UObject. All (de)serialized data the request data creates is tied to the lifecycle of this object.
	 * @param OnSuccess What to do if the requests receives a successful response.
	 * @param OnError What to do if the request receives an error response.
	 * @param OnComplete What to after either OnSuccess or OnError have finished executing.
	 * @param OutRequestId The Request Id -- used to query information about the request or to cancel it while it's in flight. 
	 */
	UFUNCTION(BlueprintCallable, Category="Beam|APIs|Accounts", meta=(AutoCreateRefTerm="UserSlot,OnSuccess,OnError,OnComplete"))
	void DeleteAdminForget(const FUserSlot& UserSlot, UDeleteAdminForgetRequest* Request, const FOnDeleteAdminForgetSuccess& OnSuccess, const FOnDeleteAdminForgetError& OnError, const FOnDeleteAdminForgetComplete& OnComplete, int64& OutRequestId);
	
};
