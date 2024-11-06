

#include "BeamableCoreBlueprintNodes/Public/BeamFlow/ApiRequest/AutoGen/Beamo/K2BeamNode_ApiRequest_DeleteMicroserviceFederationTraffic.h"

#include "BeamK2.h"

#include "BeamableCore/Public/AutoGen/SubSystems/BeamBeamoApi.h"
#include "BeamableCore/Public/AutoGen/SubSystems/Beamo/DeleteMicroserviceFederationTrafficRequest.h"
#include "BeamableCore/Public/AutoGen/CommonResponse.h"

#define LOCTEXT_NAMESPACE "K2BeamNode_ApiRequest_DeleteMicroserviceFederationTraffic"

using namespace BeamK2;

FName UK2BeamNode_ApiRequest_DeleteMicroserviceFederationTraffic::GetSelfFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamBeamoApi, GetSelf);
}

FName UK2BeamNode_ApiRequest_DeleteMicroserviceFederationTraffic::GetRequestFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamBeamoApi, DeleteMicroserviceFederationTraffic);
}

FName UK2BeamNode_ApiRequest_DeleteMicroserviceFederationTraffic::GetMakeFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UDeleteMicroserviceFederationTrafficRequest, Make);
}

FString UK2BeamNode_ApiRequest_DeleteMicroserviceFederationTraffic::GetServiceName() const
{
	return TEXT("Beamo");
}

FString UK2BeamNode_ApiRequest_DeleteMicroserviceFederationTraffic::GetEndpointName() const
{
	return TEXT("DeleteMicroserviceFederationTraffic");
}

UClass* UK2BeamNode_ApiRequest_DeleteMicroserviceFederationTraffic::GetApiClass() const
{
	return UBeamBeamoApi::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_DeleteMicroserviceFederationTraffic::GetRequestClass() const
{
	return UDeleteMicroserviceFederationTrafficRequest::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_DeleteMicroserviceFederationTraffic::GetResponseClass() const
{
	return UCommonResponse::StaticClass();
}

FString UK2BeamNode_ApiRequest_DeleteMicroserviceFederationTraffic::GetRequestSuccessDelegateName() const
{
	return TEXT("OnDeleteMicroserviceFederationTrafficSuccess");
}

FString UK2BeamNode_ApiRequest_DeleteMicroserviceFederationTraffic::GetRequestErrorDelegateName() const
{
	return TEXT("OnDeleteMicroserviceFederationTrafficError");
}

FString UK2BeamNode_ApiRequest_DeleteMicroserviceFederationTraffic::GetRequestCompleteDelegateName() const
{
	return TEXT("OnDeleteMicroserviceFederationTrafficComplete");
}

#undef LOCTEXT_NAMESPACE
