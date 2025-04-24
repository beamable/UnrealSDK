

#include "BeamableCoreBlueprintNodes/Public/BeamFlow/ApiRequest/AutoGen/Friends/K2BeamNode_ApiRequest_BasicFriendsGetFriends.h"

#include "BeamK2.h"

#include "BeamableCore/Public/AutoGen/SubSystems/BeamFriendsApi.h"
#include "BeamableCore/Public/AutoGen/SubSystems/Friends/BasicFriendsGetFriendsRequest.h"
#include "BeamableCore/Public/AutoGen/GetSocialStatusesResponse.h"

#define LOCTEXT_NAMESPACE "K2BeamNode_ApiRequest_BasicFriendsGetFriends"

using namespace BeamK2;

FName UK2BeamNode_ApiRequest_BasicFriendsGetFriends::GetSelfFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamFriendsApi, GetSelf);
}

FName UK2BeamNode_ApiRequest_BasicFriendsGetFriends::GetRequestFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamFriendsApi, GetFriends);
}

FName UK2BeamNode_ApiRequest_BasicFriendsGetFriends::GetMakeFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBasicFriendsGetFriendsRequest, Make);
}

FString UK2BeamNode_ApiRequest_BasicFriendsGetFriends::GetServiceName() const
{
	return TEXT("Friends");
}

FString UK2BeamNode_ApiRequest_BasicFriendsGetFriends::GetEndpointName() const
{
	return TEXT("GetFriends");
}

UClass* UK2BeamNode_ApiRequest_BasicFriendsGetFriends::GetApiClass() const
{
	return UBeamFriendsApi::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_BasicFriendsGetFriends::GetRequestClass() const
{
	return UBasicFriendsGetFriendsRequest::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_BasicFriendsGetFriends::GetResponseClass() const
{
	return UGetSocialStatusesResponse::StaticClass();
}

FString UK2BeamNode_ApiRequest_BasicFriendsGetFriends::GetRequestSuccessDelegateName() const
{
	return TEXT("OnBasicFriendsGetFriendsSuccess");
}

FString UK2BeamNode_ApiRequest_BasicFriendsGetFriends::GetRequestErrorDelegateName() const
{
	return TEXT("OnBasicFriendsGetFriendsError");
}

FString UK2BeamNode_ApiRequest_BasicFriendsGetFriends::GetRequestCompleteDelegateName() const
{
	return TEXT("OnBasicFriendsGetFriendsComplete");
}

#undef LOCTEXT_NAMESPACE
