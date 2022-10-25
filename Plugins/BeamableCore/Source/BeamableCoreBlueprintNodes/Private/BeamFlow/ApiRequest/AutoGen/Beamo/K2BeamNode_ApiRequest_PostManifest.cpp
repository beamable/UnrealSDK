

#include "BeamFlow/ApiRequest/AutoGen/Beamo/K2BeamNode_ApiRequest_PostManifest.h"

#include "BeamK2.h"

#include "AutoGen/SubSystems/BeamBeamoApi.h"
#include "AutoGen/SubSystems/Beamo/PostManifestRequest.h"
#include "AutoGen/PostManifestResponse.h"

#define LOCTEXT_NAMESPACE "K2BeamNode_ApiRequest_PostManifest"

using namespace BeamK2;

FName UK2BeamNode_ApiRequest_PostManifest::GetSelfFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamBeamoApi, GetSelf);
}

FName UK2BeamNode_ApiRequest_PostManifest::GetRequestFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamBeamoApi, PostManifest);
}

FName UK2BeamNode_ApiRequest_PostManifest::GetMakeFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UPostManifestRequest, Make);
}

FString UK2BeamNode_ApiRequest_PostManifest::GetServiceName() const
{
	return TEXT("Beamo");
}

FString UK2BeamNode_ApiRequest_PostManifest::GetEndpointName() const
{
	return TEXT("PostManifest");
}

UClass* UK2BeamNode_ApiRequest_PostManifest::GetApiClass() const
{
	return UBeamBeamoApi::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_PostManifest::GetRequestClass() const
{
	return UPostManifestRequest::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_PostManifest::GetResponseClass() const
{
	return UPostManifestResponse::StaticClass();
}

FString UK2BeamNode_ApiRequest_PostManifest::GetRequestSuccessDelegateName() const
{
	return TEXT("OnPostManifestSuccess");
}

FString UK2BeamNode_ApiRequest_PostManifest::GetRequestErrorDelegateName() const
{
	return TEXT("OnPostManifestError");
}

FString UK2BeamNode_ApiRequest_PostManifest::GetRequestCompleteDelegateName() const
{
	return TEXT("OnPostManifestComplete");
}

#undef LOCTEXT_NAMESPACE
