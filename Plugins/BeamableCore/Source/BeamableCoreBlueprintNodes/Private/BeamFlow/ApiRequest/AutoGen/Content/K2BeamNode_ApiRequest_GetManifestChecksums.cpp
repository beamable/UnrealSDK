

#include "BeamableCoreBlueprintNodes/Public/BeamFlow/ApiRequest/AutoGen/Content/K2BeamNode_ApiRequest_GetManifestChecksums.h"

#include "BeamK2.h"

#include "BeamableCore/Public/AutoGen/SubSystems/BeamContentApi.h"
#include "BeamableCore/Public/AutoGen/SubSystems/Content/GetManifestChecksumsRequest.h"
#include "BeamableCore/Public/AutoGen/ManifestChecksums.h"

#define LOCTEXT_NAMESPACE "K2BeamNode_ApiRequest_GetManifestChecksums"

using namespace BeamK2;

FName UK2BeamNode_ApiRequest_GetManifestChecksums::GetSelfFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamContentApi, GetSelf);
}

FName UK2BeamNode_ApiRequest_GetManifestChecksums::GetRequestFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamContentApi, GetManifestChecksums);
}

FName UK2BeamNode_ApiRequest_GetManifestChecksums::GetMakeFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UGetManifestChecksumsRequest, Make);
}

FString UK2BeamNode_ApiRequest_GetManifestChecksums::GetServiceName() const
{
	return TEXT("Content");
}

FString UK2BeamNode_ApiRequest_GetManifestChecksums::GetEndpointName() const
{
	return TEXT("GetManifestChecksums");
}

UClass* UK2BeamNode_ApiRequest_GetManifestChecksums::GetApiClass() const
{
	return UBeamContentApi::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_GetManifestChecksums::GetRequestClass() const
{
	return UGetManifestChecksumsRequest::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_GetManifestChecksums::GetResponseClass() const
{
	return UManifestChecksums::StaticClass();
}

FString UK2BeamNode_ApiRequest_GetManifestChecksums::GetRequestSuccessDelegateName() const
{
	return TEXT("OnGetManifestChecksumsSuccess");
}

FString UK2BeamNode_ApiRequest_GetManifestChecksums::GetRequestErrorDelegateName() const
{
	return TEXT("OnGetManifestChecksumsError");
}

FString UK2BeamNode_ApiRequest_GetManifestChecksums::GetRequestCompleteDelegateName() const
{
	return TEXT("OnGetManifestChecksumsComplete");
}

#undef LOCTEXT_NAMESPACE
