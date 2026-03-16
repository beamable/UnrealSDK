

#include "BeamableCoreBlueprintNodes/Public/BeamFlow/ApiRequest/AutoGen/Auth/K2BeamNode_ApiRequest_GetKeys.h"

#include "BeamK2.h"

#include "BeamableCore/Public/AutoGen/SubSystems/BeamAuthApi.h"
#include "BeamableCore/Public/AutoGen/SubSystems/Auth/GetKeysRequest.h"
#include "BeamableCore/Public/AutoGen/AuthV2JsonWebKeySet.h"

#define LOCTEXT_NAMESPACE "K2BeamNode_ApiRequest_GetKeys"

using namespace BeamK2;

FName UK2BeamNode_ApiRequest_GetKeys::GetSelfFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamAuthApi, GetSelf);
}

FName UK2BeamNode_ApiRequest_GetKeys::GetRequestFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamAuthApi, GetKeys);
}

FName UK2BeamNode_ApiRequest_GetKeys::GetMakeFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UGetKeysRequest, Make);
}

FString UK2BeamNode_ApiRequest_GetKeys::GetServiceName() const
{
	return TEXT("Auth");
}

FString UK2BeamNode_ApiRequest_GetKeys::GetEndpointName() const
{
	return TEXT("GetKeys");
}

UClass* UK2BeamNode_ApiRequest_GetKeys::GetApiClass() const
{
	return UBeamAuthApi::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_GetKeys::GetRequestClass() const
{
	return UGetKeysRequest::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_GetKeys::GetResponseClass() const
{
	return UAuthV2JsonWebKeySet::StaticClass();
}

FString UK2BeamNode_ApiRequest_GetKeys::GetRequestSuccessDelegateName() const
{
	return TEXT("OnGetKeysSuccess");
}

FString UK2BeamNode_ApiRequest_GetKeys::GetRequestErrorDelegateName() const
{
	return TEXT("OnGetKeysError");
}

FString UK2BeamNode_ApiRequest_GetKeys::GetRequestCompleteDelegateName() const
{
	return TEXT("OnGetKeysComplete");
}

#undef LOCTEXT_NAMESPACE
