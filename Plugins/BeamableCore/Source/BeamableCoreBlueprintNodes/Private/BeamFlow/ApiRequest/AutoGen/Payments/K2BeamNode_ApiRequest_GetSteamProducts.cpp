

#include "BeamableCoreBlueprintNodes/Public/BeamFlow/ApiRequest/AutoGen/Payments/K2BeamNode_ApiRequest_GetSteamProducts.h"

#include "BeamK2.h"

#include "BeamableCore/Public/AutoGen/SubSystems/BeamPaymentsApi.h"
#include "BeamableCore/Public/AutoGen/SubSystems/Payments/GetSteamProductsRequest.h"
#include "BeamableCore/Public/AutoGen/GetProductsResponse.h"

#define LOCTEXT_NAMESPACE "K2BeamNode_ApiRequest_GetSteamProducts"

using namespace BeamK2;

FName UK2BeamNode_ApiRequest_GetSteamProducts::GetSelfFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamPaymentsApi, GetSelf);
}

FName UK2BeamNode_ApiRequest_GetSteamProducts::GetRequestFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamPaymentsApi, GetSteamProducts);
}

FName UK2BeamNode_ApiRequest_GetSteamProducts::GetMakeFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UGetSteamProductsRequest, Make);
}

FString UK2BeamNode_ApiRequest_GetSteamProducts::GetServiceName() const
{
	return TEXT("Payments");
}

FString UK2BeamNode_ApiRequest_GetSteamProducts::GetEndpointName() const
{
	return TEXT("GetSteamProducts");
}

UClass* UK2BeamNode_ApiRequest_GetSteamProducts::GetApiClass() const
{
	return UBeamPaymentsApi::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_GetSteamProducts::GetRequestClass() const
{
	return UGetSteamProductsRequest::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_GetSteamProducts::GetResponseClass() const
{
	return UGetProductsResponse::StaticClass();
}

FString UK2BeamNode_ApiRequest_GetSteamProducts::GetRequestSuccessDelegateName() const
{
	return TEXT("OnGetSteamProductsSuccess");
}

FString UK2BeamNode_ApiRequest_GetSteamProducts::GetRequestErrorDelegateName() const
{
	return TEXT("OnGetSteamProductsError");
}

FString UK2BeamNode_ApiRequest_GetSteamProducts::GetRequestCompleteDelegateName() const
{
	return TEXT("OnGetSteamProductsComplete");
}

#undef LOCTEXT_NAMESPACE
