

#include "BeamableCoreBlueprintNodes/Public/BeamFlow/ApiRequest/AutoGen/Beamo/K2BeamNode_ApiRequest_ApiBeamoGetStatus.h"

#include "BeamK2.h"

#include "BeamableCore/Public/AutoGen/SubSystems/BeamBeamoApi.h"
#include "BeamableCore/Public/AutoGen/SubSystems/Beamo/ApiBeamoGetStatusRequest.h"
#include "BeamableCore/Public/AutoGen/BeamoV2GetStatusResponse.h"

#define LOCTEXT_NAMESPACE "K2BeamNode_ApiRequest_ApiBeamoGetStatus"

using namespace BeamK2;

FName UK2BeamNode_ApiRequest_ApiBeamoGetStatus::GetSelfFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamBeamoApi, GetSelf);
}

FName UK2BeamNode_ApiRequest_ApiBeamoGetStatus::GetRequestFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamBeamoApi, ApiBeamoGetStatus);
}

FName UK2BeamNode_ApiRequest_ApiBeamoGetStatus::GetMakeFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UApiBeamoGetStatusRequest, Make);
}

FString UK2BeamNode_ApiRequest_ApiBeamoGetStatus::GetServiceName() const
{
	return TEXT("Beamo");
}

FString UK2BeamNode_ApiRequest_ApiBeamoGetStatus::GetEndpointName() const
{
	return TEXT("ApiBeamoGetStatus");
}

UClass* UK2BeamNode_ApiRequest_ApiBeamoGetStatus::GetApiClass() const
{
	return UBeamBeamoApi::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_ApiBeamoGetStatus::GetRequestClass() const
{
	return UApiBeamoGetStatusRequest::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_ApiBeamoGetStatus::GetResponseClass() const
{
	return UBeamoV2GetStatusResponse::StaticClass();
}

FString UK2BeamNode_ApiRequest_ApiBeamoGetStatus::GetRequestSuccessDelegateName() const
{
	return TEXT("OnApiBeamoGetStatusSuccess");
}

FString UK2BeamNode_ApiRequest_ApiBeamoGetStatus::GetRequestErrorDelegateName() const
{
	return TEXT("OnApiBeamoGetStatusError");
}

FString UK2BeamNode_ApiRequest_ApiBeamoGetStatus::GetRequestCompleteDelegateName() const
{
	return TEXT("OnApiBeamoGetStatusComplete");
}

#undef LOCTEXT_NAMESPACE
