

#include "BeamableCoreBlueprintNodes/Public/BeamFlow/ApiRequest/AutoGen/Payments/K2BeamNode_ApiRequest_PostItunesPurchaseBegin.h"

#include "BeamK2.h"

#include "BeamableCore/Public/AutoGen/SubSystems/BeamPaymentsApi.h"
#include "BeamableCore/Public/AutoGen/SubSystems/Payments/PostItunesPurchaseBeginRequest.h"
#include "BeamableCore/Public/AutoGen/BeginPurchaseResponse.h"

#define LOCTEXT_NAMESPACE "K2BeamNode_ApiRequest_PostItunesPurchaseBegin"

using namespace BeamK2;

FName UK2BeamNode_ApiRequest_PostItunesPurchaseBegin::GetSelfFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamPaymentsApi, GetSelf);
}

FName UK2BeamNode_ApiRequest_PostItunesPurchaseBegin::GetRequestFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamPaymentsApi, PostItunesPurchaseBegin);
}

FName UK2BeamNode_ApiRequest_PostItunesPurchaseBegin::GetMakeFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UPostItunesPurchaseBeginRequest, Make);
}

FString UK2BeamNode_ApiRequest_PostItunesPurchaseBegin::GetServiceName() const
{
	return TEXT("Payments");
}

FString UK2BeamNode_ApiRequest_PostItunesPurchaseBegin::GetEndpointName() const
{
	return TEXT("PostItunesPurchaseBegin");
}

UClass* UK2BeamNode_ApiRequest_PostItunesPurchaseBegin::GetApiClass() const
{
	return UBeamPaymentsApi::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_PostItunesPurchaseBegin::GetRequestClass() const
{
	return UPostItunesPurchaseBeginRequest::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_PostItunesPurchaseBegin::GetResponseClass() const
{
	return UBeginPurchaseResponse::StaticClass();
}

FString UK2BeamNode_ApiRequest_PostItunesPurchaseBegin::GetRequestSuccessDelegateName() const
{
	return TEXT("OnPostItunesPurchaseBeginSuccess");
}

FString UK2BeamNode_ApiRequest_PostItunesPurchaseBegin::GetRequestErrorDelegateName() const
{
	return TEXT("OnPostItunesPurchaseBeginError");
}

FString UK2BeamNode_ApiRequest_PostItunesPurchaseBegin::GetRequestCompleteDelegateName() const
{
	return TEXT("OnPostItunesPurchaseBeginComplete");
}

#undef LOCTEXT_NAMESPACE
