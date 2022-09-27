// Fill out your copyright notice in the Description page of Project Settings.


#include "BeamBackendTestCallbacks.h"
#include "BeamBackend.spec.h"

void UBeamBackendTestCallbacks::MockSuccessCallback_Expected(int64 RequestId, FBeamMockGetRequest Request, FBeamMockGetRequestResponse Response) const
{
	Spec->TestTrue("Success was called", true);

	Spec->TestTrue("Request Id was correctly forwarded", RequestId == ExpectedReqId);
	Spec->TestTrue("Failure Count was correctly forwarded", BeamBackend->InFlightFailureCount[RequestId] == 0);
	Spec->TestTrue("Response Code was correctly forwarded", Response.ResponseCode == 200);
	Spec->TestTrue("Response Body was correctly forwarded", Response.Body.FakeInt == ExpectedSuccessResponse);
}

void UBeamBackendTestCallbacks::MockSuccessCallback_Fail(int64 RequestId, FBeamMockGetRequest Request, FBeamMockGetRequestResponse Response) const
{
	Spec->TestTrue("Success Was Not Called!!!", false);
}

void UBeamBackendTestCallbacks::MockErrorCallback_Expected(int64 RequestId, FBeamMockGetRequest Request, FBeamErrorResponse Response) const
{
	Spec->TestTrue("Error was called", true);

	Spec->TestTrue("Request Id was correctly forwarded", RequestId == ExpectedReqId);

	Spec->TestTrue("Failure Count was correctly forwarded", BeamBackend->InFlightFailureCount[RequestId] == ExpectedErrorFailureCount);
	
	Spec->TestTrue("Response Code was correctly forwarded", Response.status == ExpectedErrorResponseStatus);
	Spec->TestTrue("Response Body was correctly forwarded", Response.error == ExpectedErrorResponseError);
	Spec->TestTrue("Response Body was correctly forwarded", Response.service == ExpectedErrorResponseService);
	Spec->TestTrue("Response Body was correctly forwarded", Response.message == ExpectedErrorResponseMessage);
}

void UBeamBackendTestCallbacks::MockErrorCallback_Fail(int64 RequestId, FBeamMockGetRequest Request, FBeamErrorResponse Response) const
{
	Spec->TestTrue("Error Was Not Called!!!", false);	
}

void UBeamBackendTestCallbacks::MockCompleteCallback_Expected(int64 RequestId, FBeamMockGetRequest Request) const
{
	Spec->TestTrue("Complete Was Called!!!", true);
	Spec->TestTrue("Request Id was correctly forwarded", RequestId == ExpectedReqId);	
}

void UBeamBackendTestCallbacks::MockCompleteCallbackCancelled_Expected(int64 RequestId, FBeamMockGetRequest Request) const
{
	Spec->TestTrue("Beam back-end correctly stores the state as cancelled", BeamBackend->IsRequestCancelled(RequestId));	
	DoneDelegateForLatentTests.Execute();
}
