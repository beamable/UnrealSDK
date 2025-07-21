

#include "BeamableCoreBlueprintNodes/Public/BeamFlow/ApiRequest/AutoGen/Beamo/K2BeamNode_ApiRequest_ApiBeamoGetStorageConnection.h"

#include "BeamK2.h"

#include "BeamableCore/Public/AutoGen/SubSystems/BeamBeamoApi.h"
#include "BeamableCore/Public/AutoGen/SubSystems/Beamo/ApiBeamoGetStorageConnectionRequest.h"
#include "BeamableCore/Public/AutoGen/BeamoV2ConnectionStringResponse.h"

#define LOCTEXT_NAMESPACE "K2BeamNode_ApiRequest_ApiBeamoGetStorageConnection"

using namespace BeamK2;

FName UK2BeamNode_ApiRequest_ApiBeamoGetStorageConnection::GetSelfFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamBeamoApi, GetSelf);
}

FName UK2BeamNode_ApiRequest_ApiBeamoGetStorageConnection::GetRequestFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamBeamoApi, ApiBeamoGetStorageConnection);
}

FName UK2BeamNode_ApiRequest_ApiBeamoGetStorageConnection::GetMakeFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UApiBeamoGetStorageConnectionRequest, Make);
}

FString UK2BeamNode_ApiRequest_ApiBeamoGetStorageConnection::GetServiceName() const
{
	return TEXT("Beamo");
}

FString UK2BeamNode_ApiRequest_ApiBeamoGetStorageConnection::GetEndpointName() const
{
	return TEXT("ApiBeamoGetStorageConnection");
}

UClass* UK2BeamNode_ApiRequest_ApiBeamoGetStorageConnection::GetApiClass() const
{
	return UBeamBeamoApi::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_ApiBeamoGetStorageConnection::GetRequestClass() const
{
	return UApiBeamoGetStorageConnectionRequest::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_ApiBeamoGetStorageConnection::GetResponseClass() const
{
	return UBeamoV2ConnectionStringResponse::StaticClass();
}

FString UK2BeamNode_ApiRequest_ApiBeamoGetStorageConnection::GetRequestSuccessDelegateName() const
{
	return TEXT("OnApiBeamoGetStorageConnectionSuccess");
}

FString UK2BeamNode_ApiRequest_ApiBeamoGetStorageConnection::GetRequestErrorDelegateName() const
{
	return TEXT("OnApiBeamoGetStorageConnectionError");
}

FString UK2BeamNode_ApiRequest_ApiBeamoGetStorageConnection::GetRequestCompleteDelegateName() const
{
	return TEXT("OnApiBeamoGetStorageConnectionComplete");
}

#undef LOCTEXT_NAMESPACE
