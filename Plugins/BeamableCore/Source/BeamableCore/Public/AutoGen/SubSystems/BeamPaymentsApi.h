

#pragma once

#include "CoreMinimal.h"
#include "BeamBackend/BeamBackend.h"
#include "RequestTracker/BeamRequestTracker.h"

#include "Payments/PostWindowsPurchaseTrackRequest.h"
#include "Payments/GetAuditsRequest.h"
#include "Payments/PostWindowsPurchaseCompleteRequest.h"
#include "Payments/GetFacebookUpdateRequest.h"
#include "Payments/PostFacebookUpdateRequest.h"
#include "Payments/PostFacebookPurchaseCompleteRequest.h"
#include "Payments/PostTestPurchaseCompleteRequest.h"
#include "Payments/GetItunesProductRequest.h"
#include "Payments/PostGoogleplayPurchaseCompleteRequest.h"
#include "Payments/PostTestPurchaseTrackRequest.h"
#include "Payments/PostGoogleplayPurchaseVerifyRequest.h"
#include "Payments/PostCouponPurchaseTrackRequest.h"
#include "Payments/PostSteamPurchaseCompleteRequest.h"
#include "Payments/PostFacebookPurchaseTrackRequest.h"
#include "Payments/PostTestPurchaseVerifyRequest.h"
#include "Payments/PostGoogleplayPurchaseTrackRequest.h"
#include "Payments/GetSteamPricesRequest.h"
#include "Payments/PostWindowsPurchaseVerifyRequest.h"
#include "Payments/PostItunesPurchaseVerifyRequest.h"
#include "Payments/PostItunesPurchaseCompleteRequest.h"
#include "Payments/PostFacebookPurchaseVerifyRequest.h"
#include "Payments/PostSteamPurchaseTrackRequest.h"
#include "Payments/PostCouponPurchaseVerifyRequest.h"
#include "Payments/GetWindowsProductRequest.h"
#include "Payments/GetFacebookProductRequest.h"
#include "Payments/GetCouponProductRequest.h"
#include "Payments/GetSteamProductsRequest.h"
#include "Payments/PostSteamAuthRequest.h"
#include "Payments/GetSteamProductRequest.h"
#include "Payments/PostCouponPurchaseCompleteRequest.h"
#include "Payments/GetGoogleplayProductRequest.h"
#include "Payments/GetTestProductRequest.h"
#include "Payments/PostSteamPurchaseVerifyRequest.h"
#include "Payments/PostItunesPurchaseTrackRequest.h"
#include "Payments/GetPaymentsRequest.h"
#include "Payments/PostTestPurchaseBeginRequest.h"
#include "Payments/PostSteamPurchaseFailRequest.h"
#include "Payments/PostFacebookPurchaseFailRequest.h"
#include "Payments/PostGoogleplayPurchaseBeginRequest.h"
#include "Payments/PostItunesPurchaseBeginRequest.h"
#include "Payments/PostFacebookPurchaseCancelRequest.h"
#include "Payments/PostItunesPurchaseFailRequest.h"
#include "Payments/PostTestPurchaseCancelRequest.h"
#include "Payments/PostTestPurchaseFailRequest.h"
#include "Payments/PostCouponPurchaseCancelRequest.h"
#include "Payments/PostCouponPurchaseBeginRequest.h"
#include "Payments/PostFacebookPurchaseBeginRequest.h"
#include "Payments/GetSteamOrderRequest.h"
#include "Payments/PostWindowsPurchaseBeginRequest.h"
#include "Payments/PostGoogleplayPurchaseFailRequest.h"
#include "Payments/PostGoogleplayPurchaseCancelRequest.h"
#include "Payments/PostCouponPurchaseFailRequest.h"
#include "Payments/PostSteamPurchaseBeginRequest.h"
#include "Payments/PostSteamPurchaseCancelRequest.h"
#include "Payments/PostWindowsPurchaseCancelRequest.h"
#include "Payments/PostWindowsPurchaseFailRequest.h"
#include "Payments/PostItunesPurchaseCancelRequest.h"

#include "BeamPaymentsApi.generated.h"


/**
 * Subsystem containing request calls for the Payments service.
 */
UCLASS(NotBlueprintType)
class BEAMABLECORE_API UBeamPaymentsApi : public UEngineSubsystem
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

	
	/**
	 * @brief Private implementation that all overloaded BP UFunctions call.	  
	 */
	void BP_PostWindowsPurchaseTrackImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, FBeamConnectivity& ConnectivityStatus, UPostWindowsPurchaseTrackRequest* RequestData,
	                                const FOnPostWindowsPurchaseTrackSuccess& OnSuccess, const FOnPostWindowsPurchaseTrackError& OnError, const FOnPostWindowsPurchaseTrackComplete& OnComplete,
	                                int64& OutRequestId, FBeamOperationHandle OpHandle = FBeamOperationHandle()) const;
	/**
	 * @brief Overload version for binding lambdas when in C++ land. Prefer the BP version whenever possible, this is here mostly for quick experimentation purposes.	 
	 */
	void CPP_PostWindowsPurchaseTrackImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, FBeamConnectivity& ConnectivityStatus, UPostWindowsPurchaseTrackRequest* RequestData,
	                                 const FOnPostWindowsPurchaseTrackFullResponse& Handler, int64& OutRequestId, FBeamOperationHandle OpHandle = FBeamOperationHandle()) const;

		
	/**
	 * @brief Private implementation that all overloaded BP UFunctions call.	  
	 */
	void BP_GetAuditsImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, FBeamConnectivity& ConnectivityStatus, UGetAuditsRequest* RequestData,
	                                const FOnGetAuditsSuccess& OnSuccess, const FOnGetAuditsError& OnError, const FOnGetAuditsComplete& OnComplete,
	                                int64& OutRequestId, FBeamOperationHandle OpHandle = FBeamOperationHandle()) const;
	/**
	 * @brief Overload version for binding lambdas when in C++ land. Prefer the BP version whenever possible, this is here mostly for quick experimentation purposes.	 
	 */
	void CPP_GetAuditsImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, FBeamConnectivity& ConnectivityStatus, UGetAuditsRequest* RequestData,
	                                 const FOnGetAuditsFullResponse& Handler, int64& OutRequestId, FBeamOperationHandle OpHandle = FBeamOperationHandle()) const;

		
	/**
	 * @brief Private implementation that all overloaded BP UFunctions call.	  
	 */
	void BP_PostWindowsPurchaseCompleteImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, FBeamConnectivity& ConnectivityStatus, UPostWindowsPurchaseCompleteRequest* RequestData,
	                                const FOnPostWindowsPurchaseCompleteSuccess& OnSuccess, const FOnPostWindowsPurchaseCompleteError& OnError, const FOnPostWindowsPurchaseCompleteComplete& OnComplete,
	                                int64& OutRequestId, FBeamOperationHandle OpHandle = FBeamOperationHandle()) const;
	/**
	 * @brief Overload version for binding lambdas when in C++ land. Prefer the BP version whenever possible, this is here mostly for quick experimentation purposes.	 
	 */
	void CPP_PostWindowsPurchaseCompleteImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, FBeamConnectivity& ConnectivityStatus, UPostWindowsPurchaseCompleteRequest* RequestData,
	                                 const FOnPostWindowsPurchaseCompleteFullResponse& Handler, int64& OutRequestId, FBeamOperationHandle OpHandle = FBeamOperationHandle()) const;

		
	/**
	 * @brief Private implementation that all overloaded BP UFunctions call.	  
	 */
	void BP_GetFacebookUpdateImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, FBeamConnectivity& ConnectivityStatus, UGetFacebookUpdateRequest* RequestData,
	                                const FOnGetFacebookUpdateSuccess& OnSuccess, const FOnGetFacebookUpdateError& OnError, const FOnGetFacebookUpdateComplete& OnComplete,
	                                int64& OutRequestId, FBeamOperationHandle OpHandle = FBeamOperationHandle()) const;
	/**
	 * @brief Overload version for binding lambdas when in C++ land. Prefer the BP version whenever possible, this is here mostly for quick experimentation purposes.	 
	 */
	void CPP_GetFacebookUpdateImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, FBeamConnectivity& ConnectivityStatus, UGetFacebookUpdateRequest* RequestData,
	                                 const FOnGetFacebookUpdateFullResponse& Handler, int64& OutRequestId, FBeamOperationHandle OpHandle = FBeamOperationHandle()) const;

		
	/**
	 * @brief Private implementation that all overloaded BP UFunctions call.	  
	 */
	void BP_PostFacebookUpdateImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, FBeamConnectivity& ConnectivityStatus, UPostFacebookUpdateRequest* RequestData,
	                                const FOnPostFacebookUpdateSuccess& OnSuccess, const FOnPostFacebookUpdateError& OnError, const FOnPostFacebookUpdateComplete& OnComplete,
	                                int64& OutRequestId, FBeamOperationHandle OpHandle = FBeamOperationHandle()) const;
	/**
	 * @brief Overload version for binding lambdas when in C++ land. Prefer the BP version whenever possible, this is here mostly for quick experimentation purposes.	 
	 */
	void CPP_PostFacebookUpdateImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, FBeamConnectivity& ConnectivityStatus, UPostFacebookUpdateRequest* RequestData,
	                                 const FOnPostFacebookUpdateFullResponse& Handler, int64& OutRequestId, FBeamOperationHandle OpHandle = FBeamOperationHandle()) const;

		
	/**
	 * @brief Private implementation that all overloaded BP UFunctions call.	  
	 */
	void BP_PostFacebookPurchaseCompleteImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, FBeamConnectivity& ConnectivityStatus, UPostFacebookPurchaseCompleteRequest* RequestData,
	                                const FOnPostFacebookPurchaseCompleteSuccess& OnSuccess, const FOnPostFacebookPurchaseCompleteError& OnError, const FOnPostFacebookPurchaseCompleteComplete& OnComplete,
	                                int64& OutRequestId, FBeamOperationHandle OpHandle = FBeamOperationHandle()) const;
	/**
	 * @brief Overload version for binding lambdas when in C++ land. Prefer the BP version whenever possible, this is here mostly for quick experimentation purposes.	 
	 */
	void CPP_PostFacebookPurchaseCompleteImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, FBeamConnectivity& ConnectivityStatus, UPostFacebookPurchaseCompleteRequest* RequestData,
	                                 const FOnPostFacebookPurchaseCompleteFullResponse& Handler, int64& OutRequestId, FBeamOperationHandle OpHandle = FBeamOperationHandle()) const;

		
	/**
	 * @brief Private implementation that all overloaded BP UFunctions call.	  
	 */
	void BP_PostTestPurchaseCompleteImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, FBeamConnectivity& ConnectivityStatus, UPostTestPurchaseCompleteRequest* RequestData,
	                                const FOnPostTestPurchaseCompleteSuccess& OnSuccess, const FOnPostTestPurchaseCompleteError& OnError, const FOnPostTestPurchaseCompleteComplete& OnComplete,
	                                int64& OutRequestId, FBeamOperationHandle OpHandle = FBeamOperationHandle()) const;
	/**
	 * @brief Overload version for binding lambdas when in C++ land. Prefer the BP version whenever possible, this is here mostly for quick experimentation purposes.	 
	 */
	void CPP_PostTestPurchaseCompleteImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, FBeamConnectivity& ConnectivityStatus, UPostTestPurchaseCompleteRequest* RequestData,
	                                 const FOnPostTestPurchaseCompleteFullResponse& Handler, int64& OutRequestId, FBeamOperationHandle OpHandle = FBeamOperationHandle()) const;

		
	/**
	 * @brief Private implementation that all overloaded BP UFunctions call.	  
	 */
	void BP_GetItunesProductImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, FBeamConnectivity& ConnectivityStatus, UGetItunesProductRequest* RequestData,
	                                const FOnGetItunesProductSuccess& OnSuccess, const FOnGetItunesProductError& OnError, const FOnGetItunesProductComplete& OnComplete,
	                                int64& OutRequestId, FBeamOperationHandle OpHandle = FBeamOperationHandle()) const;
	/**
	 * @brief Overload version for binding lambdas when in C++ land. Prefer the BP version whenever possible, this is here mostly for quick experimentation purposes.	 
	 */
	void CPP_GetItunesProductImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, FBeamConnectivity& ConnectivityStatus, UGetItunesProductRequest* RequestData,
	                                 const FOnGetItunesProductFullResponse& Handler, int64& OutRequestId, FBeamOperationHandle OpHandle = FBeamOperationHandle()) const;

		
	/**
	 * @brief Private implementation that all overloaded BP UFunctions call.	  
	 */
	void BP_PostGoogleplayPurchaseCompleteImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, FBeamConnectivity& ConnectivityStatus, UPostGoogleplayPurchaseCompleteRequest* RequestData,
	                                const FOnPostGoogleplayPurchaseCompleteSuccess& OnSuccess, const FOnPostGoogleplayPurchaseCompleteError& OnError, const FOnPostGoogleplayPurchaseCompleteComplete& OnComplete,
	                                int64& OutRequestId, FBeamOperationHandle OpHandle = FBeamOperationHandle()) const;
	/**
	 * @brief Overload version for binding lambdas when in C++ land. Prefer the BP version whenever possible, this is here mostly for quick experimentation purposes.	 
	 */
	void CPP_PostGoogleplayPurchaseCompleteImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, FBeamConnectivity& ConnectivityStatus, UPostGoogleplayPurchaseCompleteRequest* RequestData,
	                                 const FOnPostGoogleplayPurchaseCompleteFullResponse& Handler, int64& OutRequestId, FBeamOperationHandle OpHandle = FBeamOperationHandle()) const;

		
	/**
	 * @brief Private implementation that all overloaded BP UFunctions call.	  
	 */
	void BP_PostTestPurchaseTrackImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, FBeamConnectivity& ConnectivityStatus, UPostTestPurchaseTrackRequest* RequestData,
	                                const FOnPostTestPurchaseTrackSuccess& OnSuccess, const FOnPostTestPurchaseTrackError& OnError, const FOnPostTestPurchaseTrackComplete& OnComplete,
	                                int64& OutRequestId, FBeamOperationHandle OpHandle = FBeamOperationHandle()) const;
	/**
	 * @brief Overload version for binding lambdas when in C++ land. Prefer the BP version whenever possible, this is here mostly for quick experimentation purposes.	 
	 */
	void CPP_PostTestPurchaseTrackImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, FBeamConnectivity& ConnectivityStatus, UPostTestPurchaseTrackRequest* RequestData,
	                                 const FOnPostTestPurchaseTrackFullResponse& Handler, int64& OutRequestId, FBeamOperationHandle OpHandle = FBeamOperationHandle()) const;

		
	/**
	 * @brief Private implementation that all overloaded BP UFunctions call.	  
	 */
	void BP_PostGoogleplayPurchaseVerifyImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, FBeamConnectivity& ConnectivityStatus, UPostGoogleplayPurchaseVerifyRequest* RequestData,
	                                const FOnPostGoogleplayPurchaseVerifySuccess& OnSuccess, const FOnPostGoogleplayPurchaseVerifyError& OnError, const FOnPostGoogleplayPurchaseVerifyComplete& OnComplete,
	                                int64& OutRequestId, FBeamOperationHandle OpHandle = FBeamOperationHandle()) const;
	/**
	 * @brief Overload version for binding lambdas when in C++ land. Prefer the BP version whenever possible, this is here mostly for quick experimentation purposes.	 
	 */
	void CPP_PostGoogleplayPurchaseVerifyImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, FBeamConnectivity& ConnectivityStatus, UPostGoogleplayPurchaseVerifyRequest* RequestData,
	                                 const FOnPostGoogleplayPurchaseVerifyFullResponse& Handler, int64& OutRequestId, FBeamOperationHandle OpHandle = FBeamOperationHandle()) const;

		
	/**
	 * @brief Private implementation that all overloaded BP UFunctions call.	  
	 */
	void BP_PostCouponPurchaseTrackImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, FBeamConnectivity& ConnectivityStatus, UPostCouponPurchaseTrackRequest* RequestData,
	                                const FOnPostCouponPurchaseTrackSuccess& OnSuccess, const FOnPostCouponPurchaseTrackError& OnError, const FOnPostCouponPurchaseTrackComplete& OnComplete,
	                                int64& OutRequestId, FBeamOperationHandle OpHandle = FBeamOperationHandle()) const;
	/**
	 * @brief Overload version for binding lambdas when in C++ land. Prefer the BP version whenever possible, this is here mostly for quick experimentation purposes.	 
	 */
	void CPP_PostCouponPurchaseTrackImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, FBeamConnectivity& ConnectivityStatus, UPostCouponPurchaseTrackRequest* RequestData,
	                                 const FOnPostCouponPurchaseTrackFullResponse& Handler, int64& OutRequestId, FBeamOperationHandle OpHandle = FBeamOperationHandle()) const;

		
	/**
	 * @brief Private implementation that all overloaded BP UFunctions call.	  
	 */
	void BP_PostSteamPurchaseCompleteImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, FBeamConnectivity& ConnectivityStatus, UPostSteamPurchaseCompleteRequest* RequestData,
	                                const FOnPostSteamPurchaseCompleteSuccess& OnSuccess, const FOnPostSteamPurchaseCompleteError& OnError, const FOnPostSteamPurchaseCompleteComplete& OnComplete,
	                                int64& OutRequestId, FBeamOperationHandle OpHandle = FBeamOperationHandle()) const;
	/**
	 * @brief Overload version for binding lambdas when in C++ land. Prefer the BP version whenever possible, this is here mostly for quick experimentation purposes.	 
	 */
	void CPP_PostSteamPurchaseCompleteImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, FBeamConnectivity& ConnectivityStatus, UPostSteamPurchaseCompleteRequest* RequestData,
	                                 const FOnPostSteamPurchaseCompleteFullResponse& Handler, int64& OutRequestId, FBeamOperationHandle OpHandle = FBeamOperationHandle()) const;

		
	/**
	 * @brief Private implementation that all overloaded BP UFunctions call.	  
	 */
	void BP_PostFacebookPurchaseTrackImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, FBeamConnectivity& ConnectivityStatus, UPostFacebookPurchaseTrackRequest* RequestData,
	                                const FOnPostFacebookPurchaseTrackSuccess& OnSuccess, const FOnPostFacebookPurchaseTrackError& OnError, const FOnPostFacebookPurchaseTrackComplete& OnComplete,
	                                int64& OutRequestId, FBeamOperationHandle OpHandle = FBeamOperationHandle()) const;
	/**
	 * @brief Overload version for binding lambdas when in C++ land. Prefer the BP version whenever possible, this is here mostly for quick experimentation purposes.	 
	 */
	void CPP_PostFacebookPurchaseTrackImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, FBeamConnectivity& ConnectivityStatus, UPostFacebookPurchaseTrackRequest* RequestData,
	                                 const FOnPostFacebookPurchaseTrackFullResponse& Handler, int64& OutRequestId, FBeamOperationHandle OpHandle = FBeamOperationHandle()) const;

		
	/**
	 * @brief Private implementation that all overloaded BP UFunctions call.	  
	 */
	void BP_PostTestPurchaseVerifyImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, FBeamConnectivity& ConnectivityStatus, UPostTestPurchaseVerifyRequest* RequestData,
	                                const FOnPostTestPurchaseVerifySuccess& OnSuccess, const FOnPostTestPurchaseVerifyError& OnError, const FOnPostTestPurchaseVerifyComplete& OnComplete,
	                                int64& OutRequestId, FBeamOperationHandle OpHandle = FBeamOperationHandle()) const;
	/**
	 * @brief Overload version for binding lambdas when in C++ land. Prefer the BP version whenever possible, this is here mostly for quick experimentation purposes.	 
	 */
	void CPP_PostTestPurchaseVerifyImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, FBeamConnectivity& ConnectivityStatus, UPostTestPurchaseVerifyRequest* RequestData,
	                                 const FOnPostTestPurchaseVerifyFullResponse& Handler, int64& OutRequestId, FBeamOperationHandle OpHandle = FBeamOperationHandle()) const;

		
	/**
	 * @brief Private implementation that all overloaded BP UFunctions call.	  
	 */
	void BP_PostGoogleplayPurchaseTrackImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, FBeamConnectivity& ConnectivityStatus, UPostGoogleplayPurchaseTrackRequest* RequestData,
	                                const FOnPostGoogleplayPurchaseTrackSuccess& OnSuccess, const FOnPostGoogleplayPurchaseTrackError& OnError, const FOnPostGoogleplayPurchaseTrackComplete& OnComplete,
	                                int64& OutRequestId, FBeamOperationHandle OpHandle = FBeamOperationHandle()) const;
	/**
	 * @brief Overload version for binding lambdas when in C++ land. Prefer the BP version whenever possible, this is here mostly for quick experimentation purposes.	 
	 */
	void CPP_PostGoogleplayPurchaseTrackImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, FBeamConnectivity& ConnectivityStatus, UPostGoogleplayPurchaseTrackRequest* RequestData,
	                                 const FOnPostGoogleplayPurchaseTrackFullResponse& Handler, int64& OutRequestId, FBeamOperationHandle OpHandle = FBeamOperationHandle()) const;

		
	/**
	 * @brief Private implementation that all overloaded BP UFunctions call.	  
	 */
	void BP_GetSteamPricesImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, FBeamConnectivity& ConnectivityStatus, UGetSteamPricesRequest* RequestData,
	                                const FOnGetSteamPricesSuccess& OnSuccess, const FOnGetSteamPricesError& OnError, const FOnGetSteamPricesComplete& OnComplete,
	                                int64& OutRequestId, FBeamOperationHandle OpHandle = FBeamOperationHandle()) const;
	/**
	 * @brief Overload version for binding lambdas when in C++ land. Prefer the BP version whenever possible, this is here mostly for quick experimentation purposes.	 
	 */
	void CPP_GetSteamPricesImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, FBeamConnectivity& ConnectivityStatus, UGetSteamPricesRequest* RequestData,
	                                 const FOnGetSteamPricesFullResponse& Handler, int64& OutRequestId, FBeamOperationHandle OpHandle = FBeamOperationHandle()) const;

		
	/**
	 * @brief Private implementation that all overloaded BP UFunctions call.	  
	 */
	void BP_PostWindowsPurchaseVerifyImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, FBeamConnectivity& ConnectivityStatus, UPostWindowsPurchaseVerifyRequest* RequestData,
	                                const FOnPostWindowsPurchaseVerifySuccess& OnSuccess, const FOnPostWindowsPurchaseVerifyError& OnError, const FOnPostWindowsPurchaseVerifyComplete& OnComplete,
	                                int64& OutRequestId, FBeamOperationHandle OpHandle = FBeamOperationHandle()) const;
	/**
	 * @brief Overload version for binding lambdas when in C++ land. Prefer the BP version whenever possible, this is here mostly for quick experimentation purposes.	 
	 */
	void CPP_PostWindowsPurchaseVerifyImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, FBeamConnectivity& ConnectivityStatus, UPostWindowsPurchaseVerifyRequest* RequestData,
	                                 const FOnPostWindowsPurchaseVerifyFullResponse& Handler, int64& OutRequestId, FBeamOperationHandle OpHandle = FBeamOperationHandle()) const;

		
	/**
	 * @brief Private implementation that all overloaded BP UFunctions call.	  
	 */
	void BP_PostItunesPurchaseVerifyImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, FBeamConnectivity& ConnectivityStatus, UPostItunesPurchaseVerifyRequest* RequestData,
	                                const FOnPostItunesPurchaseVerifySuccess& OnSuccess, const FOnPostItunesPurchaseVerifyError& OnError, const FOnPostItunesPurchaseVerifyComplete& OnComplete,
	                                int64& OutRequestId, FBeamOperationHandle OpHandle = FBeamOperationHandle()) const;
	/**
	 * @brief Overload version for binding lambdas when in C++ land. Prefer the BP version whenever possible, this is here mostly for quick experimentation purposes.	 
	 */
	void CPP_PostItunesPurchaseVerifyImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, FBeamConnectivity& ConnectivityStatus, UPostItunesPurchaseVerifyRequest* RequestData,
	                                 const FOnPostItunesPurchaseVerifyFullResponse& Handler, int64& OutRequestId, FBeamOperationHandle OpHandle = FBeamOperationHandle()) const;

		
	/**
	 * @brief Private implementation that all overloaded BP UFunctions call.	  
	 */
	void BP_PostItunesPurchaseCompleteImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, FBeamConnectivity& ConnectivityStatus, UPostItunesPurchaseCompleteRequest* RequestData,
	                                const FOnPostItunesPurchaseCompleteSuccess& OnSuccess, const FOnPostItunesPurchaseCompleteError& OnError, const FOnPostItunesPurchaseCompleteComplete& OnComplete,
	                                int64& OutRequestId, FBeamOperationHandle OpHandle = FBeamOperationHandle()) const;
	/**
	 * @brief Overload version for binding lambdas when in C++ land. Prefer the BP version whenever possible, this is here mostly for quick experimentation purposes.	 
	 */
	void CPP_PostItunesPurchaseCompleteImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, FBeamConnectivity& ConnectivityStatus, UPostItunesPurchaseCompleteRequest* RequestData,
	                                 const FOnPostItunesPurchaseCompleteFullResponse& Handler, int64& OutRequestId, FBeamOperationHandle OpHandle = FBeamOperationHandle()) const;

		
	/**
	 * @brief Private implementation that all overloaded BP UFunctions call.	  
	 */
	void BP_PostFacebookPurchaseVerifyImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, FBeamConnectivity& ConnectivityStatus, UPostFacebookPurchaseVerifyRequest* RequestData,
	                                const FOnPostFacebookPurchaseVerifySuccess& OnSuccess, const FOnPostFacebookPurchaseVerifyError& OnError, const FOnPostFacebookPurchaseVerifyComplete& OnComplete,
	                                int64& OutRequestId, FBeamOperationHandle OpHandle = FBeamOperationHandle()) const;
	/**
	 * @brief Overload version for binding lambdas when in C++ land. Prefer the BP version whenever possible, this is here mostly for quick experimentation purposes.	 
	 */
	void CPP_PostFacebookPurchaseVerifyImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, FBeamConnectivity& ConnectivityStatus, UPostFacebookPurchaseVerifyRequest* RequestData,
	                                 const FOnPostFacebookPurchaseVerifyFullResponse& Handler, int64& OutRequestId, FBeamOperationHandle OpHandle = FBeamOperationHandle()) const;

		
	/**
	 * @brief Private implementation that all overloaded BP UFunctions call.	  
	 */
	void BP_PostSteamPurchaseTrackImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, FBeamConnectivity& ConnectivityStatus, UPostSteamPurchaseTrackRequest* RequestData,
	                                const FOnPostSteamPurchaseTrackSuccess& OnSuccess, const FOnPostSteamPurchaseTrackError& OnError, const FOnPostSteamPurchaseTrackComplete& OnComplete,
	                                int64& OutRequestId, FBeamOperationHandle OpHandle = FBeamOperationHandle()) const;
	/**
	 * @brief Overload version for binding lambdas when in C++ land. Prefer the BP version whenever possible, this is here mostly for quick experimentation purposes.	 
	 */
	void CPP_PostSteamPurchaseTrackImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, FBeamConnectivity& ConnectivityStatus, UPostSteamPurchaseTrackRequest* RequestData,
	                                 const FOnPostSteamPurchaseTrackFullResponse& Handler, int64& OutRequestId, FBeamOperationHandle OpHandle = FBeamOperationHandle()) const;

		
	/**
	 * @brief Private implementation that all overloaded BP UFunctions call.	  
	 */
	void BP_PostCouponPurchaseVerifyImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, FBeamConnectivity& ConnectivityStatus, UPostCouponPurchaseVerifyRequest* RequestData,
	                                const FOnPostCouponPurchaseVerifySuccess& OnSuccess, const FOnPostCouponPurchaseVerifyError& OnError, const FOnPostCouponPurchaseVerifyComplete& OnComplete,
	                                int64& OutRequestId, FBeamOperationHandle OpHandle = FBeamOperationHandle()) const;
	/**
	 * @brief Overload version for binding lambdas when in C++ land. Prefer the BP version whenever possible, this is here mostly for quick experimentation purposes.	 
	 */
	void CPP_PostCouponPurchaseVerifyImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, FBeamConnectivity& ConnectivityStatus, UPostCouponPurchaseVerifyRequest* RequestData,
	                                 const FOnPostCouponPurchaseVerifyFullResponse& Handler, int64& OutRequestId, FBeamOperationHandle OpHandle = FBeamOperationHandle()) const;

		
	/**
	 * @brief Private implementation that all overloaded BP UFunctions call.	  
	 */
	void BP_GetWindowsProductImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, FBeamConnectivity& ConnectivityStatus, UGetWindowsProductRequest* RequestData,
	                                const FOnGetWindowsProductSuccess& OnSuccess, const FOnGetWindowsProductError& OnError, const FOnGetWindowsProductComplete& OnComplete,
	                                int64& OutRequestId, FBeamOperationHandle OpHandle = FBeamOperationHandle()) const;
	/**
	 * @brief Overload version for binding lambdas when in C++ land. Prefer the BP version whenever possible, this is here mostly for quick experimentation purposes.	 
	 */
	void CPP_GetWindowsProductImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, FBeamConnectivity& ConnectivityStatus, UGetWindowsProductRequest* RequestData,
	                                 const FOnGetWindowsProductFullResponse& Handler, int64& OutRequestId, FBeamOperationHandle OpHandle = FBeamOperationHandle()) const;

		
	/**
	 * @brief Private implementation that all overloaded BP UFunctions call.	  
	 */
	void BP_GetFacebookProductImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, FBeamConnectivity& ConnectivityStatus, UGetFacebookProductRequest* RequestData,
	                                const FOnGetFacebookProductSuccess& OnSuccess, const FOnGetFacebookProductError& OnError, const FOnGetFacebookProductComplete& OnComplete,
	                                int64& OutRequestId, FBeamOperationHandle OpHandle = FBeamOperationHandle()) const;
	/**
	 * @brief Overload version for binding lambdas when in C++ land. Prefer the BP version whenever possible, this is here mostly for quick experimentation purposes.	 
	 */
	void CPP_GetFacebookProductImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, FBeamConnectivity& ConnectivityStatus, UGetFacebookProductRequest* RequestData,
	                                 const FOnGetFacebookProductFullResponse& Handler, int64& OutRequestId, FBeamOperationHandle OpHandle = FBeamOperationHandle()) const;

		
	/**
	 * @brief Private implementation that all overloaded BP UFunctions call.	  
	 */
	void BP_GetCouponProductImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, FBeamConnectivity& ConnectivityStatus, UGetCouponProductRequest* RequestData,
	                                const FOnGetCouponProductSuccess& OnSuccess, const FOnGetCouponProductError& OnError, const FOnGetCouponProductComplete& OnComplete,
	                                int64& OutRequestId, FBeamOperationHandle OpHandle = FBeamOperationHandle()) const;
	/**
	 * @brief Overload version for binding lambdas when in C++ land. Prefer the BP version whenever possible, this is here mostly for quick experimentation purposes.	 
	 */
	void CPP_GetCouponProductImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, FBeamConnectivity& ConnectivityStatus, UGetCouponProductRequest* RequestData,
	                                 const FOnGetCouponProductFullResponse& Handler, int64& OutRequestId, FBeamOperationHandle OpHandle = FBeamOperationHandle()) const;

		
	/**
	 * @brief Private implementation that all overloaded BP UFunctions call.	  
	 */
	void BP_GetSteamProductsImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, FBeamConnectivity& ConnectivityStatus, UGetSteamProductsRequest* RequestData,
	                                const FOnGetSteamProductsSuccess& OnSuccess, const FOnGetSteamProductsError& OnError, const FOnGetSteamProductsComplete& OnComplete,
	                                int64& OutRequestId, FBeamOperationHandle OpHandle = FBeamOperationHandle()) const;
	/**
	 * @brief Overload version for binding lambdas when in C++ land. Prefer the BP version whenever possible, this is here mostly for quick experimentation purposes.	 
	 */
	void CPP_GetSteamProductsImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, FBeamConnectivity& ConnectivityStatus, UGetSteamProductsRequest* RequestData,
	                                 const FOnGetSteamProductsFullResponse& Handler, int64& OutRequestId, FBeamOperationHandle OpHandle = FBeamOperationHandle()) const;

		
	/**
	 * @brief Private implementation that all overloaded BP UFunctions call.	  
	 */
	void BP_PostSteamAuthImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, FBeamConnectivity& ConnectivityStatus, UPostSteamAuthRequest* RequestData,
	                                const FOnPostSteamAuthSuccess& OnSuccess, const FOnPostSteamAuthError& OnError, const FOnPostSteamAuthComplete& OnComplete,
	                                int64& OutRequestId, FBeamOperationHandle OpHandle = FBeamOperationHandle()) const;
	/**
	 * @brief Overload version for binding lambdas when in C++ land. Prefer the BP version whenever possible, this is here mostly for quick experimentation purposes.	 
	 */
	void CPP_PostSteamAuthImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, FBeamConnectivity& ConnectivityStatus, UPostSteamAuthRequest* RequestData,
	                                 const FOnPostSteamAuthFullResponse& Handler, int64& OutRequestId, FBeamOperationHandle OpHandle = FBeamOperationHandle()) const;

		
	/**
	 * @brief Private implementation that all overloaded BP UFunctions call.	  
	 */
	void BP_GetSteamProductImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, FBeamConnectivity& ConnectivityStatus, UGetSteamProductRequest* RequestData,
	                                const FOnGetSteamProductSuccess& OnSuccess, const FOnGetSteamProductError& OnError, const FOnGetSteamProductComplete& OnComplete,
	                                int64& OutRequestId, FBeamOperationHandle OpHandle = FBeamOperationHandle()) const;
	/**
	 * @brief Overload version for binding lambdas when in C++ land. Prefer the BP version whenever possible, this is here mostly for quick experimentation purposes.	 
	 */
	void CPP_GetSteamProductImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, FBeamConnectivity& ConnectivityStatus, UGetSteamProductRequest* RequestData,
	                                 const FOnGetSteamProductFullResponse& Handler, int64& OutRequestId, FBeamOperationHandle OpHandle = FBeamOperationHandle()) const;

		
	/**
	 * @brief Private implementation that all overloaded BP UFunctions call.	  
	 */
	void BP_PostCouponPurchaseCompleteImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, FBeamConnectivity& ConnectivityStatus, UPostCouponPurchaseCompleteRequest* RequestData,
	                                const FOnPostCouponPurchaseCompleteSuccess& OnSuccess, const FOnPostCouponPurchaseCompleteError& OnError, const FOnPostCouponPurchaseCompleteComplete& OnComplete,
	                                int64& OutRequestId, FBeamOperationHandle OpHandle = FBeamOperationHandle()) const;
	/**
	 * @brief Overload version for binding lambdas when in C++ land. Prefer the BP version whenever possible, this is here mostly for quick experimentation purposes.	 
	 */
	void CPP_PostCouponPurchaseCompleteImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, FBeamConnectivity& ConnectivityStatus, UPostCouponPurchaseCompleteRequest* RequestData,
	                                 const FOnPostCouponPurchaseCompleteFullResponse& Handler, int64& OutRequestId, FBeamOperationHandle OpHandle = FBeamOperationHandle()) const;

		
	/**
	 * @brief Private implementation that all overloaded BP UFunctions call.	  
	 */
	void BP_GetGoogleplayProductImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, FBeamConnectivity& ConnectivityStatus, UGetGoogleplayProductRequest* RequestData,
	                                const FOnGetGoogleplayProductSuccess& OnSuccess, const FOnGetGoogleplayProductError& OnError, const FOnGetGoogleplayProductComplete& OnComplete,
	                                int64& OutRequestId, FBeamOperationHandle OpHandle = FBeamOperationHandle()) const;
	/**
	 * @brief Overload version for binding lambdas when in C++ land. Prefer the BP version whenever possible, this is here mostly for quick experimentation purposes.	 
	 */
	void CPP_GetGoogleplayProductImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, FBeamConnectivity& ConnectivityStatus, UGetGoogleplayProductRequest* RequestData,
	                                 const FOnGetGoogleplayProductFullResponse& Handler, int64& OutRequestId, FBeamOperationHandle OpHandle = FBeamOperationHandle()) const;

		
	/**
	 * @brief Private implementation that all overloaded BP UFunctions call.	  
	 */
	void BP_GetTestProductImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, FBeamConnectivity& ConnectivityStatus, UGetTestProductRequest* RequestData,
	                                const FOnGetTestProductSuccess& OnSuccess, const FOnGetTestProductError& OnError, const FOnGetTestProductComplete& OnComplete,
	                                int64& OutRequestId, FBeamOperationHandle OpHandle = FBeamOperationHandle()) const;
	/**
	 * @brief Overload version for binding lambdas when in C++ land. Prefer the BP version whenever possible, this is here mostly for quick experimentation purposes.	 
	 */
	void CPP_GetTestProductImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, FBeamConnectivity& ConnectivityStatus, UGetTestProductRequest* RequestData,
	                                 const FOnGetTestProductFullResponse& Handler, int64& OutRequestId, FBeamOperationHandle OpHandle = FBeamOperationHandle()) const;

		
	/**
	 * @brief Private implementation that all overloaded BP UFunctions call.	  
	 */
	void BP_PostSteamPurchaseVerifyImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, FBeamConnectivity& ConnectivityStatus, UPostSteamPurchaseVerifyRequest* RequestData,
	                                const FOnPostSteamPurchaseVerifySuccess& OnSuccess, const FOnPostSteamPurchaseVerifyError& OnError, const FOnPostSteamPurchaseVerifyComplete& OnComplete,
	                                int64& OutRequestId, FBeamOperationHandle OpHandle = FBeamOperationHandle()) const;
	/**
	 * @brief Overload version for binding lambdas when in C++ land. Prefer the BP version whenever possible, this is here mostly for quick experimentation purposes.	 
	 */
	void CPP_PostSteamPurchaseVerifyImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, FBeamConnectivity& ConnectivityStatus, UPostSteamPurchaseVerifyRequest* RequestData,
	                                 const FOnPostSteamPurchaseVerifyFullResponse& Handler, int64& OutRequestId, FBeamOperationHandle OpHandle = FBeamOperationHandle()) const;

		
	/**
	 * @brief Private implementation that all overloaded BP UFunctions call.	  
	 */
	void BP_PostItunesPurchaseTrackImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, FBeamConnectivity& ConnectivityStatus, UPostItunesPurchaseTrackRequest* RequestData,
	                                const FOnPostItunesPurchaseTrackSuccess& OnSuccess, const FOnPostItunesPurchaseTrackError& OnError, const FOnPostItunesPurchaseTrackComplete& OnComplete,
	                                int64& OutRequestId, FBeamOperationHandle OpHandle = FBeamOperationHandle()) const;
	/**
	 * @brief Overload version for binding lambdas when in C++ land. Prefer the BP version whenever possible, this is here mostly for quick experimentation purposes.	 
	 */
	void CPP_PostItunesPurchaseTrackImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, FBeamConnectivity& ConnectivityStatus, UPostItunesPurchaseTrackRequest* RequestData,
	                                 const FOnPostItunesPurchaseTrackFullResponse& Handler, int64& OutRequestId, FBeamOperationHandle OpHandle = FBeamOperationHandle()) const;

		
	/**
	 * @brief Private implementation that all overloaded BP UFunctions call.	  
	 */
	void BP_GetPaymentsImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, FBeamConnectivity& ConnectivityStatus, UGetPaymentsRequest* RequestData,
	                                const FOnGetPaymentsSuccess& OnSuccess, const FOnGetPaymentsError& OnError, const FOnGetPaymentsComplete& OnComplete,
	                                int64& OutRequestId, FBeamOperationHandle OpHandle = FBeamOperationHandle()) const;
	/**
	 * @brief Overload version for binding lambdas when in C++ land. Prefer the BP version whenever possible, this is here mostly for quick experimentation purposes.	 
	 */
	void CPP_GetPaymentsImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, FBeamConnectivity& ConnectivityStatus, UGetPaymentsRequest* RequestData,
	                                 const FOnGetPaymentsFullResponse& Handler, int64& OutRequestId, FBeamOperationHandle OpHandle = FBeamOperationHandle()) const;


	
	/**
	 * @brief Private implementation for requests that require authentication that all overloaded BP UFunctions call.	  
	 */
	void BP_PostTestPurchaseBeginImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, const FBeamAuthToken& AuthToken, FBeamConnectivity& ConnectivityStatus, UPostTestPurchaseBeginRequest* RequestData,
	                  const FOnPostTestPurchaseBeginSuccess& OnSuccess, const FOnPostTestPurchaseBeginError& OnError, const FOnPostTestPurchaseBeginComplete& OnComplete, 
					  int64& OutRequestId, FBeamOperationHandle OpHandle = FBeamOperationHandle()) const;
	/**
	 * @brief Overload version for binding lambdas when in C++ land. Prefer the BP version whenever possible, this is here mostly for quick experimentation purposes.	 
	 */
	void CPP_PostTestPurchaseBeginImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, const FBeamAuthToken& AuthToken, FBeamConnectivity& ConnectivityStatus, UPostTestPurchaseBeginRequest* RequestData,
	                   const FOnPostTestPurchaseBeginFullResponse& Handler, int64& OutRequestId, FBeamOperationHandle OpHandle = FBeamOperationHandle()) const;
		
	/**
	 * @brief Private implementation for requests that require authentication that all overloaded BP UFunctions call.	  
	 */
	void BP_PostSteamPurchaseFailImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, const FBeamAuthToken& AuthToken, FBeamConnectivity& ConnectivityStatus, UPostSteamPurchaseFailRequest* RequestData,
	                  const FOnPostSteamPurchaseFailSuccess& OnSuccess, const FOnPostSteamPurchaseFailError& OnError, const FOnPostSteamPurchaseFailComplete& OnComplete, 
					  int64& OutRequestId, FBeamOperationHandle OpHandle = FBeamOperationHandle()) const;
	/**
	 * @brief Overload version for binding lambdas when in C++ land. Prefer the BP version whenever possible, this is here mostly for quick experimentation purposes.	 
	 */
	void CPP_PostSteamPurchaseFailImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, const FBeamAuthToken& AuthToken, FBeamConnectivity& ConnectivityStatus, UPostSteamPurchaseFailRequest* RequestData,
	                   const FOnPostSteamPurchaseFailFullResponse& Handler, int64& OutRequestId, FBeamOperationHandle OpHandle = FBeamOperationHandle()) const;
		
	/**
	 * @brief Private implementation for requests that require authentication that all overloaded BP UFunctions call.	  
	 */
	void BP_PostFacebookPurchaseFailImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, const FBeamAuthToken& AuthToken, FBeamConnectivity& ConnectivityStatus, UPostFacebookPurchaseFailRequest* RequestData,
	                  const FOnPostFacebookPurchaseFailSuccess& OnSuccess, const FOnPostFacebookPurchaseFailError& OnError, const FOnPostFacebookPurchaseFailComplete& OnComplete, 
					  int64& OutRequestId, FBeamOperationHandle OpHandle = FBeamOperationHandle()) const;
	/**
	 * @brief Overload version for binding lambdas when in C++ land. Prefer the BP version whenever possible, this is here mostly for quick experimentation purposes.	 
	 */
	void CPP_PostFacebookPurchaseFailImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, const FBeamAuthToken& AuthToken, FBeamConnectivity& ConnectivityStatus, UPostFacebookPurchaseFailRequest* RequestData,
	                   const FOnPostFacebookPurchaseFailFullResponse& Handler, int64& OutRequestId, FBeamOperationHandle OpHandle = FBeamOperationHandle()) const;
		
	/**
	 * @brief Private implementation for requests that require authentication that all overloaded BP UFunctions call.	  
	 */
	void BP_PostGoogleplayPurchaseBeginImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, const FBeamAuthToken& AuthToken, FBeamConnectivity& ConnectivityStatus, UPostGoogleplayPurchaseBeginRequest* RequestData,
	                  const FOnPostGoogleplayPurchaseBeginSuccess& OnSuccess, const FOnPostGoogleplayPurchaseBeginError& OnError, const FOnPostGoogleplayPurchaseBeginComplete& OnComplete, 
					  int64& OutRequestId, FBeamOperationHandle OpHandle = FBeamOperationHandle()) const;
	/**
	 * @brief Overload version for binding lambdas when in C++ land. Prefer the BP version whenever possible, this is here mostly for quick experimentation purposes.	 
	 */
	void CPP_PostGoogleplayPurchaseBeginImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, const FBeamAuthToken& AuthToken, FBeamConnectivity& ConnectivityStatus, UPostGoogleplayPurchaseBeginRequest* RequestData,
	                   const FOnPostGoogleplayPurchaseBeginFullResponse& Handler, int64& OutRequestId, FBeamOperationHandle OpHandle = FBeamOperationHandle()) const;
		
	/**
	 * @brief Private implementation for requests that require authentication that all overloaded BP UFunctions call.	  
	 */
	void BP_PostItunesPurchaseBeginImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, const FBeamAuthToken& AuthToken, FBeamConnectivity& ConnectivityStatus, UPostItunesPurchaseBeginRequest* RequestData,
	                  const FOnPostItunesPurchaseBeginSuccess& OnSuccess, const FOnPostItunesPurchaseBeginError& OnError, const FOnPostItunesPurchaseBeginComplete& OnComplete, 
					  int64& OutRequestId, FBeamOperationHandle OpHandle = FBeamOperationHandle()) const;
	/**
	 * @brief Overload version for binding lambdas when in C++ land. Prefer the BP version whenever possible, this is here mostly for quick experimentation purposes.	 
	 */
	void CPP_PostItunesPurchaseBeginImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, const FBeamAuthToken& AuthToken, FBeamConnectivity& ConnectivityStatus, UPostItunesPurchaseBeginRequest* RequestData,
	                   const FOnPostItunesPurchaseBeginFullResponse& Handler, int64& OutRequestId, FBeamOperationHandle OpHandle = FBeamOperationHandle()) const;
		
	/**
	 * @brief Private implementation for requests that require authentication that all overloaded BP UFunctions call.	  
	 */
	void BP_PostFacebookPurchaseCancelImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, const FBeamAuthToken& AuthToken, FBeamConnectivity& ConnectivityStatus, UPostFacebookPurchaseCancelRequest* RequestData,
	                  const FOnPostFacebookPurchaseCancelSuccess& OnSuccess, const FOnPostFacebookPurchaseCancelError& OnError, const FOnPostFacebookPurchaseCancelComplete& OnComplete, 
					  int64& OutRequestId, FBeamOperationHandle OpHandle = FBeamOperationHandle()) const;
	/**
	 * @brief Overload version for binding lambdas when in C++ land. Prefer the BP version whenever possible, this is here mostly for quick experimentation purposes.	 
	 */
	void CPP_PostFacebookPurchaseCancelImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, const FBeamAuthToken& AuthToken, FBeamConnectivity& ConnectivityStatus, UPostFacebookPurchaseCancelRequest* RequestData,
	                   const FOnPostFacebookPurchaseCancelFullResponse& Handler, int64& OutRequestId, FBeamOperationHandle OpHandle = FBeamOperationHandle()) const;
		
	/**
	 * @brief Private implementation for requests that require authentication that all overloaded BP UFunctions call.	  
	 */
	void BP_PostItunesPurchaseFailImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, const FBeamAuthToken& AuthToken, FBeamConnectivity& ConnectivityStatus, UPostItunesPurchaseFailRequest* RequestData,
	                  const FOnPostItunesPurchaseFailSuccess& OnSuccess, const FOnPostItunesPurchaseFailError& OnError, const FOnPostItunesPurchaseFailComplete& OnComplete, 
					  int64& OutRequestId, FBeamOperationHandle OpHandle = FBeamOperationHandle()) const;
	/**
	 * @brief Overload version for binding lambdas when in C++ land. Prefer the BP version whenever possible, this is here mostly for quick experimentation purposes.	 
	 */
	void CPP_PostItunesPurchaseFailImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, const FBeamAuthToken& AuthToken, FBeamConnectivity& ConnectivityStatus, UPostItunesPurchaseFailRequest* RequestData,
	                   const FOnPostItunesPurchaseFailFullResponse& Handler, int64& OutRequestId, FBeamOperationHandle OpHandle = FBeamOperationHandle()) const;
		
	/**
	 * @brief Private implementation for requests that require authentication that all overloaded BP UFunctions call.	  
	 */
	void BP_PostTestPurchaseCancelImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, const FBeamAuthToken& AuthToken, FBeamConnectivity& ConnectivityStatus, UPostTestPurchaseCancelRequest* RequestData,
	                  const FOnPostTestPurchaseCancelSuccess& OnSuccess, const FOnPostTestPurchaseCancelError& OnError, const FOnPostTestPurchaseCancelComplete& OnComplete, 
					  int64& OutRequestId, FBeamOperationHandle OpHandle = FBeamOperationHandle()) const;
	/**
	 * @brief Overload version for binding lambdas when in C++ land. Prefer the BP version whenever possible, this is here mostly for quick experimentation purposes.	 
	 */
	void CPP_PostTestPurchaseCancelImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, const FBeamAuthToken& AuthToken, FBeamConnectivity& ConnectivityStatus, UPostTestPurchaseCancelRequest* RequestData,
	                   const FOnPostTestPurchaseCancelFullResponse& Handler, int64& OutRequestId, FBeamOperationHandle OpHandle = FBeamOperationHandle()) const;
		
	/**
	 * @brief Private implementation for requests that require authentication that all overloaded BP UFunctions call.	  
	 */
	void BP_PostTestPurchaseFailImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, const FBeamAuthToken& AuthToken, FBeamConnectivity& ConnectivityStatus, UPostTestPurchaseFailRequest* RequestData,
	                  const FOnPostTestPurchaseFailSuccess& OnSuccess, const FOnPostTestPurchaseFailError& OnError, const FOnPostTestPurchaseFailComplete& OnComplete, 
					  int64& OutRequestId, FBeamOperationHandle OpHandle = FBeamOperationHandle()) const;
	/**
	 * @brief Overload version for binding lambdas when in C++ land. Prefer the BP version whenever possible, this is here mostly for quick experimentation purposes.	 
	 */
	void CPP_PostTestPurchaseFailImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, const FBeamAuthToken& AuthToken, FBeamConnectivity& ConnectivityStatus, UPostTestPurchaseFailRequest* RequestData,
	                   const FOnPostTestPurchaseFailFullResponse& Handler, int64& OutRequestId, FBeamOperationHandle OpHandle = FBeamOperationHandle()) const;
		
	/**
	 * @brief Private implementation for requests that require authentication that all overloaded BP UFunctions call.	  
	 */
	void BP_PostCouponPurchaseCancelImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, const FBeamAuthToken& AuthToken, FBeamConnectivity& ConnectivityStatus, UPostCouponPurchaseCancelRequest* RequestData,
	                  const FOnPostCouponPurchaseCancelSuccess& OnSuccess, const FOnPostCouponPurchaseCancelError& OnError, const FOnPostCouponPurchaseCancelComplete& OnComplete, 
					  int64& OutRequestId, FBeamOperationHandle OpHandle = FBeamOperationHandle()) const;
	/**
	 * @brief Overload version for binding lambdas when in C++ land. Prefer the BP version whenever possible, this is here mostly for quick experimentation purposes.	 
	 */
	void CPP_PostCouponPurchaseCancelImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, const FBeamAuthToken& AuthToken, FBeamConnectivity& ConnectivityStatus, UPostCouponPurchaseCancelRequest* RequestData,
	                   const FOnPostCouponPurchaseCancelFullResponse& Handler, int64& OutRequestId, FBeamOperationHandle OpHandle = FBeamOperationHandle()) const;
		
	/**
	 * @brief Private implementation for requests that require authentication that all overloaded BP UFunctions call.	  
	 */
	void BP_PostCouponPurchaseBeginImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, const FBeamAuthToken& AuthToken, FBeamConnectivity& ConnectivityStatus, UPostCouponPurchaseBeginRequest* RequestData,
	                  const FOnPostCouponPurchaseBeginSuccess& OnSuccess, const FOnPostCouponPurchaseBeginError& OnError, const FOnPostCouponPurchaseBeginComplete& OnComplete, 
					  int64& OutRequestId, FBeamOperationHandle OpHandle = FBeamOperationHandle()) const;
	/**
	 * @brief Overload version for binding lambdas when in C++ land. Prefer the BP version whenever possible, this is here mostly for quick experimentation purposes.	 
	 */
	void CPP_PostCouponPurchaseBeginImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, const FBeamAuthToken& AuthToken, FBeamConnectivity& ConnectivityStatus, UPostCouponPurchaseBeginRequest* RequestData,
	                   const FOnPostCouponPurchaseBeginFullResponse& Handler, int64& OutRequestId, FBeamOperationHandle OpHandle = FBeamOperationHandle()) const;
		
	/**
	 * @brief Private implementation for requests that require authentication that all overloaded BP UFunctions call.	  
	 */
	void BP_PostFacebookPurchaseBeginImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, const FBeamAuthToken& AuthToken, FBeamConnectivity& ConnectivityStatus, UPostFacebookPurchaseBeginRequest* RequestData,
	                  const FOnPostFacebookPurchaseBeginSuccess& OnSuccess, const FOnPostFacebookPurchaseBeginError& OnError, const FOnPostFacebookPurchaseBeginComplete& OnComplete, 
					  int64& OutRequestId, FBeamOperationHandle OpHandle = FBeamOperationHandle()) const;
	/**
	 * @brief Overload version for binding lambdas when in C++ land. Prefer the BP version whenever possible, this is here mostly for quick experimentation purposes.	 
	 */
	void CPP_PostFacebookPurchaseBeginImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, const FBeamAuthToken& AuthToken, FBeamConnectivity& ConnectivityStatus, UPostFacebookPurchaseBeginRequest* RequestData,
	                   const FOnPostFacebookPurchaseBeginFullResponse& Handler, int64& OutRequestId, FBeamOperationHandle OpHandle = FBeamOperationHandle()) const;
		
	/**
	 * @brief Private implementation for requests that require authentication that all overloaded BP UFunctions call.	  
	 */
	void BP_GetSteamOrderImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, const FBeamAuthToken& AuthToken, FBeamConnectivity& ConnectivityStatus, UGetSteamOrderRequest* RequestData,
	                  const FOnGetSteamOrderSuccess& OnSuccess, const FOnGetSteamOrderError& OnError, const FOnGetSteamOrderComplete& OnComplete, 
					  int64& OutRequestId, FBeamOperationHandle OpHandle = FBeamOperationHandle()) const;
	/**
	 * @brief Overload version for binding lambdas when in C++ land. Prefer the BP version whenever possible, this is here mostly for quick experimentation purposes.	 
	 */
	void CPP_GetSteamOrderImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, const FBeamAuthToken& AuthToken, FBeamConnectivity& ConnectivityStatus, UGetSteamOrderRequest* RequestData,
	                   const FOnGetSteamOrderFullResponse& Handler, int64& OutRequestId, FBeamOperationHandle OpHandle = FBeamOperationHandle()) const;
		
	/**
	 * @brief Private implementation for requests that require authentication that all overloaded BP UFunctions call.	  
	 */
	void BP_PostWindowsPurchaseBeginImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, const FBeamAuthToken& AuthToken, FBeamConnectivity& ConnectivityStatus, UPostWindowsPurchaseBeginRequest* RequestData,
	                  const FOnPostWindowsPurchaseBeginSuccess& OnSuccess, const FOnPostWindowsPurchaseBeginError& OnError, const FOnPostWindowsPurchaseBeginComplete& OnComplete, 
					  int64& OutRequestId, FBeamOperationHandle OpHandle = FBeamOperationHandle()) const;
	/**
	 * @brief Overload version for binding lambdas when in C++ land. Prefer the BP version whenever possible, this is here mostly for quick experimentation purposes.	 
	 */
	void CPP_PostWindowsPurchaseBeginImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, const FBeamAuthToken& AuthToken, FBeamConnectivity& ConnectivityStatus, UPostWindowsPurchaseBeginRequest* RequestData,
	                   const FOnPostWindowsPurchaseBeginFullResponse& Handler, int64& OutRequestId, FBeamOperationHandle OpHandle = FBeamOperationHandle()) const;
		
	/**
	 * @brief Private implementation for requests that require authentication that all overloaded BP UFunctions call.	  
	 */
	void BP_PostGoogleplayPurchaseFailImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, const FBeamAuthToken& AuthToken, FBeamConnectivity& ConnectivityStatus, UPostGoogleplayPurchaseFailRequest* RequestData,
	                  const FOnPostGoogleplayPurchaseFailSuccess& OnSuccess, const FOnPostGoogleplayPurchaseFailError& OnError, const FOnPostGoogleplayPurchaseFailComplete& OnComplete, 
					  int64& OutRequestId, FBeamOperationHandle OpHandle = FBeamOperationHandle()) const;
	/**
	 * @brief Overload version for binding lambdas when in C++ land. Prefer the BP version whenever possible, this is here mostly for quick experimentation purposes.	 
	 */
	void CPP_PostGoogleplayPurchaseFailImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, const FBeamAuthToken& AuthToken, FBeamConnectivity& ConnectivityStatus, UPostGoogleplayPurchaseFailRequest* RequestData,
	                   const FOnPostGoogleplayPurchaseFailFullResponse& Handler, int64& OutRequestId, FBeamOperationHandle OpHandle = FBeamOperationHandle()) const;
		
	/**
	 * @brief Private implementation for requests that require authentication that all overloaded BP UFunctions call.	  
	 */
	void BP_PostGoogleplayPurchaseCancelImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, const FBeamAuthToken& AuthToken, FBeamConnectivity& ConnectivityStatus, UPostGoogleplayPurchaseCancelRequest* RequestData,
	                  const FOnPostGoogleplayPurchaseCancelSuccess& OnSuccess, const FOnPostGoogleplayPurchaseCancelError& OnError, const FOnPostGoogleplayPurchaseCancelComplete& OnComplete, 
					  int64& OutRequestId, FBeamOperationHandle OpHandle = FBeamOperationHandle()) const;
	/**
	 * @brief Overload version for binding lambdas when in C++ land. Prefer the BP version whenever possible, this is here mostly for quick experimentation purposes.	 
	 */
	void CPP_PostGoogleplayPurchaseCancelImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, const FBeamAuthToken& AuthToken, FBeamConnectivity& ConnectivityStatus, UPostGoogleplayPurchaseCancelRequest* RequestData,
	                   const FOnPostGoogleplayPurchaseCancelFullResponse& Handler, int64& OutRequestId, FBeamOperationHandle OpHandle = FBeamOperationHandle()) const;
		
	/**
	 * @brief Private implementation for requests that require authentication that all overloaded BP UFunctions call.	  
	 */
	void BP_PostCouponPurchaseFailImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, const FBeamAuthToken& AuthToken, FBeamConnectivity& ConnectivityStatus, UPostCouponPurchaseFailRequest* RequestData,
	                  const FOnPostCouponPurchaseFailSuccess& OnSuccess, const FOnPostCouponPurchaseFailError& OnError, const FOnPostCouponPurchaseFailComplete& OnComplete, 
					  int64& OutRequestId, FBeamOperationHandle OpHandle = FBeamOperationHandle()) const;
	/**
	 * @brief Overload version for binding lambdas when in C++ land. Prefer the BP version whenever possible, this is here mostly for quick experimentation purposes.	 
	 */
	void CPP_PostCouponPurchaseFailImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, const FBeamAuthToken& AuthToken, FBeamConnectivity& ConnectivityStatus, UPostCouponPurchaseFailRequest* RequestData,
	                   const FOnPostCouponPurchaseFailFullResponse& Handler, int64& OutRequestId, FBeamOperationHandle OpHandle = FBeamOperationHandle()) const;
		
	/**
	 * @brief Private implementation for requests that require authentication that all overloaded BP UFunctions call.	  
	 */
	void BP_PostSteamPurchaseBeginImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, const FBeamAuthToken& AuthToken, FBeamConnectivity& ConnectivityStatus, UPostSteamPurchaseBeginRequest* RequestData,
	                  const FOnPostSteamPurchaseBeginSuccess& OnSuccess, const FOnPostSteamPurchaseBeginError& OnError, const FOnPostSteamPurchaseBeginComplete& OnComplete, 
					  int64& OutRequestId, FBeamOperationHandle OpHandle = FBeamOperationHandle()) const;
	/**
	 * @brief Overload version for binding lambdas when in C++ land. Prefer the BP version whenever possible, this is here mostly for quick experimentation purposes.	 
	 */
	void CPP_PostSteamPurchaseBeginImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, const FBeamAuthToken& AuthToken, FBeamConnectivity& ConnectivityStatus, UPostSteamPurchaseBeginRequest* RequestData,
	                   const FOnPostSteamPurchaseBeginFullResponse& Handler, int64& OutRequestId, FBeamOperationHandle OpHandle = FBeamOperationHandle()) const;
		
	/**
	 * @brief Private implementation for requests that require authentication that all overloaded BP UFunctions call.	  
	 */
	void BP_PostSteamPurchaseCancelImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, const FBeamAuthToken& AuthToken, FBeamConnectivity& ConnectivityStatus, UPostSteamPurchaseCancelRequest* RequestData,
	                  const FOnPostSteamPurchaseCancelSuccess& OnSuccess, const FOnPostSteamPurchaseCancelError& OnError, const FOnPostSteamPurchaseCancelComplete& OnComplete, 
					  int64& OutRequestId, FBeamOperationHandle OpHandle = FBeamOperationHandle()) const;
	/**
	 * @brief Overload version for binding lambdas when in C++ land. Prefer the BP version whenever possible, this is here mostly for quick experimentation purposes.	 
	 */
	void CPP_PostSteamPurchaseCancelImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, const FBeamAuthToken& AuthToken, FBeamConnectivity& ConnectivityStatus, UPostSteamPurchaseCancelRequest* RequestData,
	                   const FOnPostSteamPurchaseCancelFullResponse& Handler, int64& OutRequestId, FBeamOperationHandle OpHandle = FBeamOperationHandle()) const;
		
	/**
	 * @brief Private implementation for requests that require authentication that all overloaded BP UFunctions call.	  
	 */
	void BP_PostWindowsPurchaseCancelImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, const FBeamAuthToken& AuthToken, FBeamConnectivity& ConnectivityStatus, UPostWindowsPurchaseCancelRequest* RequestData,
	                  const FOnPostWindowsPurchaseCancelSuccess& OnSuccess, const FOnPostWindowsPurchaseCancelError& OnError, const FOnPostWindowsPurchaseCancelComplete& OnComplete, 
					  int64& OutRequestId, FBeamOperationHandle OpHandle = FBeamOperationHandle()) const;
	/**
	 * @brief Overload version for binding lambdas when in C++ land. Prefer the BP version whenever possible, this is here mostly for quick experimentation purposes.	 
	 */
	void CPP_PostWindowsPurchaseCancelImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, const FBeamAuthToken& AuthToken, FBeamConnectivity& ConnectivityStatus, UPostWindowsPurchaseCancelRequest* RequestData,
	                   const FOnPostWindowsPurchaseCancelFullResponse& Handler, int64& OutRequestId, FBeamOperationHandle OpHandle = FBeamOperationHandle()) const;
		
	/**
	 * @brief Private implementation for requests that require authentication that all overloaded BP UFunctions call.	  
	 */
	void BP_PostWindowsPurchaseFailImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, const FBeamAuthToken& AuthToken, FBeamConnectivity& ConnectivityStatus, UPostWindowsPurchaseFailRequest* RequestData,
	                  const FOnPostWindowsPurchaseFailSuccess& OnSuccess, const FOnPostWindowsPurchaseFailError& OnError, const FOnPostWindowsPurchaseFailComplete& OnComplete, 
					  int64& OutRequestId, FBeamOperationHandle OpHandle = FBeamOperationHandle()) const;
	/**
	 * @brief Overload version for binding lambdas when in C++ land. Prefer the BP version whenever possible, this is here mostly for quick experimentation purposes.	 
	 */
	void CPP_PostWindowsPurchaseFailImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, const FBeamAuthToken& AuthToken, FBeamConnectivity& ConnectivityStatus, UPostWindowsPurchaseFailRequest* RequestData,
	                   const FOnPostWindowsPurchaseFailFullResponse& Handler, int64& OutRequestId, FBeamOperationHandle OpHandle = FBeamOperationHandle()) const;
		
	/**
	 * @brief Private implementation for requests that require authentication that all overloaded BP UFunctions call.	  
	 */
	void BP_PostItunesPurchaseCancelImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, const FBeamAuthToken& AuthToken, FBeamConnectivity& ConnectivityStatus, UPostItunesPurchaseCancelRequest* RequestData,
	                  const FOnPostItunesPurchaseCancelSuccess& OnSuccess, const FOnPostItunesPurchaseCancelError& OnError, const FOnPostItunesPurchaseCancelComplete& OnComplete, 
					  int64& OutRequestId, FBeamOperationHandle OpHandle = FBeamOperationHandle()) const;
	/**
	 * @brief Overload version for binding lambdas when in C++ land. Prefer the BP version whenever possible, this is here mostly for quick experimentation purposes.	 
	 */
	void CPP_PostItunesPurchaseCancelImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, const FBeamAuthToken& AuthToken, FBeamConnectivity& ConnectivityStatus, UPostItunesPurchaseCancelRequest* RequestData,
	                   const FOnPostItunesPurchaseCancelFullResponse& Handler, int64& OutRequestId, FBeamOperationHandle OpHandle = FBeamOperationHandle()) const;

