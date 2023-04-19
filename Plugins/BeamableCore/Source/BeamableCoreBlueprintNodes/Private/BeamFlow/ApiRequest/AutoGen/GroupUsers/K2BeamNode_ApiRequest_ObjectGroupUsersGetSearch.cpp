

#include "BeamableCoreBlueprintNodes/Public/BeamFlow/ApiRequest/AutoGen/GroupUsers/K2BeamNode_ApiRequest_ObjectGroupUsersGetSearch.h"

#include "BeamK2.h"

#include "BeamableCore/Public/AutoGen/SubSystems/BeamGroupUsersApi.h"
#include "BeamableCore/Public/AutoGen/SubSystems/GroupUsers/ObjectGroupUsersGetSearchRequest.h"
#include "BeamableCore/Public/AutoGen/GroupSearchResponse.h"

#define LOCTEXT_NAMESPACE "K2BeamNode_ApiRequest_ObjectGroupUsersGetSearch"

using namespace BeamK2;

FName UK2BeamNode_ApiRequest_ObjectGroupUsersGetSearch::GetSelfFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamGroupUsersApi, GetSelf);
}

FName UK2BeamNode_ApiRequest_ObjectGroupUsersGetSearch::GetRequestFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamGroupUsersApi, GetSearch);
}

FName UK2BeamNode_ApiRequest_ObjectGroupUsersGetSearch::GetMakeFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UObjectGroupUsersGetSearchRequest, Make);
}

FString UK2BeamNode_ApiRequest_ObjectGroupUsersGetSearch::GetServiceName() const
{
	return TEXT("GroupUsers");
}

FString UK2BeamNode_ApiRequest_ObjectGroupUsersGetSearch::GetEndpointName() const
{
	return TEXT("GetSearch");
}

UClass* UK2BeamNode_ApiRequest_ObjectGroupUsersGetSearch::GetApiClass() const
{
	return UBeamGroupUsersApi::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_ObjectGroupUsersGetSearch::GetRequestClass() const
{
	return UObjectGroupUsersGetSearchRequest::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_ObjectGroupUsersGetSearch::GetResponseClass() const
{
	return UGroupSearchResponse::StaticClass();
}

FString UK2BeamNode_ApiRequest_ObjectGroupUsersGetSearch::GetRequestSuccessDelegateName() const
{
	return TEXT("OnObjectGroupUsersGetSearchSuccess");
}

FString UK2BeamNode_ApiRequest_ObjectGroupUsersGetSearch::GetRequestErrorDelegateName() const
{
	return TEXT("OnObjectGroupUsersGetSearchError");
}

FString UK2BeamNode_ApiRequest_ObjectGroupUsersGetSearch::GetRequestCompleteDelegateName() const
{
	return TEXT("OnObjectGroupUsersGetSearchComplete");
}

#undef LOCTEXT_NAMESPACE
