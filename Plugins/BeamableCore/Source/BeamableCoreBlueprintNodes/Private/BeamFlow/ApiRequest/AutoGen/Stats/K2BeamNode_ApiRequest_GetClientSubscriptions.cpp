

#include "BeamableCoreBlueprintNodes/Public/BeamFlow/ApiRequest/AutoGen/Stats/K2BeamNode_ApiRequest_GetClientSubscriptions.h"

#include "BeamK2.h"

#include "BeamableCore/Public/AutoGen/SubSystems/BeamStatsApi.h"
#include "BeamableCore/Public/AutoGen/SubSystems/Stats/GetClientSubscriptionsRequest.h"
#include "BeamableCore/Public/AutoGen/StatsClientSubscriptionsResponse.h"

#define LOCTEXT_NAMESPACE "K2BeamNode_ApiRequest_GetClientSubscriptions"

using namespace BeamK2;

FName UK2BeamNode_ApiRequest_GetClientSubscriptions::GetSelfFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamStatsApi, GetSelf);
}

FName UK2BeamNode_ApiRequest_GetClientSubscriptions::GetRequestFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamStatsApi, GetClientSubscriptions);
}

FName UK2BeamNode_ApiRequest_GetClientSubscriptions::GetMakeFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UGetClientSubscriptionsRequest, Make);
}

FString UK2BeamNode_ApiRequest_GetClientSubscriptions::GetServiceName() const
{
	return TEXT("Stats");
}

FString UK2BeamNode_ApiRequest_GetClientSubscriptions::GetEndpointName() const
{
	return TEXT("GetClientSubscriptions");
}

UClass* UK2BeamNode_ApiRequest_GetClientSubscriptions::GetApiClass() const
{
	return UBeamStatsApi::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_GetClientSubscriptions::GetRequestClass() const
{
	return UGetClientSubscriptionsRequest::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_GetClientSubscriptions::GetResponseClass() const
{
	return UStatsClientSubscriptionsResponse::StaticClass();
}

FString UK2BeamNode_ApiRequest_GetClientSubscriptions::GetRequestSuccessDelegateName() const
{
	return TEXT("OnGetClientSubscriptionsSuccess");
}

FString UK2BeamNode_ApiRequest_GetClientSubscriptions::GetRequestErrorDelegateName() const
{
	return TEXT("OnGetClientSubscriptionsError");
}

FString UK2BeamNode_ApiRequest_GetClientSubscriptions::GetRequestCompleteDelegateName() const
{
	return TEXT("OnGetClientSubscriptionsComplete");
}

#undef LOCTEXT_NAMESPACE
