

#include "BeamableCoreBlueprintNodes/Public/BeamFlow/ApiRequest/AutoGen/Commerce/K2BeamNode_ApiRequest_PutListingsCooldown.h"

#include "BeamK2.h"

#include "BeamableCore/Public/AutoGen/SubSystems/BeamCommerceApi.h"
#include "BeamableCore/Public/AutoGen/SubSystems/Commerce/PutListingsCooldownRequest.h"
#include "BeamableCore/Public/AutoGen/CommonResponse.h"

#define LOCTEXT_NAMESPACE "K2BeamNode_ApiRequest_PutListingsCooldown"

using namespace BeamK2;

FName UK2BeamNode_ApiRequest_PutListingsCooldown::GetSelfFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamCommerceApi, GetSelf);
}

FName UK2BeamNode_ApiRequest_PutListingsCooldown::GetRequestFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamCommerceApi, PutListingsCooldown);
}

FName UK2BeamNode_ApiRequest_PutListingsCooldown::GetMakeFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UPutListingsCooldownRequest, Make);
}

FString UK2BeamNode_ApiRequest_PutListingsCooldown::GetServiceName() const
{
	return TEXT("Commerce");
}

FString UK2BeamNode_ApiRequest_PutListingsCooldown::GetEndpointName() const
{
	return TEXT("PutListingsCooldown");
}

UClass* UK2BeamNode_ApiRequest_PutListingsCooldown::GetApiClass() const
{
	return UBeamCommerceApi::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_PutListingsCooldown::GetRequestClass() const
{
	return UPutListingsCooldownRequest::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_PutListingsCooldown::GetResponseClass() const
{
	return UCommonResponse::StaticClass();
}

FString UK2BeamNode_ApiRequest_PutListingsCooldown::GetRequestSuccessDelegateName() const
{
	return TEXT("OnPutListingsCooldownSuccess");
}

FString UK2BeamNode_ApiRequest_PutListingsCooldown::GetRequestErrorDelegateName() const
{
	return TEXT("OnPutListingsCooldownError");
}

FString UK2BeamNode_ApiRequest_PutListingsCooldown::GetRequestCompleteDelegateName() const
{
	return TEXT("OnPutListingsCooldownComplete");
}

#undef LOCTEXT_NAMESPACE
