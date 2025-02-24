

#include "BeamableCoreBlueprintNodes/Public/BeamFlow/ApiRequest/AutoGen/PlayerParty/K2BeamNode_ApiRequest_DeleteParties.h"

#include "BeamK2.h"

#include "BeamableCore/Public/AutoGen/SubSystems/BeamPlayerPartyApi.h"
#include "BeamableCore/Public/AutoGen/SubSystems/PlayerParty/DeletePartiesRequest.h"
#include "BeamableCore/Public/AutoGen/ApiPlayersPartiesDeletePlayerPartyResponse.h"

#define LOCTEXT_NAMESPACE "K2BeamNode_ApiRequest_DeleteParties"

using namespace BeamK2;

FName UK2BeamNode_ApiRequest_DeleteParties::GetSelfFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamPlayerPartyApi, GetSelf);
}

FName UK2BeamNode_ApiRequest_DeleteParties::GetRequestFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamPlayerPartyApi, DeleteParties);
}

FName UK2BeamNode_ApiRequest_DeleteParties::GetMakeFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UDeletePartiesRequest, Make);
}

FString UK2BeamNode_ApiRequest_DeleteParties::GetServiceName() const
{
	return TEXT("PlayerParty");
}

FString UK2BeamNode_ApiRequest_DeleteParties::GetEndpointName() const
{
	return TEXT("DeleteParties");
}

UClass* UK2BeamNode_ApiRequest_DeleteParties::GetApiClass() const
{
	return UBeamPlayerPartyApi::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_DeleteParties::GetRequestClass() const
{
	return UDeletePartiesRequest::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_DeleteParties::GetResponseClass() const
{
	return UApiPlayersPartiesDeletePlayerPartyResponse::StaticClass();
}

FString UK2BeamNode_ApiRequest_DeleteParties::GetRequestSuccessDelegateName() const
{
	return TEXT("OnDeletePartiesSuccess");
}

FString UK2BeamNode_ApiRequest_DeleteParties::GetRequestErrorDelegateName() const
{
	return TEXT("OnDeletePartiesError");
}

FString UK2BeamNode_ApiRequest_DeleteParties::GetRequestCompleteDelegateName() const
{
	return TEXT("OnDeletePartiesComplete");
}

#undef LOCTEXT_NAMESPACE
