

#include "BeamableCoreBlueprintNodes/Public/BeamFlow/ApiRequest/AutoGen/PlayerParty/K2BeamNode_ApiRequest_GetPartiesInvites.h"

#include "BeamK2.h"

#include "BeamableCore/Public/AutoGen/SubSystems/BeamPlayerPartyApi.h"
#include "BeamableCore/Public/AutoGen/SubSystems/PlayerParty/GetPartiesInvitesRequest.h"
#include "BeamableCore/Public/AutoGen/PartyInvitesForPlayerResponse.h"

#define LOCTEXT_NAMESPACE "K2BeamNode_ApiRequest_GetPartiesInvites"

using namespace BeamK2;

FName UK2BeamNode_ApiRequest_GetPartiesInvites::GetSelfFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamPlayerPartyApi, GetSelf);
}

FName UK2BeamNode_ApiRequest_GetPartiesInvites::GetRequestFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamPlayerPartyApi, GetPartiesInvites);
}

FName UK2BeamNode_ApiRequest_GetPartiesInvites::GetMakeFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UGetPartiesInvitesRequest, Make);
}

FString UK2BeamNode_ApiRequest_GetPartiesInvites::GetServiceName() const
{
	return TEXT("PlayerParty");
}

FString UK2BeamNode_ApiRequest_GetPartiesInvites::GetEndpointName() const
{
	return TEXT("GetPartiesInvites");
}

UClass* UK2BeamNode_ApiRequest_GetPartiesInvites::GetApiClass() const
{
	return UBeamPlayerPartyApi::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_GetPartiesInvites::GetRequestClass() const
{
	return UGetPartiesInvitesRequest::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_GetPartiesInvites::GetResponseClass() const
{
	return UPartyInvitesForPlayerResponse::StaticClass();
}

FString UK2BeamNode_ApiRequest_GetPartiesInvites::GetRequestSuccessDelegateName() const
{
	return TEXT("OnGetPartiesInvitesSuccess");
}

FString UK2BeamNode_ApiRequest_GetPartiesInvites::GetRequestErrorDelegateName() const
{
	return TEXT("OnGetPartiesInvitesError");
}

FString UK2BeamNode_ApiRequest_GetPartiesInvites::GetRequestCompleteDelegateName() const
{
	return TEXT("OnGetPartiesInvitesComplete");
}

#undef LOCTEXT_NAMESPACE
