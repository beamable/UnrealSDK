

#include "BeamableCoreBlueprintNodes/Public/BeamFlow/ApiRequest/AutoGen/Beamo/K2BeamNode_ApiRequest_DeleteServicesFederationTraffic.h"

#include "BeamK2.h"

#include "BeamableCore/Public/AutoGen/SubSystems/BeamBeamoApi.h"
#include "BeamableCore/Public/AutoGen/SubSystems/Beamo/DeleteServicesFederationTrafficRequest.h"
#include "BeamableCore/Public/AutoGen/BeamoV2EmptyMessage.h"

#define LOCTEXT_NAMESPACE "K2BeamNode_ApiRequest_DeleteServicesFederationTraffic"

using namespace BeamK2;

FName UK2BeamNode_ApiRequest_DeleteServicesFederationTraffic::GetSelfFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamBeamoApi, GetSelf);
}

FName UK2BeamNode_ApiRequest_DeleteServicesFederationTraffic::GetRequestFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamBeamoApi, DeleteServicesFederationTraffic);
}

FName UK2BeamNode_ApiRequest_DeleteServicesFederationTraffic::GetMakeFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UDeleteServicesFederationTrafficRequest, Make);
}

FString UK2BeamNode_ApiRequest_DeleteServicesFederationTraffic::GetServiceName() const
{
	return TEXT("Beamo");
}

FString UK2BeamNode_ApiRequest_DeleteServicesFederationTraffic::GetEndpointName() const
{
	return TEXT("DeleteServicesFederationTraffic");
}

UClass* UK2BeamNode_ApiRequest_DeleteServicesFederationTraffic::GetApiClass() const
{
	return UBeamBeamoApi::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_DeleteServicesFederationTraffic::GetRequestClass() const
{
	return UDeleteServicesFederationTrafficRequest::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_DeleteServicesFederationTraffic::GetResponseClass() const
{
	return UBeamoV2EmptyMessage::StaticClass();
}

FString UK2BeamNode_ApiRequest_DeleteServicesFederationTraffic::GetRequestSuccessDelegateName() const
{
	return TEXT("OnDeleteServicesFederationTrafficSuccess");
}

FString UK2BeamNode_ApiRequest_DeleteServicesFederationTraffic::GetRequestErrorDelegateName() const
{
	return TEXT("OnDeleteServicesFederationTrafficError");
}

FString UK2BeamNode_ApiRequest_DeleteServicesFederationTraffic::GetRequestCompleteDelegateName() const
{
	return TEXT("OnDeleteServicesFederationTrafficComplete");
}

#undef LOCTEXT_NAMESPACE
