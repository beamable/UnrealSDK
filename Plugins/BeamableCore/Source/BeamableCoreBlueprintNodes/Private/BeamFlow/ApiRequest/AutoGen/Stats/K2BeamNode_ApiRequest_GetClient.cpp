

#include "BeamableCoreBlueprintNodes/Public/BeamFlow/ApiRequest/AutoGen/Stats/K2BeamNode_ApiRequest_GetClient.h"

#include "BeamK2.h"

#include "BeamableCore/Public/AutoGen/SubSystems/BeamStatsApi.h"
#include "BeamableCore/Public/AutoGen/SubSystems/Stats/GetClientRequest.h"
#include "BeamableCore/Public/AutoGen/StatsResponse.h"

#define LOCTEXT_NAMESPACE "K2BeamNode_ApiRequest_GetClient"

using namespace BeamK2;

FName UK2BeamNode_ApiRequest_GetClient::GetSelfFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamStatsApi, GetSelf);
}

FName UK2BeamNode_ApiRequest_GetClient::GetRequestFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamStatsApi, GetClient);
}

FName UK2BeamNode_ApiRequest_GetClient::GetMakeFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UGetClientRequest, Make);
}

FString UK2BeamNode_ApiRequest_GetClient::GetServiceName() const
{
	return TEXT("Stats");
}

FString UK2BeamNode_ApiRequest_GetClient::GetEndpointName() const
{
	return TEXT("GetClient");
}

UClass* UK2BeamNode_ApiRequest_GetClient::GetApiClass() const
{
	return UBeamStatsApi::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_GetClient::GetRequestClass() const
{
	return UGetClientRequest::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_GetClient::GetResponseClass() const
{
	return UStatsResponse::StaticClass();
}

FString UK2BeamNode_ApiRequest_GetClient::GetRequestSuccessDelegateName() const
{
	return TEXT("OnGetClientSuccess");
}

FString UK2BeamNode_ApiRequest_GetClient::GetRequestErrorDelegateName() const
{
	return TEXT("OnGetClientError");
}

FString UK2BeamNode_ApiRequest_GetClient::GetRequestCompleteDelegateName() const
{
	return TEXT("OnGetClientComplete");
}

#undef LOCTEXT_NAMESPACE
