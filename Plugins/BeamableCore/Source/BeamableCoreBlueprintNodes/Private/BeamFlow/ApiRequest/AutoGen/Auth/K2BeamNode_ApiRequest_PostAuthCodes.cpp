

#include "BeamableCoreBlueprintNodes/Public/BeamFlow/ApiRequest/AutoGen/Auth/K2BeamNode_ApiRequest_PostAuthCodes.h"

#include "BeamK2.h"

#include "BeamableCore/Public/AutoGen/SubSystems/BeamAuthApi.h"
#include "BeamableCore/Public/AutoGen/SubSystems/Auth/PostAuthCodesRequest.h"
#include "BeamableCore/Public/AutoGen/AuthV2AuthCode.h"

#define LOCTEXT_NAMESPACE "K2BeamNode_ApiRequest_PostAuthCodes"

using namespace BeamK2;

FName UK2BeamNode_ApiRequest_PostAuthCodes::GetSelfFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamAuthApi, GetSelf);
}

FName UK2BeamNode_ApiRequest_PostAuthCodes::GetRequestFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamAuthApi, PostAuthCodes);
}

FName UK2BeamNode_ApiRequest_PostAuthCodes::GetMakeFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UPostAuthCodesRequest, Make);
}

FString UK2BeamNode_ApiRequest_PostAuthCodes::GetServiceName() const
{
	return TEXT("Auth");
}

FString UK2BeamNode_ApiRequest_PostAuthCodes::GetEndpointName() const
{
	return TEXT("PostAuthCodes");
}

UClass* UK2BeamNode_ApiRequest_PostAuthCodes::GetApiClass() const
{
	return UBeamAuthApi::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_PostAuthCodes::GetRequestClass() const
{
	return UPostAuthCodesRequest::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_PostAuthCodes::GetResponseClass() const
{
	return UAuthV2AuthCode::StaticClass();
}

FString UK2BeamNode_ApiRequest_PostAuthCodes::GetRequestSuccessDelegateName() const
{
	return TEXT("OnPostAuthCodesSuccess");
}

FString UK2BeamNode_ApiRequest_PostAuthCodes::GetRequestErrorDelegateName() const
{
	return TEXT("OnPostAuthCodesError");
}

FString UK2BeamNode_ApiRequest_PostAuthCodes::GetRequestCompleteDelegateName() const
{
	return TEXT("OnPostAuthCodesComplete");
}

#undef LOCTEXT_NAMESPACE
