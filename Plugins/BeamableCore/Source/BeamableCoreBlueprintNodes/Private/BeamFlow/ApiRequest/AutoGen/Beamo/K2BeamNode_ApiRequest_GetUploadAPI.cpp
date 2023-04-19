

#include "BeamableCoreBlueprintNodes/Public/BeamFlow/ApiRequest/AutoGen/Beamo/K2BeamNode_ApiRequest_GetUploadAPI.h"

#include "BeamK2.h"

#include "BeamableCore/Public/AutoGen/SubSystems/BeamBeamoApi.h"
#include "BeamableCore/Public/AutoGen/SubSystems/Beamo/GetUploadAPIRequest.h"
#include "BeamableCore/Public/AutoGen/GetLambdaURI.h"

#define LOCTEXT_NAMESPACE "K2BeamNode_ApiRequest_GetUploadAPI"

using namespace BeamK2;

FName UK2BeamNode_ApiRequest_GetUploadAPI::GetSelfFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamBeamoApi, GetSelf);
}

FName UK2BeamNode_ApiRequest_GetUploadAPI::GetRequestFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamBeamoApi, GetUploadAPI);
}

FName UK2BeamNode_ApiRequest_GetUploadAPI::GetMakeFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UGetUploadAPIRequest, Make);
}

FString UK2BeamNode_ApiRequest_GetUploadAPI::GetServiceName() const
{
	return TEXT("Beamo");
}

FString UK2BeamNode_ApiRequest_GetUploadAPI::GetEndpointName() const
{
	return TEXT("GetUploadAPI");
}

UClass* UK2BeamNode_ApiRequest_GetUploadAPI::GetApiClass() const
{
	return UBeamBeamoApi::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_GetUploadAPI::GetRequestClass() const
{
	return UGetUploadAPIRequest::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_GetUploadAPI::GetResponseClass() const
{
	return UGetLambdaURI::StaticClass();
}

FString UK2BeamNode_ApiRequest_GetUploadAPI::GetRequestSuccessDelegateName() const
{
	return TEXT("OnGetUploadAPISuccess");
}

FString UK2BeamNode_ApiRequest_GetUploadAPI::GetRequestErrorDelegateName() const
{
	return TEXT("OnGetUploadAPIError");
}

FString UK2BeamNode_ApiRequest_GetUploadAPI::GetRequestCompleteDelegateName() const
{
	return TEXT("OnGetUploadAPIComplete");
}

#undef LOCTEXT_NAMESPACE
