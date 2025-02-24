

#include "BeamableCoreBlueprintNodes/Public/BeamFlow/ApiRequest/AutoGen/Party/K2BeamNode_ApiRequest_ApiPartyPostInviteById.h"

#include "BeamK2.h"

#include "BeamableCore/Public/AutoGen/SubSystems/BeamPartyApi.h"
#include "BeamableCore/Public/AutoGen/SubSystems/Party/ApiPartyPostInviteByIdRequest.h"
#include "BeamableCore/Public/AutoGen/ApiPartiesInvitePostPartyResponse.h"

#define LOCTEXT_NAMESPACE "K2BeamNode_ApiRequest_ApiPartyPostInviteById"

using namespace BeamK2;

FName UK2BeamNode_ApiRequest_ApiPartyPostInviteById::GetSelfFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamPartyApi, GetSelf);
}

FName UK2BeamNode_ApiRequest_ApiPartyPostInviteById::GetRequestFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamPartyApi, PostInvite);
}

FName UK2BeamNode_ApiRequest_ApiPartyPostInviteById::GetMakeFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UApiPartyPostInviteByIdRequest, Make);
}

FString UK2BeamNode_ApiRequest_ApiPartyPostInviteById::GetServiceName() const
{
	return TEXT("Party");
}

FString UK2BeamNode_ApiRequest_ApiPartyPostInviteById::GetEndpointName() const
{
	return TEXT("PostInvite");
}

UClass* UK2BeamNode_ApiRequest_ApiPartyPostInviteById::GetApiClass() const
{
	return UBeamPartyApi::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_ApiPartyPostInviteById::GetRequestClass() const
{
	return UApiPartyPostInviteByIdRequest::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_ApiPartyPostInviteById::GetResponseClass() const
{
	return UApiPartiesInvitePostPartyResponse::StaticClass();
}

FString UK2BeamNode_ApiRequest_ApiPartyPostInviteById::GetRequestSuccessDelegateName() const
{
	return TEXT("OnApiPartyPostInviteByIdSuccess");
}

FString UK2BeamNode_ApiRequest_ApiPartyPostInviteById::GetRequestErrorDelegateName() const
{
	return TEXT("OnApiPartyPostInviteByIdError");
}

FString UK2BeamNode_ApiRequest_ApiPartyPostInviteById::GetRequestCompleteDelegateName() const
{
	return TEXT("OnApiPartyPostInviteByIdComplete");
}

#undef LOCTEXT_NAMESPACE
