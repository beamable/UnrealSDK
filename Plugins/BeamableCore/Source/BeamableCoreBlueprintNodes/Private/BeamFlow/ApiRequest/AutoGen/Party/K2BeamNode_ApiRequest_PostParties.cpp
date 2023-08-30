

#include "BeamableCoreBlueprintNodes/Public/BeamFlow/ApiRequest/AutoGen/Party/K2BeamNode_ApiRequest_PostParties.h"

#include "BeamK2.h"

#include "BeamableCore/Public/AutoGen/SubSystems/BeamPartyApi.h"
#include "BeamableCore/Public/AutoGen/SubSystems/Party/PostPartiesRequest.h"
#include "BeamableCore/Public/AutoGen/Party.h"

#define LOCTEXT_NAMESPACE "K2BeamNode_ApiRequest_PostParties"

using namespace BeamK2;

FName UK2BeamNode_ApiRequest_PostParties::GetSelfFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamPartyApi, GetSelf);
}

FName UK2BeamNode_ApiRequest_PostParties::GetRequestFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamPartyApi, PostParties);
}

FName UK2BeamNode_ApiRequest_PostParties::GetMakeFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UPostPartiesRequest, Make);
}

FString UK2BeamNode_ApiRequest_PostParties::GetServiceName() const
{
	return TEXT("Party");
}

FString UK2BeamNode_ApiRequest_PostParties::GetEndpointName() const
{
	return TEXT("PostParties");
}

UClass* UK2BeamNode_ApiRequest_PostParties::GetApiClass() const
{
	return UBeamPartyApi::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_PostParties::GetRequestClass() const
{
	return UPostPartiesRequest::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_PostParties::GetResponseClass() const
{
	return UParty::StaticClass();
}

FString UK2BeamNode_ApiRequest_PostParties::GetRequestSuccessDelegateName() const
{
	return TEXT("OnPostPartiesSuccess");
}

FString UK2BeamNode_ApiRequest_PostParties::GetRequestErrorDelegateName() const
{
	return TEXT("OnPostPartiesError");
}

FString UK2BeamNode_ApiRequest_PostParties::GetRequestCompleteDelegateName() const
{
	return TEXT("OnPostPartiesComplete");
}

#undef LOCTEXT_NAMESPACE
