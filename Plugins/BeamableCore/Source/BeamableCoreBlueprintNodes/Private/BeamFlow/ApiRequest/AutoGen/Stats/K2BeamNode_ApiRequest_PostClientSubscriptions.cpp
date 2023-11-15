

#include "BeamableCoreBlueprintNodes/Public/BeamFlow/ApiRequest/AutoGen/Stats/K2BeamNode_ApiRequest_PostClientSubscriptions.h"

#include "BeamK2.h"

#include "BeamableCore/Public/AutoGen/SubSystems/BeamStatsApi.h"
#include "BeamableCore/Public/AutoGen/SubSystems/Stats/PostClientSubscriptionsRequest.h"
#include "BeamableCore/Public/AutoGen/CommonResponse.h"

#define LOCTEXT_NAMESPACE "K2BeamNode_ApiRequest_PostClientSubscriptions"

using namespace BeamK2;

FName UK2BeamNode_ApiRequest_PostClientSubscriptions::GetSelfFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamStatsApi, GetSelf);
}

FName UK2BeamNode_ApiRequest_PostClientSubscriptions::GetRequestFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamStatsApi, PostClientSubscriptions);
}

FName UK2BeamNode_ApiRequest_PostClientSubscriptions::GetMakeFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UPostClientSubscriptionsRequest, Make);
}

FString UK2BeamNode_ApiRequest_PostClientSubscriptions::GetServiceName() const
{
	return TEXT("Stats");
}

FString UK2BeamNode_ApiRequest_PostClientSubscriptions::GetEndpointName() const
{
	return TEXT("PostClientSubscriptions");
}

UClass* UK2BeamNode_ApiRequest_PostClientSubscriptions::GetApiClass() const
{
	return UBeamStatsApi::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_PostClientSubscriptions::GetRequestClass() const
{
	return UPostClientSubscriptionsRequest::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_PostClientSubscriptions::GetResponseClass() const
{
	return UCommonResponse::StaticClass();
}

FString UK2BeamNode_ApiRequest_PostClientSubscriptions::GetRequestSuccessDelegateName() const
{
	return TEXT("OnPostClientSubscriptionsSuccess");
}

FString UK2BeamNode_ApiRequest_PostClientSubscriptions::GetRequestErrorDelegateName() const
{
	return TEXT("OnPostClientSubscriptionsError");
}

FString UK2BeamNode_ApiRequest_PostClientSubscriptions::GetRequestCompleteDelegateName() const
{
	return TEXT("OnPostClientSubscriptionsComplete");
}

#undef LOCTEXT_NAMESPACE
