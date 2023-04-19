

#include "BeamableCoreBlueprintNodes/Public/BeamFlow/ApiRequest/AutoGen/Social/K2BeamNode_ApiRequest_DeleteFriends.h"

#include "BeamK2.h"

#include "BeamableCore/Public/AutoGen/SubSystems/BeamSocialApi.h"
#include "BeamableCore/Public/AutoGen/SubSystems/Social/DeleteFriendsRequest.h"
#include "BeamableCore/Public/AutoGen/EmptyResponse.h"

#define LOCTEXT_NAMESPACE "K2BeamNode_ApiRequest_DeleteFriends"

using namespace BeamK2;

FName UK2BeamNode_ApiRequest_DeleteFriends::GetSelfFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamSocialApi, GetSelf);
}

FName UK2BeamNode_ApiRequest_DeleteFriends::GetRequestFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamSocialApi, DeleteFriends);
}

FName UK2BeamNode_ApiRequest_DeleteFriends::GetMakeFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UDeleteFriendsRequest, Make);
}

FString UK2BeamNode_ApiRequest_DeleteFriends::GetServiceName() const
{
	return TEXT("Social");
}

FString UK2BeamNode_ApiRequest_DeleteFriends::GetEndpointName() const
{
	return TEXT("DeleteFriends");
}

UClass* UK2BeamNode_ApiRequest_DeleteFriends::GetApiClass() const
{
	return UBeamSocialApi::StaticClass();
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
