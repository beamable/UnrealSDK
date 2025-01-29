

#include "BeamableCoreBlueprintNodes/Public/BeamFlow/ApiRequest/AutoGen/Party/K2BeamNode_ApiRequest_ApiPartyPutMetadataById.h"

#include "BeamK2.h"

#include "BeamableCore/Public/AutoGen/SubSystems/BeamPartyApi.h"
#include "BeamableCore/Public/AutoGen/SubSystems/Party/ApiPartyPutMetadataByIdRequest.h"
#include "BeamableCore/Public/AutoGen/Party.h"

#define LOCTEXT_NAMESPACE "K2BeamNode_ApiRequest_ApiPartyPutMetadataById"

using namespace BeamK2;

FName UK2BeamNode_ApiRequest_ApiPartyPutMetadataById::GetSelfFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamPartyApi, GetSelf);
}

FName UK2BeamNode_ApiRequest_ApiPartyPutMetadataById::GetRequestFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamPartyApi, PutMetadata);
}

FName UK2BeamNode_ApiRequest_ApiPartyPutMetadataById::GetMakeFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UApiPartyPutMetadataByIdRequest, Make);
}

FString UK2BeamNode_ApiRequest_ApiPartyPutMetadataById::GetServiceName() const
{
	return TEXT("Party");
}

FString UK2BeamNode_ApiRequest_ApiPartyPutMetadataById::GetEndpointName() const
{
	return TEXT("PutMetadata");
}

UClass* UK2BeamNode_ApiRequest_ApiPartyPutMetadataById::GetApiClass() const
{
	return UBeamPartyApi::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_ApiPartyPutMetadataById::GetRequestClass() const
{
	return UApiPartyPutMetadataByIdRequest::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_ApiPartyPutMetadataById::GetResponseClass() const
{
	return UParty::StaticClass();
}

FString UK2BeamNode_ApiRequest_ApiPartyPutMetadataById::GetRequestSuccessDelegateName() const
{
	return TEXT("OnApiPartyPutMetadataByIdSuccess");
}

FString UK2BeamNode_ApiRequest_ApiPartyPutMetadataById::GetRequestErrorDelegateName() const
{
	return TEXT("OnApiPartyPutMetadataByIdError");
}

FString UK2BeamNode_ApiRequest_ApiPartyPutMetadataById::GetRequestCompleteDelegateName() const
{
	return TEXT("OnApiPartyPutMetadataByIdComplete");
}

#undef LOCTEXT_NAMESPACE
