

#include "BeamableCoreBlueprintNodes/Public/BeamFlow/ApiRequest/AutoGen/Party/K2BeamNode_ApiRequest_ApiPartyPutMetadata.h"

#include "BeamK2.h"

#include "BeamableCore/Public/AutoGen/SubSystems/BeamPartyApi.h"
#include "BeamableCore/Public/AutoGen/SubSystems/Party/ApiPartyPutMetadataRequest.h"
#include "BeamableCore/Public/AutoGen/Party.h"

#define LOCTEXT_NAMESPACE "K2BeamNode_ApiRequest_ApiPartyPutMetadata"

using namespace BeamK2;

FName UK2BeamNode_ApiRequest_ApiPartyPutMetadata::GetSelfFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamPartyApi, GetSelf);
}

FName UK2BeamNode_ApiRequest_ApiPartyPutMetadata::GetRequestFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamPartyApi, PutMetadata);
}

FName UK2BeamNode_ApiRequest_ApiPartyPutMetadata::GetMakeFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UApiPartyPutMetadataRequest, Make);
}

FString UK2BeamNode_ApiRequest_ApiPartyPutMetadata::GetServiceName() const
{
	return TEXT("Party");
}

FString UK2BeamNode_ApiRequest_ApiPartyPutMetadata::GetEndpointName() const
{
	return TEXT("PutMetadata");
}

UClass* UK2BeamNode_ApiRequest_ApiPartyPutMetadata::GetApiClass() const
{
	return UBeamPartyApi::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_ApiPartyPutMetadata::GetRequestClass() const
{
	return UApiPartyPutMetadataRequest::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_ApiPartyPutMetadata::GetResponseClass() const
{
	return UParty::StaticClass();
}

FString UK2BeamNode_ApiRequest_ApiPartyPutMetadata::GetRequestSuccessDelegateName() const
{
	return TEXT("OnApiPartyPutMetadataSuccess");
}

FString UK2BeamNode_ApiRequest_ApiPartyPutMetadata::GetRequestErrorDelegateName() const
{
	return TEXT("OnApiPartyPutMetadataError");
}

FString UK2BeamNode_ApiRequest_ApiPartyPutMetadata::GetRequestCompleteDelegateName() const
{
	return TEXT("OnApiPartyPutMetadataComplete");
}

#undef LOCTEXT_NAMESPACE
