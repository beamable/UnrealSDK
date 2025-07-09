

#include "BeamableCoreBlueprintNodes/Public/BeamFlow/ApiRequest/AutoGen/Beamo/K2BeamNode_ApiRequest_BasicBeamoGetStatus.h"

#include "BeamK2.h"

#include "BeamableCore/Public/AutoGen/SubSystems/BeamBeamoApi.h"
#include "BeamableCore/Public/AutoGen/SubSystems/Beamo/BasicBeamoGetStatusRequest.h"
#include "BeamableCore/Public/AutoGen/GetStatusResponse.h"

#define LOCTEXT_NAMESPACE "K2BeamNode_ApiRequest_BasicBeamoGetStatus"

using namespace BeamK2;

FName UK2BeamNode_ApiRequest_BasicBeamoGetStatus::GetSelfFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamBeamoApi, GetSelf);
}

FName UK2BeamNode_ApiRequest_BasicBeamoGetStatus::GetRequestFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamBeamoApi, BasicBeamoGetStatus);
}

FName UK2BeamNode_ApiRequest_BasicBeamoGetStatus::GetMakeFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBasicBeamoGetStatusRequest, Make);
}

FString UK2BeamNode_ApiRequest_BasicBeamoGetStatus::GetServiceName() const
{
	return TEXT("Beamo");
}

FString UK2BeamNode_ApiRequest_BasicBeamoGetStatus::GetEndpointName() const
{
	return TEXT("BasicBeamoGetStatus");
}

UClass* UK2BeamNode_ApiRequest_BasicBeamoGetStatus::GetApiClass() const
{
	return UBeamBeamoApi::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_BasicBeamoGetStatus::GetRequestClass() const
{
	return UBasicBeamoGetStatusRequest::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_BasicBeamoGetStatus::GetResponseClass() const
{
	return UGetStatusResponse::StaticClass();
}

FString UK2BeamNode_ApiRequest_BasicBeamoGetStatus::GetRequestSuccessDelegateName() const
{
	return TEXT("OnBasicBeamoGetStatusSuccess");
}

FString UK2BeamNode_ApiRequest_BasicBeamoGetStatus::GetRequestErrorDelegateName() const
{
	return TEXT("OnBasicBeamoGetStatusError");
}

FString UK2BeamNode_ApiRequest_BasicBeamoGetStatus::GetRequestCompleteDelegateName() const
{
	return TEXT("OnBasicBeamoGetStatusComplete");
}

#undef LOCTEXT_NAMESPACE
