

#include "BeamableCoreBlueprintNodes/Public/BeamFlow/ApiRequest/AutoGen/Beamo/K2BeamNode_ApiRequest_GetManifestCurrent.h"

#include "BeamK2.h"

#include "BeamableCore/Public/AutoGen/SubSystems/BeamBeamoApi.h"
#include "BeamableCore/Public/AutoGen/SubSystems/Beamo/GetManifestCurrentRequest.h"
#include "BeamableCore/Public/AutoGen/GetCurrentManifestResponse.h"

#define LOCTEXT_NAMESPACE "K2BeamNode_ApiRequest_GetManifestCurrent"

using namespace BeamK2;

FName UK2BeamNode_ApiRequest_GetManifestCurrent::GetSelfFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamBeamoApi, GetSelf);
}

FName UK2BeamNode_ApiRequest_GetManifestCurrent::GetRequestFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamBeamoApi, GetManifestCurrent);
}

FName UK2BeamNode_ApiRequest_GetManifestCurrent::GetMakeFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UGetManifestCurrentRequest, Make);
}

FString UK2BeamNode_ApiRequest_GetManifestCurrent::GetServiceName() const
{
	return TEXT("Beamo");
}

FString UK2BeamNode_ApiRequest_GetManifestCurrent::GetEndpointName() const
{
	return TEXT("GetManifestCurrent");
}

UClass* UK2BeamNode_ApiRequest_GetManifestCurrent::GetApiClass() const
{
	return UBeamBeamoApi::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_GetManifestCurrent::GetRequestClass() const
{
	return UGetManifestCurrentRequest::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_GetManifestCurrent::GetResponseClass() const
{
	return UGetCurrentManifestResponse::StaticClass();
}

FString UK2BeamNode_ApiRequest_GetManifestCurrent::GetRequestSuccessDelegateName() const
{
	return TEXT("OnGetManifestCurrentSuccess");
}

FString UK2BeamNode_ApiRequest_GetManifestCurrent::GetRequestErrorDelegateName() const
{
	return TEXT("OnGetManifestCurrentError");
}

FString UK2BeamNode_ApiRequest_GetManifestCurrent::GetRequestCompleteDelegateName() const
{
	return TEXT("OnGetManifestCurrentComplete");
}

#undef LOCTEXT_NAMESPACE
