// Fill out your copyright notice in the Description page of Project Settings.


#include "RawAPIs/Auth/BeamAuthApi.h"

#include "BeamBackend.h"


void UBeamAuthApi::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
	Backend = Cast<UBeamBackend>(Collection.InitializeDependency(UBeamBackend::StaticClass()));
}

void UBeamAuthApi::Deinitialize()
{
	Super::Deinitialize();
}

/** Fully Parameterized Handlers **/

void UBeamAuthApi::BP_RegisterCustomerRequest(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, const FRegisterCustomerRequest& RequestData,
                                              FBeamConnectivity& ConnectivityStatus,
                                              const FOnRegisterCustomerSuccess& OnSuccess, const FOnRegisterCustomerError& OnError, const FOnRegisterCustomerComplete& OnComplete,
                                              int64& OutRequestId) const
{
	// AUTO-GENERATED...	
	const auto Request = Backend->CreateRequest(OutRequestId, TargetRealm, RetryConfig, RequestData);

	// Binds the handler to the static response handler (pre-generated)
	const auto BeamRequestProcessor = Backend->MakeBlueprintRequestProcessor
		<FRegisterCustomerRequest, FRegisterCustomerResponse, FOnRegisterCustomerSuccess, FOnRegisterCustomerError, FOnRegisterCustomerComplete>
		(OutRequestId, RequestData, OnSuccess, OnError, OnComplete);
	Request->OnProcessRequestComplete().BindLambda(BeamRequestProcessor);

	// Logic that actually talks to the backend --- if you pass in some other delegate, that means you can avoid making the actual back-end call.
	const auto RequestContext = FBeamRequestContext{RetryConfig, TargetRealm};
	Backend->ExecuteRequestDelegate.ExecuteIfBound(RequestContext, ConnectivityStatus, OutRequestId);
}

void UBeamAuthApi::BP_MeRequest(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, const FBeamAuthToken& AuthToken, const FMeRequest& RequestData,
                                FBeamConnectivity& ConnectivityStatus,
                                const FOnMeSuccess& OnSuccess, const FOnMeError& OnError, const FOnMeComplete& OnComplete, int64& OutRequestId) const
{
	// AUTO-GENERATED...	
	const auto Request = Backend->CreateAuthenticatedRequest(OutRequestId, TargetRealm, RetryConfig, AuthToken, RequestData);

	// Binds the handler to the static response handler (pre-generated)
	const auto BeamRequestProcessor = Backend->MakeAuthenticatedBlueprintRequestProcessor
		<FMeRequest, FMeResponse, FOnMeSuccess, FOnMeError, FOnMeComplete>
		(OutRequestId, TargetRealm, AuthToken, RequestData, OnSuccess, OnError, OnComplete);
	Request->OnProcessRequestComplete().BindLambda(BeamRequestProcessor);

	// Logic that actually talks to the backend --- if you pass in some other delegate, that means you can avoid making the actual back-end call.
	const auto RequestContext = FBeamRequestContext{RetryConfig, TargetRealm};
	Backend->ExecuteRequestDelegate.ExecuteIfBound(RequestContext, ConnectivityStatus, OutRequestId);
}


void UBeamAuthApi::CPP_RegisterCustomerRequest(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig,
                                               FBeamConnectivity& ConnectivityStatus,
                                               const FRegisterCustomerRequest& RequestData,
                                               const FOnRegisterCustomerFullResponse& Handler) const
{
	// AUTO-GENERATED...
	int64 OutRequestId;
	const auto Request = Backend->CreateRequest(OutRequestId, TargetRealm, RetryConfig, RequestData);
	// Binds the handler to the static response handler (pre-generated)	
	auto ResponseProcessor = Backend->MakeCodeRequestProcessor
		<FRegisterCustomerRequest, FRegisterCustomerResponse>
		(OutRequestId, RequestData, Handler);
	Request->OnProcessRequestComplete().BindLambda(ResponseProcessor);
	// Logic that actually talks to the backend --- if you pass in some other delegate, that means you can avoid making the actual back-end call.
	const auto RequestContext = FBeamRequestContext{RetryConfig, TargetRealm};
	Backend->ExecuteRequestDelegate.ExecuteIfBound(RequestContext, ConnectivityStatus, OutRequestId);
}

void UBeamAuthApi::CPP_MeRequest(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, const FBeamAuthToken& AuthToken,
                                 FBeamConnectivity& ConnectivityStatus,
                                 const FMeRequest& RequestData,
                                 const FOnMeFullResponse& Handler) const
{
	// AUTO-GENERATED...
	int64 OutRequestId;
	const auto Request = Backend->CreateAuthenticatedRequest(OutRequestId, TargetRealm, RetryConfig, AuthToken, RequestData);
	// Binds the handler to the static response handler (pre-generated)	
	auto ResponseProcessor = Backend->MakeAuthenticatedCodeRequestProcessor
		<FMeRequest, FMeResponse>
		(OutRequestId, TargetRealm, AuthToken, RequestData, Handler);
	Request->OnProcessRequestComplete().BindLambda(ResponseProcessor);
	// Logic that actually talks to the backend --- if you pass in some other delegate, that means you can avoid making the actual back-end call.
	const auto RequestContext = FBeamRequestContext{RetryConfig, TargetRealm};
	Backend->ExecuteRequestDelegate.ExecuteIfBound(RequestContext, ConnectivityStatus, OutRequestId);
}

