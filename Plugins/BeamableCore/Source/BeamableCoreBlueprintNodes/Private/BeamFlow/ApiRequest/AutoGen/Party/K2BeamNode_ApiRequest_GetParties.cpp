

#include "BeamableCoreBlueprintNodes/Public/BeamFlow/ApiRequest/AutoGen/Party/K2BeamNode_ApiRequest_GetParties.h"

#include "BeamK2.h"

#include "BeamableCore/Public/AutoGen/SubSystems/BeamPartyApi.h"
#include "BeamableCore/Public/AutoGen/SubSystems/Party/GetPartiesRequest.h"
#include "BeamableCore/Public/AutoGen/Party.h"

#define LOCTEXT_NAMESPACE "K2BeamNode_ApiRequest_GetParties"

using namespace BeamK2;

FName UK2BeamNode_ApiRequest_GetParties::GetSelfFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamPartyApi, GetSelf);
}

FName UK2BeamNode_ApiRequest_GetParties::GetRequestFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamPartyApi, GetParties);
}

FName UK2BeamNode_ApiRequest_GetParties::GetMakeFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UGetPartiesRequest, Make);
}

FString UK2BeamNode_ApiRequest_GetParties::GetServiceName() const
{
	return TEXT("Party");
}

FString UK2BeamNode_ApiRequest_GetParties::GetEndpointName() const
{
	return TEXT("GetParties");
}

UClass* UK2BeamNode_ApiRequest_GetParties::GetApiClass() const
{
	return UBeamPartyApi::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_GetParties::GetRequestClass() const
{
	return UGetPartiesRequest::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_GetParties::GetResponseClass() const
{
	return UParty::StaticClass();
}

FString UK2BeamNode_ApiRequest_GetParties::GetRequestSuccessDelegateName() const
{
	return TEXT("OnGetPartiesSuccess");
}

FString UK2BeamNode_ApiRequest_GetParties::GetRequestErrorDelegateName() const
{
	return TEXT("OnGetPartiesError");
}

FString UK2BeamNode_ApiRequest_GetParties::GetRequestCompleteDelegateName() const
{
	return TEXT("OnGetPartiesComplete");
}

#undef LOCTEXT_NAMESPACE
