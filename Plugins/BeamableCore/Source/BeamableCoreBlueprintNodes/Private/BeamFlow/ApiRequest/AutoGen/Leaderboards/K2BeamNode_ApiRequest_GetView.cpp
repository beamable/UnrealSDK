

#include "BeamableCoreBlueprintNodes/Public/BeamFlow/ApiRequest/AutoGen/Leaderboards/K2BeamNode_ApiRequest_GetView.h"

#include "BeamK2.h"

#include "BeamableCore/Public/AutoGen/SubSystems/BeamLeaderboardsApi.h"
#include "BeamableCore/Public/AutoGen/SubSystems/Leaderboards/GetViewRequest.h"
#include "BeamableCore/Public/AutoGen/LeaderBoardViewResponse.h"

#define LOCTEXT_NAMESPACE "K2BeamNode_ApiRequest_GetView"

using namespace BeamK2;

FName UK2BeamNode_ApiRequest_GetView::GetSelfFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamLeaderboardsApi, GetSelf);
}

FName UK2BeamNode_ApiRequest_GetView::GetRequestFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamLeaderboardsApi, GetView);
}

FName UK2BeamNode_ApiRequest_GetView::GetMakeFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UGetViewRequest, Make);
}

FString UK2BeamNode_ApiRequest_GetView::GetServiceName() const
{
	return TEXT("Leaderboards");
}

FString UK2BeamNode_ApiRequest_GetView::GetEndpointName() const
{
	return TEXT("GetView");
}

UClass* UK2BeamNode_ApiRequest_GetView::GetApiClass() const
{
	return UBeamLeaderboardsApi::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_GetView::GetRequestClass() const
{
	return UGetViewRequest::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_GetView::GetResponseClass() const
{
	return ULeaderBoardViewResponse::StaticClass();
}

FString UK2BeamNode_ApiRequest_GetView::GetRequestSuccessDelegateName() const
{
	return TEXT("OnGetViewSuccess");
}

FString UK2BeamNode_ApiRequest_GetView::GetRequestErrorDelegateName() const
{
	return TEXT("OnGetViewError");
}

FString UK2BeamNode_ApiRequest_GetView::GetRequestCompleteDelegateName() const
{
	return TEXT("OnGetViewComplete");
}

#undef LOCTEXT_NAMESPACE
