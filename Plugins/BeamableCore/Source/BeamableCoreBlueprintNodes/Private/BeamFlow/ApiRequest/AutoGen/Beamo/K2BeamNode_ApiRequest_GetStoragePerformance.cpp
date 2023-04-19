

#include "BeamableCoreBlueprintNodes/Public/BeamFlow/ApiRequest/AutoGen/Beamo/K2BeamNode_ApiRequest_GetStoragePerformance.h"

#include "BeamK2.h"

#include "BeamableCore/Public/AutoGen/SubSystems/BeamBeamoApi.h"
#include "BeamableCore/Public/AutoGen/SubSystems/Beamo/GetStoragePerformanceRequest.h"
#include "BeamableCore/Public/AutoGen/PerformanceResponse.h"

#define LOCTEXT_NAMESPACE "K2BeamNode_ApiRequest_GetStoragePerformance"

using namespace BeamK2;

FName UK2BeamNode_ApiRequest_GetStoragePerformance::GetSelfFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamBeamoApi, GetSelf);
}

FName UK2BeamNode_ApiRequest_GetStoragePerformance::GetRequestFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamBeamoApi, GetStoragePerformance);
}

FName UK2BeamNode_ApiRequest_GetStoragePerformance::GetMakeFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UGetStoragePerformanceRequest, Make);
}

FString UK2BeamNode_ApiRequest_GetStoragePerformance::GetServiceName() const
{
	return TEXT("Beamo");
}

FString UK2BeamNode_ApiRequest_GetStoragePerformance::GetEndpointName() const
{
	return TEXT("GetStoragePerformance");
}

UClass* UK2BeamNode_ApiRequest_GetStoragePerformance::GetApiClass() const
{
	return UBeamBeamoApi::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_GetStoragePerformance::GetRequestClass() const
{
	return UGetStoragePerformanceRequest::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_GetStoragePerformance::GetResponseClass() const
{
	return UPerformanceResponse::StaticClass();
}

FString UK2BeamNode_ApiRequest_GetStoragePerformance::GetRequestSuccessDelegateName() const
{
	return TEXT("OnGetStoragePerformanceSuccess");
}

FString UK2BeamNode_ApiRequest_GetStoragePerformance::GetRequestErrorDelegateName() const
{
	return TEXT("OnGetStoragePerformanceError");
}

FString UK2BeamNode_ApiRequest_GetStoragePerformance::GetRequestCompleteDelegateName() const
{
	return TEXT("OnGetStoragePerformanceComplete");
}

#undef LOCTEXT_NAMESPACE
