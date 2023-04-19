

#include "BeamableCoreBlueprintNodes/Public/BeamFlow/ApiRequest/AutoGen/Payments/K2BeamNode_ApiRequest_PostSteamPurchaseBegin.h"

#include "BeamK2.h"

#include "BeamableCore/Public/AutoGen/SubSystems/BeamPaymentsApi.h"
#include "BeamableCore/Public/AutoGen/SubSystems/Payments/PostSteamPurchaseBeginRequest.h"
#include "BeamableCore/Public/AutoGen/BeginPurchaseResponse.h"

#define LOCTEXT_NAMESPACE "K2BeamNode_ApiRequest_PostSteamPurchaseBegin"

using namespace BeamK2;

FName UK2BeamNode_ApiRequest_PostSteamPurchaseBegin::GetSelfFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamPaymentsApi, GetSelf);
}

FName UK2BeamNode_ApiRequest_PostSteamPurchaseBegin::GetRequestFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamPaymentsApi, PostSteamPurchaseBegin);
}

FName UK2BeamNode_ApiRequest_PostSteamPurchaseBegin::GetMakeFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UPostSteamPurchaseBeginRequest, Make);
}

FString UK2BeamNode_ApiRequest_PostSteamPurchaseBegin::GetServiceName() const
{
	return TEXT("Payments");
}

FString UK2BeamNode_ApiRequest_PostSteamPurchaseBegin::GetEndpointName() const
{
	return TEXT("PostSteamPurchaseBegin");
}

UClass* UK2BeamNode_ApiRequest_PostSteamPurchaseBegin::GetApiClass() const
{
	return UBeamPaymentsApi::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_PostSteamPurchaseBegin::GetRequestClass() const
{
	return UPostSteamPurchaseBeginRequest::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_PostSteamPurchaseBegin::GetResponseClass() const
{
	return UBeginPurchaseResponse::StaticClass();
}

FString UK2BeamNode_ApiRequest_PostSteamPurchaseBegin::GetRequestSuccessDelegateName() const
{
	return TEXT("OnPostSteamPurchaseBeginSuccess");
}

FString UK2BeamNode_ApiRequest_PostSteamPurchaseBegin::GetRequestErrorDelegateName() const
{
	return TEXT("OnPostSteamPurchaseBeginError");
}

FString UK2BeamNode_ApiRequest_PostSteamPurchaseBegin::GetRequestCompleteDelegateName() const
{
	return TEXT("OnPostSteamPurchaseBeginComplete");
}

#undef LOCTEXT_NAMESPACE
