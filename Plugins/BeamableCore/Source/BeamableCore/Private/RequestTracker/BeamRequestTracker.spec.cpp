#include "BeamRequestTracker.spec.h"

#include "BeamRequestTrackerTestCallbacks.h"
#include "Engine/Engine.h"
#include "Misc/AutomationTest.h"
#include "HttpModule.h"

#include "BeamBackend/BeamBackend.h"
#include "BeamBackend/BeamBackendTestCallbacks.h"


void FBeamRequestTrackerSpec::Define()
{
	Describe("Wait Handles", [this]()
	{
		const FUserSlot FakeUserSlot{"TestUserSlot"};
		const FBeamRealmHandle FakeRealmHandle{FString("TEST_CID"), FString("TEST_PID")};
		const FBeamRetryConfig FakeNoRetryConfig{{}, {}, 10, TArray<float>{0.5, 1}, 0};
		const FBeamAuthToken FakeAuthToken{"AUTH_TOKEN", "REFRESH_TOKEN"};

		BeforeEach([this]()
		{
			BeamBackendSystem = GEngine->GetEngineSubsystem<UBeamBackend>();
			RequestTrackerSystem = GEngine->GetEngineSubsystem<UBeamRequestTracker>();

			OperationCallbacks = NewObject<UBeamRequestTrackerOperationTestCallbacks>();
			OperationCallbacks->BeamBackend = BeamBackendSystem;
			OperationCallbacks->BeamRequestTracker = RequestTrackerSystem;
			OperationCallbacks->Spec = this;

			WaitAllCallbacks = NewObject<UBeamRequestTrackerWaitAllTestCallbacks>();
			WaitAllCallbacks->BeamBackend = BeamBackendSystem;
			WaitAllCallbacks->BeamRequestTracker = RequestTrackerSystem;
			WaitAllCallbacks->Spec = this;

			FHttpModule::Get().ToggleNullHttp(true);
		});

		AfterEach([this]()
		{
			// Clear callbacks object			
			OperationCallbacks = nullptr;
			WaitAllCallbacks = nullptr;
			
			// Make sure that the execute request delegate is properly set up. 
			BeamBackendSystem->ExecuteRequestDelegate.BindUFunction(BeamBackendSystem, "DefaultExecuteRequestImpl");
			FHttpModule::Get().ToggleNullHttp(false);

			// Reset the request tracker system
			RequestTrackerSystem->OperationHandleId = -1;
			RequestTrackerSystem->ActiveOperations.Reset();
			RequestTrackerSystem->ActiveOperationState.Reset();
			
			RequestTrackerSystem->WaitHandleId = -1;
			RequestTrackerSystem->ActiveWaitHandles.Reset();
			RequestTrackerSystem->ActiveWaitStates.Reset();
			
			
			

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


		It("should correctly configure WaitAll with Context, Operations and/or WaitHandles", [=, this]()
		{
			// Try to configure a wait handle with non-existent 
			{
				// Create a fake request
				UBeamMockGetRequest* FakeGetRequest = NewObject<UBeamMockGetRequest>();
				int64 ReqId;
				const auto Request = BeamBackendSystem->CreateAuthenticatedRequest(ReqId, FakeRealmHandle, FakeNoRetryConfig, FakeAuthToken, FakeGetRequest);

				// Create a fake operation
				FBeamOperationEventHandler Handler;
				Handler.BindUFunction(OperationCallbacks, GET_FUNCTION_NAME_CHECKED(UBeamRequestTrackerOperationTestCallbacks, MockOperationEvent_Fail));
				const auto OpHandle = RequestTrackerSystem->BeginOperation({FakeUserSlot}, GetTestName(), Handler);

				const TArray<FBeamRequestContext> Contexts{FBeamRequestContext{ReqId}};
				const TArray<FBeamOperationHandle> Operations{OpHandle};
				const TArray<FBeamWaitHandle> WaitHandles{};

				FOnWaitComplete FirstOnComplete;
				FirstOnComplete.BindUFunction(WaitAllCallbacks, GET_FUNCTION_NAME_CHECKED(UBeamRequestTrackerWaitAllTestCallbacks, MockWaitCompleteEvent_Fail));
				const auto FirstWaitHandle = RequestTrackerSystem->WaitAll(Contexts, Operations, WaitHandles, FirstOnComplete);

				FOnWaitComplete SecondOnComplete;
				SecondOnComplete.BindUFunction(WaitAllCallbacks, GET_FUNCTION_NAME_CHECKED(UBeamRequestTrackerWaitAllTestCallbacks, MockWaitCompleteEvent_Fail));
				const TArray<FBeamWaitHandle> NewWaitHandles{FirstWaitHandle};
				const auto SecondWaitHandle = RequestTrackerSystem->WaitAll(Contexts, Operations, NewWaitHandles, SecondOnComplete);

				TestTrue("First wait handle was created", RequestTrackerSystem->ActiveWaitHandles.Contains(FirstWaitHandle));
				TestTrue("Second wait handle was created", RequestTrackerSystem->ActiveWaitHandles.Contains(SecondWaitHandle));

				// Discard Request as we are not actually going to make it
				BeamBackendSystem->CancelRequest(ReqId);
				FakeGetRequest->MarkAsGarbage();
			}
		});

		It("should correctly gather all Request Id dependencies for the given WaitHandles", [=, this]()
		{
			// Try to configure a wait handle with non-existent 
			{
				UBeamMockGetRequest* FakeGetRequest = NewObject<UBeamMockGetRequest>();
				UBeamMockGetRequest* FakeGetRequest2 = NewObject<UBeamMockGetRequest>();
				UBeamMockGetRequest* FakeGetRequest3 = NewObject<UBeamMockGetRequest>();

				int64 ReqId;
				int64 ReqId2;
				int64 ReqId3;
				const auto Request = BeamBackendSystem->CreateAuthenticatedRequest(ReqId, FakeRealmHandle, FakeNoRetryConfig, FakeAuthToken, FakeGetRequest);
				const auto Request2 = BeamBackendSystem->CreateAuthenticatedRequest(ReqId2, FakeRealmHandle, FakeNoRetryConfig, FakeAuthToken, FakeGetRequest2);
				const auto Request3 = BeamBackendSystem->CreateAuthenticatedRequest(ReqId3, FakeRealmHandle, FakeNoRetryConfig, FakeAuthToken, FakeGetRequest3);

				// Create a fake operation
				FBeamOperationEventHandler Handler;
				Handler.BindUFunction(OperationCallbacks, GET_FUNCTION_NAME_CHECKED(UBeamRequestTrackerOperationTestCallbacks, MockOperationEvent_Fail));
				const auto OpHandle = RequestTrackerSystem->BeginOperation({FakeUserSlot}, GetTestName(), Handler);
				RequestTrackerSystem->AddRequestToOperation(OpHandle, ReqId2);

				// Create the first wait handle with Req1 and Operation (which contains req2 as a dep)
				const TArray<FBeamRequestContext> FirstContexts{FBeamRequestContext{ReqId}};
				const TArray<FBeamOperationHandle> FirstOperations{OpHandle};
				FOnWaitComplete FirstOnComplete;
				FirstOnComplete.BindUFunction(WaitAllCallbacks, GET_FUNCTION_NAME_CHECKED(UBeamRequestTrackerWaitAllTestCallbacks, MockWaitCompleteEvent_Fail));
				const auto FirstWaitHandle = RequestTrackerSystem->WaitAll(FirstContexts, FirstOperations, {}, FirstOnComplete);

				// Now we assert that if we gather the dependencies for the first wait handle
				const TArray<int64> FirstExpectedRequestDeps{ReqId, ReqId2};
				TArray<int64> GatheredDeps;
				TArray<FBeamOperationHandle> GatheredOperationDeps;
				RequestTrackerSystem->GatherRequestIdsFromWaitHandle(FirstWaitHandle, GatheredDeps, GatheredOperationDeps);
				GatheredDeps.Sort();
				TestEqual("First wait handle's dependencies are correctly gathered", GatheredDeps, FirstExpectedRequestDeps);

				// Then we create a second wait handle with just request 3 + the wait handle that depends on 1 and 2.
				FOnWaitComplete SecondOnComplete;
				SecondOnComplete.BindUFunction(WaitAllCallbacks, GET_FUNCTION_NAME_CHECKED(UBeamRequestTrackerWaitAllTestCallbacks, MockWaitCompleteEvent_Fail));
				const TArray<FBeamWaitHandle> NewWaitHandles{FirstWaitHandle};
				const auto SecondWaitHandle = RequestTrackerSystem->WaitAll({FBeamRequestContext{ReqId3}}, {}, {FirstWaitHandle}, SecondOnComplete);


				const TArray<int64> SecondExpectedRequestDeps{ReqId, ReqId2, ReqId3};
				GatheredDeps.Reset();
				GatheredOperationDeps.Reset();
				RequestTrackerSystem->GatherRequestIdsFromWaitHandle(SecondWaitHandle, GatheredDeps, GatheredOperationDeps);
				GatheredDeps.Sort();
				TestEqual("Second wait handle's dependencies are correctly gathered", GatheredDeps, SecondExpectedRequestDeps);

				// Discard Requests as we are not actually going to make them
				BeamBackendSystem->CancelRequest(ReqId);
				FakeGetRequest->MarkAsGarbage();
				BeamBackendSystem->CancelRequest(ReqId2);
				FakeGetRequest2->MarkAsGarbage();
				BeamBackendSystem->CancelRequest(ReqId3);
				FakeGetRequest3->MarkAsGarbage();
			}
		});

		It("should correctly run the complete callback with correct data", [=, this]()
		{
			// Try to configure a wait handle with non-existent 
			{
				UBeamMockGetRequest* FakeGetRequest = NewObject<UBeamMockGetRequest>();
				UBeamMockGetRequest* FakeGetRequest2 = NewObject<UBeamMockGetRequest>();

				int64 ReqId;
				int64 ReqId2;
				const auto Request = BeamBackendSystem->CreateAuthenticatedRequest(ReqId, FakeRealmHandle, FakeNoRetryConfig, FakeAuthToken, FakeGetRequest);
				const auto Request2 = BeamBackendSystem->CreateAuthenticatedRequest(ReqId2, FakeRealmHandle, FakeNoRetryConfig, FakeAuthToken, FakeGetRequest2);

				// Create a fake operation
				FBeamOperationEventHandler Handler;
				Handler.BindUFunction(OperationCallbacks, GET_FUNCTION_NAME_CHECKED(UBeamRequestTrackerOperationTestCallbacks, MockOperationEvent_Fail));
				const auto OpHandle = RequestTrackerSystem->BeginOperation({FakeUserSlot}, GetTestName(), Handler);
				RequestTrackerSystem->AddRequestToOperation(OpHandle, ReqId2);

				// Create the first wait handle with Req1 and Operation (which contains req2 as a dep)
				const TArray<FBeamRequestContext> FirstContexts{FBeamRequestContext{ReqId}};
				const TArray<FBeamOperationHandle> FirstOperations{OpHandle};
				FOnWaitComplete FirstOnComplete;
				FirstOnComplete.BindUFunction(WaitAllCallbacks, GET_FUNCTION_NAME_CHECKED(UBeamRequestTrackerWaitAllTestCallbacks, MockWaitCompleteEvent_Expected));
				const auto FirstWaitHandle = RequestTrackerSystem->WaitAll(FirstContexts, FirstOperations, {}, FirstOnComplete);

				// Now we assert that if we gather the dependencies for the first wait handle
				const TArray<int64> FirstExpectedRequestDeps{ReqId, ReqId2};
				TArray<int64> GatheredDeps;
				TArray<FBeamOperationHandle> GatheredOperationDeps;
				RequestTrackerSystem->GatherRequestIdsFromWaitHandle(FirstWaitHandle, GatheredDeps, GatheredOperationDeps);
				GatheredDeps.Sort();
				TestEqual("First wait handle's dependencies are correctly gathered", GatheredDeps, FirstExpectedRequestDeps);

				// We forcibly tag the requests as completed here so we can see if the wait callback will trigger
				{
					auto& Ctx = *BeamBackendSystem->InFlightRequestContexts.Find(ReqId);
					Ctx.BeamStatus = AS_Completed;
					auto& Ctx2 = *BeamBackendSystem->InFlightRequestContexts.Find(ReqId2);
					Ctx2.BeamStatus = AS_Completed;
				}

				// Now we run the tick OnRequestCompleted to see if it triggers the WaitComplete callback.
				WaitAllCallbacks->ExpectedContexts = {FBeamRequestContext{ReqId}, FBeamRequestContext{ReqId2}};
				WaitAllCallbacks->ExpectedRequests = {FakeGetRequest, FakeGetRequest2};
				WaitAllCallbacks->ExpectedErrors = {FBeamErrorResponse{}, FBeamErrorResponse{}}; // We expect blank because we don't actually make the requests.
				WaitAllCallbacks->ExpectedResponses = {nullptr, nullptr}; // We expect null because we don't actually make the requests.

				// Tick so that the callback assertions run.
				RequestTrackerSystem->CheckAndCompleteWaitHandles(-1);

				// Discard Requests as we are not actually going to make them
				BeamBackendSystem->CancelRequest(ReqId);
				FakeGetRequest->MarkAsGarbage();
				BeamBackendSystem->CancelRequest(ReqId2);
				FakeGetRequest2->MarkAsGarbage();
			}
		});

		It("should correctly run the complete callback (code) with correct data", [=, this]()
		{
			// Try to configure a wait handle with non-existent 
			{
				UBeamMockGetRequest* FakeGetRequest = NewObject<UBeamMockGetRequest>();
				UBeamMockGetRequest* FakeGetRequest2 = NewObject<UBeamMockGetRequest>();

				int64 ReqId;
				int64 ReqId2;
				const auto Request = BeamBackendSystem->CreateAuthenticatedRequest(ReqId, FakeRealmHandle, FakeNoRetryConfig, FakeAuthToken, FakeGetRequest);
				const auto Request2 = BeamBackendSystem->CreateAuthenticatedRequest(ReqId2, FakeRealmHandle, FakeNoRetryConfig, FakeAuthToken, FakeGetRequest2);

				// Create a fake operation
				FBeamOperationEventHandler Handler;
				Handler.BindUFunction(OperationCallbacks, GET_FUNCTION_NAME_CHECKED(UBeamRequestTrackerOperationTestCallbacks, MockOperationEvent_Fail));
				const auto OpHandle = RequestTrackerSystem->BeginOperation({FakeUserSlot}, GetTestName(), Handler);
				RequestTrackerSystem->AddRequestToOperation(OpHandle, ReqId2);

				// Create the first wait handle with Req1 and Operation (which contains req2 as a dep)
				const TArray<FBeamRequestContext> FirstContexts{FBeamRequestContext{ReqId}};
				const TArray<FBeamOperationHandle> FirstOperations{OpHandle};
				FOnWaitCompleteCode FirstOnComplete;
				FirstOnComplete.BindUFunction(WaitAllCallbacks, GET_FUNCTION_NAME_CHECKED(UBeamRequestTrackerWaitAllTestCallbacks, MockWaitCompleteEvent_Expected));
				const auto FirstWaitHandle = RequestTrackerSystem->CPP_WaitAll(FirstContexts, FirstOperations, {}, FirstOnComplete);

				// Now we assert that if we gather the dependencies for the first wait handle
				const TArray<int64> FirstExpectedRequestDeps{ReqId, ReqId2};
				TArray<int64> GatheredDeps;
				TArray<FBeamOperationHandle> GatheredOperationDeps;
				RequestTrackerSystem->GatherRequestIdsFromWaitHandle(FirstWaitHandle, GatheredDeps, GatheredOperationDeps);
				GatheredDeps.Sort();
				TestEqual("First wait handle's dependencies are correctly gathered", GatheredDeps, FirstExpectedRequestDeps);

				// We forcibly tag the requests as completed here so we can see if the wait callback will trigger
				{
					auto& Ctx = *BeamBackendSystem->InFlightRequestContexts.Find(ReqId);
					Ctx.BeamStatus = AS_Completed;
					auto& Ctx2 = *BeamBackendSystem->InFlightRequestContexts.Find(ReqId2);
					Ctx2.BeamStatus = AS_Completed;
				}

				// Now we run the tick OnRequestCompleted to see if it triggers the WaitComplete callback.
				WaitAllCallbacks->ExpectedContexts = {FBeamRequestContext{ReqId}, FBeamRequestContext{ReqId2}};
				WaitAllCallbacks->ExpectedRequests = {FakeGetRequest, FakeGetRequest2};
				WaitAllCallbacks->ExpectedErrors = {FBeamErrorResponse{}, FBeamErrorResponse{}}; // We expect blank because we don't actually make the requests.
				WaitAllCallbacks->ExpectedResponses = {nullptr, nullptr}; // We expect null because we don't actually make the requests.

				// Tick so that the callback assertions run.
				RequestTrackerSystem->CheckAndCompleteWaitHandles(-1);

				// Discard Requests as we are not actually going to make them
				BeamBackendSystem->CancelRequest(ReqId);
				FakeGetRequest->MarkAsGarbage();
				BeamBackendSystem->CancelRequest(ReqId2);
				FakeGetRequest2->MarkAsGarbage();
			}
		});
	});

	Describe("Operations", [this]()
	{
		const FUserSlot FakeUserSlot{"TestUserSlot"};
		const FBeamRealmHandle FakeRealmHandle{FString("TEST_CID"), FString("TEST_PID")};
		const FBeamRetryConfig FakeNoRetryConfig{{}, {}, 10, TArray<float>{0.5, 1}, 0};
		const FBeamAuthToken FakeAuthToken{"AUTH_TOKEN", "REFRESH_TOKEN"};

		BeforeEach([this]()
		{
			BeamBackendSystem = GEngine->GetEngineSubsystem<UBeamBackend>();
			RequestTrackerSystem = GEngine->GetEngineSubsystem<UBeamRequestTracker>();

			OperationCallbacks = NewObject<UBeamRequestTrackerOperationTestCallbacks>();
			OperationCallbacks->BeamBackend = BeamBackendSystem;
			OperationCallbacks->BeamRequestTracker = RequestTrackerSystem;
			OperationCallbacks->Spec = this;

			FHttpModule::Get().ToggleNullHttp(true);
		});

		AfterEach([this]()
		{
			// Clear callbacks object			
			OperationCallbacks = nullptr;
			WaitAllCallbacks = nullptr;
			
			// Make sure that the execute request delegate is properly set up. 
			BeamBackendSystem->ExecuteRequestDelegate.BindUFunction(BeamBackendSystem, "DefaultExecuteRequestImpl");
			FHttpModule::Get().ToggleNullHttp(false);

			// Reset the request tracker system
			RequestTrackerSystem->OperationHandleId = -1;
			RequestTrackerSystem->ActiveOperations.Reset();
			RequestTrackerSystem->ActiveOperationState.Reset();			
			
			RequestTrackerSystem->WaitHandleId = -1;
			RequestTrackerSystem->ActiveWaitHandles.Reset();
			RequestTrackerSystem->ActiveWaitStates.Reset();
			
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

		It("should begin an operation with the given parameters", [=, this]()
		{
			const FBeamOperationEventHandler Handler;
			const auto OpHandle = RequestTrackerSystem->BeginOperation({FakeUserSlot}, GetTestName(), Handler);

			// Ensure all headers were created correctly
			TestTrue("Operation was created successfully", RequestTrackerSystem->ActiveOperations.Contains(OpHandle));
			TestEqual("Operation status was correctly initialized", RequestTrackerSystem->ActiveOperationState.FindRef(OpHandle)->Status, UBeamOperationState::ONGOING);			
			TestEqual("Operation Calling System was correctly initialized", RequestTrackerSystem->ActiveOperationState.FindRef(OpHandle)->CallingSystem, GetTestName());
			TestTrue("Operation dependent user slots was correctly initialized", RequestTrackerSystem->ActiveOperationState.FindRef(OpHandle)->DependentUserSlots.Contains(FakeUserSlot));
			TestTrue("Operation callback was correctly initialized", RequestTrackerSystem->ActiveOperationState.FindRef(OpHandle)->BlueprintHandler == Handler);
		});

		It("should add an existing request to an operation with the given parameters", [=, this]()
		{
			UBeamMockGetRequest* FakeGetRequest = NewObject<UBeamMockGetRequest>();
			int64 ReqId;
			const auto Request = BeamBackendSystem->CreateAuthenticatedRequest(ReqId, FakeRealmHandle, FakeNoRetryConfig, FakeAuthToken, FakeGetRequest);

			// Ensures the operation was initialized correctly.
			const FBeamOperationEventHandler Handler;
			const auto OpHandle = RequestTrackerSystem->BeginOperation({FakeUserSlot}, GetTestName(), Handler);
			TestTrue("Operation was created successfully", RequestTrackerSystem->ActiveOperations.Contains(OpHandle));
			TestEqual("Operation status was correctly initialized", RequestTrackerSystem->ActiveOperationState.FindRef(OpHandle)->Status, UBeamOperationState::ONGOING);			
			TestEqual("Operation Calling System was correctly initialized", RequestTrackerSystem->ActiveOperationState.FindRef(OpHandle)->CallingSystem, GetTestName());
			TestTrue("Operation dependent user slots was correctly initialized", RequestTrackerSystem->ActiveOperationState.FindRef(OpHandle)->DependentUserSlots.Contains(FakeUserSlot));
			TestTrue("Operation callback was correctly initialized", RequestTrackerSystem->ActiveOperationState.FindRef(OpHandle)->BlueprintHandler == Handler);


			// Ensure we added the request correctly.
			RequestTrackerSystem->AddRequestToOperation(OpHandle, ReqId);
			TestTrue("Operation dependent requests was correctly updated", RequestTrackerSystem->ActiveOperationState.FindRef(OpHandle)->DependentRequests.Contains(ReqId));

			// Discard Request as we are not actually going to make it
			BeamBackendSystem->CancelRequest(ReqId);
			FakeGetRequest->MarkAsGarbage();
		});

		It("should trigger the shortcut events for FINAL success/error/cancelled", [=, this]()
		{
			// Initialize and trigger the operation's success
			{
				UBeamMockGetRequest* FakeGetRequest = NewObject<UBeamMockGetRequest>();
				int64 ReqId;
				const auto Request = BeamBackendSystem->CreateAuthenticatedRequest(ReqId, FakeRealmHandle, FakeNoRetryConfig, FakeAuthToken, FakeGetRequest);

				// Set up the handler and expected data
				FBeamOperationEventHandler Handler;
				Handler.BindUFunction(OperationCallbacks, GET_FUNCTION_NAME_CHECKED(UBeamRequestTrackerOperationTestCallbacks, MockOperationEvent_Expected));
				OperationCallbacks->ExpectedEventRequestId = ReqId;
				OperationCallbacks->ExpectedEventType = EBeamOperationEventType::OET_SUCCESS;
				OperationCallbacks->ExpectedEventId = NAME_None;
				OperationCallbacks->ExpectedEventSystem = TEXT("Success Test");
				OperationCallbacks->ExpectedEventCode = TEXT("SuccessData");
				OperationCallbacks->ExpectedParticipants = {FakeUserSlot};
				OperationCallbacks->ExpectedRequestsInOperations = {ReqId};

				const auto OpHandle = RequestTrackerSystem->BeginOperation({FakeUserSlot}, TEXT("Success Test"), Handler);
				RequestTrackerSystem->AddRequestToOperation(OpHandle, ReqId);
				RequestTrackerSystem->TriggerOperationSuccess(OpHandle, TEXT("SuccessData"));

				// Discard Request as we are not actually going to make it
				BeamBackendSystem->CancelRequest(ReqId);
				FakeGetRequest->MarkAsGarbage();
			}
		});

		It("should trigger the shortcut events for FINAL error", [=, this]()
		{
			// Initialize and trigger the operation's success
			{
				UBeamMockGetRequest* FakeGetRequest = NewObject<UBeamMockGetRequest>();
				int64 ErrorReqId;
				const auto Request = BeamBackendSystem->CreateAuthenticatedRequest(ErrorReqId, FakeRealmHandle, FakeNoRetryConfig, FakeAuthToken, FakeGetRequest);

				// Set up the handler and expected data
				FBeamOperationEventHandler Handler;
				Handler.BindUFunction(OperationCallbacks, GET_FUNCTION_NAME_CHECKED(UBeamRequestTrackerOperationTestCallbacks, MockOperationEvent_Expected));
				OperationCallbacks->ExpectedEventRequestId = ErrorReqId;
				OperationCallbacks->ExpectedEventType = EBeamOperationEventType::OET_ERROR;
				OperationCallbacks->ExpectedEventId = NAME_None;
				OperationCallbacks->ExpectedEventSystem = TEXT("Error Test");
				OperationCallbacks->ExpectedEventCode = TEXT("ErrorData");
				OperationCallbacks->ExpectedParticipants = {FakeUserSlot};
				OperationCallbacks->ExpectedRequestsInOperations = {ErrorReqId};

				const auto ErrorTestOpHandle = RequestTrackerSystem->BeginOperation({FakeUserSlot}, TEXT("Error Test"), Handler);
				RequestTrackerSystem->AddRequestToOperation(ErrorTestOpHandle, ErrorReqId);
				RequestTrackerSystem->TriggerOperationError(ErrorTestOpHandle, TEXT("ErrorData"));

				// Discard Request as we are not actually going to make it
				BeamBackendSystem->CancelRequest(ErrorReqId);
				FakeGetRequest->MarkAsGarbage();
			}
		});

		It("should trigger the shortcut events for FINAL cancelled", [=, this]()
		{
			// Initialize and trigger the operation's success
			{
				UBeamMockGetRequest* FakeGetRequest = NewObject<UBeamMockGetRequest>();
				int64 ReqId;
				const auto Request = BeamBackendSystem->CreateAuthenticatedRequest(ReqId, FakeRealmHandle, FakeNoRetryConfig, FakeAuthToken, FakeGetRequest);

				// Set up the handler and expected data
				FBeamOperationEventHandler Handler;
				Handler.BindUFunction(OperationCallbacks, GET_FUNCTION_NAME_CHECKED(UBeamRequestTrackerOperationTestCallbacks, MockOperationEvent_Expected));
				OperationCallbacks->ExpectedEventRequestId = ReqId;
				OperationCallbacks->ExpectedEventType = EBeamOperationEventType::OET_CANCELLED;
				OperationCallbacks->ExpectedEventId = NAME_None;
				OperationCallbacks->ExpectedEventSystem = TEXT("Cancelled Test");
				OperationCallbacks->ExpectedEventCode = TEXT("CancelledData");
				OperationCallbacks->ExpectedParticipants = {FakeUserSlot};
				OperationCallbacks->ExpectedRequestsInOperations = {ReqId};

				const auto OpHandle = RequestTrackerSystem->BeginOperation({FakeUserSlot}, TEXT("Cancelled Test"), Handler);
				RequestTrackerSystem->AddRequestToOperation(OpHandle, ReqId);
				RequestTrackerSystem->TriggerOperationCancelled(OpHandle, TEXT("CancelledData"));

				// Discard Request as we are not actually going to make it
				BeamBackendSystem->CancelRequest(ReqId);
				FakeGetRequest->MarkAsGarbage();
			}
		});

		It("should trigger custom event when requested", [=, this]()
		{
			// Initialize and trigger the operation's success
			{
				UBeamMockGetRequest* FakeGetRequest = NewObject<UBeamMockGetRequest>();
				int64 ReqId;
				const auto Request = BeamBackendSystem->CreateAuthenticatedRequest(ReqId, FakeRealmHandle, FakeNoRetryConfig, FakeAuthToken, FakeGetRequest);

				// Set up the handler and expected data
				FBeamOperationEventHandler Handler;
				Handler.BindUFunction(OperationCallbacks, GET_FUNCTION_NAME_CHECKED(UBeamRequestTrackerOperationTestCallbacks, MockOperationEvent_Expected));
				OperationCallbacks->ExpectedEventRequestId = ReqId;
				OperationCallbacks->ExpectedEventType = EBeamOperationEventType::OET_SUCCESS;
				OperationCallbacks->ExpectedEventId = FName("1");
				OperationCallbacks->ExpectedEventSystem = GetTestName();
				OperationCallbacks->ExpectedEventCode = TEXT("SuccessData");
				OperationCallbacks->ExpectedParticipants = {FakeUserSlot};
				OperationCallbacks->ExpectedRequestsInOperations = {ReqId};

				const auto OpHandle = RequestTrackerSystem->BeginOperation({FakeUserSlot}, GetTestName(), Handler);
				RequestTrackerSystem->AddRequestToOperation(OpHandle, ReqId);
				RequestTrackerSystem->TriggerOperationEvent(OpHandle, EBeamOperationEventType::OET_SUCCESS, FName("1"), TEXT("SuccessData"));

				// Discard Request as we are not actually going to make it
				BeamBackendSystem->CancelRequest(ReqId);
				FakeGetRequest->MarkAsGarbage();
			}

			// Initialize and trigger the operation's with no request made in it yet
			{
				// Set up the handler and expected data
				FBeamOperationEventHandler Handler;
				Handler.BindUFunction(OperationCallbacks, GET_FUNCTION_NAME_CHECKED(UBeamRequestTrackerOperationTestCallbacks, MockOperationEvent_Expected));
				OperationCallbacks->ExpectedEventRequestId = -1;
				OperationCallbacks->ExpectedEventType = EBeamOperationEventType::OET_SUCCESS;
				OperationCallbacks->ExpectedEventId = FName("1");
				OperationCallbacks->ExpectedEventSystem = GetTestName();
				OperationCallbacks->ExpectedEventCode = TEXT("SuccessData");
				OperationCallbacks->ExpectedParticipants = {FakeUserSlot};
				OperationCallbacks->ExpectedRequestsInOperations = {};

				const auto OpHandle = RequestTrackerSystem->BeginOperation({FakeUserSlot}, GetTestName(), Handler);
				RequestTrackerSystem->TriggerOperationEvent(OpHandle, EBeamOperationEventType::OET_SUCCESS, FName("1"), TEXT("SuccessData"));
			}
		});
	});

	Describe("Clean Up", [this]()
	{
		const FUserSlot FakeUserSlot{"TestUserSlot"};
		const FBeamRealmHandle FakeRealmHandle{FString("TEST_CID"), FString("TEST_PID")};
		const FBeamRetryConfig FakeNoRetryConfig{{}, {}, 10, TArray<float>{0.5, 1}, 0};
		const FBeamAuthToken FakeAuthToken{"AUTH_TOKEN", "REFRESH_TOKEN"};

		BeforeEach([this]()
		{
			BeamBackendSystem = GEngine->GetEngineSubsystem<UBeamBackend>();
			RequestTrackerSystem = GEngine->GetEngineSubsystem<UBeamRequestTracker>();

			OperationCallbacks = NewObject<UBeamRequestTrackerOperationTestCallbacks>();
			OperationCallbacks->BeamBackend = BeamBackendSystem;
			OperationCallbacks->BeamRequestTracker = RequestTrackerSystem;
			OperationCallbacks->Spec = this;

			FHttpModule::Get().ToggleNullHttp(true);
		});

		AfterEach([this]()
		{
			// Clear callbacks object			
			OperationCallbacks = nullptr;
			WaitAllCallbacks = nullptr;
			
			// Make sure that the execute request delegate is properly set up. 
			BeamBackendSystem->ExecuteRequestDelegate.BindUFunction(BeamBackendSystem, "DefaultExecuteRequestImpl");
			FHttpModule::Get().ToggleNullHttp(false);

			// Reset the request tracker system
			RequestTrackerSystem->OperationHandleId = -1;
			RequestTrackerSystem->ActiveOperations.Reset();
			RequestTrackerSystem->ActiveOperationState.Reset();			
			
			RequestTrackerSystem->WaitHandleId = -1;
			RequestTrackerSystem->ActiveWaitHandles.Reset();
			RequestTrackerSystem->ActiveWaitStates.Reset();			

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

		It("should remove all state associated with any completed operation and return all live ReqIds associated with any operation", [=, this]()
		{
			// Try to configure a wait handle with non-existent 
			UBeamMockGetRequest* FakeGetRequest = NewObject<UBeamMockGetRequest>();
			UBeamMockGetRequest* FakeGetRequest2 = NewObject<UBeamMockGetRequest>();

			int64 ReqId;
			int64 ReqId2;
			const auto Request = BeamBackendSystem->CreateAuthenticatedRequest(ReqId, FakeRealmHandle, FakeNoRetryConfig, FakeAuthToken, FakeGetRequest);
			const auto Request2 = BeamBackendSystem->CreateAuthenticatedRequest(ReqId2, FakeRealmHandle, FakeNoRetryConfig, FakeAuthToken, FakeGetRequest2);

			// Create a fake operation
			FBeamOperationEventHandler Handler;
			Handler.BindUFunction(OperationCallbacks, GET_FUNCTION_NAME_CHECKED(UBeamRequestTrackerOperationTestCallbacks, MockOperationEvent_Fail));
			const auto OpHandle = RequestTrackerSystem->BeginOperation({FakeUserSlot}, GetTestName(), Handler);
			RequestTrackerSystem->AddRequestToOperation(OpHandle, ReqId);

			// Create a fake operation
			FBeamOperationEventHandler Handler1;
			Handler1.BindUFunction(OperationCallbacks, GET_FUNCTION_NAME_CHECKED(UBeamRequestTrackerOperationTestCallbacks, MockOperationEvent_Fail));
			const auto OpHandle1 = RequestTrackerSystem->BeginOperation({FakeUserSlot}, GetTestName(), Handler1);
			RequestTrackerSystem->AddRequestToOperation(OpHandle1, ReqId2);

			// Now we assert that if we gather the dependencies for the first wait handle
			const TArray<int64> ExpectedLiveDependencies{ReqId2};

			// Forcibly make the first OpHandle be completed/cancelled
			RequestTrackerSystem->ActiveOperationState.FindChecked(OpHandle)->Status = UBeamOperationState::CANCELLED;

			// Clean up and get the requests that this system depends on
			TArray<int64> DependsOnRequests;
			RequestTrackerSystem->HandleBackendCleanUp(DependsOnRequests);
			RequestTrackerSystem->CleanUpOperations();						

			// Test that we cleaned up the operation that was cancelled
			TestFalse("First operation is no longer active", RequestTrackerSystem->ActiveOperations.Contains(OpHandle));
			TestTrue("First operation state was cleared", !RequestTrackerSystem->ActiveOperationState.Contains(OpHandle));			

			TestEqual("We correctly generated a list of all Request Ids that are currently in the operations", DependsOnRequests, ExpectedLiveDependencies);

			// Discard Requests as we are not actually going to make them
			BeamBackendSystem->CancelRequest(ReqId);
			FakeGetRequest->MarkAsGarbage();
			BeamBackendSystem->CancelRequest(ReqId2);
			FakeGetRequest2->MarkAsGarbage();
		});

		It("should remove all state associated with any completed wait handle and return all live ReqIds associated with any ongoing wait handle", [=, this]()
		{
			// Try to configure a wait handle with non-existent 
			UBeamMockGetRequest* FakeGetRequest = NewObject<UBeamMockGetRequest>();
			UBeamMockGetRequest* FakeGetRequest2 = NewObject<UBeamMockGetRequest>();

			int64 ReqId;
			int64 ReqId2;
			const auto Request = BeamBackendSystem->CreateAuthenticatedRequest(ReqId, FakeRealmHandle, FakeNoRetryConfig, FakeAuthToken, FakeGetRequest);
			const auto Request2 = BeamBackendSystem->CreateAuthenticatedRequest(ReqId2, FakeRealmHandle, FakeNoRetryConfig, FakeAuthToken, FakeGetRequest2);

			// Create the first wait handle with Req1 and Operation (which contains req2 as a dep)
			FOnWaitComplete FirstOnComplete;
			FOnWaitCompleteCode FirstOnCompleteCode;
			FirstOnCompleteCode.BindLambda([this](const FBeamWaitCompleteEvent&)
			{
				TestTrue("Callback should not be invoked!", false);
			});
			FirstOnComplete.BindUFunction(WaitAllCallbacks, GET_FUNCTION_NAME_CHECKED(UBeamRequestTrackerWaitAllTestCallbacks, MockWaitCompleteEvent_Fail));
			const auto FirstWaitHandle = RequestTrackerSystem->WaitAll({FBeamRequestContext{ReqId}},
			                                                           {},
			                                                           {},
			                                                           FirstOnComplete);
			const auto FirstWaitHandleCpp = RequestTrackerSystem->CPP_WaitAll({FBeamRequestContext{ReqId}},
			                                                                  {},
			                                                                  {},
			                                                                  FirstOnCompleteCode);

			// Create the first wait handle with Req1 and Operation (which contains req2 as a dep)
			FOnWaitComplete SecondOnComplete;
			FOnWaitCompleteCode SecondOnCompleteCode;
			SecondOnCompleteCode.BindLambda([this](const FBeamWaitCompleteEvent&)
			{
				TestTrue("Callback should not be invoked!", false);
			});
			SecondOnComplete.BindUFunction(WaitAllCallbacks, GET_FUNCTION_NAME_CHECKED(UBeamRequestTrackerWaitAllTestCallbacks, MockWaitCompleteEvent_Fail));
			const auto SecondWaitHandle = RequestTrackerSystem->WaitAll({FBeamRequestContext{ReqId2}},
			                                                            {},
			                                                            {},
			                                                            SecondOnComplete);
			const auto SecondWaitHandleCpp = RequestTrackerSystem->CPP_WaitAll({FBeamRequestContext{ReqId2}},
			                                                                   {},
			                                                                   {},
			                                                                   SecondOnCompleteCode);

			// Forcibly complete the first wait handle only
			RequestTrackerSystem->ActiveWaitStates.FindChecked(FirstWaitHandle)->Status = AS_Completed;
			RequestTrackerSystem->ActiveWaitStates.FindChecked(FirstWaitHandleCpp)->Status = AS_Completed;


			// Now we assert that if we gather the dependencies for the first wait handle
			const TArray<int64> ExpectedLiveDependencies{ReqId2};

			// Clean up and get the requests that this system depends on
			TArray<int64> DependsOnRequests;
			RequestTrackerSystem->HandleBackendCleanUp(DependsOnRequests);
			RequestTrackerSystem->CleanUpWaitHandles();
			RequestTrackerSystem->CleanUpOperations();			

			// Test that we cleaned up the operation that was cancelled
			TestFalse("First wait handle is no longer active", RequestTrackerSystem->ActiveWaitHandles.Contains(FirstWaitHandle));
			TestTrue("First wait handle's state was cleared'", !RequestTrackerSystem->ActiveWaitStates.Contains(FirstWaitHandle));

			TestEqual("We correctly generated a list of all Request Ids that are currently in the wait handles", DependsOnRequests, ExpectedLiveDependencies);

			// Discard Requests as we are not actually going to make them
			BeamBackendSystem->CancelRequest(ReqId);
			FakeGetRequest->MarkAsGarbage();
			BeamBackendSystem->CancelRequest(ReqId2);
			FakeGetRequest2->MarkAsGarbage();
		});
	});
};
