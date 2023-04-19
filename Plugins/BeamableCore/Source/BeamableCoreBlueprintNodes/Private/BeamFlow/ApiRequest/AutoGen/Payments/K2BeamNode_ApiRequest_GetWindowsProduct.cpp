

#include "BeamableCoreBlueprintNodes/Public/BeamFlow/ApiRequest/AutoGen/Payments/K2BeamNode_ApiRequest_GetWindowsProduct.h"

#include "BeamK2.h"

#include "BeamableCore/Public/AutoGen/SubSystems/BeamPaymentsApi.h"
#include "BeamableCore/Public/AutoGen/SubSystems/Payments/GetWindowsProductRequest.h"
#include "BeamableCore/Public/AutoGen/GetProductResponse.h"

#define LOCTEXT_NAMESPACE "K2BeamNode_ApiRequest_GetWindowsProduct"

using namespace BeamK2;

FName UK2BeamNode_ApiRequest_GetWindowsProduct::GetSelfFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamPaymentsApi, GetSelf);
}

FName UK2BeamNode_ApiRequest_GetWindowsProduct::GetRequestFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamPaymentsApi, GetWindowsProduct);
}

FName UK2BeamNode_ApiRequest_GetWindowsProduct::GetMakeFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UGetWindowsProductRequest, Make);
}

FString UK2BeamNode_ApiRequest_GetWindowsProduct::GetServiceName() const
{
	return TEXT("Payments");
}

FString UK2BeamNode_ApiRequest_GetWindowsProduct::GetEndpointName() const
{
	return TEXT("GetWindowsProduct");
}

UClass* UK2BeamNode_ApiRequest_GetWindowsProduct::GetApiClass() const
{
	return UBeamPaymentsApi::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_GetWindowsProduct::GetRequestClass() const
{
	return UGetWindowsProductRequest::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_GetWindowsProduct::GetResponseClass() const
{
	return UGetProductResponse::StaticClass();
}

FString UK2BeamNode_ApiRequest_GetWindowsProduct::GetRequestSuccessDelegateName() const
{
	return TEXT("OnGetWindowsProductSuccess");
}

FString UK2BeamNode_ApiRequest_GetWindowsProduct::GetRequestErrorDelegateName() const
{
	return TEXT("OnGetWindowsProductError");
}

FString UK2BeamNode_ApiRequest_GetWindowsProduct::GetRequestCompleteDelegateName() const
{
	return TEXT("OnGetWindowsProductComplete");
}

#undef LOCTEXT_NAMESPACE
