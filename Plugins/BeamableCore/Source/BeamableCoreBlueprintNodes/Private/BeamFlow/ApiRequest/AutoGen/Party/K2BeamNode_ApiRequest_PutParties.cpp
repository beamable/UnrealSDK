

#include "BeamableCoreBlueprintNodes/Public/BeamFlow/ApiRequest/AutoGen/Party/K2BeamNode_ApiRequest_PutParties.h"

#include "BeamK2.h"

#include "BeamableCore/Public/AutoGen/SubSystems/BeamPartyApi.h"
#include "BeamableCore/Public/AutoGen/SubSystems/Party/PutPartiesRequest.h"
#include "BeamableCore/Public/AutoGen/Party.h"

#define LOCTEXT_NAMESPACE "K2BeamNode_ApiRequest_PutParties"

using namespace BeamK2;

FName UK2BeamNode_ApiRequest_PutParties::GetSelfFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamPartyApi, GetSelf);
}

FName UK2BeamNode_ApiRequest_PutParties::GetRequestFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamPartyApi, PutParties);
}

FName UK2BeamNode_ApiRequest_PutParties::GetMakeFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UPutPartiesRequest, Make);
}

FString UK2BeamNode_ApiRequest_PutParties::GetServiceName() const
{
	return TEXT("Party");
}

FString UK2BeamNode_ApiRequest_PutParties::GetEndpointName() const
{
	return TEXT("PutParties");
}

UClass* UK2BeamNode_ApiRequest_PutParties::GetApiClass() const
{
	return UBeamPartyApi::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_PutParties::GetRequestClass() const
{
	return UPutPartiesRequest::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_PutParties::GetResponseClass() const
{
	return UParty::StaticClass();
}

FString UK2BeamNode_ApiRequest_PutParties::GetRequestSuccessDelegateName() const
{
	return TEXT("OnPutPartiesSuccess");
}

FString UK2BeamNode_ApiRequest_PutParties::GetRequestErrorDelegateName() const
{
	return TEXT("OnPutPartiesError");
}

FString UK2BeamNode_ApiRequest_PutParties::GetRequestCompleteDelegateName() const
{
	return TEXT("OnPutPartiesComplete");
}

#undef LOCTEXT_NAMESPACE
