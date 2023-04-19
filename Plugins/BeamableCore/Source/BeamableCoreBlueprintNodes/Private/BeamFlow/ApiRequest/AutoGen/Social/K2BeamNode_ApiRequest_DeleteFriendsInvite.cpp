

#include "BeamableCoreBlueprintNodes/Public/BeamFlow/ApiRequest/AutoGen/Social/K2BeamNode_ApiRequest_DeleteFriendsInvite.h"

#include "BeamK2.h"

#include "BeamableCore/Public/AutoGen/SubSystems/BeamSocialApi.h"
#include "BeamableCore/Public/AutoGen/SubSystems/Social/DeleteFriendsInviteRequest.h"
#include "BeamableCore/Public/AutoGen/EmptyResponse.h"

#define LOCTEXT_NAMESPACE "K2BeamNode_ApiRequest_DeleteFriendsInvite"

using namespace BeamK2;

FName UK2BeamNode_ApiRequest_DeleteFriendsInvite::GetSelfFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamSocialApi, GetSelf);
}

FName UK2BeamNode_ApiRequest_DeleteFriendsInvite::GetRequestFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamSocialApi, DeleteFriendsInvite);
}

FName UK2BeamNode_ApiRequest_DeleteFriendsInvite::GetMakeFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UDeleteFriendsInviteRequest, Make);
}

FString UK2BeamNode_ApiRequest_DeleteFriendsInvite::GetServiceName() const
{
	return TEXT("Social");
}

FString UK2BeamNode_ApiRequest_DeleteFriendsInvite::GetEndpointName() const
{
	return TEXT("DeleteFriendsInvite");
}

UClass* UK2BeamNode_ApiRequest_DeleteFriendsInvite::GetApiClass() const
{
	return UBeamSocialApi::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_DeleteFriendsInvite::GetRequestClass() const
{
	return UDeleteFriendsInviteRequest::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_DeleteFriendsInvite::GetResponseClass() const
{
	return UEmptyResponse::StaticClass();
}

FString UK2BeamNode_ApiRequest_DeleteFriendsInvite::GetRequestSuccessDelegateName() const
{
	return TEXT("OnDeleteFriendsInviteSuccess");
}

FString UK2BeamNode_ApiRequest_DeleteFriendsInvite::GetRequestErrorDelegateName() const
{
	return TEXT("OnDeleteFriendsInviteError");
}

FString UK2BeamNode_ApiRequest_DeleteFriendsInvite::GetRequestCompleteDelegateName() const
{
	return TEXT("OnDeleteFriendsInviteComplete");
}

#undef LOCTEXT_NAMESPACE
