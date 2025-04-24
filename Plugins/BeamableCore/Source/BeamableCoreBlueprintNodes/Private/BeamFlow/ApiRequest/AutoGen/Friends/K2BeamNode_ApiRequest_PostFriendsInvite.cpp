

#include "BeamableCoreBlueprintNodes/Public/BeamFlow/ApiRequest/AutoGen/Friends/K2BeamNode_ApiRequest_PostFriendsInvite.h"

#include "BeamK2.h"

#include "BeamableCore/Public/AutoGen/SubSystems/BeamFriendsApi.h"
#include "BeamableCore/Public/AutoGen/SubSystems/Friends/PostFriendsInviteRequest.h"
#include "BeamableCore/Public/AutoGen/EmptyResponse.h"

#define LOCTEXT_NAMESPACE "K2BeamNode_ApiRequest_PostFriendsInvite"

using namespace BeamK2;

FName UK2BeamNode_ApiRequest_PostFriendsInvite::GetSelfFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamFriendsApi, GetSelf);
}

FName UK2BeamNode_ApiRequest_PostFriendsInvite::GetRequestFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamFriendsApi, PostFriendsInvite);
}

FName UK2BeamNode_ApiRequest_PostFriendsInvite::GetMakeFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UPostFriendsInviteRequest, Make);
}

FString UK2BeamNode_ApiRequest_PostFriendsInvite::GetServiceName() const
{
	return TEXT("Friends");
}

FString UK2BeamNode_ApiRequest_PostFriendsInvite::GetEndpointName() const
{
	return TEXT("PostFriendsInvite");
}

UClass* UK2BeamNode_ApiRequest_PostFriendsInvite::GetApiClass() const
{
	return UBeamFriendsApi::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_PostFriendsInvite::GetRequestClass() const
{
	return UPostFriendsInviteRequest::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_PostFriendsInvite::GetResponseClass() const
{
	return UEmptyResponse::StaticClass();
}

FString UK2BeamNode_ApiRequest_PostFriendsInvite::GetRequestSuccessDelegateName() const
{
	return TEXT("OnPostFriendsInviteSuccess");
}

FString UK2BeamNode_ApiRequest_PostFriendsInvite::GetRequestErrorDelegateName() const
{
	return TEXT("OnPostFriendsInviteError");
}

FString UK2BeamNode_ApiRequest_PostFriendsInvite::GetRequestCompleteDelegateName() const
{
	return TEXT("OnPostFriendsInviteComplete");
}

#undef LOCTEXT_NAMESPACE
