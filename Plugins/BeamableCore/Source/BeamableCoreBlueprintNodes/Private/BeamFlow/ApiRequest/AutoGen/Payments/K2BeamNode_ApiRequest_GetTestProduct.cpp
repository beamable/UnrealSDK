

#include "BeamableCoreBlueprintNodes/Public/BeamFlow/ApiRequest/AutoGen/Payments/K2BeamNode_ApiRequest_GetTestProduct.h"

#include "BeamK2.h"

#include "BeamableCore/Public/AutoGen/SubSystems/BeamPaymentsApi.h"
#include "BeamableCore/Public/AutoGen/SubSystems/Payments/GetTestProductRequest.h"
#include "BeamableCore/Public/AutoGen/GetProductResponse.h"

#define LOCTEXT_NAMESPACE "K2BeamNode_ApiRequest_GetTestProduct"

using namespace BeamK2;

FName UK2BeamNode_ApiRequest_GetTestProduct::GetSelfFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamPaymentsApi, GetSelf);
}

FName UK2BeamNode_ApiRequest_GetTestProduct::GetRequestFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamPaymentsApi, GetTestProduct);
}

FName UK2BeamNode_ApiRequest_GetTestProduct::GetMakeFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UGetTestProductRequest, Make);
}

FString UK2BeamNode_ApiRequest_GetTestProduct::GetServiceName() const
{
	return TEXT("Payments");
}

FString UK2BeamNode_ApiRequest_GetTestProduct::GetEndpointName() const
{
	return TEXT("GetTestProduct");
}

UClass* UK2BeamNode_ApiRequest_GetTestProduct::GetApiClass() const
{
	return UBeamPaymentsApi::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_GetTestProduct::GetRequestClass() const
{
	return UGetTestProductRequest::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_GetTestProduct::GetResponseClass() const
{
	return UGetProductResponse::StaticClass();
}

FString UK2BeamNode_ApiRequest_GetTestProduct::GetRequestSuccessDelegateName() const
{
	return TEXT("OnGetTestProductSuccess");
}

FString UK2BeamNode_ApiRequest_GetTestProduct::GetRequestErrorDelegateName() const
{
	return TEXT("OnGetTestProductError");
}

FString UK2BeamNode_ApiRequest_GetTestProduct::GetRequestCompleteDelegateName() const
{
	return TEXT("OnGetTestProductComplete");
}

#undef LOCTEXT_NAMESPACE
