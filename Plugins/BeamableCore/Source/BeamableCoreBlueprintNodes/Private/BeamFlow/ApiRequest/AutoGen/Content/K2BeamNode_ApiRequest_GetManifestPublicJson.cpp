

#include "BeamableCoreBlueprintNodes/Public/BeamFlow/ApiRequest/AutoGen/Content/K2BeamNode_ApiRequest_GetManifestPublicJson.h"

#include "BeamK2.h"

#include "BeamableCore/Public/AutoGen/SubSystems/BeamContentApi.h"
#include "BeamableCore/Public/AutoGen/SubSystems/Content/GetManifestPublicJsonRequest.h"
#include "BeamableCore/Public/AutoGen/ClientManifestJsonResponse.h"

#define LOCTEXT_NAMESPACE "K2BeamNode_ApiRequest_GetManifestPublicJson"

using namespace BeamK2;

FName UK2BeamNode_ApiRequest_GetManifestPublicJson::GetSelfFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamContentApi, GetSelf);
}

FName UK2BeamNode_ApiRequest_GetManifestPublicJson::GetRequestFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamContentApi, GetManifestPublicJson);
}

FName UK2BeamNode_ApiRequest_GetManifestPublicJson::GetMakeFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UGetManifestPublicJsonRequest, Make);
}

FString UK2BeamNode_ApiRequest_GetManifestPublicJson::GetServiceName() const
{
	return TEXT("Content");
}

FString UK2BeamNode_ApiRequest_GetManifestPublicJson::GetEndpointName() const
{
	return TEXT("GetManifestPublicJson");
}

UClass* UK2BeamNode_ApiRequest_GetManifestPublicJson::GetApiClass() const
{
	return UBeamContentApi::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_GetManifestPublicJson::GetRequestClass() const
{
	return UGetManifestPublicJsonRequest::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_GetManifestPublicJson::GetResponseClass() const
{
	return UClientManifestJsonResponse::StaticClass();
}

FString UK2BeamNode_ApiRequest_GetManifestPublicJson::GetRequestSuccessDelegateName() const
{
	return TEXT("OnGetManifestPublicJsonSuccess");
}

FString UK2BeamNode_ApiRequest_GetManifestPublicJson::GetRequestErrorDelegateName() const
{
	return TEXT("OnGetManifestPublicJsonError");
}

FString UK2BeamNode_ApiRequest_GetManifestPublicJson::GetRequestCompleteDelegateName() const
{
	return TEXT("OnGetManifestPublicJsonComplete");
}

#undef LOCTEXT_NAMESPACE
