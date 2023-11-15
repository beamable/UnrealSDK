

#include "BeamableCoreBlueprintNodes/Public/BeamFlow/ApiRequest/AutoGen/Stats/K2BeamNode_ApiRequest_DeleteClientSubscriptions.h"

#include "BeamK2.h"

#include "BeamableCore/Public/AutoGen/SubSystems/BeamStatsApi.h"
#include "BeamableCore/Public/AutoGen/SubSystems/Stats/DeleteClientSubscriptionsRequest.h"
#include "BeamableCore/Public/AutoGen/CommonResponse.h"

#define LOCTEXT_NAMESPACE "K2BeamNode_ApiRequest_DeleteClientSubscriptions"

using namespace BeamK2;

FName UK2BeamNode_ApiRequest_DeleteClientSubscriptions::GetSelfFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamStatsApi, GetSelf);
}

FName UK2BeamNode_ApiRequest_DeleteClientSubscriptions::GetRequestFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamStatsApi, DeleteClientSubscriptions);
}

FName UK2BeamNode_ApiRequest_DeleteClientSubscriptions::GetMakeFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UDeleteClientSubscriptionsRequest, Make);
}

FString UK2BeamNode_ApiRequest_DeleteClientSubscriptions::GetServiceName() const
{
	return TEXT("Stats");
}

FString UK2BeamNode_ApiRequest_DeleteClientSubscriptions::GetEndpointName() const
{
	return TEXT("DeleteClientSubscriptions");
}

UClass* UK2BeamNode_ApiRequest_DeleteClientSubscriptions::GetApiClass() const
{
	return UBeamStatsApi::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_DeleteClientSubscriptions::GetRequestClass() const
{
	return UDeleteClientSubscriptionsRequest::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_DeleteClientSubscriptions::GetResponseClass() const
{
	return UCommonResponse::StaticClass();
}

FString UK2BeamNode_ApiRequest_DeleteClientSubscriptions::GetRequestSuccessDelegateName() const
{
	return TEXT("OnDeleteClientSubscriptionsSuccess");
}

FString UK2BeamNode_ApiRequest_DeleteClientSubscriptions::GetRequestErrorDelegateName() const
{
	return TEXT("OnDeleteClientSubscriptionsError");
}

FString UK2BeamNode_ApiRequest_DeleteClientSubscriptions::GetRequestCompleteDelegateName() const
{
	return TEXT("OnDeleteClientSubscriptionsComplete");
}

#undef LOCTEXT_NAMESPACE
