#include "BeamBackend.spec.h"

#include "Engine/Engine.h"
#include "Misc/AutomationTest.h"

#include "BeamBackend/BeamBackend.h"
#include "BeamBackendTestCallbacks.h"
#include "JsonObjectConverter.h"
#include "RawAPIs/BeamSharedTypes.h"

void FBeamBackendSpec::Define()
{
	Describe("Request/Response", [this]()
	{
		const FBeamRealmHandle FakeRealmHandle{"TEST_CID", "TEST_PID"};
		const FBeamRetryConfig FakeNoRetryConfig{10, TArray<float>{0.5, 1}, 0};
		const FBeamRetryConfig FakeSimpleRetryConfig{10, TArray<float>{0.5, 1}, 1};
		const FBeamAuthToken FakeAuthToken{"AUTH_TOKEN", "REFRESH_TOKEN"};

		BeforeEach([this]()
		{
			BeamBackendSystem = GEngine->GetEngineSubsystem<UBeamBackend>();

			// Prepare Back-end Tests with Blueprint-compatible mock handler
			Callbacks = NewObject<UBeamBackendTestCallbacks>();
			Callbacks->BeamBackend = BeamBackendSystem;
			Callbacks->Spec = this;

			FHttpModule::Get().ToggleNullHttp(true);
		});

		AfterEach([this]()
		{
			// Clear callbacks object			
			Callbacks = nullptr;

			// Make sure that the execute request delegate is properly set up. 
			BeamBackendSystem->ExecuteRequestDelegate.BindUFunction(BeamBackendSystem, "DefaultExecuteRequestImpl");
			FHttpModule::Get().ToggleNullHttp(false);

			// Reset the request id counter to 0 and all the state related to InFlight Requests back to initial state
			*BeamBackendSystem->InFlightRequestId = -1;
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

		It("should create an TUnrealRequestPtr WITHOUT authentication headers, correct parameters and retry configuration then discard it", [=, this]()
		{
			// GET REQUESTS
			{
				UBeamMockGetRequest* FakeGetRequest = NewObject<UBeamMockGetRequest>();

				int64 ReqId;
				const auto Request = BeamBackendSystem->CreateRequest(ReqId, FakeRealmHandle, FakeNoRetryConfig, FakeGetRequest);

				// Ensure all headers were created correctly
				TestTrue("Accept Header is Set correctly", Request->GetHeader(UBeamBackend::HEADER_ACCEPT) == UBeamBackend::HEADER_VALUE_ACCEPT_CONTENT_TYPE);
				TestTrue("Content Type Header is Set correctly", Request->GetHeader(UBeamBackend::HEADER_CONTENT_TYPE) == UBeamBackend::HEADER_VALUE_ACCEPT_CONTENT_TYPE);
				TestTrue("Client ID Header is Set correctly", Request->GetHeader(UBeamBackend::HEADER_CLIENT_ID) == FakeRealmHandle.Cid);
				TestTrue("Project ID Header is Set correctly", Request->GetHeader(UBeamBackend::HEADER_PROJECT_ID) == FakeRealmHandle.Pid);

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
				TestTrue("Client ID Header is Set correctly", Request->GetHeader(UBeamBackend::HEADER_CLIENT_ID) == FakeRealmHandle.Cid);
				TestTrue("Project ID Header is Set correctly", Request->GetHeader(UBeamBackend::HEADER_PROJECT_ID) == FakeRealmHandle.Pid);

				const auto SetUpRetryConfig = BeamBackendSystem->InFlightRequestContexts.FindRef(ReqId).RetryConfiguration;
				TestEqual("InFlightRetryConfig was set up correctly for this request", SetUpRetryConfig, FakeNoRetryConfig);

				TestTrue("VERB is Set Correctly = 'POST'", Request->GetVerb() == TEXT("POST"));
				TestTrue("Route was set up correctly", Request->GetURL().Contains(TEXT("/fake/url")));

				const auto Content = FString(UTF8_TO_TCHAR(Request->GetContent().GetData()));
				TestTrue("Body was set up correctly", Content == TEXT(R"({"fake_int":10})"));

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

		It("should create an TUnrealRequestPtr WITH authentication headers, correct parameters and retry configuration then discard it", [=, this]()
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
				         Request->GetHeader(UBeamBackend::HEADER_REQUEST_SCOPE) == FString::Format(TEXT("{0}.{1}"), {FakeRealmHandle.Cid, FakeRealmHandle.Pid}));

				TestTrue("Client ID Header is Set correctly", Request->GetHeader(UBeamBackend::HEADER_CLIENT_ID) == FakeRealmHandle.Cid);
				TestTrue("Project ID Header is Set correctly", Request->GetHeader(UBeamBackend::HEADER_PROJECT_ID) == FakeRealmHandle.Pid);

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
				         Request->GetHeader(UBeamBackend::HEADER_REQUEST_SCOPE) == FString::Format(TEXT("{0}.{1}"), {FakeRealmHandle.Cid, FakeRealmHandle.Pid}));

				TestTrue("Client ID Header is Set correctly", Request->GetHeader(UBeamBackend::HEADER_CLIENT_ID) == FakeRealmHandle.Cid);
				TestTrue("Project ID Header is Set correctly", Request->GetHeader(UBeamBackend::HEADER_PROJECT_ID) == FakeRealmHandle.Pid);

				const auto SetUpRetryConfig = BeamBackendSystem->InFlightRequestContexts.FindRef(ReqId).RetryConfiguration;
				TestEqual("InFlightRetryConfig was set up correctly for this request", SetUpRetryConfig, FakeNoRetryConfig);

				TestTrue("VERB is Set Correctly = 'POST'", Request->GetVerb() == TEXT("POST"));
				TestTrue("Route was set up correctly", Request->GetURL().Contains(TEXT("/fake/url")));

				const auto Content = FString(UTF8_TO_TCHAR(Request->GetContent().GetData()));
				TestTrue("Body was set up correctly", Content == TEXT(R"({"fake_int":10})"));

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

		It("should invoke the Success Handlers with the correct data when received a 200 response code", [=, this]()
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
				TestTrue("Is Connected", BeamBackendSystem->CurrentConnectivityStatus.IsConnected);
				TestTrue("Flagged Request as Completed", BeamBackendSystem->InFlightRequestContexts.FindRef(ReqId).BeamStatus == Completed);
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
				TestTrue("Is Connected", BeamBackendSystem->CurrentConnectivityStatus.IsConnected);
				TestTrue("Flagged Request as Completed", BeamBackendSystem->InFlightRequestContexts.FindRef(ReqId).BeamStatus == Completed);
			}

			// Un-Authenticated Code Handler 
			{
				int64 ReqId;
				const auto Request = BeamBackendSystem->CreateRequest(ReqId, FakeRealmHandle, FakeNoRetryConfig, FakeRequestData);

				FOnMockFullResponse ResponseHandler;
				ResponseHandler.BindLambda([=, this](FBeamFullResponse<UBeamMockGetRequest*, UBeamMockGetRequestResponse*> BeamFullResponse)
				{
					TestTrue("State was Success", BeamFullResponse.State == Success);

					TestTrue("Request Id was correctly forwarded", BeamFullResponse.Context.RequestId == ReqId);
					TestTrue("Attempt Number was correctly forwarded", BeamFullResponse.AttemptNumber == 0);
					TestTrue("Response Code was correctly forwarded", BeamFullResponse.Context.ResponseCode == 200);
					TestTrue("Response Body was correctly forwarded", BeamFullResponse.SuccessData->FakeInt == ExpectedFakeInt);
				});

				// This should clean up the created request's data
				BeamBackendSystem->ProcessCodeRequest<UBeamMockGetRequest, UBeamMockGetRequestResponse>(200, ResponseBody, TUnrealRequestStatus::Succeeded, ReqId, FakeRequestData, ResponseHandler);
				TestTrue("Is Connected", BeamBackendSystem->CurrentConnectivityStatus.IsConnected);
				TestTrue("Flagged Request as Completed", BeamBackendSystem->InFlightRequestContexts.FindRef(ReqId).BeamStatus == Completed);
			}

			// Authenticated Code Handler
			{
				int64 ReqId;
				const auto Request = BeamBackendSystem->CreateAuthenticatedRequest(ReqId, FakeRealmHandle, FakeNoRetryConfig, FakeAuthToken, FakeRequestData);

				FOnMockFullResponse ResponseHandler;
				ResponseHandler.BindLambda([=, this](FBeamFullResponse<UBeamMockGetRequest*, UBeamMockGetRequestResponse*> BeamFullResponse)
				{
					TestTrue("State was Success", BeamFullResponse.State == Success);

					TestTrue("Request Id was correctly forwarded", BeamFullResponse.Context.RequestId == ReqId);
					TestTrue("Attempt Number was correctly forwarded", BeamFullResponse.AttemptNumber == 0);
					TestTrue("Response Code was correctly forwarded", BeamFullResponse.Context.ResponseCode == 200);
					TestTrue("Response Body was correctly forwarded", BeamFullResponse.SuccessData->FakeInt == ExpectedFakeInt);
				});

				// This should clean up the created request's data
				BeamBackendSystem->ProcessAuthenticatedCodeRequest
					<UBeamMockGetRequest, UBeamMockGetRequestResponse>
					(200, ResponseBody, TUnrealRequestStatus::Succeeded, ReqId, FakeRealmHandle, FakeAuthToken, FakeRequestData, ResponseHandler);
				TestTrue("Is Connected", BeamBackendSystem->CurrentConnectivityStatus.IsConnected);
				TestTrue("Flagged Request as Completed", BeamBackendSystem->InFlightRequestContexts.FindRef(ReqId).BeamStatus == Completed);
			}

			// Clean Up Fake Request Data
			FakeRequestData->MarkAsGarbage();
		});

		It("should invoke the Error Handlers with the correct data when received an error response code", [=, this]()
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
				TestTrue("Flagged Request as Completed", BeamBackendSystem->InFlightRequestContexts.FindRef(ReqId).BeamStatus == Completed);
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
				TestTrue("Flagged Request as Completed", BeamBackendSystem->InFlightRequestContexts.FindRef(ReqId).BeamStatus == Completed);
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
				ResponseHandler.BindLambda([=, this](FBeamFullResponse<UBeamMockGetRequest*, UBeamMockGetRequestResponse*> BeamFullResponse)
				{
					TestTrue("State was Error", BeamFullResponse.State == EBeamFullResponseState::Error);
					Callbacks->MockErrorCallback_Expected(BeamFullResponse.Context, BeamFullResponse.RequestData, BeamFullResponse.ErrorData);
				});

				// This should clean up the created request's data
				BeamBackendSystem->ProcessCodeRequest(500, ResponseBody, TUnrealRequestStatus::Failed, ReqId, FakeRequest, ResponseHandler);
				TestTrue("Flagged Request as Completed", BeamBackendSystem->InFlightRequestContexts.FindRef(ReqId).BeamStatus == Completed);
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
				ResponseHandler.BindLambda([=, this](FBeamFullResponse<UBeamMockGetRequest*, UBeamMockGetRequestResponse*> BeamFullResponse)
				{
					TestTrue("State was Error", BeamFullResponse.State == EBeamFullResponseState::Error);
					Callbacks->MockErrorCallback_Expected(BeamFullResponse.Context, BeamFullResponse.RequestData, BeamFullResponse.ErrorData);
				});

				// This should clean up the created request's data
				BeamBackendSystem->ProcessAuthenticatedCodeRequest(500, ResponseBody, TUnrealRequestStatus::Failed, ReqId, FakeRealmHandle, FakeAuthToken, FakeRequest, ResponseHandler);
				TestTrue("Flagged Request as Completed", BeamBackendSystem->InFlightRequestContexts.FindRef(ReqId).BeamStatus == Completed);
			}

			// Clean up Fake Request
			FakeRequest->MarkAsGarbage();
		});

		It("should invoke the Error Handlers with the correct data when received an error response code AND Enqueue Request for Retry", [=, this]()
		{
			UBeamMockGetRequest* FakeRequest = NewObject<UBeamMockGetRequest>();
			const FBeamErrorResponse Error = FBeamErrorResponse{503, TEXT("Internal Server Error"), TEXT("fake basic"), TEXT("Fake Error Message")};
			FString ResponseBody;
			FJsonObjectConverter::UStructToJsonObjectString(FBeamErrorResponse::StaticStruct(), &Error, ResponseBody);

			// We expect errors if we are always logging errors --- otherwise, we expect no errors to be logged since we are binding callbacks and logging is a fallback
			if (BeamBackendSystem->AlwaysLogErrorResponses)
				AddExpectedError(TEXT("Beamable Request Failed"), EAutomationExpectedErrorFlags::Contains, 0);

			for (const auto& RetryableErrorCode : BeamBackendSystem->NON_AUTH_REQUESTS_RETRY_ALLOWED_ERRORS)
			{
				// Un-Authenticated BP Handler
				{
					int64 ReqId;
					const auto Request = BeamBackendSystem->CreateRequest(ReqId, FakeRealmHandle, FakeSimpleRetryConfig, FakeRequest);

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
						(RetryableErrorCode, ResponseBody, TUnrealRequestStatus::Failed, ReqId, FakeRequest, ResponseHandler, ResponseHandlerError, ResponseHandlerComplete);

					// Assert that the request was correctly enqueued for work
					FRequestToRetry RetryReq;
					TestTrue("Test that the Retry was enqueued", BeamBackendSystem->EnqueuedRetries.Dequeue(RetryReq));
					TestTrue("Enqueued Retry's Request Id is equal", RetryReq.RequestId == ReqId);
					TestTrue("Enqueued Retry's IsBlueprint is on", RetryReq.IsBlueprint == 1);
				}


				// Un-Authenticated Code Handler 
				{
					int64 ReqId;
					const auto Request = BeamBackendSystem->CreateRequest(ReqId, FakeRealmHandle, FakeSimpleRetryConfig, FakeRequest);

					Callbacks->ExpectedReqId = ReqId;
					Callbacks->ExpectedErrorFailureCount = 1;
					Callbacks->ExpectedErrorResponseStatus = Error.status;
					Callbacks->ExpectedErrorResponseError = Error.error;
					Callbacks->ExpectedErrorResponseService = Error.service;
					Callbacks->ExpectedErrorResponseMessage = Error.message;

					FOnMockFullResponse ResponseHandler;
					ResponseHandler.BindLambda([=, this](FBeamFullResponse<UBeamMockGetRequest*, UBeamMockGetRequestResponse*> BeamFullResponse)
					{
						TestTrue("State was Retrying", BeamFullResponse.State == EBeamFullResponseState::Retrying);
						Callbacks->MockErrorCallback_Expected(BeamFullResponse.Context, BeamFullResponse.RequestData, BeamFullResponse.ErrorData);
					});

					// This should clean up the created request's data
					BeamBackendSystem->ProcessCodeRequest(RetryableErrorCode, ResponseBody, TUnrealRequestStatus::Failed, ReqId, FakeRequest, ResponseHandler);

					// Assert that the request was correctly enqueued for work
					FRequestToRetry RetryReq;
					TestTrue("Test that the Retry was enqueued", BeamBackendSystem->EnqueuedRetries.Dequeue(RetryReq));
					TestTrue("Enqueued Retry's Request Id is equal", RetryReq.RequestId == ReqId);
					TestTrue("Enqueued Retry's IsBlueprint is off", RetryReq.IsBlueprint == 0);
				}
			}


			for (const auto& RetryableErrorCode : BeamBackendSystem->AUTH_REQUESTS_RETRY_ALLOWED_ERRORS)
			{
				const auto bIsAutomaticReAuth = RetryableErrorCode == 401;

				// Authenticated BP Handler
				{
					int64 ReqId;
					const auto Request = BeamBackendSystem->CreateAuthenticatedRequest(ReqId, FakeRealmHandle, FakeSimpleRetryConfig, FakeAuthToken, FakeRequest);

					Callbacks->ExpectedReqId = ReqId;
					// We expect to fail transparently for the automatic re-auth case.
					Callbacks->ExpectedErrorFailureCount = bIsAutomaticReAuth ? 0 : 1;
					Callbacks->ExpectedErrorResponseStatus = Error.status;
					Callbacks->ExpectedErrorResponseError = Error.error;
					Callbacks->ExpectedErrorResponseService = Error.service;
					Callbacks->ExpectedErrorResponseMessage = Error.message;

					FOnMockSuccess ResponseHandler;
					ResponseHandler.BindUFunction(Callbacks, FName(TEXT("MockSuccessCallback_Fail")));

					FOnMockError ResponseHandlerError;
					if (bIsAutomaticReAuth)
						ResponseHandlerError.BindUFunction(Callbacks, FName(TEXT("MockErrorCallback_Fail")));
					else
						ResponseHandlerError.BindUFunction(Callbacks, FName(TEXT("MockErrorCallback_Expected")));

					FOnMockComplete ResponseHandlerComplete;
					ResponseHandlerComplete.BindUFunction(Callbacks, FName(TEXT("MockCompleteCallback_Expected")));

					// This should clean up the created request's data
					BeamBackendSystem->ProcessAuthenticatedBlueprintRequest<UBeamMockGetRequest, UBeamMockGetRequestResponse>
					(RetryableErrorCode, ResponseBody, TUnrealRequestStatus::Failed, ReqId, FakeRealmHandle, FakeAuthToken, FakeRequest, ResponseHandler, ResponseHandlerError,
					 ResponseHandlerComplete);

					// Assert that the request was correctly enqueued for work
					FRequestToRetry RetryReq;
					TestTrue("Test that the Retry was enqueued", BeamBackendSystem->EnqueuedRetries.Dequeue(RetryReq));
					TestTrue("Enqueued Retry's Request Id is equal", RetryReq.RequestId == ReqId);
					TestTrue("Enqueued Retry's Realm Handle is the same", RetryReq.RealmHandle == FakeRealmHandle);
					TestTrue("Enqueued Retry's AuthToken is the same", RetryReq.AuthToken == FakeAuthToken);
					TestTrue("Enqueued Retry's IsBlueprint is on", RetryReq.IsBlueprint == 1);
					if (bIsAutomaticReAuth)
					{
						TestTrue("Test that the Retry was enqueued but with no failure count",
						         BeamBackendSystem->InFlightFailureCount[ReqId] == Callbacks->ExpectedErrorFailureCount);
					}
				}

				// Authenticated Code Handler 
				{
					int64 ReqId;
					const auto Request = BeamBackendSystem->CreateAuthenticatedRequest(ReqId, FakeRealmHandle, FakeSimpleRetryConfig, FakeAuthToken, FakeRequest);

					Callbacks->ExpectedReqId = ReqId;
					// We expect to fail transparently for the automatic re-auth case.
					Callbacks->ExpectedErrorFailureCount = bIsAutomaticReAuth ? 0 : 1;
					Callbacks->ExpectedErrorResponseStatus = Error.status;
					Callbacks->ExpectedErrorResponseError = Error.error;
					Callbacks->ExpectedErrorResponseService = Error.service;
					Callbacks->ExpectedErrorResponseMessage = Error.message;

					FOnMockFullResponse ResponseHandler;
					ResponseHandler.BindLambda([=, this](FBeamFullResponse<UBeamMockGetRequest*, UBeamMockGetRequestResponse*> BeamFullResponse)
					{
						if (bIsAutomaticReAuth)
						{
							TestTrue("Callback was not called", false);
						}
						else
						{
							TestTrue("State was Retrying", BeamFullResponse.State == EBeamFullResponseState::Retrying);
							Callbacks->MockErrorCallback_Expected(BeamFullResponse.Context, BeamFullResponse.RequestData, BeamFullResponse.ErrorData);
						}
					});

					// This should clean up the created request's data
					BeamBackendSystem->ProcessAuthenticatedCodeRequest(RetryableErrorCode, ResponseBody, TUnrealRequestStatus::Failed, ReqId, FakeRealmHandle, FakeAuthToken, FakeRequest,
					                                                   ResponseHandler);

					// Assert that the request was correctly enqueued for work
					FRequestToRetry RetryReq;
					TestTrue("Test that the Retry was enqueued", BeamBackendSystem->EnqueuedRetries.Dequeue(RetryReq));
					TestTrue("Enqueued Retry's Request Id is equal", RetryReq.RequestId == ReqId);
					TestTrue("Enqueued Retry's Realm Handle is the same", RetryReq.RealmHandle == FakeRealmHandle);
					TestTrue("Enqueued Retry's AuthToken is the same", RetryReq.AuthToken == FakeAuthToken);
					TestTrue("Enqueued Retry's IsBlueprint is off", RetryReq.IsBlueprint == 0);
					if (bIsAutomaticReAuth)
					{
						TestTrue("Test that the Retry was enqueued but with no failure count",
						         BeamBackendSystem->InFlightFailureCount[ReqId] == Callbacks->ExpectedErrorFailureCount);
					}
				}

				// Clean up fake request
				FakeRequest->MarkAsGarbage();
			}
		});

		It("should update the connectivity status if we fail with TUnrealRequestStatus::Failed_ConnectionError", [=, this]()
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
					(500, ResponseBody, TUnrealRequestStatus::Failed_ConnectionError, ReqId, FakeRequest, ResponseHandler, ResponseHandlerError, ResponseHandlerComplete);

				TestTrue("Is No Longer Connected", !BeamBackendSystem->CurrentConnectivityStatus.IsConnected);
				TestTrue("Flagged Request as Completed", BeamBackendSystem->InFlightRequestContexts.FindRef(ReqId).BeamStatus == Completed);
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
				(500, ResponseBody, TUnrealRequestStatus::Failed_ConnectionError, ReqId, FakeRealmHandle, FakeAuthToken, FakeRequest, ResponseHandler, ResponseHandlerError,
				 ResponseHandlerComplete);
				TestTrue("Is No Longer Connected", !BeamBackendSystem->CurrentConnectivityStatus.IsConnected);
				TestTrue("Flagged Request as Completed", BeamBackendSystem->InFlightRequestContexts.FindRef(ReqId).BeamStatus == Completed);
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
				ResponseHandler.BindLambda([=, this](FBeamFullResponse<UBeamMockGetRequest*, UBeamMockGetRequestResponse*> BeamFullResponse)
				{
					TestTrue("State was Error", BeamFullResponse.State == EBeamFullResponseState::Error);
					Callbacks->MockErrorCallback_Expected(BeamFullResponse.Context, BeamFullResponse.RequestData, BeamFullResponse.ErrorData);
				});

				// This should clean up the created request's data
				BeamBackendSystem->ProcessCodeRequest(500, ResponseBody, TUnrealRequestStatus::Failed_ConnectionError, ReqId, FakeRequest, ResponseHandler);
				TestTrue("Is No Longer Connected", !BeamBackendSystem->CurrentConnectivityStatus.IsConnected);
				TestTrue("Flagged Request as Completed", BeamBackendSystem->InFlightRequestContexts.FindRef(ReqId).BeamStatus == Completed);
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
				ResponseHandler.BindLambda([=, this](FBeamFullResponse<UBeamMockGetRequest*, UBeamMockGetRequestResponse*> BeamFullResponse)
				{
					TestTrue("State was Error", BeamFullResponse.State == EBeamFullResponseState::Error);
					Callbacks->MockErrorCallback_Expected(BeamFullResponse.Context, BeamFullResponse.RequestData, BeamFullResponse.ErrorData);
				});

				// This should clean up the created request's data
				BeamBackendSystem->ProcessAuthenticatedCodeRequest(500, ResponseBody, TUnrealRequestStatus::Failed_ConnectionError, ReqId, FakeRealmHandle, FakeAuthToken, FakeRequest,
				                                                   ResponseHandler);
				TestTrue("Is No Longer Connected", !BeamBackendSystem->CurrentConnectivityStatus.IsConnected);
				TestTrue("Flagged Request as Completed", BeamBackendSystem->InFlightRequestContexts.FindRef(ReqId).BeamStatus == Completed);
			}

			FakeRequest->MarkAsGarbage();
		});

		LatentIt("should create and send a BP request, cancel it mid-flight and ignore it's response", [=, this](const FDoneDelegate& Done)
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

		LatentIt("should create and send an Authenticated BP request, cancel it mid-flight and ignore it's response", [=, this](const FDoneDelegate& Done)
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

		LatentIt("should create and send a Code request, cancel it mid-flight and ignore it's response", [=, this](const FDoneDelegate& Done)
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
				TestTrue("Response state was Cancelled", FullResponse.State == Cancelled);
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

		LatentIt("should create and send an Authenticated Code request, cancel it mid-flight and ignore it's response", [=, this](const FDoneDelegate& Done)
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
				TestTrue("Response state was Cancelled", FullResponse.State == Cancelled);
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


		It("should clean up requests tagged as completed", [=, this]()
		{
			UBeamMockGetRequest* FakeRequest = NewObject<UBeamMockGetRequest>();

			// Authenticated Code Handler 
			int64 ReqId;
			const auto Request = BeamBackendSystem->CreateAuthenticatedRequest(ReqId, FakeRealmHandle, FakeSimpleRetryConfig, FakeAuthToken, FakeRequest);

			// Pretend that the failure count was increased
			BeamBackendSystem->InFlightFailureCount[ReqId] = 1;

			const auto BeamRequestContext = BeamBackendSystem->InFlightRequestContexts.Find(ReqId);
			BeamRequestContext->BeamStatus = Completed;
			BeamBackendSystem->TickCleanUp(0);

			TestFalse("In Flight Request was cleaned up", BeamBackendSystem->InFlightRequests.Contains(ReqId));
			TestFalse("In Flight Request Context was cleaned up", BeamBackendSystem->InFlightRequestContexts.Contains(ReqId));
			TestFalse("In Flight Failure Count Data was cleaned up", BeamBackendSystem->InFlightFailureCount.Contains(ReqId));
			TestFalse("In Flight Req Id was removed from Cancelled List", BeamBackendSystem->InFlightRequestsCancelled.Contains(ReqId));
			TestFalse("In Flight Request Data was cleaned up", BeamBackendSystem->InFlightRequestData.Contains(*BeamRequestContext));
			TestFalse("In Flight Response Data was cleaned up", BeamBackendSystem->InFlightResponseBodyData.Contains(*BeamRequestContext));

			FakeRequest->MarkAsGarbage();
		});
	});

	Describe("Retry Configurations", [this]()
	{
		const FUserSlot TestUserSlot{"TestSlot"};
		const FRequestType RequestType{ULoginRefreshTokenRequest::StaticClass()->GetName()};

		BeforeEach([this]()
		{
			BeamBackendSystem = GEngine->GetEngineSubsystem<UBeamBackend>();
		});

		AfterEach([=, this]()
		{
			// If these aren't working it'll break the tests below, so we don't explicitly test for these.
			BeamBackendSystem->ResetRetryConfigForRequestType(RequestType);
			BeamBackendSystem->ResetRetryConfigForUserSlot(TestUserSlot);
			BeamBackendSystem->ResetRetryConfigForUserSlotAndRequestType(TestUserSlot, RequestType);
		});

		It("should override a specific request type's retry configuration", [=, this]()
		{
			auto ExpectedOverridenConfig = BeamBackendSystem->DefaultRetryConfig;
			ExpectedOverridenConfig.Timeout = -5;
			BeamBackendSystem->SetRetryConfigForRequestType(RequestType, ExpectedOverridenConfig);

			FBeamRetryConfig ActualConfig;
			BeamBackendSystem->GetRetryConfigForRequestType(RequestType, ActualConfig);

			TestTrue("Overriden Retry Config for Request Type", ExpectedOverridenConfig.Timeout == ActualConfig.Timeout);
		});

		It("should override a specific user's retry configuration", [=, this]()
		{
			auto ExpectedOverridenConfig = BeamBackendSystem->DefaultRetryConfig;
			ExpectedOverridenConfig.Timeout = -5;
			BeamBackendSystem->SetRetryConfigForUserSlot(TestUserSlot, ExpectedOverridenConfig);

			FBeamRetryConfig ActualConfig;
			BeamBackendSystem->GetRetryConfigForUserSlot(TestUserSlot, ActualConfig);

			TestTrue("Overriden Retry Config for Request Type", ExpectedOverridenConfig.Timeout == ActualConfig.Timeout);
		});

		It("should override a specific user specific requests's retry configuration", [=, this]()
		{
			auto ExpectedOverridenConfig = BeamBackendSystem->DefaultRetryConfig;
			ExpectedOverridenConfig.Timeout = -5;
			BeamBackendSystem->SetRetryConfigForUserSlotAndRequestType(TestUserSlot, RequestType, ExpectedOverridenConfig);

			FBeamRetryConfig ActualConfig;
			BeamBackendSystem->GetRetryConfigForUserSlotAndRequestType(RequestType, TestUserSlot, ActualConfig);

			TestTrue("Overriden Retry Config for Request Type", ExpectedOverridenConfig.Timeout == ActualConfig.Timeout);
		});

		It("should fallback correctly to the request type's retry configuration", [=, this]()
		{
			auto ExpectedOverridenConfig = BeamBackendSystem->DefaultRetryConfig;
			ExpectedOverridenConfig.Timeout = -5;
			BeamBackendSystem->SetRetryConfigForRequestType(RequestType, ExpectedOverridenConfig);

			FBeamRetryConfig ActualConfig;
			BeamBackendSystem->GetRetryConfigForUserSlotAndRequestType(RequestType, TestUserSlot, ActualConfig);

			TestTrue("Overriden Retry Config for Request Type", ExpectedOverridenConfig.Timeout == ActualConfig.Timeout);
		});

		It("should fallback correctly to the default retry configuration", [=, this]()
		{
			const auto ExpectedOverridenConfig = BeamBackendSystem->DefaultRetryConfig;

			FBeamRetryConfig ActualConfig;
			BeamBackendSystem->GetRetryConfigForUserSlotAndRequestType(RequestType, TestUserSlot, ActualConfig);
			TestTrue("Overriden Retry Config for Request Type", ExpectedOverridenConfig.Timeout == ActualConfig.Timeout);

			BeamBackendSystem->GetRetryConfigForRequestType(RequestType, ActualConfig);
			TestTrue("Overriden Retry Config for Request Type", ExpectedOverridenConfig.Timeout == ActualConfig.Timeout);
		});
	});

	Describe("Retry Logic", [this]()
	{
		const FBeamRealmHandle FakeRealmHandle{"TEST_CID", "TEST_PID"};
		const FBeamRetryConfig FakeSimpleRetryConfig{10, TArray<float>{0.5, 1}, 1};
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
			*BeamBackendSystem->InFlightRequestId = -1;
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

		It("should begin processing a request enqueued for retry", [=, this]()
		{
			UBeamMockGetRequest* FakeRequest = NewObject<UBeamMockGetRequest>();

			// Authenticated Code Handler 
			int64 ReqId;
			const auto Request = BeamBackendSystem->CreateAuthenticatedRequest(ReqId, FakeRealmHandle, FakeSimpleRetryConfig, FakeAuthToken, FakeRequest);

			// Pretend that the failure count was increased
			BeamBackendSystem->InFlightFailureCount[ReqId] = 1;


			// Enqueues the request to retry.
			const auto ExpectedRetry = FRequestToRetry{
				ReqId, 0, 503, FakeRealmHandle, FakeAuthToken,
			};
			BeamBackendSystem->EnqueuedRetries.Enqueue(ExpectedRetry);

			constexpr auto ExpectedAccumulatedTime = 0.25f;
			BeamBackendSystem->TickRetryQueue(ExpectedAccumulatedTime);

			const auto ProcessingRequest = BeamBackendSystem->InFlightProcessingRequests[0];

			TestTrue("Retry Data is as expected", ProcessingRequest.RequestToRetry == ExpectedRetry);
			TestTrue("wait time correctly set", ProcessingRequest.TimeToWait == FakeSimpleRetryConfig.RetryFalloffValues[0]);
			TestTrue("accumulated time was correctly set", ProcessingRequest.AccumulatedTime == ExpectedAccumulatedTime);
			TestTrue("accumulated time was correctly set", ProcessingRequest.AccumulatedTime == ExpectedAccumulatedTime);

			FakeRequest->MarkAsGarbage();
		});


		TArray NonAuthRetryErrorCodes = UBeamBackend::NON_AUTH_REQUESTS_RETRY_ALLOWED_ERRORS;
		TArray AuthRetryErrorCodes = UBeamBackend::AUTH_REQUESTS_RETRY_ALLOWED_ERRORS;

		for (const auto& RetryErrorCode : NonAuthRetryErrorCodes)
		{
			LatentIt(FString::Format(TEXT("should call the process request when failing a non-authenticated request with {0}"), {RetryErrorCode}), [=, this](FDoneDelegate Done)
			{
				// We actually need the request to go out
				FHttpModule::Get().ToggleNullHttp(false);

				UBeamMockGetRequest* FakeRequest = NewObject<UBeamMockGetRequest>();

				int64 ReqId;
				const auto Request = BeamBackendSystem->CreateRequest(ReqId, FakeRealmHandle, FakeSimpleRetryConfig, FakeRequest);

				// Pretend that the failure count was increased
				BeamBackendSystem->InFlightFailureCount[ReqId] = 1;

				// Bind a fake lambda just so we know that the request had process request called on it.				
				Request->OnProcessRequestComplete()
				       .BindLambda([this, Done](TSharedPtr<IHttpRequest, ESPMode::ThreadSafe>, TSharedPtr<IHttpResponse, ESPMode::ThreadSafe> HttpResponse, bool sent)
				       {
					       UE_LOG(LogTemp, Display, TEXT("Process Request was called in the failed request!!!"));
					       TestTrue("Callback was called", true);
					       Done.Execute();
				       });

				// Enqueues the request to retry.
				const auto ExpectedRetry = FRequestToRetry{
					ReqId, 0, RetryErrorCode, FakeRealmHandle,
				};
				BeamBackendSystem->EnqueuedRetries.Enqueue(ExpectedRetry);

				// Set the delta time to be enough time to trigger the retry of the fake request
				constexpr auto ExpectedAccumulatedTime = 0.75f;
				BeamBackendSystem->TickRetryQueue(ExpectedAccumulatedTime);
			});
		}

		for (const auto& RetryErrorCode : AuthRetryErrorCodes)
		{
			LatentIt(FString::Format(TEXT("should call the process request when failing an authenticated request with {0}"), {RetryErrorCode}), [=, this](FDoneDelegate Done)
			{
				// We actually need the request to go out
				FHttpModule::Get().ToggleNullHttp(false);

				UBeamMockGetRequest* FakeRequest = NewObject<UBeamMockGetRequest>();

				int64 ReqId;
				const auto Request = BeamBackendSystem->CreateAuthenticatedRequest(ReqId, FakeRealmHandle, FakeSimpleRetryConfig, FakeAuthToken, FakeRequest);

				// Pretend that the failure count was increased
				BeamBackendSystem->InFlightFailureCount[ReqId] = 1;

				// Bind a fake lambda just so we know that the request had process request called on it.				
				Request->OnProcessRequestComplete()
				       .BindLambda([this, Done](TSharedPtr<IHttpRequest, ESPMode::ThreadSafe>, TSharedPtr<IHttpResponse, ESPMode::ThreadSafe> HttpResponse, bool sent)
				       {
					       UE_LOG(LogTemp, Display, TEXT("Process Request was called in the failed request!!!"));
					       TestTrue("Callback was called", true);
					       Done.Execute();
				       });

				// Enqueues the request to retry.
				const auto ExpectedRetry = FRequestToRetry{
					ReqId, 0, RetryErrorCode, FakeRealmHandle, FakeAuthToken,
				};
				BeamBackendSystem->EnqueuedRetries.Enqueue(ExpectedRetry);

				// Set the delta time to be enough time to trigger the retry of the fake request
				constexpr auto ExpectedAccumulatedTime = 0.75f;
				BeamBackendSystem->TickRetryQueue(ExpectedAccumulatedTime);
			});
		}
	});

	Describe("Connectivity", [this]()
	{
		BeforeEach([this]()
		{
			BeamBackendSystem = GEngine->GetEngineSubsystem<UBeamBackend>();
			StatusAtTestRunStart = BeamBackendSystem->CurrentConnectivityStatus;
		});

		AfterEach([=, this]()
		{
			BeamBackendSystem->CurrentConnectivityStatus = StatusAtTestRunStart;

			// Clear all Delegates we set during the test.
			for (const auto& RegisteredDelegatesDuringConnectivityTest : RegisteredDelegatesDuringConnectivityTests)
				BeamBackendSystem->GlobalConnectivityChangedCodeHandler.Remove(RegisteredDelegatesDuringConnectivityTest);
		});

		It("should turn the connectivity off and call connection changed callback", [=, this]()
		{
			constexpr int64 ExpectedRequestId = 10;
			const FString ExpectedRequestType = UBeamMockGetRequest::StaticClass()->GetName();


			const auto Handler = BeamBackendSystem->GlobalConnectivityChangedCodeHandler.AddLambda(
				[=, this](const FBeamRequestContext& RequestCtx, const FRequestType& RequestType, const bool bConnected)
				{
					TestTrue("RequestId was forwarded correctly", RequestCtx.RequestId == ExpectedRequestId);
					TestTrue("RequestType was forwarded correctly", RequestType == FRequestType{ExpectedRequestType});
					TestTrue("Connectivity properly updated", !bConnected);
				});
			RegisteredDelegatesDuringConnectivityTests.Add(Handler);

			BeamBackendSystem->UpdateConnectivity(FBeamRequestContext{ExpectedRequestId}, EHttpRequestStatus::Failed_ConnectionError, FRequestType{ExpectedRequestType});
		});

		It("should turn the connectivity on when receiving a successful response and call connection changed callback", [=, this]()
		{
			constexpr int64 ExpectedRequestId = 10;
			const FString ExpectedRequestType = UBeamMockGetRequest::StaticClass()->GetName();

			// Turn connectivity off first
			BeamBackendSystem->UpdateConnectivity(FBeamRequestContext{ExpectedRequestId}, EHttpRequestStatus::Failed_ConnectionError, FRequestType{ExpectedRequestType});

			// Set callback to assert that it gets turned back on
			const auto Handler = BeamBackendSystem->GlobalConnectivityChangedCodeHandler.AddLambda(
				[=, this](const FBeamRequestContext& RequestCtx, const FRequestType& RequestType, const bool bConnected)
				{
					TestTrue("RequestId was forwarded correctly", RequestCtx.RequestId == ExpectedRequestId);
					TestTrue("RequestType was forwarded correctly", RequestType == FRequestType{ExpectedRequestType});
					TestTrue("Connectivity properly updated", bConnected);
				});
			RegisteredDelegatesDuringConnectivityTests.Add(Handler);

			BeamBackendSystem->UpdateConnectivity(FBeamRequestContext{ExpectedRequestId}, EHttpRequestStatus::Succeeded, FRequestType{ExpectedRequestType});
		});

		It("should turn the connectivity on when receiving a failed (for non-connection issues) response and call connection changed callback", [=, this]()
		{
			constexpr int64 ExpectedRequestId = 10;
			const FString ExpectedRequestType = UBeamMockGetRequest::StaticClass()->GetName();

			// Turn connectivity off first
			BeamBackendSystem->UpdateConnectivity(FBeamRequestContext{ExpectedRequestId}, EHttpRequestStatus::Failed_ConnectionError, FRequestType{ExpectedRequestType});

			// Set callback to assert that it gets turned back on
			const auto Handler = BeamBackendSystem->GlobalConnectivityChangedCodeHandler.AddLambda(
				[=, this](const FBeamRequestContext& RequestCtx, const FRequestType& RequestType, const bool bConnected)
				{
					TestTrue("RequestId was forwarded correctly", RequestCtx.RequestId == ExpectedRequestId);
					TestTrue("RequestType was forwarded correctly", RequestType == FRequestType{ExpectedRequestType});
					TestTrue("Connectivity properly updated", bConnected);
				});
			RegisteredDelegatesDuringConnectivityTests.Add(Handler);

			BeamBackendSystem->UpdateConnectivity(FBeamRequestContext{ExpectedRequestId}, EHttpRequestStatus::Failed, FRequestType{ExpectedRequestType});
		});

		It("should not call connection changed callback when getting repeated Successfull/Failed errors", [=, this]()
		{
			constexpr int64 ExpectedRequestId = 10;
			const FString ExpectedRequestType = UBeamMockGetRequest::StaticClass()->GetName();

			// Set callback to assert that it gets turned back on
			const auto Handler = BeamBackendSystem->GlobalConnectivityChangedCodeHandler.AddLambda(
				[=, this](const FBeamRequestContext& RequestCtx, const FRequestType& RequestType, const bool bConnected)
				{
					TestTrue("you should not be seeing this", false);
				});
			BeamBackendSystem->UpdateConnectivity(FBeamRequestContext{ExpectedRequestId}, EHttpRequestStatus::Succeeded, FRequestType{ExpectedRequestType});
			BeamBackendSystem->UpdateConnectivity(FBeamRequestContext{ExpectedRequestId}, EHttpRequestStatus::Failed, FRequestType{ExpectedRequestType});

			RegisteredDelegatesDuringConnectivityTests.Add(Handler);
		});

		It("should not call connection changed callback when getting repeated Failed Connection Errors", [=, this]()
		{
			constexpr int64 ExpectedRequestId = 10;
			const FString ExpectedRequestType = UBeamMockGetRequest::StaticClass()->GetName();

			// Turn off connectivity first
			BeamBackendSystem->UpdateConnectivity(FBeamRequestContext{ExpectedRequestId}, EHttpRequestStatus::Failed_ConnectionError, FRequestType{ExpectedRequestType});
			// Set callback to assert that if it remains off the callback won't be called
			const auto Handler = BeamBackendSystem->GlobalConnectivityChangedCodeHandler.AddLambda(
				[=, this](const FBeamRequestContext& RequestCtx, const FRequestType& RequestType, const bool bConnected)
				{
					TestTrue("you should not be seeing this", false);
				});
			// Turn it off again
			BeamBackendSystem->UpdateConnectivity(FBeamRequestContext{ExpectedRequestId}, EHttpRequestStatus::Failed_ConnectionError, FRequestType{ExpectedRequestType});

			RegisteredDelegatesDuringConnectivityTests.Add(Handler);
		});
	});
}
