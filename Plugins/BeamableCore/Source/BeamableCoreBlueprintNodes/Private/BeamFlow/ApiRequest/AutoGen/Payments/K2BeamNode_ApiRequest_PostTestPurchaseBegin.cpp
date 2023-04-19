

#include "BeamableCoreBlueprintNodes/Public/BeamFlow/ApiRequest/AutoGen/Payments/K2BeamNode_ApiRequest_PostTestPurchaseBegin.h"

#include "BeamK2.h"

#include "BeamableCore/Public/AutoGen/SubSystems/BeamPaymentsApi.h"
#include "BeamableCore/Public/AutoGen/SubSystems/Payments/PostTestPurchaseBeginRequest.h"
#include "BeamableCore/Public/AutoGen/BeginPurchaseResponse.h"

#define LOCTEXT_NAMESPACE "K2BeamNode_ApiRequest_PostTestPurchaseBegin"

using namespace BeamK2;

FName UK2BeamNode_ApiRequest_PostTestPurchaseBegin::GetSelfFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamPaymentsApi, GetSelf);
}

FName UK2BeamNode_ApiRequest_PostTestPurchaseBegin::GetRequestFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamPaymentsApi, PostTestPurchaseBegin);
}

FName UK2BeamNode_ApiRequest_PostTestPurchaseBegin::GetMakeFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UPostTestPurchaseBeginRequest, Make);
}

FString UK2BeamNode_ApiRequest_PostTestPurchaseBegin::GetServiceName() const
{
	return TEXT("Payments");
}

FString UK2BeamNode_ApiRequest_PostTestPurchaseBegin::GetEndpointName() const
{
	return TEXT("PostTestPurchaseBegin");
}

UClass* UK2BeamNode_ApiRequest_PostTestPurchaseBegin::GetApiClass() const
{
	return UBeamPaymentsApi::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_PostTestPurchaseBegin::GetRequestClass() const
{
	return UPostTestPurchaseBeginRequest::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_PostTestPurchaseBegin::GetResponseClass() const
{
	return UBeginPurchaseResponse::StaticClass();
}

FString UK2BeamNode_ApiRequest_PostTestPurchaseBegin::GetRequestSuccessDelegateName() const
{
	return TEXT("OnPostTestPurchaseBeginSuccess");
}

FString UK2BeamNode_ApiRequest_PostTestPurchaseBegin::GetRequestErrorDelegateName() const
{
	return TEXT("OnPostTestPurchaseBeginError");
}

FString UK2BeamNode_ApiRequest_PostTestPurchaseBegin::GetRequestCompleteDelegateName() const
{
	return TEXT("OnPostTestPurchaseBeginComplete");
}

#undef LOCTEXT_NAMESPACE
