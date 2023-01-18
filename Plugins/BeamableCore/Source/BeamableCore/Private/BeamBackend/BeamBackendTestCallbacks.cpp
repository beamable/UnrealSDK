// Fill out your copyright notice in the Description page of Project Settings.


#include "BeamBackendTestCallbacks.h"
#include "BeamBackend.spec.h"

const FString FBeamMockGetRequestCSVResponseRow::KeyField = GET_MEMBER_NAME_STRING_CHECKED(FBeamMockGetRequestCSVResponseRow, Field4);
const TArray<FString> FBeamMockGetRequestCSVResponseRow::HeaderFields = {
	KeyField,
	GET_MEMBER_NAME_STRING_CHECKED(FBeamMockGetRequestCSVResponseRow, Field1),
	GET_MEMBER_NAME_STRING_CHECKED(FBeamMockGetRequestCSVResponseRow, Field2),
	GET_MEMBER_NAME_STRING_CHECKED(FBeamMockGetRequestCSVResponseRow, Field3),
	GET_MEMBER_NAME_STRING_CHECKED(FBeamMockGetRequestCSVResponseRow, Field5),
};

void UBeamBackendTestCallbacks::MockSuccessCallback_Expected(FBeamRequestContext Context, UBeamMockGetRequest* Request, UBeamMockGetRequestResponse* Response) const
{
	Spec->TestTrue("Success was called", true);

	Spec->TestTrue("Request Id was correctly forwarded", Context.RequestId == ExpectedReqId);
	Spec->TestTrue("Failure Count was correctly forwarded", BeamBackend->InFlightFailureCount[Context.RequestId] == 0);
	Spec->TestTrue("Response Code was correctly forwarded", Context.ResponseCode == 200);
	Spec->TestTrue("Response Body was correctly forwarded", Response->FakeInt == ExpectedSuccessResponse);
}

void UBeamBackendTestCallbacks::MockSuccessCallback_Fail(FBeamRequestContext Context, UBeamMockGetRequest* Request, UBeamMockGetRequestResponse* Response) const
{
	Spec->TestTrue("Success Was Not Called!!!", false);
}

void UBeamBackendTestCallbacks::MockErrorCallback_Expected(FBeamRequestContext Context, UBeamMockGetRequest* Request, FBeamErrorResponse Response) const
{
	Spec->TestTrue("Error was called", true);

	Spec->TestTrue("Request Id was correctly forwarded", Context.RequestId == ExpectedReqId);

	Spec->TestTrue("Failure Count was correctly forwarded", BeamBackend->InFlightFailureCount[Context.RequestId] == ExpectedErrorFailureCount);

	Spec->TestTrue("Response Code was correctly forwarded", Response.status == ExpectedErrorResponseStatus);
	Spec->TestTrue("Response Body was correctly forwarded", Response.error == ExpectedErrorResponseError);
	Spec->TestTrue("Response Body was correctly forwarded", Response.service == ExpectedErrorResponseService);
	Spec->TestTrue("Response Body was correctly forwarded", Response.message == ExpectedErrorResponseMessage);
}

void UBeamBackendTestCallbacks::MockErrorCallback_Fail(FBeamRequestContext Context, UBeamMockGetRequest* Request, FBeamErrorResponse Response) const
{
	Spec->TestTrue("Error Was Not Called!!!", false);
}

void UBeamBackendTestCallbacks::MockCompleteCallback_Expected(FBeamRequestContext Context, UBeamMockGetRequest* Request) const
{
	Spec->TestTrue("Complete Was Called!!!", true);
	Spec->TestTrue("Request Id was correctly forwarded", Context.RequestId == ExpectedReqId);
}

void UBeamBackendTestCallbacks::MockCompleteCallbackCancelled_Expected(FBeamRequestContext Context, UBeamMockGetRequest* Request) const
{
	Spec->TestTrue("Beam back-end correctly stores the state as cancelled", BeamBackend->IsRequestCancelled(Context.RequestId));
	DoneDelegateForLatentTests.Execute();
}

void UBeamBackendTestCallbacks::GenerateExternalRequestIds(TArray<int64>& OutUsingRequestIds) const
{
	OutUsingRequestIds.Append(ExternalRequestIds);
}
