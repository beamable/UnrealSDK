

#include "BeamableCoreBlueprintNodes/Public/BeamFlow/ApiRequest/AutoGen/Party/K2BeamNode_ApiRequest_DeleteInvite.h"

#include "BeamK2.h"

#include "BeamableCore/Public/AutoGen/SubSystems/BeamPartyApi.h"
#include "BeamableCore/Public/AutoGen/SubSystems/Party/DeleteInviteRequest.h"
#include "BeamableCore/Public/AutoGen/ApiPartiesInviteDeletePartyResponse.h"

#define LOCTEXT_NAMESPACE "K2BeamNode_ApiRequest_DeleteInvite"

using namespace BeamK2;

FName UK2BeamNode_ApiRequest_DeleteInvite::GetSelfFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamPartyApi, GetSelf);
}

FName UK2BeamNode_ApiRequest_DeleteInvite::GetRequestFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamPartyApi, DeleteInvite);
}

FName UK2BeamNode_ApiRequest_DeleteInvite::GetMakeFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UDeleteInviteRequest, Make);
}

FString UK2BeamNode_ApiRequest_DeleteInvite::GetServiceName() const
{
	return TEXT("Party");
}

FString UK2BeamNode_ApiRequest_DeleteInvite::GetEndpointName() const
{
	return TEXT("DeleteInvite");
}

UClass* UK2BeamNode_ApiRequest_DeleteInvite::GetApiClass() const
{
	return UBeamPartyApi::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_DeleteInvite::GetRequestClass() const
{
	return UDeleteInviteRequest::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_DeleteInvite::GetResponseClass() const
{
	return UApiPartiesInviteDeletePartyResponse::StaticClass();
}

FString UK2BeamNode_ApiRequest_DeleteInvite::GetRequestSuccessDelegateName() const
{
	return TEXT("OnDeleteInviteSuccess");
}

FString UK2BeamNode_ApiRequest_DeleteInvite::GetRequestErrorDelegateName() const
{
	return TEXT("OnDeleteInviteError");
}

FString UK2BeamNode_ApiRequest_DeleteInvite::GetRequestCompleteDelegateName() const
{
	return TEXT("OnDeleteInviteComplete");
}

#undef LOCTEXT_NAMESPACE
