

#include "BeamableCoreBlueprintNodes/Public/BeamFlow/ApiRequest/AutoGen/Party/K2BeamNode_ApiRequest_PutParty.h"

#include "BeamK2.h"

#include "BeamableCore/Public/AutoGen/SubSystems/BeamPartyApi.h"
#include "BeamableCore/Public/AutoGen/SubSystems/Party/PutPartyRequest.h"
#include "BeamableCore/Public/AutoGen/Party.h"

#define LOCTEXT_NAMESPACE "K2BeamNode_ApiRequest_PutParty"

using namespace BeamK2;

FName UK2BeamNode_ApiRequest_PutParty::GetSelfFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamPartyApi, GetSelf);
}

FName UK2BeamNode_ApiRequest_PutParty::GetRequestFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamPartyApi, PutParty);
}

FName UK2BeamNode_ApiRequest_PutParty::GetMakeFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UPutPartyRequest, Make);
}

FString UK2BeamNode_ApiRequest_PutParty::GetServiceName() const
{
	return TEXT("Party");
}

FString UK2BeamNode_ApiRequest_PutParty::GetEndpointName() const
{
	return TEXT("PutParty");
}

UClass* UK2BeamNode_ApiRequest_PutParty::GetApiClass() const
{
	return UBeamPartyApi::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_PutParty::GetRequestClass() const
{
	return UPutPartyRequest::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_PutParty::GetResponseClass() const
{
	return UParty::StaticClass();
}

FString UK2BeamNode_ApiRequest_PutParty::GetRequestSuccessDelegateName() const
{
	return TEXT("OnPutPartySuccess");
}

FString UK2BeamNode_ApiRequest_PutParty::GetRequestErrorDelegateName() const
{
	return TEXT("OnPutPartyError");
}

FString UK2BeamNode_ApiRequest_PutParty::GetRequestCompleteDelegateName() const
{
	return TEXT("OnPutPartyComplete");
}

#undef LOCTEXT_NAMESPACE
