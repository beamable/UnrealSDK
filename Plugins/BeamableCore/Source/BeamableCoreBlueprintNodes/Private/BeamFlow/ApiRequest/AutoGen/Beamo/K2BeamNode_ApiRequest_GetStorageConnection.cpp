

#include "BeamableCoreBlueprintNodes/Public/BeamFlow/ApiRequest/AutoGen/Beamo/K2BeamNode_ApiRequest_GetStorageConnection.h"

#include "BeamK2.h"

#include "BeamableCore/Public/AutoGen/SubSystems/BeamBeamoApi.h"
#include "BeamableCore/Public/AutoGen/SubSystems/Beamo/GetStorageConnectionRequest.h"
#include "BeamableCore/Public/AutoGen/ConnectionString.h"

#define LOCTEXT_NAMESPACE "K2BeamNode_ApiRequest_GetStorageConnection"

using namespace BeamK2;

FName UK2BeamNode_ApiRequest_GetStorageConnection::GetSelfFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamBeamoApi, GetSelf);
}

FName UK2BeamNode_ApiRequest_GetStorageConnection::GetRequestFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamBeamoApi, GetStorageConnection);
}

FName UK2BeamNode_ApiRequest_GetStorageConnection::GetMakeFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UGetStorageConnectionRequest, Make);
}

FString UK2BeamNode_ApiRequest_GetStorageConnection::GetServiceName() const
{
	return TEXT("Beamo");
}

FString UK2BeamNode_ApiRequest_GetStorageConnection::GetEndpointName() const
{
	return TEXT("GetStorageConnection");
}

UClass* UK2BeamNode_ApiRequest_GetStorageConnection::GetApiClass() const
{
	return UBeamBeamoApi::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_GetStorageConnection::GetRequestClass() const
{
	return UGetStorageConnectionRequest::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_GetStorageConnection::GetResponseClass() const
{
	return UConnectionString::StaticClass();
}

FString UK2BeamNode_ApiRequest_GetStorageConnection::GetRequestSuccessDelegateName() const
{
	return TEXT("OnGetStorageConnectionSuccess");
}

FString UK2BeamNode_ApiRequest_GetStorageConnection::GetRequestErrorDelegateName() const
{
	return TEXT("OnGetStorageConnectionError");
}

FString UK2BeamNode_ApiRequest_GetStorageConnection::GetRequestCompleteDelegateName() const
{
	return TEXT("OnGetStorageConnectionComplete");
}

#undef LOCTEXT_NAMESPACE
