

#include "BeamableCoreBlueprintNodes/Public/BeamFlow/ApiRequest/AutoGen/Party/K2BeamNode_ApiRequest_DeleteMembers.h"

#include "BeamK2.h"

#include "BeamableCore/Public/AutoGen/SubSystems/BeamPartyApi.h"
#include "BeamableCore/Public/AutoGen/SubSystems/Party/DeleteMembersRequest.h"
#include "BeamableCore/Public/AutoGen/ApiPartiesMembersDeletePartyResponse.h"

#define LOCTEXT_NAMESPACE "K2BeamNode_ApiRequest_DeleteMembers"

using namespace BeamK2;

FName UK2BeamNode_ApiRequest_DeleteMembers::GetSelfFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamPartyApi, GetSelf);
}

FName UK2BeamNode_ApiRequest_DeleteMembers::GetRequestFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamPartyApi, DeleteMembers);
}

FName UK2BeamNode_ApiRequest_DeleteMembers::GetMakeFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UDeleteMembersRequest, Make);
}

FString UK2BeamNode_ApiRequest_DeleteMembers::GetServiceName() const
{
	return TEXT("Party");
}

FString UK2BeamNode_ApiRequest_DeleteMembers::GetEndpointName() const
{
	return TEXT("DeleteMembers");
}

UClass* UK2BeamNode_ApiRequest_DeleteMembers::GetApiClass() const
{
	return UBeamPartyApi::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_DeleteMembers::GetRequestClass() const
{
	return UDeleteMembersRequest::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_DeleteMembers::GetResponseClass() const
{
	return UApiPartiesMembersDeletePartyResponse::StaticClass();
}

FString UK2BeamNode_ApiRequest_DeleteMembers::GetRequestSuccessDelegateName() const
{
	return TEXT("OnDeleteMembersSuccess");
}

FString UK2BeamNode_ApiRequest_DeleteMembers::GetRequestErrorDelegateName() const
{
	return TEXT("OnDeleteMembersError");
}

FString UK2BeamNode_ApiRequest_DeleteMembers::GetRequestCompleteDelegateName() const
{
	return TEXT("OnDeleteMembersComplete");
}

#undef LOCTEXT_NAMESPACE
