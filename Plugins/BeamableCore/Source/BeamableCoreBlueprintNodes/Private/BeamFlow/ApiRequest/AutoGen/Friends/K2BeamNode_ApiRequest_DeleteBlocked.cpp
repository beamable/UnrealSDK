

#include "BeamableCoreBlueprintNodes/Public/BeamFlow/ApiRequest/AutoGen/Friends/K2BeamNode_ApiRequest_DeleteBlocked.h"

#include "BeamK2.h"

#include "BeamableCore/Public/AutoGen/SubSystems/BeamFriendsApi.h"
#include "BeamableCore/Public/AutoGen/SubSystems/Friends/DeleteBlockedRequest.h"
#include "BeamableCore/Public/AutoGen/FriendshipStatus.h"

#define LOCTEXT_NAMESPACE "K2BeamNode_ApiRequest_DeleteBlocked"

using namespace BeamK2;

FName UK2BeamNode_ApiRequest_DeleteBlocked::GetSelfFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamFriendsApi, GetSelf);
}

FName UK2BeamNode_ApiRequest_DeleteBlocked::GetRequestFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamFriendsApi, DeleteBlocked);
}

FName UK2BeamNode_ApiRequest_DeleteBlocked::GetMakeFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UDeleteBlockedRequest, Make);
}

FString UK2BeamNode_ApiRequest_DeleteBlocked::GetServiceName() const
{
	return TEXT("Friends");
}

FString UK2BeamNode_ApiRequest_DeleteBlocked::GetEndpointName() const
{
	return TEXT("DeleteBlocked");
}

UClass* UK2BeamNode_ApiRequest_DeleteBlocked::GetApiClass() const
{
	return UBeamFriendsApi::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_DeleteBlocked::GetRequestClass() const
{
	return UDeleteBlockedRequest::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_DeleteBlocked::GetResponseClass() const
{
	return UFriendshipStatus::StaticClass();
}

FString UK2BeamNode_ApiRequest_DeleteBlocked::GetRequestSuccessDelegateName() const
{
	return TEXT("OnDeleteBlockedSuccess");
}

FString UK2BeamNode_ApiRequest_DeleteBlocked::GetRequestErrorDelegateName() const
{
	return TEXT("OnDeleteBlockedError");
}

FString UK2BeamNode_ApiRequest_DeleteBlocked::GetRequestCompleteDelegateName() const
{
	return TEXT("OnDeleteBlockedComplete");
}

#undef LOCTEXT_NAMESPACE
