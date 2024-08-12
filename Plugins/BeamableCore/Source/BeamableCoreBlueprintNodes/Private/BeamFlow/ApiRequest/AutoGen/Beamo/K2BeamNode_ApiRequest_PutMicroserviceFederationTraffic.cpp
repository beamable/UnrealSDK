

#include "BeamableCoreBlueprintNodes/Public/BeamFlow/ApiRequest/AutoGen/Beamo/K2BeamNode_ApiRequest_PutMicroserviceFederationTraffic.h"

#include "BeamK2.h"

#include "BeamableCore/Public/AutoGen/SubSystems/BeamBeamoApi.h"
#include "BeamableCore/Public/AutoGen/SubSystems/Beamo/PutMicroserviceFederationTrafficRequest.h"
#include "BeamableCore/Public/AutoGen/CommonResponse.h"

#define LOCTEXT_NAMESPACE "K2BeamNode_ApiRequest_PutMicroserviceFederationTraffic"

using namespace BeamK2;

FName UK2BeamNode_ApiRequest_PutMicroserviceFederationTraffic::GetSelfFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamBeamoApi, GetSelf);
}

FName UK2BeamNode_ApiRequest_PutMicroserviceFederationTraffic::GetRequestFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamBeamoApi, PutMicroserviceFederationTraffic);
}

FName UK2BeamNode_ApiRequest_PutMicroserviceFederationTraffic::GetMakeFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UPutMicroserviceFederationTrafficRequest, Make);
}

FString UK2BeamNode_ApiRequest_PutMicroserviceFederationTraffic::GetServiceName() const
{
	return TEXT("Beamo");
}

FString UK2BeamNode_ApiRequest_PutMicroserviceFederationTraffic::GetEndpointName() const
{
	return TEXT("PutMicroserviceFederationTraffic");
}

UClass* UK2BeamNode_ApiRequest_PutMicroserviceFederationTraffic::GetApiClass() const
{
	return UBeamBeamoApi::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_PutMicroserviceFederationTraffic::GetRequestClass() const
{
	return UPutMicroserviceFederationTrafficRequest::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_PutMicroserviceFederationTraffic::GetResponseClass() const
{
	return UCommonResponse::StaticClass();
}

FString UK2BeamNode_ApiRequest_PutMicroserviceFederationTraffic::GetRequestSuccessDelegateName() const
{
	return TEXT("OnPutMicroserviceFederationTrafficSuccess");
}

FString UK2BeamNode_ApiRequest_PutMicroserviceFederationTraffic::GetRequestErrorDelegateName() const
{
	return TEXT("OnPutMicroserviceFederationTrafficError");
}

FString UK2BeamNode_ApiRequest_PutMicroserviceFederationTraffic::GetRequestCompleteDelegateName() const
{
	return TEXT("OnPutMicroserviceFederationTrafficComplete");
}

#undef LOCTEXT_NAMESPACE
