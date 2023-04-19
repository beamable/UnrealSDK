

#include "BeamableCoreBlueprintNodes/Public/BeamFlow/ApiRequest/AutoGen/Commerce/K2BeamNode_ApiRequest_GetSkus.h"

#include "BeamK2.h"

#include "BeamableCore/Public/AutoGen/SubSystems/BeamCommerceApi.h"
#include "BeamableCore/Public/AutoGen/SubSystems/Commerce/GetSkusRequest.h"
#include "BeamableCore/Public/AutoGen/GetSKUsResponse.h"

#define LOCTEXT_NAMESPACE "K2BeamNode_ApiRequest_GetSkus"

using namespace BeamK2;

FName UK2BeamNode_ApiRequest_GetSkus::GetSelfFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamCommerceApi, GetSelf);
}

FName UK2BeamNode_ApiRequest_GetSkus::GetRequestFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamCommerceApi, GetSkus);
}

FName UK2BeamNode_ApiRequest_GetSkus::GetMakeFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UGetSkusRequest, Make);
}

FString UK2BeamNode_ApiRequest_GetSkus::GetServiceName() const
{
	return TEXT("Commerce");
}

FString UK2BeamNode_ApiRequest_GetSkus::GetEndpointName() const
{
	return TEXT("GetSkus");
}

UClass* UK2BeamNode_ApiRequest_GetSkus::GetApiClass() const
{
	return UBeamCommerceApi::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_GetSkus::GetRequestClass() const
{
	return UGetSkusRequest::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_GetSkus::GetResponseClass() const
{
	return UGetSKUsResponse::StaticClass();
}

FString UK2BeamNode_ApiRequest_GetSkus::GetRequestSuccessDelegateName() const
{
	return TEXT("OnGetSkusSuccess");
}

FString UK2BeamNode_ApiRequest_GetSkus::GetRequestErrorDelegateName() const
{
	return TEXT("OnGetSkusError");
}

FString UK2BeamNode_ApiRequest_GetSkus::GetRequestCompleteDelegateName() const
{
	return TEXT("OnGetSkusComplete");
}

#undef LOCTEXT_NAMESPACE
