

#include "BeamableCoreBlueprintNodes/Public/BeamFlow/ApiRequest/AutoGen/Friends/K2BeamNode_ApiRequest_DeleteFriends.h"

#include "BeamK2.h"

#include "BeamableCore/Public/AutoGen/SubSystems/BeamFriendsApi.h"
#include "BeamableCore/Public/AutoGen/SubSystems/Friends/DeleteFriendsRequest.h"
#include "BeamableCore/Public/AutoGen/EmptyResponse.h"

#define LOCTEXT_NAMESPACE "K2BeamNode_ApiRequest_DeleteFriends"

using namespace BeamK2;

FName UK2BeamNode_ApiRequest_DeleteFriends::GetSelfFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamFriendsApi, GetSelf);
}

FName UK2BeamNode_ApiRequest_DeleteFriends::GetRequestFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamFriendsApi, DeleteFriends);
}

FName UK2BeamNode_ApiRequest_DeleteFriends::GetMakeFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UDeleteFriendsRequest, Make);
}

FString UK2BeamNode_ApiRequest_DeleteFriends::GetServiceName() const
{
	return TEXT("Friends");
}

FString UK2BeamNode_ApiRequest_DeleteFriends::GetEndpointName() const
{
	return TEXT("DeleteFriends");
}

UClass* UK2BeamNode_ApiRequest_DeleteFriends::GetApiClass() const
{
	return UBeamFriendsApi::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_DeleteFriends::GetRequestClass() const
{
	return UDeleteFriendsRequest::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_DeleteFriends::GetResponseClass() const
{
	return UEmptyResponse::StaticClass();
}

FString UK2BeamNode_ApiRequest_DeleteFriends::GetRequestSuccessDelegateName() const
{
	return TEXT("OnDeleteFriendsSuccess");
}

FString UK2BeamNode_ApiRequest_DeleteFriends::GetRequestErrorDelegateName() const
{
	return TEXT("OnDeleteFriendsError");
}

FString UK2BeamNode_ApiRequest_DeleteFriends::GetRequestCompleteDelegateName() const
{
	return TEXT("OnDeleteFriendsComplete");
}

#undef LOCTEXT_NAMESPACE
