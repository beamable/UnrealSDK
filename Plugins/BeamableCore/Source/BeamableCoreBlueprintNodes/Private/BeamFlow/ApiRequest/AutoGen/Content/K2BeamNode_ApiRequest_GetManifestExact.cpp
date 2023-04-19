

#include "BeamableCoreBlueprintNodes/Public/BeamFlow/ApiRequest/AutoGen/Content/K2BeamNode_ApiRequest_GetManifestExact.h"

#include "BeamK2.h"

#include "BeamableCore/Public/AutoGen/SubSystems/BeamContentApi.h"
#include "BeamableCore/Public/AutoGen/SubSystems/Content/GetManifestExactRequest.h"
#include "BeamableCore/Public/AutoGen/ContentBasicManifest.h"

#define LOCTEXT_NAMESPACE "K2BeamNode_ApiRequest_GetManifestExact"

using namespace BeamK2;

FName UK2BeamNode_ApiRequest_GetManifestExact::GetSelfFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamContentApi, GetSelf);
}

FName UK2BeamNode_ApiRequest_GetManifestExact::GetRequestFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamContentApi, GetManifestExact);
}

FName UK2BeamNode_ApiRequest_GetManifestExact::GetMakeFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UGetManifestExactRequest, Make);
}

FString UK2BeamNode_ApiRequest_GetManifestExact::GetServiceName() const
{
	return TEXT("Content");
}

FString UK2BeamNode_ApiRequest_GetManifestExact::GetEndpointName() const
{
	return TEXT("GetManifestExact");
}

UClass* UK2BeamNode_ApiRequest_GetManifestExact::GetApiClass() const
{
	return UBeamContentApi::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_GetManifestExact::GetRequestClass() const
{
	return UGetManifestExactRequest::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_GetManifestExact::GetResponseClass() const
{
	return UContentBasicManifest::StaticClass();
}

FString UK2BeamNode_ApiRequest_GetManifestExact::GetRequestSuccessDelegateName() const
{
	return TEXT("OnGetManifestExactSuccess");
}

FString UK2BeamNode_ApiRequest_GetManifestExact::GetRequestErrorDelegateName() const
{
	return TEXT("OnGetManifestExactError");
}

FString UK2BeamNode_ApiRequest_GetManifestExact::GetRequestCompleteDelegateName() const
{
	return TEXT("OnGetManifestExactComplete");
}

#undef LOCTEXT_NAMESPACE
