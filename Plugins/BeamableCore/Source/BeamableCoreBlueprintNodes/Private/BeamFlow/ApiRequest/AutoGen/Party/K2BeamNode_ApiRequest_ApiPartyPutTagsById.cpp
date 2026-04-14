

#include "BeamableCoreBlueprintNodes/Public/BeamFlow/ApiRequest/AutoGen/Party/K2BeamNode_ApiRequest_ApiPartyPutTagsById.h"

#include "BeamK2.h"

#include "BeamableCore/Public/AutoGen/SubSystems/BeamPartyApi.h"
#include "BeamableCore/Public/AutoGen/SubSystems/Party/ApiPartyPutTagsByIdRequest.h"
#include "BeamableCore/Public/AutoGen/Party.h"

#define LOCTEXT_NAMESPACE "K2BeamNode_ApiRequest_ApiPartyPutTagsById"

using namespace BeamK2;

FName UK2BeamNode_ApiRequest_ApiPartyPutTagsById::GetSelfFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamPartyApi, GetSelf);
}

FName UK2BeamNode_ApiRequest_ApiPartyPutTagsById::GetRequestFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamPartyApi, PutTags);
}

FName UK2BeamNode_ApiRequest_ApiPartyPutTagsById::GetMakeFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UApiPartyPutTagsByIdRequest, Make);
}

FString UK2BeamNode_ApiRequest_ApiPartyPutTagsById::GetServiceName() const
{
	return TEXT("Party");
}

FString UK2BeamNode_ApiRequest_ApiPartyPutTagsById::GetEndpointName() const
{
	return TEXT("PutTags");
}

UClass* UK2BeamNode_ApiRequest_ApiPartyPutTagsById::GetApiClass() const
{
	return UBeamPartyApi::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_ApiPartyPutTagsById::GetRequestClass() const
{
	return UApiPartyPutTagsByIdRequest::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_ApiPartyPutTagsById::GetResponseClass() const
{
	return UParty::StaticClass();
}

FString UK2BeamNode_ApiRequest_ApiPartyPutTagsById::GetRequestSuccessDelegateName() const
{
	return TEXT("OnApiPartyPutTagsByIdSuccess");
}

FString UK2BeamNode_ApiRequest_ApiPartyPutTagsById::GetRequestErrorDelegateName() const
{
	return TEXT("OnApiPartyPutTagsByIdError");
}

FString UK2BeamNode_ApiRequest_ApiPartyPutTagsById::GetRequestCompleteDelegateName() const
{
	return TEXT("OnApiPartyPutTagsByIdComplete");
}

#undef LOCTEXT_NAMESPACE
