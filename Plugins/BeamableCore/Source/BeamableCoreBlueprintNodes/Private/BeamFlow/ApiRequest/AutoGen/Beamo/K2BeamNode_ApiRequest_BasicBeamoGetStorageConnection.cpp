

#include "BeamableCoreBlueprintNodes/Public/BeamFlow/ApiRequest/AutoGen/Beamo/K2BeamNode_ApiRequest_BasicBeamoGetStorageConnection.h"

#include "BeamK2.h"

#include "BeamableCore/Public/AutoGen/SubSystems/BeamBeamoApi.h"
#include "BeamableCore/Public/AutoGen/SubSystems/Beamo/BasicBeamoGetStorageConnectionRequest.h"
#include "BeamableCore/Public/AutoGen/ConnectionString.h"

#define LOCTEXT_NAMESPACE "K2BeamNode_ApiRequest_BasicBeamoGetStorageConnection"

using namespace BeamK2;

FName UK2BeamNode_ApiRequest_BasicBeamoGetStorageConnection::GetSelfFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamBeamoApi, GetSelf);
}

FName UK2BeamNode_ApiRequest_BasicBeamoGetStorageConnection::GetRequestFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamBeamoApi, BasicBeamoGetStorageConnection);
}

FName UK2BeamNode_ApiRequest_BasicBeamoGetStorageConnection::GetMakeFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBasicBeamoGetStorageConnectionRequest, Make);
}

FString UK2BeamNode_ApiRequest_BasicBeamoGetStorageConnection::GetServiceName() const
{
	return TEXT("Beamo");
}

FString UK2BeamNode_ApiRequest_BasicBeamoGetStorageConnection::GetEndpointName() const
{
	return TEXT("BasicBeamoGetStorageConnection");
}

UClass* UK2BeamNode_ApiRequest_BasicBeamoGetStorageConnection::GetApiClass() const
{
	return UBeamBeamoApi::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_BasicBeamoGetStorageConnection::GetRequestClass() const
{
	return UBasicBeamoGetStorageConnectionRequest::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_BasicBeamoGetStorageConnection::GetResponseClass() const
{
	return UConnectionString::StaticClass();
}

FString UK2BeamNode_ApiRequest_BasicBeamoGetStorageConnection::GetRequestSuccessDelegateName() const
{
	return TEXT("OnBasicBeamoGetStorageConnectionSuccess");
}

FString UK2BeamNode_ApiRequest_BasicBeamoGetStorageConnection::GetRequestErrorDelegateName() const
{
	return TEXT("OnBasicBeamoGetStorageConnectionError");
}

FString UK2BeamNode_ApiRequest_BasicBeamoGetStorageConnection::GetRequestCompleteDelegateName() const
{
	return TEXT("OnBasicBeamoGetStorageConnectionComplete");
}

#undef LOCTEXT_NAMESPACE
