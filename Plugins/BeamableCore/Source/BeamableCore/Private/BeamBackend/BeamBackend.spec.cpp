#include "BeamBackend.spec.h"

#include "Engine/Engine.h"
#include "Misc/AutomationTest.h"
#include "HttpModule.h"
#include "JsonObjectConverter.h"

#include "BeamBackend/BeamCustomRequests.h"
#include "BeamBackend/BeamBackend.h"
#include "BeamBackendTestCallbacks.h"

void FBeamBackendSpec::Define()
{
	Describe("Request/Response", [=, this]()
	{
		const FBeamRealmHandle FakeRealmHandle{FString("000000000000"), FString("DE_000000000000")};
		const FBeamRetryConfig FakeNoRetryConfig{{}, {}, 10, TArray<float>{0.5, 1}, 0};
		const FBeamRetryConfig FakeResponseCodeRetryConfig{{503}, {}, 10, TArray<float>{0.5, 1}, 1};
		const FBeamRetryConfig FakeErrorCodeRetryConfig{{}, {"ErrorCode"}, 10, TArray<float>{0.5, 1}, 1};
		const FBeamAuthToken FakeAuthToken{"AUTH_TOKEN", "REFRESH_TOKEN"};
		const FString FakeCustomHeader{"X-FAKE-HEADER"};
		const FString FakeCustomHeaderValue{"FakeHeaderValue"};

		BeforeEach([this]()
		{
			BeamBackendSystem = GEngine->GetEngineSubsystem<UBeamBackend>();

			// Prepare Back-end Tests with Blueprint-compatible mock handler
			Callbacks = NewObject<UBeamBackendTestCallbacks>();
			Callbacks->BeamBackend = BeamBackendSystem;
			Callbacks->Spec = this;

			RequestFuncUObject = BeamBackendSystem->ExecuteRequestDelegate.GetUObject();

#if USE_DELEGATE_TRYGETBOUNDFUNCTIONNAME
			RequestFuncName = BeamBackendSystem->ExecuteRequestDelegate.TryGetBoundFunctionName();
#endif			

			FHttpModule::Get().ToggleNullHttp(true);
		});

		AfterEach([this]()
		{
			// Clear callbacks object			
			Callbacks = nullptr;

			// Make sure that the execute request delegate is properly set up.
#if USE_DELEGATE_TRYGETBOUNDFUNCTIONNAME
			BeamBackendSystem->ExecuteRequestDelegate.BindUFunction(RequestFuncUObject, RequestFuncName);
#endif			
			FHttpModule::Get().ToggleNullHttp(false);

			// Reset the request id counter to 0 and all the state related to InFlight Requests back to initial state
			BeamBackendSystem->InFlightRequestId = -1;
			BeamBackendSystem->InFlightRequests.Reset();
			BeamBackendSystem->InFlightFailureCount.Reset();
			BeamBackendSystem->InFlightRequestContexts.Reset();
			BeamBackendSystem->InFlightRequestsCancelled.Reset();

			// Clear all Enqueued Retries
			BeamBackendSystem->EnqueuedRetries.Empty();
			BeamBackendSystem->InFlightProcessingRequests.Reset();

			// Clear all Global Handlers
			BeamBackendSystem->GlobalRequestErrorHandler.Clear();
			BeamBackendSystem->GlobalRequestErrorCodeHandler.Unbind();
		});

		It("should create an TUnrealRequestPtr WITHOUT authentication headers, correct parameters and retry configuration then discard it", [this, FakeCustomHeader, FakeCustomHeaderValue, FakeRealmHandle, FakeNoRetryConfig]()
		{
			// GET REQUESTS
			{
				UBeamMockGetRequest* FakeGetRequest = NewObject<UBeamMockGetRequest>();
				FakeGetRequest->CustomHeaders.Add(FakeCustomHeader, FakeCustomHeaderValue);

				int64 ReqId;
				const auto Request = BeamBackendSystem->CreateRequest(ReqId, FakeRealmHandle, FakeNoRetryConfig, FakeGetRequest);

				// Ensure all headers were created correctly
				TestTrue("Accept Header is Set correctly", Request->GetHeader(UBeamBackend::HEADER_ACCEPT) == UBeamBackend::HEADER_VALUE_ACCEPT_CONTENT_TYPE);
				TestTrue("Content Type Header is Set correctly", Request->GetHeader(UBeamBackend::HEADER_CONTENT_TYPE) == UBeamBackend::HEADER_VALUE_ACCEPT_CONTENT_TYPE);				
				TestTrue("Custom Header was added correctly", Request->GetHeader(FakeCustomHeader) == FakeCustomHeaderValue);

				const auto SetUpRetryConfig = BeamBackendSystem->InFlightRequestContexts.FindRef(ReqId).RetryConfiguration;
				TestTrue("InFlightRetryConfig was set up correctly for this request", SetUpRetryConfig == FakeNoRetryConfig);

				TestTrue("VERB is Set Correctly = 'GET'", Request->GetVerb() == TEXT("GET"));
				TestTrue("Route was set up correctly", Request->GetURL().Contains(TEXT("/fake/url")));

				// Test discarding unset data associated with InFlight Requests.
				BeamBackendSystem->CancelRequest(ReqId);
				TestTrue("ReqId no longer found in list of in flight requests", !BeamBackendSystem->InFlightRequests.Contains(ReqId));
				TestTrue("ReqId no longer found in list of in flight processing requests", !BeamBackendSystem->InFlightProcessingRequests.Contains(ReqId));
				TestTrue("ReqId no longer found in list of in flight retry configurations", !BeamBackendSystem->InFlightRequestContexts.Contains(ReqId));
				TestTrue("ReqId no longer found in list of in flight failure counts", !BeamBackendSystem->InFlightFailureCount.Contains(ReqId));
				TestTrue("ReqId no longer found in list of cancelled in flight requests", !BeamBackendSystem->InFlightRequestsCancelled.Contains(ReqId));

				// Clean up FakeGetRequest
				FakeGetRequest->MarkAsGarbage();
			}

			// POST REQUESTS
			{
				UBeamMockPostRequest* FakePostRequest = NewObject<UBeamMockPostRequest>();
				FakePostRequest->Body = NewObject<UBeamMockBody>(FakePostRequest);
				FakePostRequest->Body->FakeInt = 10;

				int64 ReqId;
				const auto Request = BeamBackendSystem->CreateRequest(ReqId, FakeRealmHandle, FakeNoRetryConfig, FakePostRequest);

				// Ensure all headers were created correctly
				TestTrue("Accept Header is Set correctly", Request->GetHeader(UBeamBackend::HEADER_ACCEPT) == UBeamBackend::HEADER_VALUE_ACCEPT_CONTENT_TYPE);
				TestTrue("Content Type Header is Set correctly", Request->GetHeader(UBeamBackend::HEADER_CONTENT_TYPE) == UBeamBackend::HEADER_VALUE_ACCEPT_CONTENT_TYPE);				

				const auto SetUpRetryConfig = BeamBackendSystem->InFlightRequestContexts.FindRef(ReqId).RetryConfiguration;
				TestEqual("InFlightRetryConfig was set up correctly for this request", SetUpRetryConfig, FakeNoRetryConfig);

				TestTrue("VERB is Set Correctly = 'POST'", Request->GetVerb() == TEXT("POST"));
				TestTrue("Route was set up correctly", Request->GetURL().Contains(TEXT("/fake/url")));

				const auto ContentUTF8 = reinterpret_cast<const UTF8CHAR*>(Request->GetContent().GetData());
				const auto Content = FString(TStringConversion<FUTF8ToTCHAR_Convert>(ContentUTF8, Request->GetContent().Num()));				
				TestEqual("Body was set up correctly", Content, TEXT(R"({"fake_int":10})"));

				// Test discarding unset data associated with InFlight Requests.
				BeamBackendSystem->CancelRequest(ReqId);
				TestTrue("ReqId no longer found in list of in flight requests", !BeamBackendSystem->InFlightRequests.Contains(ReqId));
				TestTrue("ReqId no longer found in list of in flight processing requests", !BeamBackendSystem->InFlightProcessingRequests.Contains(ReqId));
				TestTrue("ReqId no longer found in list of in flight retry configurations", !BeamBackendSystem->InFlightRequestContexts.Contains(ReqId));
				TestTrue("ReqId no longer found in list of in flight failure counts", !BeamBackendSystem->InFlightFailureCount.Contains(ReqId));
				TestTrue("ReqId no longer found in list of cancelled in flight requests", !BeamBackendSystem->InFlightRequestsCancelled.Contains(ReqId));

				// Clean up object
				FakePostRequest->MarkAsGarbage();
			}
		});

		It("should create an TUnrealRequestPtr WITH authentication headers, correct parameters and retry configuration then discard it", [this, FakeRealmHandle, FakeNoRetryConfig, FakeAuthToken]()
		{
			// GET REQUESTS
			{
				UBeamMockGetRequest* FakeGetRequest = NewObject<UBeamMockGetRequest>();
				int64 ReqId;
				const auto Request = BeamBackendSystem->CreateAuthenticatedRequest(ReqId, FakeRealmHandle, FakeNoRetryConfig, FakeAuthToken, FakeGetRequest);

				// Ensure all headers were created correctly
				TestTrue("Accept Header is Set correctly", Request->GetHeader(UBeamBackend::HEADER_ACCEPT) == UBeamBackend::HEADER_VALUE_ACCEPT_CONTENT_TYPE);
				TestTrue("Content Type Header is Set correctly", Request->GetHeader(UBeamBackend::HEADER_CONTENT_TYPE) == UBeamBackend::HEADER_VALUE_ACCEPT_CONTENT_TYPE);

				TestTrue("Authorization Header is Set correctly",
				         Request->GetHeader(UBeamBackend::HEADER_AUTHORIZATION) == FString::Format(*UBeamBackend::HEADER_VALUE_AUTHORIZATION, {FakeAuthToken.AccessToken}));
				TestTrue("Request Scope Header is Set correctly",
				         Request->GetHeader(UBeamBackend::HEADER_REQUEST_SCOPE) == FString::Format(TEXT("{0}.{1}"), {FakeRealmHandle.Cid.AsString, FakeRealmHandle.Pid.AsString}));

				const auto SetUpRetryConfig = BeamBackendSystem->InFlightRequestContexts.FindRef(ReqId).RetryConfiguration;
				TestTrue("InFlightRetryConfig was set up correctly for this request", SetUpRetryConfig == FakeNoRetryConfig);

				TestTrue("VERB is Set Correctly = 'GET'", Request->GetVerb() == TEXT("GET"));
				TestTrue("Route was set up correctly", Request->GetURL().Contains(TEXT("/fake/url")));

				// Test discarding unset data associated with InFlight Requests.
				BeamBackendSystem->CancelRequest(ReqId);
				TestTrue("ReqId no longer found in list of in flight requests", !BeamBackendSystem->InFlightRequests.Contains(ReqId));
				TestTrue("ReqId no longer found in list of in flight processing requests", !BeamBackendSystem->InFlightProcessingRequests.Contains(ReqId));
				TestTrue("ReqId no longer found in list of in flight retry configurations", !BeamBackendSystem->InFlightRequestContexts.Contains(ReqId));
				TestTrue("ReqId no longer found in list of in flight failure counts", !BeamBackendSystem->InFlightFailureCount.Contains(ReqId));
				TestTrue("ReqId no longer found in list of cancelled in flight requests", !BeamBackendSystem->InFlightRequestsCancelled.Contains(ReqId));

				FakeGetRequest->MarkAsGarbage();
			}

			// POST REQUESTS
			{
				UBeamMockPostRequest* FakePostRequest = NewObject<UBeamMockPostRequest>();
				FakePostRequest->Body = NewObject<UBeamMockBody>(FakePostRequest);
				FakePostRequest->Body->FakeInt = 10;

				int64 ReqId;
				const auto Request = BeamBackendSystem->CreateAuthenticatedRequest(ReqId, FakeRealmHandle, FakeNoRetryConfig, FakeAuthToken, FakePostRequest);

				// Ensure all headers were created correctly
				TestTrue("Accept Header is Set correctly", Request->GetHeader(UBeamBackend::HEADER_ACCEPT) == UBeamBackend::HEADER_VALUE_ACCEPT_CONTENT_TYPE);
				TestTrue("Content Type Header is Set correctly", Request->GetHeader(UBeamBackend::HEADER_CONTENT_TYPE) == UBeamBackend::HEADER_VALUE_ACCEPT_CONTENT_TYPE);

				TestTrue("Authorization Header is Set correctly",
				         Request->GetHeader(UBeamBackend::HEADER_AUTHORIZATION) == FString::Format(*UBeamBackend::HEADER_VALUE_AUTHORIZATION, {FakeAuthToken.AccessToken}));
				TestTrue("Request Scope Header is Set correctly",
				         Request->GetHeader(UBeamBackend::HEADER_REQUEST_SCOPE) == FString::Format(TEXT("{0}.{1}"), {FakeRealmHandle.Cid.AsString, FakeRealmHandle.Pid.AsString}));
				

				const auto SetUpRetryConfig = BeamBackendSystem->InFlightRequestContexts.FindRef(ReqId).RetryConfiguration;
				TestEqual("InFlightRetryConfig was set up correctly for this request", SetUpRetryConfig, FakeNoRetryConfig);

				TestTrue("VERB is Set Correctly = 'POST'", Request->GetVerb() == TEXT("POST"));
				TestTrue("Route was set up correctly", Request->GetURL().Contains(TEXT("/fake/url")));

				const auto ContentUTF8 = reinterpret_cast<const UTF8CHAR*>(Request->GetContent().GetData());
				const auto Content = FString(TStringConversion<FUTF8ToTCHAR_Convert>(ContentUTF8, Request->GetContent().Num()));				
				TestEqual("Body was set up correctly", Content, TEXT(R"({"fake_int":10})"));
				
				// Test discarding unset data associated with InFlight Requests.
				BeamBackendSystem->CancelRequest(ReqId);
				TestTrue("ReqId no longer found in list of in flight requests", !BeamBackendSystem->InFlightRequests.Contains(ReqId));
				TestTrue("ReqId no longer found in list of in flight processing requests", !BeamBackendSystem->InFlightProcessingRequests.Contains(ReqId));
				TestTrue("ReqId no longer found in list of in flight retry configurations", !BeamBackendSystem->InFlightRequestContexts.Contains(ReqId));
				TestTrue("ReqId no longer found in list of in flight failure counts", !BeamBackendSystem->InFlightFailureCount.Contains(ReqId));
				TestTrue("ReqId no longer found in list of cancelled in flight requests", !BeamBackendSystem->InFlightRequestsCancelled.Contains(ReqId));

				FakePostRequest->MarkAsGarbage();
			}
		});

		It("should invoke the Success Handlers with the correct data when received a 200 response code", [this, FakeRealmHandle, FakeNoRetryConfig, FakeAuthToken]()
		{
			UBeamMockGetRequest* FakeRequestData = NewObject<UBeamMockGetRequest>();
			const int ExpectedFakeInt = 10;
			const FString ResponseBody(FString::Format(TEXT("{\"fake_int\":{0}}"), {ExpectedFakeInt}));

			// Un-Authenticated BP Handler
			{
				int64 ReqId;
				const auto Request = BeamBackendSystem->CreateRequest(ReqId, FakeRealmHandle, FakeNoRetryConfig, FakeRequestData);

				Callbacks->ExpectedReqId = ReqId;
				Callbacks->ExpectedSuccessResponse = ExpectedFakeInt;

				FOnMockSuccess ResponseHandler;
				ResponseHandler.BindUFunction(Callbacks, FName(TEXT("MockSuccessCallback_Expected")));

				FOnMockError ResponseHandlerError;
				ResponseHandlerError.BindUFunction(Callbacks, FName(TEXT("MockErrorCallback_Fail")));

				FOnMockComplete ResponseHandlerComplete;
				ResponseHandlerComplete.BindUFunction(Callbacks, FName(TEXT("MockCompleteCallback_Expected")));

				// This should clean up the created request's data
				BeamBackendSystem->ProcessBlueprintRequest<UBeamMockGetRequest, UBeamMockGetRequestResponse>
					(200, ResponseBody, TUnrealRequestStatus::Succeeded, ReqId, FakeRequestData, ResponseHandler, ResponseHandlerError, ResponseHandlerComplete);				
				TestTrue("Flagged Request as Completed", BeamBackendSystem->InFlightRequestContexts.FindRef(ReqId).BeamStatus == AS_Completed);
			}

			// Authenticated BP Handler
			{
				int64 ReqId;
				const auto Request = BeamBackendSystem->CreateAuthenticatedRequest(ReqId, FakeRealmHandle, FakeNoRetryConfig, FakeAuthToken, FakeRequestData);

				Callbacks->ExpectedReqId = ReqId;
				Callbacks->ExpectedSuccessResponse = ExpectedFakeInt;

				FOnMockSuccess ResponseHandler;
				ResponseHandler.BindUFunction(Callbacks, FName(TEXT("MockSuccessCallback_Expected")));

				FOnMockError ResponseHandlerError;
				ResponseHandlerError.BindUFunction(Callbacks, FName(TEXT("MockErrorCallback_Fail")));

				FOnMockComplete ResponseHandlerComplete;
				ResponseHandlerComplete.BindUFunction(Callbacks, FName(TEXT("MockCompleteCallback_Expected")));

				// This should clean up the created request's data
				BeamBackendSystem->ProcessAuthenticatedBlueprintRequest<UBeamMockGetRequest, UBeamMockGetRequestResponse>
					(200, ResponseBody, TUnrealRequestStatus::Succeeded, ReqId, FakeRealmHandle, FakeAuthToken, FakeRequestData, ResponseHandler, ResponseHandlerError, ResponseHandlerComplete);				
				TestTrue("Flagged Request as Completed", BeamBackendSystem->InFlightRequestContexts.FindRef(ReqId).BeamStatus == AS_Completed);
			}

			// Un-Authenticated Code Handler 
			{
				int64 ReqId;
				const auto Request = BeamBackendSystem->CreateRequest(ReqId, FakeRealmHandle, FakeNoRetryConfig, FakeRequestData);

				FOnMockFullResponse ResponseHandler;
				ResponseHandler.BindLambda([this, ReqId](FBeamFullResponse<UBeamMockGetRequest*, UBeamMockGetRequestResponse*> BeamFullResponse)
				{
					TestTrue("State was Success", BeamFullResponse.State == EBeamFullResponseState::RS_Success);

					TestTrue("Request Id was correctly forwarded", BeamFullResponse.Context.RequestId == ReqId);
					TestTrue("Attempt Number was correctly forwarded", BeamFullResponse.AttemptNumber == 0);
					TestTrue("Response Code was correctly forwarded", BeamFullResponse.Context.ResponseCode == 200);
					TestTrue("Response Body was correctly forwarded", BeamFullResponse.SuccessData->FakeInt == ExpectedFakeInt);
				});

				// This should clean up the created request's data
				BeamBackendSystem->ProcessCodeRequest<UBeamMockGetRequest, UBeamMockGetRequestResponse>(200, ResponseBody, TUnrealRequestStatus::Succeeded, ReqId, FakeRequestData, ResponseHandler);				
				TestTrue("Flagged Request as Completed", BeamBackendSystem->InFlightRequestContexts.FindRef(ReqId).BeamStatus == AS_Completed);
			}

			// Authenticated Code Handler
			{
				int64 ReqId;
				const auto Request = BeamBackendSystem->CreateAuthenticatedRequest(ReqId, FakeRealmHandle, FakeNoRetryConfig, FakeAuthToken, FakeRequestData);

				FOnMockFullResponse ResponseHandler;
				ResponseHandler.BindLambda([this, ReqId](FBeamFullResponse<UBeamMockGetRequest*, UBeamMockGetRequestResponse*> BeamFullResponse)
				{
					TestTrue("State was Success", BeamFullResponse.State == EBeamFullResponseState::RS_Success);

					TestTrue("Request Id was correctly forwarded", BeamFullResponse.Context.RequestId == ReqId);
					TestTrue("Attempt Number was correctly forwarded", BeamFullResponse.AttemptNumber == 0);
					TestTrue("Response Code was correctly forwarded", BeamFullResponse.Context.ResponseCode == 200);
					TestTrue("Response Body was correctly forwarded", BeamFullResponse.SuccessData->FakeInt == ExpectedFakeInt);
				});

				// This should clean up the created request's data
				BeamBackendSystem->ProcessAuthenticatedCodeRequest
					<UBeamMockGetRequest, UBeamMockGetRequestResponse>
					(200, ResponseBody, TUnrealRequestStatus::Succeeded, ReqId, FakeRealmHandle, FakeAuthToken, FakeRequestData, ResponseHandler);				
				TestTrue("Flagged Request as Completed", BeamBackendSystem->InFlightRequestContexts.FindRef(ReqId).BeamStatus == AS_Completed);
			}

			// Clean Up Fake Request Data
			FakeRequestData->MarkAsGarbage();
		});

		It("should invoke the Error Handlers with the correct data when received an error response code", [this, FakeRealmHandle, FakeNoRetryConfig, FakeAuthToken]()
		{
			// We expect errors if we are always logging errors --- otherwise, we expect no errors to be logged since we are binding callbacks and logging is a fallback
			if (BeamBackendSystem->AlwaysLogErrorResponses)
				AddExpectedError(TEXT("Beamable Request Failed"), EAutomationExpectedErrorFlags::Contains, 4);

			UBeamMockGetRequest* FakeRequest = NewObject<UBeamMockGetRequest>();
			const FBeamErrorResponse Error = FBeamErrorResponse{500, TEXT("Internal Server Error"), TEXT("fake basic"), TEXT("Fake Error Message")};
			FString ResponseBody;
			FJsonObjectConverter::UStructToJsonObjectString(FBeamErrorResponse::StaticStruct(), &Error, ResponseBody);

			// Un-Authenticated BP Handler
			{
				int64 ReqId;
				const auto Request = BeamBackendSystem->CreateRequest(ReqId, FakeRealmHandle, FakeNoRetryConfig, FakeRequest);

				Callbacks->ExpectedReqId = ReqId;
				Callbacks->ExpectedErrorFailureCount = 1;
				Callbacks->ExpectedErrorResponseStatus = Error.status;
				Callbacks->ExpectedErrorResponseError = Error.error;
				Callbacks->ExpectedErrorResponseService = Error.service;
				Callbacks->ExpectedErrorResponseMessage = Error.message;

				FOnMockSuccess ResponseHandler;
				ResponseHandler.BindUFunction(Callbacks, FName(TEXT("MockSuccessCallback_Fail")));

				FOnMockError ResponseHandlerError;
				ResponseHandlerError.BindUFunction(Callbacks, FName(TEXT("MockErrorCallback_Expected")));

				FOnMockComplete ResponseHandlerComplete;
				ResponseHandlerComplete.BindUFunction(Callbacks, FName(TEXT("MockCompleteCallback_Expected")));


				// This should clean up the created request's data
				BeamBackendSystem->ProcessBlueprintRequest<UBeamMockGetRequest, UBeamMockGetRequestResponse>
					(500, ResponseBody, TUnrealRequestStatus::Failed, ReqId, FakeRequest, ResponseHandler, ResponseHandlerError, ResponseHandlerComplete);
				TestTrue("Flagged Request as Completed", BeamBackendSystem->InFlightRequestContexts.FindRef(ReqId).BeamStatus == AS_Completed);
			}

			// Authenticated BP Handler
			{
				int64 ReqId;
				const auto Request = BeamBackendSystem->CreateAuthenticatedRequest(ReqId, FakeRealmHandle, FakeNoRetryConfig, FakeAuthToken, FakeRequest);

				Callbacks->ExpectedReqId = ReqId;
				Callbacks->ExpectedErrorFailureCount = 1;
				Callbacks->ExpectedErrorResponseStatus = Error.status;
				Callbacks->ExpectedErrorResponseError = Error.error;
				Callbacks->ExpectedErrorResponseService = Error.service;
				Callbacks->ExpectedErrorResponseMessage = Error.message;

				FOnMockSuccess ResponseHandler;
				ResponseHandler.BindUFunction(Callbacks, FName(TEXT("MockSuccessCallback_Fail")));

				FOnMockError ResponseHandlerError;
				ResponseHandlerError.BindUFunction(Callbacks, FName(TEXT("MockErrorCallback_Expected")));

				FOnMockComplete ResponseHandlerComplete;
				ResponseHandlerComplete.BindUFunction(Callbacks, FName(TEXT("MockCompleteCallback_Expected")));

				// This should clean up the created request's data
				BeamBackendSystem->ProcessAuthenticatedBlueprintRequest<UBeamMockGetRequest, UBeamMockGetRequestResponse>
					(500, ResponseBody, TUnrealRequestStatus::Failed, ReqId, FakeRealmHandle, FakeAuthToken, FakeRequest, ResponseHandler, ResponseHandlerError, ResponseHandlerComplete);
				TestTrue("Flagged Request as Completed", BeamBackendSystem->InFlightRequestContexts.FindRef(ReqId).BeamStatus == AS_Completed);
			}

			// Un-Authenticated Code Handler 
			{
				int64 ReqId;
				const auto Request = BeamBackendSystem->CreateRequest(ReqId, FakeRealmHandle, FakeNoRetryConfig, FakeRequest);

				Callbacks->ExpectedReqId = ReqId;
				Callbacks->ExpectedErrorFailureCount = 1;
				Callbacks->ExpectedErrorResponseStatus = Error.status;
				Callbacks->ExpectedErrorResponseError = Error.error;
				Callbacks->ExpectedErrorResponseService = Error.service;
				Callbacks->ExpectedErrorResponseMessage = Error.message;

				FOnMockFullResponse ResponseHandler;
				ResponseHandler.BindLambda([this](FBeamFullResponse<UBeamMockGetRequest*, UBeamMockGetRequestResponse*> BeamFullResponse)
				{
					TestTrue("State was Error", BeamFullResponse.State == EBeamFullResponseState::RS_Error);
					Callbacks->MockErrorCallback_Expected(BeamFullResponse.Context, BeamFullResponse.RequestData, BeamFullResponse.ErrorData);
				});

				// This should clean up the created request's data
				BeamBackendSystem->ProcessCodeRequest(500, ResponseBody, TUnrealRequestStatus::Failed, ReqId, FakeRequest, ResponseHandler);
				TestTrue("Flagged Request as Completed", BeamBackendSystem->InFlightRequestContexts.FindRef(ReqId).BeamStatus == AS_Completed);
			}

			// Authenticated Code Handler
			{
				int64 ReqId;
				const auto Request = BeamBackendSystem->CreateAuthenticatedRequest(ReqId, FakeRealmHandle, FakeNoRetryConfig, FakeAuthToken, FakeRequest);

				Callbacks->ExpectedReqId = ReqId;
				Callbacks->ExpectedErrorFailureCount = 1;
				Callbacks->ExpectedErrorResponseStatus = Error.status;
				Callbacks->ExpectedErrorResponseError = Error.error;
				Callbacks->ExpectedErrorResponseService = Error.service;
				Callbacks->ExpectedErrorResponseMessage = Error.message;

				FOnMockFullResponse ResponseHandler;
				ResponseHandler.BindLambda([this](FBeamFullResponse<UBeamMockGetRequest*, UBeamMockGetRequestResponse*> BeamFullResponse)
				{
					TestTrue("State was Error", BeamFullResponse.State == EBeamFullResponseState::RS_Error);
					Callbacks->MockErrorCallback_Expected(BeamFullResponse.Context, BeamFullResponse.RequestData, BeamFullResponse.ErrorData);
				});

				// This should clean up the created request's data
				BeamBackendSystem->ProcessAuthenticatedCodeRequest(500, ResponseBody, TUnrealRequestStatus::Failed, ReqId, FakeRealmHandle, FakeAuthToken, FakeRequest, ResponseHandler);
				TestTrue("Flagged Request as Completed", BeamBackendSystem->InFlightRequestContexts.FindRef(ReqId).BeamStatus == AS_Completed);
			}

			// Clean up Fake Request
			FakeRequest->MarkAsGarbage();
		});

		It("should invoke the Error Handlers with the correct data when received an error response code AND Enqueue Request for Retry", [this, FakeRealmHandle, FakeResponseCodeRetryConfig, FakeAuthToken]()
		{
			UBeamMockGetRequest* FakeRequest = NewObject<UBeamMockGetRequest>();
			const FBeamErrorResponse Error = FBeamErrorResponse{503, TEXT("Internal Server Error"), TEXT("fake basic"), TEXT("Fake Error Message")};
			FString ResponseBody;
			FJsonObjectConverter::UStructToJsonObjectString(FBeamErrorResponse::StaticStruct(), &Error, ResponseBody);

			// We expect errors if we are always logging errors --- otherwise, we expect no errors to be logged since we are binding callbacks and logging is a fallback
			if (BeamBackendSystem->AlwaysLogErrorResponses)
				AddExpectedError(TEXT("Beamable Request Failed"), EAutomationExpectedErrorFlags::Contains, 0);

			const auto ReceivedResponseCode = Error.status;
			// Un-Authenticated BP Handler
			{
				int64 ReqId;
				const auto Request = BeamBackendSystem->CreateRequest(ReqId, FakeRealmHandle, FakeResponseCodeRetryConfig, FakeRequest);

				Callbacks->ExpectedReqId = ReqId;
				Callbacks->ExpectedErrorFailureCount = 1;
				Callbacks->ExpectedErrorResponseStatus = Error.status;
				Callbacks->ExpectedErrorResponseError = Error.error;
				Callbacks->ExpectedErrorResponseService = Error.service;
				Callbacks->ExpectedErrorResponseMessage = Error.message;

				FOnMockSuccess ResponseHandler;
				ResponseHandler.BindUFunction(Callbacks, FName(TEXT("MockSuccessCallback_Fail")));

				FOnMockError ResponseHandlerError;
				ResponseHandlerError.BindUFunction(Callbacks, FName(TEXT("MockErrorCallback_Expected")));

				FOnMockComplete ResponseHandlerComplete;
				ResponseHandlerComplete.BindUFunction(Callbacks, FName(TEXT("MockCompleteCallback_Expected")));


				// This should clean up the created request's data
				BeamBackendSystem->ProcessBlueprintRequest<UBeamMockGetRequest, UBeamMockGetRequestResponse>
					(ReceivedResponseCode, ResponseBody, TUnrealRequestStatus::Failed, ReqId, FakeRequest, ResponseHandler, ResponseHandlerError, ResponseHandlerComplete);

				// Assert that the request was correctly enqueued for work
				FRequestToRetry RetryReq;
				TestTrue("Test that the Retry was enqueued", BeamBackendSystem->EnqueuedRetries.Dequeue(RetryReq));
				TestTrue("Enqueued Retry's Request Id is equal", RetryReq.RequestId == ReqId);
				TestTrue("Enqueued Retry's IsBlueprint is on", RetryReq.IsBlueprintCompatible == 1);
			}


			// Un-Authenticated Code Handler 
			{
				int64 ReqId;
				const auto Request = BeamBackendSystem->CreateRequest(ReqId, FakeRealmHandle, FakeResponseCodeRetryConfig, FakeRequest);

				Callbacks->ExpectedReqId = ReqId;
				Callbacks->ExpectedErrorFailureCount = 1;
				Callbacks->ExpectedErrorResponseStatus = Error.status;
				Callbacks->ExpectedErrorResponseError = Error.error;
				Callbacks->ExpectedErrorResponseService = Error.service;
				Callbacks->ExpectedErrorResponseMessage = Error.message;

				FOnMockFullResponse ResponseHandler;
				ResponseHandler.BindLambda([this](FBeamFullResponse<UBeamMockGetRequest*, UBeamMockGetRequestResponse*> BeamFullResponse)
				{
					TestTrue("State was Retrying", BeamFullResponse.State == EBeamFullResponseState::RS_Retrying);
					Callbacks->MockErrorCallback_Expected(BeamFullResponse.Context, BeamFullResponse.RequestData, BeamFullResponse.ErrorData);
				});

				// This should clean up the created request's data
				BeamBackendSystem->ProcessCodeRequest(ReceivedResponseCode, ResponseBody, TUnrealRequestStatus::Failed, ReqId, FakeRequest, ResponseHandler);

				// Assert that the request was correctly enqueued for work
				FRequestToRetry RetryReq;
				TestTrue("Test that the Retry was enqueued", BeamBackendSystem->EnqueuedRetries.Dequeue(RetryReq));
				TestTrue("Enqueued Retry's Request Id is equal", RetryReq.RequestId == ReqId);
				TestTrue("Enqueued Retry's IsBlueprint is off", RetryReq.IsBlueprintCompatible == 0);
			}


			// Authenticated BP Handler
			{
				int64 ReqId;
				const auto Request = BeamBackendSystem->CreateAuthenticatedRequest(ReqId, FakeRealmHandle, FakeResponseCodeRetryConfig, FakeAuthToken, FakeRequest);

				Callbacks->ExpectedReqId = ReqId;
				// We expect to fail transparently for the automatic re-auth case.
				Callbacks->ExpectedErrorFailureCount = 1;
				Callbacks->ExpectedErrorResponseStatus = Error.status;
				Callbacks->ExpectedErrorResponseError = Error.error;
				Callbacks->ExpectedErrorResponseService = Error.service;
				Callbacks->ExpectedErrorResponseMessage = Error.message;

				FOnMockSuccess ResponseHandler;
				ResponseHandler.BindUFunction(Callbacks, FName(TEXT("MockSuccessCallback_Fail")));

				FOnMockError ResponseHandlerError;
				ResponseHandlerError.BindUFunction(Callbacks, FName(TEXT("MockErrorCallback_Expected")));

				FOnMockComplete ResponseHandlerComplete;
				ResponseHandlerComplete.BindUFunction(Callbacks, FName(TEXT("MockCompleteCallback_Expected")));

				// This should clean up the created request's data
				BeamBackendSystem->ProcessAuthenticatedBlueprintRequest<UBeamMockGetRequest, UBeamMockGetRequestResponse>
				(ReceivedResponseCode, ResponseBody, TUnrealRequestStatus::Failed, ReqId, FakeRealmHandle, FakeAuthToken, FakeRequest, ResponseHandler, ResponseHandlerError,
				 ResponseHandlerComplete);

				// Assert that the request was correctly enqueued for work
				FRequestToRetry RetryReq;
				TestTrue("Test that the Retry was enqueued", BeamBackendSystem->EnqueuedRetries.Dequeue(RetryReq));
				TestTrue("Enqueued Retry's Request Id is equal", RetryReq.RequestId == ReqId);
				TestTrue("Enqueued Retry's Realm Handle is the same", RetryReq.RealmHandle == FakeRealmHandle);
				TestTrue("Enqueued Retry's AuthToken is the same", RetryReq.AuthToken == FakeAuthToken);
				TestTrue("Enqueued Retry's IsBlueprint is on", RetryReq.IsBlueprintCompatible == 1);
			}

			// Authenticated Code Handler 
			{
				int64 ReqId;
				const auto Request = BeamBackendSystem->CreateAuthenticatedRequest(ReqId, FakeRealmHandle, FakeResponseCodeRetryConfig, FakeAuthToken, FakeRequest);

				Callbacks->ExpectedReqId = ReqId;
				// We expect to fail transparently for the automatic re-auth case.
				Callbacks->ExpectedErrorFailureCount = 1;
				Callbacks->ExpectedErrorResponseStatus = Error.status;
				Callbacks->ExpectedErrorResponseError = Error.error;
				Callbacks->ExpectedErrorResponseService = Error.service;
				Callbacks->ExpectedErrorResponseMessage = Error.message;

				FOnMockFullResponse ResponseHandler;
				ResponseHandler.BindLambda([this](FBeamFullResponse<UBeamMockGetRequest*, UBeamMockGetRequestResponse*> BeamFullResponse)
				{
					TestTrue("State was Retrying", BeamFullResponse.State == EBeamFullResponseState::RS_Retrying);
					Callbacks->MockErrorCallback_Expected(BeamFullResponse.Context, BeamFullResponse.RequestData, BeamFullResponse.ErrorData);
				});

				// This should clean up the created request's data
				BeamBackendSystem->ProcessAuthenticatedCodeRequest(ReceivedResponseCode, ResponseBody, TUnrealRequestStatus::Failed, ReqId, FakeRealmHandle, FakeAuthToken, FakeRequest,
				                                                   ResponseHandler);

				// Assert that the request was correctly enqueued for work
				FRequestToRetry RetryReq;
				TestTrue("Test that the Retry was enqueued", BeamBackendSystem->EnqueuedRetries.Dequeue(RetryReq));
				TestTrue("Enqueued Retry's Request Id is equal", RetryReq.RequestId == ReqId);
				TestTrue("Enqueued Retry's Realm Handle is the same", RetryReq.RealmHandle == FakeRealmHandle);
				TestTrue("Enqueued Retry's AuthToken is the same", RetryReq.AuthToken == FakeAuthToken);
				TestTrue("Enqueued Retry's IsBlueprint is off", RetryReq.IsBlueprintCompatible == 0);
			}

			// Clean up fake request
			FakeRequest->MarkAsGarbage();
		});

		It("should invoke the Error Handlers with the correct data when received an error response code AND Enqueue Request for Re-Auth based retry", [this, FakeRealmHandle, FakeNoRetryConfig, FakeAuthToken]()
		{
			UBeamMockGetRequest* FakeRequest = NewObject<UBeamMockGetRequest>();
			const FBeamErrorResponse Error = FBeamErrorResponse{401, UBeamBackend::AUTH_ERROR_CODE_RETRY_ALLOWED[0], TEXT("fake basic"), TEXT("Fake Error Message")};
			FString ResponseBody;
			FJsonObjectConverter::UStructToJsonObjectString(FBeamErrorResponse::StaticStruct(), &Error, ResponseBody);

			const auto ReceivedResponseCode = Error.status;

			// Authenticated BP Handler
			{
				int64 ReqId;
				const auto Request = BeamBackendSystem->CreateAuthenticatedRequest(ReqId, FakeRealmHandle, FakeNoRetryConfig, FakeAuthToken, FakeRequest);

				Callbacks->ExpectedReqId = ReqId;
				// We expect to fail transparently for the automatic re-auth case.
				Callbacks->ExpectedErrorFailureCount = 0;
				Callbacks->ExpectedErrorResponseStatus = Error.status;
				Callbacks->ExpectedErrorResponseError = Error.error;
				Callbacks->ExpectedErrorResponseService = Error.service;
				Callbacks->ExpectedErrorResponseMessage = Error.message;

				FOnMockSuccess ResponseHandler;
				ResponseHandler.BindUFunction(Callbacks, FName(TEXT("MockSuccessCallback_Fail")));

				FOnMockError ResponseHandlerError;
				ResponseHandlerError.BindUFunction(Callbacks, FName(TEXT("MockErrorCallback_Fail")));

				FOnMockComplete ResponseHandlerComplete;
				ResponseHandlerComplete.BindUFunction(Callbacks, FName(TEXT("MockCompleteCallback_Expected")));

				// This should clean up the created request's data
				BeamBackendSystem->ProcessAuthenticatedBlueprintRequest<UBeamMockGetRequest, UBeamMockGetRequestResponse>
				(ReceivedResponseCode, ResponseBody, TUnrealRequestStatus::Failed, ReqId, FakeRealmHandle, FakeAuthToken, FakeRequest, ResponseHandler, ResponseHandlerError,
				 ResponseHandlerComplete);

				// Assert that the request was correctly enqueued for work
				FRequestToRetry RetryReq;
				TestTrue("Test that the Retry was enqueued", BeamBackendSystem->EnqueuedRetries.Dequeue(RetryReq));
				TestEqual("Enqueued Retry's Request Id is equal", RetryReq.RequestId, ReqId);
				TestEqual("Enqueued Retry's Realm Handle is the same", RetryReq.RealmHandle, FakeRealmHandle);
				TestEqual("Enqueued Retry's AuthToken is the same", RetryReq.AuthToken, FakeAuthToken);
				TestEqual("Enqueued Retry's IsBlueprint is on", RetryReq.IsBlueprintCompatible, 1);
				TestEqual("Test that the Retry was enqueued but with no failure count", BeamBackendSystem->InFlightFailureCount[ReqId], Callbacks->ExpectedErrorFailureCount);
			}

			// Authenticated Code Handler 
			{
				int64 ReqId;
				const auto Request = BeamBackendSystem->CreateAuthenticatedRequest(ReqId, FakeRealmHandle, FakeNoRetryConfig, FakeAuthToken, FakeRequest);

				Callbacks->ExpectedReqId = ReqId;
				// We expect to fail transparently for the automatic re-auth case.
				Callbacks->ExpectedErrorFailureCount = 0;
				Callbacks->ExpectedErrorResponseStatus = Error.status;
				Callbacks->ExpectedErrorResponseError = Error.error;
				Callbacks->ExpectedErrorResponseService = Error.service;
				Callbacks->ExpectedErrorResponseMessage = Error.message;

				FOnMockFullResponse ResponseHandler;
				ResponseHandler.BindLambda([this](FBeamFullResponse<UBeamMockGetRequest*, UBeamMockGetRequestResponse*> BeamFullResponse)
				{
					TestTrue("Callback was not called", false);
				});

				// This should clean up the created request's data
				BeamBackendSystem->ProcessAuthenticatedCodeRequest(ReceivedResponseCode, ResponseBody, TUnrealRequestStatus::Failed, ReqId, FakeRealmHandle, FakeAuthToken, FakeRequest,
				                                                   ResponseHandler);

				// Assert that the request was correctly enqueued for work
				FRequestToRetry RetryReq;
				TestTrue("Test that the Retry was enqueued", BeamBackendSystem->EnqueuedRetries.Dequeue(RetryReq));
				TestEqual("Enqueued Retry's Request Id is equal", RetryReq.RequestId, ReqId);
				TestEqual("Enqueued Retry's Realm Handle is the same", RetryReq.RealmHandle, FakeRealmHandle);
				TestEqual("Enqueued Retry's AuthToken is the same", RetryReq.AuthToken, FakeAuthToken);
				TestEqual("Enqueued Retry's IsBlueprint is off", RetryReq.IsBlueprintCompatible, 0);
				TestEqual("Test that the Retry was enqueued but with no failure count", BeamBackendSystem->InFlightFailureCount[ReqId], Callbacks->ExpectedErrorFailureCount);
			}

			// Clean up fake request
			FakeRequest->MarkAsGarbage();
		});

		It("should update the connectivity status if we fail with TUnrealRequestStatus::Failed_ConnectionError", [this, FakeRealmHandle, FakeNoRetryConfig, FakeAuthToken]()
		{
			// We expect errors if we are always logging errors --- otherwise, we expect no errors to be logged since we are binding callbacks and logging is a fallback
			if (BeamBackendSystem->AlwaysLogErrorResponses)
				AddExpectedError(TEXT("Beamable Request Failed"), EAutomationExpectedErrorFlags::Contains, 4);

			UBeamMockGetRequest* FakeRequest = NewObject<UBeamMockGetRequest>();
			const FBeamErrorResponse Error = FBeamErrorResponse{500, TEXT("Internal Server Error"), TEXT("fake basic"), TEXT("Fake Error Message")};
			FString ResponseBody;
			FJsonObjectConverter::UStructToJsonObjectString(FBeamErrorResponse::StaticStruct(), &Error, ResponseBody);

			// Un-Authenticated BP Handler
			{
				int64 ReqId;
				const auto Request = BeamBackendSystem->CreateRequest(ReqId, FakeRealmHandle, FakeNoRetryConfig, FakeRequest);

				Callbacks->ExpectedReqId = ReqId;
				Callbacks->ExpectedErrorFailureCount = 1;
				Callbacks->ExpectedErrorResponseStatus = Error.status;
				Callbacks->ExpectedErrorResponseError = Error.error;
				Callbacks->ExpectedErrorResponseService = Error.service;
				Callbacks->ExpectedErrorResponseMessage = Error.message;

				FOnMockSuccess ResponseHandler;
				ResponseHandler.BindUFunction(Callbacks, FName(TEXT("MockSuccessCallback_Fail")));

				FOnMockError ResponseHandlerError;
				ResponseHandlerError.BindUFunction(Callbacks, FName(TEXT("MockErrorCallback_Expected")));

				FOnMockComplete ResponseHandlerComplete;
				ResponseHandlerComplete.BindUFunction(Callbacks, FName(TEXT("MockCompleteCallback_Expected")));


				// This should clean up the created request's data
				BeamBackendSystem->ProcessBlueprintRequest<UBeamMockGetRequest, UBeamMockGetRequestResponse>
					(500, ResponseBody, TUnrealRequestStatus::Failed, ReqId, FakeRequest, ResponseHandler, ResponseHandlerError, ResponseHandlerComplete);

				TestTrue("Flagged Request as Completed", BeamBackendSystem->InFlightRequestContexts.FindRef(ReqId).BeamStatus == AS_Completed);
			}

			// Authenticated BP Handler
			{
				int64 ReqId;
				const auto Request = BeamBackendSystem->CreateAuthenticatedRequest(ReqId, FakeRealmHandle, FakeNoRetryConfig, FakeAuthToken, FakeRequest);

				Callbacks->ExpectedReqId = ReqId;
				Callbacks->ExpectedErrorFailureCount = 1;
				Callbacks->ExpectedErrorResponseStatus = Error.status;
				Callbacks->ExpectedErrorResponseError = Error.error;
				Callbacks->ExpectedErrorResponseService = Error.service;
				Callbacks->ExpectedErrorResponseMessage = Error.message;

				FOnMockSuccess ResponseHandler;
				ResponseHandler.BindUFunction(Callbacks, FName(TEXT("MockSuccessCallback_Fail")));

				FOnMockError ResponseHandlerError;
				ResponseHandlerError.BindUFunction(Callbacks, FName(TEXT("MockErrorCallback_Expected")));

				FOnMockComplete ResponseHandlerComplete;
				ResponseHandlerComplete.BindUFunction(Callbacks, FName(TEXT("MockCompleteCallback_Expected")));

				// This should clean up the created request's data
				BeamBackendSystem->ProcessAuthenticatedBlueprintRequest<UBeamMockGetRequest, UBeamMockGetRequestResponse>
				(500, ResponseBody, TUnrealRequestStatus::Failed, ReqId, FakeRealmHandle, FakeAuthToken, FakeRequest, ResponseHandler, ResponseHandlerError,
				 ResponseHandlerComplete);				
				TestTrue("Flagged Request as Completed", BeamBackendSystem->InFlightRequestContexts.FindRef(ReqId).BeamStatus == AS_Completed);
			}

			// Un-Authenticated Code Handler 
			{
				int64 ReqId;
				const auto Request = BeamBackendSystem->CreateRequest(ReqId, FakeRealmHandle, FakeNoRetryConfig, FakeRequest);

				Callbacks->ExpectedReqId = ReqId;
				Callbacks->ExpectedErrorFailureCount = 1;
				Callbacks->ExpectedErrorResponseStatus = Error.status;
				Callbacks->ExpectedErrorResponseError = Error.error;
				Callbacks->ExpectedErrorResponseService = Error.service;
				Callbacks->ExpectedErrorResponseMessage = Error.message;

				FOnMockFullResponse ResponseHandler;
				ResponseHandler.BindLambda([this](FBeamFullResponse<UBeamMockGetRequest*, UBeamMockGetRequestResponse*> BeamFullResponse)
				{
					TestTrue("State was Error", BeamFullResponse.State == EBeamFullResponseState::RS_Error);
					Callbacks->MockErrorCallback_Expected(BeamFullResponse.Context, BeamFullResponse.RequestData, BeamFullResponse.ErrorData);
				});

				// This should clean up the created request's data
				BeamBackendSystem->ProcessCodeRequest(500, ResponseBody, TUnrealRequestStatus::Failed, ReqId, FakeRequest, ResponseHandler);				
				TestTrue("Flagged Request as Completed", BeamBackendSystem->InFlightRequestContexts.FindRef(ReqId).BeamStatus == AS_Completed);
			}

			// Authenticated Code Handler
			{
				int64 ReqId;
				const auto Request = BeamBackendSystem->CreateAuthenticatedRequest(ReqId, FakeRealmHandle, FakeNoRetryConfig, FakeAuthToken, FakeRequest);

				Callbacks->ExpectedReqId = ReqId;
				Callbacks->ExpectedErrorFailureCount = 1;
				Callbacks->ExpectedErrorResponseStatus = Error.status;
				Callbacks->ExpectedErrorResponseError = Error.error;
				Callbacks->ExpectedErrorResponseService = Error.service;
				Callbacks->ExpectedErrorResponseMessage = Error.message;

				FOnMockFullResponse ResponseHandler;
				ResponseHandler.BindLambda([this](FBeamFullResponse<UBeamMockGetRequest*, UBeamMockGetRequestResponse*> BeamFullResponse)
				{
					TestTrue("State was Error", BeamFullResponse.State == EBeamFullResponseState::RS_Error);
					Callbacks->MockErrorCallback_Expected(BeamFullResponse.Context, BeamFullResponse.RequestData, BeamFullResponse.ErrorData);
				});

				// This should clean up the created request's data
				BeamBackendSystem->ProcessAuthenticatedCodeRequest(500, ResponseBody, TUnrealRequestStatus::Failed, ReqId, FakeRealmHandle, FakeAuthToken, FakeRequest,
				                                                   ResponseHandler);				
				TestTrue("Flagged Request as Completed", BeamBackendSystem->InFlightRequestContexts.FindRef(ReqId).BeamStatus == AS_Completed);
			}

			FakeRequest->MarkAsGarbage();
		});

		LatentIt("should create and send a BP request, cancel it mid-flight and ignore it's response", [this, FakeRealmHandle, FakeNoRetryConfig](const FDoneDelegate& Done)
		{
			// We actually need the request to go out
			FHttpModule::Get().ToggleNullHttp(false);

			UBeamMockGetRequest* FakeRequest = NewObject<UBeamMockGetRequest>();

			// Un-Authenticated BP Request
			int64 ReqId;
			const auto Request = BeamBackendSystem->CreateRequest(ReqId, FakeRealmHandle, FakeNoRetryConfig, FakeRequest);

			Callbacks->DoneDelegateForLatentTests = Done;

			FOnMockSuccess ResponseHandler;
			ResponseHandler.BindUFunction(Callbacks, FName(TEXT("MockSuccessCallback_Fail")));

			FOnMockError ResponseHandlerError;
			ResponseHandlerError.BindUFunction(Callbacks, FName(TEXT("MockErrorCallback_Fail")));

			FOnMockComplete ResponseHandlerComplete;
			ResponseHandlerComplete.BindUFunction(Callbacks, FName(TEXT("MockCompleteCallbackCancelled_Expected")));

			// Binds the handler to the static response handler (pre-generated)	
			auto ResponseProcessor = BeamBackendSystem->MakeBlueprintRequestProcessor
				<UBeamMockGetRequest, UBeamMockGetRequestResponse>
				(ReqId, FakeRequest, ResponseHandler, ResponseHandlerError, ResponseHandlerComplete);
			Request->OnProcessRequestComplete().BindLambda(ResponseProcessor);

			// Send out the fake request knowing that it'll fail --- we don't care cause we are canceling it. 
			Request->ProcessRequest();

			// Test discarding unset data associated with InFlight Requests.
			BeamBackendSystem->CancelRequest(ReqId);
		});

		LatentIt("should create and send an Authenticated BP request, cancel it mid-flight and ignore it's response", [this, FakeRealmHandle, FakeNoRetryConfig, FakeAuthToken](const FDoneDelegate& Done)
		{
			// We actually need the request to go out
			FHttpModule::Get().ToggleNullHttp(false);
			UBeamMockGetRequest* FakeRequest = NewObject<UBeamMockGetRequest>();

			// Authenticated BP Request
			int64 ReqId;
			const auto Request = BeamBackendSystem->CreateAuthenticatedRequest(ReqId, FakeRealmHandle, FakeNoRetryConfig, FakeAuthToken, FakeRequest);

			Callbacks->DoneDelegateForLatentTests = Done;

			FOnMockSuccess ResponseHandler;
			ResponseHandler.BindUFunction(Callbacks, FName(TEXT("MockSuccessCallback_Fail")));

			FOnMockError ResponseHandlerError;
			ResponseHandlerError.BindUFunction(Callbacks, FName(TEXT("MockErrorCallback_Fail")));

			FOnMockComplete ResponseHandlerComplete;
			ResponseHandlerComplete.BindUFunction(Callbacks, FName(TEXT("MockCompleteCallbackCancelled_Expected")));

			// Binds the handler to the static response handler (pre-generated)	
			auto ResponseProcessor = BeamBackendSystem->MakeAuthenticatedBlueprintRequestProcessor
				<UBeamMockGetRequest, UBeamMockGetRequestResponse>
				(ReqId, FakeRealmHandle, FakeAuthToken, FakeRequest, ResponseHandler, ResponseHandlerError, ResponseHandlerComplete);
			Request->OnProcessRequestComplete().BindLambda(ResponseProcessor);

			// Send out the fake request knowing that it'll fail --- we don't care cause we are canceling it. 
			Request->ProcessRequest();

			// Test discarding unset data associated with InFlight Requests.
			BeamBackendSystem->CancelRequest(ReqId);
		});

		LatentIt("should create and send a Code request, cancel it mid-flight and ignore it's response", [this, FakeRealmHandle, FakeNoRetryConfig](const FDoneDelegate& Done)
		{
			// We actually need the request to go out
			FHttpModule::Get().ToggleNullHttp(false);

			UBeamMockGetRequest* FakeRequest = NewObject<UBeamMockGetRequest>();

			// Un-Authenticated Code Request
			int64 ReqId;
			const auto Request = BeamBackendSystem->CreateRequest(ReqId, FakeRealmHandle, FakeNoRetryConfig, FakeRequest);

			// Binds the lambda so we can test it
			FOnMockFullResponse ResponseHandler;
			ResponseHandler.BindLambda([this, Done](const FMockFullResponse FullResponse)
			{
				TestTrue("Beam back-end correctly stores the state as cancelled", BeamBackendSystem->IsRequestCancelled(FullResponse.Context.RequestId));
				TestTrue("Response state was Cancelled", FullResponse.State == EBeamFullResponseState::RS_Cancelled);
				TestTrue("Response state was Cancelled on the first attempt", FullResponse.AttemptNumber == 0);
				Done.Execute();
			});

			// Binds the handler to the static response handler (pre-generated)	
			auto ResponseProcessor = BeamBackendSystem->MakeCodeRequestProcessor
				<UBeamMockGetRequest, UBeamMockGetRequestResponse>
				(ReqId, FakeRequest, ResponseHandler);
			Request->OnProcessRequestComplete().BindLambda(ResponseProcessor);

			// Send out the fake request knowing that it'll fail --- we don't care cause we are canceling it. 
			Request->ProcessRequest();

			// Test discarding unset data associated with InFlight Requests.
			BeamBackendSystem->CancelRequest(ReqId);
		});

		LatentIt("should create and send an Authenticated Code request, cancel it mid-flight and ignore it's response", [this, FakeRealmHandle, FakeNoRetryConfig, FakeAuthToken](const FDoneDelegate& Done)
		{
			// We actually need the request to go out
			FHttpModule::Get().ToggleNullHttp(false);

			UBeamMockGetRequest* FakeRequest = NewObject<UBeamMockGetRequest>();

			// Authenticated Code Request
			int64 ReqId;
			const auto Request = BeamBackendSystem->CreateAuthenticatedRequest(ReqId, FakeRealmHandle, FakeNoRetryConfig, FakeAuthToken, FakeRequest);

			// Binds the lambda so we can test it
			FOnMockFullResponse ResponseHandler;
			ResponseHandler.BindLambda([this, Done](const FMockFullResponse FullResponse)
			{
				TestTrue("Beam back-end correctly stores the state as cancelled", BeamBackendSystem->IsRequestCancelled(FullResponse.Context.RequestId));
				TestTrue("Response state was Cancelled", FullResponse.State == EBeamFullResponseState::RS_Cancelled);
				TestTrue("Response state was Cancelled on the first attempt", FullResponse.AttemptNumber == 0);
				Done.Execute();
			});

			// Binds the handler to the static response handler (pre-generated)	
			auto ResponseProcessor = BeamBackendSystem->MakeAuthenticatedCodeRequestProcessor
				<UBeamMockGetRequest, UBeamMockGetRequestResponse>
				(ReqId, FakeRealmHandle, FakeAuthToken, FakeRequest, ResponseHandler);
			Request->OnProcessRequestComplete().BindLambda(ResponseProcessor);

			// Send out the fake request knowing that it'll fail --- we don't care cause we are canceling it. 
			Request->ProcessRequest();

			// Test discarding unset data associated with InFlight Requests.
			BeamBackendSystem->CancelRequest(ReqId);
		});


		It("should clean up requests tagged as completed", [this, FakeRealmHandle, FakeResponseCodeRetryConfig, FakeAuthToken]()
		{
			UBeamMockGetRequest* FakeRequest = NewObject<UBeamMockGetRequest>();

			// Authenticated Code Handler 
			int64 ReqId, ReqId2;
			const auto Request = BeamBackendSystem->CreateAuthenticatedRequest(ReqId, FakeRealmHandle, FakeResponseCodeRetryConfig, FakeAuthToken, FakeRequest);
			const auto Request2 = BeamBackendSystem->CreateAuthenticatedRequest(ReqId2, FakeRealmHandle, FakeResponseCodeRetryConfig, FakeAuthToken, FakeRequest);

			// Pretend that the failure count was increased
			BeamBackendSystem->InFlightFailureCount[ReqId] = 1;

			// We get the first request and fake it's completion.
			const auto BeamRequestContext = BeamBackendSystem->InFlightRequestContexts.Find(ReqId);
			BeamRequestContext->BeamStatus = AS_Completed;

			// We get the second request context and fake it's completion
			const auto BeamRequestContext2 = BeamBackendSystem->InFlightRequestContexts.Find(ReqId2);
			BeamRequestContext2->BeamStatus = AS_Completed;

			// We set up the handler to pretend that request 2 is being depended by some external system.
			Callbacks->ExternalRequestIds.Add(ReqId2);
			FTickOnBackendCleanUp CleanUpHandler;
			CleanUpHandler.BindUFunction(Callbacks, GET_FUNCTION_NAME_CHECKED(UBeamBackendTestCallbacks, GenerateExternalRequestIds));
			BeamBackendSystem->TickOnBackendCleanUpDelegates.Add(CleanUpHandler);
			BeamBackendSystem->CleanUpRequestData();
			BeamBackendSystem->TickOnBackendCleanUpDelegates.Remove(CleanUpHandler);

			// Because it's NOT an external dependency and it's completed, we can clean it up.
			TestFalse("First Request  was cleaned up", BeamBackendSystem->InFlightRequests.Contains(ReqId));
			TestFalse("First Request Context was cleaned up", BeamBackendSystem->InFlightRequestContexts.Contains(ReqId));
			TestFalse("First Failure Count Data was cleaned up", BeamBackendSystem->InFlightFailureCount.Contains(ReqId));
			TestFalse("First Req Id was removed from Cancelled List", BeamBackendSystem->InFlightRequestsCancelled.Contains(ReqId));
			TestFalse("First Request Data was cleaned up", BeamBackendSystem->InFlightRequestData.Contains(*BeamRequestContext));
			TestFalse("First Response Data was cleaned up", BeamBackendSystem->InFlightResponseBodyData.Contains(*BeamRequestContext));
			TestFalse("First Error Data was cleaned up", BeamBackendSystem->InFlightResponseErrorData.Contains(*BeamRequestContext));

			// Because it's an external dependency, we should keep it in memory
			TestTrue("Second Request was not cleaned up", BeamBackendSystem->InFlightRequests.Contains(ReqId2));
			TestTrue("Second Request Context was not cleaned up", BeamBackendSystem->InFlightRequestContexts.Contains(ReqId2));
			TestTrue("Second Failure Count Data was not cleaned up", BeamBackendSystem->InFlightFailureCount.Contains(ReqId2));
			TestTrue("Second Request Data was not cleaned up", BeamBackendSystem->InFlightRequestData.Contains(*BeamRequestContext2));
			TestTrue("Second Response Data was not cleaned up", BeamBackendSystem->InFlightResponseBodyData.Contains(*BeamRequestContext2));
			TestTrue("Second Error Data was not cleaned up", BeamBackendSystem->InFlightResponseErrorData.Contains(*BeamRequestContext2));

			FakeRequest->MarkAsGarbage();
		});
	});

	Describe("Retry Configurations", [=, this]()
	{
		const FUserSlot TestUserSlot{"TestSlot"};
		const FRequestType RequestType{ULoginRefreshTokenRequest::StaticClass()->GetName()};

		BeforeEach([this]()
		{
			BeamBackendSystem = GEngine->GetEngineSubsystem<UBeamBackend>();
		});

		AfterEach([this, RequestType, TestUserSlot]()
		{
			// If these aren't working it'll break the tests below, so we don't explicitly test for these.
			BeamBackendSystem->ResetRetryConfigForRequestType(RequestType);
			BeamBackendSystem->ResetRetryConfigForUserSlot(TestUserSlot);
			BeamBackendSystem->ResetRetryConfigForUserSlotAndRequestType(TestUserSlot, RequestType);
		});

		It("should override a specific request type's retry configuration", [this, RequestType]()
		{
			auto ExpectedOverridenConfig = BeamBackendSystem->DefaultRetryConfig;
			ExpectedOverridenConfig.Timeout = -5;
			BeamBackendSystem->SetRetryConfigForRequestType(RequestType, ExpectedOverridenConfig);

			FBeamRetryConfig ActualConfig;
			BeamBackendSystem->GetRetryConfigForRequestType(RequestType, ActualConfig);

			TestTrue("Overriden Retry Config for Request Type", ExpectedOverridenConfig.Timeout == ActualConfig.Timeout);
		});

		It("should override a specific user's retry configuration", [this, TestUserSlot]()
		{
			auto ExpectedOverridenConfig = BeamBackendSystem->DefaultRetryConfig;
			ExpectedOverridenConfig.Timeout = -5;
			BeamBackendSystem->SetRetryConfigForUserSlot(TestUserSlot, ExpectedOverridenConfig);

			FBeamRetryConfig ActualConfig;
			BeamBackendSystem->GetRetryConfigForUserSlot(TestUserSlot, ActualConfig);

			TestTrue("Overriden Retry Config for Request Type", ExpectedOverridenConfig.Timeout == ActualConfig.Timeout);
		});

		It("should override a specific user specific requests's retry configuration", [this, TestUserSlot, RequestType]()
		{
			auto ExpectedOverridenConfig = BeamBackendSystem->DefaultRetryConfig;
			ExpectedOverridenConfig.Timeout = -5;
			BeamBackendSystem->SetRetryConfigForUserSlotAndRequestType(TestUserSlot, RequestType, ExpectedOverridenConfig);

			FBeamRetryConfig ActualConfig;
			BeamBackendSystem->GetRetryConfigForUserSlotAndRequestType(RequestType, TestUserSlot, ActualConfig);

			TestTrue("Overriden Retry Config for Request Type", ExpectedOverridenConfig.Timeout == ActualConfig.Timeout);
		});

		It("should fallback correctly to the request type's retry configuration", [this, RequestType, TestUserSlot]()
		{
			auto ExpectedOverridenConfig = BeamBackendSystem->DefaultRetryConfig;
			ExpectedOverridenConfig.Timeout = -5;
			BeamBackendSystem->SetRetryConfigForRequestType(RequestType, ExpectedOverridenConfig);

			FBeamRetryConfig ActualConfig;
			BeamBackendSystem->GetRetryConfigForUserSlotAndRequestType(RequestType, TestUserSlot, ActualConfig);

			TestTrue("Overriden Retry Config for Request Type", ExpectedOverridenConfig.Timeout == ActualConfig.Timeout);
		});

		It("should fallback correctly to the default retry configuration", [this, RequestType, TestUserSlot]()
		{
			const auto ExpectedOverridenConfig = BeamBackendSystem->DefaultRetryConfig;

			FBeamRetryConfig ActualConfig;
			BeamBackendSystem->GetRetryConfigForUserSlotAndRequestType(RequestType, TestUserSlot, ActualConfig);
			TestTrue("Overriden Retry Config for Request Type", ExpectedOverridenConfig.Timeout == ActualConfig.Timeout);

			BeamBackendSystem->GetRetryConfigForRequestType(RequestType, ActualConfig);
			TestTrue("Overriden Retry Config for Request Type", ExpectedOverridenConfig.Timeout == ActualConfig.Timeout);
		});
	});

	Describe("Retry Logic", [=, this]()
	{
		const FBeamRealmHandle FakeRealmHandle{FString("TEST_CID"), FString("TEST_PID")};
		const FBeamRetryConfig FakeResponseCodeRetryConfig{{503}, {}, 10, TArray<float>{0.5, 1}, 1};
		const FBeamRetryConfig FakeErrorCodeRetryConfig{{}, {TEXT("ErrorCode")}, 10, TArray<float>{0.5, 1}, 1};
		const FBeamAuthToken FakeAuthToken{"AUTH_TOKEN", "REFRESH_TOKEN"};

		BeforeEach([this]()
		{
			BeamBackendSystem = GEngine->GetEngineSubsystem<UBeamBackend>();

			FHttpModule::Get().ToggleNullHttp(true);
		});

		AfterEach([this]()
		{
			// Make sure that the execute request delegate is properly set up. 
			BeamBackendSystem->ExecuteRequestDelegate.BindUFunction(BeamBackendSystem, "DefaultExecuteRequestImpl");
			FHttpModule::Get().ToggleNullHttp(false);

			// Reset the request id counter to 0 and all the state related to InFlight Requests back to initial state
			BeamBackendSystem->InFlightRequestId = -1;
			BeamBackendSystem->InFlightRequests.Reset();
			BeamBackendSystem->InFlightFailureCount.Reset();
			BeamBackendSystem->InFlightRequestContexts.Reset();
			BeamBackendSystem->InFlightRequestsCancelled.Reset();

			// Clear all Enqueued Retries
			BeamBackendSystem->EnqueuedRetries.Empty();
			BeamBackendSystem->InFlightProcessingRequests.Reset();

			// Clear all Global Handlers
			BeamBackendSystem->GlobalRequestErrorHandler.Clear();
			BeamBackendSystem->GlobalRequestErrorCodeHandler.Unbind();
		});

		It("should begin processing a request enqueued for retry", [this, FakeRealmHandle, FakeResponseCodeRetryConfig, FakeAuthToken, FakeErrorCodeRetryConfig]()
		{
			UBeamMockGetRequest* FakeRequest = NewObject<UBeamMockGetRequest>();

			// Authenticated Code Handler 
			int64 ResponseCodeReqId, ErrorCodeReqId;
			const auto ResponseCodeRequest = BeamBackendSystem->CreateAuthenticatedRequest(ResponseCodeReqId, FakeRealmHandle, FakeResponseCodeRetryConfig, FakeAuthToken, FakeRequest);
			const auto ErrorCodeRequest = BeamBackendSystem->CreateAuthenticatedRequest(ErrorCodeReqId, FakeRealmHandle, FakeErrorCodeRetryConfig, FakeAuthToken, FakeRequest);

			// Pretend that the failure count was increased
			BeamBackendSystem->InFlightFailureCount[ResponseCodeReqId] = 1;
			BeamBackendSystem->InFlightFailureCount[ErrorCodeReqId] = 1;


			// Enqueues the request to retry.
			const auto ExpectedResponseCodeRetry = FRequestToRetry{
				ResponseCodeReqId, 0, 503, FakeRealmHandle,
			};
			const auto ExpectedErrorCodeRetry = FRequestToRetry{
				ErrorCodeReqId, 0, 504, {FakeRealmHandle}, {FString("ErrorCode")}
			};
			BeamBackendSystem->EnqueuedRetries.Enqueue(ExpectedResponseCodeRetry);
			BeamBackendSystem->EnqueuedRetries.Enqueue(ExpectedErrorCodeRetry);

			constexpr auto ExpectedAccumulatedTime = 0.25f;
			BeamBackendSystem->TickRetryQueue(ExpectedAccumulatedTime);

			const auto ProcessingResponseCodeRequest = BeamBackendSystem->InFlightProcessingRequests[ResponseCodeReqId];
			const auto ProcessingErrorCodeRequest = BeamBackendSystem->InFlightProcessingRequests[ErrorCodeReqId];

			TestTrue("Retry Data is as expected", ProcessingResponseCodeRequest.RequestToRetry == ExpectedResponseCodeRetry);
			TestTrue("Retry Data is as expected", ProcessingErrorCodeRequest.RequestToRetry == ExpectedErrorCodeRetry);

			TestTrue("wait time correctly set", ProcessingResponseCodeRequest.TimeToWait == FakeResponseCodeRetryConfig.RetryFalloffValues[0]);
			TestTrue("wait time correctly set", ProcessingErrorCodeRequest.TimeToWait == FakeErrorCodeRetryConfig.RetryFalloffValues[0]);

			TestTrue("accumulated time was correctly set", ProcessingResponseCodeRequest.AccumulatedTime == ExpectedAccumulatedTime);
			TestTrue("accumulated time was correctly set", ProcessingErrorCodeRequest.AccumulatedTime == ExpectedAccumulatedTime);

			FakeRequest->MarkAsGarbage();
		});

		LatentIt("should call the process request when failing a non-authenticated request", [this, FakeRealmHandle, FakeErrorCodeRetryConfig, FakeResponseCodeRetryConfig](FDoneDelegate Done)
		{
			// We actually need the request to go out
			FHttpModule::Get().ToggleNullHttp(false);

			UBeamMockGetRequest* FakeRequest = NewObject<UBeamMockGetRequest>();

			int64 ResponseCodeReqId, ErrorCodeReqId;
			const auto ResponseCodeRequest = BeamBackendSystem->CreateRequest(ResponseCodeReqId, FakeRealmHandle, FakeResponseCodeRetryConfig, FakeRequest);
			const auto ErrorCodeRequest = BeamBackendSystem->CreateRequest(ErrorCodeReqId, FakeRealmHandle, FakeErrorCodeRetryConfig, FakeRequest);

			// Pretend that the failure count was increased
			BeamBackendSystem->InFlightFailureCount[ResponseCodeReqId] = 1;
			BeamBackendSystem->InFlightFailureCount[ErrorCodeReqId] = 1;

			// Pretend the requests went out
			BeamBackendSystem->InFlightRequestContexts.Find(ResponseCodeReqId)->BeamStatus = AS_InFlight;
			BeamBackendSystem->InFlightRequestContexts.Find(ErrorCodeReqId)->BeamStatus = AS_InFlight;
			
			// Bind a fake lambda just so we know that the request had process request called on it.				
			ResponseCodeRequest->OnProcessRequestComplete()
			                   .BindLambda([this, Done](TSharedPtr<IHttpRequest, ESPMode::ThreadSafe>, TSharedPtr<IHttpResponse, ESPMode::ThreadSafe> HttpResponse, bool sent)
			                   {
				                   UE_LOG(LogTemp, Display, TEXT("Process Request was called in the failed request!!!"));
				                   TestTrue("Callback was called", true);
				                   Done.Execute();
			                   });

			ErrorCodeRequest->OnProcessRequestComplete()
			                .BindLambda([this, Done](TSharedPtr<IHttpRequest, ESPMode::ThreadSafe>, TSharedPtr<IHttpResponse, ESPMode::ThreadSafe> HttpResponse, bool sent)
			                {
				                UE_LOG(LogTemp, Display, TEXT("Process Request was called in the failed request!!!"));
				                TestTrue("Callback was called", true);
				                Done.Execute();
			                });

			// Enqueues the request to retry.
			const auto ExpectedResponseCodeRetry = FRequestToRetry{
				ResponseCodeReqId, 0, 503, FakeRealmHandle, {},
			};
			const auto ExpectedErrorCodeRetry = FRequestToRetry{
				ErrorCodeReqId, 0, 504, FakeRealmHandle, {}, TEXT("ErrorCode")
			};
			BeamBackendSystem->EnqueuedRetries.Enqueue(ExpectedResponseCodeRetry);
			BeamBackendSystem->EnqueuedRetries.Enqueue(ExpectedErrorCodeRetry);

			// Set the delta time to be enough time to trigger the retry of the fake request
			constexpr auto ExpectedAccumulatedTime = 0.75f;
			BeamBackendSystem->TickRetryQueue(ExpectedAccumulatedTime);
		});


		LatentIt("should call the process request when failing an authenticated request", [this, FakeRealmHandle, FakeResponseCodeRetryConfig, FakeErrorCodeRetryConfig, FakeAuthToken](FDoneDelegate Done)
		{
			// We actually need the request to go out
			FHttpModule::Get().ToggleNullHttp(false);

			UBeamMockGetRequest* FakeRequest = NewObject<UBeamMockGetRequest>();

			int64 ResponseCodeReqId, ErrorCodeReqId;
			const auto ResponseCodeRequest = BeamBackendSystem->CreateAuthenticatedRequest(ResponseCodeReqId, FakeRealmHandle, FakeResponseCodeRetryConfig, FakeAuthToken, FakeRequest);
			const auto ErrorCodeRequest = BeamBackendSystem->CreateAuthenticatedRequest(ErrorCodeReqId, FakeRealmHandle, FakeErrorCodeRetryConfig, FakeAuthToken, FakeRequest);

			// Pretend that the failure count was increased
			BeamBackendSystem->InFlightFailureCount[ResponseCodeReqId] = 1;
			BeamBackendSystem->InFlightFailureCount[ErrorCodeReqId] = 1;

			// Pretend the requests went out
			BeamBackendSystem->InFlightRequestContexts.Find(ResponseCodeReqId)->BeamStatus = AS_InFlight;
			BeamBackendSystem->InFlightRequestContexts.Find(ErrorCodeReqId)->BeamStatus = AS_InFlight;
			
			// Bind a fake lambda just so we know that the request had process request called on it.				
			ResponseCodeRequest->OnProcessRequestComplete()
			                   .BindLambda([this, Done](TSharedPtr<IHttpRequest, ESPMode::ThreadSafe>, TSharedPtr<IHttpResponse, ESPMode::ThreadSafe> HttpResponse, bool sent)
			                   {
				                   UE_LOG(LogTemp, Display, TEXT("Process Request was called in the failed request!!!"));
				                   TestTrue("Callback was called", true);
				                   Done.Execute();
			                   });

			ErrorCodeRequest->OnProcessRequestComplete()
			                .BindLambda([this, Done](TSharedPtr<IHttpRequest, ESPMode::ThreadSafe>, TSharedPtr<IHttpResponse, ESPMode::ThreadSafe> HttpResponse, bool sent)
			                {
				                UE_LOG(LogTemp, Display, TEXT("Process Request was called in the failed request!!!"));
				                TestTrue("Callback was called", true);
				                Done.Execute();
			                });

			// Enqueues the request to retry.
			const auto ExpectedResponseCodeRetry = FRequestToRetry{
				ResponseCodeReqId, 0, 503, FakeRealmHandle, FakeAuthToken,
			};
			const auto ExpectedErrorCodeRetry = FRequestToRetry{
				ErrorCodeReqId, 0, 504, FakeRealmHandle, FakeAuthToken, TEXT("ErrorCode")
			};
			BeamBackendSystem->EnqueuedRetries.Enqueue(ExpectedResponseCodeRetry);
			BeamBackendSystem->EnqueuedRetries.Enqueue(ExpectedErrorCodeRetry);

			// Set the delta time to be enough time to trigger the retry of the fake request
			constexpr auto ExpectedAccumulatedTime = 0.75f;
			BeamBackendSystem->TickRetryQueue(ExpectedAccumulatedTime);
		});
	});	

	Describe("Dedicated Servers", [=, this]()
	{		
		BeforeEach([this]()
		{						
			BeamBackendSystem = GEngine->GetEngineSubsystem<UBeamBackend>();
		});

		AfterEach([this]()
		{
		});

		It("should correctly extract URLs for request signing", [this]()
		{
			constexpr int64 ExpectedRequestId = 10;
			const FString ExpectedRequestType = UBeamMockGetRequest::StaticClass()->GetName();

			const FString ScalaUrl = FString(TEXT("https://dev.api.beamable.com/object/stats/game.public.player.1595037680985091/"));
			const FString CSharpUrl = FString(TEXT("https://dev.api.beamable.com/api/lobbies/7c9f10d1-b16c-46d1-8af1-df76604b1e1b/"));

			FString SigScalaUrl;
			BeamBackendSystem->ExtractUrlForSignature(ScalaUrl,SigScalaUrl);

			FString SigCSharpUrl;
			BeamBackendSystem->ExtractUrlForSignature(CSharpUrl,SigCSharpUrl);

			TestEqual("Scala URL extracted correctly", SigScalaUrl, TEXT("/object/stats/game.public.player.1595037680985091/"));
			TestEqual("CSharp URL extracted correctly", SigCSharpUrl, TEXT("/api/lobbies/7c9f10d1-b16c-46d1-8af1-df76604b1e1b/"));
			
		});
	});
}
