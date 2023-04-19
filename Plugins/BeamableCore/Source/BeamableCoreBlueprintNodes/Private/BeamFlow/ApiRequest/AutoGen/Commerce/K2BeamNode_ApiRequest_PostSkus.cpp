

#include "BeamableCoreBlueprintNodes/Public/BeamFlow/ApiRequest/AutoGen/Commerce/K2BeamNode_ApiRequest_PostSkus.h"

#include "BeamK2.h"

#include "BeamableCore/Public/AutoGen/SubSystems/BeamCommerceApi.h"
#include "BeamableCore/Public/AutoGen/SubSystems/Commerce/PostSkusRequest.h"
#include "BeamableCore/Public/AutoGen/ResultResponse.h"

#define LOCTEXT_NAMESPACE "K2BeamNode_ApiRequest_PostSkus"

using namespace BeamK2;

FName UK2BeamNode_ApiRequest_PostSkus::GetSelfFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamCommerceApi, GetSelf);
}

FName UK2BeamNode_ApiRequest_PostSkus::GetRequestFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamCommerceApi, PostSkus);
}

FName UK2BeamNode_ApiRequest_PostSkus::GetMakeFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UPostSkusRequest, Make);
}

FString UK2BeamNode_ApiRequest_PostSkus::GetServiceName() const
{
	return TEXT("Commerce");
}

FString UK2BeamNode_ApiRequest_PostSkus::GetEndpointName() const
{
	return TEXT("PostSkus");
}

UClass* UK2BeamNode_ApiRequest_PostSkus::GetApiClass() const
{
	return UBeamCommerceApi::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_PostSkus::GetRequestClass() const
{
	return UPostSkusRequest::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_PostSkus::GetResponseClass() const
{
	return UResultResponse::StaticClass();
}

FString UK2BeamNode_ApiRequest_PostSkus::GetRequestSuccessDelegateName() const
{
	return TEXT("OnPostSkusSuccess");
}

FString UK2BeamNode_ApiRequest_PostSkus::GetRequestErrorDelegateName() const
{
	return TEXT("OnPostSkusError");
}

FString UK2BeamNode_ApiRequest_PostSkus::GetRequestCompleteDelegateName() const
{
	return TEXT("OnPostSkusComplete");
}

#undef LOCTEXT_NAMESPACE
