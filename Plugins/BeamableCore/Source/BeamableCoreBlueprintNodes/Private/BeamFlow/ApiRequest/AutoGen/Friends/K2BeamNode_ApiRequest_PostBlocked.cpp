

#include "BeamableCoreBlueprintNodes/Public/BeamFlow/ApiRequest/AutoGen/Friends/K2BeamNode_ApiRequest_PostBlocked.h"

#include "BeamK2.h"

#include "BeamableCore/Public/AutoGen/SubSystems/BeamFriendsApi.h"
#include "BeamableCore/Public/AutoGen/SubSystems/Friends/PostBlockedRequest.h"
#include "BeamableCore/Public/AutoGen/FriendshipStatus.h"

#define LOCTEXT_NAMESPACE "K2BeamNode_ApiRequest_PostBlocked"

using namespace BeamK2;

FName UK2BeamNode_ApiRequest_PostBlocked::GetSelfFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamFriendsApi, GetSelf);
}

FName UK2BeamNode_ApiRequest_PostBlocked::GetRequestFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamFriendsApi, PostBlocked);
}

FName UK2BeamNode_ApiRequest_PostBlocked::GetMakeFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UPostBlockedRequest, Make);
}

FString UK2BeamNode_ApiRequest_PostBlocked::GetServiceName() const
{
	return TEXT("Friends");
}

FString UK2BeamNode_ApiRequest_PostBlocked::GetEndpointName() const
{
	return TEXT("PostBlocked");
}

UClass* UK2BeamNode_ApiRequest_PostBlocked::GetApiClass() const
{
	return UBeamFriendsApi::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_PostBlocked::GetRequestClass() const
{
	return UPostBlockedRequest::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_PostBlocked::GetResponseClass() const
{
	return UFriendshipStatus::StaticClass();
}

FString UK2BeamNode_ApiRequest_PostBlocked::GetRequestSuccessDelegateName() const
{
	return TEXT("OnPostBlockedSuccess");
}

FString UK2BeamNode_ApiRequest_PostBlocked::GetRequestErrorDelegateName() const
{
	return TEXT("OnPostBlockedError");
}

FString UK2BeamNode_ApiRequest_PostBlocked::GetRequestCompleteDelegateName() const
{
	return TEXT("OnPostBlockedComplete");
}

#undef LOCTEXT_NAMESPACE