/** RegisterCustomerRequest **/


void UBeamAuthApi::CPP_RegisterCustomerRequest(const FRegisterCustomerRequest& Request,
                                               const FOnRegisterCustomerFullResponse& Handler) const
{
	FBeamRetryConfig RetryConfig;
	Backend->GetRetryConfigForRequestType(FRegisterCustomerRequest::StaticStruct()->GetName(), RetryConfig);

	CPP_RegisterCustomerRequest(Backend->UnauthenticatedRequestsTargetRealm, RetryConfig,
	                            Backend->CurrentConnectivityStatus, Request, Handler);
}

void UBeamAuthApi::RegisterCustomerRequest(const FRegisterCustomerRequest& Request, const FOnRegisterCustomerSuccess& OnSuccess, const FOnRegisterCustomerError& OnError,
                                           const FOnRegisterCustomerComplete& OnComplete, int64& OutRequestId)
{
	// AUTO-GENERATED...	
	const auto TargetRealm = Backend->UnauthenticatedRequestsTargetRealm;
	FBeamRetryConfig RetryConfig;
	Backend->GetRetryConfigForRequestType(FRegisterCustomerRequest::StaticStruct()->GetName(), RetryConfig);
	BP_RegisterCustomerRequest(TargetRealm, RetryConfig, Request,
	                           Backend->CurrentConnectivityStatus,
	                           OnSuccess, OnError, OnComplete, OutRequestId);
}


void UBeamAuthApi::RegisterCustomerWithContext(const FBeamRequestContext& RequestContext, const FRegisterCustomerRequest& RequestData,
                                               const FOnRegisterCustomerSuccess& OnSuccess, const FOnRegisterCustomerError& OnError, const FOnRegisterCustomerComplete& OnComplete,
                                               int64& OutRequestId)
{
	// AUTO-GENERATED...	
	BP_RegisterCustomerRequest(RequestContext.Handle, RequestContext.RetryConfiguration, RequestData, Backend->CurrentConnectivityStatus, OnSuccess, OnError, OnComplete, OutRequestId);
}


/** MeRequest **/

void UBeamAuthApi::CPP_MeRequest(const FString& UserSlotId,
                                 const FMeRequest& Request,
                                 const FOnMeFullResponse& Handler) const
{
	// AUTO-GENERATED...
	FBeamRealmUser AuthenticatedUser;
	Backend->BeamUserSlots->GetUserDataAtSlot(UserSlotId, AuthenticatedUser);

	FBeamRetryConfig RetryConfig;
	Backend->GetRetryConfigForUserSlotAndRequestType(FMeRequest::StaticStruct()->GetName(), UserSlotId, RetryConfig);

	CPP_MeRequest(AuthenticatedUser.RealmHandle,
	              RetryConfig,
	              AuthenticatedUser.AuthToken,
	              Backend->CurrentConnectivityStatus,
	              Request,
	              Handler);
}

void UBeamAuthApi::MeRequest(const FString& UserSlotId, const FMeRequest& RequestData,
                             const FOnMeSuccess& OnSuccess, const FOnMeError& OnError, const FOnMeComplete& OnComplete,
                             int64& OutRequestId)
{
	// AUTO-GENERATED...
	FBeamRealmUser AuthenticatedUser;
	Backend->BeamUserSlots->GetUserDataAtSlot(UserSlotId, AuthenticatedUser);

	FBeamRetryConfig RetryConfig;
	Backend->GetRetryConfigForUserSlotAndRequestType(FMeRequest::StaticStruct()->GetName(), UserSlotId, RetryConfig);

	BP_MeRequest(AuthenticatedUser.RealmHandle, RetryConfig, AuthenticatedUser.AuthToken, RequestData, Backend->CurrentConnectivityStatus, OnSuccess, OnError, OnComplete, OutRequestId);
}

void UBeamAuthApi::MeRequestWithRetry(const FString& UserSlotId, const FBeamRetryConfig RetryConfig, const FMeRequest& RequestData,
                                      const FOnMeSuccess& OnSuccess, const FOnMeError& OnError, const FOnMeComplete& OnComplete,
                                      int64& OutRequestId)
{
	// AUTO-GENERATED...
	FBeamRealmUser authenticatedUser;
	Backend->BeamUserSlots->GetUserDataAtSlot(UserSlotId, authenticatedUser);

	BP_MeRequest(authenticatedUser.RealmHandle, RetryConfig, authenticatedUser.AuthToken,
	             RequestData, Backend->CurrentConnectivityStatus, OnSuccess, OnError, OnComplete, OutRequestId);
}
