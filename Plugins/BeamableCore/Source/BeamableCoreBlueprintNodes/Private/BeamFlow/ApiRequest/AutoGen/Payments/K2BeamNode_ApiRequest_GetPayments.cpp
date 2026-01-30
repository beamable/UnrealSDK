

#include "BeamableCoreBlueprintNodes/Public/BeamFlow/ApiRequest/AutoGen/Payments/K2BeamNode_ApiRequest_GetPayments.h"

#include "BeamK2.h"

#include "BeamableCore/Public/AutoGen/SubSystems/BeamPaymentsApi.h"
#include "BeamableCore/Public/AutoGen/SubSystems/Payments/GetPaymentsRequest.h"
#include "BeamableCore/Public/AutoGen/CommonResponse.h"

#define LOCTEXT_NAMESPACE "K2BeamNode_ApiRequest_GetPayments"

using namespace BeamK2;

FName UK2BeamNode_ApiRequest_GetPayments::GetSelfFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamPaymentsApi, GetSelf);
}

FName UK2BeamNode_ApiRequest_GetPayments::GetRequestFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamPaymentsApi, GetPayments);
}

FName UK2BeamNode_ApiRequest_GetPayments::GetMakeFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UGetPaymentsRequest, Make);
}

FString UK2BeamNode_ApiRequest_GetPayments::GetServiceName() const
{
	return TEXT("Payments");
}

FString UK2BeamNode_ApiRequest_GetPayments::GetEndpointName() const
{
	return TEXT("GetPayments");
}

UClass* UK2BeamNode_ApiRequest_GetPayments::GetApiClass() const
{
	return UBeamPaymentsApi::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_GetPayments::GetRequestClass() const
{
	return UGetPaymentsRequest::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_GetPayments::GetResponseClass() const
{
	return UCommonResponse::StaticClass();
}

FString UK2BeamNode_ApiRequest_GetPayments::GetRequestSuccessDelegateName() const
{
	return TEXT("OnGetPaymentsSuccess");
}

FString UK2BeamNode_ApiRequest_GetPayments::GetRequestErrorDelegateName() const
{
	return TEXT("OnGetPaymentsError");
}

FString UK2BeamNode_ApiRequest_GetPayments::GetRequestCompleteDelegateName() const
{
	return TEXT("OnGetPaymentsComplete");
}

#undef LOCTEXT_NAMESPACE
