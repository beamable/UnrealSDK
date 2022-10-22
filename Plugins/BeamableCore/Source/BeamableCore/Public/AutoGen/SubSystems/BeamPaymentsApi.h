

#pragma once

#include "CoreMinimal.h"
#include "BeamBackend/BeamBackend.h"

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
UCLASS(BlueprintType)
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

	
	/**
	 * @brief Private implementation that all overloaded BP UFunctions call.	  
	 */
	void BP_PostWindowsPurchaseTrackImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, FBeamConnectivity& ConnectivityStatus, UPostWindowsPurchaseTrackRequest* RequestData,
	                                const FOnPostWindowsPurchaseTrackSuccess& OnSuccess, const FOnPostWindowsPurchaseTrackError& OnError, const FOnPostWindowsPurchaseTrackComplete& OnComplete,
	                                int64& OutRequestId) const;
	/**
	 * @brief Overload version for binding lambdas when in C++ land. Prefer the BP version whenever possible, this is here mostly for quick experimentation purposes.	 
	 */
	void CPP_PostWindowsPurchaseTrackImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, FBeamConnectivity& ConnectivityStatus, UPostWindowsPurchaseTrackRequest* RequestData,
	                                 const FOnPostWindowsPurchaseTrackFullResponse& Handler) const;

		
	/**
	 * @brief Private implementation that all overloaded BP UFunctions call.	  
	 */
	void BP_GetAuditsImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, FBeamConnectivity& ConnectivityStatus, UGetAuditsRequest* RequestData,
	                                const FOnGetAuditsSuccess& OnSuccess, const FOnGetAuditsError& OnError, const FOnGetAuditsComplete& OnComplete,
	                                int64& OutRequestId) const;
	/**
	 * @brief Overload version for binding lambdas when in C++ land. Prefer the BP version whenever possible, this is here mostly for quick experimentation purposes.	 
	 */
	void CPP_GetAuditsImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, FBeamConnectivity& ConnectivityStatus, UGetAuditsRequest* RequestData,
	                                 const FOnGetAuditsFullResponse& Handler) const;

		
	/**
	 * @brief Private implementation that all overloaded BP UFunctions call.	  
	 */
	void BP_PostWindowsPurchaseCompleteImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, FBeamConnectivity& ConnectivityStatus, UPostWindowsPurchaseCompleteRequest* RequestData,
	                                const FOnPostWindowsPurchaseCompleteSuccess& OnSuccess, const FOnPostWindowsPurchaseCompleteError& OnError, const FOnPostWindowsPurchaseCompleteComplete& OnComplete,
	                                int64& OutRequestId) const;
	/**
	 * @brief Overload version for binding lambdas when in C++ land. Prefer the BP version whenever possible, this is here mostly for quick experimentation purposes.	 
	 */
	void CPP_PostWindowsPurchaseCompleteImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, FBeamConnectivity& ConnectivityStatus, UPostWindowsPurchaseCompleteRequest* RequestData,
	                                 const FOnPostWindowsPurchaseCompleteFullResponse& Handler) const;

		
	/**
	 * @brief Private implementation that all overloaded BP UFunctions call.	  
	 */
	void BP_GetFacebookUpdateImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, FBeamConnectivity& ConnectivityStatus, UGetFacebookUpdateRequest* RequestData,
	                                const FOnGetFacebookUpdateSuccess& OnSuccess, const FOnGetFacebookUpdateError& OnError, const FOnGetFacebookUpdateComplete& OnComplete,
	                                int64& OutRequestId) const;
	/**
	 * @brief Overload version for binding lambdas when in C++ land. Prefer the BP version whenever possible, this is here mostly for quick experimentation purposes.	 
	 */
	void CPP_GetFacebookUpdateImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, FBeamConnectivity& ConnectivityStatus, UGetFacebookUpdateRequest* RequestData,
	                                 const FOnGetFacebookUpdateFullResponse& Handler) const;

		
	/**
	 * @brief Private implementation that all overloaded BP UFunctions call.	  
	 */
	void BP_PostFacebookUpdateImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, FBeamConnectivity& ConnectivityStatus, UPostFacebookUpdateRequest* RequestData,
	                                const FOnPostFacebookUpdateSuccess& OnSuccess, const FOnPostFacebookUpdateError& OnError, const FOnPostFacebookUpdateComplete& OnComplete,
	                                int64& OutRequestId) const;
	/**
	 * @brief Overload version for binding lambdas when in C++ land. Prefer the BP version whenever possible, this is here mostly for quick experimentation purposes.	 
	 */
	void CPP_PostFacebookUpdateImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, FBeamConnectivity& ConnectivityStatus, UPostFacebookUpdateRequest* RequestData,
	                                 const FOnPostFacebookUpdateFullResponse& Handler) const;

		
	/**
	 * @brief Private implementation that all overloaded BP UFunctions call.	  
	 */
	void BP_PostFacebookPurchaseCompleteImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, FBeamConnectivity& ConnectivityStatus, UPostFacebookPurchaseCompleteRequest* RequestData,
	                                const FOnPostFacebookPurchaseCompleteSuccess& OnSuccess, const FOnPostFacebookPurchaseCompleteError& OnError, const FOnPostFacebookPurchaseCompleteComplete& OnComplete,
	                                int64& OutRequestId) const;
	/**
	 * @brief Overload version for binding lambdas when in C++ land. Prefer the BP version whenever possible, this is here mostly for quick experimentation purposes.	 
	 */
	void CPP_PostFacebookPurchaseCompleteImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, FBeamConnectivity& ConnectivityStatus, UPostFacebookPurchaseCompleteRequest* RequestData,
	                                 const FOnPostFacebookPurchaseCompleteFullResponse& Handler) const;

		
	/**
	 * @brief Private implementation that all overloaded BP UFunctions call.	  
	 */
	void BP_PostTestPurchaseCompleteImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, FBeamConnectivity& ConnectivityStatus, UPostTestPurchaseCompleteRequest* RequestData,
	                                const FOnPostTestPurchaseCompleteSuccess& OnSuccess, const FOnPostTestPurchaseCompleteError& OnError, const FOnPostTestPurchaseCompleteComplete& OnComplete,
	                                int64& OutRequestId) const;
	/**
	 * @brief Overload version for binding lambdas when in C++ land. Prefer the BP version whenever possible, this is here mostly for quick experimentation purposes.	 
	 */
	void CPP_PostTestPurchaseCompleteImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, FBeamConnectivity& ConnectivityStatus, UPostTestPurchaseCompleteRequest* RequestData,
	                                 const FOnPostTestPurchaseCompleteFullResponse& Handler) const;

		
	/**
	 * @brief Private implementation that all overloaded BP UFunctions call.	  
	 */
	void BP_GetItunesProductImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, FBeamConnectivity& ConnectivityStatus, UGetItunesProductRequest* RequestData,
	                                const FOnGetItunesProductSuccess& OnSuccess, const FOnGetItunesProductError& OnError, const FOnGetItunesProductComplete& OnComplete,
	                                int64& OutRequestId) const;
	/**
	 * @brief Overload version for binding lambdas when in C++ land. Prefer the BP version whenever possible, this is here mostly for quick experimentation purposes.	 
	 */
	void CPP_GetItunesProductImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, FBeamConnectivity& ConnectivityStatus, UGetItunesProductRequest* RequestData,
	                                 const FOnGetItunesProductFullResponse& Handler) const;

		
	/**
	 * @brief Private implementation that all overloaded BP UFunctions call.	  
	 */
	void BP_PostGoogleplayPurchaseCompleteImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, FBeamConnectivity& ConnectivityStatus, UPostGoogleplayPurchaseCompleteRequest* RequestData,
	                                const FOnPostGoogleplayPurchaseCompleteSuccess& OnSuccess, const FOnPostGoogleplayPurchaseCompleteError& OnError, const FOnPostGoogleplayPurchaseCompleteComplete& OnComplete,
	                                int64& OutRequestId) const;
	/**
	 * @brief Overload version for binding lambdas when in C++ land. Prefer the BP version whenever possible, this is here mostly for quick experimentation purposes.	 
	 */
	void CPP_PostGoogleplayPurchaseCompleteImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, FBeamConnectivity& ConnectivityStatus, UPostGoogleplayPurchaseCompleteRequest* RequestData,
	                                 const FOnPostGoogleplayPurchaseCompleteFullResponse& Handler) const;

		
	/**
	 * @brief Private implementation that all overloaded BP UFunctions call.	  
	 */
	void BP_PostTestPurchaseTrackImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, FBeamConnectivity& ConnectivityStatus, UPostTestPurchaseTrackRequest* RequestData,
	                                const FOnPostTestPurchaseTrackSuccess& OnSuccess, const FOnPostTestPurchaseTrackError& OnError, const FOnPostTestPurchaseTrackComplete& OnComplete,
	                                int64& OutRequestId) const;
	/**
	 * @brief Overload version for binding lambdas when in C++ land. Prefer the BP version whenever possible, this is here mostly for quick experimentation purposes.	 
	 */
	void CPP_PostTestPurchaseTrackImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, FBeamConnectivity& ConnectivityStatus, UPostTestPurchaseTrackRequest* RequestData,
	                                 const FOnPostTestPurchaseTrackFullResponse& Handler) const;

		
	/**
	 * @brief Private implementation that all overloaded BP UFunctions call.	  
	 */
	void BP_PostGoogleplayPurchaseVerifyImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, FBeamConnectivity& ConnectivityStatus, UPostGoogleplayPurchaseVerifyRequest* RequestData,
	                                const FOnPostGoogleplayPurchaseVerifySuccess& OnSuccess, const FOnPostGoogleplayPurchaseVerifyError& OnError, const FOnPostGoogleplayPurchaseVerifyComplete& OnComplete,
	                                int64& OutRequestId) const;
	/**
	 * @brief Overload version for binding lambdas when in C++ land. Prefer the BP version whenever possible, this is here mostly for quick experimentation purposes.	 
	 */
	void CPP_PostGoogleplayPurchaseVerifyImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, FBeamConnectivity& ConnectivityStatus, UPostGoogleplayPurchaseVerifyRequest* RequestData,
	                                 const FOnPostGoogleplayPurchaseVerifyFullResponse& Handler) const;

		
	/**
	 * @brief Private implementation that all overloaded BP UFunctions call.	  
	 */
	void BP_PostCouponPurchaseTrackImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, FBeamConnectivity& ConnectivityStatus, UPostCouponPurchaseTrackRequest* RequestData,
	                                const FOnPostCouponPurchaseTrackSuccess& OnSuccess, const FOnPostCouponPurchaseTrackError& OnError, const FOnPostCouponPurchaseTrackComplete& OnComplete,
	                                int64& OutRequestId) const;
	/**
	 * @brief Overload version for binding lambdas when in C++ land. Prefer the BP version whenever possible, this is here mostly for quick experimentation purposes.	 
	 */
	void CPP_PostCouponPurchaseTrackImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, FBeamConnectivity& ConnectivityStatus, UPostCouponPurchaseTrackRequest* RequestData,
	                                 const FOnPostCouponPurchaseTrackFullResponse& Handler) const;

		
	/**
	 * @brief Private implementation that all overloaded BP UFunctions call.	  
	 */
	void BP_PostSteamPurchaseCompleteImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, FBeamConnectivity& ConnectivityStatus, UPostSteamPurchaseCompleteRequest* RequestData,
	                                const FOnPostSteamPurchaseCompleteSuccess& OnSuccess, const FOnPostSteamPurchaseCompleteError& OnError, const FOnPostSteamPurchaseCompleteComplete& OnComplete,
	                                int64& OutRequestId) const;
	/**
	 * @brief Overload version for binding lambdas when in C++ land. Prefer the BP version whenever possible, this is here mostly for quick experimentation purposes.	 
	 */
	void CPP_PostSteamPurchaseCompleteImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, FBeamConnectivity& ConnectivityStatus, UPostSteamPurchaseCompleteRequest* RequestData,
	                                 const FOnPostSteamPurchaseCompleteFullResponse& Handler) const;

		
	/**
	 * @brief Private implementation that all overloaded BP UFunctions call.	  
	 */
	void BP_PostFacebookPurchaseTrackImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, FBeamConnectivity& ConnectivityStatus, UPostFacebookPurchaseTrackRequest* RequestData,
	                                const FOnPostFacebookPurchaseTrackSuccess& OnSuccess, const FOnPostFacebookPurchaseTrackError& OnError, const FOnPostFacebookPurchaseTrackComplete& OnComplete,
	                                int64& OutRequestId) const;
	/**
	 * @brief Overload version for binding lambdas when in C++ land. Prefer the BP version whenever possible, this is here mostly for quick experimentation purposes.	 
	 */
	void CPP_PostFacebookPurchaseTrackImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, FBeamConnectivity& ConnectivityStatus, UPostFacebookPurchaseTrackRequest* RequestData,
	                                 const FOnPostFacebookPurchaseTrackFullResponse& Handler) const;

		
	/**
	 * @brief Private implementation that all overloaded BP UFunctions call.	  
	 */
	void BP_PostTestPurchaseVerifyImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, FBeamConnectivity& ConnectivityStatus, UPostTestPurchaseVerifyRequest* RequestData,
	                                const FOnPostTestPurchaseVerifySuccess& OnSuccess, const FOnPostTestPurchaseVerifyError& OnError, const FOnPostTestPurchaseVerifyComplete& OnComplete,
	                                int64& OutRequestId) const;
	/**
	 * @brief Overload version for binding lambdas when in C++ land. Prefer the BP version whenever possible, this is here mostly for quick experimentation purposes.	 
	 */
	void CPP_PostTestPurchaseVerifyImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, FBeamConnectivity& ConnectivityStatus, UPostTestPurchaseVerifyRequest* RequestData,
	                                 const FOnPostTestPurchaseVerifyFullResponse& Handler) const;

		
	/**
	 * @brief Private implementation that all overloaded BP UFunctions call.	  
	 */
	void BP_PostGoogleplayPurchaseTrackImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, FBeamConnectivity& ConnectivityStatus, UPostGoogleplayPurchaseTrackRequest* RequestData,
	                                const FOnPostGoogleplayPurchaseTrackSuccess& OnSuccess, const FOnPostGoogleplayPurchaseTrackError& OnError, const FOnPostGoogleplayPurchaseTrackComplete& OnComplete,
	                                int64& OutRequestId) const;
	/**
	 * @brief Overload version for binding lambdas when in C++ land. Prefer the BP version whenever possible, this is here mostly for quick experimentation purposes.	 
	 */
	void CPP_PostGoogleplayPurchaseTrackImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, FBeamConnectivity& ConnectivityStatus, UPostGoogleplayPurchaseTrackRequest* RequestData,
	                                 const FOnPostGoogleplayPurchaseTrackFullResponse& Handler) const;

		
	/**
	 * @brief Private implementation that all overloaded BP UFunctions call.	  
	 */
	void BP_GetSteamPricesImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, FBeamConnectivity& ConnectivityStatus, UGetSteamPricesRequest* RequestData,
	                                const FOnGetSteamPricesSuccess& OnSuccess, const FOnGetSteamPricesError& OnError, const FOnGetSteamPricesComplete& OnComplete,
	                                int64& OutRequestId) const;
	/**
	 * @brief Overload version for binding lambdas when in C++ land. Prefer the BP version whenever possible, this is here mostly for quick experimentation purposes.	 
	 */
	void CPP_GetSteamPricesImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, FBeamConnectivity& ConnectivityStatus, UGetSteamPricesRequest* RequestData,
	                                 const FOnGetSteamPricesFullResponse& Handler) const;

		
	/**
	 * @brief Private implementation that all overloaded BP UFunctions call.	  
	 */
	void BP_PostWindowsPurchaseVerifyImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, FBeamConnectivity& ConnectivityStatus, UPostWindowsPurchaseVerifyRequest* RequestData,
	                                const FOnPostWindowsPurchaseVerifySuccess& OnSuccess, const FOnPostWindowsPurchaseVerifyError& OnError, const FOnPostWindowsPurchaseVerifyComplete& OnComplete,
	                                int64& OutRequestId) const;
	/**
	 * @brief Overload version for binding lambdas when in C++ land. Prefer the BP version whenever possible, this is here mostly for quick experimentation purposes.	 
	 */
	void CPP_PostWindowsPurchaseVerifyImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, FBeamConnectivity& ConnectivityStatus, UPostWindowsPurchaseVerifyRequest* RequestData,
	                                 const FOnPostWindowsPurchaseVerifyFullResponse& Handler) const;

		
	/**
	 * @brief Private implementation that all overloaded BP UFunctions call.	  
	 */
	void BP_PostItunesPurchaseVerifyImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, FBeamConnectivity& ConnectivityStatus, UPostItunesPurchaseVerifyRequest* RequestData,
	                                const FOnPostItunesPurchaseVerifySuccess& OnSuccess, const FOnPostItunesPurchaseVerifyError& OnError, const FOnPostItunesPurchaseVerifyComplete& OnComplete,
	                                int64& OutRequestId) const;
	/**
	 * @brief Overload version for binding lambdas when in C++ land. Prefer the BP version whenever possible, this is here mostly for quick experimentation purposes.	 
	 */
	void CPP_PostItunesPurchaseVerifyImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, FBeamConnectivity& ConnectivityStatus, UPostItunesPurchaseVerifyRequest* RequestData,
	                                 const FOnPostItunesPurchaseVerifyFullResponse& Handler) const;

		
	/**
	 * @brief Private implementation that all overloaded BP UFunctions call.	  
	 */
	void BP_PostItunesPurchaseCompleteImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, FBeamConnectivity& ConnectivityStatus, UPostItunesPurchaseCompleteRequest* RequestData,
	                                const FOnPostItunesPurchaseCompleteSuccess& OnSuccess, const FOnPostItunesPurchaseCompleteError& OnError, const FOnPostItunesPurchaseCompleteComplete& OnComplete,
	                                int64& OutRequestId) const;
	/**
	 * @brief Overload version for binding lambdas when in C++ land. Prefer the BP version whenever possible, this is here mostly for quick experimentation purposes.	 
	 */
	void CPP_PostItunesPurchaseCompleteImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, FBeamConnectivity& ConnectivityStatus, UPostItunesPurchaseCompleteRequest* RequestData,
	                                 const FOnPostItunesPurchaseCompleteFullResponse& Handler) const;

		
	/**
	 * @brief Private implementation that all overloaded BP UFunctions call.	  
	 */
	void BP_PostFacebookPurchaseVerifyImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, FBeamConnectivity& ConnectivityStatus, UPostFacebookPurchaseVerifyRequest* RequestData,
	                                const FOnPostFacebookPurchaseVerifySuccess& OnSuccess, const FOnPostFacebookPurchaseVerifyError& OnError, const FOnPostFacebookPurchaseVerifyComplete& OnComplete,
	                                int64& OutRequestId) const;
	/**
	 * @brief Overload version for binding lambdas when in C++ land. Prefer the BP version whenever possible, this is here mostly for quick experimentation purposes.	 
	 */
	void CPP_PostFacebookPurchaseVerifyImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, FBeamConnectivity& ConnectivityStatus, UPostFacebookPurchaseVerifyRequest* RequestData,
	                                 const FOnPostFacebookPurchaseVerifyFullResponse& Handler) const;

		
	/**
	 * @brief Private implementation that all overloaded BP UFunctions call.	  
	 */
	void BP_PostSteamPurchaseTrackImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, FBeamConnectivity& ConnectivityStatus, UPostSteamPurchaseTrackRequest* RequestData,
	                                const FOnPostSteamPurchaseTrackSuccess& OnSuccess, const FOnPostSteamPurchaseTrackError& OnError, const FOnPostSteamPurchaseTrackComplete& OnComplete,
	                                int64& OutRequestId) const;
	/**
	 * @brief Overload version for binding lambdas when in C++ land. Prefer the BP version whenever possible, this is here mostly for quick experimentation purposes.	 
	 */
	void CPP_PostSteamPurchaseTrackImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, FBeamConnectivity& ConnectivityStatus, UPostSteamPurchaseTrackRequest* RequestData,
	                                 const FOnPostSteamPurchaseTrackFullResponse& Handler) const;

		
	/**
	 * @brief Private implementation that all overloaded BP UFunctions call.	  
	 */
	void BP_PostCouponPurchaseVerifyImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, FBeamConnectivity& ConnectivityStatus, UPostCouponPurchaseVerifyRequest* RequestData,
	                                const FOnPostCouponPurchaseVerifySuccess& OnSuccess, const FOnPostCouponPurchaseVerifyError& OnError, const FOnPostCouponPurchaseVerifyComplete& OnComplete,
	                                int64& OutRequestId) const;
	/**
	 * @brief Overload version for binding lambdas when in C++ land. Prefer the BP version whenever possible, this is here mostly for quick experimentation purposes.	 
	 */
	void CPP_PostCouponPurchaseVerifyImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, FBeamConnectivity& ConnectivityStatus, UPostCouponPurchaseVerifyRequest* RequestData,
	                                 const FOnPostCouponPurchaseVerifyFullResponse& Handler) const;

		
	/**
	 * @brief Private implementation that all overloaded BP UFunctions call.	  
	 */
	void BP_GetWindowsProductImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, FBeamConnectivity& ConnectivityStatus, UGetWindowsProductRequest* RequestData,
	                                const FOnGetWindowsProductSuccess& OnSuccess, const FOnGetWindowsProductError& OnError, const FOnGetWindowsProductComplete& OnComplete,
	                                int64& OutRequestId) const;
	/**
	 * @brief Overload version for binding lambdas when in C++ land. Prefer the BP version whenever possible, this is here mostly for quick experimentation purposes.	 
	 */
	void CPP_GetWindowsProductImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, FBeamConnectivity& ConnectivityStatus, UGetWindowsProductRequest* RequestData,
	                                 const FOnGetWindowsProductFullResponse& Handler) const;

		
	/**
	 * @brief Private implementation that all overloaded BP UFunctions call.	  
	 */
	void BP_GetFacebookProductImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, FBeamConnectivity& ConnectivityStatus, UGetFacebookProductRequest* RequestData,
	                                const FOnGetFacebookProductSuccess& OnSuccess, const FOnGetFacebookProductError& OnError, const FOnGetFacebookProductComplete& OnComplete,
	                                int64& OutRequestId) const;
	/**
	 * @brief Overload version for binding lambdas when in C++ land. Prefer the BP version whenever possible, this is here mostly for quick experimentation purposes.	 
	 */
	void CPP_GetFacebookProductImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, FBeamConnectivity& ConnectivityStatus, UGetFacebookProductRequest* RequestData,
	                                 const FOnGetFacebookProductFullResponse& Handler) const;

		
	/**
	 * @brief Private implementation that all overloaded BP UFunctions call.	  
	 */
	void BP_GetCouponProductImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, FBeamConnectivity& ConnectivityStatus, UGetCouponProductRequest* RequestData,
	                                const FOnGetCouponProductSuccess& OnSuccess, const FOnGetCouponProductError& OnError, const FOnGetCouponProductComplete& OnComplete,
	                                int64& OutRequestId) const;
	/**
	 * @brief Overload version for binding lambdas when in C++ land. Prefer the BP version whenever possible, this is here mostly for quick experimentation purposes.	 
	 */
	void CPP_GetCouponProductImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, FBeamConnectivity& ConnectivityStatus, UGetCouponProductRequest* RequestData,
	                                 const FOnGetCouponProductFullResponse& Handler) const;

		
	/**
	 * @brief Private implementation that all overloaded BP UFunctions call.	  
	 */
	void BP_GetSteamProductsImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, FBeamConnectivity& ConnectivityStatus, UGetSteamProductsRequest* RequestData,
	                                const FOnGetSteamProductsSuccess& OnSuccess, const FOnGetSteamProductsError& OnError, const FOnGetSteamProductsComplete& OnComplete,
	                                int64& OutRequestId) const;
	/**
	 * @brief Overload version for binding lambdas when in C++ land. Prefer the BP version whenever possible, this is here mostly for quick experimentation purposes.	 
	 */
	void CPP_GetSteamProductsImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, FBeamConnectivity& ConnectivityStatus, UGetSteamProductsRequest* RequestData,
	                                 const FOnGetSteamProductsFullResponse& Handler) const;

		
	/**
	 * @brief Private implementation that all overloaded BP UFunctions call.	  
	 */
	void BP_PostSteamAuthImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, FBeamConnectivity& ConnectivityStatus, UPostSteamAuthRequest* RequestData,
	                                const FOnPostSteamAuthSuccess& OnSuccess, const FOnPostSteamAuthError& OnError, const FOnPostSteamAuthComplete& OnComplete,
	                                int64& OutRequestId) const;
	/**
	 * @brief Overload version for binding lambdas when in C++ land. Prefer the BP version whenever possible, this is here mostly for quick experimentation purposes.	 
	 */
	void CPP_PostSteamAuthImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, FBeamConnectivity& ConnectivityStatus, UPostSteamAuthRequest* RequestData,
	                                 const FOnPostSteamAuthFullResponse& Handler) const;

		
	/**
	 * @brief Private implementation that all overloaded BP UFunctions call.	  
	 */
	void BP_GetSteamProductImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, FBeamConnectivity& ConnectivityStatus, UGetSteamProductRequest* RequestData,
	                                const FOnGetSteamProductSuccess& OnSuccess, const FOnGetSteamProductError& OnError, const FOnGetSteamProductComplete& OnComplete,
	                                int64& OutRequestId) const;
	/**
	 * @brief Overload version for binding lambdas when in C++ land. Prefer the BP version whenever possible, this is here mostly for quick experimentation purposes.	 
	 */
	void CPP_GetSteamProductImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, FBeamConnectivity& ConnectivityStatus, UGetSteamProductRequest* RequestData,
	                                 const FOnGetSteamProductFullResponse& Handler) const;

		
	/**
	 * @brief Private implementation that all overloaded BP UFunctions call.	  
	 */
	void BP_PostCouponPurchaseCompleteImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, FBeamConnectivity& ConnectivityStatus, UPostCouponPurchaseCompleteRequest* RequestData,
	                                const FOnPostCouponPurchaseCompleteSuccess& OnSuccess, const FOnPostCouponPurchaseCompleteError& OnError, const FOnPostCouponPurchaseCompleteComplete& OnComplete,
	                                int64& OutRequestId) const;
	/**
	 * @brief Overload version for binding lambdas when in C++ land. Prefer the BP version whenever possible, this is here mostly for quick experimentation purposes.	 
	 */
	void CPP_PostCouponPurchaseCompleteImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, FBeamConnectivity& ConnectivityStatus, UPostCouponPurchaseCompleteRequest* RequestData,
	                                 const FOnPostCouponPurchaseCompleteFullResponse& Handler) const;

		
	/**
	 * @brief Private implementation that all overloaded BP UFunctions call.	  
	 */
	void BP_GetGoogleplayProductImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, FBeamConnectivity& ConnectivityStatus, UGetGoogleplayProductRequest* RequestData,
	                                const FOnGetGoogleplayProductSuccess& OnSuccess, const FOnGetGoogleplayProductError& OnError, const FOnGetGoogleplayProductComplete& OnComplete,
	                                int64& OutRequestId) const;
	/**
	 * @brief Overload version for binding lambdas when in C++ land. Prefer the BP version whenever possible, this is here mostly for quick experimentation purposes.	 
	 */
	void CPP_GetGoogleplayProductImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, FBeamConnectivity& ConnectivityStatus, UGetGoogleplayProductRequest* RequestData,
	                                 const FOnGetGoogleplayProductFullResponse& Handler) const;

		
	/**
	 * @brief Private implementation that all overloaded BP UFunctions call.	  
	 */
	void BP_GetTestProductImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, FBeamConnectivity& ConnectivityStatus, UGetTestProductRequest* RequestData,
	                                const FOnGetTestProductSuccess& OnSuccess, const FOnGetTestProductError& OnError, const FOnGetTestProductComplete& OnComplete,
	                                int64& OutRequestId) const;
	/**
	 * @brief Overload version for binding lambdas when in C++ land. Prefer the BP version whenever possible, this is here mostly for quick experimentation purposes.	 
	 */
	void CPP_GetTestProductImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, FBeamConnectivity& ConnectivityStatus, UGetTestProductRequest* RequestData,
	                                 const FOnGetTestProductFullResponse& Handler) const;

		
	/**
	 * @brief Private implementation that all overloaded BP UFunctions call.	  
	 */
	void BP_PostSteamPurchaseVerifyImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, FBeamConnectivity& ConnectivityStatus, UPostSteamPurchaseVerifyRequest* RequestData,
	                                const FOnPostSteamPurchaseVerifySuccess& OnSuccess, const FOnPostSteamPurchaseVerifyError& OnError, const FOnPostSteamPurchaseVerifyComplete& OnComplete,
	                                int64& OutRequestId) const;
	/**
	 * @brief Overload version for binding lambdas when in C++ land. Prefer the BP version whenever possible, this is here mostly for quick experimentation purposes.	 
	 */
	void CPP_PostSteamPurchaseVerifyImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, FBeamConnectivity& ConnectivityStatus, UPostSteamPurchaseVerifyRequest* RequestData,
	                                 const FOnPostSteamPurchaseVerifyFullResponse& Handler) const;

		
	/**
	 * @brief Private implementation that all overloaded BP UFunctions call.	  
	 */
	void BP_PostItunesPurchaseTrackImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, FBeamConnectivity& ConnectivityStatus, UPostItunesPurchaseTrackRequest* RequestData,
	                                const FOnPostItunesPurchaseTrackSuccess& OnSuccess, const FOnPostItunesPurchaseTrackError& OnError, const FOnPostItunesPurchaseTrackComplete& OnComplete,
	                                int64& OutRequestId) const;
	/**
	 * @brief Overload version for binding lambdas when in C++ land. Prefer the BP version whenever possible, this is here mostly for quick experimentation purposes.	 
	 */
	void CPP_PostItunesPurchaseTrackImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, FBeamConnectivity& ConnectivityStatus, UPostItunesPurchaseTrackRequest* RequestData,
	                                 const FOnPostItunesPurchaseTrackFullResponse& Handler) const;

		
	/**
	 * @brief Private implementation that all overloaded BP UFunctions call.	  
	 */
	void BP_GetPaymentsImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, FBeamConnectivity& ConnectivityStatus, UGetPaymentsRequest* RequestData,
	                                const FOnGetPaymentsSuccess& OnSuccess, const FOnGetPaymentsError& OnError, const FOnGetPaymentsComplete& OnComplete,
	                                int64& OutRequestId) const;
	/**
	 * @brief Overload version for binding lambdas when in C++ land. Prefer the BP version whenever possible, this is here mostly for quick experimentation purposes.	 
	 */
	void CPP_GetPaymentsImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, FBeamConnectivity& ConnectivityStatus, UGetPaymentsRequest* RequestData,
	                                 const FOnGetPaymentsFullResponse& Handler) const;


	
	/**
	 * @brief Private implementation for requests that require authentication that all overloaded BP UFunctions call.	  
	 */
	void BP_PostTestPurchaseBeginImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, const FBeamAuthToken& AuthToken, FBeamConnectivity& ConnectivityStatus, UPostTestPurchaseBeginRequest* RequestData,
	                  const FOnPostTestPurchaseBeginSuccess& OnSuccess, const FOnPostTestPurchaseBeginError& OnError, const FOnPostTestPurchaseBeginComplete& OnComplete, int64& OutRequestId) const;
	/**
	 * @brief Overload version for binding lambdas when in C++ land. Prefer the BP version whenever possible, this is here mostly for quick experimentation purposes.	 
	 */
	void CPP_PostTestPurchaseBeginImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, const FBeamAuthToken& AuthToken, FBeamConnectivity& ConnectivityStatus, UPostTestPurchaseBeginRequest* RequestData,
	                   const FOnPostTestPurchaseBeginFullResponse& Handler) const;
		
	/**
	 * @brief Private implementation for requests that require authentication that all overloaded BP UFunctions call.	  
	 */
	void BP_PostSteamPurchaseFailImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, const FBeamAuthToken& AuthToken, FBeamConnectivity& ConnectivityStatus, UPostSteamPurchaseFailRequest* RequestData,
	                  const FOnPostSteamPurchaseFailSuccess& OnSuccess, const FOnPostSteamPurchaseFailError& OnError, const FOnPostSteamPurchaseFailComplete& OnComplete, int64& OutRequestId) const;
	/**
	 * @brief Overload version for binding lambdas when in C++ land. Prefer the BP version whenever possible, this is here mostly for quick experimentation purposes.	 
	 */
	void CPP_PostSteamPurchaseFailImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, const FBeamAuthToken& AuthToken, FBeamConnectivity& ConnectivityStatus, UPostSteamPurchaseFailRequest* RequestData,
	                   const FOnPostSteamPurchaseFailFullResponse& Handler) const;
		
	/**
	 * @brief Private implementation for requests that require authentication that all overloaded BP UFunctions call.	  
	 */
	void BP_PostFacebookPurchaseFailImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, const FBeamAuthToken& AuthToken, FBeamConnectivity& ConnectivityStatus, UPostFacebookPurchaseFailRequest* RequestData,
	                  const FOnPostFacebookPurchaseFailSuccess& OnSuccess, const FOnPostFacebookPurchaseFailError& OnError, const FOnPostFacebookPurchaseFailComplete& OnComplete, int64& OutRequestId) const;
	/**
	 * @brief Overload version for binding lambdas when in C++ land. Prefer the BP version whenever possible, this is here mostly for quick experimentation purposes.	 
	 */
	void CPP_PostFacebookPurchaseFailImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, const FBeamAuthToken& AuthToken, FBeamConnectivity& ConnectivityStatus, UPostFacebookPurchaseFailRequest* RequestData,
	                   const FOnPostFacebookPurchaseFailFullResponse& Handler) const;
		
	/**
	 * @brief Private implementation for requests that require authentication that all overloaded BP UFunctions call.	  
	 */
	void BP_PostGoogleplayPurchaseBeginImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, const FBeamAuthToken& AuthToken, FBeamConnectivity& ConnectivityStatus, UPostGoogleplayPurchaseBeginRequest* RequestData,
	                  const FOnPostGoogleplayPurchaseBeginSuccess& OnSuccess, const FOnPostGoogleplayPurchaseBeginError& OnError, const FOnPostGoogleplayPurchaseBeginComplete& OnComplete, int64& OutRequestId) const;
	/**
	 * @brief Overload version for binding lambdas when in C++ land. Prefer the BP version whenever possible, this is here mostly for quick experimentation purposes.	 
	 */
	void CPP_PostGoogleplayPurchaseBeginImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, const FBeamAuthToken& AuthToken, FBeamConnectivity& ConnectivityStatus, UPostGoogleplayPurchaseBeginRequest* RequestData,
	                   const FOnPostGoogleplayPurchaseBeginFullResponse& Handler) const;
		
	/**
	 * @brief Private implementation for requests that require authentication that all overloaded BP UFunctions call.	  
	 */
	void BP_PostItunesPurchaseBeginImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, const FBeamAuthToken& AuthToken, FBeamConnectivity& ConnectivityStatus, UPostItunesPurchaseBeginRequest* RequestData,
	                  const FOnPostItunesPurchaseBeginSuccess& OnSuccess, const FOnPostItunesPurchaseBeginError& OnError, const FOnPostItunesPurchaseBeginComplete& OnComplete, int64& OutRequestId) const;
	/**
	 * @brief Overload version for binding lambdas when in C++ land. Prefer the BP version whenever possible, this is here mostly for quick experimentation purposes.	 
	 */
	void CPP_PostItunesPurchaseBeginImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, const FBeamAuthToken& AuthToken, FBeamConnectivity& ConnectivityStatus, UPostItunesPurchaseBeginRequest* RequestData,
	                   const FOnPostItunesPurchaseBeginFullResponse& Handler) const;
		
	/**
	 * @brief Private implementation for requests that require authentication that all overloaded BP UFunctions call.	  
	 */
	void BP_PostFacebookPurchaseCancelImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, const FBeamAuthToken& AuthToken, FBeamConnectivity& ConnectivityStatus, UPostFacebookPurchaseCancelRequest* RequestData,
	                  const FOnPostFacebookPurchaseCancelSuccess& OnSuccess, const FOnPostFacebookPurchaseCancelError& OnError, const FOnPostFacebookPurchaseCancelComplete& OnComplete, int64& OutRequestId) const;
	/**
	 * @brief Overload version for binding lambdas when in C++ land. Prefer the BP version whenever possible, this is here mostly for quick experimentation purposes.	 
	 */
	void CPP_PostFacebookPurchaseCancelImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, const FBeamAuthToken& AuthToken, FBeamConnectivity& ConnectivityStatus, UPostFacebookPurchaseCancelRequest* RequestData,
	                   const FOnPostFacebookPurchaseCancelFullResponse& Handler) const;
		
	/**
	 * @brief Private implementation for requests that require authentication that all overloaded BP UFunctions call.	  
	 */
	void BP_PostItunesPurchaseFailImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, const FBeamAuthToken& AuthToken, FBeamConnectivity& ConnectivityStatus, UPostItunesPurchaseFailRequest* RequestData,
	                  const FOnPostItunesPurchaseFailSuccess& OnSuccess, const FOnPostItunesPurchaseFailError& OnError, const FOnPostItunesPurchaseFailComplete& OnComplete, int64& OutRequestId) const;
	/**
	 * @brief Overload version for binding lambdas when in C++ land. Prefer the BP version whenever possible, this is here mostly for quick experimentation purposes.	 
	 */
	void CPP_PostItunesPurchaseFailImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, const FBeamAuthToken& AuthToken, FBeamConnectivity& ConnectivityStatus, UPostItunesPurchaseFailRequest* RequestData,
	                   const FOnPostItunesPurchaseFailFullResponse& Handler) const;
		
	/**
	 * @brief Private implementation for requests that require authentication that all overloaded BP UFunctions call.	  
	 */
	void BP_PostTestPurchaseCancelImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, const FBeamAuthToken& AuthToken, FBeamConnectivity& ConnectivityStatus, UPostTestPurchaseCancelRequest* RequestData,
	                  const FOnPostTestPurchaseCancelSuccess& OnSuccess, const FOnPostTestPurchaseCancelError& OnError, const FOnPostTestPurchaseCancelComplete& OnComplete, int64& OutRequestId) const;
	/**
	 * @brief Overload version for binding lambdas when in C++ land. Prefer the BP version whenever possible, this is here mostly for quick experimentation purposes.	 
	 */
	void CPP_PostTestPurchaseCancelImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, const FBeamAuthToken& AuthToken, FBeamConnectivity& ConnectivityStatus, UPostTestPurchaseCancelRequest* RequestData,
	                   const FOnPostTestPurchaseCancelFullResponse& Handler) const;
		
	/**
	 * @brief Private implementation for requests that require authentication that all overloaded BP UFunctions call.	  
	 */
	void BP_PostTestPurchaseFailImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, const FBeamAuthToken& AuthToken, FBeamConnectivity& ConnectivityStatus, UPostTestPurchaseFailRequest* RequestData,
	                  const FOnPostTestPurchaseFailSuccess& OnSuccess, const FOnPostTestPurchaseFailError& OnError, const FOnPostTestPurchaseFailComplete& OnComplete, int64& OutRequestId) const;
	/**
	 * @brief Overload version for binding lambdas when in C++ land. Prefer the BP version whenever possible, this is here mostly for quick experimentation purposes.	 
	 */
	void CPP_PostTestPurchaseFailImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, const FBeamAuthToken& AuthToken, FBeamConnectivity& ConnectivityStatus, UPostTestPurchaseFailRequest* RequestData,
	                   const FOnPostTestPurchaseFailFullResponse& Handler) const;
		
	/**
	 * @brief Private implementation for requests that require authentication that all overloaded BP UFunctions call.	  
	 */
	void BP_PostCouponPurchaseCancelImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, const FBeamAuthToken& AuthToken, FBeamConnectivity& ConnectivityStatus, UPostCouponPurchaseCancelRequest* RequestData,
	                  const FOnPostCouponPurchaseCancelSuccess& OnSuccess, const FOnPostCouponPurchaseCancelError& OnError, const FOnPostCouponPurchaseCancelComplete& OnComplete, int64& OutRequestId) const;
	/**
	 * @brief Overload version for binding lambdas when in C++ land. Prefer the BP version whenever possible, this is here mostly for quick experimentation purposes.	 
	 */
	void CPP_PostCouponPurchaseCancelImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, const FBeamAuthToken& AuthToken, FBeamConnectivity& ConnectivityStatus, UPostCouponPurchaseCancelRequest* RequestData,
	                   const FOnPostCouponPurchaseCancelFullResponse& Handler) const;
		
	/**
	 * @brief Private implementation for requests that require authentication that all overloaded BP UFunctions call.	  
	 */
	void BP_PostCouponPurchaseBeginImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, const FBeamAuthToken& AuthToken, FBeamConnectivity& ConnectivityStatus, UPostCouponPurchaseBeginRequest* RequestData,
	                  const FOnPostCouponPurchaseBeginSuccess& OnSuccess, const FOnPostCouponPurchaseBeginError& OnError, const FOnPostCouponPurchaseBeginComplete& OnComplete, int64& OutRequestId) const;
	/**
	 * @brief Overload version for binding lambdas when in C++ land. Prefer the BP version whenever possible, this is here mostly for quick experimentation purposes.	 
	 */
	void CPP_PostCouponPurchaseBeginImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, const FBeamAuthToken& AuthToken, FBeamConnectivity& ConnectivityStatus, UPostCouponPurchaseBeginRequest* RequestData,
	                   const FOnPostCouponPurchaseBeginFullResponse& Handler) const;
		
	/**
	 * @brief Private implementation for requests that require authentication that all overloaded BP UFunctions call.	  
	 */
	void BP_PostFacebookPurchaseBeginImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, const FBeamAuthToken& AuthToken, FBeamConnectivity& ConnectivityStatus, UPostFacebookPurchaseBeginRequest* RequestData,
	                  const FOnPostFacebookPurchaseBeginSuccess& OnSuccess, const FOnPostFacebookPurchaseBeginError& OnError, const FOnPostFacebookPurchaseBeginComplete& OnComplete, int64& OutRequestId) const;
	/**
	 * @brief Overload version for binding lambdas when in C++ land. Prefer the BP version whenever possible, this is here mostly for quick experimentation purposes.	 
	 */
	void CPP_PostFacebookPurchaseBeginImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, const FBeamAuthToken& AuthToken, FBeamConnectivity& ConnectivityStatus, UPostFacebookPurchaseBeginRequest* RequestData,
	                   const FOnPostFacebookPurchaseBeginFullResponse& Handler) const;
		
	/**
	 * @brief Private implementation for requests that require authentication that all overloaded BP UFunctions call.	  
	 */
	void BP_GetSteamOrderImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, const FBeamAuthToken& AuthToken, FBeamConnectivity& ConnectivityStatus, UGetSteamOrderRequest* RequestData,
	                  const FOnGetSteamOrderSuccess& OnSuccess, const FOnGetSteamOrderError& OnError, const FOnGetSteamOrderComplete& OnComplete, int64& OutRequestId) const;
	/**
	 * @brief Overload version for binding lambdas when in C++ land. Prefer the BP version whenever possible, this is here mostly for quick experimentation purposes.	 
	 */
	void CPP_GetSteamOrderImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, const FBeamAuthToken& AuthToken, FBeamConnectivity& ConnectivityStatus, UGetSteamOrderRequest* RequestData,
	                   const FOnGetSteamOrderFullResponse& Handler) const;
		
	/**
	 * @brief Private implementation for requests that require authentication that all overloaded BP UFunctions call.	  
	 */
	void BP_PostWindowsPurchaseBeginImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, const FBeamAuthToken& AuthToken, FBeamConnectivity& ConnectivityStatus, UPostWindowsPurchaseBeginRequest* RequestData,
	                  const FOnPostWindowsPurchaseBeginSuccess& OnSuccess, const FOnPostWindowsPurchaseBeginError& OnError, const FOnPostWindowsPurchaseBeginComplete& OnComplete, int64& OutRequestId) const;
	/**
	 * @brief Overload version for binding lambdas when in C++ land. Prefer the BP version whenever possible, this is here mostly for quick experimentation purposes.	 
	 */
	void CPP_PostWindowsPurchaseBeginImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, const FBeamAuthToken& AuthToken, FBeamConnectivity& ConnectivityStatus, UPostWindowsPurchaseBeginRequest* RequestData,
	                   const FOnPostWindowsPurchaseBeginFullResponse& Handler) const;
		
	/**
	 * @brief Private implementation for requests that require authentication that all overloaded BP UFunctions call.	  
	 */
	void BP_PostGoogleplayPurchaseFailImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, const FBeamAuthToken& AuthToken, FBeamConnectivity& ConnectivityStatus, UPostGoogleplayPurchaseFailRequest* RequestData,
	                  const FOnPostGoogleplayPurchaseFailSuccess& OnSuccess, const FOnPostGoogleplayPurchaseFailError& OnError, const FOnPostGoogleplayPurchaseFailComplete& OnComplete, int64& OutRequestId) const;
	/**
	 * @brief Overload version for binding lambdas when in C++ land. Prefer the BP version whenever possible, this is here mostly for quick experimentation purposes.	 
	 */
	void CPP_PostGoogleplayPurchaseFailImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, const FBeamAuthToken& AuthToken, FBeamConnectivity& ConnectivityStatus, UPostGoogleplayPurchaseFailRequest* RequestData,
	                   const FOnPostGoogleplayPurchaseFailFullResponse& Handler) const;
		
	/**
	 * @brief Private implementation for requests that require authentication that all overloaded BP UFunctions call.	  
	 */
	void BP_PostGoogleplayPurchaseCancelImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, const FBeamAuthToken& AuthToken, FBeamConnectivity& ConnectivityStatus, UPostGoogleplayPurchaseCancelRequest* RequestData,
	                  const FOnPostGoogleplayPurchaseCancelSuccess& OnSuccess, const FOnPostGoogleplayPurchaseCancelError& OnError, const FOnPostGoogleplayPurchaseCancelComplete& OnComplete, int64& OutRequestId) const;
	/**
	 * @brief Overload version for binding lambdas when in C++ land. Prefer the BP version whenever possible, this is here mostly for quick experimentation purposes.	 
	 */
	void CPP_PostGoogleplayPurchaseCancelImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, const FBeamAuthToken& AuthToken, FBeamConnectivity& ConnectivityStatus, UPostGoogleplayPurchaseCancelRequest* RequestData,
	                   const FOnPostGoogleplayPurchaseCancelFullResponse& Handler) const;
		
	/**
	 * @brief Private implementation for requests that require authentication that all overloaded BP UFunctions call.	  
	 */
	void BP_PostCouponPurchaseFailImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, const FBeamAuthToken& AuthToken, FBeamConnectivity& ConnectivityStatus, UPostCouponPurchaseFailRequest* RequestData,
	                  const FOnPostCouponPurchaseFailSuccess& OnSuccess, const FOnPostCouponPurchaseFailError& OnError, const FOnPostCouponPurchaseFailComplete& OnComplete, int64& OutRequestId) const;
	/**
	 * @brief Overload version for binding lambdas when in C++ land. Prefer the BP version whenever possible, this is here mostly for quick experimentation purposes.	 
	 */
	void CPP_PostCouponPurchaseFailImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, const FBeamAuthToken& AuthToken, FBeamConnectivity& ConnectivityStatus, UPostCouponPurchaseFailRequest* RequestData,
	                   const FOnPostCouponPurchaseFailFullResponse& Handler) const;
		
	/**
	 * @brief Private implementation for requests that require authentication that all overloaded BP UFunctions call.	  
	 */
	void BP_PostSteamPurchaseBeginImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, const FBeamAuthToken& AuthToken, FBeamConnectivity& ConnectivityStatus, UPostSteamPurchaseBeginRequest* RequestData,
	                  const FOnPostSteamPurchaseBeginSuccess& OnSuccess, const FOnPostSteamPurchaseBeginError& OnError, const FOnPostSteamPurchaseBeginComplete& OnComplete, int64& OutRequestId) const;
	/**
	 * @brief Overload version for binding lambdas when in C++ land. Prefer the BP version whenever possible, this is here mostly for quick experimentation purposes.	 
	 */
	void CPP_PostSteamPurchaseBeginImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, const FBeamAuthToken& AuthToken, FBeamConnectivity& ConnectivityStatus, UPostSteamPurchaseBeginRequest* RequestData,
	                   const FOnPostSteamPurchaseBeginFullResponse& Handler) const;
		
	/**
	 * @brief Private implementation for requests that require authentication that all overloaded BP UFunctions call.	  
	 */
	void BP_PostSteamPurchaseCancelImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, const FBeamAuthToken& AuthToken, FBeamConnectivity& ConnectivityStatus, UPostSteamPurchaseCancelRequest* RequestData,
	                  const FOnPostSteamPurchaseCancelSuccess& OnSuccess, const FOnPostSteamPurchaseCancelError& OnError, const FOnPostSteamPurchaseCancelComplete& OnComplete, int64& OutRequestId) const;
	/**
	 * @brief Overload version for binding lambdas when in C++ land. Prefer the BP version whenever possible, this is here mostly for quick experimentation purposes.	 
	 */
	void CPP_PostSteamPurchaseCancelImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, const FBeamAuthToken& AuthToken, FBeamConnectivity& ConnectivityStatus, UPostSteamPurchaseCancelRequest* RequestData,
	                   const FOnPostSteamPurchaseCancelFullResponse& Handler) const;
		
	/**
	 * @brief Private implementation for requests that require authentication that all overloaded BP UFunctions call.	  
	 */
	void BP_PostWindowsPurchaseCancelImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, const FBeamAuthToken& AuthToken, FBeamConnectivity& ConnectivityStatus, UPostWindowsPurchaseCancelRequest* RequestData,
	                  const FOnPostWindowsPurchaseCancelSuccess& OnSuccess, const FOnPostWindowsPurchaseCancelError& OnError, const FOnPostWindowsPurchaseCancelComplete& OnComplete, int64& OutRequestId) const;
	/**
	 * @brief Overload version for binding lambdas when in C++ land. Prefer the BP version whenever possible, this is here mostly for quick experimentation purposes.	 
	 */
	void CPP_PostWindowsPurchaseCancelImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, const FBeamAuthToken& AuthToken, FBeamConnectivity& ConnectivityStatus, UPostWindowsPurchaseCancelRequest* RequestData,
	                   const FOnPostWindowsPurchaseCancelFullResponse& Handler) const;
		
	/**
	 * @brief Private implementation for requests that require authentication that all overloaded BP UFunctions call.	  
	 */
	void BP_PostWindowsPurchaseFailImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, const FBeamAuthToken& AuthToken, FBeamConnectivity& ConnectivityStatus, UPostWindowsPurchaseFailRequest* RequestData,
	                  const FOnPostWindowsPurchaseFailSuccess& OnSuccess, const FOnPostWindowsPurchaseFailError& OnError, const FOnPostWindowsPurchaseFailComplete& OnComplete, int64& OutRequestId) const;
	/**
	 * @brief Overload version for binding lambdas when in C++ land. Prefer the BP version whenever possible, this is here mostly for quick experimentation purposes.	 
	 */
	void CPP_PostWindowsPurchaseFailImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, const FBeamAuthToken& AuthToken, FBeamConnectivity& ConnectivityStatus, UPostWindowsPurchaseFailRequest* RequestData,
	                   const FOnPostWindowsPurchaseFailFullResponse& Handler) const;
		
	/**
	 * @brief Private implementation for requests that require authentication that all overloaded BP UFunctions call.	  
	 */
	void BP_PostItunesPurchaseCancelImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, const FBeamAuthToken& AuthToken, FBeamConnectivity& ConnectivityStatus, UPostItunesPurchaseCancelRequest* RequestData,
	                  const FOnPostItunesPurchaseCancelSuccess& OnSuccess, const FOnPostItunesPurchaseCancelError& OnError, const FOnPostItunesPurchaseCancelComplete& OnComplete, int64& OutRequestId) const;
	/**
	 * @brief Overload version for binding lambdas when in C++ land. Prefer the BP version whenever possible, this is here mostly for quick experimentation purposes.	 
	 */
	void CPP_PostItunesPurchaseCancelImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, const FBeamAuthToken& AuthToken, FBeamConnectivity& ConnectivityStatus, UPostItunesPurchaseCancelRequest* RequestData,
	                   const FOnPostItunesPurchaseCancelFullResponse& Handler) const;

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
	 */
	void CPP_PostWindowsPurchaseTrack(UPostWindowsPurchaseTrackRequest* Request, const FOnPostWindowsPurchaseTrackFullResponse& Handler) const;

		
	/**
	 * @brief Makes a request to the Get /basic/payments/audits endpoint of the Payments Service.
	 *
	 * PREFER THE UFUNCTION OVERLOAD AS OPPOSED TO THIS. THIS MAINLY EXISTS TO ALLOW LAMBDA BINDING THE HANDLER.
	 * (Dynamic delegates do not allow for that so... we autogen this one to make experimenting in CPP a bit faster and for whenever you need to capture variables).
	 * 
	 * @param Request The Request UObject. All (de)serialized data the request data creates is tied to the lifecycle of this object.
	 * @param Handler A callback that defines how to handle success, error and completion. 
	 */
	void CPP_GetAudits(UGetAuditsRequest* Request, const FOnGetAuditsFullResponse& Handler) const;

		
	/**
	 * @brief Makes a request to the Post /basic/payments/windows/purchase/complete endpoint of the Payments Service.
	 *
	 * PREFER THE UFUNCTION OVERLOAD AS OPPOSED TO THIS. THIS MAINLY EXISTS TO ALLOW LAMBDA BINDING THE HANDLER.
	 * (Dynamic delegates do not allow for that so... we autogen this one to make experimenting in CPP a bit faster and for whenever you need to capture variables).
	 * 
	 * @param Request The Request UObject. All (de)serialized data the request data creates is tied to the lifecycle of this object.
	 * @param Handler A callback that defines how to handle success, error and completion. 
	 */
	void CPP_PostWindowsPurchaseComplete(UPostWindowsPurchaseCompleteRequest* Request, const FOnPostWindowsPurchaseCompleteFullResponse& Handler) const;

		
	/**
	 * @brief Makes a request to the Get /basic/payments/facebook/update endpoint of the Payments Service.
	 *
	 * PREFER THE UFUNCTION OVERLOAD AS OPPOSED TO THIS. THIS MAINLY EXISTS TO ALLOW LAMBDA BINDING THE HANDLER.
	 * (Dynamic delegates do not allow for that so... we autogen this one to make experimenting in CPP a bit faster and for whenever you need to capture variables).
	 * 
	 * @param Request The Request UObject. All (de)serialized data the request data creates is tied to the lifecycle of this object.
	 * @param Handler A callback that defines how to handle success, error and completion. 
	 */
	void CPP_GetFacebookUpdate(UGetFacebookUpdateRequest* Request, const FOnGetFacebookUpdateFullResponse& Handler) const;

		
	/**
	 * @brief Makes a request to the Post /basic/payments/facebook/update endpoint of the Payments Service.
	 *
	 * PREFER THE UFUNCTION OVERLOAD AS OPPOSED TO THIS. THIS MAINLY EXISTS TO ALLOW LAMBDA BINDING THE HANDLER.
	 * (Dynamic delegates do not allow for that so... we autogen this one to make experimenting in CPP a bit faster and for whenever you need to capture variables).
	 * 
	 * @param Request The Request UObject. All (de)serialized data the request data creates is tied to the lifecycle of this object.
	 * @param Handler A callback that defines how to handle success, error and completion. 
	 */
	void CPP_PostFacebookUpdate(UPostFacebookUpdateRequest* Request, const FOnPostFacebookUpdateFullResponse& Handler) const;

		
	/**
	 * @brief Makes a request to the Post /basic/payments/facebook/purchase/complete endpoint of the Payments Service.
	 *
	 * PREFER THE UFUNCTION OVERLOAD AS OPPOSED TO THIS. THIS MAINLY EXISTS TO ALLOW LAMBDA BINDING THE HANDLER.
	 * (Dynamic delegates do not allow for that so... we autogen this one to make experimenting in CPP a bit faster and for whenever you need to capture variables).
	 * 
	 * @param Request The Request UObject. All (de)serialized data the request data creates is tied to the lifecycle of this object.
	 * @param Handler A callback that defines how to handle success, error and completion. 
	 */
	void CPP_PostFacebookPurchaseComplete(UPostFacebookPurchaseCompleteRequest* Request, const FOnPostFacebookPurchaseCompleteFullResponse& Handler) const;

		
	/**
	 * @brief Makes a request to the Post /basic/payments/test/purchase/complete endpoint of the Payments Service.
	 *
	 * PREFER THE UFUNCTION OVERLOAD AS OPPOSED TO THIS. THIS MAINLY EXISTS TO ALLOW LAMBDA BINDING THE HANDLER.
	 * (Dynamic delegates do not allow for that so... we autogen this one to make experimenting in CPP a bit faster and for whenever you need to capture variables).
	 * 
	 * @param Request The Request UObject. All (de)serialized data the request data creates is tied to the lifecycle of this object.
	 * @param Handler A callback that defines how to handle success, error and completion. 
	 */
	void CPP_PostTestPurchaseComplete(UPostTestPurchaseCompleteRequest* Request, const FOnPostTestPurchaseCompleteFullResponse& Handler) const;

		
	/**
	 * @brief Makes a request to the Get /basic/payments/itunes/product endpoint of the Payments Service.
	 *
	 * PREFER THE UFUNCTION OVERLOAD AS OPPOSED TO THIS. THIS MAINLY EXISTS TO ALLOW LAMBDA BINDING THE HANDLER.
	 * (Dynamic delegates do not allow for that so... we autogen this one to make experimenting in CPP a bit faster and for whenever you need to capture variables).
	 * 
	 * @param Request The Request UObject. All (de)serialized data the request data creates is tied to the lifecycle of this object.
	 * @param Handler A callback that defines how to handle success, error and completion. 
	 */
	void CPP_GetItunesProduct(UGetItunesProductRequest* Request, const FOnGetItunesProductFullResponse& Handler) const;

		
	/**
	 * @brief Makes a request to the Post /basic/payments/googleplay/purchase/complete endpoint of the Payments Service.
	 *
	 * PREFER THE UFUNCTION OVERLOAD AS OPPOSED TO THIS. THIS MAINLY EXISTS TO ALLOW LAMBDA BINDING THE HANDLER.
	 * (Dynamic delegates do not allow for that so... we autogen this one to make experimenting in CPP a bit faster and for whenever you need to capture variables).
	 * 
	 * @param Request The Request UObject. All (de)serialized data the request data creates is tied to the lifecycle of this object.
	 * @param Handler A callback that defines how to handle success, error and completion. 
	 */
	void CPP_PostGoogleplayPurchaseComplete(UPostGoogleplayPurchaseCompleteRequest* Request, const FOnPostGoogleplayPurchaseCompleteFullResponse& Handler) const;

		
	/**
	 * @brief Makes a request to the Post /basic/payments/test/purchase/track endpoint of the Payments Service.
	 *
	 * PREFER THE UFUNCTION OVERLOAD AS OPPOSED TO THIS. THIS MAINLY EXISTS TO ALLOW LAMBDA BINDING THE HANDLER.
	 * (Dynamic delegates do not allow for that so... we autogen this one to make experimenting in CPP a bit faster and for whenever you need to capture variables).
	 * 
	 * @param Request The Request UObject. All (de)serialized data the request data creates is tied to the lifecycle of this object.
	 * @param Handler A callback that defines how to handle success, error and completion. 
	 */
	void CPP_PostTestPurchaseTrack(UPostTestPurchaseTrackRequest* Request, const FOnPostTestPurchaseTrackFullResponse& Handler) const;

		
	/**
	 * @brief Makes a request to the Post /basic/payments/googleplay/purchase/verify endpoint of the Payments Service.
	 *
	 * PREFER THE UFUNCTION OVERLOAD AS OPPOSED TO THIS. THIS MAINLY EXISTS TO ALLOW LAMBDA BINDING THE HANDLER.
	 * (Dynamic delegates do not allow for that so... we autogen this one to make experimenting in CPP a bit faster and for whenever you need to capture variables).
	 * 
	 * @param Request The Request UObject. All (de)serialized data the request data creates is tied to the lifecycle of this object.
	 * @param Handler A callback that defines how to handle success, error and completion. 
	 */
	void CPP_PostGoogleplayPurchaseVerify(UPostGoogleplayPurchaseVerifyRequest* Request, const FOnPostGoogleplayPurchaseVerifyFullResponse& Handler) const;

		
	/**
	 * @brief Makes a request to the Post /basic/payments/coupon/purchase/track endpoint of the Payments Service.
	 *
	 * PREFER THE UFUNCTION OVERLOAD AS OPPOSED TO THIS. THIS MAINLY EXISTS TO ALLOW LAMBDA BINDING THE HANDLER.
	 * (Dynamic delegates do not allow for that so... we autogen this one to make experimenting in CPP a bit faster and for whenever you need to capture variables).
	 * 
	 * @param Request The Request UObject. All (de)serialized data the request data creates is tied to the lifecycle of this object.
	 * @param Handler A callback that defines how to handle success, error and completion. 
	 */
	void CPP_PostCouponPurchaseTrack(UPostCouponPurchaseTrackRequest* Request, const FOnPostCouponPurchaseTrackFullResponse& Handler) const;

		
	/**
	 * @brief Makes a request to the Post /basic/payments/steam/purchase/complete endpoint of the Payments Service.
	 *
	 * PREFER THE UFUNCTION OVERLOAD AS OPPOSED TO THIS. THIS MAINLY EXISTS TO ALLOW LAMBDA BINDING THE HANDLER.
	 * (Dynamic delegates do not allow for that so... we autogen this one to make experimenting in CPP a bit faster and for whenever you need to capture variables).
	 * 
	 * @param Request The Request UObject. All (de)serialized data the request data creates is tied to the lifecycle of this object.
	 * @param Handler A callback that defines how to handle success, error and completion. 
	 */
	void CPP_PostSteamPurchaseComplete(UPostSteamPurchaseCompleteRequest* Request, const FOnPostSteamPurchaseCompleteFullResponse& Handler) const;

		
	/**
	 * @brief Makes a request to the Post /basic/payments/facebook/purchase/track endpoint of the Payments Service.
	 *
	 * PREFER THE UFUNCTION OVERLOAD AS OPPOSED TO THIS. THIS MAINLY EXISTS TO ALLOW LAMBDA BINDING THE HANDLER.
	 * (Dynamic delegates do not allow for that so... we autogen this one to make experimenting in CPP a bit faster and for whenever you need to capture variables).
	 * 
	 * @param Request The Request UObject. All (de)serialized data the request data creates is tied to the lifecycle of this object.
	 * @param Handler A callback that defines how to handle success, error and completion. 
	 */
	void CPP_PostFacebookPurchaseTrack(UPostFacebookPurchaseTrackRequest* Request, const FOnPostFacebookPurchaseTrackFullResponse& Handler) const;

		
	/**
	 * @brief Makes a request to the Post /basic/payments/test/purchase/verify endpoint of the Payments Service.
	 *
	 * PREFER THE UFUNCTION OVERLOAD AS OPPOSED TO THIS. THIS MAINLY EXISTS TO ALLOW LAMBDA BINDING THE HANDLER.
	 * (Dynamic delegates do not allow for that so... we autogen this one to make experimenting in CPP a bit faster and for whenever you need to capture variables).
	 * 
	 * @param Request The Request UObject. All (de)serialized data the request data creates is tied to the lifecycle of this object.
	 * @param Handler A callback that defines how to handle success, error and completion. 
	 */
	void CPP_PostTestPurchaseVerify(UPostTestPurchaseVerifyRequest* Request, const FOnPostTestPurchaseVerifyFullResponse& Handler) const;

		
	/**
	 * @brief Makes a request to the Post /basic/payments/googleplay/purchase/track endpoint of the Payments Service.
	 *
	 * PREFER THE UFUNCTION OVERLOAD AS OPPOSED TO THIS. THIS MAINLY EXISTS TO ALLOW LAMBDA BINDING THE HANDLER.
	 * (Dynamic delegates do not allow for that so... we autogen this one to make experimenting in CPP a bit faster and for whenever you need to capture variables).
	 * 
	 * @param Request The Request UObject. All (de)serialized data the request data creates is tied to the lifecycle of this object.
	 * @param Handler A callback that defines how to handle success, error and completion. 
	 */
	void CPP_PostGoogleplayPurchaseTrack(UPostGoogleplayPurchaseTrackRequest* Request, const FOnPostGoogleplayPurchaseTrackFullResponse& Handler) const;

		
	/**
	 * @brief Makes a request to the Get /basic/payments/steam/prices endpoint of the Payments Service.
	 *
	 * PREFER THE UFUNCTION OVERLOAD AS OPPOSED TO THIS. THIS MAINLY EXISTS TO ALLOW LAMBDA BINDING THE HANDLER.
	 * (Dynamic delegates do not allow for that so... we autogen this one to make experimenting in CPP a bit faster and for whenever you need to capture variables).
	 * 
	 * @param Request The Request UObject. All (de)serialized data the request data creates is tied to the lifecycle of this object.
	 * @param Handler A callback that defines how to handle success, error and completion. 
	 */
	void CPP_GetSteamPrices(UGetSteamPricesRequest* Request, const FOnGetSteamPricesFullResponse& Handler) const;

		
	/**
	 * @brief Makes a request to the Post /basic/payments/windows/purchase/verify endpoint of the Payments Service.
	 *
	 * PREFER THE UFUNCTION OVERLOAD AS OPPOSED TO THIS. THIS MAINLY EXISTS TO ALLOW LAMBDA BINDING THE HANDLER.
	 * (Dynamic delegates do not allow for that so... we autogen this one to make experimenting in CPP a bit faster and for whenever you need to capture variables).
	 * 
	 * @param Request The Request UObject. All (de)serialized data the request data creates is tied to the lifecycle of this object.
	 * @param Handler A callback that defines how to handle success, error and completion. 
	 */
	void CPP_PostWindowsPurchaseVerify(UPostWindowsPurchaseVerifyRequest* Request, const FOnPostWindowsPurchaseVerifyFullResponse& Handler) const;

		
	/**
	 * @brief Makes a request to the Post /basic/payments/itunes/purchase/verify endpoint of the Payments Service.
	 *
	 * PREFER THE UFUNCTION OVERLOAD AS OPPOSED TO THIS. THIS MAINLY EXISTS TO ALLOW LAMBDA BINDING THE HANDLER.
	 * (Dynamic delegates do not allow for that so... we autogen this one to make experimenting in CPP a bit faster and for whenever you need to capture variables).
	 * 
	 * @param Request The Request UObject. All (de)serialized data the request data creates is tied to the lifecycle of this object.
	 * @param Handler A callback that defines how to handle success, error and completion. 
	 */
	void CPP_PostItunesPurchaseVerify(UPostItunesPurchaseVerifyRequest* Request, const FOnPostItunesPurchaseVerifyFullResponse& Handler) const;

		
	/**
	 * @brief Makes a request to the Post /basic/payments/itunes/purchase/complete endpoint of the Payments Service.
	 *
	 * PREFER THE UFUNCTION OVERLOAD AS OPPOSED TO THIS. THIS MAINLY EXISTS TO ALLOW LAMBDA BINDING THE HANDLER.
	 * (Dynamic delegates do not allow for that so... we autogen this one to make experimenting in CPP a bit faster and for whenever you need to capture variables).
	 * 
	 * @param Request The Request UObject. All (de)serialized data the request data creates is tied to the lifecycle of this object.
	 * @param Handler A callback that defines how to handle success, error and completion. 
	 */
	void CPP_PostItunesPurchaseComplete(UPostItunesPurchaseCompleteRequest* Request, const FOnPostItunesPurchaseCompleteFullResponse& Handler) const;

		
	/**
	 * @brief Makes a request to the Post /basic/payments/facebook/purchase/verify endpoint of the Payments Service.
	 *
	 * PREFER THE UFUNCTION OVERLOAD AS OPPOSED TO THIS. THIS MAINLY EXISTS TO ALLOW LAMBDA BINDING THE HANDLER.
	 * (Dynamic delegates do not allow for that so... we autogen this one to make experimenting in CPP a bit faster and for whenever you need to capture variables).
	 * 
	 * @param Request The Request UObject. All (de)serialized data the request data creates is tied to the lifecycle of this object.
	 * @param Handler A callback that defines how to handle success, error and completion. 
	 */
	void CPP_PostFacebookPurchaseVerify(UPostFacebookPurchaseVerifyRequest* Request, const FOnPostFacebookPurchaseVerifyFullResponse& Handler) const;

		
	/**
	 * @brief Makes a request to the Post /basic/payments/steam/purchase/track endpoint of the Payments Service.
	 *
	 * PREFER THE UFUNCTION OVERLOAD AS OPPOSED TO THIS. THIS MAINLY EXISTS TO ALLOW LAMBDA BINDING THE HANDLER.
	 * (Dynamic delegates do not allow for that so... we autogen this one to make experimenting in CPP a bit faster and for whenever you need to capture variables).
	 * 
	 * @param Request The Request UObject. All (de)serialized data the request data creates is tied to the lifecycle of this object.
	 * @param Handler A callback that defines how to handle success, error and completion. 
	 */
	void CPP_PostSteamPurchaseTrack(UPostSteamPurchaseTrackRequest* Request, const FOnPostSteamPurchaseTrackFullResponse& Handler) const;

		
	/**
	 * @brief Makes a request to the Post /basic/payments/coupon/purchase/verify endpoint of the Payments Service.
	 *
	 * PREFER THE UFUNCTION OVERLOAD AS OPPOSED TO THIS. THIS MAINLY EXISTS TO ALLOW LAMBDA BINDING THE HANDLER.
	 * (Dynamic delegates do not allow for that so... we autogen this one to make experimenting in CPP a bit faster and for whenever you need to capture variables).
	 * 
	 * @param Request The Request UObject. All (de)serialized data the request data creates is tied to the lifecycle of this object.
	 * @param Handler A callback that defines how to handle success, error and completion. 
	 */
	void CPP_PostCouponPurchaseVerify(UPostCouponPurchaseVerifyRequest* Request, const FOnPostCouponPurchaseVerifyFullResponse& Handler) const;

		
	/**
	 * @brief Makes a request to the Get /basic/payments/windows/product endpoint of the Payments Service.
	 *
	 * PREFER THE UFUNCTION OVERLOAD AS OPPOSED TO THIS. THIS MAINLY EXISTS TO ALLOW LAMBDA BINDING THE HANDLER.
	 * (Dynamic delegates do not allow for that so... we autogen this one to make experimenting in CPP a bit faster and for whenever you need to capture variables).
	 * 
	 * @param Request The Request UObject. All (de)serialized data the request data creates is tied to the lifecycle of this object.
	 * @param Handler A callback that defines how to handle success, error and completion. 
	 */
	void CPP_GetWindowsProduct(UGetWindowsProductRequest* Request, const FOnGetWindowsProductFullResponse& Handler) const;

		
	/**
	 * @brief Makes a request to the Get /basic/payments/facebook/product endpoint of the Payments Service.
	 *
	 * PREFER THE UFUNCTION OVERLOAD AS OPPOSED TO THIS. THIS MAINLY EXISTS TO ALLOW LAMBDA BINDING THE HANDLER.
	 * (Dynamic delegates do not allow for that so... we autogen this one to make experimenting in CPP a bit faster and for whenever you need to capture variables).
	 * 
	 * @param Request The Request UObject. All (de)serialized data the request data creates is tied to the lifecycle of this object.
	 * @param Handler A callback that defines how to handle success, error and completion. 
	 */
	void CPP_GetFacebookProduct(UGetFacebookProductRequest* Request, const FOnGetFacebookProductFullResponse& Handler) const;

		
	/**
	 * @brief Makes a request to the Get /basic/payments/coupon/product endpoint of the Payments Service.
	 *
	 * PREFER THE UFUNCTION OVERLOAD AS OPPOSED TO THIS. THIS MAINLY EXISTS TO ALLOW LAMBDA BINDING THE HANDLER.
	 * (Dynamic delegates do not allow for that so... we autogen this one to make experimenting in CPP a bit faster and for whenever you need to capture variables).
	 * 
	 * @param Request The Request UObject. All (de)serialized data the request data creates is tied to the lifecycle of this object.
	 * @param Handler A callback that defines how to handle success, error and completion. 
	 */
	void CPP_GetCouponProduct(UGetCouponProductRequest* Request, const FOnGetCouponProductFullResponse& Handler) const;

		
	/**
	 * @brief Makes a request to the Get /basic/payments/steam/products endpoint of the Payments Service.
	 *
	 * PREFER THE UFUNCTION OVERLOAD AS OPPOSED TO THIS. THIS MAINLY EXISTS TO ALLOW LAMBDA BINDING THE HANDLER.
	 * (Dynamic delegates do not allow for that so... we autogen this one to make experimenting in CPP a bit faster and for whenever you need to capture variables).
	 * 
	 * @param Request The Request UObject. All (de)serialized data the request data creates is tied to the lifecycle of this object.
	 * @param Handler A callback that defines how to handle success, error and completion. 
	 */
	void CPP_GetSteamProducts(UGetSteamProductsRequest* Request, const FOnGetSteamProductsFullResponse& Handler) const;

		
	/**
	 * @brief Makes a request to the Post /basic/payments/steam/auth endpoint of the Payments Service.
	 *
	 * PREFER THE UFUNCTION OVERLOAD AS OPPOSED TO THIS. THIS MAINLY EXISTS TO ALLOW LAMBDA BINDING THE HANDLER.
	 * (Dynamic delegates do not allow for that so... we autogen this one to make experimenting in CPP a bit faster and for whenever you need to capture variables).
	 * 
	 * @param Request The Request UObject. All (de)serialized data the request data creates is tied to the lifecycle of this object.
	 * @param Handler A callback that defines how to handle success, error and completion. 
	 */
	void CPP_PostSteamAuth(UPostSteamAuthRequest* Request, const FOnPostSteamAuthFullResponse& Handler) const;

		
	/**
	 * @brief Makes a request to the Get /basic/payments/steam/product endpoint of the Payments Service.
	 *
	 * PREFER THE UFUNCTION OVERLOAD AS OPPOSED TO THIS. THIS MAINLY EXISTS TO ALLOW LAMBDA BINDING THE HANDLER.
	 * (Dynamic delegates do not allow for that so... we autogen this one to make experimenting in CPP a bit faster and for whenever you need to capture variables).
	 * 
	 * @param Request The Request UObject. All (de)serialized data the request data creates is tied to the lifecycle of this object.
	 * @param Handler A callback that defines how to handle success, error and completion. 
	 */
	void CPP_GetSteamProduct(UGetSteamProductRequest* Request, const FOnGetSteamProductFullResponse& Handler) const;

		
	/**
	 * @brief Makes a request to the Post /basic/payments/coupon/purchase/complete endpoint of the Payments Service.
	 *
	 * PREFER THE UFUNCTION OVERLOAD AS OPPOSED TO THIS. THIS MAINLY EXISTS TO ALLOW LAMBDA BINDING THE HANDLER.
	 * (Dynamic delegates do not allow for that so... we autogen this one to make experimenting in CPP a bit faster and for whenever you need to capture variables).
	 * 
	 * @param Request The Request UObject. All (de)serialized data the request data creates is tied to the lifecycle of this object.
	 * @param Handler A callback that defines how to handle success, error and completion. 
	 */
	void CPP_PostCouponPurchaseComplete(UPostCouponPurchaseCompleteRequest* Request, const FOnPostCouponPurchaseCompleteFullResponse& Handler) const;

		
	/**
	 * @brief Makes a request to the Get /basic/payments/googleplay/product endpoint of the Payments Service.
	 *
	 * PREFER THE UFUNCTION OVERLOAD AS OPPOSED TO THIS. THIS MAINLY EXISTS TO ALLOW LAMBDA BINDING THE HANDLER.
	 * (Dynamic delegates do not allow for that so... we autogen this one to make experimenting in CPP a bit faster and for whenever you need to capture variables).
	 * 
	 * @param Request The Request UObject. All (de)serialized data the request data creates is tied to the lifecycle of this object.
	 * @param Handler A callback that defines how to handle success, error and completion. 
	 */
	void CPP_GetGoogleplayProduct(UGetGoogleplayProductRequest* Request, const FOnGetGoogleplayProductFullResponse& Handler) const;

		
	/**
	 * @brief Makes a request to the Get /basic/payments/test/product endpoint of the Payments Service.
	 *
	 * PREFER THE UFUNCTION OVERLOAD AS OPPOSED TO THIS. THIS MAINLY EXISTS TO ALLOW LAMBDA BINDING THE HANDLER.
	 * (Dynamic delegates do not allow for that so... we autogen this one to make experimenting in CPP a bit faster and for whenever you need to capture variables).
	 * 
	 * @param Request The Request UObject. All (de)serialized data the request data creates is tied to the lifecycle of this object.
	 * @param Handler A callback that defines how to handle success, error and completion. 
	 */
	void CPP_GetTestProduct(UGetTestProductRequest* Request, const FOnGetTestProductFullResponse& Handler) const;

		
	/**
	 * @brief Makes a request to the Post /basic/payments/steam/purchase/verify endpoint of the Payments Service.
	 *
	 * PREFER THE UFUNCTION OVERLOAD AS OPPOSED TO THIS. THIS MAINLY EXISTS TO ALLOW LAMBDA BINDING THE HANDLER.
	 * (Dynamic delegates do not allow for that so... we autogen this one to make experimenting in CPP a bit faster and for whenever you need to capture variables).
	 * 
	 * @param Request The Request UObject. All (de)serialized data the request data creates is tied to the lifecycle of this object.
	 * @param Handler A callback that defines how to handle success, error and completion. 
	 */
	void CPP_PostSteamPurchaseVerify(UPostSteamPurchaseVerifyRequest* Request, const FOnPostSteamPurchaseVerifyFullResponse& Handler) const;

		
	/**
	 * @brief Makes a request to the Post /basic/payments/itunes/purchase/track endpoint of the Payments Service.
	 *
	 * PREFER THE UFUNCTION OVERLOAD AS OPPOSED TO THIS. THIS MAINLY EXISTS TO ALLOW LAMBDA BINDING THE HANDLER.
	 * (Dynamic delegates do not allow for that so... we autogen this one to make experimenting in CPP a bit faster and for whenever you need to capture variables).
	 * 
	 * @param Request The Request UObject. All (de)serialized data the request data creates is tied to the lifecycle of this object.
	 * @param Handler A callback that defines how to handle success, error and completion. 
	 */
	void CPP_PostItunesPurchaseTrack(UPostItunesPurchaseTrackRequest* Request, const FOnPostItunesPurchaseTrackFullResponse& Handler) const;

		
	/**
	 * @brief Makes a request to the Get /object/payments/{objectId}/ endpoint of the Payments Service.
	 *
	 * PREFER THE UFUNCTION OVERLOAD AS OPPOSED TO THIS. THIS MAINLY EXISTS TO ALLOW LAMBDA BINDING THE HANDLER.
	 * (Dynamic delegates do not allow for that so... we autogen this one to make experimenting in CPP a bit faster and for whenever you need to capture variables).
	 * 
	 * @param Request The Request UObject. All (de)serialized data the request data creates is tied to the lifecycle of this object.
	 * @param Handler A callback that defines how to handle success, error and completion. 
	 */
	void CPP_GetPayments(UGetPaymentsRequest* Request, const FOnGetPaymentsFullResponse& Handler) const;


	
	/**
	 * @brief Makes an authenticated request to the Post /basic/payments/test/purchase/begin endpoint of the Payments Service.
	 *
	 * PREFER THE UFUNCTION OVERLOAD AS OPPOSED TO THIS. THIS MAINLY EXISTS TO ALLOW LAMBDA BINDING THE HANDLER.
	 * (Dynamic delegates do not allow for that so... we autogen this one to make experimenting in CPP a bit faster).
	 * 
	 * @param UserSlot The Authenticated User Slot that is making this request.
	 * @param Request The Request UObject. All (de)serialized data the request data creates is tied to the lifecycle of this object.
	 * @param Handler A callback that defines how to handle success, error and completion. 
	 */
	void CPP_PostTestPurchaseBegin(const FUserSlot& UserSlot, UPostTestPurchaseBeginRequest* Request, const FOnPostTestPurchaseBeginFullResponse& Handler) const;

		
	/**
	 * @brief Makes an authenticated request to the Post /basic/payments/steam/purchase/fail endpoint of the Payments Service.
	 *
	 * PREFER THE UFUNCTION OVERLOAD AS OPPOSED TO THIS. THIS MAINLY EXISTS TO ALLOW LAMBDA BINDING THE HANDLER.
	 * (Dynamic delegates do not allow for that so... we autogen this one to make experimenting in CPP a bit faster).
	 * 
	 * @param UserSlot The Authenticated User Slot that is making this request.
	 * @param Request The Request UObject. All (de)serialized data the request data creates is tied to the lifecycle of this object.
	 * @param Handler A callback that defines how to handle success, error and completion. 
	 */
	void CPP_PostSteamPurchaseFail(const FUserSlot& UserSlot, UPostSteamPurchaseFailRequest* Request, const FOnPostSteamPurchaseFailFullResponse& Handler) const;

		
	/**
	 * @brief Makes an authenticated request to the Post /basic/payments/facebook/purchase/fail endpoint of the Payments Service.
	 *
	 * PREFER THE UFUNCTION OVERLOAD AS OPPOSED TO THIS. THIS MAINLY EXISTS TO ALLOW LAMBDA BINDING THE HANDLER.
	 * (Dynamic delegates do not allow for that so... we autogen this one to make experimenting in CPP a bit faster).
	 * 
	 * @param UserSlot The Authenticated User Slot that is making this request.
	 * @param Request The Request UObject. All (de)serialized data the request data creates is tied to the lifecycle of this object.
	 * @param Handler A callback that defines how to handle success, error and completion. 
	 */
	void CPP_PostFacebookPurchaseFail(const FUserSlot& UserSlot, UPostFacebookPurchaseFailRequest* Request, const FOnPostFacebookPurchaseFailFullResponse& Handler) const;

		
	/**
	 * @brief Makes an authenticated request to the Post /basic/payments/googleplay/purchase/begin endpoint of the Payments Service.
	 *
	 * PREFER THE UFUNCTION OVERLOAD AS OPPOSED TO THIS. THIS MAINLY EXISTS TO ALLOW LAMBDA BINDING THE HANDLER.
	 * (Dynamic delegates do not allow for that so... we autogen this one to make experimenting in CPP a bit faster).
	 * 
	 * @param UserSlot The Authenticated User Slot that is making this request.
	 * @param Request The Request UObject. All (de)serialized data the request data creates is tied to the lifecycle of this object.
	 * @param Handler A callback that defines how to handle success, error and completion. 
	 */
	void CPP_PostGoogleplayPurchaseBegin(const FUserSlot& UserSlot, UPostGoogleplayPurchaseBeginRequest* Request, const FOnPostGoogleplayPurchaseBeginFullResponse& Handler) const;

		
	/**
	 * @brief Makes an authenticated request to the Post /basic/payments/itunes/purchase/begin endpoint of the Payments Service.
	 *
	 * PREFER THE UFUNCTION OVERLOAD AS OPPOSED TO THIS. THIS MAINLY EXISTS TO ALLOW LAMBDA BINDING THE HANDLER.
	 * (Dynamic delegates do not allow for that so... we autogen this one to make experimenting in CPP a bit faster).
	 * 
	 * @param UserSlot The Authenticated User Slot that is making this request.
	 * @param Request The Request UObject. All (de)serialized data the request data creates is tied to the lifecycle of this object.
	 * @param Handler A callback that defines how to handle success, error and completion. 
	 */
	void CPP_PostItunesPurchaseBegin(const FUserSlot& UserSlot, UPostItunesPurchaseBeginRequest* Request, const FOnPostItunesPurchaseBeginFullResponse& Handler) const;

		
	/**
	 * @brief Makes an authenticated request to the Post /basic/payments/facebook/purchase/cancel endpoint of the Payments Service.
	 *
	 * PREFER THE UFUNCTION OVERLOAD AS OPPOSED TO THIS. THIS MAINLY EXISTS TO ALLOW LAMBDA BINDING THE HANDLER.
	 * (Dynamic delegates do not allow for that so... we autogen this one to make experimenting in CPP a bit faster).
	 * 
	 * @param UserSlot The Authenticated User Slot that is making this request.
	 * @param Request The Request UObject. All (de)serialized data the request data creates is tied to the lifecycle of this object.
	 * @param Handler A callback that defines how to handle success, error and completion. 
	 */
	void CPP_PostFacebookPurchaseCancel(const FUserSlot& UserSlot, UPostFacebookPurchaseCancelRequest* Request, const FOnPostFacebookPurchaseCancelFullResponse& Handler) const;

		
	/**
	 * @brief Makes an authenticated request to the Post /basic/payments/itunes/purchase/fail endpoint of the Payments Service.
	 *
	 * PREFER THE UFUNCTION OVERLOAD AS OPPOSED TO THIS. THIS MAINLY EXISTS TO ALLOW LAMBDA BINDING THE HANDLER.
	 * (Dynamic delegates do not allow for that so... we autogen this one to make experimenting in CPP a bit faster).
	 * 
	 * @param UserSlot The Authenticated User Slot that is making this request.
	 * @param Request The Request UObject. All (de)serialized data the request data creates is tied to the lifecycle of this object.
	 * @param Handler A callback that defines how to handle success, error and completion. 
	 */
	void CPP_PostItunesPurchaseFail(const FUserSlot& UserSlot, UPostItunesPurchaseFailRequest* Request, const FOnPostItunesPurchaseFailFullResponse& Handler) const;

		
	/**
	 * @brief Makes an authenticated request to the Post /basic/payments/test/purchase/cancel endpoint of the Payments Service.
	 *
	 * PREFER THE UFUNCTION OVERLOAD AS OPPOSED TO THIS. THIS MAINLY EXISTS TO ALLOW LAMBDA BINDING THE HANDLER.
	 * (Dynamic delegates do not allow for that so... we autogen this one to make experimenting in CPP a bit faster).
	 * 
	 * @param UserSlot The Authenticated User Slot that is making this request.
	 * @param Request The Request UObject. All (de)serialized data the request data creates is tied to the lifecycle of this object.
	 * @param Handler A callback that defines how to handle success, error and completion. 
	 */
	void CPP_PostTestPurchaseCancel(const FUserSlot& UserSlot, UPostTestPurchaseCancelRequest* Request, const FOnPostTestPurchaseCancelFullResponse& Handler) const;

		
	/**
	 * @brief Makes an authenticated request to the Post /basic/payments/test/purchase/fail endpoint of the Payments Service.
	 *
	 * PREFER THE UFUNCTION OVERLOAD AS OPPOSED TO THIS. THIS MAINLY EXISTS TO ALLOW LAMBDA BINDING THE HANDLER.
	 * (Dynamic delegates do not allow for that so... we autogen this one to make experimenting in CPP a bit faster).
	 * 
	 * @param UserSlot The Authenticated User Slot that is making this request.
	 * @param Request The Request UObject. All (de)serialized data the request data creates is tied to the lifecycle of this object.
	 * @param Handler A callback that defines how to handle success, error and completion. 
	 */
	void CPP_PostTestPurchaseFail(const FUserSlot& UserSlot, UPostTestPurchaseFailRequest* Request, const FOnPostTestPurchaseFailFullResponse& Handler) const;

		
	/**
	 * @brief Makes an authenticated request to the Post /basic/payments/coupon/purchase/cancel endpoint of the Payments Service.
	 *
	 * PREFER THE UFUNCTION OVERLOAD AS OPPOSED TO THIS. THIS MAINLY EXISTS TO ALLOW LAMBDA BINDING THE HANDLER.
	 * (Dynamic delegates do not allow for that so... we autogen this one to make experimenting in CPP a bit faster).
	 * 
	 * @param UserSlot The Authenticated User Slot that is making this request.
	 * @param Request The Request UObject. All (de)serialized data the request data creates is tied to the lifecycle of this object.
	 * @param Handler A callback that defines how to handle success, error and completion. 
	 */
	void CPP_PostCouponPurchaseCancel(const FUserSlot& UserSlot, UPostCouponPurchaseCancelRequest* Request, const FOnPostCouponPurchaseCancelFullResponse& Handler) const;

		
	/**
	 * @brief Makes an authenticated request to the Post /basic/payments/coupon/purchase/begin endpoint of the Payments Service.
	 *
	 * PREFER THE UFUNCTION OVERLOAD AS OPPOSED TO THIS. THIS MAINLY EXISTS TO ALLOW LAMBDA BINDING THE HANDLER.
	 * (Dynamic delegates do not allow for that so... we autogen this one to make experimenting in CPP a bit faster).
	 * 
	 * @param UserSlot The Authenticated User Slot that is making this request.
	 * @param Request The Request UObject. All (de)serialized data the request data creates is tied to the lifecycle of this object.
	 * @param Handler A callback that defines how to handle success, error and completion. 
	 */
	void CPP_PostCouponPurchaseBegin(const FUserSlot& UserSlot, UPostCouponPurchaseBeginRequest* Request, const FOnPostCouponPurchaseBeginFullResponse& Handler) const;

		
	/**
	 * @brief Makes an authenticated request to the Post /basic/payments/facebook/purchase/begin endpoint of the Payments Service.
	 *
	 * PREFER THE UFUNCTION OVERLOAD AS OPPOSED TO THIS. THIS MAINLY EXISTS TO ALLOW LAMBDA BINDING THE HANDLER.
	 * (Dynamic delegates do not allow for that so... we autogen this one to make experimenting in CPP a bit faster).
	 * 
	 * @param UserSlot The Authenticated User Slot that is making this request.
	 * @param Request The Request UObject. All (de)serialized data the request data creates is tied to the lifecycle of this object.
	 * @param Handler A callback that defines how to handle success, error and completion. 
	 */
	void CPP_PostFacebookPurchaseBegin(const FUserSlot& UserSlot, UPostFacebookPurchaseBeginRequest* Request, const FOnPostFacebookPurchaseBeginFullResponse& Handler) const;

		
	/**
	 * @brief Makes an authenticated request to the Get /basic/payments/steam/order endpoint of the Payments Service.
	 *
	 * PREFER THE UFUNCTION OVERLOAD AS OPPOSED TO THIS. THIS MAINLY EXISTS TO ALLOW LAMBDA BINDING THE HANDLER.
	 * (Dynamic delegates do not allow for that so... we autogen this one to make experimenting in CPP a bit faster).
	 * 
	 * @param UserSlot The Authenticated User Slot that is making this request.
	 * @param Request The Request UObject. All (de)serialized data the request data creates is tied to the lifecycle of this object.
	 * @param Handler A callback that defines how to handle success, error and completion. 
	 */
	void CPP_GetSteamOrder(const FUserSlot& UserSlot, UGetSteamOrderRequest* Request, const FOnGetSteamOrderFullResponse& Handler) const;

		
	/**
	 * @brief Makes an authenticated request to the Post /basic/payments/windows/purchase/begin endpoint of the Payments Service.
	 *
	 * PREFER THE UFUNCTION OVERLOAD AS OPPOSED TO THIS. THIS MAINLY EXISTS TO ALLOW LAMBDA BINDING THE HANDLER.
	 * (Dynamic delegates do not allow for that so... we autogen this one to make experimenting in CPP a bit faster).
	 * 
	 * @param UserSlot The Authenticated User Slot that is making this request.
	 * @param Request The Request UObject. All (de)serialized data the request data creates is tied to the lifecycle of this object.
	 * @param Handler A callback that defines how to handle success, error and completion. 
	 */
	void CPP_PostWindowsPurchaseBegin(const FUserSlot& UserSlot, UPostWindowsPurchaseBeginRequest* Request, const FOnPostWindowsPurchaseBeginFullResponse& Handler) const;

		
	/**
	 * @brief Makes an authenticated request to the Post /basic/payments/googleplay/purchase/fail endpoint of the Payments Service.
	 *
	 * PREFER THE UFUNCTION OVERLOAD AS OPPOSED TO THIS. THIS MAINLY EXISTS TO ALLOW LAMBDA BINDING THE HANDLER.
	 * (Dynamic delegates do not allow for that so... we autogen this one to make experimenting in CPP a bit faster).
	 * 
	 * @param UserSlot The Authenticated User Slot that is making this request.
	 * @param Request The Request UObject. All (de)serialized data the request data creates is tied to the lifecycle of this object.
	 * @param Handler A callback that defines how to handle success, error and completion. 
	 */
	void CPP_PostGoogleplayPurchaseFail(const FUserSlot& UserSlot, UPostGoogleplayPurchaseFailRequest* Request, const FOnPostGoogleplayPurchaseFailFullResponse& Handler) const;

		
	/**
	 * @brief Makes an authenticated request to the Post /basic/payments/googleplay/purchase/cancel endpoint of the Payments Service.
	 *
	 * PREFER THE UFUNCTION OVERLOAD AS OPPOSED TO THIS. THIS MAINLY EXISTS TO ALLOW LAMBDA BINDING THE HANDLER.
	 * (Dynamic delegates do not allow for that so... we autogen this one to make experimenting in CPP a bit faster).
	 * 
	 * @param UserSlot The Authenticated User Slot that is making this request.
	 * @param Request The Request UObject. All (de)serialized data the request data creates is tied to the lifecycle of this object.
	 * @param Handler A callback that defines how to handle success, error and completion. 
	 */
	void CPP_PostGoogleplayPurchaseCancel(const FUserSlot& UserSlot, UPostGoogleplayPurchaseCancelRequest* Request, const FOnPostGoogleplayPurchaseCancelFullResponse& Handler) const;

		
	/**
	 * @brief Makes an authenticated request to the Post /basic/payments/coupon/purchase/fail endpoint of the Payments Service.
	 *
	 * PREFER THE UFUNCTION OVERLOAD AS OPPOSED TO THIS. THIS MAINLY EXISTS TO ALLOW LAMBDA BINDING THE HANDLER.
	 * (Dynamic delegates do not allow for that so... we autogen this one to make experimenting in CPP a bit faster).
	 * 
	 * @param UserSlot The Authenticated User Slot that is making this request.
	 * @param Request The Request UObject. All (de)serialized data the request data creates is tied to the lifecycle of this object.
	 * @param Handler A callback that defines how to handle success, error and completion. 
	 */
	void CPP_PostCouponPurchaseFail(const FUserSlot& UserSlot, UPostCouponPurchaseFailRequest* Request, const FOnPostCouponPurchaseFailFullResponse& Handler) const;

		
	/**
	 * @brief Makes an authenticated request to the Post /basic/payments/steam/purchase/begin endpoint of the Payments Service.
	 *
	 * PREFER THE UFUNCTION OVERLOAD AS OPPOSED TO THIS. THIS MAINLY EXISTS TO ALLOW LAMBDA BINDING THE HANDLER.
	 * (Dynamic delegates do not allow for that so... we autogen this one to make experimenting in CPP a bit faster).
	 * 
	 * @param UserSlot The Authenticated User Slot that is making this request.
	 * @param Request The Request UObject. All (de)serialized data the request data creates is tied to the lifecycle of this object.
	 * @param Handler A callback that defines how to handle success, error and completion. 
	 */
	void CPP_PostSteamPurchaseBegin(const FUserSlot& UserSlot, UPostSteamPurchaseBeginRequest* Request, const FOnPostSteamPurchaseBeginFullResponse& Handler) const;

		
	/**
	 * @brief Makes an authenticated request to the Post /basic/payments/steam/purchase/cancel endpoint of the Payments Service.
	 *
	 * PREFER THE UFUNCTION OVERLOAD AS OPPOSED TO THIS. THIS MAINLY EXISTS TO ALLOW LAMBDA BINDING THE HANDLER.
	 * (Dynamic delegates do not allow for that so... we autogen this one to make experimenting in CPP a bit faster).
	 * 
	 * @param UserSlot The Authenticated User Slot that is making this request.
	 * @param Request The Request UObject. All (de)serialized data the request data creates is tied to the lifecycle of this object.
	 * @param Handler A callback that defines how to handle success, error and completion. 
	 */
	void CPP_PostSteamPurchaseCancel(const FUserSlot& UserSlot, UPostSteamPurchaseCancelRequest* Request, const FOnPostSteamPurchaseCancelFullResponse& Handler) const;

		
	/**
	 * @brief Makes an authenticated request to the Post /basic/payments/windows/purchase/cancel endpoint of the Payments Service.
	 *
	 * PREFER THE UFUNCTION OVERLOAD AS OPPOSED TO THIS. THIS MAINLY EXISTS TO ALLOW LAMBDA BINDING THE HANDLER.
	 * (Dynamic delegates do not allow for that so... we autogen this one to make experimenting in CPP a bit faster).
	 * 
	 * @param UserSlot The Authenticated User Slot that is making this request.
	 * @param Request The Request UObject. All (de)serialized data the request data creates is tied to the lifecycle of this object.
	 * @param Handler A callback that defines how to handle success, error and completion. 
	 */
	void CPP_PostWindowsPurchaseCancel(const FUserSlot& UserSlot, UPostWindowsPurchaseCancelRequest* Request, const FOnPostWindowsPurchaseCancelFullResponse& Handler) const;

		
	/**
	 * @brief Makes an authenticated request to the Post /basic/payments/windows/purchase/fail endpoint of the Payments Service.
	 *
	 * PREFER THE UFUNCTION OVERLOAD AS OPPOSED TO THIS. THIS MAINLY EXISTS TO ALLOW LAMBDA BINDING THE HANDLER.
	 * (Dynamic delegates do not allow for that so... we autogen this one to make experimenting in CPP a bit faster).
	 * 
	 * @param UserSlot The Authenticated User Slot that is making this request.
	 * @param Request The Request UObject. All (de)serialized data the request data creates is tied to the lifecycle of this object.
	 * @param Handler A callback that defines how to handle success, error and completion. 
	 */
	void CPP_PostWindowsPurchaseFail(const FUserSlot& UserSlot, UPostWindowsPurchaseFailRequest* Request, const FOnPostWindowsPurchaseFailFullResponse& Handler) const;

		
	/**
	 * @brief Makes an authenticated request to the Post /basic/payments/itunes/purchase/cancel endpoint of the Payments Service.
	 *
	 * PREFER THE UFUNCTION OVERLOAD AS OPPOSED TO THIS. THIS MAINLY EXISTS TO ALLOW LAMBDA BINDING THE HANDLER.
	 * (Dynamic delegates do not allow for that so... we autogen this one to make experimenting in CPP a bit faster).
	 * 
	 * @param UserSlot The Authenticated User Slot that is making this request.
	 * @param Request The Request UObject. All (de)serialized data the request data creates is tied to the lifecycle of this object.
	 * @param Handler A callback that defines how to handle success, error and completion. 
	 */
	void CPP_PostItunesPurchaseCancel(const FUserSlot& UserSlot, UPostItunesPurchaseCancelRequest* Request, const FOnPostItunesPurchaseCancelFullResponse& Handler) const;


	
	/**
	 * @brief Makes a request to the Post /basic/payments/windows/purchase/track endpoint of the Payments Service.
	 *
	 * @param Request The Request UObject. All (de)serialized data the request data creates is tied to the lifecycle of this object.
	 * @param OnSuccess What to do if the requests receives a successful response.
	 * @param OnError What to do if the request receives an error response.
	 * @param OnComplete What to after either OnSuccess or OnError have finished executing.
	 * @param OutRequestId The Request Id -- used to query information about the request or to cancel it while it's in flight. 
	 */
	UFUNCTION(BlueprintCallable, Category="Beam|APIs|Payments", meta=(AutoCreateRefTerm="OnSuccess,OnError,OnComplete"))
	void PostWindowsPurchaseTrack(UPostWindowsPurchaseTrackRequest* Request, const FOnPostWindowsPurchaseTrackSuccess& OnSuccess, const FOnPostWindowsPurchaseTrackError& OnError, const FOnPostWindowsPurchaseTrackComplete& OnComplete,
								 int64& OutRequestId);

		
	/**
	 * @brief Makes a request to the Get /basic/payments/audits endpoint of the Payments Service.
	 *
	 * @param Request The Request UObject. All (de)serialized data the request data creates is tied to the lifecycle of this object.
	 * @param OnSuccess What to do if the requests receives a successful response.
	 * @param OnError What to do if the request receives an error response.
	 * @param OnComplete What to after either OnSuccess or OnError have finished executing.
	 * @param OutRequestId The Request Id -- used to query information about the request or to cancel it while it's in flight. 
	 */
	UFUNCTION(BlueprintCallable, Category="Beam|APIs|Payments", meta=(AutoCreateRefTerm="OnSuccess,OnError,OnComplete"))
	void GetAudits(UGetAuditsRequest* Request, const FOnGetAuditsSuccess& OnSuccess, const FOnGetAuditsError& OnError, const FOnGetAuditsComplete& OnComplete,
								 int64& OutRequestId);

		
	/**
	 * @brief Makes a request to the Post /basic/payments/windows/purchase/complete endpoint of the Payments Service.
	 *
	 * @param Request The Request UObject. All (de)serialized data the request data creates is tied to the lifecycle of this object.
	 * @param OnSuccess What to do if the requests receives a successful response.
	 * @param OnError What to do if the request receives an error response.
	 * @param OnComplete What to after either OnSuccess or OnError have finished executing.
	 * @param OutRequestId The Request Id -- used to query information about the request or to cancel it while it's in flight. 
	 */
	UFUNCTION(BlueprintCallable, Category="Beam|APIs|Payments", meta=(AutoCreateRefTerm="OnSuccess,OnError,OnComplete"))
	void PostWindowsPurchaseComplete(UPostWindowsPurchaseCompleteRequest* Request, const FOnPostWindowsPurchaseCompleteSuccess& OnSuccess, const FOnPostWindowsPurchaseCompleteError& OnError, const FOnPostWindowsPurchaseCompleteComplete& OnComplete,
								 int64& OutRequestId);

		
	/**
	 * @brief Makes a request to the Get /basic/payments/facebook/update endpoint of the Payments Service.
	 *
	 * @param Request The Request UObject. All (de)serialized data the request data creates is tied to the lifecycle of this object.
	 * @param OnSuccess What to do if the requests receives a successful response.
	 * @param OnError What to do if the request receives an error response.
	 * @param OnComplete What to after either OnSuccess or OnError have finished executing.
	 * @param OutRequestId The Request Id -- used to query information about the request or to cancel it while it's in flight. 
	 */
	UFUNCTION(BlueprintCallable, Category="Beam|APIs|Payments", meta=(AutoCreateRefTerm="OnSuccess,OnError,OnComplete"))
	void GetFacebookUpdate(UGetFacebookUpdateRequest* Request, const FOnGetFacebookUpdateSuccess& OnSuccess, const FOnGetFacebookUpdateError& OnError, const FOnGetFacebookUpdateComplete& OnComplete,
								 int64& OutRequestId);

		
	/**
	 * @brief Makes a request to the Post /basic/payments/facebook/update endpoint of the Payments Service.
	 *
	 * @param Request The Request UObject. All (de)serialized data the request data creates is tied to the lifecycle of this object.
	 * @param OnSuccess What to do if the requests receives a successful response.
	 * @param OnError What to do if the request receives an error response.
	 * @param OnComplete What to after either OnSuccess or OnError have finished executing.
	 * @param OutRequestId The Request Id -- used to query information about the request or to cancel it while it's in flight. 
	 */
	UFUNCTION(BlueprintCallable, Category="Beam|APIs|Payments", meta=(AutoCreateRefTerm="OnSuccess,OnError,OnComplete"))
	void PostFacebookUpdate(UPostFacebookUpdateRequest* Request, const FOnPostFacebookUpdateSuccess& OnSuccess, const FOnPostFacebookUpdateError& OnError, const FOnPostFacebookUpdateComplete& OnComplete,
								 int64& OutRequestId);

		
	/**
	 * @brief Makes a request to the Post /basic/payments/facebook/purchase/complete endpoint of the Payments Service.
	 *
	 * @param Request The Request UObject. All (de)serialized data the request data creates is tied to the lifecycle of this object.
	 * @param OnSuccess What to do if the requests receives a successful response.
	 * @param OnError What to do if the request receives an error response.
	 * @param OnComplete What to after either OnSuccess or OnError have finished executing.
	 * @param OutRequestId The Request Id -- used to query information about the request or to cancel it while it's in flight. 
	 */
	UFUNCTION(BlueprintCallable, Category="Beam|APIs|Payments", meta=(AutoCreateRefTerm="OnSuccess,OnError,OnComplete"))
	void PostFacebookPurchaseComplete(UPostFacebookPurchaseCompleteRequest* Request, const FOnPostFacebookPurchaseCompleteSuccess& OnSuccess, const FOnPostFacebookPurchaseCompleteError& OnError, const FOnPostFacebookPurchaseCompleteComplete& OnComplete,
								 int64& OutRequestId);

		
	/**
	 * @brief Makes a request to the Post /basic/payments/test/purchase/complete endpoint of the Payments Service.
	 *
	 * @param Request The Request UObject. All (de)serialized data the request data creates is tied to the lifecycle of this object.
	 * @param OnSuccess What to do if the requests receives a successful response.
	 * @param OnError What to do if the request receives an error response.
	 * @param OnComplete What to after either OnSuccess or OnError have finished executing.
	 * @param OutRequestId The Request Id -- used to query information about the request or to cancel it while it's in flight. 
	 */
	UFUNCTION(BlueprintCallable, Category="Beam|APIs|Payments", meta=(AutoCreateRefTerm="OnSuccess,OnError,OnComplete"))
	void PostTestPurchaseComplete(UPostTestPurchaseCompleteRequest* Request, const FOnPostTestPurchaseCompleteSuccess& OnSuccess, const FOnPostTestPurchaseCompleteError& OnError, const FOnPostTestPurchaseCompleteComplete& OnComplete,
								 int64& OutRequestId);

		
	/**
	 * @brief Makes a request to the Get /basic/payments/itunes/product endpoint of the Payments Service.
	 *
	 * @param Request The Request UObject. All (de)serialized data the request data creates is tied to the lifecycle of this object.
	 * @param OnSuccess What to do if the requests receives a successful response.
	 * @param OnError What to do if the request receives an error response.
	 * @param OnComplete What to after either OnSuccess or OnError have finished executing.
	 * @param OutRequestId The Request Id -- used to query information about the request or to cancel it while it's in flight. 
	 */
	UFUNCTION(BlueprintCallable, Category="Beam|APIs|Payments", meta=(AutoCreateRefTerm="OnSuccess,OnError,OnComplete"))
	void GetItunesProduct(UGetItunesProductRequest* Request, const FOnGetItunesProductSuccess& OnSuccess, const FOnGetItunesProductError& OnError, const FOnGetItunesProductComplete& OnComplete,
								 int64& OutRequestId);

		
	/**
	 * @brief Makes a request to the Post /basic/payments/googleplay/purchase/complete endpoint of the Payments Service.
	 *
	 * @param Request The Request UObject. All (de)serialized data the request data creates is tied to the lifecycle of this object.
	 * @param OnSuccess What to do if the requests receives a successful response.
	 * @param OnError What to do if the request receives an error response.
	 * @param OnComplete What to after either OnSuccess or OnError have finished executing.
	 * @param OutRequestId The Request Id -- used to query information about the request or to cancel it while it's in flight. 
	 */
	UFUNCTION(BlueprintCallable, Category="Beam|APIs|Payments", meta=(AutoCreateRefTerm="OnSuccess,OnError,OnComplete"))
	void PostGoogleplayPurchaseComplete(UPostGoogleplayPurchaseCompleteRequest* Request, const FOnPostGoogleplayPurchaseCompleteSuccess& OnSuccess, const FOnPostGoogleplayPurchaseCompleteError& OnError, const FOnPostGoogleplayPurchaseCompleteComplete& OnComplete,
								 int64& OutRequestId);

		
	/**
	 * @brief Makes a request to the Post /basic/payments/test/purchase/track endpoint of the Payments Service.
	 *
	 * @param Request The Request UObject. All (de)serialized data the request data creates is tied to the lifecycle of this object.
	 * @param OnSuccess What to do if the requests receives a successful response.
	 * @param OnError What to do if the request receives an error response.
	 * @param OnComplete What to after either OnSuccess or OnError have finished executing.
	 * @param OutRequestId The Request Id -- used to query information about the request or to cancel it while it's in flight. 
	 */
	UFUNCTION(BlueprintCallable, Category="Beam|APIs|Payments", meta=(AutoCreateRefTerm="OnSuccess,OnError,OnComplete"))
	void PostTestPurchaseTrack(UPostTestPurchaseTrackRequest* Request, const FOnPostTestPurchaseTrackSuccess& OnSuccess, const FOnPostTestPurchaseTrackError& OnError, const FOnPostTestPurchaseTrackComplete& OnComplete,
								 int64& OutRequestId);

		
	/**
	 * @brief Makes a request to the Post /basic/payments/googleplay/purchase/verify endpoint of the Payments Service.
	 *
	 * @param Request The Request UObject. All (de)serialized data the request data creates is tied to the lifecycle of this object.
	 * @param OnSuccess What to do if the requests receives a successful response.
	 * @param OnError What to do if the request receives an error response.
	 * @param OnComplete What to after either OnSuccess or OnError have finished executing.
	 * @param OutRequestId The Request Id -- used to query information about the request or to cancel it while it's in flight. 
	 */
	UFUNCTION(BlueprintCallable, Category="Beam|APIs|Payments", meta=(AutoCreateRefTerm="OnSuccess,OnError,OnComplete"))
	void PostGoogleplayPurchaseVerify(UPostGoogleplayPurchaseVerifyRequest* Request, const FOnPostGoogleplayPurchaseVerifySuccess& OnSuccess, const FOnPostGoogleplayPurchaseVerifyError& OnError, const FOnPostGoogleplayPurchaseVerifyComplete& OnComplete,
								 int64& OutRequestId);

		
	/**
	 * @brief Makes a request to the Post /basic/payments/coupon/purchase/track endpoint of the Payments Service.
	 *
	 * @param Request The Request UObject. All (de)serialized data the request data creates is tied to the lifecycle of this object.
	 * @param OnSuccess What to do if the requests receives a successful response.
	 * @param OnError What to do if the request receives an error response.
	 * @param OnComplete What to after either OnSuccess or OnError have finished executing.
	 * @param OutRequestId The Request Id -- used to query information about the request or to cancel it while it's in flight. 
	 */
	UFUNCTION(BlueprintCallable, Category="Beam|APIs|Payments", meta=(AutoCreateRefTerm="OnSuccess,OnError,OnComplete"))
	void PostCouponPurchaseTrack(UPostCouponPurchaseTrackRequest* Request, const FOnPostCouponPurchaseTrackSuccess& OnSuccess, const FOnPostCouponPurchaseTrackError& OnError, const FOnPostCouponPurchaseTrackComplete& OnComplete,
								 int64& OutRequestId);

		
	/**
	 * @brief Makes a request to the Post /basic/payments/steam/purchase/complete endpoint of the Payments Service.
	 *
	 * @param Request The Request UObject. All (de)serialized data the request data creates is tied to the lifecycle of this object.
	 * @param OnSuccess What to do if the requests receives a successful response.
	 * @param OnError What to do if the request receives an error response.
	 * @param OnComplete What to after either OnSuccess or OnError have finished executing.
	 * @param OutRequestId The Request Id -- used to query information about the request or to cancel it while it's in flight. 
	 */
	UFUNCTION(BlueprintCallable, Category="Beam|APIs|Payments", meta=(AutoCreateRefTerm="OnSuccess,OnError,OnComplete"))
	void PostSteamPurchaseComplete(UPostSteamPurchaseCompleteRequest* Request, const FOnPostSteamPurchaseCompleteSuccess& OnSuccess, const FOnPostSteamPurchaseCompleteError& OnError, const FOnPostSteamPurchaseCompleteComplete& OnComplete,
								 int64& OutRequestId);

		
	/**
	 * @brief Makes a request to the Post /basic/payments/facebook/purchase/track endpoint of the Payments Service.
	 *
	 * @param Request The Request UObject. All (de)serialized data the request data creates is tied to the lifecycle of this object.
	 * @param OnSuccess What to do if the requests receives a successful response.
	 * @param OnError What to do if the request receives an error response.
	 * @param OnComplete What to after either OnSuccess or OnError have finished executing.
	 * @param OutRequestId The Request Id -- used to query information about the request or to cancel it while it's in flight. 
	 */
	UFUNCTION(BlueprintCallable, Category="Beam|APIs|Payments", meta=(AutoCreateRefTerm="OnSuccess,OnError,OnComplete"))
	void PostFacebookPurchaseTrack(UPostFacebookPurchaseTrackRequest* Request, const FOnPostFacebookPurchaseTrackSuccess& OnSuccess, const FOnPostFacebookPurchaseTrackError& OnError, const FOnPostFacebookPurchaseTrackComplete& OnComplete,
								 int64& OutRequestId);

		
	/**
	 * @brief Makes a request to the Post /basic/payments/test/purchase/verify endpoint of the Payments Service.
	 *
	 * @param Request The Request UObject. All (de)serialized data the request data creates is tied to the lifecycle of this object.
	 * @param OnSuccess What to do if the requests receives a successful response.
	 * @param OnError What to do if the request receives an error response.
	 * @param OnComplete What to after either OnSuccess or OnError have finished executing.
	 * @param OutRequestId The Request Id -- used to query information about the request or to cancel it while it's in flight. 
	 */
	UFUNCTION(BlueprintCallable, Category="Beam|APIs|Payments", meta=(AutoCreateRefTerm="OnSuccess,OnError,OnComplete"))
	void PostTestPurchaseVerify(UPostTestPurchaseVerifyRequest* Request, const FOnPostTestPurchaseVerifySuccess& OnSuccess, const FOnPostTestPurchaseVerifyError& OnError, const FOnPostTestPurchaseVerifyComplete& OnComplete,
								 int64& OutRequestId);

		
	/**
	 * @brief Makes a request to the Post /basic/payments/googleplay/purchase/track endpoint of the Payments Service.
	 *
	 * @param Request The Request UObject. All (de)serialized data the request data creates is tied to the lifecycle of this object.
	 * @param OnSuccess What to do if the requests receives a successful response.
	 * @param OnError What to do if the request receives an error response.
	 * @param OnComplete What to after either OnSuccess or OnError have finished executing.
	 * @param OutRequestId The Request Id -- used to query information about the request or to cancel it while it's in flight. 
	 */
	UFUNCTION(BlueprintCallable, Category="Beam|APIs|Payments", meta=(AutoCreateRefTerm="OnSuccess,OnError,OnComplete"))
	void PostGoogleplayPurchaseTrack(UPostGoogleplayPurchaseTrackRequest* Request, const FOnPostGoogleplayPurchaseTrackSuccess& OnSuccess, const FOnPostGoogleplayPurchaseTrackError& OnError, const FOnPostGoogleplayPurchaseTrackComplete& OnComplete,
								 int64& OutRequestId);

		
	/**
	 * @brief Makes a request to the Get /basic/payments/steam/prices endpoint of the Payments Service.
	 *
	 * @param Request The Request UObject. All (de)serialized data the request data creates is tied to the lifecycle of this object.
	 * @param OnSuccess What to do if the requests receives a successful response.
	 * @param OnError What to do if the request receives an error response.
	 * @param OnComplete What to after either OnSuccess or OnError have finished executing.
	 * @param OutRequestId The Request Id -- used to query information about the request or to cancel it while it's in flight. 
	 */
	UFUNCTION(BlueprintCallable, Category="Beam|APIs|Payments", meta=(AutoCreateRefTerm="OnSuccess,OnError,OnComplete"))
	void GetSteamPrices(UGetSteamPricesRequest* Request, const FOnGetSteamPricesSuccess& OnSuccess, const FOnGetSteamPricesError& OnError, const FOnGetSteamPricesComplete& OnComplete,
								 int64& OutRequestId);

		
	/**
	 * @brief Makes a request to the Post /basic/payments/windows/purchase/verify endpoint of the Payments Service.
	 *
	 * @param Request The Request UObject. All (de)serialized data the request data creates is tied to the lifecycle of this object.
	 * @param OnSuccess What to do if the requests receives a successful response.
	 * @param OnError What to do if the request receives an error response.
	 * @param OnComplete What to after either OnSuccess or OnError have finished executing.
	 * @param OutRequestId The Request Id -- used to query information about the request or to cancel it while it's in flight. 
	 */
	UFUNCTION(BlueprintCallable, Category="Beam|APIs|Payments", meta=(AutoCreateRefTerm="OnSuccess,OnError,OnComplete"))
	void PostWindowsPurchaseVerify(UPostWindowsPurchaseVerifyRequest* Request, const FOnPostWindowsPurchaseVerifySuccess& OnSuccess, const FOnPostWindowsPurchaseVerifyError& OnError, const FOnPostWindowsPurchaseVerifyComplete& OnComplete,
								 int64& OutRequestId);

		
	/**
	 * @brief Makes a request to the Post /basic/payments/itunes/purchase/verify endpoint of the Payments Service.
	 *
	 * @param Request The Request UObject. All (de)serialized data the request data creates is tied to the lifecycle of this object.
	 * @param OnSuccess What to do if the requests receives a successful response.
	 * @param OnError What to do if the request receives an error response.
	 * @param OnComplete What to after either OnSuccess or OnError have finished executing.
	 * @param OutRequestId The Request Id -- used to query information about the request or to cancel it while it's in flight. 
	 */
	UFUNCTION(BlueprintCallable, Category="Beam|APIs|Payments", meta=(AutoCreateRefTerm="OnSuccess,OnError,OnComplete"))
	void PostItunesPurchaseVerify(UPostItunesPurchaseVerifyRequest* Request, const FOnPostItunesPurchaseVerifySuccess& OnSuccess, const FOnPostItunesPurchaseVerifyError& OnError, const FOnPostItunesPurchaseVerifyComplete& OnComplete,
								 int64& OutRequestId);

		
	/**
	 * @brief Makes a request to the Post /basic/payments/itunes/purchase/complete endpoint of the Payments Service.
	 *
	 * @param Request The Request UObject. All (de)serialized data the request data creates is tied to the lifecycle of this object.
	 * @param OnSuccess What to do if the requests receives a successful response.
	 * @param OnError What to do if the request receives an error response.
	 * @param OnComplete What to after either OnSuccess or OnError have finished executing.
	 * @param OutRequestId The Request Id -- used to query information about the request or to cancel it while it's in flight. 
	 */
	UFUNCTION(BlueprintCallable, Category="Beam|APIs|Payments", meta=(AutoCreateRefTerm="OnSuccess,OnError,OnComplete"))
	void PostItunesPurchaseComplete(UPostItunesPurchaseCompleteRequest* Request, const FOnPostItunesPurchaseCompleteSuccess& OnSuccess, const FOnPostItunesPurchaseCompleteError& OnError, const FOnPostItunesPurchaseCompleteComplete& OnComplete,
								 int64& OutRequestId);

		
	/**
	 * @brief Makes a request to the Post /basic/payments/facebook/purchase/verify endpoint of the Payments Service.
	 *
	 * @param Request The Request UObject. All (de)serialized data the request data creates is tied to the lifecycle of this object.
	 * @param OnSuccess What to do if the requests receives a successful response.
	 * @param OnError What to do if the request receives an error response.
	 * @param OnComplete What to after either OnSuccess or OnError have finished executing.
	 * @param OutRequestId The Request Id -- used to query information about the request or to cancel it while it's in flight. 
	 */
	UFUNCTION(BlueprintCallable, Category="Beam|APIs|Payments", meta=(AutoCreateRefTerm="OnSuccess,OnError,OnComplete"))
	void PostFacebookPurchaseVerify(UPostFacebookPurchaseVerifyRequest* Request, const FOnPostFacebookPurchaseVerifySuccess& OnSuccess, const FOnPostFacebookPurchaseVerifyError& OnError, const FOnPostFacebookPurchaseVerifyComplete& OnComplete,
								 int64& OutRequestId);

		
	/**
	 * @brief Makes a request to the Post /basic/payments/steam/purchase/track endpoint of the Payments Service.
	 *
	 * @param Request The Request UObject. All (de)serialized data the request data creates is tied to the lifecycle of this object.
	 * @param OnSuccess What to do if the requests receives a successful response.
	 * @param OnError What to do if the request receives an error response.
	 * @param OnComplete What to after either OnSuccess or OnError have finished executing.
	 * @param OutRequestId The Request Id -- used to query information about the request or to cancel it while it's in flight. 
	 */
	UFUNCTION(BlueprintCallable, Category="Beam|APIs|Payments", meta=(AutoCreateRefTerm="OnSuccess,OnError,OnComplete"))
	void PostSteamPurchaseTrack(UPostSteamPurchaseTrackRequest* Request, const FOnPostSteamPurchaseTrackSuccess& OnSuccess, const FOnPostSteamPurchaseTrackError& OnError, const FOnPostSteamPurchaseTrackComplete& OnComplete,
								 int64& OutRequestId);

		
	/**
	 * @brief Makes a request to the Post /basic/payments/coupon/purchase/verify endpoint of the Payments Service.
	 *
	 * @param Request The Request UObject. All (de)serialized data the request data creates is tied to the lifecycle of this object.
	 * @param OnSuccess What to do if the requests receives a successful response.
	 * @param OnError What to do if the request receives an error response.
	 * @param OnComplete What to after either OnSuccess or OnError have finished executing.
	 * @param OutRequestId The Request Id -- used to query information about the request or to cancel it while it's in flight. 
	 */
	UFUNCTION(BlueprintCallable, Category="Beam|APIs|Payments", meta=(AutoCreateRefTerm="OnSuccess,OnError,OnComplete"))
	void PostCouponPurchaseVerify(UPostCouponPurchaseVerifyRequest* Request, const FOnPostCouponPurchaseVerifySuccess& OnSuccess, const FOnPostCouponPurchaseVerifyError& OnError, const FOnPostCouponPurchaseVerifyComplete& OnComplete,
								 int64& OutRequestId);

		
	/**
	 * @brief Makes a request to the Get /basic/payments/windows/product endpoint of the Payments Service.
	 *
	 * @param Request The Request UObject. All (de)serialized data the request data creates is tied to the lifecycle of this object.
	 * @param OnSuccess What to do if the requests receives a successful response.
	 * @param OnError What to do if the request receives an error response.
	 * @param OnComplete What to after either OnSuccess or OnError have finished executing.
	 * @param OutRequestId The Request Id -- used to query information about the request or to cancel it while it's in flight. 
	 */
	UFUNCTION(BlueprintCallable, Category="Beam|APIs|Payments", meta=(AutoCreateRefTerm="OnSuccess,OnError,OnComplete"))
	void GetWindowsProduct(UGetWindowsProductRequest* Request, const FOnGetWindowsProductSuccess& OnSuccess, const FOnGetWindowsProductError& OnError, const FOnGetWindowsProductComplete& OnComplete,
								 int64& OutRequestId);

		
	/**
	 * @brief Makes a request to the Get /basic/payments/facebook/product endpoint of the Payments Service.
	 *
	 * @param Request The Request UObject. All (de)serialized data the request data creates is tied to the lifecycle of this object.
	 * @param OnSuccess What to do if the requests receives a successful response.
	 * @param OnError What to do if the request receives an error response.
	 * @param OnComplete What to after either OnSuccess or OnError have finished executing.
	 * @param OutRequestId The Request Id -- used to query information about the request or to cancel it while it's in flight. 
	 */
	UFUNCTION(BlueprintCallable, Category="Beam|APIs|Payments", meta=(AutoCreateRefTerm="OnSuccess,OnError,OnComplete"))
	void GetFacebookProduct(UGetFacebookProductRequest* Request, const FOnGetFacebookProductSuccess& OnSuccess, const FOnGetFacebookProductError& OnError, const FOnGetFacebookProductComplete& OnComplete,
								 int64& OutRequestId);

		
	/**
	 * @brief Makes a request to the Get /basic/payments/coupon/product endpoint of the Payments Service.
	 *
	 * @param Request The Request UObject. All (de)serialized data the request data creates is tied to the lifecycle of this object.
	 * @param OnSuccess What to do if the requests receives a successful response.
	 * @param OnError What to do if the request receives an error response.
	 * @param OnComplete What to after either OnSuccess or OnError have finished executing.
	 * @param OutRequestId The Request Id -- used to query information about the request or to cancel it while it's in flight. 
	 */
	UFUNCTION(BlueprintCallable, Category="Beam|APIs|Payments", meta=(AutoCreateRefTerm="OnSuccess,OnError,OnComplete"))
	void GetCouponProduct(UGetCouponProductRequest* Request, const FOnGetCouponProductSuccess& OnSuccess, const FOnGetCouponProductError& OnError, const FOnGetCouponProductComplete& OnComplete,
								 int64& OutRequestId);

		
	/**
	 * @brief Makes a request to the Get /basic/payments/steam/products endpoint of the Payments Service.
	 *
	 * @param Request The Request UObject. All (de)serialized data the request data creates is tied to the lifecycle of this object.
	 * @param OnSuccess What to do if the requests receives a successful response.
	 * @param OnError What to do if the request receives an error response.
	 * @param OnComplete What to after either OnSuccess or OnError have finished executing.
	 * @param OutRequestId The Request Id -- used to query information about the request or to cancel it while it's in flight. 
	 */
	UFUNCTION(BlueprintCallable, Category="Beam|APIs|Payments", meta=(AutoCreateRefTerm="OnSuccess,OnError,OnComplete"))
	void GetSteamProducts(UGetSteamProductsRequest* Request, const FOnGetSteamProductsSuccess& OnSuccess, const FOnGetSteamProductsError& OnError, const FOnGetSteamProductsComplete& OnComplete,
								 int64& OutRequestId);

		
	/**
	 * @brief Makes a request to the Post /basic/payments/steam/auth endpoint of the Payments Service.
	 *
	 * @param Request The Request UObject. All (de)serialized data the request data creates is tied to the lifecycle of this object.
	 * @param OnSuccess What to do if the requests receives a successful response.
	 * @param OnError What to do if the request receives an error response.
	 * @param OnComplete What to after either OnSuccess or OnError have finished executing.
	 * @param OutRequestId The Request Id -- used to query information about the request or to cancel it while it's in flight. 
	 */
	UFUNCTION(BlueprintCallable, Category="Beam|APIs|Payments", meta=(AutoCreateRefTerm="OnSuccess,OnError,OnComplete"))
	void PostSteamAuth(UPostSteamAuthRequest* Request, const FOnPostSteamAuthSuccess& OnSuccess, const FOnPostSteamAuthError& OnError, const FOnPostSteamAuthComplete& OnComplete,
								 int64& OutRequestId);

		
	/**
	 * @brief Makes a request to the Get /basic/payments/steam/product endpoint of the Payments Service.
	 *
	 * @param Request The Request UObject. All (de)serialized data the request data creates is tied to the lifecycle of this object.
	 * @param OnSuccess What to do if the requests receives a successful response.
	 * @param OnError What to do if the request receives an error response.
	 * @param OnComplete What to after either OnSuccess or OnError have finished executing.
	 * @param OutRequestId The Request Id -- used to query information about the request or to cancel it while it's in flight. 
	 */
	UFUNCTION(BlueprintCallable, Category="Beam|APIs|Payments", meta=(AutoCreateRefTerm="OnSuccess,OnError,OnComplete"))
	void GetSteamProduct(UGetSteamProductRequest* Request, const FOnGetSteamProductSuccess& OnSuccess, const FOnGetSteamProductError& OnError, const FOnGetSteamProductComplete& OnComplete,
								 int64& OutRequestId);

		
	/**
	 * @brief Makes a request to the Post /basic/payments/coupon/purchase/complete endpoint of the Payments Service.
	 *
	 * @param Request The Request UObject. All (de)serialized data the request data creates is tied to the lifecycle of this object.
	 * @param OnSuccess What to do if the requests receives a successful response.
	 * @param OnError What to do if the request receives an error response.
	 * @param OnComplete What to after either OnSuccess or OnError have finished executing.
	 * @param OutRequestId The Request Id -- used to query information about the request or to cancel it while it's in flight. 
	 */
	UFUNCTION(BlueprintCallable, Category="Beam|APIs|Payments", meta=(AutoCreateRefTerm="OnSuccess,OnError,OnComplete"))
	void PostCouponPurchaseComplete(UPostCouponPurchaseCompleteRequest* Request, const FOnPostCouponPurchaseCompleteSuccess& OnSuccess, const FOnPostCouponPurchaseCompleteError& OnError, const FOnPostCouponPurchaseCompleteComplete& OnComplete,
								 int64& OutRequestId);

		
	/**
	 * @brief Makes a request to the Get /basic/payments/googleplay/product endpoint of the Payments Service.
	 *
	 * @param Request The Request UObject. All (de)serialized data the request data creates is tied to the lifecycle of this object.
	 * @param OnSuccess What to do if the requests receives a successful response.
	 * @param OnError What to do if the request receives an error response.
	 * @param OnComplete What to after either OnSuccess or OnError have finished executing.
	 * @param OutRequestId The Request Id -- used to query information about the request or to cancel it while it's in flight. 
	 */
	UFUNCTION(BlueprintCallable, Category="Beam|APIs|Payments", meta=(AutoCreateRefTerm="OnSuccess,OnError,OnComplete"))
	void GetGoogleplayProduct(UGetGoogleplayProductRequest* Request, const FOnGetGoogleplayProductSuccess& OnSuccess, const FOnGetGoogleplayProductError& OnError, const FOnGetGoogleplayProductComplete& OnComplete,
								 int64& OutRequestId);

		
	/**
	 * @brief Makes a request to the Get /basic/payments/test/product endpoint of the Payments Service.
	 *
	 * @param Request The Request UObject. All (de)serialized data the request data creates is tied to the lifecycle of this object.
	 * @param OnSuccess What to do if the requests receives a successful response.
	 * @param OnError What to do if the request receives an error response.
	 * @param OnComplete What to after either OnSuccess or OnError have finished executing.
	 * @param OutRequestId The Request Id -- used to query information about the request or to cancel it while it's in flight. 
	 */
	UFUNCTION(BlueprintCallable, Category="Beam|APIs|Payments", meta=(AutoCreateRefTerm="OnSuccess,OnError,OnComplete"))
	void GetTestProduct(UGetTestProductRequest* Request, const FOnGetTestProductSuccess& OnSuccess, const FOnGetTestProductError& OnError, const FOnGetTestProductComplete& OnComplete,
								 int64& OutRequestId);

		
	/**
	 * @brief Makes a request to the Post /basic/payments/steam/purchase/verify endpoint of the Payments Service.
	 *
	 * @param Request The Request UObject. All (de)serialized data the request data creates is tied to the lifecycle of this object.
	 * @param OnSuccess What to do if the requests receives a successful response.
	 * @param OnError What to do if the request receives an error response.
	 * @param OnComplete What to after either OnSuccess or OnError have finished executing.
	 * @param OutRequestId The Request Id -- used to query information about the request or to cancel it while it's in flight. 
	 */
	UFUNCTION(BlueprintCallable, Category="Beam|APIs|Payments", meta=(AutoCreateRefTerm="OnSuccess,OnError,OnComplete"))
	void PostSteamPurchaseVerify(UPostSteamPurchaseVerifyRequest* Request, const FOnPostSteamPurchaseVerifySuccess& OnSuccess, const FOnPostSteamPurchaseVerifyError& OnError, const FOnPostSteamPurchaseVerifyComplete& OnComplete,
								 int64& OutRequestId);

		
	/**
	 * @brief Makes a request to the Post /basic/payments/itunes/purchase/track endpoint of the Payments Service.
	 *
	 * @param Request The Request UObject. All (de)serialized data the request data creates is tied to the lifecycle of this object.
	 * @param OnSuccess What to do if the requests receives a successful response.
	 * @param OnError What to do if the request receives an error response.
	 * @param OnComplete What to after either OnSuccess or OnError have finished executing.
	 * @param OutRequestId The Request Id -- used to query information about the request or to cancel it while it's in flight. 
	 */
	UFUNCTION(BlueprintCallable, Category="Beam|APIs|Payments", meta=(AutoCreateRefTerm="OnSuccess,OnError,OnComplete"))
	void PostItunesPurchaseTrack(UPostItunesPurchaseTrackRequest* Request, const FOnPostItunesPurchaseTrackSuccess& OnSuccess, const FOnPostItunesPurchaseTrackError& OnError, const FOnPostItunesPurchaseTrackComplete& OnComplete,
								 int64& OutRequestId);

		
	/**
	 * @brief Makes a request to the Get /object/payments/{objectId}/ endpoint of the Payments Service.
	 *
	 * @param Request The Request UObject. All (de)serialized data the request data creates is tied to the lifecycle of this object.
	 * @param OnSuccess What to do if the requests receives a successful response.
	 * @param OnError What to do if the request receives an error response.
	 * @param OnComplete What to after either OnSuccess or OnError have finished executing.
	 * @param OutRequestId The Request Id -- used to query information about the request or to cancel it while it's in flight. 
	 */
	UFUNCTION(BlueprintCallable, Category="Beam|APIs|Payments", meta=(AutoCreateRefTerm="OnSuccess,OnError,OnComplete"))
	void GetPayments(UGetPaymentsRequest* Request, const FOnGetPaymentsSuccess& OnSuccess, const FOnGetPaymentsError& OnError, const FOnGetPaymentsComplete& OnComplete,
								 int64& OutRequestId);


	
	/**
	 * @brief Makes an authenticated request to the Post /basic/payments/test/purchase/begin endpoint of the Payments Service.
	 *
	 * @param UserSlot The authenticated UserSlot with the user making the request. 
	 * @param Request The Request UObject. All (de)serialized data the request data creates is tied to the lifecycle of this object.
	 * @param OnSuccess What to do if the requests receives a successful response.
	 * @param OnError What to do if the request receives an error response.
	 * @param OnComplete What to after either OnSuccess or OnError have finished executing.
	 * @param OutRequestId The Request Id -- used to query information about the request or to cancel it while it's in flight. 
	 */
	UFUNCTION(BlueprintCallable, Category="Beam|APIs|Payments", meta=(AutoCreateRefTerm="UserSlot,OnSuccess,OnError,OnComplete"))
	void PostTestPurchaseBegin(const FUserSlot& UserSlot, UPostTestPurchaseBeginRequest* Request, const FOnPostTestPurchaseBeginSuccess& OnSuccess, const FOnPostTestPurchaseBeginError& OnError, const FOnPostTestPurchaseBeginComplete& OnComplete, int64& OutRequestId);

		
	/**
	 * @brief Makes an authenticated request to the Post /basic/payments/steam/purchase/fail endpoint of the Payments Service.
	 *
	 * @param UserSlot The authenticated UserSlot with the user making the request. 
	 * @param Request The Request UObject. All (de)serialized data the request data creates is tied to the lifecycle of this object.
	 * @param OnSuccess What to do if the requests receives a successful response.
	 * @param OnError What to do if the request receives an error response.
	 * @param OnComplete What to after either OnSuccess or OnError have finished executing.
	 * @param OutRequestId The Request Id -- used to query information about the request or to cancel it while it's in flight. 
	 */
	UFUNCTION(BlueprintCallable, Category="Beam|APIs|Payments", meta=(AutoCreateRefTerm="UserSlot,OnSuccess,OnError,OnComplete"))
	void PostSteamPurchaseFail(const FUserSlot& UserSlot, UPostSteamPurchaseFailRequest* Request, const FOnPostSteamPurchaseFailSuccess& OnSuccess, const FOnPostSteamPurchaseFailError& OnError, const FOnPostSteamPurchaseFailComplete& OnComplete, int64& OutRequestId);

		
	/**
	 * @brief Makes an authenticated request to the Post /basic/payments/facebook/purchase/fail endpoint of the Payments Service.
	 *
	 * @param UserSlot The authenticated UserSlot with the user making the request. 
	 * @param Request The Request UObject. All (de)serialized data the request data creates is tied to the lifecycle of this object.
	 * @param OnSuccess What to do if the requests receives a successful response.
	 * @param OnError What to do if the request receives an error response.
	 * @param OnComplete What to after either OnSuccess or OnError have finished executing.
	 * @param OutRequestId The Request Id -- used to query information about the request or to cancel it while it's in flight. 
	 */
	UFUNCTION(BlueprintCallable, Category="Beam|APIs|Payments", meta=(AutoCreateRefTerm="UserSlot,OnSuccess,OnError,OnComplete"))
	void PostFacebookPurchaseFail(const FUserSlot& UserSlot, UPostFacebookPurchaseFailRequest* Request, const FOnPostFacebookPurchaseFailSuccess& OnSuccess, const FOnPostFacebookPurchaseFailError& OnError, const FOnPostFacebookPurchaseFailComplete& OnComplete, int64& OutRequestId);

		
	/**
	 * @brief Makes an authenticated request to the Post /basic/payments/googleplay/purchase/begin endpoint of the Payments Service.
	 *
	 * @param UserSlot The authenticated UserSlot with the user making the request. 
	 * @param Request The Request UObject. All (de)serialized data the request data creates is tied to the lifecycle of this object.
	 * @param OnSuccess What to do if the requests receives a successful response.
	 * @param OnError What to do if the request receives an error response.
	 * @param OnComplete What to after either OnSuccess or OnError have finished executing.
	 * @param OutRequestId The Request Id -- used to query information about the request or to cancel it while it's in flight. 
	 */
	UFUNCTION(BlueprintCallable, Category="Beam|APIs|Payments", meta=(AutoCreateRefTerm="UserSlot,OnSuccess,OnError,OnComplete"))
	void PostGoogleplayPurchaseBegin(const FUserSlot& UserSlot, UPostGoogleplayPurchaseBeginRequest* Request, const FOnPostGoogleplayPurchaseBeginSuccess& OnSuccess, const FOnPostGoogleplayPurchaseBeginError& OnError, const FOnPostGoogleplayPurchaseBeginComplete& OnComplete, int64& OutRequestId);

		
	/**
	 * @brief Makes an authenticated request to the Post /basic/payments/itunes/purchase/begin endpoint of the Payments Service.
	 *
	 * @param UserSlot The authenticated UserSlot with the user making the request. 
	 * @param Request The Request UObject. All (de)serialized data the request data creates is tied to the lifecycle of this object.
	 * @param OnSuccess What to do if the requests receives a successful response.
	 * @param OnError What to do if the request receives an error response.
	 * @param OnComplete What to after either OnSuccess or OnError have finished executing.
	 * @param OutRequestId The Request Id -- used to query information about the request or to cancel it while it's in flight. 
	 */
	UFUNCTION(BlueprintCallable, Category="Beam|APIs|Payments", meta=(AutoCreateRefTerm="UserSlot,OnSuccess,OnError,OnComplete"))
	void PostItunesPurchaseBegin(const FUserSlot& UserSlot, UPostItunesPurchaseBeginRequest* Request, const FOnPostItunesPurchaseBeginSuccess& OnSuccess, const FOnPostItunesPurchaseBeginError& OnError, const FOnPostItunesPurchaseBeginComplete& OnComplete, int64& OutRequestId);

		
	/**
	 * @brief Makes an authenticated request to the Post /basic/payments/facebook/purchase/cancel endpoint of the Payments Service.
	 *
	 * @param UserSlot The authenticated UserSlot with the user making the request. 
	 * @param Request The Request UObject. All (de)serialized data the request data creates is tied to the lifecycle of this object.
	 * @param OnSuccess What to do if the requests receives a successful response.
	 * @param OnError What to do if the request receives an error response.
	 * @param OnComplete What to after either OnSuccess or OnError have finished executing.
	 * @param OutRequestId The Request Id -- used to query information about the request or to cancel it while it's in flight. 
	 */
	UFUNCTION(BlueprintCallable, Category="Beam|APIs|Payments", meta=(AutoCreateRefTerm="UserSlot,OnSuccess,OnError,OnComplete"))
	void PostFacebookPurchaseCancel(const FUserSlot& UserSlot, UPostFacebookPurchaseCancelRequest* Request, const FOnPostFacebookPurchaseCancelSuccess& OnSuccess, const FOnPostFacebookPurchaseCancelError& OnError, const FOnPostFacebookPurchaseCancelComplete& OnComplete, int64& OutRequestId);

		
	/**
	 * @brief Makes an authenticated request to the Post /basic/payments/itunes/purchase/fail endpoint of the Payments Service.
	 *
	 * @param UserSlot The authenticated UserSlot with the user making the request. 
	 * @param Request The Request UObject. All (de)serialized data the request data creates is tied to the lifecycle of this object.
	 * @param OnSuccess What to do if the requests receives a successful response.
	 * @param OnError What to do if the request receives an error response.
	 * @param OnComplete What to after either OnSuccess or OnError have finished executing.
	 * @param OutRequestId The Request Id -- used to query information about the request or to cancel it while it's in flight. 
	 */
	UFUNCTION(BlueprintCallable, Category="Beam|APIs|Payments", meta=(AutoCreateRefTerm="UserSlot,OnSuccess,OnError,OnComplete"))
	void PostItunesPurchaseFail(const FUserSlot& UserSlot, UPostItunesPurchaseFailRequest* Request, const FOnPostItunesPurchaseFailSuccess& OnSuccess, const FOnPostItunesPurchaseFailError& OnError, const FOnPostItunesPurchaseFailComplete& OnComplete, int64& OutRequestId);

		
	/**
	 * @brief Makes an authenticated request to the Post /basic/payments/test/purchase/cancel endpoint of the Payments Service.
	 *
	 * @param UserSlot The authenticated UserSlot with the user making the request. 
	 * @param Request The Request UObject. All (de)serialized data the request data creates is tied to the lifecycle of this object.
	 * @param OnSuccess What to do if the requests receives a successful response.
	 * @param OnError What to do if the request receives an error response.
	 * @param OnComplete What to after either OnSuccess or OnError have finished executing.
	 * @param OutRequestId The Request Id -- used to query information about the request or to cancel it while it's in flight. 
	 */
	UFUNCTION(BlueprintCallable, Category="Beam|APIs|Payments", meta=(AutoCreateRefTerm="UserSlot,OnSuccess,OnError,OnComplete"))
	void PostTestPurchaseCancel(const FUserSlot& UserSlot, UPostTestPurchaseCancelRequest* Request, const FOnPostTestPurchaseCancelSuccess& OnSuccess, const FOnPostTestPurchaseCancelError& OnError, const FOnPostTestPurchaseCancelComplete& OnComplete, int64& OutRequestId);

		
	/**
	 * @brief Makes an authenticated request to the Post /basic/payments/test/purchase/fail endpoint of the Payments Service.
	 *
	 * @param UserSlot The authenticated UserSlot with the user making the request. 
	 * @param Request The Request UObject. All (de)serialized data the request data creates is tied to the lifecycle of this object.
	 * @param OnSuccess What to do if the requests receives a successful response.
	 * @param OnError What to do if the request receives an error response.
	 * @param OnComplete What to after either OnSuccess or OnError have finished executing.
	 * @param OutRequestId The Request Id -- used to query information about the request or to cancel it while it's in flight. 
	 */
	UFUNCTION(BlueprintCallable, Category="Beam|APIs|Payments", meta=(AutoCreateRefTerm="UserSlot,OnSuccess,OnError,OnComplete"))
	void PostTestPurchaseFail(const FUserSlot& UserSlot, UPostTestPurchaseFailRequest* Request, const FOnPostTestPurchaseFailSuccess& OnSuccess, const FOnPostTestPurchaseFailError& OnError, const FOnPostTestPurchaseFailComplete& OnComplete, int64& OutRequestId);

		
	/**
	 * @brief Makes an authenticated request to the Post /basic/payments/coupon/purchase/cancel endpoint of the Payments Service.
	 *
	 * @param UserSlot The authenticated UserSlot with the user making the request. 
	 * @param Request The Request UObject. All (de)serialized data the request data creates is tied to the lifecycle of this object.
	 * @param OnSuccess What to do if the requests receives a successful response.
	 * @param OnError What to do if the request receives an error response.
	 * @param OnComplete What to after either OnSuccess or OnError have finished executing.
	 * @param OutRequestId The Request Id -- used to query information about the request or to cancel it while it's in flight. 
	 */
	UFUNCTION(BlueprintCallable, Category="Beam|APIs|Payments", meta=(AutoCreateRefTerm="UserSlot,OnSuccess,OnError,OnComplete"))
	void PostCouponPurchaseCancel(const FUserSlot& UserSlot, UPostCouponPurchaseCancelRequest* Request, const FOnPostCouponPurchaseCancelSuccess& OnSuccess, const FOnPostCouponPurchaseCancelError& OnError, const FOnPostCouponPurchaseCancelComplete& OnComplete, int64& OutRequestId);

		
	/**
	 * @brief Makes an authenticated request to the Post /basic/payments/coupon/purchase/begin endpoint of the Payments Service.
	 *
	 * @param UserSlot The authenticated UserSlot with the user making the request. 
	 * @param Request The Request UObject. All (de)serialized data the request data creates is tied to the lifecycle of this object.
	 * @param OnSuccess What to do if the requests receives a successful response.
	 * @param OnError What to do if the request receives an error response.
	 * @param OnComplete What to after either OnSuccess or OnError have finished executing.
	 * @param OutRequestId The Request Id -- used to query information about the request or to cancel it while it's in flight. 
	 */
	UFUNCTION(BlueprintCallable, Category="Beam|APIs|Payments", meta=(AutoCreateRefTerm="UserSlot,OnSuccess,OnError,OnComplete"))
	void PostCouponPurchaseBegin(const FUserSlot& UserSlot, UPostCouponPurchaseBeginRequest* Request, const FOnPostCouponPurchaseBeginSuccess& OnSuccess, const FOnPostCouponPurchaseBeginError& OnError, const FOnPostCouponPurchaseBeginComplete& OnComplete, int64& OutRequestId);

		
	/**
	 * @brief Makes an authenticated request to the Post /basic/payments/facebook/purchase/begin endpoint of the Payments Service.
	 *
	 * @param UserSlot The authenticated UserSlot with the user making the request. 
	 * @param Request The Request UObject. All (de)serialized data the request data creates is tied to the lifecycle of this object.
	 * @param OnSuccess What to do if the requests receives a successful response.
	 * @param OnError What to do if the request receives an error response.
	 * @param OnComplete What to after either OnSuccess or OnError have finished executing.
	 * @param OutRequestId The Request Id -- used to query information about the request or to cancel it while it's in flight. 
	 */
	UFUNCTION(BlueprintCallable, Category="Beam|APIs|Payments", meta=(AutoCreateRefTerm="UserSlot,OnSuccess,OnError,OnComplete"))
	void PostFacebookPurchaseBegin(const FUserSlot& UserSlot, UPostFacebookPurchaseBeginRequest* Request, const FOnPostFacebookPurchaseBeginSuccess& OnSuccess, const FOnPostFacebookPurchaseBeginError& OnError, const FOnPostFacebookPurchaseBeginComplete& OnComplete, int64& OutRequestId);

		
	/**
	 * @brief Makes an authenticated request to the Get /basic/payments/steam/order endpoint of the Payments Service.
	 *
	 * @param UserSlot The authenticated UserSlot with the user making the request. 
	 * @param Request The Request UObject. All (de)serialized data the request data creates is tied to the lifecycle of this object.
	 * @param OnSuccess What to do if the requests receives a successful response.
	 * @param OnError What to do if the request receives an error response.
	 * @param OnComplete What to after either OnSuccess or OnError have finished executing.
	 * @param OutRequestId The Request Id -- used to query information about the request or to cancel it while it's in flight. 
	 */
	UFUNCTION(BlueprintCallable, Category="Beam|APIs|Payments", meta=(AutoCreateRefTerm="UserSlot,OnSuccess,OnError,OnComplete"))
	void GetSteamOrder(const FUserSlot& UserSlot, UGetSteamOrderRequest* Request, const FOnGetSteamOrderSuccess& OnSuccess, const FOnGetSteamOrderError& OnError, const FOnGetSteamOrderComplete& OnComplete, int64& OutRequestId);

		
	/**
	 * @brief Makes an authenticated request to the Post /basic/payments/windows/purchase/begin endpoint of the Payments Service.
	 *
	 * @param UserSlot The authenticated UserSlot with the user making the request. 
	 * @param Request The Request UObject. All (de)serialized data the request data creates is tied to the lifecycle of this object.
	 * @param OnSuccess What to do if the requests receives a successful response.
	 * @param OnError What to do if the request receives an error response.
	 * @param OnComplete What to after either OnSuccess or OnError have finished executing.
	 * @param OutRequestId The Request Id -- used to query information about the request or to cancel it while it's in flight. 
	 */
	UFUNCTION(BlueprintCallable, Category="Beam|APIs|Payments", meta=(AutoCreateRefTerm="UserSlot,OnSuccess,OnError,OnComplete"))
	void PostWindowsPurchaseBegin(const FUserSlot& UserSlot, UPostWindowsPurchaseBeginRequest* Request, const FOnPostWindowsPurchaseBeginSuccess& OnSuccess, const FOnPostWindowsPurchaseBeginError& OnError, const FOnPostWindowsPurchaseBeginComplete& OnComplete, int64& OutRequestId);

		
	/**
	 * @brief Makes an authenticated request to the Post /basic/payments/googleplay/purchase/fail endpoint of the Payments Service.
	 *
	 * @param UserSlot The authenticated UserSlot with the user making the request. 
	 * @param Request The Request UObject. All (de)serialized data the request data creates is tied to the lifecycle of this object.
	 * @param OnSuccess What to do if the requests receives a successful response.
	 * @param OnError What to do if the request receives an error response.
	 * @param OnComplete What to after either OnSuccess or OnError have finished executing.
	 * @param OutRequestId The Request Id -- used to query information about the request or to cancel it while it's in flight. 
	 */
	UFUNCTION(BlueprintCallable, Category="Beam|APIs|Payments", meta=(AutoCreateRefTerm="UserSlot,OnSuccess,OnError,OnComplete"))
	void PostGoogleplayPurchaseFail(const FUserSlot& UserSlot, UPostGoogleplayPurchaseFailRequest* Request, const FOnPostGoogleplayPurchaseFailSuccess& OnSuccess, const FOnPostGoogleplayPurchaseFailError& OnError, const FOnPostGoogleplayPurchaseFailComplete& OnComplete, int64& OutRequestId);

		
	/**
	 * @brief Makes an authenticated request to the Post /basic/payments/googleplay/purchase/cancel endpoint of the Payments Service.
	 *
	 * @param UserSlot The authenticated UserSlot with the user making the request. 
	 * @param Request The Request UObject. All (de)serialized data the request data creates is tied to the lifecycle of this object.
	 * @param OnSuccess What to do if the requests receives a successful response.
	 * @param OnError What to do if the request receives an error response.
	 * @param OnComplete What to after either OnSuccess or OnError have finished executing.
	 * @param OutRequestId The Request Id -- used to query information about the request or to cancel it while it's in flight. 
	 */
	UFUNCTION(BlueprintCallable, Category="Beam|APIs|Payments", meta=(AutoCreateRefTerm="UserSlot,OnSuccess,OnError,OnComplete"))
	void PostGoogleplayPurchaseCancel(const FUserSlot& UserSlot, UPostGoogleplayPurchaseCancelRequest* Request, const FOnPostGoogleplayPurchaseCancelSuccess& OnSuccess, const FOnPostGoogleplayPurchaseCancelError& OnError, const FOnPostGoogleplayPurchaseCancelComplete& OnComplete, int64& OutRequestId);

		
	/**
	 * @brief Makes an authenticated request to the Post /basic/payments/coupon/purchase/fail endpoint of the Payments Service.
	 *
	 * @param UserSlot The authenticated UserSlot with the user making the request. 
	 * @param Request The Request UObject. All (de)serialized data the request data creates is tied to the lifecycle of this object.
	 * @param OnSuccess What to do if the requests receives a successful response.
	 * @param OnError What to do if the request receives an error response.
	 * @param OnComplete What to after either OnSuccess or OnError have finished executing.
	 * @param OutRequestId The Request Id -- used to query information about the request or to cancel it while it's in flight. 
	 */
	UFUNCTION(BlueprintCallable, Category="Beam|APIs|Payments", meta=(AutoCreateRefTerm="UserSlot,OnSuccess,OnError,OnComplete"))
	void PostCouponPurchaseFail(const FUserSlot& UserSlot, UPostCouponPurchaseFailRequest* Request, const FOnPostCouponPurchaseFailSuccess& OnSuccess, const FOnPostCouponPurchaseFailError& OnError, const FOnPostCouponPurchaseFailComplete& OnComplete, int64& OutRequestId);

		
	/**
	 * @brief Makes an authenticated request to the Post /basic/payments/steam/purchase/begin endpoint of the Payments Service.
	 *
	 * @param UserSlot The authenticated UserSlot with the user making the request. 
	 * @param Request The Request UObject. All (de)serialized data the request data creates is tied to the lifecycle of this object.
	 * @param OnSuccess What to do if the requests receives a successful response.
	 * @param OnError What to do if the request receives an error response.
	 * @param OnComplete What to after either OnSuccess or OnError have finished executing.
	 * @param OutRequestId The Request Id -- used to query information about the request or to cancel it while it's in flight. 
	 */
	UFUNCTION(BlueprintCallable, Category="Beam|APIs|Payments", meta=(AutoCreateRefTerm="UserSlot,OnSuccess,OnError,OnComplete"))
	void PostSteamPurchaseBegin(const FUserSlot& UserSlot, UPostSteamPurchaseBeginRequest* Request, const FOnPostSteamPurchaseBeginSuccess& OnSuccess, const FOnPostSteamPurchaseBeginError& OnError, const FOnPostSteamPurchaseBeginComplete& OnComplete, int64& OutRequestId);

		
	/**
	 * @brief Makes an authenticated request to the Post /basic/payments/steam/purchase/cancel endpoint of the Payments Service.
	 *
	 * @param UserSlot The authenticated UserSlot with the user making the request. 
	 * @param Request The Request UObject. All (de)serialized data the request data creates is tied to the lifecycle of this object.
	 * @param OnSuccess What to do if the requests receives a successful response.
	 * @param OnError What to do if the request receives an error response.
	 * @param OnComplete What to after either OnSuccess or OnError have finished executing.
	 * @param OutRequestId The Request Id -- used to query information about the request or to cancel it while it's in flight. 
	 */
	UFUNCTION(BlueprintCallable, Category="Beam|APIs|Payments", meta=(AutoCreateRefTerm="UserSlot,OnSuccess,OnError,OnComplete"))
	void PostSteamPurchaseCancel(const FUserSlot& UserSlot, UPostSteamPurchaseCancelRequest* Request, const FOnPostSteamPurchaseCancelSuccess& OnSuccess, const FOnPostSteamPurchaseCancelError& OnError, const FOnPostSteamPurchaseCancelComplete& OnComplete, int64& OutRequestId);

		
	/**
	 * @brief Makes an authenticated request to the Post /basic/payments/windows/purchase/cancel endpoint of the Payments Service.
	 *
	 * @param UserSlot The authenticated UserSlot with the user making the request. 
	 * @param Request The Request UObject. All (de)serialized data the request data creates is tied to the lifecycle of this object.
	 * @param OnSuccess What to do if the requests receives a successful response.
	 * @param OnError What to do if the request receives an error response.
	 * @param OnComplete What to after either OnSuccess or OnError have finished executing.
	 * @param OutRequestId The Request Id -- used to query information about the request or to cancel it while it's in flight. 
	 */
	UFUNCTION(BlueprintCallable, Category="Beam|APIs|Payments", meta=(AutoCreateRefTerm="UserSlot,OnSuccess,OnError,OnComplete"))
	void PostWindowsPurchaseCancel(const FUserSlot& UserSlot, UPostWindowsPurchaseCancelRequest* Request, const FOnPostWindowsPurchaseCancelSuccess& OnSuccess, const FOnPostWindowsPurchaseCancelError& OnError, const FOnPostWindowsPurchaseCancelComplete& OnComplete, int64& OutRequestId);

		
	/**
	 * @brief Makes an authenticated request to the Post /basic/payments/windows/purchase/fail endpoint of the Payments Service.
	 *
	 * @param UserSlot The authenticated UserSlot with the user making the request. 
	 * @param Request The Request UObject. All (de)serialized data the request data creates is tied to the lifecycle of this object.
	 * @param OnSuccess What to do if the requests receives a successful response.
	 * @param OnError What to do if the request receives an error response.
	 * @param OnComplete What to after either OnSuccess or OnError have finished executing.
	 * @param OutRequestId The Request Id -- used to query information about the request or to cancel it while it's in flight. 
	 */
	UFUNCTION(BlueprintCallable, Category="Beam|APIs|Payments", meta=(AutoCreateRefTerm="UserSlot,OnSuccess,OnError,OnComplete"))
	void PostWindowsPurchaseFail(const FUserSlot& UserSlot, UPostWindowsPurchaseFailRequest* Request, const FOnPostWindowsPurchaseFailSuccess& OnSuccess, const FOnPostWindowsPurchaseFailError& OnError, const FOnPostWindowsPurchaseFailComplete& OnComplete, int64& OutRequestId);

		
	/**
	 * @brief Makes an authenticated request to the Post /basic/payments/itunes/purchase/cancel endpoint of the Payments Service.
	 *
	 * @param UserSlot The authenticated UserSlot with the user making the request. 
	 * @param Request The Request UObject. All (de)serialized data the request data creates is tied to the lifecycle of this object.
	 * @param OnSuccess What to do if the requests receives a successful response.
	 * @param OnError What to do if the request receives an error response.
	 * @param OnComplete What to after either OnSuccess or OnError have finished executing.
	 * @param OutRequestId The Request Id -- used to query information about the request or to cancel it while it's in flight. 
	 */
	UFUNCTION(BlueprintCallable, Category="Beam|APIs|Payments", meta=(AutoCreateRefTerm="UserSlot,OnSuccess,OnError,OnComplete"))
	void PostItunesPurchaseCancel(const FUserSlot& UserSlot, UPostItunesPurchaseCancelRequest* Request, const FOnPostItunesPurchaseCancelSuccess& OnSuccess, const FOnPostItunesPurchaseCancelError& OnError, const FOnPostItunesPurchaseCancelComplete& OnComplete, int64& OutRequestId);
	
};
