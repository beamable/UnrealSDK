#include "Engine/Engine.h"
#include "Misc/AutomationTest.h"

#include "BeamBackend.h"
#include "RawAPIs/Auth/BeamAuthApi.h"

BEGIN_DEFINE_SPEC(FBeamBackendSpec, "BeamableUnreal.BeamBackend", EAutomationTestFlags::ProductFilter | EAutomationTestFlags::ApplicationContextMask)
	UBeamBackend* BeamBackendSystem;
	UBeamAuthApi* AuthApi;
END_DEFINE_SPEC(FBeamBackendSpec)

void FBeamBackendSpec::Define()
{
	Describe("Request/Response", [this]()
	{
		USTRUCT()
		struct FBeamFakeBody : public FBeamJsonSerializable
		{
			UPROPERTY()
			int FakeInt;

			virtual void BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const override
			{
				Serializer->WriteValue("fake_int", FakeInt);
			}

			virtual void BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag) override
			{
				FakeInt = Bag->GetIntegerField("fake_int");
			}
		};

		USTRUCT()
		struct FBeamFakeGetRequest : public FBeamBaseRequest
		{
			virtual void BuildVerb(FString& VerbString) const override { VerbString = TEXT("GET"); }
			virtual void BuildBody(FString& BodyString) const override { BodyString = TEXT(""); }
			virtual void BuildRoute(FString& RouteString) const override { RouteString.Appendf(TEXT("/fake/url")); }
		};

		USTRUCT()
		struct FBeamFakePostRequest : public FBeamBaseRequest
		{
			UPROPERTY()
			FBeamFakeBody Body;

			virtual void BuildVerb(FString& VerbString) const override { VerbString = TEXT("POST"); }

			virtual void BuildBody(FString& BodyString) const override
			{
				TUnrealJsonSerializer JsonSerializer = TJsonStringWriter<TCondensedJsonPrintPolicy<wchar_t>>::Create(&BodyString);
				Body.BeamSerialize(JsonSerializer);
				JsonSerializer->Close();
			}

			virtual void BuildRoute(FString& RouteString) const override { RouteString.Appendf(TEXT("/fake/url")); }
		};

		BeforeEach([this]()
		{
			BeamBackendSystem = GEngine->GetEngineSubsystem<UBeamBackend>();
			AuthApi = GEngine->GetEngineSubsystem<UBeamAuthApi>();
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
			BeamBackendSystem->InFlightRetryConfigs.Reset();
			BeamBackendSystem->InFlightRequestsCancelled.Reset();

			// Clear all Enqueued Retries
			BeamBackendSystem->EnqueuedRetries.Empty();
			BeamBackendSystem->InFlightProcessingRequests.Reset();

			// Clear all Global Handlers
			BeamBackendSystem->GlobalRequestErrorHandler.Clear();
			BeamBackendSystem->GlobalRequestErrorCodeHandler.Unbind();
		});

		It("should be preparing Requests InFlightRequest correctly", [this]()
		{
			// Replace callback that actually gets the prepared request and sends it out, with one that we can validate the data is correctly set up and then cancel the request.
			BeamBackendSystem->ExecuteRequestDelegate.BindLambda([this](FBeamRequestContext RequestContext, FBeamConnectivity& Connectivity, int ActiveRequestId)
			{
				TestTrue("Number of Requests == 1", BeamBackendSystem->InFlightRequests.Num() == 1);

				auto BuiltRequest = BeamBackendSystem->InFlightRequests[ActiveRequestId];
				TestTrue("Verb is Set Correctly == 'POST'", BeamBackendSystem->InFlightRequests[ActiveRequestId]->GetVerb() == TEXT("POST"));
				TestTrue("Route is Set Correctly == '/basic/realms/customer'", BeamBackendSystem->InFlightRequests[ActiveRequestId]->GetURL().Contains(TEXT("/basic/realms/customer")));
				TestTrue("Outgoing request has a binding", BuiltRequest->OnProcessRequestComplete().IsBound());

				// This will not send the request but still trigger the OnProcessRequestComplete callback, so we unbind it.
				BuiltRequest->OnProcessRequestComplete().Unbind();
				BuiltRequest->ProcessRequest();
				BeamBackendSystem->InFlightRequests.Remove(ActiveRequestId);
			});

			// Calls the Create request function.
			const auto OutRequest = FRegisterCustomerRequest{
				FRegisterCustomerRequestBody{
					TEXT("test@test.com"), TEXT("testing"), TEXT("Mr.Test"), TEXT("MegaTester123!"), TEXT("Soo much testing!")
				}
			};
			const auto ResponseHandler = FOnRegisterCustomerFullResponse::CreateLambda([](FRegisterCustomerFullResponse FullResponse)
			{
			});
			AuthApi->CPP_RegisterCustomerRequest(OutRequest, ResponseHandler);
		});

		LatentIt("should be cancelling requests correctly", [this](const FDoneDelegate& Done)
		{
			// We actually need the request to go out
			FHttpModule::Get().ToggleNullHttp(false);

			// Calls the Create request function.
			const auto OutRequest = FRegisterCustomerRequest{
				FRegisterCustomerRequestBody{
					TEXT("test@test.com"), TEXT("testing"), TEXT("Mr.Test"), TEXT("MegaTester123!"), TEXT("Soo much testing!")
				}
			};
			const auto ResponseHandler = FOnRegisterCustomerFullResponse::CreateLambda([this, Done](FRegisterCustomerFullResponse FullResponse)
			{
				TestTrue("Response state was Cancelled", FullResponse.State == Cancelled);
				TestTrue("Response state was Cancelled on the first attempt", FullResponse.AttemptNumber == 0);
				Done.Execute();
			});
			// Let's cancel the first request that is going out.
			AuthApi->CPP_RegisterCustomerRequest(OutRequest, ResponseHandler);
			// Cancel the last request that was made
			BeamBackendSystem->CancelRequest(*BeamBackendSystem->InFlightRequestId);
		});

		// TODO: Change Generated APIs to use CreateRequest(...) and CreateAuthenticatedRequest(...) instead of the current CreateRequest + PrepareCalls.
		// TODO: Keep the processor thing separate (just merge the PrepareXXX calls into the CreateXXX calls.

		// Request
		//  - Test that we are correctly setting up the retry configuration and timeout when we create a request.
		//  - Test that Prepare Request To Realm (W/ and W/o AuthToken are adding the proper headers).
		//  - Test the Verb/Route/Body are correctly being set up in the Unreal Request.
		//  - Test that the processor correctly yields a lambda that is correctly bound (CheckCallable).
		//  - Test that we can discard unset requests correctly and all state regarding the InFlight Requests is cleaned up.
		//  - Test that we can cancel sent requests and that in doing so we invoke the Complete callback anyway.
		//  - Test that we can check whether or not a request is cancelled via its request id during the Complete callback		

		// Response (for each Processor method) --- All 4 should be under the same describe because all 4 processors are expected to yield the same behaviour.
		//  - Test success handler is called when a 200 response comes in.
		//  - Test error handler is called when a non-200 response comes in.
		//    - Test that we can get the Failure Count for a request via its ID during the OnError Callback.
		//  - Test that retry is enqueued and failure count is properly incremented when correct error codes are received.		
		//  - Test complete handler is always called with the correct request data and after the individual error/success handlers.
	});

	Describe("Retry Configurations", [this]()
	{
		const FUserSlot TestUserSlot{"TestSlot"};
		const FRequestType RequestType{FLoginRefreshTokenRequest::StaticStruct()->GetName()};

		BeforeEach([this]()
		{
			BeamBackendSystem = GEngine->GetEngineSubsystem<UBeamBackend>();
		});

		AfterEach([=, this]()
		{
			// If these aren't working it'll break the tests below, so we don't explicitly test for these.
			BeamBackendSystem->ResetRetryConfigForRequestType(RequestType);
			BeamBackendSystem->ResetRetryConfigForUser(TestUserSlot);
			BeamBackendSystem->ResetRetryConfigForUserAndRequestType(TestUserSlot, RequestType);
		});

		It("should override a specific request type's retry configuration", [=, this]()
		{
			auto ExpectedOverridenConfig = BeamBackendSystem->DefaultRetryConfig;
			ExpectedOverridenConfig.Timeout = -5;
			BeamBackendSystem->SetRetryConfigForRequestType(RequestType, ExpectedOverridenConfig);

			FBeamRetryConfig ActualConfig;
			BeamBackendSystem->GetRetryConfig<FLoginRefreshTokenRequest>(ActualConfig);

			TestTrue("Overriden Retry Config for Request Type", ExpectedOverridenConfig.Timeout == ActualConfig.Timeout);
		});

		It("should override a specific user's retry configuration", [=, this]()
		{
			auto ExpectedOverridenConfig = BeamBackendSystem->DefaultRetryConfig;
			ExpectedOverridenConfig.Timeout = -5;
			BeamBackendSystem->SetRetryConfigForUser(TestUserSlot, ExpectedOverridenConfig);

			FBeamRetryConfig ActualConfig;
			BeamBackendSystem->GetRetryConfig<FLoginRefreshTokenRequest>(TestUserSlot, ActualConfig);

			TestTrue("Overriden Retry Config for Request Type", ExpectedOverridenConfig.Timeout == ActualConfig.Timeout);
		});

		It("should override a specific user specific requests's retry configuration", [=, this]()
		{
			auto ExpectedOverridenConfig = BeamBackendSystem->DefaultRetryConfig;
			ExpectedOverridenConfig.Timeout = -5;
			BeamBackendSystem->SetRetryConfigForUserAndRequestType(TestUserSlot, RequestType, ExpectedOverridenConfig);

			FBeamRetryConfig ActualConfig;
			BeamBackendSystem->GetRetryConfig<FLoginRefreshTokenRequest>(TestUserSlot, ActualConfig);

			TestTrue("Overriden Retry Config for Request Type", ExpectedOverridenConfig.Timeout == ActualConfig.Timeout);
		});

		It("should fallback correctly to the request type's retry configuration", [=, this]()
		{
			auto ExpectedOverridenConfig = BeamBackendSystem->DefaultRetryConfig;
			ExpectedOverridenConfig.Timeout = -5;
			BeamBackendSystem->SetRetryConfigForRequestType(RequestType, ExpectedOverridenConfig);

			FBeamRetryConfig ActualConfig;
			BeamBackendSystem->GetRetryConfig<FLoginRefreshTokenRequest>(TestUserSlot, ActualConfig);

			TestTrue("Overriden Retry Config for Request Type", ExpectedOverridenConfig.Timeout == ActualConfig.Timeout);
		});

		It("should fallback correctly to the default retry configuration", [=, this]()
		{
			const auto ExpectedOverridenConfig = BeamBackendSystem->DefaultRetryConfig;

			FBeamRetryConfig ActualConfig;
			BeamBackendSystem->GetRetryConfig<FLoginRefreshTokenRequest>(TestUserSlot, ActualConfig);
			TestTrue("Overriden Retry Config for Request Type", ExpectedOverridenConfig.Timeout == ActualConfig.Timeout);

			BeamBackendSystem->GetRetryConfig<FLoginRefreshTokenRequest>(ActualConfig);
			TestTrue("Overriden Retry Config for Request Type", ExpectedOverridenConfig.Timeout == ActualConfig.Timeout);
		});
	});
}
