

#include "BeamableCoreBlueprintNodes/Public/BeamFlow/ApiRequest/AutoGen/Auth/K2BeamNode_ApiRequest_PutTokenRevoke.h"

#include "BeamK2.h"

#include "BeamableCore/Public/AutoGen/SubSystems/BeamAuthApi.h"
#include "BeamableCore/Public/AutoGen/SubSystems/Auth/PutTokenRevokeRequest.h"
#include "BeamableCore/Public/AutoGen/CommonResponse.h"

#define LOCTEXT_NAMESPACE "K2BeamNode_ApiRequest_PutTokenRevoke"

using namespace BeamK2;

FName UK2BeamNode_ApiRequest_PutTokenRevoke::GetSelfFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamAuthApi, GetSelf);
}

FName UK2BeamNode_ApiRequest_PutTokenRevoke::GetRequestFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamAuthApi, PutTokenRevoke);
}

FName UK2BeamNode_ApiRequest_PutTokenRevoke::GetMakeFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UPutTokenRevokeRequest, Make);
}

FString UK2BeamNode_ApiRequest_PutTokenRevoke::GetServiceName() const
{
	return TEXT("Auth");
}

FString UK2BeamNode_ApiRequest_PutTokenRevoke::GetEndpointName() const
{
	return TEXT("PutTokenRevoke");
}

UClass* UK2BeamNode_ApiRequest_PutTokenRevoke::GetApiClass() const
{
	return UBeamAuthApi::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_PutTokenRevoke::GetRequestClass() const
{
	return UPutTokenRevokeRequest::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_PutTokenRevoke::GetResponseClass() const
{
	return UCommonResponse::StaticClass();
}

FString UK2BeamNode_ApiRequest_PutTokenRevoke::GetRequestSuccessDelegateName() const
{
	return TEXT("OnPutTokenRevokeSuccess");
}

FString UK2BeamNode_ApiRequest_PutTokenRevoke::GetRequestErrorDelegateName() const
{
	return TEXT("OnPutTokenRevokeError");
}

FString UK2BeamNode_ApiRequest_PutTokenRevoke::GetRequestCompleteDelegateName() const
{
	return TEXT("OnPutTokenRevokeComplete");
}

#undef LOCTEXT_NAMESPACE
