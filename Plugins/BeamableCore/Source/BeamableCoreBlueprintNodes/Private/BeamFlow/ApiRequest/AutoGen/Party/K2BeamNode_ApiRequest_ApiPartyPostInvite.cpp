

#include "BeamableCoreBlueprintNodes/Public/BeamFlow/ApiRequest/AutoGen/Party/K2BeamNode_ApiRequest_ApiPartyPostInvite.h"

#include "BeamK2.h"

#include "BeamableCore/Public/AutoGen/SubSystems/BeamPartyApi.h"
#include "BeamableCore/Public/AutoGen/SubSystems/Party/ApiPartyPostInviteRequest.h"
#include "BeamableCore/Public/AutoGen/ApiPartiesInvitePostPartyResponse.h"

#define LOCTEXT_NAMESPACE "K2BeamNode_ApiRequest_ApiPartyPostInvite"

using namespace BeamK2;

FName UK2BeamNode_ApiRequest_ApiPartyPostInvite::GetSelfFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamPartyApi, GetSelf);
}

FName UK2BeamNode_ApiRequest_ApiPartyPostInvite::GetRequestFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamPartyApi, PostInvite);
}

FName UK2BeamNode_ApiRequest_ApiPartyPostInvite::GetMakeFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UApiPartyPostInviteRequest, Make);
}

FString UK2BeamNode_ApiRequest_ApiPartyPostInvite::GetServiceName() const
{
	return TEXT("Party");
}

FString UK2BeamNode_ApiRequest_ApiPartyPostInvite::GetEndpointName() const
{
	return TEXT("PostInvite");
}

UClass* UK2BeamNode_ApiRequest_ApiPartyPostInvite::GetApiClass() const
{
	return UBeamPartyApi::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_ApiPartyPostInvite::GetRequestClass() const
{
	return UApiPartyPostInviteRequest::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_ApiPartyPostInvite::GetResponseClass() const
{
	return UApiPartiesInvitePostPartyResponse::StaticClass();
}

FString UK2BeamNode_ApiRequest_ApiPartyPostInvite::GetRequestSuccessDelegateName() const
{
	return TEXT("OnApiPartyPostInviteSuccess");
}

FString UK2BeamNode_ApiRequest_ApiPartyPostInvite::GetRequestErrorDelegateName() const
{
	return TEXT("OnApiPartyPostInviteError");
}

FString UK2BeamNode_ApiRequest_ApiPartyPostInvite::GetRequestCompleteDelegateName() const
{
	return TEXT("OnApiPartyPostInviteComplete");
}

#undef LOCTEXT_NAMESPACE
