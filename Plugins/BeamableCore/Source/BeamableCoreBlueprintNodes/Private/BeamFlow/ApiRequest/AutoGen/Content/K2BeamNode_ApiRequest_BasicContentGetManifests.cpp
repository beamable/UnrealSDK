

#include "BeamableCoreBlueprintNodes/Public/BeamFlow/ApiRequest/AutoGen/Content/K2BeamNode_ApiRequest_BasicContentGetManifests.h"

#include "BeamK2.h"

#include "BeamableCore/Public/AutoGen/SubSystems/BeamContentApi.h"
#include "BeamableCore/Public/AutoGen/SubSystems/Content/BasicContentGetManifestsRequest.h"
#include "BeamableCore/Public/AutoGen/GetManifestsResponse.h"

#define LOCTEXT_NAMESPACE "K2BeamNode_ApiRequest_BasicContentGetManifests"

using namespace BeamK2;

FName UK2BeamNode_ApiRequest_BasicContentGetManifests::GetSelfFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamContentApi, GetSelf);
}

FName UK2BeamNode_ApiRequest_BasicContentGetManifests::GetRequestFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamContentApi, GetManifests);
}

FName UK2BeamNode_ApiRequest_BasicContentGetManifests::GetMakeFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBasicContentGetManifestsRequest, Make);
}

FString UK2BeamNode_ApiRequest_BasicContentGetManifests::GetServiceName() const
{
	return TEXT("Content");
}

FString UK2BeamNode_ApiRequest_BasicContentGetManifests::GetEndpointName() const
{
	return TEXT("GetManifests");
}

UClass* UK2BeamNode_ApiRequest_BasicContentGetManifests::GetApiClass() const
{
	return UBeamContentApi::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_BasicContentGetManifests::GetRequestClass() const
{
	return UBasicContentGetManifestsRequest::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_BasicContentGetManifests::GetResponseClass() const
{
	return UGetManifestsResponse::StaticClass();
}

FString UK2BeamNode_ApiRequest_BasicContentGetManifests::GetRequestSuccessDelegateName() const
{
	return TEXT("OnBasicContentGetManifestsSuccess");
}

FString UK2BeamNode_ApiRequest_BasicContentGetManifests::GetRequestErrorDelegateName() const
{
	return TEXT("OnBasicContentGetManifestsError");
}

FString UK2BeamNode_ApiRequest_BasicContentGetManifests::GetRequestCompleteDelegateName() const
{
	return TEXT("OnBasicContentGetManifestsComplete");
}

#undef LOCTEXT_NAMESPACE
