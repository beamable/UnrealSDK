

#include "BeamableCoreBlueprintNodes/Public/BeamFlow/ApiRequest/AutoGen/Party/K2BeamNode_ApiRequest_GetParty.h"

#include "BeamK2.h"

#include "BeamableCore/Public/AutoGen/SubSystems/BeamPartyApi.h"
#include "BeamableCore/Public/AutoGen/SubSystems/Party/GetPartyRequest.h"
#include "BeamableCore/Public/AutoGen/Party.h"

#define LOCTEXT_NAMESPACE "K2BeamNode_ApiRequest_GetParty"

using namespace BeamK2;

FName UK2BeamNode_ApiRequest_GetParty::GetSelfFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamPartyApi, GetSelf);
}

FName UK2BeamNode_ApiRequest_GetParty::GetRequestFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamPartyApi, GetParty);
}

FName UK2BeamNode_ApiRequest_GetParty::GetMakeFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UGetPartyRequest, Make);
}

FString UK2BeamNode_ApiRequest_GetParty::GetServiceName() const
{
	return TEXT("Party");
}

FString UK2BeamNode_ApiRequest_GetParty::GetEndpointName() const
{
	return TEXT("GetParty");
}

UClass* UK2BeamNode_ApiRequest_GetParty::GetApiClass() const
{
	return UBeamPartyApi::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_GetParty::GetRequestClass() const
{
	return UGetPartyRequest::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_GetParty::GetResponseClass() const
{
	return UParty::StaticClass();
}

FString UK2BeamNode_ApiRequest_GetParty::GetRequestSuccessDelegateName() const
{
	return TEXT("OnGetPartySuccess");
}

FString UK2BeamNode_ApiRequest_GetParty::GetRequestErrorDelegateName() const
{
	return TEXT("OnGetPartyError");
}

FString UK2BeamNode_ApiRequest_GetParty::GetRequestCompleteDelegateName() const
{
	return TEXT("OnGetPartyComplete");
}

#undef LOCTEXT_NAMESPACE
