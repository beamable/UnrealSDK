

#include "BeamableCoreBlueprintNodes/Public/BeamFlow/ApiRequest/AutoGen/Payments/K2BeamNode_ApiRequest_GetItunesProduct.h"

#include "BeamK2.h"

#include "BeamableCore/Public/AutoGen/SubSystems/BeamPaymentsApi.h"
#include "BeamableCore/Public/AutoGen/SubSystems/Payments/GetItunesProductRequest.h"
#include "BeamableCore/Public/AutoGen/GetProductResponse.h"

#define LOCTEXT_NAMESPACE "K2BeamNode_ApiRequest_GetItunesProduct"

using namespace BeamK2;

FName UK2BeamNode_ApiRequest_GetItunesProduct::GetSelfFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamPaymentsApi, GetSelf);
}

FName UK2BeamNode_ApiRequest_GetItunesProduct::GetRequestFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamPaymentsApi, GetItunesProduct);
}

FName UK2BeamNode_ApiRequest_GetItunesProduct::GetMakeFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UGetItunesProductRequest, Make);
}

FString UK2BeamNode_ApiRequest_GetItunesProduct::GetServiceName() const
{
	return TEXT("Payments");
}

FString UK2BeamNode_ApiRequest_GetItunesProduct::GetEndpointName() const
{
	return TEXT("GetItunesProduct");
}

UClass* UK2BeamNode_ApiRequest_GetItunesProduct::GetApiClass() const
{
	return UBeamPaymentsApi::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_GetItunesProduct::GetRequestClass() const
{
	return UGetItunesProductRequest::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_GetItunesProduct::GetResponseClass() const
{
	return UGetProductResponse::StaticClass();
}

FString UK2BeamNode_ApiRequest_GetItunesProduct::GetRequestSuccessDelegateName() const
{
	return TEXT("OnGetItunesProductSuccess");
}

FString UK2BeamNode_ApiRequest_GetItunesProduct::GetRequestErrorDelegateName() const
{
	return TEXT("OnGetItunesProductError");
}

FString UK2BeamNode_ApiRequest_GetItunesProduct::GetRequestCompleteDelegateName() const
{
	return TEXT("OnGetItunesProductComplete");
}

#undef LOCTEXT_NAMESPACE
