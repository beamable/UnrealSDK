

#include "BeamableCoreBlueprintNodes/Public/BeamFlow/ApiRequest/AutoGen/PlayerParty/K2BeamNode_ApiRequest_GetPartyInvites.h"

#include "BeamK2.h"

#include "BeamableCore/Public/AutoGen/SubSystems/BeamPlayerPartyApi.h"
#include "BeamableCore/Public/AutoGen/SubSystems/PlayerParty/GetPartyInvitesRequest.h"
#include "BeamableCore/Public/AutoGen/PartyInvitesForPlayerResponse.h"

#define LOCTEXT_NAMESPACE "K2BeamNode_ApiRequest_GetPartyInvites"

using namespace BeamK2;

FName UK2BeamNode_ApiRequest_GetPartyInvites::GetSelfFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamPlayerPartyApi, GetSelf);
}

FName UK2BeamNode_ApiRequest_GetPartyInvites::GetRequestFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamPlayerPartyApi, GetPartyInvites);
}

FName UK2BeamNode_ApiRequest_GetPartyInvites::GetMakeFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UGetPartyInvitesRequest, Make);
}

FString UK2BeamNode_ApiRequest_GetPartyInvites::GetServiceName() const
{
	return TEXT("PlayerParty");
}

FString UK2BeamNode_ApiRequest_GetPartyInvites::GetEndpointName() const
{
	return TEXT("GetPartyInvites");
}

UClass* UK2BeamNode_ApiRequest_GetPartyInvites::GetApiClass() const
{
	return UBeamPlayerPartyApi::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_GetPartyInvites::GetRequestClass() const
{
	return UGetPartyInvitesRequest::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_GetPartyInvites::GetResponseClass() const
{
	return UPartyInvitesForPlayerResponse::StaticClass();
}

FString UK2BeamNode_ApiRequest_GetPartyInvites::GetRequestSuccessDelegateName() const
{
	return TEXT("OnGetPartyInvitesSuccess");
}

FString UK2BeamNode_ApiRequest_GetPartyInvites::GetRequestErrorDelegateName() const
{
	return TEXT("OnGetPartyInvitesError");
}

FString UK2BeamNode_ApiRequest_GetPartyInvites::GetRequestCompleteDelegateName() const
{
	return TEXT("OnGetPartyInvitesComplete");
}

#undef LOCTEXT_NAMESPACE
