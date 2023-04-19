

#include "BeamableCoreBlueprintNodes/Public/BeamFlow/ApiRequest/AutoGen/Payments/K2BeamNode_ApiRequest_GetSteamPrices.h"

#include "BeamK2.h"

#include "BeamableCore/Public/AutoGen/SubSystems/BeamPaymentsApi.h"
#include "BeamableCore/Public/AutoGen/SubSystems/Payments/GetSteamPricesRequest.h"
#include "BeamableCore/Public/AutoGen/LocalizedPriceMap.h"

#define LOCTEXT_NAMESPACE "K2BeamNode_ApiRequest_GetSteamPrices"

using namespace BeamK2;

FName UK2BeamNode_ApiRequest_GetSteamPrices::GetSelfFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamPaymentsApi, GetSelf);
}

FName UK2BeamNode_ApiRequest_GetSteamPrices::GetRequestFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamPaymentsApi, GetSteamPrices);
}

FName UK2BeamNode_ApiRequest_GetSteamPrices::GetMakeFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UGetSteamPricesRequest, Make);
}

FString UK2BeamNode_ApiRequest_GetSteamPrices::GetServiceName() const
{
	return TEXT("Payments");
}

FString UK2BeamNode_ApiRequest_GetSteamPrices::GetEndpointName() const
{
	return TEXT("GetSteamPrices");
}

UClass* UK2BeamNode_ApiRequest_GetSteamPrices::GetApiClass() const
{
	return UBeamPaymentsApi::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_GetSteamPrices::GetRequestClass() const
{
	return UGetSteamPricesRequest::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_GetSteamPrices::GetResponseClass() const
{
	return ULocalizedPriceMap::StaticClass();
}

FString UK2BeamNode_ApiRequest_GetSteamPrices::GetRequestSuccessDelegateName() const
{
	return TEXT("OnGetSteamPricesSuccess");
}

FString UK2BeamNode_ApiRequest_GetSteamPrices::GetRequestErrorDelegateName() const
{
	return TEXT("OnGetSteamPricesError");
}

FString UK2BeamNode_ApiRequest_GetSteamPrices::GetRequestCompleteDelegateName() const
{
	return TEXT("OnGetSteamPricesComplete");
}

#undef LOCTEXT_NAMESPACE
