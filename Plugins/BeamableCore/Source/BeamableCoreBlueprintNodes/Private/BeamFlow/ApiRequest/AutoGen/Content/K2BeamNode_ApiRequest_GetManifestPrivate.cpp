

#include "BeamableCoreBlueprintNodes/Public/BeamFlow/ApiRequest/AutoGen/Content/K2BeamNode_ApiRequest_GetManifestPrivate.h"

#include "BeamK2.h"

#include "BeamableCore/Public/AutoGen/SubSystems/BeamContentApi.h"
#include "BeamableCore/Public/AutoGen/SubSystems/Content/GetManifestPrivateRequest.h"
#include "BeamableCore/Public/AutoGen/ClientManifestResponse.h"

#define LOCTEXT_NAMESPACE "K2BeamNode_ApiRequest_GetManifestPrivate"

using namespace BeamK2;

FName UK2BeamNode_ApiRequest_GetManifestPrivate::GetSelfFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamContentApi, GetSelf);
}

FName UK2BeamNode_ApiRequest_GetManifestPrivate::GetRequestFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamContentApi, GetManifestPrivate);
}

FName UK2BeamNode_ApiRequest_GetManifestPrivate::GetMakeFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UGetManifestPrivateRequest, Make);
}

FString UK2BeamNode_ApiRequest_GetManifestPrivate::GetServiceName() const
{
	return TEXT("Content");
}

FString UK2BeamNode_ApiRequest_GetManifestPrivate::GetEndpointName() const
{
	return TEXT("GetManifestPrivate");
}

UClass* UK2BeamNode_ApiRequest_GetManifestPrivate::GetApiClass() const
{
	return UBeamContentApi::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_GetManifestPrivate::GetRequestClass() const
{
	return UGetManifestPrivateRequest::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_GetManifestPrivate::GetResponseClass() const
{
	return UClientManifestResponse::StaticClass();
}

FString UK2BeamNode_ApiRequest_GetManifestPrivate::GetRequestSuccessDelegateName() const
{
	return TEXT("OnGetManifestPrivateSuccess");
}

FString UK2BeamNode_ApiRequest_GetManifestPrivate::GetRequestErrorDelegateName() const
{
	return TEXT("OnGetManifestPrivateError");
}

FString UK2BeamNode_ApiRequest_GetManifestPrivate::GetRequestCompleteDelegateName() const
{
	return TEXT("OnGetManifestPrivateComplete");
}

#undef LOCTEXT_NAMESPACE
