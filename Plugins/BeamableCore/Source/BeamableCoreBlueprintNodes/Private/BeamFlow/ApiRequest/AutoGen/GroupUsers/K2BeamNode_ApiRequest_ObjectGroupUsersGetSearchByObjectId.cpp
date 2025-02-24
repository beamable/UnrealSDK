

#include "BeamableCoreBlueprintNodes/Public/BeamFlow/ApiRequest/AutoGen/GroupUsers/K2BeamNode_ApiRequest_ObjectGroupUsersGetSearchByObjectId.h"

#include "BeamK2.h"

#include "BeamableCore/Public/AutoGen/SubSystems/BeamGroupUsersApi.h"
#include "BeamableCore/Public/AutoGen/SubSystems/GroupUsers/ObjectGroupUsersGetSearchByObjectIdRequest.h"
#include "BeamableCore/Public/AutoGen/GroupSearchResponse.h"

#define LOCTEXT_NAMESPACE "K2BeamNode_ApiRequest_ObjectGroupUsersGetSearchByObjectId"

using namespace BeamK2;

FName UK2BeamNode_ApiRequest_ObjectGroupUsersGetSearchByObjectId::GetSelfFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamGroupUsersApi, GetSelf);
}

FName UK2BeamNode_ApiRequest_ObjectGroupUsersGetSearchByObjectId::GetRequestFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamGroupUsersApi, GetSearch);
}

FName UK2BeamNode_ApiRequest_ObjectGroupUsersGetSearchByObjectId::GetMakeFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UObjectGroupUsersGetSearchByObjectIdRequest, Make);
}

FString UK2BeamNode_ApiRequest_ObjectGroupUsersGetSearchByObjectId::GetServiceName() const
{
	return TEXT("GroupUsers");
}

FString UK2BeamNode_ApiRequest_ObjectGroupUsersGetSearchByObjectId::GetEndpointName() const
{
	return TEXT("GetSearch");
}

UClass* UK2BeamNode_ApiRequest_ObjectGroupUsersGetSearchByObjectId::GetApiClass() const
{
	return UBeamGroupUsersApi::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_ObjectGroupUsersGetSearchByObjectId::GetRequestClass() const
{
	return UObjectGroupUsersGetSearchByObjectIdRequest::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_ObjectGroupUsersGetSearchByObjectId::GetResponseClass() const
{
	return UGroupSearchResponse::StaticClass();
}

FString UK2BeamNode_ApiRequest_ObjectGroupUsersGetSearchByObjectId::GetRequestSuccessDelegateName() const
{
	return TEXT("OnObjectGroupUsersGetSearchByObjectIdSuccess");
}

FString UK2BeamNode_ApiRequest_ObjectGroupUsersGetSearchByObjectId::GetRequestErrorDelegateName() const
{
	return TEXT("OnObjectGroupUsersGetSearchByObjectIdError");
}

FString UK2BeamNode_ApiRequest_ObjectGroupUsersGetSearchByObjectId::GetRequestCompleteDelegateName() const
{
	return TEXT("OnObjectGroupUsersGetSearchByObjectIdComplete");
}

#undef LOCTEXT_NAMESPACE
