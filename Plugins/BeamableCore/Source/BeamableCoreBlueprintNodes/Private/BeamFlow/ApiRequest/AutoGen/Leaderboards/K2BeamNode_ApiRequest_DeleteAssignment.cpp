

#include "BeamableCoreBlueprintNodes/Public/BeamFlow/ApiRequest/AutoGen/Leaderboards/K2BeamNode_ApiRequest_DeleteAssignment.h"

#include "BeamK2.h"

#include "BeamableCore/Public/AutoGen/SubSystems/BeamLeaderboardsApi.h"
#include "BeamableCore/Public/AutoGen/SubSystems/Leaderboards/DeleteAssignmentRequest.h"
#include "BeamableCore/Public/AutoGen/CommonResponse.h"

#define LOCTEXT_NAMESPACE "K2BeamNode_ApiRequest_DeleteAssignment"

using namespace BeamK2;

FName UK2BeamNode_ApiRequest_DeleteAssignment::GetSelfFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamLeaderboardsApi, GetSelf);
}

FName UK2BeamNode_ApiRequest_DeleteAssignment::GetRequestFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamLeaderboardsApi, DeleteAssignment);
}

FName UK2BeamNode_ApiRequest_DeleteAssignment::GetMakeFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UDeleteAssignmentRequest, Make);
}

FString UK2BeamNode_ApiRequest_DeleteAssignment::GetServiceName() const
{
	return TEXT("Leaderboards");
}

FString UK2BeamNode_ApiRequest_DeleteAssignment::GetEndpointName() const
{
	return TEXT("DeleteAssignment");
}

UClass* UK2BeamNode_ApiRequest_DeleteAssignment::GetApiClass() const
{
	return UBeamLeaderboardsApi::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_DeleteAssignment::GetRequestClass() const
{
	return UDeleteAssignmentRequest::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_DeleteAssignment::GetResponseClass() const
{
	return UCommonResponse::StaticClass();
}

FString UK2BeamNode_ApiRequest_DeleteAssignment::GetRequestSuccessDelegateName() const
{
	return TEXT("OnDeleteAssignmentSuccess");
}

FString UK2BeamNode_ApiRequest_DeleteAssignment::GetRequestErrorDelegateName() const
{
	return TEXT("OnDeleteAssignmentError");
}

FString UK2BeamNode_ApiRequest_DeleteAssignment::GetRequestCompleteDelegateName() const
{
	return TEXT("OnDeleteAssignmentComplete");
}

#undef LOCTEXT_NAMESPACE
