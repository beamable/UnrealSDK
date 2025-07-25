

#include "BeamableCoreBlueprintNodes/Public/BeamFlow/ApiRequest/AutoGen/Beamo/K2BeamNode_ApiRequest_ApiBeamoGetStoragePerformanceByStorageObjectName.h"

#include "BeamK2.h"

#include "BeamableCore/Public/AutoGen/SubSystems/BeamBeamoApi.h"
#include "BeamableCore/Public/AutoGen/SubSystems/Beamo/ApiBeamoGetStoragePerformanceByStorageObjectNameRequest.h"
#include "BeamableCore/Public/AutoGen/BeamoV2StoragePerformance.h"

#define LOCTEXT_NAMESPACE "K2BeamNode_ApiRequest_ApiBeamoGetStoragePerformanceByStorageObjectName"

using namespace BeamK2;

FName UK2BeamNode_ApiRequest_ApiBeamoGetStoragePerformanceByStorageObjectName::GetSelfFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamBeamoApi, GetSelf);
}

FName UK2BeamNode_ApiRequest_ApiBeamoGetStoragePerformanceByStorageObjectName::GetRequestFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamBeamoApi, ApiBeamoGetStoragePerformanceByStorageObjectName);
}

FName UK2BeamNode_ApiRequest_ApiBeamoGetStoragePerformanceByStorageObjectName::GetMakeFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UApiBeamoGetStoragePerformanceByStorageObjectNameRequest, Make);
}

FString UK2BeamNode_ApiRequest_ApiBeamoGetStoragePerformanceByStorageObjectName::GetServiceName() const
{
	return TEXT("Beamo");
}

FString UK2BeamNode_ApiRequest_ApiBeamoGetStoragePerformanceByStorageObjectName::GetEndpointName() const
{
	return TEXT("ApiBeamoGetStoragePerformanceByStorageObjectName");
}

UClass* UK2BeamNode_ApiRequest_ApiBeamoGetStoragePerformanceByStorageObjectName::GetApiClass() const
{
	return UBeamBeamoApi::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_ApiBeamoGetStoragePerformanceByStorageObjectName::GetRequestClass() const
{
	return UApiBeamoGetStoragePerformanceByStorageObjectNameRequest::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_ApiBeamoGetStoragePerformanceByStorageObjectName::GetResponseClass() const
{
	return UBeamoV2StoragePerformance::StaticClass();
}

FString UK2BeamNode_ApiRequest_ApiBeamoGetStoragePerformanceByStorageObjectName::GetRequestSuccessDelegateName() const
{
	return TEXT("OnApiBeamoGetStoragePerformanceByStorageObjectNameSuccess");
}

FString UK2BeamNode_ApiRequest_ApiBeamoGetStoragePerformanceByStorageObjectName::GetRequestErrorDelegateName() const
{
	return TEXT("OnApiBeamoGetStoragePerformanceByStorageObjectNameError");
}

FString UK2BeamNode_ApiRequest_ApiBeamoGetStoragePerformanceByStorageObjectName::GetRequestCompleteDelegateName() const
{
	return TEXT("OnApiBeamoGetStoragePerformanceByStorageObjectNameComplete");
}

#undef LOCTEXT_NAMESPACE
