

#include "BeamableCoreBlueprintNodes/Public/BeamFlow/ApiRequest/AutoGen/GroupUsers/K2BeamNode_ApiRequest_GetGroupUsers.h"

#include "BeamK2.h"

#include "BeamableCore/Public/AutoGen/SubSystems/BeamGroupUsersApi.h"
#include "BeamableCore/Public/AutoGen/SubSystems/GroupUsers/GetGroupUsersRequest.h"
#include "BeamableCore/Public/AutoGen/GroupUser.h"

#define LOCTEXT_NAMESPACE "K2BeamNode_ApiRequest_GetGroupUsers"

using namespace BeamK2;

FName UK2BeamNode_ApiRequest_GetGroupUsers::GetSelfFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamGroupUsersApi, GetSelf);
}

FName UK2BeamNode_ApiRequest_GetGroupUsers::GetRequestFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamGroupUsersApi, GetGroupUsers);
}

FName UK2BeamNode_ApiRequest_GetGroupUsers::GetMakeFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UGetGroupUsersRequest, Make);
}

FString UK2BeamNode_ApiRequest_GetGroupUsers::GetServiceName() const
{
	return TEXT("GroupUsers");
}

FString UK2BeamNode_ApiRequest_GetGroupUsers::GetEndpointName() const
{
	return TEXT("GetGroupUsers");
}

UClass* UK2BeamNode_ApiRequest_GetGroupUsers::GetApiClass() const
{
	return UBeamGroupUsersApi::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_GetGroupUsers::GetRequestClass() const
{
	return UGetGroupUsersRequest::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_GetGroupUsers::GetResponseClass() const
{
	return UGroupUser::StaticClass();
}

FString UK2BeamNode_ApiRequest_GetGroupUsers::GetRequestSuccessDelegateName() const
{
	return TEXT("OnGetGroupUsersSuccess");
}

FString UK2BeamNode_ApiRequest_GetGroupUsers::GetRequestErrorDelegateName() const
{
	return TEXT("OnGetGroupUsersError");
}

FString UK2BeamNode_ApiRequest_GetGroupUsers::GetRequestCompleteDelegateName() const
{
	return TEXT("OnGetGroupUsersComplete");
}

#undef LOCTEXT_NAMESPACE
