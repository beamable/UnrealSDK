

#include "BeamableCoreBlueprintNodes/Public/BeamFlow/ApiRequest/AutoGen/Beamo/K2BeamNode_ApiRequest_GetStatus.h"

#include "BeamK2.h"

#include "BeamableCore/Public/AutoGen/SubSystems/BeamBeamoApi.h"
#include "BeamableCore/Public/AutoGen/SubSystems/Beamo/GetStatusRequest.h"
#include "BeamableCore/Public/AutoGen/GetStatusResponse.h"

#define LOCTEXT_NAMESPACE "K2BeamNode_ApiRequest_GetStatus"

using namespace BeamK2;

FName UK2BeamNode_ApiRequest_GetStatus::GetSelfFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamBeamoApi, GetSelf);
}

FName UK2BeamNode_ApiRequest_GetStatus::GetRequestFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamBeamoApi, GetStatus);
}

FName UK2BeamNode_ApiRequest_GetStatus::GetMakeFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UGetStatusRequest, Make);
}

FString UK2BeamNode_ApiRequest_GetStatus::GetServiceName() const
{
	return TEXT("Beamo");
}

FString UK2BeamNode_ApiRequest_GetStatus::GetEndpointName() const
{
	return TEXT("GetStatus");
}

UClass* UK2BeamNode_ApiRequest_GetStatus::GetApiClass() const
{
	return UBeamBeamoApi::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_GetStatus::GetRequestClass() const
{
	return UGetStatusRequest::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_GetStatus::GetResponseClass() const
{
	return UGetStatusResponse::StaticClass();
}

FString UK2BeamNode_ApiRequest_GetStatus::GetRequestSuccessDelegateName() const
{
	return TEXT("OnGetStatusSuccess");
}

FString UK2BeamNode_ApiRequest_GetStatus::GetRequestErrorDelegateName() const
{
	return TEXT("OnGetStatusError");
}

FString UK2BeamNode_ApiRequest_GetStatus::GetRequestCompleteDelegateName() const
{
	return TEXT("OnGetStatusComplete");
}

#undef LOCTEXT_NAMESPACE
