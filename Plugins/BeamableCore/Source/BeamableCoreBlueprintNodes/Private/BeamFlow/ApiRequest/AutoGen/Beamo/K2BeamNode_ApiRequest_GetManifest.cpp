

#include "BeamFlow/ApiRequest/AutoGen/Beamo/K2BeamNode_ApiRequest_GetManifest.h"

#include "BeamK2.h"

#include "AutoGen/SubSystems/BeamBeamoApi.h"
#include "AutoGen/SubSystems/Beamo/GetManifestRequest.h"
#include "AutoGen/GetManifestResponse.h"

#define LOCTEXT_NAMESPACE "K2BeamNode_ApiRequest_GetManifest"

using namespace BeamK2;

FName UK2BeamNode_ApiRequest_GetManifest::GetSelfFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamBeamoApi, GetSelf);
}

FName UK2BeamNode_ApiRequest_GetManifest::GetRequestFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamBeamoApi, GetManifest);
}

FName UK2BeamNode_ApiRequest_GetManifest::GetMakeFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UGetManifestRequest, Make);
}

FString UK2BeamNode_ApiRequest_GetManifest::GetServiceName() const
{
	return TEXT("Beamo");
}

FString UK2BeamNode_ApiRequest_GetManifest::GetEndpointName() const
{
	return TEXT("GetManifest");
}

UClass* UK2BeamNode_ApiRequest_GetManifest::GetApiClass() const
{
	return UBeamBeamoApi::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_GetManifest::GetRequestClass() const
{
	return UGetManifestRequest::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_GetManifest::GetResponseClass() const
{
	return UGetManifestResponse::StaticClass();
}

FString UK2BeamNode_ApiRequest_GetManifest::GetRequestSuccessDelegateName() const
{
	return TEXT("OnGetManifestSuccess");
}

FString UK2BeamNode_ApiRequest_GetManifest::GetRequestErrorDelegateName() const
{
	return TEXT("OnGetManifestError");
}

FString UK2BeamNode_ApiRequest_GetManifest::GetRequestCompleteDelegateName() const
{
	return TEXT("OnGetManifestComplete");
}

#undef LOCTEXT_NAMESPACE
