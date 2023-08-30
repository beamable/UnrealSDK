

#include "BeamableCoreBlueprintNodes/Public/BeamFlow/ApiRequest/AutoGen/Player/K2BeamNode_ApiRequest_GetPartiesInvites.h"

#include "BeamK2.h"

#include "BeamableCore/Public/AutoGen/SubSystems/BeamPlayerApi.h"
#include "BeamableCore/Public/AutoGen/SubSystems/Player/GetPartiesInvitesRequest.h"
#include "BeamableCore/Public/AutoGen/PartyInvitesForPlayerResponse.h"

#define LOCTEXT_NAMESPACE "K2BeamNode_ApiRequest_GetPartiesInvites"

using namespace BeamK2;

FName UK2BeamNode_ApiRequest_GetPartiesInvites::GetSelfFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamPlayerApi, GetSelf);
}

FName UK2BeamNode_ApiRequest_GetPartiesInvites::GetRequestFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamPlayerApi, GetPartiesInvites);
}

FName UK2BeamNode_ApiRequest_GetPartiesInvites::GetMakeFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UGetPartiesInvitesRequest, Make);
}

FString UK2BeamNode_ApiRequest_GetPartiesInvites::GetServiceName() const
{
	return TEXT("Player");
}

FString UK2BeamNode_ApiRequest_GetPartiesInvites::GetEndpointName() const
{
	return TEXT("GetPartiesInvites");
}

UClass* UK2BeamNode_ApiRequest_GetPartiesInvites::GetApiClass() const
{
	return UBeamPlayerApi::StaticClass();
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
