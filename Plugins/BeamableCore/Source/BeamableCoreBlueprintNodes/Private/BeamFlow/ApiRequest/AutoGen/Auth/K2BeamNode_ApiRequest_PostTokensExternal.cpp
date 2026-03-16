

#include "BeamableCoreBlueprintNodes/Public/BeamFlow/ApiRequest/AutoGen/Auth/K2BeamNode_ApiRequest_PostTokensExternal.h"

#include "BeamK2.h"

#include "BeamableCore/Public/AutoGen/SubSystems/BeamAuthApi.h"
#include "BeamableCore/Public/AutoGen/SubSystems/Auth/PostTokensExternalRequest.h"
#include "BeamableCore/Public/AutoGen/AuthV2ExternalAuthResponse.h"

#define LOCTEXT_NAMESPACE "K2BeamNode_ApiRequest_PostTokensExternal"

using namespace BeamK2;

FName UK2BeamNode_ApiRequest_PostTokensExternal::GetSelfFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamAuthApi, GetSelf);
}

FName UK2BeamNode_ApiRequest_PostTokensExternal::GetRequestFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamAuthApi, PostTokensExternal);
}

FName UK2BeamNode_ApiRequest_PostTokensExternal::GetMakeFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UPostTokensExternalRequest, Make);
}

FString UK2BeamNode_ApiRequest_PostTokensExternal::GetServiceName() const
{
	return TEXT("Auth");
}

FString UK2BeamNode_ApiRequest_PostTokensExternal::GetEndpointName() const
{
	return TEXT("PostTokensExternal");
}

UClass* UK2BeamNode_ApiRequest_PostTokensExternal::GetApiClass() const
{
	return UBeamAuthApi::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_PostTokensExternal::GetRequestClass() const
{
	return UPostTokensExternalRequest::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_PostTokensExternal::GetResponseClass() const
{
	return UAuthV2ExternalAuthResponse::StaticClass();
}

FString UK2BeamNode_ApiRequest_PostTokensExternal::GetRequestSuccessDelegateName() const
{
	return TEXT("OnPostTokensExternalSuccess");
}

FString UK2BeamNode_ApiRequest_PostTokensExternal::GetRequestErrorDelegateName() const
{
	return TEXT("OnPostTokensExternalError");
}

FString UK2BeamNode_ApiRequest_PostTokensExternal::GetRequestCompleteDelegateName() const
{
	return TEXT("OnPostTokensExternalComplete");
}

#undef LOCTEXT_NAMESPACE
