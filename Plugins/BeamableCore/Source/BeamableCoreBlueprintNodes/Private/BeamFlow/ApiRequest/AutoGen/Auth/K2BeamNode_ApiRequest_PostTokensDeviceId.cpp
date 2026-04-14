

#include "BeamableCoreBlueprintNodes/Public/BeamFlow/ApiRequest/AutoGen/Auth/K2BeamNode_ApiRequest_PostTokensDeviceId.h"

#include "BeamK2.h"

#include "BeamableCore/Public/AutoGen/SubSystems/BeamAuthApi.h"
#include "BeamableCore/Public/AutoGen/SubSystems/Auth/PostTokensDeviceIdRequest.h"
#include "BeamableCore/Public/AutoGen/AuthV2AuthResponse.h"

#define LOCTEXT_NAMESPACE "K2BeamNode_ApiRequest_PostTokensDeviceId"

using namespace BeamK2;

FName UK2BeamNode_ApiRequest_PostTokensDeviceId::GetSelfFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamAuthApi, GetSelf);
}

FName UK2BeamNode_ApiRequest_PostTokensDeviceId::GetRequestFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamAuthApi, PostTokensDeviceId);
}

FName UK2BeamNode_ApiRequest_PostTokensDeviceId::GetMakeFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UPostTokensDeviceIdRequest, Make);
}

FString UK2BeamNode_ApiRequest_PostTokensDeviceId::GetServiceName() const
{
	return TEXT("Auth");
}

FString UK2BeamNode_ApiRequest_PostTokensDeviceId::GetEndpointName() const
{
	return TEXT("PostTokensDeviceId");
}

UClass* UK2BeamNode_ApiRequest_PostTokensDeviceId::GetApiClass() const
{
	return UBeamAuthApi::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_PostTokensDeviceId::GetRequestClass() const
{
	return UPostTokensDeviceIdRequest::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_PostTokensDeviceId::GetResponseClass() const
{
	return UAuthV2AuthResponse::StaticClass();
}

FString UK2BeamNode_ApiRequest_PostTokensDeviceId::GetRequestSuccessDelegateName() const
{
	return TEXT("OnPostTokensDeviceIdSuccess");
}

FString UK2BeamNode_ApiRequest_PostTokensDeviceId::GetRequestErrorDelegateName() const
{
	return TEXT("OnPostTokensDeviceIdError");
}

FString UK2BeamNode_ApiRequest_PostTokensDeviceId::GetRequestCompleteDelegateName() const
{
	return TEXT("OnPostTokensDeviceIdComplete");
}

#undef LOCTEXT_NAMESPACE
