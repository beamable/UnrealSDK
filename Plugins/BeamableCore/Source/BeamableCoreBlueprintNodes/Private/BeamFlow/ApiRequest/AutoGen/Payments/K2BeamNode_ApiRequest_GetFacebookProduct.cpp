

#include "BeamableCoreBlueprintNodes/Public/BeamFlow/ApiRequest/AutoGen/Payments/K2BeamNode_ApiRequest_GetFacebookProduct.h"

#include "BeamK2.h"

#include "BeamableCore/Public/AutoGen/SubSystems/BeamPaymentsApi.h"
#include "BeamableCore/Public/AutoGen/SubSystems/Payments/GetFacebookProductRequest.h"
#include "BeamableCore/Public/AutoGen/GetProductResponse.h"

#define LOCTEXT_NAMESPACE "K2BeamNode_ApiRequest_GetFacebookProduct"

using namespace BeamK2;

FName UK2BeamNode_ApiRequest_GetFacebookProduct::GetSelfFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamPaymentsApi, GetSelf);
}

FName UK2BeamNode_ApiRequest_GetFacebookProduct::GetRequestFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamPaymentsApi, GetFacebookProduct);
}

FName UK2BeamNode_ApiRequest_GetFacebookProduct::GetMakeFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UGetFacebookProductRequest, Make);
}

FString UK2BeamNode_ApiRequest_GetFacebookProduct::GetServiceName() const
{
	return TEXT("Payments");
}

FString UK2BeamNode_ApiRequest_GetFacebookProduct::GetEndpointName() const
{
	return TEXT("GetFacebookProduct");
}

UClass* UK2BeamNode_ApiRequest_GetFacebookProduct::GetApiClass() const
{
	return UBeamPaymentsApi::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_GetFacebookProduct::GetRequestClass() const
{
	return UGetFacebookProductRequest::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_GetFacebookProduct::GetResponseClass() const
{
	return UGetProductResponse::StaticClass();
}

FString UK2BeamNode_ApiRequest_GetFacebookProduct::GetRequestSuccessDelegateName() const
{
	return TEXT("OnGetFacebookProductSuccess");
}

FString UK2BeamNode_ApiRequest_GetFacebookProduct::GetRequestErrorDelegateName() const
{
	return TEXT("OnGetFacebookProductError");
}

FString UK2BeamNode_ApiRequest_GetFacebookProduct::GetRequestCompleteDelegateName() const
{
	return TEXT("OnGetFacebookProductComplete");
}

#undef LOCTEXT_NAMESPACE
