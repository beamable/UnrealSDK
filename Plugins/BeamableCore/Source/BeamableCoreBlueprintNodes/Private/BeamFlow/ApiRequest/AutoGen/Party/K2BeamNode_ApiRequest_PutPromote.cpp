

#include "BeamableCoreBlueprintNodes/Public/BeamFlow/ApiRequest/AutoGen/Party/K2BeamNode_ApiRequest_PutPromote.h"

#include "BeamK2.h"

#include "BeamableCore/Public/AutoGen/SubSystems/BeamPartyApi.h"
#include "BeamableCore/Public/AutoGen/SubSystems/Party/PutPromoteRequest.h"
#include "BeamableCore/Public/AutoGen/Party.h"

#define LOCTEXT_NAMESPACE "K2BeamNode_ApiRequest_PutPromote"

using namespace BeamK2;

FName UK2BeamNode_ApiRequest_PutPromote::GetSelfFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamPartyApi, GetSelf);
}

FName UK2BeamNode_ApiRequest_PutPromote::GetRequestFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamPartyApi, PutPromote);
}

FName UK2BeamNode_ApiRequest_PutPromote::GetMakeFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UPutPromoteRequest, Make);
}

FString UK2BeamNode_ApiRequest_PutPromote::GetServiceName() const
{
	return TEXT("Party");
}

FString UK2BeamNode_ApiRequest_PutPromote::GetEndpointName() const
{
	return TEXT("PutPromote");
}

UClass* UK2BeamNode_ApiRequest_PutPromote::GetApiClass() const
{
	return UBeamPartyApi::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_PutPromote::GetRequestClass() const
{
	return UPutPromoteRequest::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_PutPromote::GetResponseClass() const
{
	return UParty::StaticClass();
}

FString UK2BeamNode_ApiRequest_PutPromote::GetRequestSuccessDelegateName() const
{
	return TEXT("OnPutPromoteSuccess");
}

FString UK2BeamNode_ApiRequest_PutPromote::GetRequestErrorDelegateName() const
{
	return TEXT("OnPutPromoteError");
}

FString UK2BeamNode_ApiRequest_PutPromote::GetRequestCompleteDelegateName() const
{
	return TEXT("OnPutPromoteComplete");
}

#undef LOCTEXT_NAMESPACE
