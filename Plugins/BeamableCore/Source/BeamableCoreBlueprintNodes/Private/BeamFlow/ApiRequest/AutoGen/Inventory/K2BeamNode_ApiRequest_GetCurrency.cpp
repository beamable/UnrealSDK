

#include "BeamableCoreBlueprintNodes/Public/BeamFlow/ApiRequest/AutoGen/Inventory/K2BeamNode_ApiRequest_GetCurrency.h"

#include "BeamK2.h"

#include "BeamableCore/Public/AutoGen/SubSystems/BeamInventoryApi.h"
#include "BeamableCore/Public/AutoGen/SubSystems/Inventory/GetCurrencyRequest.h"
#include "BeamableCore/Public/AutoGen/CurrencyContentResponse.h"

#define LOCTEXT_NAMESPACE "K2BeamNode_ApiRequest_GetCurrency"

using namespace BeamK2;

FName UK2BeamNode_ApiRequest_GetCurrency::GetSelfFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamInventoryApi, GetSelf);
}

FName UK2BeamNode_ApiRequest_GetCurrency::GetRequestFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamInventoryApi, GetCurrency);
}

FName UK2BeamNode_ApiRequest_GetCurrency::GetMakeFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UGetCurrencyRequest, Make);
}

FString UK2BeamNode_ApiRequest_GetCurrency::GetServiceName() const
{
	return TEXT("Inventory");
}

FString UK2BeamNode_ApiRequest_GetCurrency::GetEndpointName() const
{
	return TEXT("GetCurrency");
}

UClass* UK2BeamNode_ApiRequest_GetCurrency::GetApiClass() const
{
	return UBeamInventoryApi::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_GetCurrency::GetRequestClass() const
{
	return UGetCurrencyRequest::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_GetCurrency::GetResponseClass() const
{
	return UCurrencyContentResponse::StaticClass();
}

FString UK2BeamNode_ApiRequest_GetCurrency::GetRequestSuccessDelegateName() const
{
	return TEXT("OnGetCurrencySuccess");
}

FString UK2BeamNode_ApiRequest_GetCurrency::GetRequestErrorDelegateName() const
{
	return TEXT("OnGetCurrencyError");
}

FString UK2BeamNode_ApiRequest_GetCurrency::GetRequestCompleteDelegateName() const
{
	return TEXT("OnGetCurrencyComplete");
}

#undef LOCTEXT_NAMESPACE
