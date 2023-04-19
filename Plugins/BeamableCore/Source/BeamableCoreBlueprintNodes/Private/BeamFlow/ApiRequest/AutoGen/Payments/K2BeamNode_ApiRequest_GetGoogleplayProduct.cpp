

#include "BeamableCoreBlueprintNodes/Public/BeamFlow/ApiRequest/AutoGen/Payments/K2BeamNode_ApiRequest_GetGoogleplayProduct.h"

#include "BeamK2.h"

#include "BeamableCore/Public/AutoGen/SubSystems/BeamPaymentsApi.h"
#include "BeamableCore/Public/AutoGen/SubSystems/Payments/GetGoogleplayProductRequest.h"
#include "BeamableCore/Public/AutoGen/GetProductResponse.h"

#define LOCTEXT_NAMESPACE "K2BeamNode_ApiRequest_GetGoogleplayProduct"

using namespace BeamK2;

FName UK2BeamNode_ApiRequest_GetGoogleplayProduct::GetSelfFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamPaymentsApi, GetSelf);
}

FName UK2BeamNode_ApiRequest_GetGoogleplayProduct::GetRequestFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamPaymentsApi, GetGoogleplayProduct);
}

FName UK2BeamNode_ApiRequest_GetGoogleplayProduct::GetMakeFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UGetGoogleplayProductRequest, Make);
}

FString UK2BeamNode_ApiRequest_GetGoogleplayProduct::GetServiceName() const
{
	return TEXT("Payments");
}

FString UK2BeamNode_ApiRequest_GetGoogleplayProduct::GetEndpointName() const
{
	return TEXT("GetGoogleplayProduct");
}

UClass* UK2BeamNode_ApiRequest_GetGoogleplayProduct::GetApiClass() const
{
	return UBeamPaymentsApi::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_GetGoogleplayProduct::GetRequestClass() const
{
	return UGetGoogleplayProductRequest::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_GetGoogleplayProduct::GetResponseClass() const
{
	return UGetProductResponse::StaticClass();
}

FString UK2BeamNode_ApiRequest_GetGoogleplayProduct::GetRequestSuccessDelegateName() const
{
	return TEXT("OnGetGoogleplayProductSuccess");
}

FString UK2BeamNode_ApiRequest_GetGoogleplayProduct::GetRequestErrorDelegateName() const
{
	return TEXT("OnGetGoogleplayProductError");
}

FString UK2BeamNode_ApiRequest_GetGoogleplayProduct::GetRequestCompleteDelegateName() const
{
	return TEXT("OnGetGoogleplayProductComplete");
}

#undef LOCTEXT_NAMESPACE
