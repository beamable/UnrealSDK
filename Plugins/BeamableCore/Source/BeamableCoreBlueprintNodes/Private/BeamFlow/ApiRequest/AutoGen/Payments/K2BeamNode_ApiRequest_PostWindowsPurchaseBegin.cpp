

#include "BeamableCoreBlueprintNodes/Public/BeamFlow/ApiRequest/AutoGen/Payments/K2BeamNode_ApiRequest_PostWindowsPurchaseBegin.h"

#include "BeamK2.h"

#include "BeamableCore/Public/AutoGen/SubSystems/BeamPaymentsApi.h"
#include "BeamableCore/Public/AutoGen/SubSystems/Payments/PostWindowsPurchaseBeginRequest.h"
#include "BeamableCore/Public/AutoGen/BeginPurchaseResponse.h"

#define LOCTEXT_NAMESPACE "K2BeamNode_ApiRequest_PostWindowsPurchaseBegin"

using namespace BeamK2;

FName UK2BeamNode_ApiRequest_PostWindowsPurchaseBegin::GetSelfFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamPaymentsApi, GetSelf);
}

FName UK2BeamNode_ApiRequest_PostWindowsPurchaseBegin::GetRequestFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamPaymentsApi, PostWindowsPurchaseBegin);
}

FName UK2BeamNode_ApiRequest_PostWindowsPurchaseBegin::GetMakeFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UPostWindowsPurchaseBeginRequest, Make);
}

FString UK2BeamNode_ApiRequest_PostWindowsPurchaseBegin::GetServiceName() const
{
	return TEXT("Payments");
}

FString UK2BeamNode_ApiRequest_PostWindowsPurchaseBegin::GetEndpointName() const
{
	return TEXT("PostWindowsPurchaseBegin");
}

UClass* UK2BeamNode_ApiRequest_PostWindowsPurchaseBegin::GetApiClass() const
{
	return UBeamPaymentsApi::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_PostWindowsPurchaseBegin::GetRequestClass() const
{
	return UPostWindowsPurchaseBeginRequest::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_PostWindowsPurchaseBegin::GetResponseClass() const
{
	return UBeginPurchaseResponse::StaticClass();
}

FString UK2BeamNode_ApiRequest_PostWindowsPurchaseBegin::GetRequestSuccessDelegateName() const
{
	return TEXT("OnPostWindowsPurchaseBeginSuccess");
}

FString UK2BeamNode_ApiRequest_PostWindowsPurchaseBegin::GetRequestErrorDelegateName() const
{
	return TEXT("OnPostWindowsPurchaseBeginError");
}

FString UK2BeamNode_ApiRequest_PostWindowsPurchaseBegin::GetRequestCompleteDelegateName() const
{
	return TEXT("OnPostWindowsPurchaseBeginComplete");
}

#undef LOCTEXT_NAMESPACE
