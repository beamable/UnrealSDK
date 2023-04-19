

#include "BeamableCoreBlueprintNodes/Public/BeamFlow/ApiRequest/AutoGen/Content/K2BeamNode_ApiRequest_GetManifestChecksum.h"

#include "BeamK2.h"

#include "BeamableCore/Public/AutoGen/SubSystems/BeamContentApi.h"
#include "BeamableCore/Public/AutoGen/SubSystems/Content/GetManifestChecksumRequest.h"
#include "BeamableCore/Public/AutoGen/ContentBasicManifestChecksum.h"

#define LOCTEXT_NAMESPACE "K2BeamNode_ApiRequest_GetManifestChecksum"

using namespace BeamK2;

FName UK2BeamNode_ApiRequest_GetManifestChecksum::GetSelfFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamContentApi, GetSelf);
}

FName UK2BeamNode_ApiRequest_GetManifestChecksum::GetRequestFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamContentApi, GetManifestChecksum);
}

FName UK2BeamNode_ApiRequest_GetManifestChecksum::GetMakeFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UGetManifestChecksumRequest, Make);
}

FString UK2BeamNode_ApiRequest_GetManifestChecksum::GetServiceName() const
{
	return TEXT("Content");
}

FString UK2BeamNode_ApiRequest_GetManifestChecksum::GetEndpointName() const
{
	return TEXT("GetManifestChecksum");
}

UClass* UK2BeamNode_ApiRequest_GetManifestChecksum::GetApiClass() const
{
	return UBeamContentApi::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_GetManifestChecksum::GetRequestClass() const
{
	return UGetManifestChecksumRequest::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_GetManifestChecksum::GetResponseClass() const
{
	return UContentBasicManifestChecksum::StaticClass();
}

FString UK2BeamNode_ApiRequest_GetManifestChecksum::GetRequestSuccessDelegateName() const
{
	return TEXT("OnGetManifestChecksumSuccess");
}

FString UK2BeamNode_ApiRequest_GetManifestChecksum::GetRequestErrorDelegateName() const
{
	return TEXT("OnGetManifestChecksumError");
}

FString UK2BeamNode_ApiRequest_GetManifestChecksum::GetRequestCompleteDelegateName() const
{
	return TEXT("OnGetManifestChecksumComplete");
}

#undef LOCTEXT_NAMESPACE
