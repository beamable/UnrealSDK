

#include "BeamableCoreBlueprintNodes/Public/BeamFlow/ApiRequest/AutoGen/Content/K2BeamNode_ApiRequest_GetManifestPrivateJson.h"

#include "BeamK2.h"

#include "BeamableCore/Public/AutoGen/SubSystems/BeamContentApi.h"
#include "BeamableCore/Public/AutoGen/SubSystems/Content/GetManifestPrivateJsonRequest.h"
#include "BeamableCore/Public/AutoGen/ClientManifestJsonResponse.h"

#define LOCTEXT_NAMESPACE "K2BeamNode_ApiRequest_GetManifestPrivateJson"

using namespace BeamK2;

FName UK2BeamNode_ApiRequest_GetManifestPrivateJson::GetSelfFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamContentApi, GetSelf);
}

FName UK2BeamNode_ApiRequest_GetManifestPrivateJson::GetRequestFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamContentApi, GetManifestPrivateJson);
}

FName UK2BeamNode_ApiRequest_GetManifestPrivateJson::GetMakeFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UGetManifestPrivateJsonRequest, Make);
}

FString UK2BeamNode_ApiRequest_GetManifestPrivateJson::GetServiceName() const
{
	return TEXT("Content");
}

FString UK2BeamNode_ApiRequest_GetManifestPrivateJson::GetEndpointName() const
{
	return TEXT("GetManifestPrivateJson");
}

UClass* UK2BeamNode_ApiRequest_GetManifestPrivateJson::GetApiClass() const
{
	return UBeamContentApi::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_GetManifestPrivateJson::GetRequestClass() const
{
	return UGetManifestPrivateJsonRequest::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_GetManifestPrivateJson::GetResponseClass() const
{
	return UClientManifestJsonResponse::StaticClass();
}

FString UK2BeamNode_ApiRequest_GetManifestPrivateJson::GetRequestSuccessDelegateName() const
{
	return TEXT("OnGetManifestPrivateJsonSuccess");
}

FString UK2BeamNode_ApiRequest_GetManifestPrivateJson::GetRequestErrorDelegateName() const
{
	return TEXT("OnGetManifestPrivateJsonError");
}

FString UK2BeamNode_ApiRequest_GetManifestPrivateJson::GetRequestCompleteDelegateName() const
{
	return TEXT("OnGetManifestPrivateJsonComplete");
}

#undef LOCTEXT_NAMESPACE
