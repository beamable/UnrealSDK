

#include "BeamableCoreBlueprintNodes/Public/BeamFlow/ApiRequest/AutoGen/GroupUsers/K2BeamNode_ApiRequest_PostJoin.h"

#include "BeamK2.h"

#include "BeamableCore/Public/AutoGen/SubSystems/BeamGroupUsersApi.h"
#include "BeamableCore/Public/AutoGen/SubSystems/GroupUsers/PostJoinRequest.h"
#include "BeamableCore/Public/AutoGen/GroupMembershipResponse.h"

#define LOCTEXT_NAMESPACE "K2BeamNode_ApiRequest_PostJoin"

using namespace BeamK2;

FName UK2BeamNode_ApiRequest_PostJoin::GetSelfFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamGroupUsersApi, GetSelf);
}

FName UK2BeamNode_ApiRequest_PostJoin::GetRequestFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamGroupUsersApi, PostJoin);
}

FName UK2BeamNode_ApiRequest_PostJoin::GetMakeFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UPostJoinRequest, Make);
}

FString UK2BeamNode_ApiRequest_PostJoin::GetServiceName() const
{
	return TEXT("GroupUsers");
}

FString UK2BeamNode_ApiRequest_PostJoin::GetEndpointName() const
{
	return TEXT("PostJoin");
}

UClass* UK2BeamNode_ApiRequest_PostJoin::GetApiClass() const
{
	return UBeamGroupUsersApi::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_PostJoin::GetRequestClass() const
{
	return UPostJoinRequest::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_PostJoin::GetResponseClass() const
{
	return UGroupMembershipResponse::StaticClass();
}

FString UK2BeamNode_ApiRequest_PostJoin::GetRequestSuccessDelegateName() const
{
	return TEXT("OnPostJoinSuccess");
}

FString UK2BeamNode_ApiRequest_PostJoin::GetRequestErrorDelegateName() const
{
	return TEXT("OnPostJoinError");
}

FString UK2BeamNode_ApiRequest_PostJoin::GetRequestCompleteDelegateName() const
{
	return TEXT("OnPostJoinComplete");
}

#undef LOCTEXT_NAMESPACE
