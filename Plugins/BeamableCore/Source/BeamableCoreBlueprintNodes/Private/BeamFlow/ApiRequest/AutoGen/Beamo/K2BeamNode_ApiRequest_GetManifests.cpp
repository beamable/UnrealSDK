

#include "BeamFlow/ApiRequest/AutoGen/Beamo/K2BeamNode_ApiRequest_GetManifests.h"

#include "BeamK2.h"

#include "AutoGen/SubSystems/BeamBeamoApi.h"
#include "AutoGen/SubSystems/Beamo/GetManifestsRequest.h"
#include "AutoGen/GetManifestsResponse.h"

#define LOCTEXT_NAMESPACE "K2BeamNode_ApiRequest_GetManifests"

using namespace BeamK2;

FName UK2BeamNode_ApiRequest_GetManifests::GetSelfFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamBeamoApi, GetSelf);
}

FName UK2BeamNode_ApiRequest_GetManifests::GetRequestFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamBeamoApi, GetManifests);
}

FName UK2BeamNode_ApiRequest_GetManifests::GetMakeFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UGetManifestsRequest, Make);
}

FString UK2BeamNode_ApiRequest_GetManifests::GetServiceName() const
{
	return TEXT("Beamo");
}

FString UK2BeamNode_ApiRequest_GetManifests::GetEndpointName() const
{
	return TEXT("GetManifests");
}

UClass* UK2BeamNode_ApiRequest_GetManifests::GetApiClass() const
{
	return UBeamBeamoApi::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_GetManifests::GetRequestClass() const
{
	return UGetManifestsRequest::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_GetManifests::GetResponseClass() const
{
	return UGetManifestsResponse::StaticClass();
}

FString UK2BeamNode_ApiRequest_GetManifests::GetRequestSuccessDelegateName() const
{
	return TEXT("OnGetManifestsSuccess");
}

FString UK2BeamNode_ApiRequest_GetManifests::GetRequestErrorDelegateName() const
{
	return TEXT("OnGetManifestsError");
}

FString UK2BeamNode_ApiRequest_GetManifests::GetRequestCompleteDelegateName() const
{
	return TEXT("OnGetManifestsComplete");
}

#undef LOCTEXT_NAMESPACE
