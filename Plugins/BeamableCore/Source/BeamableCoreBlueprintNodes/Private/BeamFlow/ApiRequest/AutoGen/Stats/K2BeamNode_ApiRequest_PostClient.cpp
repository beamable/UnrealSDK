

#include "BeamableCoreBlueprintNodes/Public/BeamFlow/ApiRequest/AutoGen/Stats/K2BeamNode_ApiRequest_PostClient.h"

#include "BeamK2.h"

#include "BeamableCore/Public/AutoGen/SubSystems/BeamStatsApi.h"
#include "BeamableCore/Public/AutoGen/SubSystems/Stats/PostClientRequest.h"
#include "BeamableCore/Public/AutoGen/EmptyResponse.h"

#define LOCTEXT_NAMESPACE "K2BeamNode_ApiRequest_PostClient"

using namespace BeamK2;

FName UK2BeamNode_ApiRequest_PostClient::GetSelfFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamStatsApi, GetSelf);
}

FName UK2BeamNode_ApiRequest_PostClient::GetRequestFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamStatsApi, PostClient);
}

FName UK2BeamNode_ApiRequest_PostClient::GetMakeFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UPostClientRequest, Make);
}

FString UK2BeamNode_ApiRequest_PostClient::GetServiceName() const
{
	return TEXT("Stats");
}

FString UK2BeamNode_ApiRequest_PostClient::GetEndpointName() const
{
	return TEXT("PostClient");
}

UClass* UK2BeamNode_ApiRequest_PostClient::GetApiClass() const
{
	return UBeamStatsApi::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_PostClient::GetRequestClass() const
{
	return UPostClientRequest::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_PostClient::GetResponseClass() const
{
	return UEmptyResponse::StaticClass();
}

FString UK2BeamNode_ApiRequest_PostClient::GetRequestSuccessDelegateName() const
{
	return TEXT("OnPostClientSuccess");
}

FString UK2BeamNode_ApiRequest_PostClient::GetRequestErrorDelegateName() const
{
	return TEXT("OnPostClientError");
}

FString UK2BeamNode_ApiRequest_PostClient::GetRequestCompleteDelegateName() const
{
	return TEXT("OnPostClientComplete");
}

#undef LOCTEXT_NAMESPACE
