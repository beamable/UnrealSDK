

#include "BeamableCoreBlueprintNodes/Public/BeamFlow/ApiRequest/AutoGen/GroupUsers/K2BeamNode_ApiRequest_DeleteJoin.h"

#include "BeamK2.h"

#include "BeamableCore/Public/AutoGen/SubSystems/BeamGroupUsersApi.h"
#include "BeamableCore/Public/AutoGen/SubSystems/GroupUsers/DeleteJoinRequest.h"
#include "BeamableCore/Public/AutoGen/GroupMembershipResponse.h"

#define LOCTEXT_NAMESPACE "K2BeamNode_ApiRequest_DeleteJoin"

using namespace BeamK2;

FName UK2BeamNode_ApiRequest_DeleteJoin::GetSelfFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamGroupUsersApi, GetSelf);
}

FName UK2BeamNode_ApiRequest_DeleteJoin::GetRequestFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamGroupUsersApi, DeleteJoin);
}

FName UK2BeamNode_ApiRequest_DeleteJoin::GetMakeFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UDeleteJoinRequest, Make);
}

FString UK2BeamNode_ApiRequest_DeleteJoin::GetServiceName() const
{
	return TEXT("GroupUsers");
}

FString UK2BeamNode_ApiRequest_DeleteJoin::GetEndpointName() const
{
	return TEXT("DeleteJoin");
}

UClass* UK2BeamNode_ApiRequest_DeleteJoin::GetApiClass() const
{
	return UBeamGroupUsersApi::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_DeleteJoin::GetRequestClass() const
{
	return UDeleteJoinRequest::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_DeleteJoin::GetResponseClass() const
{
	return UGroupMembershipResponse::StaticClass();
}

FString UK2BeamNode_ApiRequest_DeleteJoin::GetRequestSuccessDelegateName() const
{
	return TEXT("OnDeleteJoinSuccess");
}

FString UK2BeamNode_ApiRequest_DeleteJoin::GetRequestErrorDelegateName() const
{
	return TEXT("OnDeleteJoinError");
}

FString UK2BeamNode_ApiRequest_DeleteJoin::GetRequestCompleteDelegateName() const
{
	return TEXT("OnDeleteJoinComplete");
}

#undef LOCTEXT_NAMESPACE
