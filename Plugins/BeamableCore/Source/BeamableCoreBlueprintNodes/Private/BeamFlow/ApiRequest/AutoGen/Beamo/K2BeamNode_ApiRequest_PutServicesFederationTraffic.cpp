

#include "BeamableCoreBlueprintNodes/Public/BeamFlow/ApiRequest/AutoGen/Beamo/K2BeamNode_ApiRequest_PutServicesFederationTraffic.h"

#include "BeamK2.h"

#include "BeamableCore/Public/AutoGen/SubSystems/BeamBeamoApi.h"
#include "BeamableCore/Public/AutoGen/SubSystems/Beamo/PutServicesFederationTrafficRequest.h"
#include "BeamableCore/Public/AutoGen/BeamoV2EmptyMessage.h"

#define LOCTEXT_NAMESPACE "K2BeamNode_ApiRequest_PutServicesFederationTraffic"

using namespace BeamK2;

FName UK2BeamNode_ApiRequest_PutServicesFederationTraffic::GetSelfFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamBeamoApi, GetSelf);
}

FName UK2BeamNode_ApiRequest_PutServicesFederationTraffic::GetRequestFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamBeamoApi, PutServicesFederationTraffic);
}

FName UK2BeamNode_ApiRequest_PutServicesFederationTraffic::GetMakeFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UPutServicesFederationTrafficRequest, Make);
}

FString UK2BeamNode_ApiRequest_PutServicesFederationTraffic::GetServiceName() const
{
	return TEXT("Beamo");
}

FString UK2BeamNode_ApiRequest_PutServicesFederationTraffic::GetEndpointName() const
{
	return TEXT("PutServicesFederationTraffic");
}

UClass* UK2BeamNode_ApiRequest_PutServicesFederationTraffic::GetApiClass() const
{
	return UBeamBeamoApi::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_PutServicesFederationTraffic::GetRequestClass() const
{
	return UPutServicesFederationTrafficRequest::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_PutServicesFederationTraffic::GetResponseClass() const
{
	return UBeamoV2EmptyMessage::StaticClass();
}

FString UK2BeamNode_ApiRequest_PutServicesFederationTraffic::GetRequestSuccessDelegateName() const
{
	return TEXT("OnPutServicesFederationTrafficSuccess");
}

FString UK2BeamNode_ApiRequest_PutServicesFederationTraffic::GetRequestErrorDelegateName() const
{
	return TEXT("OnPutServicesFederationTrafficError");
}

FString UK2BeamNode_ApiRequest_PutServicesFederationTraffic::GetRequestCompleteDelegateName() const
{
	return TEXT("OnPutServicesFederationTrafficComplete");
}

#undef LOCTEXT_NAMESPACE
