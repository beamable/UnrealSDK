

#include "BeamableCoreBlueprintNodes/Public/BeamFlow/ApiRequest/AutoGen/Content/K2BeamNode_ApiRequest_GetManifestPublic.h"

#include "BeamK2.h"

#include "BeamableCore/Public/AutoGen/SubSystems/BeamContentApi.h"
#include "BeamableCore/Public/AutoGen/SubSystems/Content/GetManifestPublicRequest.h"
#include "BeamableCore/Public/AutoGen/ClientManifestResponse.h"

#define LOCTEXT_NAMESPACE "K2BeamNode_ApiRequest_GetManifestPublic"

using namespace BeamK2;

FName UK2BeamNode_ApiRequest_GetManifestPublic::GetSelfFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamContentApi, GetSelf);
}

FName UK2BeamNode_ApiRequest_GetManifestPublic::GetRequestFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamContentApi, GetManifestPublic);
}

FName UK2BeamNode_ApiRequest_GetManifestPublic::GetMakeFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UGetManifestPublicRequest, Make);
}

FString UK2BeamNode_ApiRequest_GetManifestPublic::GetServiceName() const
{
	return TEXT("Content");
}

FString UK2BeamNode_ApiRequest_GetManifestPublic::GetEndpointName() const
{
	return TEXT("GetManifestPublic");
}

UClass* UK2BeamNode_ApiRequest_GetManifestPublic::GetApiClass() const
{
	return UBeamContentApi::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_GetManifestPublic::GetRequestClass() const
{
	return UGetManifestPublicRequest::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_GetManifestPublic::GetResponseClass() const
{
	return UClientManifestResponse::StaticClass();
}

FString UK2BeamNode_ApiRequest_GetManifestPublic::GetRequestSuccessDelegateName() const
{
	return TEXT("OnGetManifestPublicSuccess");
}

FString UK2BeamNode_ApiRequest_GetManifestPublic::GetRequestErrorDelegateName() const
{
	return TEXT("OnGetManifestPublicError");
}

FString UK2BeamNode_ApiRequest_GetManifestPublic::GetRequestCompleteDelegateName() const
{
	return TEXT("OnGetManifestPublicComplete");
}

#undef LOCTEXT_NAMESPACE