public:
	
	/** Used by a helper blueprint node so that you can easily chain requests in BP-land. */
	UFUNCTION(BlueprintPure, BlueprintInternalUseOnly)
	static UBeamPaymentsApi* GetSelf() { return GEngine->GetEngineSubsystem<UBeamPaymentsApi>(); }

	
	/**
	 * @brief Makes a request to the Post /basic/payments/windows/purchase/track endpoint of the Payments Service.
	 *
	 * PREFER THE UFUNCTION OVERLOAD AS OPPOSED TO THIS. THIS MAINLY EXISTS TO ALLOW LAMBDA BINDING THE HANDLER.
	 * (Dynamic delegates do not allow for that so... we autogen this one to make experimenting in CPP a bit faster and for whenever you need to capture variables).
	 * 
	 * @param Request The Request UObject. All (de)serialized data the request data creates is tied to the lifecycle of this object.
	 * @param Handler A callback that defines how to handle success, error and completion.
     * @param OutRequestContext The Request Context associated with this request -- used to query information about the request or to cancel it while it's in flight.
	 * @param OpHandle When made as part of an Operation, you can pass this in and it'll register the request with the operation automatically. 
	 */
	void CPP_PostWindowsPurchaseTrack(UPostWindowsPurchaseTrackRequest* Request, const FOnPostWindowsPurchaseTrackFullResponse& Handler, FBeamRequestContext& OutRequestContext, FBeamOperationHandle OpHandle = FBeamOperationHandle()) const;

		
	/**
	 * @brief Makes a request to the Get /basic/payments/audits endpoint of the Payments Service.
	 *
	 * PREFER THE UFUNCTION OVERLOAD AS OPPOSED TO THIS. THIS MAINLY EXISTS TO ALLOW LAMBDA BINDING THE HANDLER.
	 * (Dynamic delegates do not allow for that so... we autogen this one to make experimenting in CPP a bit faster and for whenever you need to capture variables).
	 * 
	 * @param Request The Request UObject. All (de)serialized data the request data creates is tied to the lifecycle of this object.
	 * @param Handler A callback that defines how to handle success, error and completion.
     * @param OutRequestContext The Request Context associated with this request -- used to query information about the request or to cancel it while it's in flight.
	 * @param OpHandle When made as part of an Operation, you can pass this in and it'll register the request with the operation automatically. 
	 */
	void CPP_GetAudits(UGetAuditsRequest* Request, const FOnGetAuditsFullResponse& Handler, FBeamRequestContext& OutRequestContext, FBeamOperationHandle OpHandle = FBeamOperationHandle()) const;

		
	/**
	 * @brief Makes a request to the Post /basic/payments/windows/purchase/complete endpoint of the Payments Service.
	 *
	 * PREFER THE UFUNCTION OVERLOAD AS OPPOSED TO THIS. THIS MAINLY EXISTS TO ALLOW LAMBDA BINDING THE HANDLER.
	 * (Dynamic delegates do not allow for that so... we autogen this one to make experimenting in CPP a bit faster and for whenever you need to capture variables).
	 * 
	 * @param Request The Request UObject. All (de)serialized data the request data creates is tied to the lifecycle of this object.
	 * @param Handler A callback that defines how to handle success, error and completion.
     * @param OutRequestContext The Request Context associated with this request -- used to query information about the request or to cancel it while it's in flight.
	 * @param OpHandle When made as part of an Operation, you can pass this in and it'll register the request with the operation automatically. 
	 */
	void CPP_PostWindowsPurchaseComplete(UPostWindowsPurchaseCompleteRequest* Request, const FOnPostWindowsPurchaseCompleteFullResponse& Handler, FBeamRequestContext& OutRequestContext, FBeamOperationHandle OpHandle = FBeamOperationHandle()) const;

		
	/**
	 * @brief Makes a request to the Get /basic/payments/facebook/update endpoint of the Payments Service.
	 *
	 * PREFER THE UFUNCTION OVERLOAD AS OPPOSED TO THIS. THIS MAINLY EXISTS TO ALLOW LAMBDA BINDING THE HANDLER.
	 * (Dynamic delegates do not allow for that so... we autogen this one to make experimenting in CPP a bit faster and for whenever you need to capture variables).
	 * 
	 * @param Request The Request UObject. All (de)serialized data the request data creates is tied to the lifecycle of this object.
	 * @param Handler A callback that defines how to handle success, error and completion.
     * @param OutRequestContext The Request Context associated with this request -- used to query information about the request or to cancel it while it's in flight.
	 * @param OpHandle When made as part of an Operation, you can pass this in and it'll register the request with the operation automatically. 
	 */
	void CPP_GetFacebookUpdate(UGetFacebookUpdateRequest* Request, const FOnGetFacebookUpdateFullResponse& Handler, FBeamRequestContext& OutRequestContext, FBeamOperationHandle OpHandle = FBeamOperationHandle()) const;

		
	/**
	 * @brief Makes a request to the Post /basic/payments/facebook/update endpoint of the Payments Service.
	 *
	 * PREFER THE UFUNCTION OVERLOAD AS OPPOSED TO THIS. THIS MAINLY EXISTS TO ALLOW LAMBDA BINDING THE HANDLER.
	 * (Dynamic delegates do not allow for that so... we autogen this one to make experimenting in CPP a bit faster and for whenever you need to capture variables).
	 * 
	 * @param Request The Request UObject. All (de)serialized data the request data creates is tied to the lifecycle of this object.
	 * @param Handler A callback that defines how to handle success, error and completion.
     * @param OutRequestContext The Request Context associated with this request -- used to query information about the request or to cancel it while it's in flight.
	 * @param OpHandle When made as part of an Operation, you can pass this in and it'll register the request with the operation automatically. 
	 */
	void CPP_PostFacebookUpdate(UPostFacebookUpdateRequest* Request, const FOnPostFacebookUpdateFullResponse& Handler, FBeamRequestContext& OutRequestContext, FBeamOperationHandle OpHandle = FBeamOperationHandle()) const;

		
	/**
	 * @brief Makes a request to the Post /basic/payments/facebook/purchase/complete endpoint of the Payments Service.
	 *
	 * PREFER THE UFUNCTION OVERLOAD AS OPPOSED TO THIS. THIS MAINLY EXISTS TO ALLOW LAMBDA BINDING THE HANDLER.
	 * (Dynamic delegates do not allow for that so... we autogen this one to make experimenting in CPP a bit faster and for whenever you need to capture variables).
	 * 
	 * @param Request The Request UObject. All (de)serialized data the request data creates is tied to the lifecycle of this object.
	 * @param Handler A callback that defines how to handle success, error and completion.
     * @param OutRequestContext The Request Context associated with this request -- used to query information about the request or to cancel it while it's in flight.
	 * @param OpHandle When made as part of an Operation, you can pass this in and it'll register the request with the operation automatically. 
	 */
	void CPP_PostFacebookPurchaseComplete(UPostFacebookPurchaseCompleteRequest* Request, const FOnPostFacebookPurchaseCompleteFullResponse& Handler, FBeamRequestContext& OutRequestContext, FBeamOperationHandle OpHandle = FBeamOperationHandle()) const;

		
	/**
	 * @brief Makes a request to the Post /basic/payments/test/purchase/complete endpoint of the Payments Service.
	 *
	 * PREFER THE UFUNCTION OVERLOAD AS OPPOSED TO THIS. THIS MAINLY EXISTS TO ALLOW LAMBDA BINDING THE HANDLER.
	 * (Dynamic delegates do not allow for that so... we autogen this one to make experimenting in CPP a bit faster and for whenever you need to capture variables).
	 * 
	 * @param Request The Request UObject. All (de)serialized data the request data creates is tied to the lifecycle of this object.
	 * @param Handler A callback that defines how to handle success, error and completion.
     * @param OutRequestContext The Request Context associated with this request -- used to query information about the request or to cancel it while it's in flight.
	 * @param OpHandle When made as part of an Operation, you can pass this in and it'll register the request with the operation automatically. 
	 */
	void CPP_PostTestPurchaseComplete(UPostTestPurchaseCompleteRequest* Request, const FOnPostTestPurchaseCompleteFullResponse& Handler, FBeamRequestContext& OutRequestContext, FBeamOperationHandle OpHandle = FBeamOperationHandle()) const;

		
	/**
	 * @brief Makes a request to the Get /basic/payments/itunes/product endpoint of the Payments Service.
	 *
	 * PREFER THE UFUNCTION OVERLOAD AS OPPOSED TO THIS. THIS MAINLY EXISTS TO ALLOW LAMBDA BINDING THE HANDLER.
	 * (Dynamic delegates do not allow for that so... we autogen this one to make experimenting in CPP a bit faster and for whenever you need to capture variables).
	 * 
	 * @param Request The Request UObject. All (de)serialized data the request data creates is tied to the lifecycle of this object.
	 * @param Handler A callback that defines how to handle success, error and completion.
     * @param OutRequestContext The Request Context associated with this request -- used to query information about the request or to cancel it while it's in flight.
	 * @param OpHandle When made as part of an Operation, you can pass this in and it'll register the request with the operation automatically. 
	 */
	void CPP_GetItunesProduct(UGetItunesProductRequest* Request, const FOnGetItunesProductFullResponse& Handler, FBeamRequestContext& OutRequestContext, FBeamOperationHandle OpHandle = FBeamOperationHandle()) const;

		
	/**
	 * @brief Makes a request to the Post /basic/payments/googleplay/purchase/complete endpoint of the Payments Service.
	 *
	 * PREFER THE UFUNCTION OVERLOAD AS OPPOSED TO THIS. THIS MAINLY EXISTS TO ALLOW LAMBDA BINDING THE HANDLER.
	 * (Dynamic delegates do not allow for that so... we autogen this one to make experimenting in CPP a bit faster and for whenever you need to capture variables).
	 * 
	 * @param Request The Request UObject. All (de)serialized data the request data creates is tied to the lifecycle of this object.
	 * @param Handler A callback that defines how to handle success, error and completion.
     * @param OutRequestContext The Request Context associated with this request -- used to query information about the request or to cancel it while it's in flight.
	 * @param OpHandle When made as part of an Operation, you can pass this in and it'll register the request with the operation automatically. 
	 */
	void CPP_PostGoogleplayPurchaseComplete(UPostGoogleplayPurchaseCompleteRequest* Request, const FOnPostGoogleplayPurchaseCompleteFullResponse& Handler, FBeamRequestContext& OutRequestContext, FBeamOperationHandle OpHandle = FBeamOperationHandle()) const;

		
	/**
	 * @brief Makes a request to the Post /basic/payments/test/purchase/track endpoint of the Payments Service.
	 *
	 * PREFER THE UFUNCTION OVERLOAD AS OPPOSED TO THIS. THIS MAINLY EXISTS TO ALLOW LAMBDA BINDING THE HANDLER.
	 * (Dynamic delegates do not allow for that so... we autogen this one to make experimenting in CPP a bit faster and for whenever you need to capture variables).
	 * 
	 * @param Request The Request UObject. All (de)serialized data the request data creates is tied to the lifecycle of this object.
	 * @param Handler A callback that defines how to handle success, error and completion.
     * @param OutRequestContext The Request Context associated with this request -- used to query information about the request or to cancel it while it's in flight.
	 * @param OpHandle When made as part of an Operation, you can pass this in and it'll register the request with the operation automatically. 
	 */
	void CPP_PostTestPurchaseTrack(UPostTestPurchaseTrackRequest* Request, const FOnPostTestPurchaseTrackFullResponse& Handler, FBeamRequestContext& OutRequestContext, FBeamOperationHandle OpHandle = FBeamOperationHandle()) const;

		
	/**
	 * @brief Makes a request to the Post /basic/payments/googleplay/purchase/verify endpoint of the Payments Service.
	 *
	 * PREFER THE UFUNCTION OVERLOAD AS OPPOSED TO THIS. THIS MAINLY EXISTS TO ALLOW LAMBDA BINDING THE HANDLER.
	 * (Dynamic delegates do not allow for that so... we autogen this one to make experimenting in CPP a bit faster and for whenever you need to capture variables).
	 * 
	 * @param Request The Request UObject. All (de)serialized data the request data creates is tied to the lifecycle of this object.
	 * @param Handler A callback that defines how to handle success, error and completion.
     * @param OutRequestContext The Request Context associated with this request -- used to query information about the request or to cancel it while it's in flight.
	 * @param OpHandle When made as part of an Operation, you can pass this in and it'll register the request with the operation automatically. 
	 */
	void CPP_PostGoogleplayPurchaseVerify(UPostGoogleplayPurchaseVerifyRequest* Request, const FOnPostGoogleplayPurchaseVerifyFullResponse& Handler, FBeamRequestContext& OutRequestContext, FBeamOperationHandle OpHandle = FBeamOperationHandle()) const;

		
	/**
	 * @brief Makes a request to the Post /basic/payments/coupon/purchase/track endpoint of the Payments Service.
	 *
	 * PREFER THE UFUNCTION OVERLOAD AS OPPOSED TO THIS. THIS MAINLY EXISTS TO ALLOW LAMBDA BINDING THE HANDLER.
	 * (Dynamic delegates do not allow for that so... we autogen this one to make experimenting in CPP a bit faster and for whenever you need to capture variables).
	 * 
	 * @param Request The Request UObject. All (de)serialized data the request data creates is tied to the lifecycle of this object.
	 * @param Handler A callback that defines how to handle success, error and completion.
     * @param OutRequestContext The Request Context associated with this request -- used to query information about the request or to cancel it while it's in flight.
	 * @param OpHandle When made as part of an Operation, you can pass this in and it'll register the request with the operation automatically. 
	 */
	void CPP_PostCouponPurchaseTrack(UPostCouponPurchaseTrackRequest* Request, const FOnPostCouponPurchaseTrackFullResponse& Handler, FBeamRequestContext& OutRequestContext, FBeamOperationHandle OpHandle = FBeamOperationHandle()) const;

		
	/**
	 * @brief Makes a request to the Post /basic/payments/steam/purchase/complete endpoint of the Payments Service.
	 *
	 * PREFER THE UFUNCTION OVERLOAD AS OPPOSED TO THIS. THIS MAINLY EXISTS TO ALLOW LAMBDA BINDING THE HANDLER.
	 * (Dynamic delegates do not allow for that so... we autogen this one to make experimenting in CPP a bit faster and for whenever you need to capture variables).
	 * 
	 * @param Request The Request UObject. All (de)serialized data the request data creates is tied to the lifecycle of this object.
	 * @param Handler A callback that defines how to handle success, error and completion.
     * @param OutRequestContext The Request Context associated with this request -- used to query information about the request or to cancel it while it's in flight.
	 * @param OpHandle When made as part of an Operation, you can pass this in and it'll register the request with the operation automatically. 
	 */
	void CPP_PostSteamPurchaseComplete(UPostSteamPurchaseCompleteRequest* Request, const FOnPostSteamPurchaseCompleteFullResponse& Handler, FBeamRequestContext& OutRequestContext, FBeamOperationHandle OpHandle = FBeamOperationHandle()) const;

		
	/**
	 * @brief Makes a request to the Post /basic/payments/facebook/purchase/track endpoint of the Payments Service.
	 *
	 * PREFER THE UFUNCTION OVERLOAD AS OPPOSED TO THIS. THIS MAINLY EXISTS TO ALLOW LAMBDA BINDING THE HANDLER.
	 * (Dynamic delegates do not allow for that so... we autogen this one to make experimenting in CPP a bit faster and for whenever you need to capture variables).
	 * 
	 * @param Request The Request UObject. All (de)serialized data the request data creates is tied to the lifecycle of this object.
	 * @param Handler A callback that defines how to handle success, error and completion.
     * @param OutRequestContext The Request Context associated with this request -- used to query information about the request or to cancel it while it's in flight.
	 * @param OpHandle When made as part of an Operation, you can pass this in and it'll register the request with the operation automatically. 
	 */
	void CPP_PostFacebookPurchaseTrack(UPostFacebookPurchaseTrackRequest* Request, const FOnPostFacebookPurchaseTrackFullResponse& Handler, FBeamRequestContext& OutRequestContext, FBeamOperationHandle OpHandle = FBeamOperationHandle()) const;

		
	/**
	 * @brief Makes a request to the Post /basic/payments/test/purchase/verify endpoint of the Payments Service.
	 *
	 * PREFER THE UFUNCTION OVERLOAD AS OPPOSED TO THIS. THIS MAINLY EXISTS TO ALLOW LAMBDA BINDING THE HANDLER.
	 * (Dynamic delegates do not allow for that so... we autogen this one to make experimenting in CPP a bit faster and for whenever you need to capture variables).
	 * 
	 * @param Request The Request UObject. All (de)serialized data the request data creates is tied to the lifecycle of this object.
	 * @param Handler A callback that defines how to handle success, error and completion.
     * @param OutRequestContext The Request Context associated with this request -- used to query information about the request or to cancel it while it's in flight.
	 * @param OpHandle When made as part of an Operation, you can pass this in and it'll register the request with the operation automatically. 
	 */
	void CPP_PostTestPurchaseVerify(UPostTestPurchaseVerifyRequest* Request, const FOnPostTestPurchaseVerifyFullResponse& Handler, FBeamRequestContext& OutRequestContext, FBeamOperationHandle OpHandle = FBeamOperationHandle()) const;

		
	/**
	 * @brief Makes a request to the Post /basic/payments/googleplay/purchase/track endpoint of the Payments Service.
	 *
	 * PREFER THE UFUNCTION OVERLOAD AS OPPOSED TO THIS. THIS MAINLY EXISTS TO ALLOW LAMBDA BINDING THE HANDLER.
	 * (Dynamic delegates do not allow for that so... we autogen this one to make experimenting in CPP a bit faster and for whenever you need to capture variables).
	 * 
	 * @param Request The Request UObject. All (de)serialized data the request data creates is tied to the lifecycle of this object.
	 * @param Handler A callback that defines how to handle success, error and completion.
     * @param OutRequestContext The Request Context associated with this request -- used to query information about the request or to cancel it while it's in flight.
	 * @param OpHandle When made as part of an Operation, you can pass this in and it'll register the request with the operation automatically. 
	 */
	void CPP_PostGoogleplayPurchaseTrack(UPostGoogleplayPurchaseTrackRequest* Request, const FOnPostGoogleplayPurchaseTrackFullResponse& Handler, FBeamRequestContext& OutRequestContext, FBeamOperationHandle OpHandle = FBeamOperationHandle()) const;

		
	/**
	 * @brief Makes a request to the Get /basic/payments/steam/prices endpoint of the Payments Service.
	 *
	 * PREFER THE UFUNCTION OVERLOAD AS OPPOSED TO THIS. THIS MAINLY EXISTS TO ALLOW LAMBDA BINDING THE HANDLER.
	 * (Dynamic delegates do not allow for that so... we autogen this one to make experimenting in CPP a bit faster and for whenever you need to capture variables).
	 * 
	 * @param Request The Request UObject. All (de)serialized data the request data creates is tied to the lifecycle of this object.
	 * @param Handler A callback that defines how to handle success, error and completion.
     * @param OutRequestContext The Request Context associated with this request -- used to query information about the request or to cancel it while it's in flight.
	 * @param OpHandle When made as part of an Operation, you can pass this in and it'll register the request with the operation automatically. 
	 */
	void CPP_GetSteamPrices(UGetSteamPricesRequest* Request, const FOnGetSteamPricesFullResponse& Handler, FBeamRequestContext& OutRequestContext, FBeamOperationHandle OpHandle = FBeamOperationHandle()) const;

		
	/**
	 * @brief Makes a request to the Post /basic/payments/windows/purchase/verify endpoint of the Payments Service.
	 *
	 * PREFER THE UFUNCTION OVERLOAD AS OPPOSED TO THIS. THIS MAINLY EXISTS TO ALLOW LAMBDA BINDING THE HANDLER.
	 * (Dynamic delegates do not allow for that so... we autogen this one to make experimenting in CPP a bit faster and for whenever you need to capture variables).
	 * 
	 * @param Request The Request UObject. All (de)serialized data the request data creates is tied to the lifecycle of this object.
	 * @param Handler A callback that defines how to handle success, error and completion.
     * @param OutRequestContext The Request Context associated with this request -- used to query information about the request or to cancel it while it's in flight.
	 * @param OpHandle When made as part of an Operation, you can pass this in and it'll register the request with the operation automatically. 
	 */
	void CPP_PostWindowsPurchaseVerify(UPostWindowsPurchaseVerifyRequest* Request, const FOnPostWindowsPurchaseVerifyFullResponse& Handler, FBeamRequestContext& OutRequestContext, FBeamOperationHandle OpHandle = FBeamOperationHandle()) const;

		
	/**
	 * @brief Makes a request to the Post /basic/payments/itunes/purchase/verify endpoint of the Payments Service.
	 *
	 * PREFER THE UFUNCTION OVERLOAD AS OPPOSED TO THIS. THIS MAINLY EXISTS TO ALLOW LAMBDA BINDING THE HANDLER.
	 * (Dynamic delegates do not allow for that so... we autogen this one to make experimenting in CPP a bit faster and for whenever you need to capture variables).
	 * 
	 * @param Request The Request UObject. All (de)serialized data the request data creates is tied to the lifecycle of this object.
	 * @param Handler A callback that defines how to handle success, error and completion.
     * @param OutRequestContext The Request Context associated with this request -- used to query information about the request or to cancel it while it's in flight.
	 * @param OpHandle When made as part of an Operation, you can pass this in and it'll register the request with the operation automatically. 
	 */
	void CPP_PostItunesPurchaseVerify(UPostItunesPurchaseVerifyRequest* Request, const FOnPostItunesPurchaseVerifyFullResponse& Handler, FBeamRequestContext& OutRequestContext, FBeamOperationHandle OpHandle = FBeamOperationHandle()) const;

		
	/**
	 * @brief Makes a request to the Post /basic/payments/itunes/purchase/complete endpoint of the Payments Service.
	 *
	 * PREFER THE UFUNCTION OVERLOAD AS OPPOSED TO THIS. THIS MAINLY EXISTS TO ALLOW LAMBDA BINDING THE HANDLER.
	 * (Dynamic delegates do not allow for that so... we autogen this one to make experimenting in CPP a bit faster and for whenever you need to capture variables).
	 * 
	 * @param Request The Request UObject. All (de)serialized data the request data creates is tied to the lifecycle of this object.
	 * @param Handler A callback that defines how to handle success, error and completion.
     * @param OutRequestContext The Request Context associated with this request -- used to query information about the request or to cancel it while it's in flight.
	 * @param OpHandle When made as part of an Operation, you can pass this in and it'll register the request with the operation automatically. 
	 */
	void CPP_PostItunesPurchaseComplete(UPostItunesPurchaseCompleteRequest* Request, const FOnPostItunesPurchaseCompleteFullResponse& Handler, FBeamRequestContext& OutRequestContext, FBeamOperationHandle OpHandle = FBeamOperationHandle()) const;

		
	/**
	 * @brief Makes a request to the Post /basic/payments/facebook/purchase/verify endpoint of the Payments Service.
	 *
	 * PREFER THE UFUNCTION OVERLOAD AS OPPOSED TO THIS. THIS MAINLY EXISTS TO ALLOW LAMBDA BINDING THE HANDLER.
	 * (Dynamic delegates do not allow for that so... we autogen this one to make experimenting in CPP a bit faster and for whenever you need to capture variables).
	 * 
	 * @param Request The Request UObject. All (de)serialized data the request data creates is tied to the lifecycle of this object.
	 * @param Handler A callback that defines how to handle success, error and completion.
     * @param OutRequestContext The Request Context associated with this request -- used to query information about the request or to cancel it while it's in flight.
	 * @param OpHandle When made as part of an Operation, you can pass this in and it'll register the request with the operation automatically. 
	 */
	void CPP_PostFacebookPurchaseVerify(UPostFacebookPurchaseVerifyRequest* Request, const FOnPostFacebookPurchaseVerifyFullResponse& Handler, FBeamRequestContext& OutRequestContext, FBeamOperationHandle OpHandle = FBeamOperationHandle()) const;

		
	/**
	 * @brief Makes a request to the Post /basic/payments/steam/purchase/track endpoint of the Payments Service.
	 *
	 * PREFER THE UFUNCTION OVERLOAD AS OPPOSED TO THIS. THIS MAINLY EXISTS TO ALLOW LAMBDA BINDING THE HANDLER.
	 * (Dynamic delegates do not allow for that so... we autogen this one to make experimenting in CPP a bit faster and for whenever you need to capture variables).
	 * 
	 * @param Request The Request UObject. All (de)serialized data the request data creates is tied to the lifecycle of this object.
	 * @param Handler A callback that defines how to handle success, error and completion.
     * @param OutRequestContext The Request Context associated with this request -- used to query information about the request or to cancel it while it's in flight.
	 * @param OpHandle When made as part of an Operation, you can pass this in and it'll register the request with the operation automatically. 
	 */
	void CPP_PostSteamPurchaseTrack(UPostSteamPurchaseTrackRequest* Request, const FOnPostSteamPurchaseTrackFullResponse& Handler, FBeamRequestContext& OutRequestContext, FBeamOperationHandle OpHandle = FBeamOperationHandle()) const;

		
	/**
	 * @brief Makes a request to the Post /basic/payments/coupon/purchase/verify endpoint of the Payments Service.
	 *
	 * PREFER THE UFUNCTION OVERLOAD AS OPPOSED TO THIS. THIS MAINLY EXISTS TO ALLOW LAMBDA BINDING THE HANDLER.
	 * (Dynamic delegates do not allow for that so... we autogen this one to make experimenting in CPP a bit faster and for whenever you need to capture variables).
	 * 
	 * @param Request The Request UObject. All (de)serialized data the request data creates is tied to the lifecycle of this object.
	 * @param Handler A callback that defines how to handle success, error and completion.
     * @param OutRequestContext The Request Context associated with this request -- used to query information about the request or to cancel it while it's in flight.
	 * @param OpHandle When made as part of an Operation, you can pass this in and it'll register the request with the operation automatically. 
	 */
	void CPP_PostCouponPurchaseVerify(UPostCouponPurchaseVerifyRequest* Request, const FOnPostCouponPurchaseVerifyFullResponse& Handler, FBeamRequestContext& OutRequestContext, FBeamOperationHandle OpHandle = FBeamOperationHandle()) const;

		
	/**
	 * @brief Makes a request to the Get /basic/payments/windows/product endpoint of the Payments Service.
	 *
	 * PREFER THE UFUNCTION OVERLOAD AS OPPOSED TO THIS. THIS MAINLY EXISTS TO ALLOW LAMBDA BINDING THE HANDLER.
	 * (Dynamic delegates do not allow for that so... we autogen this one to make experimenting in CPP a bit faster and for whenever you need to capture variables).
	 * 
	 * @param Request The Request UObject. All (de)serialized data the request data creates is tied to the lifecycle of this object.
	 * @param Handler A callback that defines how to handle success, error and completion.
     * @param OutRequestContext The Request Context associated with this request -- used to query information about the request or to cancel it while it's in flight.
	 * @param OpHandle When made as part of an Operation, you can pass this in and it'll register the request with the operation automatically. 
	 */
	void CPP_GetWindowsProduct(UGetWindowsProductRequest* Request, const FOnGetWindowsProductFullResponse& Handler, FBeamRequestContext& OutRequestContext, FBeamOperationHandle OpHandle = FBeamOperationHandle()) const;

		
	/**
	 * @brief Makes a request to the Get /basic/payments/facebook/product endpoint of the Payments Service.
	 *
	 * PREFER THE UFUNCTION OVERLOAD AS OPPOSED TO THIS. THIS MAINLY EXISTS TO ALLOW LAMBDA BINDING THE HANDLER.
	 * (Dynamic delegates do not allow for that so... we autogen this one to make experimenting in CPP a bit faster and for whenever you need to capture variables).
	 * 
	 * @param Request The Request UObject. All (de)serialized data the request data creates is tied to the lifecycle of this object.
	 * @param Handler A callback that defines how to handle success, error and completion.
     * @param OutRequestContext The Request Context associated with this request -- used to query information about the request or to cancel it while it's in flight.
	 * @param OpHandle When made as part of an Operation, you can pass this in and it'll register the request with the operation automatically. 
	 */
	void CPP_GetFacebookProduct(UGetFacebookProductRequest* Request, const FOnGetFacebookProductFullResponse& Handler, FBeamRequestContext& OutRequestContext, FBeamOperationHandle OpHandle = FBeamOperationHandle()) const;

		
	/**
	 * @brief Makes a request to the Get /basic/payments/coupon/product endpoint of the Payments Service.
	 *
	 * PREFER THE UFUNCTION OVERLOAD AS OPPOSED TO THIS. THIS MAINLY EXISTS TO ALLOW LAMBDA BINDING THE HANDLER.
	 * (Dynamic delegates do not allow for that so... we autogen this one to make experimenting in CPP a bit faster and for whenever you need to capture variables).
	 * 
	 * @param Request The Request UObject. All (de)serialized data the request data creates is tied to the lifecycle of this object.
	 * @param Handler A callback that defines how to handle success, error and completion.
     * @param OutRequestContext The Request Context associated with this request -- used to query information about the request or to cancel it while it's in flight.
	 * @param OpHandle When made as part of an Operation, you can pass this in and it'll register the request with the operation automatically. 
	 */
	void CPP_GetCouponProduct(UGetCouponProductRequest* Request, const FOnGetCouponProductFullResponse& Handler, FBeamRequestContext& OutRequestContext, FBeamOperationHandle OpHandle = FBeamOperationHandle()) const;

		
	/**
	 * @brief Makes a request to the Get /basic/payments/steam/products endpoint of the Payments Service.
	 *
	 * PREFER THE UFUNCTION OVERLOAD AS OPPOSED TO THIS. THIS MAINLY EXISTS TO ALLOW LAMBDA BINDING THE HANDLER.
	 * (Dynamic delegates do not allow for that so... we autogen this one to make experimenting in CPP a bit faster and for whenever you need to capture variables).
	 * 
	 * @param Request The Request UObject. All (de)serialized data the request data creates is tied to the lifecycle of this object.
	 * @param Handler A callback that defines how to handle success, error and completion.
     * @param OutRequestContext The Request Context associated with this request -- used to query information about the request or to cancel it while it's in flight.
	 * @param OpHandle When made as part of an Operation, you can pass this in and it'll register the request with the operation automatically. 
	 */
	void CPP_GetSteamProducts(UGetSteamProductsRequest* Request, const FOnGetSteamProductsFullResponse& Handler, FBeamRequestContext& OutRequestContext, FBeamOperationHandle OpHandle = FBeamOperationHandle()) const;

		
	/**
	 * @brief Makes a request to the Post /basic/payments/steam/auth endpoint of the Payments Service.
	 *
	 * PREFER THE UFUNCTION OVERLOAD AS OPPOSED TO THIS. THIS MAINLY EXISTS TO ALLOW LAMBDA BINDING THE HANDLER.
	 * (Dynamic delegates do not allow for that so... we autogen this one to make experimenting in CPP a bit faster and for whenever you need to capture variables).
	 * 
	 * @param Request The Request UObject. All (de)serialized data the request data creates is tied to the lifecycle of this object.
	 * @param Handler A callback that defines how to handle success, error and completion.
     * @param OutRequestContext The Request Context associated with this request -- used to query information about the request or to cancel it while it's in flight.
	 * @param OpHandle When made as part of an Operation, you can pass this in and it'll register the request with the operation automatically. 
	 */
	void CPP_PostSteamAuth(UPostSteamAuthRequest* Request, const FOnPostSteamAuthFullResponse& Handler, FBeamRequestContext& OutRequestContext, FBeamOperationHandle OpHandle = FBeamOperationHandle()) const;

		
	/**
	 * @brief Makes a request to the Get /basic/payments/steam/product endpoint of the Payments Service.
	 *
	 * PREFER THE UFUNCTION OVERLOAD AS OPPOSED TO THIS. THIS MAINLY EXISTS TO ALLOW LAMBDA BINDING THE HANDLER.
	 * (Dynamic delegates do not allow for that so... we autogen this one to make experimenting in CPP a bit faster and for whenever you need to capture variables).
	 * 
	 * @param Request The Request UObject. All (de)serialized data the request data creates is tied to the lifecycle of this object.
	 * @param Handler A callback that defines how to handle success, error and completion.
     * @param OutRequestContext The Request Context associated with this request -- used to query information about the request or to cancel it while it's in flight.
	 * @param OpHandle When made as part of an Operation, you can pass this in and it'll register the request with the operation automatically. 
	 */
	void CPP_GetSteamProduct(UGetSteamProductRequest* Request, const FOnGetSteamProductFullResponse& Handler, FBeamRequestContext& OutRequestContext, FBeamOperationHandle OpHandle = FBeamOperationHandle()) const;

		
	/**
	 * @brief Makes a request to the Post /basic/payments/coupon/purchase/complete endpoint of the Payments Service.
	 *
	 * PREFER THE UFUNCTION OVERLOAD AS OPPOSED TO THIS. THIS MAINLY EXISTS TO ALLOW LAMBDA BINDING THE HANDLER.
	 * (Dynamic delegates do not allow for that so... we autogen this one to make experimenting in CPP a bit faster and for whenever you need to capture variables).
	 * 
	 * @param Request The Request UObject. All (de)serialized data the request data creates is tied to the lifecycle of this object.
	 * @param Handler A callback that defines how to handle success, error and completion.
     * @param OutRequestContext The Request Context associated with this request -- used to query information about the request or to cancel it while it's in flight.
	 * @param OpHandle When made as part of an Operation, you can pass this in and it'll register the request with the operation automatically. 
	 */
	void CPP_PostCouponPurchaseComplete(UPostCouponPurchaseCompleteRequest* Request, const FOnPostCouponPurchaseCompleteFullResponse& Handler, FBeamRequestContext& OutRequestContext, FBeamOperationHandle OpHandle = FBeamOperationHandle()) const;

		
	/**
	 * @brief Makes a request to the Get /basic/payments/googleplay/product endpoint of the Payments Service.
	 *
	 * PREFER THE UFUNCTION OVERLOAD AS OPPOSED TO THIS. THIS MAINLY EXISTS TO ALLOW LAMBDA BINDING THE HANDLER.
	 * (Dynamic delegates do not allow for that so... we autogen this one to make experimenting in CPP a bit faster and for whenever you need to capture variables).
	 * 
	 * @param Request The Request UObject. All (de)serialized data the request data creates is tied to the lifecycle of this object.
	 * @param Handler A callback that defines how to handle success, error and completion.
     * @param OutRequestContext The Request Context associated with this request -- used to query information about the request or to cancel it while it's in flight.
	 * @param OpHandle When made as part of an Operation, you can pass this in and it'll register the request with the operation automatically. 
	 */
	void CPP_GetGoogleplayProduct(UGetGoogleplayProductRequest* Request, const FOnGetGoogleplayProductFullResponse& Handler, FBeamRequestContext& OutRequestContext, FBeamOperationHandle OpHandle = FBeamOperationHandle()) const;

		
	/**
	 * @brief Makes a request to the Get /basic/payments/test/product endpoint of the Payments Service.
	 *
	 * PREFER THE UFUNCTION OVERLOAD AS OPPOSED TO THIS. THIS MAINLY EXISTS TO ALLOW LAMBDA BINDING THE HANDLER.
	 * (Dynamic delegates do not allow for that so... we autogen this one to make experimenting in CPP a bit faster and for whenever you need to capture variables).
	 * 
	 * @param Request The Request UObject. All (de)serialized data the request data creates is tied to the lifecycle of this object.
	 * @param Handler A callback that defines how to handle success, error and completion.
     * @param OutRequestContext The Request Context associated with this request -- used to query information about the request or to cancel it while it's in flight.
	 * @param OpHandle When made as part of an Operation, you can pass this in and it'll register the request with the operation automatically. 
	 */
	void CPP_GetTestProduct(UGetTestProductRequest* Request, const FOnGetTestProductFullResponse& Handler, FBeamRequestContext& OutRequestContext, FBeamOperationHandle OpHandle = FBeamOperationHandle()) const;

		
	/**
	 * @brief Makes a request to the Post /basic/payments/steam/purchase/verify endpoint of the Payments Service.
	 *
	 * PREFER THE UFUNCTION OVERLOAD AS OPPOSED TO THIS. THIS MAINLY EXISTS TO ALLOW LAMBDA BINDING THE HANDLER.
	 * (Dynamic delegates do not allow for that so... we autogen this one to make experimenting in CPP a bit faster and for whenever you need to capture variables).
	 * 
	 * @param Request The Request UObject. All (de)serialized data the request data creates is tied to the lifecycle of this object.
	 * @param Handler A callback that defines how to handle success, error and completion.
     * @param OutRequestContext The Request Context associated with this request -- used to query information about the request or to cancel it while it's in flight.
	 * @param OpHandle When made as part of an Operation, you can pass this in and it'll register the request with the operation automatically. 
	 */
	void CPP_PostSteamPurchaseVerify(UPostSteamPurchaseVerifyRequest* Request, const FOnPostSteamPurchaseVerifyFullResponse& Handler, FBeamRequestContext& OutRequestContext, FBeamOperationHandle OpHandle = FBeamOperationHandle()) const;

		
	/**
	 * @brief Makes a request to the Post /basic/payments/itunes/purchase/track endpoint of the Payments Service.
	 *
	 * PREFER THE UFUNCTION OVERLOAD AS OPPOSED TO THIS. THIS MAINLY EXISTS TO ALLOW LAMBDA BINDING THE HANDLER.
	 * (Dynamic delegates do not allow for that so... we autogen this one to make experimenting in CPP a bit faster and for whenever you need to capture variables).
	 * 
	 * @param Request The Request UObject. All (de)serialized data the request data creates is tied to the lifecycle of this object.
	 * @param Handler A callback that defines how to handle success, error and completion.
     * @param OutRequestContext The Request Context associated with this request -- used to query information about the request or to cancel it while it's in flight.
	 * @param OpHandle When made as part of an Operation, you can pass this in and it'll register the request with the operation automatically. 
	 */
	void CPP_PostItunesPurchaseTrack(UPostItunesPurchaseTrackRequest* Request, const FOnPostItunesPurchaseTrackFullResponse& Handler, FBeamRequestContext& OutRequestContext, FBeamOperationHandle OpHandle = FBeamOperationHandle()) const;

		
	/**
	 * @brief Makes a request to the Get /object/payments/{objectId}/ endpoint of the Payments Service.
	 *
	 * PREFER THE UFUNCTION OVERLOAD AS OPPOSED TO THIS. THIS MAINLY EXISTS TO ALLOW LAMBDA BINDING THE HANDLER.
	 * (Dynamic delegates do not allow for that so... we autogen this one to make experimenting in CPP a bit faster and for whenever you need to capture variables).
	 * 
	 * @param Request The Request UObject. All (de)serialized data the request data creates is tied to the lifecycle of this object.
	 * @param Handler A callback that defines how to handle success, error and completion.
     * @param OutRequestContext The Request Context associated with this request -- used to query information about the request or to cancel it while it's in flight.
	 * @param OpHandle When made as part of an Operation, you can pass this in and it'll register the request with the operation automatically. 
	 */
	void CPP_GetPayments(UGetPaymentsRequest* Request, const FOnGetPaymentsFullResponse& Handler, FBeamRequestContext& OutRequestContext, FBeamOperationHandle OpHandle = FBeamOperationHandle()) const;


	
	/**
	 * @brief Makes an authenticated request to the Post /basic/payments/test/purchase/begin endpoint of the Payments Service.
	 *
	 * PREFER THE UFUNCTION OVERLOAD AS OPPOSED TO THIS. THIS MAINLY EXISTS TO ALLOW LAMBDA BINDING THE HANDLER.
	 * (Dynamic delegates do not allow for that so... we autogen this one to make experimenting in CPP a bit faster).
	 * 
	 * @param UserSlot The Authenticated User Slot that is making this request.
	 * @param Request The Request UObject. All (de)serialized data the request data creates is tied to the lifecycle of this object.
	 * @param Handler A callback that defines how to handle success, error and completion.
     * @param OutRequestContext The Request Context associated with this request -- used to query information about the request or to cancel it while it's in flight.
	 * @param OpHandle When made as part of an Operation, you can pass this in and it'll register the request with the operation automatically.
     * @param CallingContext A UObject managed by the world that's making the request. Used to support multiple PIEs (see UBeamUserSlot::GetNamespacedSlotId). 
	 */
	void CPP_PostTestPurchaseBegin(const FUserSlot& UserSlot, UPostTestPurchaseBeginRequest* Request, const FOnPostTestPurchaseBeginFullResponse& Handler, FBeamRequestContext& OutRequestContext, FBeamOperationHandle OpHandle = FBeamOperationHandle(), const UObject* CallingContext = nullptr) const;

		
	/**
	 * @brief Makes an authenticated request to the Post /basic/payments/steam/purchase/fail endpoint of the Payments Service.
	 *
	 * PREFER THE UFUNCTION OVERLOAD AS OPPOSED TO THIS. THIS MAINLY EXISTS TO ALLOW LAMBDA BINDING THE HANDLER.
	 * (Dynamic delegates do not allow for that so... we autogen this one to make experimenting in CPP a bit faster).
	 * 
	 * @param UserSlot The Authenticated User Slot that is making this request.
	 * @param Request The Request UObject. All (de)serialized data the request data creates is tied to the lifecycle of this object.
	 * @param Handler A callback that defines how to handle success, error and completion.
     * @param OutRequestContext The Request Context associated with this request -- used to query information about the request or to cancel it while it's in flight.
	 * @param OpHandle When made as part of an Operation, you can pass this in and it'll register the request with the operation automatically.
     * @param CallingContext A UObject managed by the world that's making the request. Used to support multiple PIEs (see UBeamUserSlot::GetNamespacedSlotId). 
	 */
	void CPP_PostSteamPurchaseFail(const FUserSlot& UserSlot, UPostSteamPurchaseFailRequest* Request, const FOnPostSteamPurchaseFailFullResponse& Handler, FBeamRequestContext& OutRequestContext, FBeamOperationHandle OpHandle = FBeamOperationHandle(), const UObject* CallingContext = nullptr) const;

		
	/**
	 * @brief Makes an authenticated request to the Post /basic/payments/facebook/purchase/fail endpoint of the Payments Service.
	 *
	 * PREFER THE UFUNCTION OVERLOAD AS OPPOSED TO THIS. THIS MAINLY EXISTS TO ALLOW LAMBDA BINDING THE HANDLER.
	 * (Dynamic delegates do not allow for that so... we autogen this one to make experimenting in CPP a bit faster).
	 * 
	 * @param UserSlot The Authenticated User Slot that is making this request.
	 * @param Request The Request UObject. All (de)serialized data the request data creates is tied to the lifecycle of this object.
	 * @param Handler A callback that defines how to handle success, error and completion.
     * @param OutRequestContext The Request Context associated with this request -- used to query information about the request or to cancel it while it's in flight.
	 * @param OpHandle When made as part of an Operation, you can pass this in and it'll register the request with the operation automatically.
     * @param CallingContext A UObject managed by the world that's making the request. Used to support multiple PIEs (see UBeamUserSlot::GetNamespacedSlotId). 
	 */
	void CPP_PostFacebookPurchaseFail(const FUserSlot& UserSlot, UPostFacebookPurchaseFailRequest* Request, const FOnPostFacebookPurchaseFailFullResponse& Handler, FBeamRequestContext& OutRequestContext, FBeamOperationHandle OpHandle = FBeamOperationHandle(), const UObject* CallingContext = nullptr) const;

		
	/**
	 * @brief Makes an authenticated request to the Post /basic/payments/googleplay/purchase/begin endpoint of the Payments Service.
	 *
	 * PREFER THE UFUNCTION OVERLOAD AS OPPOSED TO THIS. THIS MAINLY EXISTS TO ALLOW LAMBDA BINDING THE HANDLER.
	 * (Dynamic delegates do not allow for that so... we autogen this one to make experimenting in CPP a bit faster).
	 * 
	 * @param UserSlot The Authenticated User Slot that is making this request.
	 * @param Request The Request UObject. All (de)serialized data the request data creates is tied to the lifecycle of this object.
	 * @param Handler A callback that defines how to handle success, error and completion.
     * @param OutRequestContext The Request Context associated with this request -- used to query information about the request or to cancel it while it's in flight.
	 * @param OpHandle When made as part of an Operation, you can pass this in and it'll register the request with the operation automatically.
     * @param CallingContext A UObject managed by the world that's making the request. Used to support multiple PIEs (see UBeamUserSlot::GetNamespacedSlotId). 
	 */
	void CPP_PostGoogleplayPurchaseBegin(const FUserSlot& UserSlot, UPostGoogleplayPurchaseBeginRequest* Request, const FOnPostGoogleplayPurchaseBeginFullResponse& Handler, FBeamRequestContext& OutRequestContext, FBeamOperationHandle OpHandle = FBeamOperationHandle(), const UObject* CallingContext = nullptr) const;

		
	/**
	 * @brief Makes an authenticated request to the Post /basic/payments/itunes/purchase/begin endpoint of the Payments Service.
	 *
	 * PREFER THE UFUNCTION OVERLOAD AS OPPOSED TO THIS. THIS MAINLY EXISTS TO ALLOW LAMBDA BINDING THE HANDLER.
	 * (Dynamic delegates do not allow for that so... we autogen this one to make experimenting in CPP a bit faster).
	 * 
	 * @param UserSlot The Authenticated User Slot that is making this request.
	 * @param Request The Request UObject. All (de)serialized data the request data creates is tied to the lifecycle of this object.
	 * @param Handler A callback that defines how to handle success, error and completion.
     * @param OutRequestContext The Request Context associated with this request -- used to query information about the request or to cancel it while it's in flight.
	 * @param OpHandle When made as part of an Operation, you can pass this in and it'll register the request with the operation automatically.
     * @param CallingContext A UObject managed by the world that's making the request. Used to support multiple PIEs (see UBeamUserSlot::GetNamespacedSlotId). 
	 */
	void CPP_PostItunesPurchaseBegin(const FUserSlot& UserSlot, UPostItunesPurchaseBeginRequest* Request, const FOnPostItunesPurchaseBeginFullResponse& Handler, FBeamRequestContext& OutRequestContext, FBeamOperationHandle OpHandle = FBeamOperationHandle(), const UObject* CallingContext = nullptr) const;

		
	/**
	 * @brief Makes an authenticated request to the Post /basic/payments/facebook/purchase/cancel endpoint of the Payments Service.
	 *
	 * PREFER THE UFUNCTION OVERLOAD AS OPPOSED TO THIS. THIS MAINLY EXISTS TO ALLOW LAMBDA BINDING THE HANDLER.
	 * (Dynamic delegates do not allow for that so... we autogen this one to make experimenting in CPP a bit faster).
	 * 
	 * @param UserSlot The Authenticated User Slot that is making this request.
	 * @param Request The Request UObject. All (de)serialized data the request data creates is tied to the lifecycle of this object.
	 * @param Handler A callback that defines how to handle success, error and completion.
     * @param OutRequestContext The Request Context associated with this request -- used to query information about the request or to cancel it while it's in flight.
	 * @param OpHandle When made as part of an Operation, you can pass this in and it'll register the request with the operation automatically.
     * @param CallingContext A UObject managed by the world that's making the request. Used to support multiple PIEs (see UBeamUserSlot::GetNamespacedSlotId). 
	 */
	void CPP_PostFacebookPurchaseCancel(const FUserSlot& UserSlot, UPostFacebookPurchaseCancelRequest* Request, const FOnPostFacebookPurchaseCancelFullResponse& Handler, FBeamRequestContext& OutRequestContext, FBeamOperationHandle OpHandle = FBeamOperationHandle(), const UObject* CallingContext = nullptr) const;

		
	/**
	 * @brief Makes an authenticated request to the Post /basic/payments/itunes/purchase/fail endpoint of the Payments Service.
	 *
	 * PREFER THE UFUNCTION OVERLOAD AS OPPOSED TO THIS. THIS MAINLY EXISTS TO ALLOW LAMBDA BINDING THE HANDLER.
	 * (Dynamic delegates do not allow for that so... we autogen this one to make experimenting in CPP a bit faster).
	 * 
	 * @param UserSlot The Authenticated User Slot that is making this request.
	 * @param Request The Request UObject. All (de)serialized data the request data creates is tied to the lifecycle of this object.
	 * @param Handler A callback that defines how to handle success, error and completion.
     * @param OutRequestContext The Request Context associated with this request -- used to query information about the request or to cancel it while it's in flight.
	 * @param OpHandle When made as part of an Operation, you can pass this in and it'll register the request with the operation automatically.
     * @param CallingContext A UObject managed by the world that's making the request. Used to support multiple PIEs (see UBeamUserSlot::GetNamespacedSlotId). 
	 */
	void CPP_PostItunesPurchaseFail(const FUserSlot& UserSlot, UPostItunesPurchaseFailRequest* Request, const FOnPostItunesPurchaseFailFullResponse& Handler, FBeamRequestContext& OutRequestContext, FBeamOperationHandle OpHandle = FBeamOperationHandle(), const UObject* CallingContext = nullptr) const;

		
	/**
	 * @brief Makes an authenticated request to the Post /basic/payments/test/purchase/cancel endpoint of the Payments Service.
	 *
	 * PREFER THE UFUNCTION OVERLOAD AS OPPOSED TO THIS. THIS MAINLY EXISTS TO ALLOW LAMBDA BINDING THE HANDLER.
	 * (Dynamic delegates do not allow for that so... we autogen this one to make experimenting in CPP a bit faster).
	 * 
	 * @param UserSlot The Authenticated User Slot that is making this request.
	 * @param Request The Request UObject. All (de)serialized data the request data creates is tied to the lifecycle of this object.
	 * @param Handler A callback that defines how to handle success, error and completion.
     * @param OutRequestContext The Request Context associated with this request -- used to query information about the request or to cancel it while it's in flight.
	 * @param OpHandle When made as part of an Operation, you can pass this in and it'll register the request with the operation automatically.
     * @param CallingContext A UObject managed by the world that's making the request. Used to support multiple PIEs (see UBeamUserSlot::GetNamespacedSlotId). 
	 */
	void CPP_PostTestPurchaseCancel(const FUserSlot& UserSlot, UPostTestPurchaseCancelRequest* Request, const FOnPostTestPurchaseCancelFullResponse& Handler, FBeamRequestContext& OutRequestContext, FBeamOperationHandle OpHandle = FBeamOperationHandle(), const UObject* CallingContext = nullptr) const;

		
	/**
	 * @brief Makes an authenticated request to the Post /basic/payments/test/purchase/fail endpoint of the Payments Service.
	 *
	 * PREFER THE UFUNCTION OVERLOAD AS OPPOSED TO THIS. THIS MAINLY EXISTS TO ALLOW LAMBDA BINDING THE HANDLER.
	 * (Dynamic delegates do not allow for that so... we autogen this one to make experimenting in CPP a bit faster).
	 * 
	 * @param UserSlot The Authenticated User Slot that is making this request.
	 * @param Request The Request UObject. All (de)serialized data the request data creates is tied to the lifecycle of this object.
	 * @param Handler A callback that defines how to handle success, error and completion.
     * @param OutRequestContext The Request Context associated with this request -- used to query information about the request or to cancel it while it's in flight.
	 * @param OpHandle When made as part of an Operation, you can pass this in and it'll register the request with the operation automatically.
     * @param CallingContext A UObject managed by the world that's making the request. Used to support multiple PIEs (see UBeamUserSlot::GetNamespacedSlotId). 
	 */
	void CPP_PostTestPurchaseFail(const FUserSlot& UserSlot, UPostTestPurchaseFailRequest* Request, const FOnPostTestPurchaseFailFullResponse& Handler, FBeamRequestContext& OutRequestContext, FBeamOperationHandle OpHandle = FBeamOperationHandle(), const UObject* CallingContext = nullptr) const;

		
	/**
	 * @brief Makes an authenticated request to the Post /basic/payments/coupon/purchase/cancel endpoint of the Payments Service.
	 *
	 * PREFER THE UFUNCTION OVERLOAD AS OPPOSED TO THIS. THIS MAINLY EXISTS TO ALLOW LAMBDA BINDING THE HANDLER.
	 * (Dynamic delegates do not allow for that so... we autogen this one to make experimenting in CPP a bit faster).
	 * 
	 * @param UserSlot The Authenticated User Slot that is making this request.
	 * @param Request The Request UObject. All (de)serialized data the request data creates is tied to the lifecycle of this object.
	 * @param Handler A callback that defines how to handle success, error and completion.
     * @param OutRequestContext The Request Context associated with this request -- used to query information about the request or to cancel it while it's in flight.
	 * @param OpHandle When made as part of an Operation, you can pass this in and it'll register the request with the operation automatically.
     * @param CallingContext A UObject managed by the world that's making the request. Used to support multiple PIEs (see UBeamUserSlot::GetNamespacedSlotId). 
	 */
	void CPP_PostCouponPurchaseCancel(const FUserSlot& UserSlot, UPostCouponPurchaseCancelRequest* Request, const FOnPostCouponPurchaseCancelFullResponse& Handler, FBeamRequestContext& OutRequestContext, FBeamOperationHandle OpHandle = FBeamOperationHandle(), const UObject* CallingContext = nullptr) const;

		
	/**
	 * @brief Makes an authenticated request to the Post /basic/payments/coupon/purchase/begin endpoint of the Payments Service.
	 *
	 * PREFER THE UFUNCTION OVERLOAD AS OPPOSED TO THIS. THIS MAINLY EXISTS TO ALLOW LAMBDA BINDING THE HANDLER.
	 * (Dynamic delegates do not allow for that so... we autogen this one to make experimenting in CPP a bit faster).
	 * 
	 * @param UserSlot The Authenticated User Slot that is making this request.
	 * @param Request The Request UObject. All (de)serialized data the request data creates is tied to the lifecycle of this object.
	 * @param Handler A callback that defines how to handle success, error and completion.
     * @param OutRequestContext The Request Context associated with this request -- used to query information about the request or to cancel it while it's in flight.
	 * @param OpHandle When made as part of an Operation, you can pass this in and it'll register the request with the operation automatically.
     * @param CallingContext A UObject managed by the world that's making the request. Used to support multiple PIEs (see UBeamUserSlot::GetNamespacedSlotId). 
	 */
	void CPP_PostCouponPurchaseBegin(const FUserSlot& UserSlot, UPostCouponPurchaseBeginRequest* Request, const FOnPostCouponPurchaseBeginFullResponse& Handler, FBeamRequestContext& OutRequestContext, FBeamOperationHandle OpHandle = FBeamOperationHandle(), const UObject* CallingContext = nullptr) const;

		
	/**
	 * @brief Makes an authenticated request to the Post /basic/payments/facebook/purchase/begin endpoint of the Payments Service.
	 *
	 * PREFER THE UFUNCTION OVERLOAD AS OPPOSED TO THIS. THIS MAINLY EXISTS TO ALLOW LAMBDA BINDING THE HANDLER.
	 * (Dynamic delegates do not allow for that so... we autogen this one to make experimenting in CPP a bit faster).
	 * 
	 * @param UserSlot The Authenticated User Slot that is making this request.
	 * @param Request The Request UObject. All (de)serialized data the request data creates is tied to the lifecycle of this object.
	 * @param Handler A callback that defines how to handle success, error and completion.
     * @param OutRequestContext The Request Context associated with this request -- used to query information about the request or to cancel it while it's in flight.
	 * @param OpHandle When made as part of an Operation, you can pass this in and it'll register the request with the operation automatically.
     * @param CallingContext A UObject managed by the world that's making the request. Used to support multiple PIEs (see UBeamUserSlot::GetNamespacedSlotId). 
	 */
	void CPP_PostFacebookPurchaseBegin(const FUserSlot& UserSlot, UPostFacebookPurchaseBeginRequest* Request, const FOnPostFacebookPurchaseBeginFullResponse& Handler, FBeamRequestContext& OutRequestContext, FBeamOperationHandle OpHandle = FBeamOperationHandle(), const UObject* CallingContext = nullptr) const;

		
	/**
	 * @brief Makes an authenticated request to the Get /basic/payments/steam/order endpoint of the Payments Service.
	 *
	 * PREFER THE UFUNCTION OVERLOAD AS OPPOSED TO THIS. THIS MAINLY EXISTS TO ALLOW LAMBDA BINDING THE HANDLER.
	 * (Dynamic delegates do not allow for that so... we autogen this one to make experimenting in CPP a bit faster).
	 * 
	 * @param UserSlot The Authenticated User Slot that is making this request.
	 * @param Request The Request UObject. All (de)serialized data the request data creates is tied to the lifecycle of this object.
	 * @param Handler A callback that defines how to handle success, error and completion.
     * @param OutRequestContext The Request Context associated with this request -- used to query information about the request or to cancel it while it's in flight.
	 * @param OpHandle When made as part of an Operation, you can pass this in and it'll register the request with the operation automatically.
     * @param CallingContext A UObject managed by the world that's making the request. Used to support multiple PIEs (see UBeamUserSlot::GetNamespacedSlotId). 
	 */
	void CPP_GetSteamOrder(const FUserSlot& UserSlot, UGetSteamOrderRequest* Request, const FOnGetSteamOrderFullResponse& Handler, FBeamRequestContext& OutRequestContext, FBeamOperationHandle OpHandle = FBeamOperationHandle(), const UObject* CallingContext = nullptr) const;

		
	/**
	 * @brief Makes an authenticated request to the Post /basic/payments/windows/purchase/begin endpoint of the Payments Service.
	 *
	 * PREFER THE UFUNCTION OVERLOAD AS OPPOSED TO THIS. THIS MAINLY EXISTS TO ALLOW LAMBDA BINDING THE HANDLER.
	 * (Dynamic delegates do not allow for that so... we autogen this one to make experimenting in CPP a bit faster).
	 * 
	 * @param UserSlot The Authenticated User Slot that is making this request.
	 * @param Request The Request UObject. All (de)serialized data the request data creates is tied to the lifecycle of this object.
	 * @param Handler A callback that defines how to handle success, error and completion.
     * @param OutRequestContext The Request Context associated with this request -- used to query information about the request or to cancel it while it's in flight.
	 * @param OpHandle When made as part of an Operation, you can pass this in and it'll register the request with the operation automatically.
     * @param CallingContext A UObject managed by the world that's making the request. Used to support multiple PIEs (see UBeamUserSlot::GetNamespacedSlotId). 
	 */
	void CPP_PostWindowsPurchaseBegin(const FUserSlot& UserSlot, UPostWindowsPurchaseBeginRequest* Request, const FOnPostWindowsPurchaseBeginFullResponse& Handler, FBeamRequestContext& OutRequestContext, FBeamOperationHandle OpHandle = FBeamOperationHandle(), const UObject* CallingContext = nullptr) const;

		
	/**
	 * @brief Makes an authenticated request to the Post /basic/payments/googleplay/purchase/fail endpoint of the Payments Service.
	 *
	 * PREFER THE UFUNCTION OVERLOAD AS OPPOSED TO THIS. THIS MAINLY EXISTS TO ALLOW LAMBDA BINDING THE HANDLER.
	 * (Dynamic delegates do not allow for that so... we autogen this one to make experimenting in CPP a bit faster).
	 * 
	 * @param UserSlot The Authenticated User Slot that is making this request.
	 * @param Request The Request UObject. All (de)serialized data the request data creates is tied to the lifecycle of this object.
	 * @param Handler A callback that defines how to handle success, error and completion.
     * @param OutRequestContext The Request Context associated with this request -- used to query information about the request or to cancel it while it's in flight.
	 * @param OpHandle When made as part of an Operation, you can pass this in and it'll register the request with the operation automatically.
     * @param CallingContext A UObject managed by the world that's making the request. Used to support multiple PIEs (see UBeamUserSlot::GetNamespacedSlotId). 
	 */
	void CPP_PostGoogleplayPurchaseFail(const FUserSlot& UserSlot, UPostGoogleplayPurchaseFailRequest* Request, const FOnPostGoogleplayPurchaseFailFullResponse& Handler, FBeamRequestContext& OutRequestContext, FBeamOperationHandle OpHandle = FBeamOperationHandle(), const UObject* CallingContext = nullptr) const;

		
	/**
	 * @brief Makes an authenticated request to the Post /basic/payments/googleplay/purchase/cancel endpoint of the Payments Service.
	 *
	 * PREFER THE UFUNCTION OVERLOAD AS OPPOSED TO THIS. THIS MAINLY EXISTS TO ALLOW LAMBDA BINDING THE HANDLER.
	 * (Dynamic delegates do not allow for that so... we autogen this one to make experimenting in CPP a bit faster).
	 * 
	 * @param UserSlot The Authenticated User Slot that is making this request.
	 * @param Request The Request UObject. All (de)serialized data the request data creates is tied to the lifecycle of this object.
	 * @param Handler A callback that defines how to handle success, error and completion.
     * @param OutRequestContext The Request Context associated with this request -- used to query information about the request or to cancel it while it's in flight.
	 * @param OpHandle When made as part of an Operation, you can pass this in and it'll register the request with the operation automatically.
     * @param CallingContext A UObject managed by the world that's making the request. Used to support multiple PIEs (see UBeamUserSlot::GetNamespacedSlotId). 
	 */
	void CPP_PostGoogleplayPurchaseCancel(const FUserSlot& UserSlot, UPostGoogleplayPurchaseCancelRequest* Request, const FOnPostGoogleplayPurchaseCancelFullResponse& Handler, FBeamRequestContext& OutRequestContext, FBeamOperationHandle OpHandle = FBeamOperationHandle(), const UObject* CallingContext = nullptr) const;

		
	/**
	 * @brief Makes an authenticated request to the Post /basic/payments/coupon/purchase/fail endpoint of the Payments Service.
	 *
	 * PREFER THE UFUNCTION OVERLOAD AS OPPOSED TO THIS. THIS MAINLY EXISTS TO ALLOW LAMBDA BINDING THE HANDLER.
	 * (Dynamic delegates do not allow for that so... we autogen this one to make experimenting in CPP a bit faster).
	 * 
	 * @param UserSlot The Authenticated User Slot that is making this request.
	 * @param Request The Request UObject. All (de)serialized data the request data creates is tied to the lifecycle of this object.
	 * @param Handler A callback that defines how to handle success, error and completion.
     * @param OutRequestContext The Request Context associated with this request -- used to query information about the request or to cancel it while it's in flight.
	 * @param OpHandle When made as part of an Operation, you can pass this in and it'll register the request with the operation automatically.
     * @param CallingContext A UObject managed by the world that's making the request. Used to support multiple PIEs (see UBeamUserSlot::GetNamespacedSlotId). 
	 */
	void CPP_PostCouponPurchaseFail(const FUserSlot& UserSlot, UPostCouponPurchaseFailRequest* Request, const FOnPostCouponPurchaseFailFullResponse& Handler, FBeamRequestContext& OutRequestContext, FBeamOperationHandle OpHandle = FBeamOperationHandle(), const UObject* CallingContext = nullptr) const;

		
	/**
	 * @brief Makes an authenticated request to the Post /basic/payments/steam/purchase/begin endpoint of the Payments Service.
	 *
	 * PREFER THE UFUNCTION OVERLOAD AS OPPOSED TO THIS. THIS MAINLY EXISTS TO ALLOW LAMBDA BINDING THE HANDLER.
	 * (Dynamic delegates do not allow for that so... we autogen this one to make experimenting in CPP a bit faster).
	 * 
	 * @param UserSlot The Authenticated User Slot that is making this request.
	 * @param Request The Request UObject. All (de)serialized data the request data creates is tied to the lifecycle of this object.
	 * @param Handler A callback that defines how to handle success, error and completion.
     * @param OutRequestContext The Request Context associated with this request -- used to query information about the request or to cancel it while it's in flight.
	 * @param OpHandle When made as part of an Operation, you can pass this in and it'll register the request with the operation automatically.
     * @param CallingContext A UObject managed by the world that's making the request. Used to support multiple PIEs (see UBeamUserSlot::GetNamespacedSlotId). 
	 */
	void CPP_PostSteamPurchaseBegin(const FUserSlot& UserSlot, UPostSteamPurchaseBeginRequest* Request, const FOnPostSteamPurchaseBeginFullResponse& Handler, FBeamRequestContext& OutRequestContext, FBeamOperationHandle OpHandle = FBeamOperationHandle(), const UObject* CallingContext = nullptr) const;

		
	/**
	 * @brief Makes an authenticated request to the Post /basic/payments/steam/purchase/cancel endpoint of the Payments Service.
	 *
	 * PREFER THE UFUNCTION OVERLOAD AS OPPOSED TO THIS. THIS MAINLY EXISTS TO ALLOW LAMBDA BINDING THE HANDLER.
	 * (Dynamic delegates do not allow for that so... we autogen this one to make experimenting in CPP a bit faster).
	 * 
	 * @param UserSlot The Authenticated User Slot that is making this request.
	 * @param Request The Request UObject. All (de)serialized data the request data creates is tied to the lifecycle of this object.
	 * @param Handler A callback that defines how to handle success, error and completion.
     * @param OutRequestContext The Request Context associated with this request -- used to query information about the request or to cancel it while it's in flight.
	 * @param OpHandle When made as part of an Operation, you can pass this in and it'll register the request with the operation automatically.
     * @param CallingContext A UObject managed by the world that's making the request. Used to support multiple PIEs (see UBeamUserSlot::GetNamespacedSlotId). 
	 */
	void CPP_PostSteamPurchaseCancel(const FUserSlot& UserSlot, UPostSteamPurchaseCancelRequest* Request, const FOnPostSteamPurchaseCancelFullResponse& Handler, FBeamRequestContext& OutRequestContext, FBeamOperationHandle OpHandle = FBeamOperationHandle(), const UObject* CallingContext = nullptr) const;

		
	/**
	 * @brief Makes an authenticated request to the Post /basic/payments/windows/purchase/cancel endpoint of the Payments Service.
	 *
	 * PREFER THE UFUNCTION OVERLOAD AS OPPOSED TO THIS. THIS MAINLY EXISTS TO ALLOW LAMBDA BINDING THE HANDLER.
	 * (Dynamic delegates do not allow for that so... we autogen this one to make experimenting in CPP a bit faster).
	 * 
	 * @param UserSlot The Authenticated User Slot that is making this request.
	 * @param Request The Request UObject. All (de)serialized data the request data creates is tied to the lifecycle of this object.
	 * @param Handler A callback that defines how to handle success, error and completion.
     * @param OutRequestContext The Request Context associated with this request -- used to query information about the request or to cancel it while it's in flight.
	 * @param OpHandle When made as part of an Operation, you can pass this in and it'll register the request with the operation automatically.
     * @param CallingContext A UObject managed by the world that's making the request. Used to support multiple PIEs (see UBeamUserSlot::GetNamespacedSlotId). 
	 */
	void CPP_PostWindowsPurchaseCancel(const FUserSlot& UserSlot, UPostWindowsPurchaseCancelRequest* Request, const FOnPostWindowsPurchaseCancelFullResponse& Handler, FBeamRequestContext& OutRequestContext, FBeamOperationHandle OpHandle = FBeamOperationHandle(), const UObject* CallingContext = nullptr) const;

		
	/**
	 * @brief Makes an authenticated request to the Post /basic/payments/windows/purchase/fail endpoint of the Payments Service.
	 *
	 * PREFER THE UFUNCTION OVERLOAD AS OPPOSED TO THIS. THIS MAINLY EXISTS TO ALLOW LAMBDA BINDING THE HANDLER.
	 * (Dynamic delegates do not allow for that so... we autogen this one to make experimenting in CPP a bit faster).
	 * 
	 * @param UserSlot The Authenticated User Slot that is making this request.
	 * @param Request The Request UObject. All (de)serialized data the request data creates is tied to the lifecycle of this object.
	 * @param Handler A callback that defines how to handle success, error and completion.
     * @param OutRequestContext The Request Context associated with this request -- used to query information about the request or to cancel it while it's in flight.
	 * @param OpHandle When made as part of an Operation, you can pass this in and it'll register the request with the operation automatically.
     * @param CallingContext A UObject managed by the world that's making the request. Used to support multiple PIEs (see UBeamUserSlot::GetNamespacedSlotId). 
	 */
	void CPP_PostWindowsPurchaseFail(const FUserSlot& UserSlot, UPostWindowsPurchaseFailRequest* Request, const FOnPostWindowsPurchaseFailFullResponse& Handler, FBeamRequestContext& OutRequestContext, FBeamOperationHandle OpHandle = FBeamOperationHandle(), const UObject* CallingContext = nullptr) const;

		
	/**
	 * @brief Makes an authenticated request to the Post /basic/payments/itunes/purchase/cancel endpoint of the Payments Service.
	 *
	 * PREFER THE UFUNCTION OVERLOAD AS OPPOSED TO THIS. THIS MAINLY EXISTS TO ALLOW LAMBDA BINDING THE HANDLER.
	 * (Dynamic delegates do not allow for that so... we autogen this one to make experimenting in CPP a bit faster).
	 * 
	 * @param UserSlot The Authenticated User Slot that is making this request.
	 * @param Request The Request UObject. All (de)serialized data the request data creates is tied to the lifecycle of this object.
	 * @param Handler A callback that defines how to handle success, error and completion.
     * @param OutRequestContext The Request Context associated with this request -- used to query information about the request or to cancel it while it's in flight.
	 * @param OpHandle When made as part of an Operation, you can pass this in and it'll register the request with the operation automatically.
     * @param CallingContext A UObject managed by the world that's making the request. Used to support multiple PIEs (see UBeamUserSlot::GetNamespacedSlotId). 
	 */
	void CPP_PostItunesPurchaseCancel(const FUserSlot& UserSlot, UPostItunesPurchaseCancelRequest* Request, const FOnPostItunesPurchaseCancelFullResponse& Handler, FBeamRequestContext& OutRequestContext, FBeamOperationHandle OpHandle = FBeamOperationHandle(), const UObject* CallingContext = nullptr) const;


	
	/**
	 * @brief Makes a request to the Post /basic/payments/windows/purchase/track endpoint of the Payments Service.
	 *
	 * @param Request The Request UObject. All (de)serialized data the request data creates is tied to the lifecycle of this object.
	 * @param OnSuccess What to do if the requests receives a successful response.
	 * @param OnError What to do if the request receives an error response.
	 * @param OnComplete What to after either OnSuccess or OnError have finished executing.
	 * @param OutRequestContext The Request Context associated with this request -- used to query information about the request or to cancel it while it's in flight. 
	 */
	UFUNCTION(BlueprintCallable, BlueprintInternalUseOnly, Category="Beam|Backend|Payments", meta=(AdvancedDisplay="OpHandle", AutoCreateRefTerm="OnSuccess,OnError,OnComplete,OpHandle", BeamFlowFunction))
	void PostWindowsPurchaseTrack(UPostWindowsPurchaseTrackRequest* Request, const FOnPostWindowsPurchaseTrackSuccess& OnSuccess, const FOnPostWindowsPurchaseTrackError& OnError, const FOnPostWindowsPurchaseTrackComplete& OnComplete, FBeamRequestContext& OutRequestContext, FBeamOperationHandle OpHandle = FBeamOperationHandle());

		
	/**
	 * @brief Makes a request to the Get /basic/payments/audits endpoint of the Payments Service.
	 *
	 * @param Request The Request UObject. All (de)serialized data the request data creates is tied to the lifecycle of this object.
	 * @param OnSuccess What to do if the requests receives a successful response.
	 * @param OnError What to do if the request receives an error response.
	 * @param OnComplete What to after either OnSuccess or OnError have finished executing.
	 * @param OutRequestContext The Request Context associated with this request -- used to query information about the request or to cancel it while it's in flight. 
	 */
	UFUNCTION(BlueprintCallable, BlueprintInternalUseOnly, Category="Beam|Backend|Payments", meta=(AdvancedDisplay="OpHandle", AutoCreateRefTerm="OnSuccess,OnError,OnComplete,OpHandle", BeamFlowFunction))
	void GetAudits(UGetAuditsRequest* Request, const FOnGetAuditsSuccess& OnSuccess, const FOnGetAuditsError& OnError, const FOnGetAuditsComplete& OnComplete, FBeamRequestContext& OutRequestContext, FBeamOperationHandle OpHandle = FBeamOperationHandle());

		
	/**
	 * @brief Makes a request to the Post /basic/payments/windows/purchase/complete endpoint of the Payments Service.
	 *
	 * @param Request The Request UObject. All (de)serialized data the request data creates is tied to the lifecycle of this object.
	 * @param OnSuccess What to do if the requests receives a successful response.
	 * @param OnError What to do if the request receives an error response.
	 * @param OnComplete What to after either OnSuccess or OnError have finished executing.
	 * @param OutRequestContext The Request Context associated with this request -- used to query information about the request or to cancel it while it's in flight. 
	 */
	UFUNCTION(BlueprintCallable, BlueprintInternalUseOnly, Category="Beam|Backend|Payments", meta=(AdvancedDisplay="OpHandle", AutoCreateRefTerm="OnSuccess,OnError,OnComplete,OpHandle", BeamFlowFunction))
	void PostWindowsPurchaseComplete(UPostWindowsPurchaseCompleteRequest* Request, const FOnPostWindowsPurchaseCompleteSuccess& OnSuccess, const FOnPostWindowsPurchaseCompleteError& OnError, const FOnPostWindowsPurchaseCompleteComplete& OnComplete, FBeamRequestContext& OutRequestContext, FBeamOperationHandle OpHandle = FBeamOperationHandle());

		
	/**
	 * @brief Makes a request to the Get /basic/payments/facebook/update endpoint of the Payments Service.
	 *
	 * @param Request The Request UObject. All (de)serialized data the request data creates is tied to the lifecycle of this object.
	 * @param OnSuccess What to do if the requests receives a successful response.
	 * @param OnError What to do if the request receives an error response.
	 * @param OnComplete What to after either OnSuccess or OnError have finished executing.
	 * @param OutRequestContext The Request Context associated with this request -- used to query information about the request or to cancel it while it's in flight. 
	 */
	UFUNCTION(BlueprintCallable, BlueprintInternalUseOnly, Category="Beam|Backend|Payments", meta=(AdvancedDisplay="OpHandle", AutoCreateRefTerm="OnSuccess,OnError,OnComplete,OpHandle", BeamFlowFunction))
	void GetFacebookUpdate(UGetFacebookUpdateRequest* Request, const FOnGetFacebookUpdateSuccess& OnSuccess, const FOnGetFacebookUpdateError& OnError, const FOnGetFacebookUpdateComplete& OnComplete, FBeamRequestContext& OutRequestContext, FBeamOperationHandle OpHandle = FBeamOperationHandle());

		
	/**
	 * @brief Makes a request to the Post /basic/payments/facebook/update endpoint of the Payments Service.
	 *
	 * @param Request The Request UObject. All (de)serialized data the request data creates is tied to the lifecycle of this object.
	 * @param OnSuccess What to do if the requests receives a successful response.
	 * @param OnError What to do if the request receives an error response.
	 * @param OnComplete What to after either OnSuccess or OnError have finished executing.
	 * @param OutRequestContext The Request Context associated with this request -- used to query information about the request or to cancel it while it's in flight. 
	 */
	UFUNCTION(BlueprintCallable, BlueprintInternalUseOnly, Category="Beam|Backend|Payments", meta=(AdvancedDisplay="OpHandle", AutoCreateRefTerm="OnSuccess,OnError,OnComplete,OpHandle", BeamFlowFunction))
	void PostFacebookUpdate(UPostFacebookUpdateRequest* Request, const FOnPostFacebookUpdateSuccess& OnSuccess, const FOnPostFacebookUpdateError& OnError, const FOnPostFacebookUpdateComplete& OnComplete, FBeamRequestContext& OutRequestContext, FBeamOperationHandle OpHandle = FBeamOperationHandle());

		
	/**
	 * @brief Makes a request to the Post /basic/payments/facebook/purchase/complete endpoint of the Payments Service.
	 *
	 * @param Request The Request UObject. All (de)serialized data the request data creates is tied to the lifecycle of this object.
	 * @param OnSuccess What to do if the requests receives a successful response.
	 * @param OnError What to do if the request receives an error response.
	 * @param OnComplete What to after either OnSuccess or OnError have finished executing.
	 * @param OutRequestContext The Request Context associated with this request -- used to query information about the request or to cancel it while it's in flight. 
	 */
	UFUNCTION(BlueprintCallable, BlueprintInternalUseOnly, Category="Beam|Backend|Payments", meta=(AdvancedDisplay="OpHandle", AutoCreateRefTerm="OnSuccess,OnError,OnComplete,OpHandle", BeamFlowFunction))
	void PostFacebookPurchaseComplete(UPostFacebookPurchaseCompleteRequest* Request, const FOnPostFacebookPurchaseCompleteSuccess& OnSuccess, const FOnPostFacebookPurchaseCompleteError& OnError, const FOnPostFacebookPurchaseCompleteComplete& OnComplete, FBeamRequestContext& OutRequestContext, FBeamOperationHandle OpHandle = FBeamOperationHandle());

		
	/**
	 * @brief Makes a request to the Post /basic/payments/test/purchase/complete endpoint of the Payments Service.
	 *
	 * @param Request The Request UObject. All (de)serialized data the request data creates is tied to the lifecycle of this object.
	 * @param OnSuccess What to do if the requests receives a successful response.
	 * @param OnError What to do if the request receives an error response.
	 * @param OnComplete What to after either OnSuccess or OnError have finished executing.
	 * @param OutRequestContext The Request Context associated with this request -- used to query information about the request or to cancel it while it's in flight. 
	 */
	UFUNCTION(BlueprintCallable, BlueprintInternalUseOnly, Category="Beam|Backend|Payments", meta=(AdvancedDisplay="OpHandle", AutoCreateRefTerm="OnSuccess,OnError,OnComplete,OpHandle", BeamFlowFunction))
	void PostTestPurchaseComplete(UPostTestPurchaseCompleteRequest* Request, const FOnPostTestPurchaseCompleteSuccess& OnSuccess, const FOnPostTestPurchaseCompleteError& OnError, const FOnPostTestPurchaseCompleteComplete& OnComplete, FBeamRequestContext& OutRequestContext, FBeamOperationHandle OpHandle = FBeamOperationHandle());

		
	/**
	 * @brief Makes a request to the Get /basic/payments/itunes/product endpoint of the Payments Service.
	 *
	 * @param Request The Request UObject. All (de)serialized data the request data creates is tied to the lifecycle of this object.
	 * @param OnSuccess What to do if the requests receives a successful response.
	 * @param OnError What to do if the request receives an error response.
	 * @param OnComplete What to after either OnSuccess or OnError have finished executing.
	 * @param OutRequestContext The Request Context associated with this request -- used to query information about the request or to cancel it while it's in flight. 
	 */
	UFUNCTION(BlueprintCallable, BlueprintInternalUseOnly, Category="Beam|Backend|Payments", meta=(AdvancedDisplay="OpHandle", AutoCreateRefTerm="OnSuccess,OnError,OnComplete,OpHandle", BeamFlowFunction))
	void GetItunesProduct(UGetItunesProductRequest* Request, const FOnGetItunesProductSuccess& OnSuccess, const FOnGetItunesProductError& OnError, const FOnGetItunesProductComplete& OnComplete, FBeamRequestContext& OutRequestContext, FBeamOperationHandle OpHandle = FBeamOperationHandle());

		
	/**
	 * @brief Makes a request to the Post /basic/payments/googleplay/purchase/complete endpoint of the Payments Service.
	 *
	 * @param Request The Request UObject. All (de)serialized data the request data creates is tied to the lifecycle of this object.
	 * @param OnSuccess What to do if the requests receives a successful response.
	 * @param OnError What to do if the request receives an error response.
	 * @param OnComplete What to after either OnSuccess or OnError have finished executing.
	 * @param OutRequestContext The Request Context associated with this request -- used to query information about the request or to cancel it while it's in flight. 
	 */
	UFUNCTION(BlueprintCallable, BlueprintInternalUseOnly, Category="Beam|Backend|Payments", meta=(AdvancedDisplay="OpHandle", AutoCreateRefTerm="OnSuccess,OnError,OnComplete,OpHandle", BeamFlowFunction))
	void PostGoogleplayPurchaseComplete(UPostGoogleplayPurchaseCompleteRequest* Request, const FOnPostGoogleplayPurchaseCompleteSuccess& OnSuccess, const FOnPostGoogleplayPurchaseCompleteError& OnError, const FOnPostGoogleplayPurchaseCompleteComplete& OnComplete, FBeamRequestContext& OutRequestContext, FBeamOperationHandle OpHandle = FBeamOperationHandle());

		
	/**
	 * @brief Makes a request to the Post /basic/payments/test/purchase/track endpoint of the Payments Service.
	 *
	 * @param Request The Request UObject. All (de)serialized data the request data creates is tied to the lifecycle of this object.
	 * @param OnSuccess What to do if the requests receives a successful response.
	 * @param OnError What to do if the request receives an error response.
	 * @param OnComplete What to after either OnSuccess or OnError have finished executing.
	 * @param OutRequestContext The Request Context associated with this request -- used to query information about the request or to cancel it while it's in flight. 
	 */
	UFUNCTION(BlueprintCallable, BlueprintInternalUseOnly, Category="Beam|Backend|Payments", meta=(AdvancedDisplay="OpHandle", AutoCreateRefTerm="OnSuccess,OnError,OnComplete,OpHandle", BeamFlowFunction))
	void PostTestPurchaseTrack(UPostTestPurchaseTrackRequest* Request, const FOnPostTestPurchaseTrackSuccess& OnSuccess, const FOnPostTestPurchaseTrackError& OnError, const FOnPostTestPurchaseTrackComplete& OnComplete, FBeamRequestContext& OutRequestContext, FBeamOperationHandle OpHandle = FBeamOperationHandle());

		
	/**
	 * @brief Makes a request to the Post /basic/payments/googleplay/purchase/verify endpoint of the Payments Service.
	 *
	 * @param Request The Request UObject. All (de)serialized data the request data creates is tied to the lifecycle of this object.
	 * @param OnSuccess What to do if the requests receives a successful response.
	 * @param OnError What to do if the request receives an error response.
	 * @param OnComplete What to after either OnSuccess or OnError have finished executing.
	 * @param OutRequestContext The Request Context associated with this request -- used to query information about the request or to cancel it while it's in flight. 
	 */
	UFUNCTION(BlueprintCallable, BlueprintInternalUseOnly, Category="Beam|Backend|Payments", meta=(AdvancedDisplay="OpHandle", AutoCreateRefTerm="OnSuccess,OnError,OnComplete,OpHandle", BeamFlowFunction))
	void PostGoogleplayPurchaseVerify(UPostGoogleplayPurchaseVerifyRequest* Request, const FOnPostGoogleplayPurchaseVerifySuccess& OnSuccess, const FOnPostGoogleplayPurchaseVerifyError& OnError, const FOnPostGoogleplayPurchaseVerifyComplete& OnComplete, FBeamRequestContext& OutRequestContext, FBeamOperationHandle OpHandle = FBeamOperationHandle());

		
	/**
	 * @brief Makes a request to the Post /basic/payments/coupon/purchase/track endpoint of the Payments Service.
	 *
	 * @param Request The Request UObject. All (de)serialized data the request data creates is tied to the lifecycle of this object.
	 * @param OnSuccess What to do if the requests receives a successful response.
	 * @param OnError What to do if the request receives an error response.
	 * @param OnComplete What to after either OnSuccess or OnError have finished executing.
	 * @param OutRequestContext The Request Context associated with this request -- used to query information about the request or to cancel it while it's in flight. 
	 */
	UFUNCTION(BlueprintCallable, BlueprintInternalUseOnly, Category="Beam|Backend|Payments", meta=(AdvancedDisplay="OpHandle", AutoCreateRefTerm="OnSuccess,OnError,OnComplete,OpHandle", BeamFlowFunction))
	void PostCouponPurchaseTrack(UPostCouponPurchaseTrackRequest* Request, const FOnPostCouponPurchaseTrackSuccess& OnSuccess, const FOnPostCouponPurchaseTrackError& OnError, const FOnPostCouponPurchaseTrackComplete& OnComplete, FBeamRequestContext& OutRequestContext, FBeamOperationHandle OpHandle = FBeamOperationHandle());

		
	/**
	 * @brief Makes a request to the Post /basic/payments/steam/purchase/complete endpoint of the Payments Service.
	 *
	 * @param Request The Request UObject. All (de)serialized data the request data creates is tied to the lifecycle of this object.
	 * @param OnSuccess What to do if the requests receives a successful response.
	 * @param OnError What to do if the request receives an error response.
	 * @param OnComplete What to after either OnSuccess or OnError have finished executing.
	 * @param OutRequestContext The Request Context associated with this request -- used to query information about the request or to cancel it while it's in flight. 
	 */
	UFUNCTION(BlueprintCallable, BlueprintInternalUseOnly, Category="Beam|Backend|Payments", meta=(AdvancedDisplay="OpHandle", AutoCreateRefTerm="OnSuccess,OnError,OnComplete,OpHandle", BeamFlowFunction))
	void PostSteamPurchaseComplete(UPostSteamPurchaseCompleteRequest* Request, const FOnPostSteamPurchaseCompleteSuccess& OnSuccess, const FOnPostSteamPurchaseCompleteError& OnError, const FOnPostSteamPurchaseCompleteComplete& OnComplete, FBeamRequestContext& OutRequestContext, FBeamOperationHandle OpHandle = FBeamOperationHandle());

		
	/**
	 * @brief Makes a request to the Post /basic/payments/facebook/purchase/track endpoint of the Payments Service.
	 *
	 * @param Request The Request UObject. All (de)serialized data the request data creates is tied to the lifecycle of this object.
	 * @param OnSuccess What to do if the requests receives a successful response.
	 * @param OnError What to do if the request receives an error response.
	 * @param OnComplete What to after either OnSuccess or OnError have finished executing.
	 * @param OutRequestContext The Request Context associated with this request -- used to query information about the request or to cancel it while it's in flight. 
	 */
	UFUNCTION(BlueprintCallable, BlueprintInternalUseOnly, Category="Beam|Backend|Payments", meta=(AdvancedDisplay="OpHandle", AutoCreateRefTerm="OnSuccess,OnError,OnComplete,OpHandle", BeamFlowFunction))
	void PostFacebookPurchaseTrack(UPostFacebookPurchaseTrackRequest* Request, const FOnPostFacebookPurchaseTrackSuccess& OnSuccess, const FOnPostFacebookPurchaseTrackError& OnError, const FOnPostFacebookPurchaseTrackComplete& OnComplete, FBeamRequestContext& OutRequestContext, FBeamOperationHandle OpHandle = FBeamOperationHandle());

		
	/**
	 * @brief Makes a request to the Post /basic/payments/test/purchase/verify endpoint of the Payments Service.
	 *
	 * @param Request The Request UObject. All (de)serialized data the request data creates is tied to the lifecycle of this object.
	 * @param OnSuccess What to do if the requests receives a successful response.
	 * @param OnError What to do if the request receives an error response.
	 * @param OnComplete What to after either OnSuccess or OnError have finished executing.
	 * @param OutRequestContext The Request Context associated with this request -- used to query information about the request or to cancel it while it's in flight. 
	 */
	UFUNCTION(BlueprintCallable, BlueprintInternalUseOnly, Category="Beam|Backend|Payments", meta=(AdvancedDisplay="OpHandle", AutoCreateRefTerm="OnSuccess,OnError,OnComplete,OpHandle", BeamFlowFunction))
	void PostTestPurchaseVerify(UPostTestPurchaseVerifyRequest* Request, const FOnPostTestPurchaseVerifySuccess& OnSuccess, const FOnPostTestPurchaseVerifyError& OnError, const FOnPostTestPurchaseVerifyComplete& OnComplete, FBeamRequestContext& OutRequestContext, FBeamOperationHandle OpHandle = FBeamOperationHandle());

		
	/**
	 * @brief Makes a request to the Post /basic/payments/googleplay/purchase/track endpoint of the Payments Service.
	 *
	 * @param Request The Request UObject. All (de)serialized data the request data creates is tied to the lifecycle of this object.
	 * @param OnSuccess What to do if the requests receives a successful response.
	 * @param OnError What to do if the request receives an error response.
	 * @param OnComplete What to after either OnSuccess or OnError have finished executing.
	 * @param OutRequestContext The Request Context associated with this request -- used to query information about the request or to cancel it while it's in flight. 
	 */
	UFUNCTION(BlueprintCallable, BlueprintInternalUseOnly, Category="Beam|Backend|Payments", meta=(AdvancedDisplay="OpHandle", AutoCreateRefTerm="OnSuccess,OnError,OnComplete,OpHandle", BeamFlowFunction))
	void PostGoogleplayPurchaseTrack(UPostGoogleplayPurchaseTrackRequest* Request, const FOnPostGoogleplayPurchaseTrackSuccess& OnSuccess, const FOnPostGoogleplayPurchaseTrackError& OnError, const FOnPostGoogleplayPurchaseTrackComplete& OnComplete, FBeamRequestContext& OutRequestContext, FBeamOperationHandle OpHandle = FBeamOperationHandle());

		
	/**
	 * @brief Makes a request to the Get /basic/payments/steam/prices endpoint of the Payments Service.
	 *
	 * @param Request The Request UObject. All (de)serialized data the request data creates is tied to the lifecycle of this object.
	 * @param OnSuccess What to do if the requests receives a successful response.
	 * @param OnError What to do if the request receives an error response.
	 * @param OnComplete What to after either OnSuccess or OnError have finished executing.
	 * @param OutRequestContext The Request Context associated with this request -- used to query information about the request or to cancel it while it's in flight. 
	 */
	UFUNCTION(BlueprintCallable, BlueprintInternalUseOnly, Category="Beam|Backend|Payments", meta=(AdvancedDisplay="OpHandle", AutoCreateRefTerm="OnSuccess,OnError,OnComplete,OpHandle", BeamFlowFunction))
	void GetSteamPrices(UGetSteamPricesRequest* Request, const FOnGetSteamPricesSuccess& OnSuccess, const FOnGetSteamPricesError& OnError, const FOnGetSteamPricesComplete& OnComplete, FBeamRequestContext& OutRequestContext, FBeamOperationHandle OpHandle = FBeamOperationHandle());

		
	/**
	 * @brief Makes a request to the Post /basic/payments/windows/purchase/verify endpoint of the Payments Service.
	 *
	 * @param Request The Request UObject. All (de)serialized data the request data creates is tied to the lifecycle of this object.
	 * @param OnSuccess What to do if the requests receives a successful response.
	 * @param OnError What to do if the request receives an error response.
	 * @param OnComplete What to after either OnSuccess or OnError have finished executing.
	 * @param OutRequestContext The Request Context associated with this request -- used to query information about the request or to cancel it while it's in flight. 
	 */
	UFUNCTION(BlueprintCallable, BlueprintInternalUseOnly, Category="Beam|Backend|Payments", meta=(AdvancedDisplay="OpHandle", AutoCreateRefTerm="OnSuccess,OnError,OnComplete,OpHandle", BeamFlowFunction))
	void PostWindowsPurchaseVerify(UPostWindowsPurchaseVerifyRequest* Request, const FOnPostWindowsPurchaseVerifySuccess& OnSuccess, const FOnPostWindowsPurchaseVerifyError& OnError, const FOnPostWindowsPurchaseVerifyComplete& OnComplete, FBeamRequestContext& OutRequestContext, FBeamOperationHandle OpHandle = FBeamOperationHandle());

		
	/**
	 * @brief Makes a request to the Post /basic/payments/itunes/purchase/verify endpoint of the Payments Service.
	 *
	 * @param Request The Request UObject. All (de)serialized data the request data creates is tied to the lifecycle of this object.
	 * @param OnSuccess What to do if the requests receives a successful response.
	 * @param OnError What to do if the request receives an error response.
	 * @param OnComplete What to after either OnSuccess or OnError have finished executing.
	 * @param OutRequestContext The Request Context associated with this request -- used to query information about the request or to cancel it while it's in flight. 
	 */
	UFUNCTION(BlueprintCallable, BlueprintInternalUseOnly, Category="Beam|Backend|Payments", meta=(AdvancedDisplay="OpHandle", AutoCreateRefTerm="OnSuccess,OnError,OnComplete,OpHandle", BeamFlowFunction))
	void PostItunesPurchaseVerify(UPostItunesPurchaseVerifyRequest* Request, const FOnPostItunesPurchaseVerifySuccess& OnSuccess, const FOnPostItunesPurchaseVerifyError& OnError, const FOnPostItunesPurchaseVerifyComplete& OnComplete, FBeamRequestContext& OutRequestContext, FBeamOperationHandle OpHandle = FBeamOperationHandle());

		
	/**
	 * @brief Makes a request to the Post /basic/payments/itunes/purchase/complete endpoint of the Payments Service.
	 *
	 * @param Request The Request UObject. All (de)serialized data the request data creates is tied to the lifecycle of this object.
	 * @param OnSuccess What to do if the requests receives a successful response.
	 * @param OnError What to do if the request receives an error response.
	 * @param OnComplete What to after either OnSuccess or OnError have finished executing.
	 * @param OutRequestContext The Request Context associated with this request -- used to query information about the request or to cancel it while it's in flight. 
	 */
	UFUNCTION(BlueprintCallable, BlueprintInternalUseOnly, Category="Beam|Backend|Payments", meta=(AdvancedDisplay="OpHandle", AutoCreateRefTerm="OnSuccess,OnError,OnComplete,OpHandle", BeamFlowFunction))
	void PostItunesPurchaseComplete(UPostItunesPurchaseCompleteRequest* Request, const FOnPostItunesPurchaseCompleteSuccess& OnSuccess, const FOnPostItunesPurchaseCompleteError& OnError, const FOnPostItunesPurchaseCompleteComplete& OnComplete, FBeamRequestContext& OutRequestContext, FBeamOperationHandle OpHandle = FBeamOperationHandle());

		
	/**
	 * @brief Makes a request to the Post /basic/payments/facebook/purchase/verify endpoint of the Payments Service.
	 *
	 * @param Request The Request UObject. All (de)serialized data the request data creates is tied to the lifecycle of this object.
	 * @param OnSuccess What to do if the requests receives a successful response.
	 * @param OnError What to do if the request receives an error response.
	 * @param OnComplete What to after either OnSuccess or OnError have finished executing.
	 * @param OutRequestContext The Request Context associated with this request -- used to query information about the request or to cancel it while it's in flight. 
	 */
	UFUNCTION(BlueprintCallable, BlueprintInternalUseOnly, Category="Beam|Backend|Payments", meta=(AdvancedDisplay="OpHandle", AutoCreateRefTerm="OnSuccess,OnError,OnComplete,OpHandle", BeamFlowFunction))
	void PostFacebookPurchaseVerify(UPostFacebookPurchaseVerifyRequest* Request, const FOnPostFacebookPurchaseVerifySuccess& OnSuccess, const FOnPostFacebookPurchaseVerifyError& OnError, const FOnPostFacebookPurchaseVerifyComplete& OnComplete, FBeamRequestContext& OutRequestContext, FBeamOperationHandle OpHandle = FBeamOperationHandle());

		
	/**
	 * @brief Makes a request to the Post /basic/payments/steam/purchase/track endpoint of the Payments Service.
	 *
	 * @param Request The Request UObject. All (de)serialized data the request data creates is tied to the lifecycle of this object.
	 * @param OnSuccess What to do if the requests receives a successful response.
	 * @param OnError What to do if the request receives an error response.
	 * @param OnComplete What to after either OnSuccess or OnError have finished executing.
	 * @param OutRequestContext The Request Context associated with this request -- used to query information about the request or to cancel it while it's in flight. 
	 */
	UFUNCTION(BlueprintCallable, BlueprintInternalUseOnly, Category="Beam|Backend|Payments", meta=(AdvancedDisplay="OpHandle", AutoCreateRefTerm="OnSuccess,OnError,OnComplete,OpHandle", BeamFlowFunction))
	void PostSteamPurchaseTrack(UPostSteamPurchaseTrackRequest* Request, const FOnPostSteamPurchaseTrackSuccess& OnSuccess, const FOnPostSteamPurchaseTrackError& OnError, const FOnPostSteamPurchaseTrackComplete& OnComplete, FBeamRequestContext& OutRequestContext, FBeamOperationHandle OpHandle = FBeamOperationHandle());

		
	/**
	 * @brief Makes a request to the Post /basic/payments/coupon/purchase/verify endpoint of the Payments Service.
	 *
	 * @param Request The Request UObject. All (de)serialized data the request data creates is tied to the lifecycle of this object.
	 * @param OnSuccess What to do if the requests receives a successful response.
	 * @param OnError What to do if the request receives an error response.
	 * @param OnComplete What to after either OnSuccess or OnError have finished executing.
	 * @param OutRequestContext The Request Context associated with this request -- used to query information about the request or to cancel it while it's in flight. 
	 */
	UFUNCTION(BlueprintCallable, BlueprintInternalUseOnly, Category="Beam|Backend|Payments", meta=(AdvancedDisplay="OpHandle", AutoCreateRefTerm="OnSuccess,OnError,OnComplete,OpHandle", BeamFlowFunction))
	void PostCouponPurchaseVerify(UPostCouponPurchaseVerifyRequest* Request, const FOnPostCouponPurchaseVerifySuccess& OnSuccess, const FOnPostCouponPurchaseVerifyError& OnError, const FOnPostCouponPurchaseVerifyComplete& OnComplete, FBeamRequestContext& OutRequestContext, FBeamOperationHandle OpHandle = FBeamOperationHandle());

		
	/**
	 * @brief Makes a request to the Get /basic/payments/windows/product endpoint of the Payments Service.
	 *
	 * @param Request The Request UObject. All (de)serialized data the request data creates is tied to the lifecycle of this object.
	 * @param OnSuccess What to do if the requests receives a successful response.
	 * @param OnError What to do if the request receives an error response.
	 * @param OnComplete What to after either OnSuccess or OnError have finished executing.
	 * @param OutRequestContext The Request Context associated with this request -- used to query information about the request or to cancel it while it's in flight. 
	 */
	UFUNCTION(BlueprintCallable, BlueprintInternalUseOnly, Category="Beam|Backend|Payments", meta=(AdvancedDisplay="OpHandle", AutoCreateRefTerm="OnSuccess,OnError,OnComplete,OpHandle", BeamFlowFunction))
	void GetWindowsProduct(UGetWindowsProductRequest* Request, const FOnGetWindowsProductSuccess& OnSuccess, const FOnGetWindowsProductError& OnError, const FOnGetWindowsProductComplete& OnComplete, FBeamRequestContext& OutRequestContext, FBeamOperationHandle OpHandle = FBeamOperationHandle());

		
	/**
	 * @brief Makes a request to the Get /basic/payments/facebook/product endpoint of the Payments Service.
	 *
	 * @param Request The Request UObject. All (de)serialized data the request data creates is tied to the lifecycle of this object.
	 * @param OnSuccess What to do if the requests receives a successful response.
	 * @param OnError What to do if the request receives an error response.
	 * @param OnComplete What to after either OnSuccess or OnError have finished executing.
	 * @param OutRequestContext The Request Context associated with this request -- used to query information about the request or to cancel it while it's in flight. 
	 */
	UFUNCTION(BlueprintCallable, BlueprintInternalUseOnly, Category="Beam|Backend|Payments", meta=(AdvancedDisplay="OpHandle", AutoCreateRefTerm="OnSuccess,OnError,OnComplete,OpHandle", BeamFlowFunction))
	void GetFacebookProduct(UGetFacebookProductRequest* Request, const FOnGetFacebookProductSuccess& OnSuccess, const FOnGetFacebookProductError& OnError, const FOnGetFacebookProductComplete& OnComplete, FBeamRequestContext& OutRequestContext, FBeamOperationHandle OpHandle = FBeamOperationHandle());

		
	/**
	 * @brief Makes a request to the Get /basic/payments/coupon/product endpoint of the Payments Service.
	 *
	 * @param Request The Request UObject. All (de)serialized data the request data creates is tied to the lifecycle of this object.
	 * @param OnSuccess What to do if the requests receives a successful response.
	 * @param OnError What to do if the request receives an error response.
	 * @param OnComplete What to after either OnSuccess or OnError have finished executing.
	 * @param OutRequestContext The Request Context associated with this request -- used to query information about the request or to cancel it while it's in flight. 
	 */
	UFUNCTION(BlueprintCallable, BlueprintInternalUseOnly, Category="Beam|Backend|Payments", meta=(AdvancedDisplay="OpHandle", AutoCreateRefTerm="OnSuccess,OnError,OnComplete,OpHandle", BeamFlowFunction))
	void GetCouponProduct(UGetCouponProductRequest* Request, const FOnGetCouponProductSuccess& OnSuccess, const FOnGetCouponProductError& OnError, const FOnGetCouponProductComplete& OnComplete, FBeamRequestContext& OutRequestContext, FBeamOperationHandle OpHandle = FBeamOperationHandle());

		
	/**
	 * @brief Makes a request to the Get /basic/payments/steam/products endpoint of the Payments Service.
	 *
	 * @param Request The Request UObject. All (de)serialized data the request data creates is tied to the lifecycle of this object.
	 * @param OnSuccess What to do if the requests receives a successful response.
	 * @param OnError What to do if the request receives an error response.
	 * @param OnComplete What to after either OnSuccess or OnError have finished executing.
	 * @param OutRequestContext The Request Context associated with this request -- used to query information about the request or to cancel it while it's in flight. 
	 */
	UFUNCTION(BlueprintCallable, BlueprintInternalUseOnly, Category="Beam|Backend|Payments", meta=(AdvancedDisplay="OpHandle", AutoCreateRefTerm="OnSuccess,OnError,OnComplete,OpHandle", BeamFlowFunction))
	void GetSteamProducts(UGetSteamProductsRequest* Request, const FOnGetSteamProductsSuccess& OnSuccess, const FOnGetSteamProductsError& OnError, const FOnGetSteamProductsComplete& OnComplete, FBeamRequestContext& OutRequestContext, FBeamOperationHandle OpHandle = FBeamOperationHandle());

		
	/**
	 * @brief Makes a request to the Post /basic/payments/steam/auth endpoint of the Payments Service.
	 *
	 * @param Request The Request UObject. All (de)serialized data the request data creates is tied to the lifecycle of this object.
	 * @param OnSuccess What to do if the requests receives a successful response.
	 * @param OnError What to do if the request receives an error response.
	 * @param OnComplete What to after either OnSuccess or OnError have finished executing.
	 * @param OutRequestContext The Request Context associated with this request -- used to query information about the request or to cancel it while it's in flight. 
	 */
	UFUNCTION(BlueprintCallable, BlueprintInternalUseOnly, Category="Beam|Backend|Payments", meta=(AdvancedDisplay="OpHandle", AutoCreateRefTerm="OnSuccess,OnError,OnComplete,OpHandle", BeamFlowFunction))
	void PostSteamAuth(UPostSteamAuthRequest* Request, const FOnPostSteamAuthSuccess& OnSuccess, const FOnPostSteamAuthError& OnError, const FOnPostSteamAuthComplete& OnComplete, FBeamRequestContext& OutRequestContext, FBeamOperationHandle OpHandle = FBeamOperationHandle());

		
	/**
	 * @brief Makes a request to the Get /basic/payments/steam/product endpoint of the Payments Service.
	 *
	 * @param Request The Request UObject. All (de)serialized data the request data creates is tied to the lifecycle of this object.
	 * @param OnSuccess What to do if the requests receives a successful response.
	 * @param OnError What to do if the request receives an error response.
	 * @param OnComplete What to after either OnSuccess or OnError have finished executing.
	 * @param OutRequestContext The Request Context associated with this request -- used to query information about the request or to cancel it while it's in flight. 
	 */
	UFUNCTION(BlueprintCallable, BlueprintInternalUseOnly, Category="Beam|Backend|Payments", meta=(AdvancedDisplay="OpHandle", AutoCreateRefTerm="OnSuccess,OnError,OnComplete,OpHandle", BeamFlowFunction))
	void GetSteamProduct(UGetSteamProductRequest* Request, const FOnGetSteamProductSuccess& OnSuccess, const FOnGetSteamProductError& OnError, const FOnGetSteamProductComplete& OnComplete, FBeamRequestContext& OutRequestContext, FBeamOperationHandle OpHandle = FBeamOperationHandle());

		
	/**
	 * @brief Makes a request to the Post /basic/payments/coupon/purchase/complete endpoint of the Payments Service.
	 *
	 * @param Request The Request UObject. All (de)serialized data the request data creates is tied to the lifecycle of this object.
	 * @param OnSuccess What to do if the requests receives a successful response.
	 * @param OnError What to do if the request receives an error response.
	 * @param OnComplete What to after either OnSuccess or OnError have finished executing.
	 * @param OutRequestContext The Request Context associated with this request -- used to query information about the request or to cancel it while it's in flight. 
	 */
	UFUNCTION(BlueprintCallable, BlueprintInternalUseOnly, Category="Beam|Backend|Payments", meta=(AdvancedDisplay="OpHandle", AutoCreateRefTerm="OnSuccess,OnError,OnComplete,OpHandle", BeamFlowFunction))
	void PostCouponPurchaseComplete(UPostCouponPurchaseCompleteRequest* Request, const FOnPostCouponPurchaseCompleteSuccess& OnSuccess, const FOnPostCouponPurchaseCompleteError& OnError, const FOnPostCouponPurchaseCompleteComplete& OnComplete, FBeamRequestContext& OutRequestContext, FBeamOperationHandle OpHandle = FBeamOperationHandle());

		
	/**
	 * @brief Makes a request to the Get /basic/payments/googleplay/product endpoint of the Payments Service.
	 *
	 * @param Request The Request UObject. All (de)serialized data the request data creates is tied to the lifecycle of this object.
	 * @param OnSuccess What to do if the requests receives a successful response.
	 * @param OnError What to do if the request receives an error response.
	 * @param OnComplete What to after either OnSuccess or OnError have finished executing.
	 * @param OutRequestContext The Request Context associated with this request -- used to query information about the request or to cancel it while it's in flight. 
	 */
	UFUNCTION(BlueprintCallable, BlueprintInternalUseOnly, Category="Beam|Backend|Payments", meta=(AdvancedDisplay="OpHandle", AutoCreateRefTerm="OnSuccess,OnError,OnComplete,OpHandle", BeamFlowFunction))
	void GetGoogleplayProduct(UGetGoogleplayProductRequest* Request, const FOnGetGoogleplayProductSuccess& OnSuccess, const FOnGetGoogleplayProductError& OnError, const FOnGetGoogleplayProductComplete& OnComplete, FBeamRequestContext& OutRequestContext, FBeamOperationHandle OpHandle = FBeamOperationHandle());

		
	/**
	 * @brief Makes a request to the Get /basic/payments/test/product endpoint of the Payments Service.
	 *
	 * @param Request The Request UObject. All (de)serialized data the request data creates is tied to the lifecycle of this object.
	 * @param OnSuccess What to do if the requests receives a successful response.
	 * @param OnError What to do if the request receives an error response.
	 * @param OnComplete What to after either OnSuccess or OnError have finished executing.
	 * @param OutRequestContext The Request Context associated with this request -- used to query information about the request or to cancel it while it's in flight. 
	 */
	UFUNCTION(BlueprintCallable, BlueprintInternalUseOnly, Category="Beam|Backend|Payments", meta=(AdvancedDisplay="OpHandle", AutoCreateRefTerm="OnSuccess,OnError,OnComplete,OpHandle", BeamFlowFunction))
	void GetTestProduct(UGetTestProductRequest* Request, const FOnGetTestProductSuccess& OnSuccess, const FOnGetTestProductError& OnError, const FOnGetTestProductComplete& OnComplete, FBeamRequestContext& OutRequestContext, FBeamOperationHandle OpHandle = FBeamOperationHandle());

		
	/**
	 * @brief Makes a request to the Post /basic/payments/steam/purchase/verify endpoint of the Payments Service.
	 *
	 * @param Request The Request UObject. All (de)serialized data the request data creates is tied to the lifecycle of this object.
	 * @param OnSuccess What to do if the requests receives a successful response.
	 * @param OnError What to do if the request receives an error response.
	 * @param OnComplete What to after either OnSuccess or OnError have finished executing.
	 * @param OutRequestContext The Request Context associated with this request -- used to query information about the request or to cancel it while it's in flight. 
	 */
	UFUNCTION(BlueprintCallable, BlueprintInternalUseOnly, Category="Beam|Backend|Payments", meta=(AdvancedDisplay="OpHandle", AutoCreateRefTerm="OnSuccess,OnError,OnComplete,OpHandle", BeamFlowFunction))
	void PostSteamPurchaseVerify(UPostSteamPurchaseVerifyRequest* Request, const FOnPostSteamPurchaseVerifySuccess& OnSuccess, const FOnPostSteamPurchaseVerifyError& OnError, const FOnPostSteamPurchaseVerifyComplete& OnComplete, FBeamRequestContext& OutRequestContext, FBeamOperationHandle OpHandle = FBeamOperationHandle());

		
	/**
	 * @brief Makes a request to the Post /basic/payments/itunes/purchase/track endpoint of the Payments Service.
	 *
	 * @param Request The Request UObject. All (de)serialized data the request data creates is tied to the lifecycle of this object.
	 * @param OnSuccess What to do if the requests receives a successful response.
	 * @param OnError What to do if the request receives an error response.
	 * @param OnComplete What to after either OnSuccess or OnError have finished executing.
	 * @param OutRequestContext The Request Context associated with this request -- used to query information about the request or to cancel it while it's in flight. 
	 */
	UFUNCTION(BlueprintCallable, BlueprintInternalUseOnly, Category="Beam|Backend|Payments", meta=(AdvancedDisplay="OpHandle", AutoCreateRefTerm="OnSuccess,OnError,OnComplete,OpHandle", BeamFlowFunction))
	void PostItunesPurchaseTrack(UPostItunesPurchaseTrackRequest* Request, const FOnPostItunesPurchaseTrackSuccess& OnSuccess, const FOnPostItunesPurchaseTrackError& OnError, const FOnPostItunesPurchaseTrackComplete& OnComplete, FBeamRequestContext& OutRequestContext, FBeamOperationHandle OpHandle = FBeamOperationHandle());

		
	/**
	 * @brief Makes a request to the Get /object/payments/{objectId}/ endpoint of the Payments Service.
	 *
	 * @param Request The Request UObject. All (de)serialized data the request data creates is tied to the lifecycle of this object.
	 * @param OnSuccess What to do if the requests receives a successful response.
	 * @param OnError What to do if the request receives an error response.
	 * @param OnComplete What to after either OnSuccess or OnError have finished executing.
	 * @param OutRequestContext The Request Context associated with this request -- used to query information about the request or to cancel it while it's in flight. 
	 */
	UFUNCTION(BlueprintCallable, BlueprintInternalUseOnly, Category="Beam|Backend|Payments", meta=(AdvancedDisplay="OpHandle", AutoCreateRefTerm="OnSuccess,OnError,OnComplete,OpHandle", BeamFlowFunction))
	void GetPayments(UGetPaymentsRequest* Request, const FOnGetPaymentsSuccess& OnSuccess, const FOnGetPaymentsError& OnError, const FOnGetPaymentsComplete& OnComplete, FBeamRequestContext& OutRequestContext, FBeamOperationHandle OpHandle = FBeamOperationHandle());


	
	/**
	 * @brief Makes an authenticated request to the Post /basic/payments/test/purchase/begin endpoint of the Payments Service.
	 *
	 * @param UserSlot The authenticated UserSlot with the user making the request. 
	 * @param Request The Request UObject. All (de)serialized data the request data creates is tied to the lifecycle of this object.
	 * @param OnSuccess What to do if the requests receives a successful response.
	 * @param OnError What to do if the request receives an error response.
	 * @param OnComplete What to after either OnSuccess or OnError have finished executing.
	 * @param OutRequestContext The Request Context associated with this request -- used to query information about the request or to cancel it while it's in flight.
     * @param CallingContext A UObject managed by the world that's making the request. Used to support multiple PIEs (see UBeamUserSlot::GetNamespacedSlotId).
	 */
	UFUNCTION(BlueprintCallable, BlueprintInternalUseOnly, Category="Beam|Backend|Payments", meta=(DefaultToSelf="CallingContext", AdvancedDisplay="OpHandle,CallingContext",AutoCreateRefTerm="UserSlot,OnSuccess,OnError,OnComplete,OpHandle", BeamFlowFunction))
	void PostTestPurchaseBegin(FUserSlot UserSlot, UPostTestPurchaseBeginRequest* Request, const FOnPostTestPurchaseBeginSuccess& OnSuccess, const FOnPostTestPurchaseBeginError& OnError, const FOnPostTestPurchaseBeginComplete& OnComplete, FBeamRequestContext& OutRequestContext, FBeamOperationHandle OpHandle = FBeamOperationHandle(), const UObject* CallingContext = nullptr);

		
	/**
	 * @brief Makes an authenticated request to the Post /basic/payments/steam/purchase/fail endpoint of the Payments Service.
	 *
	 * @param UserSlot The authenticated UserSlot with the user making the request. 
	 * @param Request The Request UObject. All (de)serialized data the request data creates is tied to the lifecycle of this object.
	 * @param OnSuccess What to do if the requests receives a successful response.
	 * @param OnError What to do if the request receives an error response.
	 * @param OnComplete What to after either OnSuccess or OnError have finished executing.
	 * @param OutRequestContext The Request Context associated with this request -- used to query information about the request or to cancel it while it's in flight.
     * @param CallingContext A UObject managed by the world that's making the request. Used to support multiple PIEs (see UBeamUserSlot::GetNamespacedSlotId).
	 */
	UFUNCTION(BlueprintCallable, BlueprintInternalUseOnly, Category="Beam|Backend|Payments", meta=(DefaultToSelf="CallingContext", AdvancedDisplay="OpHandle,CallingContext",AutoCreateRefTerm="UserSlot,OnSuccess,OnError,OnComplete,OpHandle", BeamFlowFunction))
	void PostSteamPurchaseFail(FUserSlot UserSlot, UPostSteamPurchaseFailRequest* Request, const FOnPostSteamPurchaseFailSuccess& OnSuccess, const FOnPostSteamPurchaseFailError& OnError, const FOnPostSteamPurchaseFailComplete& OnComplete, FBeamRequestContext& OutRequestContext, FBeamOperationHandle OpHandle = FBeamOperationHandle(), const UObject* CallingContext = nullptr);

		
	/**
	 * @brief Makes an authenticated request to the Post /basic/payments/facebook/purchase/fail endpoint of the Payments Service.
	 *
	 * @param UserSlot The authenticated UserSlot with the user making the request. 
	 * @param Request The Request UObject. All (de)serialized data the request data creates is tied to the lifecycle of this object.
	 * @param OnSuccess What to do if the requests receives a successful response.
	 * @param OnError What to do if the request receives an error response.
	 * @param OnComplete What to after either OnSuccess or OnError have finished executing.
	 * @param OutRequestContext The Request Context associated with this request -- used to query information about the request or to cancel it while it's in flight.
     * @param CallingContext A UObject managed by the world that's making the request. Used to support multiple PIEs (see UBeamUserSlot::GetNamespacedSlotId).
	 */
	UFUNCTION(BlueprintCallable, BlueprintInternalUseOnly, Category="Beam|Backend|Payments", meta=(DefaultToSelf="CallingContext", AdvancedDisplay="OpHandle,CallingContext",AutoCreateRefTerm="UserSlot,OnSuccess,OnError,OnComplete,OpHandle", BeamFlowFunction))
	void PostFacebookPurchaseFail(FUserSlot UserSlot, UPostFacebookPurchaseFailRequest* Request, const FOnPostFacebookPurchaseFailSuccess& OnSuccess, const FOnPostFacebookPurchaseFailError& OnError, const FOnPostFacebookPurchaseFailComplete& OnComplete, FBeamRequestContext& OutRequestContext, FBeamOperationHandle OpHandle = FBeamOperationHandle(), const UObject* CallingContext = nullptr);

		
	/**
	 * @brief Makes an authenticated request to the Post /basic/payments/googleplay/purchase/begin endpoint of the Payments Service.
	 *
	 * @param UserSlot The authenticated UserSlot with the user making the request. 
	 * @param Request The Request UObject. All (de)serialized data the request data creates is tied to the lifecycle of this object.
	 * @param OnSuccess What to do if the requests receives a successful response.
	 * @param OnError What to do if the request receives an error response.
	 * @param OnComplete What to after either OnSuccess or OnError have finished executing.
	 * @param OutRequestContext The Request Context associated with this request -- used to query information about the request or to cancel it while it's in flight.
     * @param CallingContext A UObject managed by the world that's making the request. Used to support multiple PIEs (see UBeamUserSlot::GetNamespacedSlotId).
	 */
	UFUNCTION(BlueprintCallable, BlueprintInternalUseOnly, Category="Beam|Backend|Payments", meta=(DefaultToSelf="CallingContext", AdvancedDisplay="OpHandle,CallingContext",AutoCreateRefTerm="UserSlot,OnSuccess,OnError,OnComplete,OpHandle", BeamFlowFunction))
	void PostGoogleplayPurchaseBegin(FUserSlot UserSlot, UPostGoogleplayPurchaseBeginRequest* Request, const FOnPostGoogleplayPurchaseBeginSuccess& OnSuccess, const FOnPostGoogleplayPurchaseBeginError& OnError, const FOnPostGoogleplayPurchaseBeginComplete& OnComplete, FBeamRequestContext& OutRequestContext, FBeamOperationHandle OpHandle = FBeamOperationHandle(), const UObject* CallingContext = nullptr);

		
	/**
	 * @brief Makes an authenticated request to the Post /basic/payments/itunes/purchase/begin endpoint of the Payments Service.
	 *
	 * @param UserSlot The authenticated UserSlot with the user making the request. 
	 * @param Request The Request UObject. All (de)serialized data the request data creates is tied to the lifecycle of this object.
	 * @param OnSuccess What to do if the requests receives a successful response.
	 * @param OnError What to do if the request receives an error response.
	 * @param OnComplete What to after either OnSuccess or OnError have finished executing.
	 * @param OutRequestContext The Request Context associated with this request -- used to query information about the request or to cancel it while it's in flight.
     * @param CallingContext A UObject managed by the world that's making the request. Used to support multiple PIEs (see UBeamUserSlot::GetNamespacedSlotId).
	 */
	UFUNCTION(BlueprintCallable, BlueprintInternalUseOnly, Category="Beam|Backend|Payments", meta=(DefaultToSelf="CallingContext", AdvancedDisplay="OpHandle,CallingContext",AutoCreateRefTerm="UserSlot,OnSuccess,OnError,OnComplete,OpHandle", BeamFlowFunction))
	void PostItunesPurchaseBegin(FUserSlot UserSlot, UPostItunesPurchaseBeginRequest* Request, const FOnPostItunesPurchaseBeginSuccess& OnSuccess, const FOnPostItunesPurchaseBeginError& OnError, const FOnPostItunesPurchaseBeginComplete& OnComplete, FBeamRequestContext& OutRequestContext, FBeamOperationHandle OpHandle = FBeamOperationHandle(), const UObject* CallingContext = nullptr);

		
	/**
	 * @brief Makes an authenticated request to the Post /basic/payments/facebook/purchase/cancel endpoint of the Payments Service.
	 *
	 * @param UserSlot The authenticated UserSlot with the user making the request. 
	 * @param Request The Request UObject. All (de)serialized data the request data creates is tied to the lifecycle of this object.
	 * @param OnSuccess What to do if the requests receives a successful response.
	 * @param OnError What to do if the request receives an error response.
	 * @param OnComplete What to after either OnSuccess or OnError have finished executing.
	 * @param OutRequestContext The Request Context associated with this request -- used to query information about the request or to cancel it while it's in flight.
     * @param CallingContext A UObject managed by the world that's making the request. Used to support multiple PIEs (see UBeamUserSlot::GetNamespacedSlotId).
	 */
	UFUNCTION(BlueprintCallable, BlueprintInternalUseOnly, Category="Beam|Backend|Payments", meta=(DefaultToSelf="CallingContext", AdvancedDisplay="OpHandle,CallingContext",AutoCreateRefTerm="UserSlot,OnSuccess,OnError,OnComplete,OpHandle", BeamFlowFunction))
	void PostFacebookPurchaseCancel(FUserSlot UserSlot, UPostFacebookPurchaseCancelRequest* Request, const FOnPostFacebookPurchaseCancelSuccess& OnSuccess, const FOnPostFacebookPurchaseCancelError& OnError, const FOnPostFacebookPurchaseCancelComplete& OnComplete, FBeamRequestContext& OutRequestContext, FBeamOperationHandle OpHandle = FBeamOperationHandle(), const UObject* CallingContext = nullptr);

		
	/**
	 * @brief Makes an authenticated request to the Post /basic/payments/itunes/purchase/fail endpoint of the Payments Service.
	 *
	 * @param UserSlot The authenticated UserSlot with the user making the request. 
	 * @param Request The Request UObject. All (de)serialized data the request data creates is tied to the lifecycle of this object.
	 * @param OnSuccess What to do if the requests receives a successful response.
	 * @param OnError What to do if the request receives an error response.
	 * @param OnComplete What to after either OnSuccess or OnError have finished executing.
	 * @param OutRequestContext The Request Context associated with this request -- used to query information about the request or to cancel it while it's in flight.
     * @param CallingContext A UObject managed by the world that's making the request. Used to support multiple PIEs (see UBeamUserSlot::GetNamespacedSlotId).
	 */
	UFUNCTION(BlueprintCallable, BlueprintInternalUseOnly, Category="Beam|Backend|Payments", meta=(DefaultToSelf="CallingContext", AdvancedDisplay="OpHandle,CallingContext",AutoCreateRefTerm="UserSlot,OnSuccess,OnError,OnComplete,OpHandle", BeamFlowFunction))
	void PostItunesPurchaseFail(FUserSlot UserSlot, UPostItunesPurchaseFailRequest* Request, const FOnPostItunesPurchaseFailSuccess& OnSuccess, const FOnPostItunesPurchaseFailError& OnError, const FOnPostItunesPurchaseFailComplete& OnComplete, FBeamRequestContext& OutRequestContext, FBeamOperationHandle OpHandle = FBeamOperationHandle(), const UObject* CallingContext = nullptr);

		
	/**
	 * @brief Makes an authenticated request to the Post /basic/payments/test/purchase/cancel endpoint of the Payments Service.
	 *
	 * @param UserSlot The authenticated UserSlot with the user making the request. 
	 * @param Request The Request UObject. All (de)serialized data the request data creates is tied to the lifecycle of this object.
	 * @param OnSuccess What to do if the requests receives a successful response.
	 * @param OnError What to do if the request receives an error response.
	 * @param OnComplete What to after either OnSuccess or OnError have finished executing.
	 * @param OutRequestContext The Request Context associated with this request -- used to query information about the request or to cancel it while it's in flight.
     * @param CallingContext A UObject managed by the world that's making the request. Used to support multiple PIEs (see UBeamUserSlot::GetNamespacedSlotId).
	 */
	UFUNCTION(BlueprintCallable, BlueprintInternalUseOnly, Category="Beam|Backend|Payments", meta=(DefaultToSelf="CallingContext", AdvancedDisplay="OpHandle,CallingContext",AutoCreateRefTerm="UserSlot,OnSuccess,OnError,OnComplete,OpHandle", BeamFlowFunction))
	void PostTestPurchaseCancel(FUserSlot UserSlot, UPostTestPurchaseCancelRequest* Request, const FOnPostTestPurchaseCancelSuccess& OnSuccess, const FOnPostTestPurchaseCancelError& OnError, const FOnPostTestPurchaseCancelComplete& OnComplete, FBeamRequestContext& OutRequestContext, FBeamOperationHandle OpHandle = FBeamOperationHandle(), const UObject* CallingContext = nullptr);

		
	/**
	 * @brief Makes an authenticated request to the Post /basic/payments/test/purchase/fail endpoint of the Payments Service.
	 *
	 * @param UserSlot The authenticated UserSlot with the user making the request. 
	 * @param Request The Request UObject. All (de)serialized data the request data creates is tied to the lifecycle of this object.
	 * @param OnSuccess What to do if the requests receives a successful response.
	 * @param OnError What to do if the request receives an error response.
	 * @param OnComplete What to after either OnSuccess or OnError have finished executing.
	 * @param OutRequestContext The Request Context associated with this request -- used to query information about the request or to cancel it while it's in flight.
     * @param CallingContext A UObject managed by the world that's making the request. Used to support multiple PIEs (see UBeamUserSlot::GetNamespacedSlotId).
	 */
	UFUNCTION(BlueprintCallable, BlueprintInternalUseOnly, Category="Beam|Backend|Payments", meta=(DefaultToSelf="CallingContext", AdvancedDisplay="OpHandle,CallingContext",AutoCreateRefTerm="UserSlot,OnSuccess,OnError,OnComplete,OpHandle", BeamFlowFunction))
	void PostTestPurchaseFail(FUserSlot UserSlot, UPostTestPurchaseFailRequest* Request, const FOnPostTestPurchaseFailSuccess& OnSuccess, const FOnPostTestPurchaseFailError& OnError, const FOnPostTestPurchaseFailComplete& OnComplete, FBeamRequestContext& OutRequestContext, FBeamOperationHandle OpHandle = FBeamOperationHandle(), const UObject* CallingContext = nullptr);

		
	/**
	 * @brief Makes an authenticated request to the Post /basic/payments/coupon/purchase/cancel endpoint of the Payments Service.
	 *
	 * @param UserSlot The authenticated UserSlot with the user making the request. 
	 * @param Request The Request UObject. All (de)serialized data the request data creates is tied to the lifecycle of this object.
	 * @param OnSuccess What to do if the requests receives a successful response.
	 * @param OnError What to do if the request receives an error response.
	 * @param OnComplete What to after either OnSuccess or OnError have finished executing.
	 * @param OutRequestContext The Request Context associated with this request -- used to query information about the request or to cancel it while it's in flight.
     * @param CallingContext A UObject managed by the world that's making the request. Used to support multiple PIEs (see UBeamUserSlot::GetNamespacedSlotId).
	 */
	UFUNCTION(BlueprintCallable, BlueprintInternalUseOnly, Category="Beam|Backend|Payments", meta=(DefaultToSelf="CallingContext", AdvancedDisplay="OpHandle,CallingContext",AutoCreateRefTerm="UserSlot,OnSuccess,OnError,OnComplete,OpHandle", BeamFlowFunction))
	void PostCouponPurchaseCancel(FUserSlot UserSlot, UPostCouponPurchaseCancelRequest* Request, const FOnPostCouponPurchaseCancelSuccess& OnSuccess, const FOnPostCouponPurchaseCancelError& OnError, const FOnPostCouponPurchaseCancelComplete& OnComplete, FBeamRequestContext& OutRequestContext, FBeamOperationHandle OpHandle = FBeamOperationHandle(), const UObject* CallingContext = nullptr);

		
	/**
	 * @brief Makes an authenticated request to the Post /basic/payments/coupon/purchase/begin endpoint of the Payments Service.
	 *
	 * @param UserSlot The authenticated UserSlot with the user making the request. 
	 * @param Request The Request UObject. All (de)serialized data the request data creates is tied to the lifecycle of this object.
	 * @param OnSuccess What to do if the requests receives a successful response.
	 * @param OnError What to do if the request receives an error response.
	 * @param OnComplete What to after either OnSuccess or OnError have finished executing.
	 * @param OutRequestContext The Request Context associated with this request -- used to query information about the request or to cancel it while it's in flight.
     * @param CallingContext A UObject managed by the world that's making the request. Used to support multiple PIEs (see UBeamUserSlot::GetNamespacedSlotId).
	 */
	UFUNCTION(BlueprintCallable, BlueprintInternalUseOnly, Category="Beam|Backend|Payments", meta=(DefaultToSelf="CallingContext", AdvancedDisplay="OpHandle,CallingContext",AutoCreateRefTerm="UserSlot,OnSuccess,OnError,OnComplete,OpHandle", BeamFlowFunction))
	void PostCouponPurchaseBegin(FUserSlot UserSlot, UPostCouponPurchaseBeginRequest* Request, const FOnPostCouponPurchaseBeginSuccess& OnSuccess, const FOnPostCouponPurchaseBeginError& OnError, const FOnPostCouponPurchaseBeginComplete& OnComplete, FBeamRequestContext& OutRequestContext, FBeamOperationHandle OpHandle = FBeamOperationHandle(), const UObject* CallingContext = nullptr);

		
	/**
	 * @brief Makes an authenticated request to the Post /basic/payments/facebook/purchase/begin endpoint of the Payments Service.
	 *
	 * @param UserSlot The authenticated UserSlot with the user making the request. 
	 * @param Request The Request UObject. All (de)serialized data the request data creates is tied to the lifecycle of this object.
	 * @param OnSuccess What to do if the requests receives a successful response.
	 * @param OnError What to do if the request receives an error response.
	 * @param OnComplete What to after either OnSuccess or OnError have finished executing.
	 * @param OutRequestContext The Request Context associated with this request -- used to query information about the request or to cancel it while it's in flight.
     * @param CallingContext A UObject managed by the world that's making the request. Used to support multiple PIEs (see UBeamUserSlot::GetNamespacedSlotId).
	 */
	UFUNCTION(BlueprintCallable, BlueprintInternalUseOnly, Category="Beam|Backend|Payments", meta=(DefaultToSelf="CallingContext", AdvancedDisplay="OpHandle,CallingContext",AutoCreateRefTerm="UserSlot,OnSuccess,OnError,OnComplete,OpHandle", BeamFlowFunction))
	void PostFacebookPurchaseBegin(FUserSlot UserSlot, UPostFacebookPurchaseBeginRequest* Request, const FOnPostFacebookPurchaseBeginSuccess& OnSuccess, const FOnPostFacebookPurchaseBeginError& OnError, const FOnPostFacebookPurchaseBeginComplete& OnComplete, FBeamRequestContext& OutRequestContext, FBeamOperationHandle OpHandle = FBeamOperationHandle(), const UObject* CallingContext = nullptr);

		
	/**
	 * @brief Makes an authenticated request to the Get /basic/payments/steam/order endpoint of the Payments Service.
	 *
	 * @param UserSlot The authenticated UserSlot with the user making the request. 
	 * @param Request The Request UObject. All (de)serialized data the request data creates is tied to the lifecycle of this object.
	 * @param OnSuccess What to do if the requests receives a successful response.
	 * @param OnError What to do if the request receives an error response.
	 * @param OnComplete What to after either OnSuccess or OnError have finished executing.
	 * @param OutRequestContext The Request Context associated with this request -- used to query information about the request or to cancel it while it's in flight.
     * @param CallingContext A UObject managed by the world that's making the request. Used to support multiple PIEs (see UBeamUserSlot::GetNamespacedSlotId).
	 */
	UFUNCTION(BlueprintCallable, BlueprintInternalUseOnly, Category="Beam|Backend|Payments", meta=(DefaultToSelf="CallingContext", AdvancedDisplay="OpHandle,CallingContext",AutoCreateRefTerm="UserSlot,OnSuccess,OnError,OnComplete,OpHandle", BeamFlowFunction))
	void GetSteamOrder(FUserSlot UserSlot, UGetSteamOrderRequest* Request, const FOnGetSteamOrderSuccess& OnSuccess, const FOnGetSteamOrderError& OnError, const FOnGetSteamOrderComplete& OnComplete, FBeamRequestContext& OutRequestContext, FBeamOperationHandle OpHandle = FBeamOperationHandle(), const UObject* CallingContext = nullptr);

		
	/**
	 * @brief Makes an authenticated request to the Post /basic/payments/windows/purchase/begin endpoint of the Payments Service.
	 *
	 * @param UserSlot The authenticated UserSlot with the user making the request. 
	 * @param Request The Request UObject. All (de)serialized data the request data creates is tied to the lifecycle of this object.
	 * @param OnSuccess What to do if the requests receives a successful response.
	 * @param OnError What to do if the request receives an error response.
	 * @param OnComplete What to after either OnSuccess or OnError have finished executing.
	 * @param OutRequestContext The Request Context associated with this request -- used to query information about the request or to cancel it while it's in flight.
     * @param CallingContext A UObject managed by the world that's making the request. Used to support multiple PIEs (see UBeamUserSlot::GetNamespacedSlotId).
	 */
	UFUNCTION(BlueprintCallable, BlueprintInternalUseOnly, Category="Beam|Backend|Payments", meta=(DefaultToSelf="CallingContext", AdvancedDisplay="OpHandle,CallingContext",AutoCreateRefTerm="UserSlot,OnSuccess,OnError,OnComplete,OpHandle", BeamFlowFunction))
	void PostWindowsPurchaseBegin(FUserSlot UserSlot, UPostWindowsPurchaseBeginRequest* Request, const FOnPostWindowsPurchaseBeginSuccess& OnSuccess, const FOnPostWindowsPurchaseBeginError& OnError, const FOnPostWindowsPurchaseBeginComplete& OnComplete, FBeamRequestContext& OutRequestContext, FBeamOperationHandle OpHandle = FBeamOperationHandle(), const UObject* CallingContext = nullptr);

		
	/**
	 * @brief Makes an authenticated request to the Post /basic/payments/googleplay/purchase/fail endpoint of the Payments Service.
	 *
	 * @param UserSlot The authenticated UserSlot with the user making the request. 
	 * @param Request The Request UObject. All (de)serialized data the request data creates is tied to the lifecycle of this object.
	 * @param OnSuccess What to do if the requests receives a successful response.
	 * @param OnError What to do if the request receives an error response.
	 * @param OnComplete What to after either OnSuccess or OnError have finished executing.
	 * @param OutRequestContext The Request Context associated with this request -- used to query information about the request or to cancel it while it's in flight.
     * @param CallingContext A UObject managed by the world that's making the request. Used to support multiple PIEs (see UBeamUserSlot::GetNamespacedSlotId).
	 */
	UFUNCTION(BlueprintCallable, BlueprintInternalUseOnly, Category="Beam|Backend|Payments", meta=(DefaultToSelf="CallingContext", AdvancedDisplay="OpHandle,CallingContext",AutoCreateRefTerm="UserSlot,OnSuccess,OnError,OnComplete,OpHandle", BeamFlowFunction))
	void PostGoogleplayPurchaseFail(FUserSlot UserSlot, UPostGoogleplayPurchaseFailRequest* Request, const FOnPostGoogleplayPurchaseFailSuccess& OnSuccess, const FOnPostGoogleplayPurchaseFailError& OnError, const FOnPostGoogleplayPurchaseFailComplete& OnComplete, FBeamRequestContext& OutRequestContext, FBeamOperationHandle OpHandle = FBeamOperationHandle(), const UObject* CallingContext = nullptr);

		
	/**
	 * @brief Makes an authenticated request to the Post /basic/payments/googleplay/purchase/cancel endpoint of the Payments Service.
	 *
	 * @param UserSlot The authenticated UserSlot with the user making the request. 
	 * @param Request The Request UObject. All (de)serialized data the request data creates is tied to the lifecycle of this object.
	 * @param OnSuccess What to do if the requests receives a successful response.
	 * @param OnError What to do if the request receives an error response.
	 * @param OnComplete What to after either OnSuccess or OnError have finished executing.
	 * @param OutRequestContext The Request Context associated with this request -- used to query information about the request or to cancel it while it's in flight.
     * @param CallingContext A UObject managed by the world that's making the request. Used to support multiple PIEs (see UBeamUserSlot::GetNamespacedSlotId).
	 */
	UFUNCTION(BlueprintCallable, BlueprintInternalUseOnly, Category="Beam|Backend|Payments", meta=(DefaultToSelf="CallingContext", AdvancedDisplay="OpHandle,CallingContext",AutoCreateRefTerm="UserSlot,OnSuccess,OnError,OnComplete,OpHandle", BeamFlowFunction))
	void PostGoogleplayPurchaseCancel(FUserSlot UserSlot, UPostGoogleplayPurchaseCancelRequest* Request, const FOnPostGoogleplayPurchaseCancelSuccess& OnSuccess, const FOnPostGoogleplayPurchaseCancelError& OnError, const FOnPostGoogleplayPurchaseCancelComplete& OnComplete, FBeamRequestContext& OutRequestContext, FBeamOperationHandle OpHandle = FBeamOperationHandle(), const UObject* CallingContext = nullptr);

		
	/**
	 * @brief Makes an authenticated request to the Post /basic/payments/coupon/purchase/fail endpoint of the Payments Service.
	 *
	 * @param UserSlot The authenticated UserSlot with the user making the request. 
	 * @param Request The Request UObject. All (de)serialized data the request data creates is tied to the lifecycle of this object.
	 * @param OnSuccess What to do if the requests receives a successful response.
	 * @param OnError What to do if the request receives an error response.
	 * @param OnComplete What to after either OnSuccess or OnError have finished executing.
	 * @param OutRequestContext The Request Context associated with this request -- used to query information about the request or to cancel it while it's in flight.
     * @param CallingContext A UObject managed by the world that's making the request. Used to support multiple PIEs (see UBeamUserSlot::GetNamespacedSlotId).
	 */
	UFUNCTION(BlueprintCallable, BlueprintInternalUseOnly, Category="Beam|Backend|Payments", meta=(DefaultToSelf="CallingContext", AdvancedDisplay="OpHandle,CallingContext",AutoCreateRefTerm="UserSlot,OnSuccess,OnError,OnComplete,OpHandle", BeamFlowFunction))
	void PostCouponPurchaseFail(FUserSlot UserSlot, UPostCouponPurchaseFailRequest* Request, const FOnPostCouponPurchaseFailSuccess& OnSuccess, const FOnPostCouponPurchaseFailError& OnError, const FOnPostCouponPurchaseFailComplete& OnComplete, FBeamRequestContext& OutRequestContext, FBeamOperationHandle OpHandle = FBeamOperationHandle(), const UObject* CallingContext = nullptr);

		
	/**
	 * @brief Makes an authenticated request to the Post /basic/payments/steam/purchase/begin endpoint of the Payments Service.
	 *
	 * @param UserSlot The authenticated UserSlot with the user making the request. 
	 * @param Request The Request UObject. All (de)serialized data the request data creates is tied to the lifecycle of this object.
	 * @param OnSuccess What to do if the requests receives a successful response.
	 * @param OnError What to do if the request receives an error response.
	 * @param OnComplete What to after either OnSuccess or OnError have finished executing.
	 * @param OutRequestContext The Request Context associated with this request -- used to query information about the request or to cancel it while it's in flight.
     * @param CallingContext A UObject managed by the world that's making the request. Used to support multiple PIEs (see UBeamUserSlot::GetNamespacedSlotId).
	 */
	UFUNCTION(BlueprintCallable, BlueprintInternalUseOnly, Category="Beam|Backend|Payments", meta=(DefaultToSelf="CallingContext", AdvancedDisplay="OpHandle,CallingContext",AutoCreateRefTerm="UserSlot,OnSuccess,OnError,OnComplete,OpHandle", BeamFlowFunction))
	void PostSteamPurchaseBegin(FUserSlot UserSlot, UPostSteamPurchaseBeginRequest* Request, const FOnPostSteamPurchaseBeginSuccess& OnSuccess, const FOnPostSteamPurchaseBeginError& OnError, const FOnPostSteamPurchaseBeginComplete& OnComplete, FBeamRequestContext& OutRequestContext, FBeamOperationHandle OpHandle = FBeamOperationHandle(), const UObject* CallingContext = nullptr);

		
	/**
	 * @brief Makes an authenticated request to the Post /basic/payments/steam/purchase/cancel endpoint of the Payments Service.
	 *
	 * @param UserSlot The authenticated UserSlot with the user making the request. 
	 * @param Request The Request UObject. All (de)serialized data the request data creates is tied to the lifecycle of this object.
	 * @param OnSuccess What to do if the requests receives a successful response.
	 * @param OnError What to do if the request receives an error response.
	 * @param OnComplete What to after either OnSuccess or OnError have finished executing.
	 * @param OutRequestContext The Request Context associated with this request -- used to query information about the request or to cancel it while it's in flight.
     * @param CallingContext A UObject managed by the world that's making the request. Used to support multiple PIEs (see UBeamUserSlot::GetNamespacedSlotId).
	 */
	UFUNCTION(BlueprintCallable, BlueprintInternalUseOnly, Category="Beam|Backend|Payments", meta=(DefaultToSelf="CallingContext", AdvancedDisplay="OpHandle,CallingContext",AutoCreateRefTerm="UserSlot,OnSuccess,OnError,OnComplete,OpHandle", BeamFlowFunction))
	void PostSteamPurchaseCancel(FUserSlot UserSlot, UPostSteamPurchaseCancelRequest* Request, const FOnPostSteamPurchaseCancelSuccess& OnSuccess, const FOnPostSteamPurchaseCancelError& OnError, const FOnPostSteamPurchaseCancelComplete& OnComplete, FBeamRequestContext& OutRequestContext, FBeamOperationHandle OpHandle = FBeamOperationHandle(), const UObject* CallingContext = nullptr);

		
	/**
	 * @brief Makes an authenticated request to the Post /basic/payments/windows/purchase/cancel endpoint of the Payments Service.
	 *
	 * @param UserSlot The authenticated UserSlot with the user making the request. 
	 * @param Request The Request UObject. All (de)serialized data the request data creates is tied to the lifecycle of this object.
	 * @param OnSuccess What to do if the requests receives a successful response.
	 * @param OnError What to do if the request receives an error response.
	 * @param OnComplete What to after either OnSuccess or OnError have finished executing.
	 * @param OutRequestContext The Request Context associated with this request -- used to query information about the request or to cancel it while it's in flight.
     * @param CallingContext A UObject managed by the world that's making the request. Used to support multiple PIEs (see UBeamUserSlot::GetNamespacedSlotId).
	 */
	UFUNCTION(BlueprintCallable, BlueprintInternalUseOnly, Category="Beam|Backend|Payments", meta=(DefaultToSelf="CallingContext", AdvancedDisplay="OpHandle,CallingContext",AutoCreateRefTerm="UserSlot,OnSuccess,OnError,OnComplete,OpHandle", BeamFlowFunction))
	void PostWindowsPurchaseCancel(FUserSlot UserSlot, UPostWindowsPurchaseCancelRequest* Request, const FOnPostWindowsPurchaseCancelSuccess& OnSuccess, const FOnPostWindowsPurchaseCancelError& OnError, const FOnPostWindowsPurchaseCancelComplete& OnComplete, FBeamRequestContext& OutRequestContext, FBeamOperationHandle OpHandle = FBeamOperationHandle(), const UObject* CallingContext = nullptr);

		
	/**
	 * @brief Makes an authenticated request to the Post /basic/payments/windows/purchase/fail endpoint of the Payments Service.
	 *
	 * @param UserSlot The authenticated UserSlot with the user making the request. 
	 * @param Request The Request UObject. All (de)serialized data the request data creates is tied to the lifecycle of this object.
	 * @param OnSuccess What to do if the requests receives a successful response.
	 * @param OnError What to do if the request receives an error response.
	 * @param OnComplete What to after either OnSuccess or OnError have finished executing.
	 * @param OutRequestContext The Request Context associated with this request -- used to query information about the request or to cancel it while it's in flight.
     * @param CallingContext A UObject managed by the world that's making the request. Used to support multiple PIEs (see UBeamUserSlot::GetNamespacedSlotId).
	 */
	UFUNCTION(BlueprintCallable, BlueprintInternalUseOnly, Category="Beam|Backend|Payments", meta=(DefaultToSelf="CallingContext", AdvancedDisplay="OpHandle,CallingContext",AutoCreateRefTerm="UserSlot,OnSuccess,OnError,OnComplete,OpHandle", BeamFlowFunction))
	void PostWindowsPurchaseFail(FUserSlot UserSlot, UPostWindowsPurchaseFailRequest* Request, const FOnPostWindowsPurchaseFailSuccess& OnSuccess, const FOnPostWindowsPurchaseFailError& OnError, const FOnPostWindowsPurchaseFailComplete& OnComplete, FBeamRequestContext& OutRequestContext, FBeamOperationHandle OpHandle = FBeamOperationHandle(), const UObject* CallingContext = nullptr);

		
	/**
	 * @brief Makes an authenticated request to the Post /basic/payments/itunes/purchase/cancel endpoint of the Payments Service.
	 *
	 * @param UserSlot The authenticated UserSlot with the user making the request. 
	 * @param Request The Request UObject. All (de)serialized data the request data creates is tied to the lifecycle of this object.
	 * @param OnSuccess What to do if the requests receives a successful response.
	 * @param OnError What to do if the request receives an error response.
	 * @param OnComplete What to after either OnSuccess or OnError have finished executing.
	 * @param OutRequestContext The Request Context associated with this request -- used to query information about the request or to cancel it while it's in flight.
     * @param CallingContext A UObject managed by the world that's making the request. Used to support multiple PIEs (see UBeamUserSlot::GetNamespacedSlotId).
	 */
	UFUNCTION(BlueprintCallable, BlueprintInternalUseOnly, Category="Beam|Backend|Payments", meta=(DefaultToSelf="CallingContext", AdvancedDisplay="OpHandle,CallingContext",AutoCreateRefTerm="UserSlot,OnSuccess,OnError,OnComplete,OpHandle", BeamFlowFunction))
	void PostItunesPurchaseCancel(FUserSlot UserSlot, UPostItunesPurchaseCancelRequest* Request, const FOnPostItunesPurchaseCancelSuccess& OnSuccess, const FOnPostItunesPurchaseCancelError& OnError, const FOnPostItunesPurchaseCancelComplete& OnComplete, FBeamRequestContext& OutRequestContext, FBeamOperationHandle OpHandle = FBeamOperationHandle(), const UObject* CallingContext = nullptr);
	

	
	/**
	 * @brief Makes a request to the Post /basic/payments/windows/purchase/track endpoint of the Payments Service.
	 *	 
	 * @param RetryConfig The retry config for this specific request. 
	 * @param Request The Request UObject. All (de)serialized data the request data creates is tied to the lifecycle of this object.
	 * @param OnSuccess What to do if the requests receives a successful response.
	 * @param OnError What to do if the request receives an error response.
	 * @param OnComplete What to after either OnSuccess or OnError have finished executing.
	 * @param OutRequestContext The Request Context -- used to query information about the request or to cancel it while it's in flight.	  
	 */
	UFUNCTION(BlueprintCallable, BlueprintInternalUseOnly, Category="Beam|Backend|Payments", meta=(AutoCreateRefTerm="OnSuccess,OnError,OnComplete", BeamFlowFunction))
	void PostWindowsPurchaseTrackWithRetry(const FBeamRetryConfig& RetryConfig, UPostWindowsPurchaseTrackRequest* Request, const FOnPostWindowsPurchaseTrackSuccess& OnSuccess, const FOnPostWindowsPurchaseTrackError& OnError, const FOnPostWindowsPurchaseTrackComplete& OnComplete, FBeamRequestContext& OutRequestContext);
		
	/**
	 * @brief Makes a request to the Get /basic/payments/audits endpoint of the Payments Service.
	 *	 
	 * @param RetryConfig The retry config for this specific request. 
	 * @param Request The Request UObject. All (de)serialized data the request data creates is tied to the lifecycle of this object.
	 * @param OnSuccess What to do if the requests receives a successful response.
	 * @param OnError What to do if the request receives an error response.
	 * @param OnComplete What to after either OnSuccess or OnError have finished executing.
	 * @param OutRequestContext The Request Context -- used to query information about the request or to cancel it while it's in flight.	  
	 */
	UFUNCTION(BlueprintCallable, BlueprintInternalUseOnly, Category="Beam|Backend|Payments", meta=(AutoCreateRefTerm="OnSuccess,OnError,OnComplete", BeamFlowFunction))
	void GetAuditsWithRetry(const FBeamRetryConfig& RetryConfig, UGetAuditsRequest* Request, const FOnGetAuditsSuccess& OnSuccess, const FOnGetAuditsError& OnError, const FOnGetAuditsComplete& OnComplete, FBeamRequestContext& OutRequestContext);
		
	/**
	 * @brief Makes a request to the Post /basic/payments/windows/purchase/complete endpoint of the Payments Service.
	 *	 
	 * @param RetryConfig The retry config for this specific request. 
	 * @param Request The Request UObject. All (de)serialized data the request data creates is tied to the lifecycle of this object.
	 * @param OnSuccess What to do if the requests receives a successful response.
	 * @param OnError What to do if the request receives an error response.
	 * @param OnComplete What to after either OnSuccess or OnError have finished executing.
	 * @param OutRequestContext The Request Context -- used to query information about the request or to cancel it while it's in flight.	  
	 */
	UFUNCTION(BlueprintCallable, BlueprintInternalUseOnly, Category="Beam|Backend|Payments", meta=(AutoCreateRefTerm="OnSuccess,OnError,OnComplete", BeamFlowFunction))
	void PostWindowsPurchaseCompleteWithRetry(const FBeamRetryConfig& RetryConfig, UPostWindowsPurchaseCompleteRequest* Request, const FOnPostWindowsPurchaseCompleteSuccess& OnSuccess, const FOnPostWindowsPurchaseCompleteError& OnError, const FOnPostWindowsPurchaseCompleteComplete& OnComplete, FBeamRequestContext& OutRequestContext);
		
	/**
	 * @brief Makes a request to the Get /basic/payments/facebook/update endpoint of the Payments Service.
	 *	 
	 * @param RetryConfig The retry config for this specific request. 
	 * @param Request The Request UObject. All (de)serialized data the request data creates is tied to the lifecycle of this object.
	 * @param OnSuccess What to do if the requests receives a successful response.
	 * @param OnError What to do if the request receives an error response.
	 * @param OnComplete What to after either OnSuccess or OnError have finished executing.
	 * @param OutRequestContext The Request Context -- used to query information about the request or to cancel it while it's in flight.	  
	 */
	UFUNCTION(BlueprintCallable, BlueprintInternalUseOnly, Category="Beam|Backend|Payments", meta=(AutoCreateRefTerm="OnSuccess,OnError,OnComplete", BeamFlowFunction))
	void GetFacebookUpdateWithRetry(const FBeamRetryConfig& RetryConfig, UGetFacebookUpdateRequest* Request, const FOnGetFacebookUpdateSuccess& OnSuccess, const FOnGetFacebookUpdateError& OnError, const FOnGetFacebookUpdateComplete& OnComplete, FBeamRequestContext& OutRequestContext);
		
	/**
	 * @brief Makes a request to the Post /basic/payments/facebook/update endpoint of the Payments Service.
	 *	 
	 * @param RetryConfig The retry config for this specific request. 
	 * @param Request The Request UObject. All (de)serialized data the request data creates is tied to the lifecycle of this object.
	 * @param OnSuccess What to do if the requests receives a successful response.
	 * @param OnError What to do if the request receives an error response.
	 * @param OnComplete What to after either OnSuccess or OnError have finished executing.
	 * @param OutRequestContext The Request Context -- used to query information about the request or to cancel it while it's in flight.	  
	 */
	UFUNCTION(BlueprintCallable, BlueprintInternalUseOnly, Category="Beam|Backend|Payments", meta=(AutoCreateRefTerm="OnSuccess,OnError,OnComplete", BeamFlowFunction))
	void PostFacebookUpdateWithRetry(const FBeamRetryConfig& RetryConfig, UPostFacebookUpdateRequest* Request, const FOnPostFacebookUpdateSuccess& OnSuccess, const FOnPostFacebookUpdateError& OnError, const FOnPostFacebookUpdateComplete& OnComplete, FBeamRequestContext& OutRequestContext);
		
	/**
	 * @brief Makes a request to the Post /basic/payments/facebook/purchase/complete endpoint of the Payments Service.
	 *	 
	 * @param RetryConfig The retry config for this specific request. 
	 * @param Request The Request UObject. All (de)serialized data the request data creates is tied to the lifecycle of this object.
	 * @param OnSuccess What to do if the requests receives a successful response.
	 * @param OnError What to do if the request receives an error response.
	 * @param OnComplete What to after either OnSuccess or OnError have finished executing.
	 * @param OutRequestContext The Request Context -- used to query information about the request or to cancel it while it's in flight.	  
	 */
	UFUNCTION(BlueprintCallable, BlueprintInternalUseOnly, Category="Beam|Backend|Payments", meta=(AutoCreateRefTerm="OnSuccess,OnError,OnComplete", BeamFlowFunction))
	void PostFacebookPurchaseCompleteWithRetry(const FBeamRetryConfig& RetryConfig, UPostFacebookPurchaseCompleteRequest* Request, const FOnPostFacebookPurchaseCompleteSuccess& OnSuccess, const FOnPostFacebookPurchaseCompleteError& OnError, const FOnPostFacebookPurchaseCompleteComplete& OnComplete, FBeamRequestContext& OutRequestContext);
		
	/**
	 * @brief Makes a request to the Post /basic/payments/test/purchase/complete endpoint of the Payments Service.
	 *	 
	 * @param RetryConfig The retry config for this specific request. 
	 * @param Request The Request UObject. All (de)serialized data the request data creates is tied to the lifecycle of this object.
	 * @param OnSuccess What to do if the requests receives a successful response.
	 * @param OnError What to do if the request receives an error response.
	 * @param OnComplete What to after either OnSuccess or OnError have finished executing.
	 * @param OutRequestContext The Request Context -- used to query information about the request or to cancel it while it's in flight.	  
	 */
	UFUNCTION(BlueprintCallable, BlueprintInternalUseOnly, Category="Beam|Backend|Payments", meta=(AutoCreateRefTerm="OnSuccess,OnError,OnComplete", BeamFlowFunction))
	void PostTestPurchaseCompleteWithRetry(const FBeamRetryConfig& RetryConfig, UPostTestPurchaseCompleteRequest* Request, const FOnPostTestPurchaseCompleteSuccess& OnSuccess, const FOnPostTestPurchaseCompleteError& OnError, const FOnPostTestPurchaseCompleteComplete& OnComplete, FBeamRequestContext& OutRequestContext);
		
	/**
	 * @brief Makes a request to the Get /basic/payments/itunes/product endpoint of the Payments Service.
	 *	 
	 * @param RetryConfig The retry config for this specific request. 
	 * @param Request The Request UObject. All (de)serialized data the request data creates is tied to the lifecycle of this object.
	 * @param OnSuccess What to do if the requests receives a successful response.
	 * @param OnError What to do if the request receives an error response.
	 * @param OnComplete What to after either OnSuccess or OnError have finished executing.
	 * @param OutRequestContext The Request Context -- used to query information about the request or to cancel it while it's in flight.	  
	 */
	UFUNCTION(BlueprintCallable, BlueprintInternalUseOnly, Category="Beam|Backend|Payments", meta=(AutoCreateRefTerm="OnSuccess,OnError,OnComplete", BeamFlowFunction))
	void GetItunesProductWithRetry(const FBeamRetryConfig& RetryConfig, UGetItunesProductRequest* Request, const FOnGetItunesProductSuccess& OnSuccess, const FOnGetItunesProductError& OnError, const FOnGetItunesProductComplete& OnComplete, FBeamRequestContext& OutRequestContext);
		
	/**
	 * @brief Makes a request to the Post /basic/payments/googleplay/purchase/complete endpoint of the Payments Service.
	 *	 
	 * @param RetryConfig The retry config for this specific request. 
	 * @param Request The Request UObject. All (de)serialized data the request data creates is tied to the lifecycle of this object.
	 * @param OnSuccess What to do if the requests receives a successful response.
	 * @param OnError What to do if the request receives an error response.
	 * @param OnComplete What to after either OnSuccess or OnError have finished executing.
	 * @param OutRequestContext The Request Context -- used to query information about the request or to cancel it while it's in flight.	  
	 */
	UFUNCTION(BlueprintCallable, BlueprintInternalUseOnly, Category="Beam|Backend|Payments", meta=(AutoCreateRefTerm="OnSuccess,OnError,OnComplete", BeamFlowFunction))
	void PostGoogleplayPurchaseCompleteWithRetry(const FBeamRetryConfig& RetryConfig, UPostGoogleplayPurchaseCompleteRequest* Request, const FOnPostGoogleplayPurchaseCompleteSuccess& OnSuccess, const FOnPostGoogleplayPurchaseCompleteError& OnError, const FOnPostGoogleplayPurchaseCompleteComplete& OnComplete, FBeamRequestContext& OutRequestContext);
		
	/**
	 * @brief Makes a request to the Post /basic/payments/test/purchase/track endpoint of the Payments Service.
	 *	 
	 * @param RetryConfig The retry config for this specific request. 
	 * @param Request The Request UObject. All (de)serialized data the request data creates is tied to the lifecycle of this object.
	 * @param OnSuccess What to do if the requests receives a successful response.
	 * @param OnError What to do if the request receives an error response.
	 * @param OnComplete What to after either OnSuccess or OnError have finished executing.
	 * @param OutRequestContext The Request Context -- used to query information about the request or to cancel it while it's in flight.	  
	 */
	UFUNCTION(BlueprintCallable, BlueprintInternalUseOnly, Category="Beam|Backend|Payments", meta=(AutoCreateRefTerm="OnSuccess,OnError,OnComplete", BeamFlowFunction))
	void PostTestPurchaseTrackWithRetry(const FBeamRetryConfig& RetryConfig, UPostTestPurchaseTrackRequest* Request, const FOnPostTestPurchaseTrackSuccess& OnSuccess, const FOnPostTestPurchaseTrackError& OnError, const FOnPostTestPurchaseTrackComplete& OnComplete, FBeamRequestContext& OutRequestContext);
		
	/**
	 * @brief Makes a request to the Post /basic/payments/googleplay/purchase/verify endpoint of the Payments Service.
	 *	 
	 * @param RetryConfig The retry config for this specific request. 
	 * @param Request The Request UObject. All (de)serialized data the request data creates is tied to the lifecycle of this object.
	 * @param OnSuccess What to do if the requests receives a successful response.
	 * @param OnError What to do if the request receives an error response.
	 * @param OnComplete What to after either OnSuccess or OnError have finished executing.
	 * @param OutRequestContext The Request Context -- used to query information about the request or to cancel it while it's in flight.	  
	 */
	UFUNCTION(BlueprintCallable, BlueprintInternalUseOnly, Category="Beam|Backend|Payments", meta=(AutoCreateRefTerm="OnSuccess,OnError,OnComplete", BeamFlowFunction))
	void PostGoogleplayPurchaseVerifyWithRetry(const FBeamRetryConfig& RetryConfig, UPostGoogleplayPurchaseVerifyRequest* Request, const FOnPostGoogleplayPurchaseVerifySuccess& OnSuccess, const FOnPostGoogleplayPurchaseVerifyError& OnError, const FOnPostGoogleplayPurchaseVerifyComplete& OnComplete, FBeamRequestContext& OutRequestContext);
		
	/**
	 * @brief Makes a request to the Post /basic/payments/coupon/purchase/track endpoint of the Payments Service.
	 *	 
	 * @param RetryConfig The retry config for this specific request. 
	 * @param Request The Request UObject. All (de)serialized data the request data creates is tied to the lifecycle of this object.
	 * @param OnSuccess What to do if the requests receives a successful response.
	 * @param OnError What to do if the request receives an error response.
	 * @param OnComplete What to after either OnSuccess or OnError have finished executing.
	 * @param OutRequestContext The Request Context -- used to query information about the request or to cancel it while it's in flight.	  
	 */
	UFUNCTION(BlueprintCallable, BlueprintInternalUseOnly, Category="Beam|Backend|Payments", meta=(AutoCreateRefTerm="OnSuccess,OnError,OnComplete", BeamFlowFunction))
	void PostCouponPurchaseTrackWithRetry(const FBeamRetryConfig& RetryConfig, UPostCouponPurchaseTrackRequest* Request, const FOnPostCouponPurchaseTrackSuccess& OnSuccess, const FOnPostCouponPurchaseTrackError& OnError, const FOnPostCouponPurchaseTrackComplete& OnComplete, FBeamRequestContext& OutRequestContext);
		
	/**
	 * @brief Makes a request to the Post /basic/payments/steam/purchase/complete endpoint of the Payments Service.
	 *	 
	 * @param RetryConfig The retry config for this specific request. 
	 * @param Request The Request UObject. All (de)serialized data the request data creates is tied to the lifecycle of this object.
	 * @param OnSuccess What to do if the requests receives a successful response.
	 * @param OnError What to do if the request receives an error response.
	 * @param OnComplete What to after either OnSuccess or OnError have finished executing.
	 * @param OutRequestContext The Request Context -- used to query information about the request or to cancel it while it's in flight.	  
	 */
	UFUNCTION(BlueprintCallable, BlueprintInternalUseOnly, Category="Beam|Backend|Payments", meta=(AutoCreateRefTerm="OnSuccess,OnError,OnComplete", BeamFlowFunction))
	void PostSteamPurchaseCompleteWithRetry(const FBeamRetryConfig& RetryConfig, UPostSteamPurchaseCompleteRequest* Request, const FOnPostSteamPurchaseCompleteSuccess& OnSuccess, const FOnPostSteamPurchaseCompleteError& OnError, const FOnPostSteamPurchaseCompleteComplete& OnComplete, FBeamRequestContext& OutRequestContext);
		
	/**
	 * @brief Makes a request to the Post /basic/payments/facebook/purchase/track endpoint of the Payments Service.
	 *	 
	 * @param RetryConfig The retry config for this specific request. 
	 * @param Request The Request UObject. All (de)serialized data the request data creates is tied to the lifecycle of this object.
	 * @param OnSuccess What to do if the requests receives a successful response.
	 * @param OnError What to do if the request receives an error response.
	 * @param OnComplete What to after either OnSuccess or OnError have finished executing.
	 * @param OutRequestContext The Request Context -- used to query information about the request or to cancel it while it's in flight.	  
	 */
	UFUNCTION(BlueprintCallable, BlueprintInternalUseOnly, Category="Beam|Backend|Payments", meta=(AutoCreateRefTerm="OnSuccess,OnError,OnComplete", BeamFlowFunction))
	void PostFacebookPurchaseTrackWithRetry(const FBeamRetryConfig& RetryConfig, UPostFacebookPurchaseTrackRequest* Request, const FOnPostFacebookPurchaseTrackSuccess& OnSuccess, const FOnPostFacebookPurchaseTrackError& OnError, const FOnPostFacebookPurchaseTrackComplete& OnComplete, FBeamRequestContext& OutRequestContext);
		
	/**
	 * @brief Makes a request to the Post /basic/payments/test/purchase/verify endpoint of the Payments Service.
	 *	 
	 * @param RetryConfig The retry config for this specific request. 
	 * @param Request The Request UObject. All (de)serialized data the request data creates is tied to the lifecycle of this object.
	 * @param OnSuccess What to do if the requests receives a successful response.
	 * @param OnError What to do if the request receives an error response.
	 * @param OnComplete What to after either OnSuccess or OnError have finished executing.
	 * @param OutRequestContext The Request Context -- used to query information about the request or to cancel it while it's in flight.	  
	 */
	UFUNCTION(BlueprintCallable, BlueprintInternalUseOnly, Category="Beam|Backend|Payments", meta=(AutoCreateRefTerm="OnSuccess,OnError,OnComplete", BeamFlowFunction))
	void PostTestPurchaseVerifyWithRetry(const FBeamRetryConfig& RetryConfig, UPostTestPurchaseVerifyRequest* Request, const FOnPostTestPurchaseVerifySuccess& OnSuccess, const FOnPostTestPurchaseVerifyError& OnError, const FOnPostTestPurchaseVerifyComplete& OnComplete, FBeamRequestContext& OutRequestContext);
		
	/**
	 * @brief Makes a request to the Post /basic/payments/googleplay/purchase/track endpoint of the Payments Service.
	 *	 
	 * @param RetryConfig The retry config for this specific request. 
	 * @param Request The Request UObject. All (de)serialized data the request data creates is tied to the lifecycle of this object.
	 * @param OnSuccess What to do if the requests receives a successful response.
	 * @param OnError What to do if the request receives an error response.
	 * @param OnComplete What to after either OnSuccess or OnError have finished executing.
	 * @param OutRequestContext The Request Context -- used to query information about the request or to cancel it while it's in flight.	  
	 */
	UFUNCTION(BlueprintCallable, BlueprintInternalUseOnly, Category="Beam|Backend|Payments", meta=(AutoCreateRefTerm="OnSuccess,OnError,OnComplete", BeamFlowFunction))
	void PostGoogleplayPurchaseTrackWithRetry(const FBeamRetryConfig& RetryConfig, UPostGoogleplayPurchaseTrackRequest* Request, const FOnPostGoogleplayPurchaseTrackSuccess& OnSuccess, const FOnPostGoogleplayPurchaseTrackError& OnError, const FOnPostGoogleplayPurchaseTrackComplete& OnComplete, FBeamRequestContext& OutRequestContext);
		
	/**
	 * @brief Makes a request to the Get /basic/payments/steam/prices endpoint of the Payments Service.
	 *	 
	 * @param RetryConfig The retry config for this specific request. 
	 * @param Request The Request UObject. All (de)serialized data the request data creates is tied to the lifecycle of this object.
	 * @param OnSuccess What to do if the requests receives a successful response.
	 * @param OnError What to do if the request receives an error response.
	 * @param OnComplete What to after either OnSuccess or OnError have finished executing.
	 * @param OutRequestContext The Request Context -- used to query information about the request or to cancel it while it's in flight.	  
	 */
	UFUNCTION(BlueprintCallable, BlueprintInternalUseOnly, Category="Beam|Backend|Payments", meta=(AutoCreateRefTerm="OnSuccess,OnError,OnComplete", BeamFlowFunction))
	void GetSteamPricesWithRetry(const FBeamRetryConfig& RetryConfig, UGetSteamPricesRequest* Request, const FOnGetSteamPricesSuccess& OnSuccess, const FOnGetSteamPricesError& OnError, const FOnGetSteamPricesComplete& OnComplete, FBeamRequestContext& OutRequestContext);
		
	/**
	 * @brief Makes a request to the Post /basic/payments/windows/purchase/verify endpoint of the Payments Service.
	 *	 
	 * @param RetryConfig The retry config for this specific request. 
	 * @param Request The Request UObject. All (de)serialized data the request data creates is tied to the lifecycle of this object.
	 * @param OnSuccess What to do if the requests receives a successful response.
	 * @param OnError What to do if the request receives an error response.
	 * @param OnComplete What to after either OnSuccess or OnError have finished executing.
	 * @param OutRequestContext The Request Context -- used to query information about the request or to cancel it while it's in flight.	  
	 */
	UFUNCTION(BlueprintCallable, BlueprintInternalUseOnly, Category="Beam|Backend|Payments", meta=(AutoCreateRefTerm="OnSuccess,OnError,OnComplete", BeamFlowFunction))
	void PostWindowsPurchaseVerifyWithRetry(const FBeamRetryConfig& RetryConfig, UPostWindowsPurchaseVerifyRequest* Request, const FOnPostWindowsPurchaseVerifySuccess& OnSuccess, const FOnPostWindowsPurchaseVerifyError& OnError, const FOnPostWindowsPurchaseVerifyComplete& OnComplete, FBeamRequestContext& OutRequestContext);
		
	/**
	 * @brief Makes a request to the Post /basic/payments/itunes/purchase/verify endpoint of the Payments Service.
	 *	 
	 * @param RetryConfig The retry config for this specific request. 
	 * @param Request The Request UObject. All (de)serialized data the request data creates is tied to the lifecycle of this object.
	 * @param OnSuccess What to do if the requests receives a successful response.
	 * @param OnError What to do if the request receives an error response.
	 * @param OnComplete What to after either OnSuccess or OnError have finished executing.
	 * @param OutRequestContext The Request Context -- used to query information about the request or to cancel it while it's in flight.	  
	 */
	UFUNCTION(BlueprintCallable, BlueprintInternalUseOnly, Category="Beam|Backend|Payments", meta=(AutoCreateRefTerm="OnSuccess,OnError,OnComplete", BeamFlowFunction))
	void PostItunesPurchaseVerifyWithRetry(const FBeamRetryConfig& RetryConfig, UPostItunesPurchaseVerifyRequest* Request, const FOnPostItunesPurchaseVerifySuccess& OnSuccess, const FOnPostItunesPurchaseVerifyError& OnError, const FOnPostItunesPurchaseVerifyComplete& OnComplete, FBeamRequestContext& OutRequestContext);
		
	/**
	 * @brief Makes a request to the Post /basic/payments/itunes/purchase/complete endpoint of the Payments Service.
	 *	 
	 * @param RetryConfig The retry config for this specific request. 
	 * @param Request The Request UObject. All (de)serialized data the request data creates is tied to the lifecycle of this object.
	 * @param OnSuccess What to do if the requests receives a successful response.
	 * @param OnError What to do if the request receives an error response.
	 * @param OnComplete What to after either OnSuccess or OnError have finished executing.
	 * @param OutRequestContext The Request Context -- used to query information about the request or to cancel it while it's in flight.	  
	 */
	UFUNCTION(BlueprintCallable, BlueprintInternalUseOnly, Category="Beam|Backend|Payments", meta=(AutoCreateRefTerm="OnSuccess,OnError,OnComplete", BeamFlowFunction))
	void PostItunesPurchaseCompleteWithRetry(const FBeamRetryConfig& RetryConfig, UPostItunesPurchaseCompleteRequest* Request, const FOnPostItunesPurchaseCompleteSuccess& OnSuccess, const FOnPostItunesPurchaseCompleteError& OnError, const FOnPostItunesPurchaseCompleteComplete& OnComplete, FBeamRequestContext& OutRequestContext);
		
	/**
	 * @brief Makes a request to the Post /basic/payments/facebook/purchase/verify endpoint of the Payments Service.
	 *	 
	 * @param RetryConfig The retry config for this specific request. 
	 * @param Request The Request UObject. All (de)serialized data the request data creates is tied to the lifecycle of this object.
	 * @param OnSuccess What to do if the requests receives a successful response.
	 * @param OnError What to do if the request receives an error response.
	 * @param OnComplete What to after either OnSuccess or OnError have finished executing.
	 * @param OutRequestContext The Request Context -- used to query information about the request or to cancel it while it's in flight.	  
	 */
	UFUNCTION(BlueprintCallable, BlueprintInternalUseOnly, Category="Beam|Backend|Payments", meta=(AutoCreateRefTerm="OnSuccess,OnError,OnComplete", BeamFlowFunction))
	void PostFacebookPurchaseVerifyWithRetry(const FBeamRetryConfig& RetryConfig, UPostFacebookPurchaseVerifyRequest* Request, const FOnPostFacebookPurchaseVerifySuccess& OnSuccess, const FOnPostFacebookPurchaseVerifyError& OnError, const FOnPostFacebookPurchaseVerifyComplete& OnComplete, FBeamRequestContext& OutRequestContext);
		
	/**
	 * @brief Makes a request to the Post /basic/payments/steam/purchase/track endpoint of the Payments Service.
	 *	 
	 * @param RetryConfig The retry config for this specific request. 
	 * @param Request The Request UObject. All (de)serialized data the request data creates is tied to the lifecycle of this object.
	 * @param OnSuccess What to do if the requests receives a successful response.
	 * @param OnError What to do if the request receives an error response.
	 * @param OnComplete What to after either OnSuccess or OnError have finished executing.
	 * @param OutRequestContext The Request Context -- used to query information about the request or to cancel it while it's in flight.	  
	 */
	UFUNCTION(BlueprintCallable, BlueprintInternalUseOnly, Category="Beam|Backend|Payments", meta=(AutoCreateRefTerm="OnSuccess,OnError,OnComplete", BeamFlowFunction))
	void PostSteamPurchaseTrackWithRetry(const FBeamRetryConfig& RetryConfig, UPostSteamPurchaseTrackRequest* Request, const FOnPostSteamPurchaseTrackSuccess& OnSuccess, const FOnPostSteamPurchaseTrackError& OnError, const FOnPostSteamPurchaseTrackComplete& OnComplete, FBeamRequestContext& OutRequestContext);
		
	/**
	 * @brief Makes a request to the Post /basic/payments/coupon/purchase/verify endpoint of the Payments Service.
	 *	 
	 * @param RetryConfig The retry config for this specific request. 
	 * @param Request The Request UObject. All (de)serialized data the request data creates is tied to the lifecycle of this object.
	 * @param OnSuccess What to do if the requests receives a successful response.
	 * @param OnError What to do if the request receives an error response.
	 * @param OnComplete What to after either OnSuccess or OnError have finished executing.
	 * @param OutRequestContext The Request Context -- used to query information about the request or to cancel it while it's in flight.	  
	 */
	UFUNCTION(BlueprintCallable, BlueprintInternalUseOnly, Category="Beam|Backend|Payments", meta=(AutoCreateRefTerm="OnSuccess,OnError,OnComplete", BeamFlowFunction))
	void PostCouponPurchaseVerifyWithRetry(const FBeamRetryConfig& RetryConfig, UPostCouponPurchaseVerifyRequest* Request, const FOnPostCouponPurchaseVerifySuccess& OnSuccess, const FOnPostCouponPurchaseVerifyError& OnError, const FOnPostCouponPurchaseVerifyComplete& OnComplete, FBeamRequestContext& OutRequestContext);
		
	/**
	 * @brief Makes a request to the Get /basic/payments/windows/product endpoint of the Payments Service.
	 *	 
	 * @param RetryConfig The retry config for this specific request. 
	 * @param Request The Request UObject. All (de)serialized data the request data creates is tied to the lifecycle of this object.
	 * @param OnSuccess What to do if the requests receives a successful response.
	 * @param OnError What to do if the request receives an error response.
	 * @param OnComplete What to after either OnSuccess or OnError have finished executing.
	 * @param OutRequestContext The Request Context -- used to query information about the request or to cancel it while it's in flight.	  
	 */
	UFUNCTION(BlueprintCallable, BlueprintInternalUseOnly, Category="Beam|Backend|Payments", meta=(AutoCreateRefTerm="OnSuccess,OnError,OnComplete", BeamFlowFunction))
	void GetWindowsProductWithRetry(const FBeamRetryConfig& RetryConfig, UGetWindowsProductRequest* Request, const FOnGetWindowsProductSuccess& OnSuccess, const FOnGetWindowsProductError& OnError, const FOnGetWindowsProductComplete& OnComplete, FBeamRequestContext& OutRequestContext);
		
	/**
	 * @brief Makes a request to the Get /basic/payments/facebook/product endpoint of the Payments Service.
	 *	 
	 * @param RetryConfig The retry config for this specific request. 
	 * @param Request The Request UObject. All (de)serialized data the request data creates is tied to the lifecycle of this object.
	 * @param OnSuccess What to do if the requests receives a successful response.
	 * @param OnError What to do if the request receives an error response.
	 * @param OnComplete What to after either OnSuccess or OnError have finished executing.
	 * @param OutRequestContext The Request Context -- used to query information about the request or to cancel it while it's in flight.	  
	 */
	UFUNCTION(BlueprintCallable, BlueprintInternalUseOnly, Category="Beam|Backend|Payments", meta=(AutoCreateRefTerm="OnSuccess,OnError,OnComplete", BeamFlowFunction))
	void GetFacebookProductWithRetry(const FBeamRetryConfig& RetryConfig, UGetFacebookProductRequest* Request, const FOnGetFacebookProductSuccess& OnSuccess, const FOnGetFacebookProductError& OnError, const FOnGetFacebookProductComplete& OnComplete, FBeamRequestContext& OutRequestContext);
		
	/**
	 * @brief Makes a request to the Get /basic/payments/coupon/product endpoint of the Payments Service.
	 *	 
	 * @param RetryConfig The retry config for this specific request. 
	 * @param Request The Request UObject. All (de)serialized data the request data creates is tied to the lifecycle of this object.
	 * @param OnSuccess What to do if the requests receives a successful response.
	 * @param OnError What to do if the request receives an error response.
	 * @param OnComplete What to after either OnSuccess or OnError have finished executing.
	 * @param OutRequestContext The Request Context -- used to query information about the request or to cancel it while it's in flight.	  
	 */
	UFUNCTION(BlueprintCallable, BlueprintInternalUseOnly, Category="Beam|Backend|Payments", meta=(AutoCreateRefTerm="OnSuccess,OnError,OnComplete", BeamFlowFunction))
	void GetCouponProductWithRetry(const FBeamRetryConfig& RetryConfig, UGetCouponProductRequest* Request, const FOnGetCouponProductSuccess& OnSuccess, const FOnGetCouponProductError& OnError, const FOnGetCouponProductComplete& OnComplete, FBeamRequestContext& OutRequestContext);
		
	/**
	 * @brief Makes a request to the Get /basic/payments/steam/products endpoint of the Payments Service.
	 *	 
	 * @param RetryConfig The retry config for this specific request. 
	 * @param Request The Request UObject. All (de)serialized data the request data creates is tied to the lifecycle of this object.
	 * @param OnSuccess What to do if the requests receives a successful response.
	 * @param OnError What to do if the request receives an error response.
	 * @param OnComplete What to after either OnSuccess or OnError have finished executing.
	 * @param OutRequestContext The Request Context -- used to query information about the request or to cancel it while it's in flight.	  
	 */
	UFUNCTION(BlueprintCallable, BlueprintInternalUseOnly, Category="Beam|Backend|Payments", meta=(AutoCreateRefTerm="OnSuccess,OnError,OnComplete", BeamFlowFunction))
	void GetSteamProductsWithRetry(const FBeamRetryConfig& RetryConfig, UGetSteamProductsRequest* Request, const FOnGetSteamProductsSuccess& OnSuccess, const FOnGetSteamProductsError& OnError, const FOnGetSteamProductsComplete& OnComplete, FBeamRequestContext& OutRequestContext);
		
	/**
	 * @brief Makes a request to the Post /basic/payments/steam/auth endpoint of the Payments Service.
	 *	 
	 * @param RetryConfig The retry config for this specific request. 
	 * @param Request The Request UObject. All (de)serialized data the request data creates is tied to the lifecycle of this object.
	 * @param OnSuccess What to do if the requests receives a successful response.
	 * @param OnError What to do if the request receives an error response.
	 * @param OnComplete What to after either OnSuccess or OnError have finished executing.
	 * @param OutRequestContext The Request Context -- used to query information about the request or to cancel it while it's in flight.	  
	 */
	UFUNCTION(BlueprintCallable, BlueprintInternalUseOnly, Category="Beam|Backend|Payments", meta=(AutoCreateRefTerm="OnSuccess,OnError,OnComplete", BeamFlowFunction))
	void PostSteamAuthWithRetry(const FBeamRetryConfig& RetryConfig, UPostSteamAuthRequest* Request, const FOnPostSteamAuthSuccess& OnSuccess, const FOnPostSteamAuthError& OnError, const FOnPostSteamAuthComplete& OnComplete, FBeamRequestContext& OutRequestContext);
		
	/**
	 * @brief Makes a request to the Get /basic/payments/steam/product endpoint of the Payments Service.
	 *	 
	 * @param RetryConfig The retry config for this specific request. 
	 * @param Request The Request UObject. All (de)serialized data the request data creates is tied to the lifecycle of this object.
	 * @param OnSuccess What to do if the requests receives a successful response.
	 * @param OnError What to do if the request receives an error response.
	 * @param OnComplete What to after either OnSuccess or OnError have finished executing.
	 * @param OutRequestContext The Request Context -- used to query information about the request or to cancel it while it's in flight.	  
	 */
	UFUNCTION(BlueprintCallable, BlueprintInternalUseOnly, Category="Beam|Backend|Payments", meta=(AutoCreateRefTerm="OnSuccess,OnError,OnComplete", BeamFlowFunction))
	void GetSteamProductWithRetry(const FBeamRetryConfig& RetryConfig, UGetSteamProductRequest* Request, const FOnGetSteamProductSuccess& OnSuccess, const FOnGetSteamProductError& OnError, const FOnGetSteamProductComplete& OnComplete, FBeamRequestContext& OutRequestContext);
		
	/**
	 * @brief Makes a request to the Post /basic/payments/coupon/purchase/complete endpoint of the Payments Service.
	 *	 
	 * @param RetryConfig The retry config for this specific request. 
	 * @param Request The Request UObject. All (de)serialized data the request data creates is tied to the lifecycle of this object.
	 * @param OnSuccess What to do if the requests receives a successful response.
	 * @param OnError What to do if the request receives an error response.
	 * @param OnComplete What to after either OnSuccess or OnError have finished executing.
	 * @param OutRequestContext The Request Context -- used to query information about the request or to cancel it while it's in flight.	  
	 */
	UFUNCTION(BlueprintCallable, BlueprintInternalUseOnly, Category="Beam|Backend|Payments", meta=(AutoCreateRefTerm="OnSuccess,OnError,OnComplete", BeamFlowFunction))
	void PostCouponPurchaseCompleteWithRetry(const FBeamRetryConfig& RetryConfig, UPostCouponPurchaseCompleteRequest* Request, const FOnPostCouponPurchaseCompleteSuccess& OnSuccess, const FOnPostCouponPurchaseCompleteError& OnError, const FOnPostCouponPurchaseCompleteComplete& OnComplete, FBeamRequestContext& OutRequestContext);
		
	/**
	 * @brief Makes a request to the Get /basic/payments/googleplay/product endpoint of the Payments Service.
	 *	 
	 * @param RetryConfig The retry config for this specific request. 
	 * @param Request The Request UObject. All (de)serialized data the request data creates is tied to the lifecycle of this object.
	 * @param OnSuccess What to do if the requests receives a successful response.
	 * @param OnError What to do if the request receives an error response.
	 * @param OnComplete What to after either OnSuccess or OnError have finished executing.
	 * @param OutRequestContext The Request Context -- used to query information about the request or to cancel it while it's in flight.	  
	 */
	UFUNCTION(BlueprintCallable, BlueprintInternalUseOnly, Category="Beam|Backend|Payments", meta=(AutoCreateRefTerm="OnSuccess,OnError,OnComplete", BeamFlowFunction))
	void GetGoogleplayProductWithRetry(const FBeamRetryConfig& RetryConfig, UGetGoogleplayProductRequest* Request, const FOnGetGoogleplayProductSuccess& OnSuccess, const FOnGetGoogleplayProductError& OnError, const FOnGetGoogleplayProductComplete& OnComplete, FBeamRequestContext& OutRequestContext);
		
	/**
	 * @brief Makes a request to the Get /basic/payments/test/product endpoint of the Payments Service.
	 *	 
	 * @param RetryConfig The retry config for this specific request. 
	 * @param Request The Request UObject. All (de)serialized data the request data creates is tied to the lifecycle of this object.
	 * @param OnSuccess What to do if the requests receives a successful response.
	 * @param OnError What to do if the request receives an error response.
	 * @param OnComplete What to after either OnSuccess or OnError have finished executing.
	 * @param OutRequestContext The Request Context -- used to query information about the request or to cancel it while it's in flight.	  
	 */
	UFUNCTION(BlueprintCallable, BlueprintInternalUseOnly, Category="Beam|Backend|Payments", meta=(AutoCreateRefTerm="OnSuccess,OnError,OnComplete", BeamFlowFunction))
	void GetTestProductWithRetry(const FBeamRetryConfig& RetryConfig, UGetTestProductRequest* Request, const FOnGetTestProductSuccess& OnSuccess, const FOnGetTestProductError& OnError, const FOnGetTestProductComplete& OnComplete, FBeamRequestContext& OutRequestContext);
		
	/**
	 * @brief Makes a request to the Post /basic/payments/steam/purchase/verify endpoint of the Payments Service.
	 *	 
	 * @param RetryConfig The retry config for this specific request. 
	 * @param Request The Request UObject. All (de)serialized data the request data creates is tied to the lifecycle of this object.
	 * @param OnSuccess What to do if the requests receives a successful response.
	 * @param OnError What to do if the request receives an error response.
	 * @param OnComplete What to after either OnSuccess or OnError have finished executing.
	 * @param OutRequestContext The Request Context -- used to query information about the request or to cancel it while it's in flight.	  
	 */
	UFUNCTION(BlueprintCallable, BlueprintInternalUseOnly, Category="Beam|Backend|Payments", meta=(AutoCreateRefTerm="OnSuccess,OnError,OnComplete", BeamFlowFunction))
	void PostSteamPurchaseVerifyWithRetry(const FBeamRetryConfig& RetryConfig, UPostSteamPurchaseVerifyRequest* Request, const FOnPostSteamPurchaseVerifySuccess& OnSuccess, const FOnPostSteamPurchaseVerifyError& OnError, const FOnPostSteamPurchaseVerifyComplete& OnComplete, FBeamRequestContext& OutRequestContext);
		
	/**
	 * @brief Makes a request to the Post /basic/payments/itunes/purchase/track endpoint of the Payments Service.
	 *	 
	 * @param RetryConfig The retry config for this specific request. 
	 * @param Request The Request UObject. All (de)serialized data the request data creates is tied to the lifecycle of this object.
	 * @param OnSuccess What to do if the requests receives a successful response.
	 * @param OnError What to do if the request receives an error response.
	 * @param OnComplete What to after either OnSuccess or OnError have finished executing.
	 * @param OutRequestContext The Request Context -- used to query information about the request or to cancel it while it's in flight.	  
	 */
	UFUNCTION(BlueprintCallable, BlueprintInternalUseOnly, Category="Beam|Backend|Payments", meta=(AutoCreateRefTerm="OnSuccess,OnError,OnComplete", BeamFlowFunction))
	void PostItunesPurchaseTrackWithRetry(const FBeamRetryConfig& RetryConfig, UPostItunesPurchaseTrackRequest* Request, const FOnPostItunesPurchaseTrackSuccess& OnSuccess, const FOnPostItunesPurchaseTrackError& OnError, const FOnPostItunesPurchaseTrackComplete& OnComplete, FBeamRequestContext& OutRequestContext);
		
	/**
	 * @brief Makes a request to the Get /object/payments/{objectId}/ endpoint of the Payments Service.
	 *	 
	 * @param RetryConfig The retry config for this specific request. 
	 * @param Request The Request UObject. All (de)serialized data the request data creates is tied to the lifecycle of this object.
	 * @param OnSuccess What to do if the requests receives a successful response.
	 * @param OnError What to do if the request receives an error response.
	 * @param OnComplete What to after either OnSuccess or OnError have finished executing.
	 * @param OutRequestContext The Request Context -- used to query information about the request or to cancel it while it's in flight.	  
	 */
	UFUNCTION(BlueprintCallable, BlueprintInternalUseOnly, Category="Beam|Backend|Payments", meta=(AutoCreateRefTerm="OnSuccess,OnError,OnComplete", BeamFlowFunction))
	void GetPaymentsWithRetry(const FBeamRetryConfig& RetryConfig, UGetPaymentsRequest* Request, const FOnGetPaymentsSuccess& OnSuccess, const FOnGetPaymentsError& OnError, const FOnGetPaymentsComplete& OnComplete, FBeamRequestContext& OutRequestContext);

	
	/**
	 * @brief Makes an authenticated request to the Post /basic/payments/test/purchase/begin endpoint of the Payments Service.
	 *
	 * @param UserSlot The authenticated UserSlot with the user making the request.
	 * @param RetryConfig The retry config for this specific request. 
	 * @param Request The Request UObject. All (de)serialized data the request data creates is tied to the lifecycle of this object.
	 * @param OnSuccess What to do if the requests receives a successful response.
	 * @param OnError What to do if the request receives an error response.
	 * @param OnComplete What to after either OnSuccess or OnError have finished executing.
	 * @param OutRequestContext The Request Context -- used to query information about the request or to cancel it while it's in flight.
	 * @param CallingContext A UObject managed by the UWorld that's making the request. Used to support multiple PIEs (see UBeamUserSlot::GetNamespacedSlotId). 
	 */
	UFUNCTION(BlueprintCallable, BlueprintInternalUseOnly, Category="Beam|Backend|Payments", meta=(DefaultToSelf="CallingContext", AdvancedDisplay="CallingContext", AutoCreateRefTerm="UserSlot,OnSuccess,OnError,OnComplete", BeamFlowFunction))
	void PostTestPurchaseBeginWithRetry(FUserSlot UserSlot, const FBeamRetryConfig& RetryConfig, UPostTestPurchaseBeginRequest* Request, const FOnPostTestPurchaseBeginSuccess& OnSuccess, const FOnPostTestPurchaseBeginError& OnError, const FOnPostTestPurchaseBeginComplete& OnComplete, FBeamRequestContext& OutRequestContext, const UObject* CallingContext = nullptr);
		
	/**
	 * @brief Makes an authenticated request to the Post /basic/payments/steam/purchase/fail endpoint of the Payments Service.
	 *
	 * @param UserSlot The authenticated UserSlot with the user making the request.
	 * @param RetryConfig The retry config for this specific request. 
	 * @param Request The Request UObject. All (de)serialized data the request data creates is tied to the lifecycle of this object.
	 * @param OnSuccess What to do if the requests receives a successful response.
	 * @param OnError What to do if the request receives an error response.
	 * @param OnComplete What to after either OnSuccess or OnError have finished executing.
	 * @param OutRequestContext The Request Context -- used to query information about the request or to cancel it while it's in flight.
	 * @param CallingContext A UObject managed by the UWorld that's making the request. Used to support multiple PIEs (see UBeamUserSlot::GetNamespacedSlotId). 
	 */
	UFUNCTION(BlueprintCallable, BlueprintInternalUseOnly, Category="Beam|Backend|Payments", meta=(DefaultToSelf="CallingContext", AdvancedDisplay="CallingContext", AutoCreateRefTerm="UserSlot,OnSuccess,OnError,OnComplete", BeamFlowFunction))
	void PostSteamPurchaseFailWithRetry(FUserSlot UserSlot, const FBeamRetryConfig& RetryConfig, UPostSteamPurchaseFailRequest* Request, const FOnPostSteamPurchaseFailSuccess& OnSuccess, const FOnPostSteamPurchaseFailError& OnError, const FOnPostSteamPurchaseFailComplete& OnComplete, FBeamRequestContext& OutRequestContext, const UObject* CallingContext = nullptr);
		
	/**
	 * @brief Makes an authenticated request to the Post /basic/payments/facebook/purchase/fail endpoint of the Payments Service.
	 *
	 * @param UserSlot The authenticated UserSlot with the user making the request.
	 * @param RetryConfig The retry config for this specific request. 
	 * @param Request The Request UObject. All (de)serialized data the request data creates is tied to the lifecycle of this object.
	 * @param OnSuccess What to do if the requests receives a successful response.
	 * @param OnError What to do if the request receives an error response.
	 * @param OnComplete What to after either OnSuccess or OnError have finished executing.
	 * @param OutRequestContext The Request Context -- used to query information about the request or to cancel it while it's in flight.
	 * @param CallingContext A UObject managed by the UWorld that's making the request. Used to support multiple PIEs (see UBeamUserSlot::GetNamespacedSlotId). 
	 */
	UFUNCTION(BlueprintCallable, BlueprintInternalUseOnly, Category="Beam|Backend|Payments", meta=(DefaultToSelf="CallingContext", AdvancedDisplay="CallingContext", AutoCreateRefTerm="UserSlot,OnSuccess,OnError,OnComplete", BeamFlowFunction))
	void PostFacebookPurchaseFailWithRetry(FUserSlot UserSlot, const FBeamRetryConfig& RetryConfig, UPostFacebookPurchaseFailRequest* Request, const FOnPostFacebookPurchaseFailSuccess& OnSuccess, const FOnPostFacebookPurchaseFailError& OnError, const FOnPostFacebookPurchaseFailComplete& OnComplete, FBeamRequestContext& OutRequestContext, const UObject* CallingContext = nullptr);
		
	/**
	 * @brief Makes an authenticated request to the Post /basic/payments/googleplay/purchase/begin endpoint of the Payments Service.
	 *
	 * @param UserSlot The authenticated UserSlot with the user making the request.
	 * @param RetryConfig The retry config for this specific request. 
	 * @param Request The Request UObject. All (de)serialized data the request data creates is tied to the lifecycle of this object.
	 * @param OnSuccess What to do if the requests receives a successful response.
	 * @param OnError What to do if the request receives an error response.
	 * @param OnComplete What to after either OnSuccess or OnError have finished executing.
	 * @param OutRequestContext The Request Context -- used to query information about the request or to cancel it while it's in flight.
	 * @param CallingContext A UObject managed by the UWorld that's making the request. Used to support multiple PIEs (see UBeamUserSlot::GetNamespacedSlotId). 
	 */
	UFUNCTION(BlueprintCallable, BlueprintInternalUseOnly, Category="Beam|Backend|Payments", meta=(DefaultToSelf="CallingContext", AdvancedDisplay="CallingContext", AutoCreateRefTerm="UserSlot,OnSuccess,OnError,OnComplete", BeamFlowFunction))
	void PostGoogleplayPurchaseBeginWithRetry(FUserSlot UserSlot, const FBeamRetryConfig& RetryConfig, UPostGoogleplayPurchaseBeginRequest* Request, const FOnPostGoogleplayPurchaseBeginSuccess& OnSuccess, const FOnPostGoogleplayPurchaseBeginError& OnError, const FOnPostGoogleplayPurchaseBeginComplete& OnComplete, FBeamRequestContext& OutRequestContext, const UObject* CallingContext = nullptr);
		
	/**
	 * @brief Makes an authenticated request to the Post /basic/payments/itunes/purchase/begin endpoint of the Payments Service.
	 *
	 * @param UserSlot The authenticated UserSlot with the user making the request.
	 * @param RetryConfig The retry config for this specific request. 
	 * @param Request The Request UObject. All (de)serialized data the request data creates is tied to the lifecycle of this object.
	 * @param OnSuccess What to do if the requests receives a successful response.
	 * @param OnError What to do if the request receives an error response.
	 * @param OnComplete What to after either OnSuccess or OnError have finished executing.
	 * @param OutRequestContext The Request Context -- used to query information about the request or to cancel it while it's in flight.
	 * @param CallingContext A UObject managed by the UWorld that's making the request. Used to support multiple PIEs (see UBeamUserSlot::GetNamespacedSlotId). 
	 */
	UFUNCTION(BlueprintCallable, BlueprintInternalUseOnly, Category="Beam|Backend|Payments", meta=(DefaultToSelf="CallingContext", AdvancedDisplay="CallingContext", AutoCreateRefTerm="UserSlot,OnSuccess,OnError,OnComplete", BeamFlowFunction))
	void PostItunesPurchaseBeginWithRetry(FUserSlot UserSlot, const FBeamRetryConfig& RetryConfig, UPostItunesPurchaseBeginRequest* Request, const FOnPostItunesPurchaseBeginSuccess& OnSuccess, const FOnPostItunesPurchaseBeginError& OnError, const FOnPostItunesPurchaseBeginComplete& OnComplete, FBeamRequestContext& OutRequestContext, const UObject* CallingContext = nullptr);
		
	/**
	 * @brief Makes an authenticated request to the Post /basic/payments/facebook/purchase/cancel endpoint of the Payments Service.
	 *
	 * @param UserSlot The authenticated UserSlot with the user making the request.
	 * @param RetryConfig The retry config for this specific request. 
	 * @param Request The Request UObject. All (de)serialized data the request data creates is tied to the lifecycle of this object.
	 * @param OnSuccess What to do if the requests receives a successful response.
	 * @param OnError What to do if the request receives an error response.
	 * @param OnComplete What to after either OnSuccess or OnError have finished executing.
	 * @param OutRequestContext The Request Context -- used to query information about the request or to cancel it while it's in flight.
	 * @param CallingContext A UObject managed by the UWorld that's making the request. Used to support multiple PIEs (see UBeamUserSlot::GetNamespacedSlotId). 
	 */
	UFUNCTION(BlueprintCallable, BlueprintInternalUseOnly, Category="Beam|Backend|Payments", meta=(DefaultToSelf="CallingContext", AdvancedDisplay="CallingContext", AutoCreateRefTerm="UserSlot,OnSuccess,OnError,OnComplete", BeamFlowFunction))
	void PostFacebookPurchaseCancelWithRetry(FUserSlot UserSlot, const FBeamRetryConfig& RetryConfig, UPostFacebookPurchaseCancelRequest* Request, const FOnPostFacebookPurchaseCancelSuccess& OnSuccess, const FOnPostFacebookPurchaseCancelError& OnError, const FOnPostFacebookPurchaseCancelComplete& OnComplete, FBeamRequestContext& OutRequestContext, const UObject* CallingContext = nullptr);
		
	/**
	 * @brief Makes an authenticated request to the Post /basic/payments/itunes/purchase/fail endpoint of the Payments Service.
	 *
	 * @param UserSlot The authenticated UserSlot with the user making the request.
	 * @param RetryConfig The retry config for this specific request. 
	 * @param Request The Request UObject. All (de)serialized data the request data creates is tied to the lifecycle of this object.
	 * @param OnSuccess What to do if the requests receives a successful response.
	 * @param OnError What to do if the request receives an error response.
	 * @param OnComplete What to after either OnSuccess or OnError have finished executing.
	 * @param OutRequestContext The Request Context -- used to query information about the request or to cancel it while it's in flight.
	 * @param CallingContext A UObject managed by the UWorld that's making the request. Used to support multiple PIEs (see UBeamUserSlot::GetNamespacedSlotId). 
	 */
	UFUNCTION(BlueprintCallable, BlueprintInternalUseOnly, Category="Beam|Backend|Payments", meta=(DefaultToSelf="CallingContext", AdvancedDisplay="CallingContext", AutoCreateRefTerm="UserSlot,OnSuccess,OnError,OnComplete", BeamFlowFunction))
	void PostItunesPurchaseFailWithRetry(FUserSlot UserSlot, const FBeamRetryConfig& RetryConfig, UPostItunesPurchaseFailRequest* Request, const FOnPostItunesPurchaseFailSuccess& OnSuccess, const FOnPostItunesPurchaseFailError& OnError, const FOnPostItunesPurchaseFailComplete& OnComplete, FBeamRequestContext& OutRequestContext, const UObject* CallingContext = nullptr);
		
	/**
	 * @brief Makes an authenticated request to the Post /basic/payments/test/purchase/cancel endpoint of the Payments Service.
	 *
	 * @param UserSlot The authenticated UserSlot with the user making the request.
	 * @param RetryConfig The retry config for this specific request. 
	 * @param Request The Request UObject. All (de)serialized data the request data creates is tied to the lifecycle of this object.
	 * @param OnSuccess What to do if the requests receives a successful response.
	 * @param OnError What to do if the request receives an error response.
	 * @param OnComplete What to after either OnSuccess or OnError have finished executing.
	 * @param OutRequestContext The Request Context -- used to query information about the request or to cancel it while it's in flight.
	 * @param CallingContext A UObject managed by the UWorld that's making the request. Used to support multiple PIEs (see UBeamUserSlot::GetNamespacedSlotId). 
	 */
	UFUNCTION(BlueprintCallable, BlueprintInternalUseOnly, Category="Beam|Backend|Payments", meta=(DefaultToSelf="CallingContext", AdvancedDisplay="CallingContext", AutoCreateRefTerm="UserSlot,OnSuccess,OnError,OnComplete", BeamFlowFunction))
	void PostTestPurchaseCancelWithRetry(FUserSlot UserSlot, const FBeamRetryConfig& RetryConfig, UPostTestPurchaseCancelRequest* Request, const FOnPostTestPurchaseCancelSuccess& OnSuccess, const FOnPostTestPurchaseCancelError& OnError, const FOnPostTestPurchaseCancelComplete& OnComplete, FBeamRequestContext& OutRequestContext, const UObject* CallingContext = nullptr);
		
	/**
	 * @brief Makes an authenticated request to the Post /basic/payments/test/purchase/fail endpoint of the Payments Service.
	 *
	 * @param UserSlot The authenticated UserSlot with the user making the request.
	 * @param RetryConfig The retry config for this specific request. 
	 * @param Request The Request UObject. All (de)serialized data the request data creates is tied to the lifecycle of this object.
	 * @param OnSuccess What to do if the requests receives a successful response.
	 * @param OnError What to do if the request receives an error response.
	 * @param OnComplete What to after either OnSuccess or OnError have finished executing.
	 * @param OutRequestContext The Request Context -- used to query information about the request or to cancel it while it's in flight.
	 * @param CallingContext A UObject managed by the UWorld that's making the request. Used to support multiple PIEs (see UBeamUserSlot::GetNamespacedSlotId). 
	 */
	UFUNCTION(BlueprintCallable, BlueprintInternalUseOnly, Category="Beam|Backend|Payments", meta=(DefaultToSelf="CallingContext", AdvancedDisplay="CallingContext", AutoCreateRefTerm="UserSlot,OnSuccess,OnError,OnComplete", BeamFlowFunction))
	void PostTestPurchaseFailWithRetry(FUserSlot UserSlot, const FBeamRetryConfig& RetryConfig, UPostTestPurchaseFailRequest* Request, const FOnPostTestPurchaseFailSuccess& OnSuccess, const FOnPostTestPurchaseFailError& OnError, const FOnPostTestPurchaseFailComplete& OnComplete, FBeamRequestContext& OutRequestContext, const UObject* CallingContext = nullptr);
		
	/**
	 * @brief Makes an authenticated request to the Post /basic/payments/coupon/purchase/cancel endpoint of the Payments Service.
	 *
	 * @param UserSlot The authenticated UserSlot with the user making the request.
	 * @param RetryConfig The retry config for this specific request. 
	 * @param Request The Request UObject. All (de)serialized data the request data creates is tied to the lifecycle of this object.
	 * @param OnSuccess What to do if the requests receives a successful response.
	 * @param OnError What to do if the request receives an error response.
	 * @param OnComplete What to after either OnSuccess or OnError have finished executing.
	 * @param OutRequestContext The Request Context -- used to query information about the request or to cancel it while it's in flight.
	 * @param CallingContext A UObject managed by the UWorld that's making the request. Used to support multiple PIEs (see UBeamUserSlot::GetNamespacedSlotId). 
	 */
	UFUNCTION(BlueprintCallable, BlueprintInternalUseOnly, Category="Beam|Backend|Payments", meta=(DefaultToSelf="CallingContext", AdvancedDisplay="CallingContext", AutoCreateRefTerm="UserSlot,OnSuccess,OnError,OnComplete", BeamFlowFunction))
	void PostCouponPurchaseCancelWithRetry(FUserSlot UserSlot, const FBeamRetryConfig& RetryConfig, UPostCouponPurchaseCancelRequest* Request, const FOnPostCouponPurchaseCancelSuccess& OnSuccess, const FOnPostCouponPurchaseCancelError& OnError, const FOnPostCouponPurchaseCancelComplete& OnComplete, FBeamRequestContext& OutRequestContext, const UObject* CallingContext = nullptr);
		
	/**
	 * @brief Makes an authenticated request to the Post /basic/payments/coupon/purchase/begin endpoint of the Payments Service.
	 *
	 * @param UserSlot The authenticated UserSlot with the user making the request.
	 * @param RetryConfig The retry config for this specific request. 
	 * @param Request The Request UObject. All (de)serialized data the request data creates is tied to the lifecycle of this object.
	 * @param OnSuccess What to do if the requests receives a successful response.
	 * @param OnError What to do if the request receives an error response.
	 * @param OnComplete What to after either OnSuccess or OnError have finished executing.
	 * @param OutRequestContext The Request Context -- used to query information about the request or to cancel it while it's in flight.
	 * @param CallingContext A UObject managed by the UWorld that's making the request. Used to support multiple PIEs (see UBeamUserSlot::GetNamespacedSlotId). 
	 */
	UFUNCTION(BlueprintCallable, BlueprintInternalUseOnly, Category="Beam|Backend|Payments", meta=(DefaultToSelf="CallingContext", AdvancedDisplay="CallingContext", AutoCreateRefTerm="UserSlot,OnSuccess,OnError,OnComplete", BeamFlowFunction))
	void PostCouponPurchaseBeginWithRetry(FUserSlot UserSlot, const FBeamRetryConfig& RetryConfig, UPostCouponPurchaseBeginRequest* Request, const FOnPostCouponPurchaseBeginSuccess& OnSuccess, const FOnPostCouponPurchaseBeginError& OnError, const FOnPostCouponPurchaseBeginComplete& OnComplete, FBeamRequestContext& OutRequestContext, const UObject* CallingContext = nullptr);
		
	/**
	 * @brief Makes an authenticated request to the Post /basic/payments/facebook/purchase/begin endpoint of the Payments Service.
	 *
	 * @param UserSlot The authenticated UserSlot with the user making the request.
	 * @param RetryConfig The retry config for this specific request. 
	 * @param Request The Request UObject. All (de)serialized data the request data creates is tied to the lifecycle of this object.
	 * @param OnSuccess What to do if the requests receives a successful response.
	 * @param OnError What to do if the request receives an error response.
	 * @param OnComplete What to after either OnSuccess or OnError have finished executing.
	 * @param OutRequestContext The Request Context -- used to query information about the request or to cancel it while it's in flight.
	 * @param CallingContext A UObject managed by the UWorld that's making the request. Used to support multiple PIEs (see UBeamUserSlot::GetNamespacedSlotId). 
	 */
	UFUNCTION(BlueprintCallable, BlueprintInternalUseOnly, Category="Beam|Backend|Payments", meta=(DefaultToSelf="CallingContext", AdvancedDisplay="CallingContext", AutoCreateRefTerm="UserSlot,OnSuccess,OnError,OnComplete", BeamFlowFunction))
	void PostFacebookPurchaseBeginWithRetry(FUserSlot UserSlot, const FBeamRetryConfig& RetryConfig, UPostFacebookPurchaseBeginRequest* Request, const FOnPostFacebookPurchaseBeginSuccess& OnSuccess, const FOnPostFacebookPurchaseBeginError& OnError, const FOnPostFacebookPurchaseBeginComplete& OnComplete, FBeamRequestContext& OutRequestContext, const UObject* CallingContext = nullptr);
		
	/**
	 * @brief Makes an authenticated request to the Get /basic/payments/steam/order endpoint of the Payments Service.
	 *
	 * @param UserSlot The authenticated UserSlot with the user making the request.
	 * @param RetryConfig The retry config for this specific request. 
	 * @param Request The Request UObject. All (de)serialized data the request data creates is tied to the lifecycle of this object.
	 * @param OnSuccess What to do if the requests receives a successful response.
	 * @param OnError What to do if the request receives an error response.
	 * @param OnComplete What to after either OnSuccess or OnError have finished executing.
	 * @param OutRequestContext The Request Context -- used to query information about the request or to cancel it while it's in flight.
	 * @param CallingContext A UObject managed by the UWorld that's making the request. Used to support multiple PIEs (see UBeamUserSlot::GetNamespacedSlotId). 
	 */
	UFUNCTION(BlueprintCallable, BlueprintInternalUseOnly, Category="Beam|Backend|Payments", meta=(DefaultToSelf="CallingContext", AdvancedDisplay="CallingContext", AutoCreateRefTerm="UserSlot,OnSuccess,OnError,OnComplete", BeamFlowFunction))
	void GetSteamOrderWithRetry(FUserSlot UserSlot, const FBeamRetryConfig& RetryConfig, UGetSteamOrderRequest* Request, const FOnGetSteamOrderSuccess& OnSuccess, const FOnGetSteamOrderError& OnError, const FOnGetSteamOrderComplete& OnComplete, FBeamRequestContext& OutRequestContext, const UObject* CallingContext = nullptr);
		
	/**
	 * @brief Makes an authenticated request to the Post /basic/payments/windows/purchase/begin endpoint of the Payments Service.
	 *
	 * @param UserSlot The authenticated UserSlot with the user making the request.
	 * @param RetryConfig The retry config for this specific request. 
	 * @param Request The Request UObject. All (de)serialized data the request data creates is tied to the lifecycle of this object.
	 * @param OnSuccess What to do if the requests receives a successful response.
	 * @param OnError What to do if the request receives an error response.
	 * @param OnComplete What to after either OnSuccess or OnError have finished executing.
	 * @param OutRequestContext The Request Context -- used to query information about the request or to cancel it while it's in flight.
	 * @param CallingContext A UObject managed by the UWorld that's making the request. Used to support multiple PIEs (see UBeamUserSlot::GetNamespacedSlotId). 
	 */
	UFUNCTION(BlueprintCallable, BlueprintInternalUseOnly, Category="Beam|Backend|Payments", meta=(DefaultToSelf="CallingContext", AdvancedDisplay="CallingContext", AutoCreateRefTerm="UserSlot,OnSuccess,OnError,OnComplete", BeamFlowFunction))
	void PostWindowsPurchaseBeginWithRetry(FUserSlot UserSlot, const FBeamRetryConfig& RetryConfig, UPostWindowsPurchaseBeginRequest* Request, const FOnPostWindowsPurchaseBeginSuccess& OnSuccess, const FOnPostWindowsPurchaseBeginError& OnError, const FOnPostWindowsPurchaseBeginComplete& OnComplete, FBeamRequestContext& OutRequestContext, const UObject* CallingContext = nullptr);
		
	/**
	 * @brief Makes an authenticated request to the Post /basic/payments/googleplay/purchase/fail endpoint of the Payments Service.
	 *
	 * @param UserSlot The authenticated UserSlot with the user making the request.
	 * @param RetryConfig The retry config for this specific request. 
	 * @param Request The Request UObject. All (de)serialized data the request data creates is tied to the lifecycle of this object.
	 * @param OnSuccess What to do if the requests receives a successful response.
	 * @param OnError What to do if the request receives an error response.
	 * @param OnComplete What to after either OnSuccess or OnError have finished executing.
	 * @param OutRequestContext The Request Context -- used to query information about the request or to cancel it while it's in flight.
	 * @param CallingContext A UObject managed by the UWorld that's making the request. Used to support multiple PIEs (see UBeamUserSlot::GetNamespacedSlotId). 
	 */
	UFUNCTION(BlueprintCallable, BlueprintInternalUseOnly, Category="Beam|Backend|Payments", meta=(DefaultToSelf="CallingContext", AdvancedDisplay="CallingContext", AutoCreateRefTerm="UserSlot,OnSuccess,OnError,OnComplete", BeamFlowFunction))
	void PostGoogleplayPurchaseFailWithRetry(FUserSlot UserSlot, const FBeamRetryConfig& RetryConfig, UPostGoogleplayPurchaseFailRequest* Request, const FOnPostGoogleplayPurchaseFailSuccess& OnSuccess, const FOnPostGoogleplayPurchaseFailError& OnError, const FOnPostGoogleplayPurchaseFailComplete& OnComplete, FBeamRequestContext& OutRequestContext, const UObject* CallingContext = nullptr);
		
	/**
	 * @brief Makes an authenticated request to the Post /basic/payments/googleplay/purchase/cancel endpoint of the Payments Service.
	 *
	 * @param UserSlot The authenticated UserSlot with the user making the request.
	 * @param RetryConfig The retry config for this specific request. 
	 * @param Request The Request UObject. All (de)serialized data the request data creates is tied to the lifecycle of this object.
	 * @param OnSuccess What to do if the requests receives a successful response.
	 * @param OnError What to do if the request receives an error response.
	 * @param OnComplete What to after either OnSuccess or OnError have finished executing.
	 * @param OutRequestContext The Request Context -- used to query information about the request or to cancel it while it's in flight.
	 * @param CallingContext A UObject managed by the UWorld that's making the request. Used to support multiple PIEs (see UBeamUserSlot::GetNamespacedSlotId). 
	 */
	UFUNCTION(BlueprintCallable, BlueprintInternalUseOnly, Category="Beam|Backend|Payments", meta=(DefaultToSelf="CallingContext", AdvancedDisplay="CallingContext", AutoCreateRefTerm="UserSlot,OnSuccess,OnError,OnComplete", BeamFlowFunction))
	void PostGoogleplayPurchaseCancelWithRetry(FUserSlot UserSlot, const FBeamRetryConfig& RetryConfig, UPostGoogleplayPurchaseCancelRequest* Request, const FOnPostGoogleplayPurchaseCancelSuccess& OnSuccess, const FOnPostGoogleplayPurchaseCancelError& OnError, const FOnPostGoogleplayPurchaseCancelComplete& OnComplete, FBeamRequestContext& OutRequestContext, const UObject* CallingContext = nullptr);
		
	/**
	 * @brief Makes an authenticated request to the Post /basic/payments/coupon/purchase/fail endpoint of the Payments Service.
	 *
	 * @param UserSlot The authenticated UserSlot with the user making the request.
	 * @param RetryConfig The retry config for this specific request. 
	 * @param Request The Request UObject. All (de)serialized data the request data creates is tied to the lifecycle of this object.
	 * @param OnSuccess What to do if the requests receives a successful response.
	 * @param OnError What to do if the request receives an error response.
	 * @param OnComplete What to after either OnSuccess or OnError have finished executing.
	 * @param OutRequestContext The Request Context -- used to query information about the request or to cancel it while it's in flight.
	 * @param CallingContext A UObject managed by the UWorld that's making the request. Used to support multiple PIEs (see UBeamUserSlot::GetNamespacedSlotId). 
	 */
	UFUNCTION(BlueprintCallable, BlueprintInternalUseOnly, Category="Beam|Backend|Payments", meta=(DefaultToSelf="CallingContext", AdvancedDisplay="CallingContext", AutoCreateRefTerm="UserSlot,OnSuccess,OnError,OnComplete", BeamFlowFunction))
	void PostCouponPurchaseFailWithRetry(FUserSlot UserSlot, const FBeamRetryConfig& RetryConfig, UPostCouponPurchaseFailRequest* Request, const FOnPostCouponPurchaseFailSuccess& OnSuccess, const FOnPostCouponPurchaseFailError& OnError, const FOnPostCouponPurchaseFailComplete& OnComplete, FBeamRequestContext& OutRequestContext, const UObject* CallingContext = nullptr);
		
	/**
	 * @brief Makes an authenticated request to the Post /basic/payments/steam/purchase/begin endpoint of the Payments Service.
	 *
	 * @param UserSlot The authenticated UserSlot with the user making the request.
	 * @param RetryConfig The retry config for this specific request. 
	 * @param Request The Request UObject. All (de)serialized data the request data creates is tied to the lifecycle of this object.
	 * @param OnSuccess What to do if the requests receives a successful response.
	 * @param OnError What to do if the request receives an error response.
	 * @param OnComplete What to after either OnSuccess or OnError have finished executing.
	 * @param OutRequestContext The Request Context -- used to query information about the request or to cancel it while it's in flight.
	 * @param CallingContext A UObject managed by the UWorld that's making the request. Used to support multiple PIEs (see UBeamUserSlot::GetNamespacedSlotId). 
	 */
	UFUNCTION(BlueprintCallable, BlueprintInternalUseOnly, Category="Beam|Backend|Payments", meta=(DefaultToSelf="CallingContext", AdvancedDisplay="CallingContext", AutoCreateRefTerm="UserSlot,OnSuccess,OnError,OnComplete", BeamFlowFunction))
	void PostSteamPurchaseBeginWithRetry(FUserSlot UserSlot, const FBeamRetryConfig& RetryConfig, UPostSteamPurchaseBeginRequest* Request, const FOnPostSteamPurchaseBeginSuccess& OnSuccess, const FOnPostSteamPurchaseBeginError& OnError, const FOnPostSteamPurchaseBeginComplete& OnComplete, FBeamRequestContext& OutRequestContext, const UObject* CallingContext = nullptr);
		
	/**
	 * @brief Makes an authenticated request to the Post /basic/payments/steam/purchase/cancel endpoint of the Payments Service.
	 *
	 * @param UserSlot The authenticated UserSlot with the user making the request.
	 * @param RetryConfig The retry config for this specific request. 
	 * @param Request The Request UObject. All (de)serialized data the request data creates is tied to the lifecycle of this object.
	 * @param OnSuccess What to do if the requests receives a successful response.
	 * @param OnError What to do if the request receives an error response.
	 * @param OnComplete What to after either OnSuccess or OnError have finished executing.
	 * @param OutRequestContext The Request Context -- used to query information about the request or to cancel it while it's in flight.
	 * @param CallingContext A UObject managed by the UWorld that's making the request. Used to support multiple PIEs (see UBeamUserSlot::GetNamespacedSlotId). 
	 */
	UFUNCTION(BlueprintCallable, BlueprintInternalUseOnly, Category="Beam|Backend|Payments", meta=(DefaultToSelf="CallingContext", AdvancedDisplay="CallingContext", AutoCreateRefTerm="UserSlot,OnSuccess,OnError,OnComplete", BeamFlowFunction))
	void PostSteamPurchaseCancelWithRetry(FUserSlot UserSlot, const FBeamRetryConfig& RetryConfig, UPostSteamPurchaseCancelRequest* Request, const FOnPostSteamPurchaseCancelSuccess& OnSuccess, const FOnPostSteamPurchaseCancelError& OnError, const FOnPostSteamPurchaseCancelComplete& OnComplete, FBeamRequestContext& OutRequestContext, const UObject* CallingContext = nullptr);
		
	/**
	 * @brief Makes an authenticated request to the Post /basic/payments/windows/purchase/cancel endpoint of the Payments Service.
	 *
	 * @param UserSlot The authenticated UserSlot with the user making the request.
	 * @param RetryConfig The retry config for this specific request. 
	 * @param Request The Request UObject. All (de)serialized data the request data creates is tied to the lifecycle of this object.
	 * @param OnSuccess What to do if the requests receives a successful response.
	 * @param OnError What to do if the request receives an error response.
	 * @param OnComplete What to after either OnSuccess or OnError have finished executing.
	 * @param OutRequestContext The Request Context -- used to query information about the request or to cancel it while it's in flight.
	 * @param CallingContext A UObject managed by the UWorld that's making the request. Used to support multiple PIEs (see UBeamUserSlot::GetNamespacedSlotId). 
	 */
	UFUNCTION(BlueprintCallable, BlueprintInternalUseOnly, Category="Beam|Backend|Payments", meta=(DefaultToSelf="CallingContext", AdvancedDisplay="CallingContext", AutoCreateRefTerm="UserSlot,OnSuccess,OnError,OnComplete", BeamFlowFunction))
	void PostWindowsPurchaseCancelWithRetry(FUserSlot UserSlot, const FBeamRetryConfig& RetryConfig, UPostWindowsPurchaseCancelRequest* Request, const FOnPostWindowsPurchaseCancelSuccess& OnSuccess, const FOnPostWindowsPurchaseCancelError& OnError, const FOnPostWindowsPurchaseCancelComplete& OnComplete, FBeamRequestContext& OutRequestContext, const UObject* CallingContext = nullptr);
		
	/**
	 * @brief Makes an authenticated request to the Post /basic/payments/windows/purchase/fail endpoint of the Payments Service.
	 *
	 * @param UserSlot The authenticated UserSlot with the user making the request.
	 * @param RetryConfig The retry config for this specific request. 
	 * @param Request The Request UObject. All (de)serialized data the request data creates is tied to the lifecycle of this object.
	 * @param OnSuccess What to do if the requests receives a successful response.
	 * @param OnError What to do if the request receives an error response.
	 * @param OnComplete What to after either OnSuccess or OnError have finished executing.
	 * @param OutRequestContext The Request Context -- used to query information about the request or to cancel it while it's in flight.
	 * @param CallingContext A UObject managed by the UWorld that's making the request. Used to support multiple PIEs (see UBeamUserSlot::GetNamespacedSlotId). 
	 */
	UFUNCTION(BlueprintCallable, BlueprintInternalUseOnly, Category="Beam|Backend|Payments", meta=(DefaultToSelf="CallingContext", AdvancedDisplay="CallingContext", AutoCreateRefTerm="UserSlot,OnSuccess,OnError,OnComplete", BeamFlowFunction))
	void PostWindowsPurchaseFailWithRetry(FUserSlot UserSlot, const FBeamRetryConfig& RetryConfig, UPostWindowsPurchaseFailRequest* Request, const FOnPostWindowsPurchaseFailSuccess& OnSuccess, const FOnPostWindowsPurchaseFailError& OnError, const FOnPostWindowsPurchaseFailComplete& OnComplete, FBeamRequestContext& OutRequestContext, const UObject* CallingContext = nullptr);
		
	/**
	 * @brief Makes an authenticated request to the Post /basic/payments/itunes/purchase/cancel endpoint of the Payments Service.
	 *
	 * @param UserSlot The authenticated UserSlot with the user making the request.
	 * @param RetryConfig The retry config for this specific request. 
	 * @param Request The Request UObject. All (de)serialized data the request data creates is tied to the lifecycle of this object.
	 * @param OnSuccess What to do if the requests receives a successful response.
	 * @param OnError What to do if the request receives an error response.
	 * @param OnComplete What to after either OnSuccess or OnError have finished executing.
	 * @param OutRequestContext The Request Context -- used to query information about the request or to cancel it while it's in flight.
	 * @param CallingContext A UObject managed by the UWorld that's making the request. Used to support multiple PIEs (see UBeamUserSlot::GetNamespacedSlotId). 
	 */
	UFUNCTION(BlueprintCallable, BlueprintInternalUseOnly, Category="Beam|Backend|Payments", meta=(DefaultToSelf="CallingContext", AdvancedDisplay="CallingContext", AutoCreateRefTerm="UserSlot,OnSuccess,OnError,OnComplete", BeamFlowFunction))
	void PostItunesPurchaseCancelWithRetry(FUserSlot UserSlot, const FBeamRetryConfig& RetryConfig, UPostItunesPurchaseCancelRequest* Request, const FOnPostItunesPurchaseCancelSuccess& OnSuccess, const FOnPostItunesPurchaseCancelError& OnError, const FOnPostItunesPurchaseCancelComplete& OnComplete, FBeamRequestContext& OutRequestContext, const UObject* CallingContext = nullptr);
};
