

#include "BeamableCoreBlueprintNodes/Public/BeamFlow/ApiRequest/AutoGen/Commerce/K2BeamNode_ApiRequest_GetCommerce.h"

#include "BeamK2.h"

#include "BeamableCore/Public/AutoGen/SubSystems/BeamCommerceApi.h"
#include "BeamableCore/Public/AutoGen/SubSystems/Commerce/GetCommerceRequest.h"
#include "BeamableCore/Public/AutoGen/GetActiveOffersResponse.h"

#define LOCTEXT_NAMESPACE "K2BeamNode_ApiRequest_GetCommerce"

using namespace BeamK2;

FName UK2BeamNode_ApiRequest_GetCommerce::GetSelfFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamCommerceApi, GetSelf);
}

FName UK2BeamNode_ApiRequest_GetCommerce::GetRequestFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamCommerceApi, GetCommerce);
}

FName UK2BeamNode_ApiRequest_GetCommerce::GetMakeFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UGetCommerceRequest, Make);
}

FString UK2BeamNode_ApiRequest_GetCommerce::GetServiceName() const
{
	return TEXT("Commerce");
}

FString UK2BeamNode_ApiRequest_GetCommerce::GetEndpointName() const
{
	return TEXT("GetCommerce");
}

UClass* UK2BeamNode_ApiRequest_GetCommerce::GetApiClass() const
{
	return UBeamCommerceApi::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_GetCommerce::GetRequestClass() const
{
	return UGetCommerceRequest::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_GetCommerce::GetResponseClass() const
{
	return UGetActiveOffersResponse::StaticClass();
}

FString UK2BeamNode_ApiRequest_GetCommerce::GetRequestSuccessDelegateName() const
{
	return TEXT("OnGetCommerceSuccess");
}

FString UK2BeamNode_ApiRequest_GetCommerce::GetRequestErrorDelegateName() const
{
	return TEXT("OnGetCommerceError");
}

FString UK2BeamNode_ApiRequest_GetCommerce::GetRequestCompleteDelegateName() const
{
	return TEXT("OnGetCommerceComplete");
}

#undef LOCTEXT_NAMESPACE
