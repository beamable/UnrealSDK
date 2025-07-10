

#include "BeamableCoreBlueprintNodes/Public/BeamFlow/ApiRequest/AutoGen/Beamo/K2BeamNode_ApiRequest_BasicBeamoGetStoragePerformance.h"

#include "BeamK2.h"

#include "BeamableCore/Public/AutoGen/SubSystems/BeamBeamoApi.h"
#include "BeamableCore/Public/AutoGen/SubSystems/Beamo/BasicBeamoGetStoragePerformanceRequest.h"
#include "BeamableCore/Public/AutoGen/PerformanceResponse.h"

#define LOCTEXT_NAMESPACE "K2BeamNode_ApiRequest_BasicBeamoGetStoragePerformance"

using namespace BeamK2;

FName UK2BeamNode_ApiRequest_BasicBeamoGetStoragePerformance::GetSelfFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamBeamoApi, GetSelf);
}

FName UK2BeamNode_ApiRequest_BasicBeamoGetStoragePerformance::GetRequestFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamBeamoApi, BasicBeamoGetStoragePerformance);
}

FName UK2BeamNode_ApiRequest_BasicBeamoGetStoragePerformance::GetMakeFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBasicBeamoGetStoragePerformanceRequest, Make);
}

FString UK2BeamNode_ApiRequest_BasicBeamoGetStoragePerformance::GetServiceName() const
{
	return TEXT("Beamo");
}

FString UK2BeamNode_ApiRequest_BasicBeamoGetStoragePerformance::GetEndpointName() const
{
	return TEXT("BasicBeamoGetStoragePerformance");
}

UClass* UK2BeamNode_ApiRequest_BasicBeamoGetStoragePerformance::GetApiClass() const
{
	return UBeamBeamoApi::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_BasicBeamoGetStoragePerformance::GetRequestClass() const
{
	return UBasicBeamoGetStoragePerformanceRequest::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_BasicBeamoGetStoragePerformance::GetResponseClass() const
{
	return UPerformanceResponse::StaticClass();
}

FString UK2BeamNode_ApiRequest_BasicBeamoGetStoragePerformance::GetRequestSuccessDelegateName() const
{
	return TEXT("OnBasicBeamoGetStoragePerformanceSuccess");
}

FString UK2BeamNode_ApiRequest_BasicBeamoGetStoragePerformance::GetRequestErrorDelegateName() const
{
	return TEXT("OnBasicBeamoGetStoragePerformanceError");
}

FString UK2BeamNode_ApiRequest_BasicBeamoGetStoragePerformance::GetRequestCompleteDelegateName() const
{
	return TEXT("OnBasicBeamoGetStoragePerformanceComplete");
}

#undef LOCTEXT_NAMESPACE
