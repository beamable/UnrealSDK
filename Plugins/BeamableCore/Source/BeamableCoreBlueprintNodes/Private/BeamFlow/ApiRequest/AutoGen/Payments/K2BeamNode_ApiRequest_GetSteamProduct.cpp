

#include "BeamableCoreBlueprintNodes/Public/BeamFlow/ApiRequest/AutoGen/Payments/K2BeamNode_ApiRequest_GetSteamProduct.h"

#include "BeamK2.h"

#include "BeamableCore/Public/AutoGen/SubSystems/BeamPaymentsApi.h"
#include "BeamableCore/Public/AutoGen/SubSystems/Payments/GetSteamProductRequest.h"
#include "BeamableCore/Public/AutoGen/GetProductResponse.h"

#define LOCTEXT_NAMESPACE "K2BeamNode_ApiRequest_GetSteamProduct"

using namespace BeamK2;

FName UK2BeamNode_ApiRequest_GetSteamProduct::GetSelfFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamPaymentsApi, GetSelf);
}

FName UK2BeamNode_ApiRequest_GetSteamProduct::GetRequestFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamPaymentsApi, GetSteamProduct);
}

FName UK2BeamNode_ApiRequest_GetSteamProduct::GetMakeFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UGetSteamProductRequest, Make);
}

FString UK2BeamNode_ApiRequest_GetSteamProduct::GetServiceName() const
{
	return TEXT("Payments");
}

FString UK2BeamNode_ApiRequest_GetSteamProduct::GetEndpointName() const
{
	return TEXT("GetSteamProduct");
}

UClass* UK2BeamNode_ApiRequest_GetSteamProduct::GetApiClass() const
{
	return UBeamPaymentsApi::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_GetSteamProduct::GetRequestClass() const
{
	return UGetSteamProductRequest::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_GetSteamProduct::GetResponseClass() const
{
	return UGetProductResponse::StaticClass();
}

FString UK2BeamNode_ApiRequest_GetSteamProduct::GetRequestSuccessDelegateName() const
{
	return TEXT("OnGetSteamProductSuccess");
}

FString UK2BeamNode_ApiRequest_GetSteamProduct::GetRequestErrorDelegateName() const
{
	return TEXT("OnGetSteamProductError");
}

FString UK2BeamNode_ApiRequest_GetSteamProduct::GetRequestCompleteDelegateName() const
{
	return TEXT("OnGetSteamProductComplete");
}

#undef LOCTEXT_NAMESPACE
