

#include "BeamableCoreBlueprintNodes/Public/BeamFlow/ApiRequest/AutoGen/Cloudsaving/K2BeamNode_ApiRequest_GetDataMetadata.h"

#include "BeamK2.h"

#include "BeamableCore/Public/AutoGen/SubSystems/BeamCloudsavingApi.h"
#include "BeamableCore/Public/AutoGen/SubSystems/Cloudsaving/GetDataMetadataRequest.h"
#include "BeamableCore/Public/AutoGen/ObjectsMetadataResponse.h"

#define LOCTEXT_NAMESPACE "K2BeamNode_ApiRequest_GetDataMetadata"

using namespace BeamK2;

FName UK2BeamNode_ApiRequest_GetDataMetadata::GetSelfFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamCloudsavingApi, GetSelf);
}

FName UK2BeamNode_ApiRequest_GetDataMetadata::GetRequestFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamCloudsavingApi, GetDataMetadata);
}

FName UK2BeamNode_ApiRequest_GetDataMetadata::GetMakeFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UGetDataMetadataRequest, Make);
}

FString UK2BeamNode_ApiRequest_GetDataMetadata::GetServiceName() const
{
	return TEXT("Cloudsaving");
}

FString UK2BeamNode_ApiRequest_GetDataMetadata::GetEndpointName() const
{
	return TEXT("GetDataMetadata");
}

UClass* UK2BeamNode_ApiRequest_GetDataMetadata::GetApiClass() const
{
	return UBeamCloudsavingApi::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_GetDataMetadata::GetRequestClass() const
{
	return UGetDataMetadataRequest::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_GetDataMetadata::GetResponseClass() const
{
	return UObjectsMetadataResponse::StaticClass();
}

FString UK2BeamNode_ApiRequest_GetDataMetadata::GetRequestSuccessDelegateName() const
{
	return TEXT("OnGetDataMetadataSuccess");
}

FString UK2BeamNode_ApiRequest_GetDataMetadata::GetRequestErrorDelegateName() const
{
	return TEXT("OnGetDataMetadataError");
}

FString UK2BeamNode_ApiRequest_GetDataMetadata::GetRequestCompleteDelegateName() const
{
	return TEXT("OnGetDataMetadataComplete");
}

#undef LOCTEXT_NAMESPACE
