

#include "BeamFlow/ApiRequest/AutoGen/Payments/K2BeamNode_ApiRequest_PostGoogleplayPurchaseBegin.h"

#include "BeamK2.h"

#include "AutoGen/SubSystems/BeamPaymentsApi.h"
#include "AutoGen/SubSystems/Payments/PostGoogleplayPurchaseBeginRequest.h"
#include "AutoGen/BeginPurchaseResponse.h"

#define LOCTEXT_NAMESPACE "K2BeamNode_ApiRequest_PostGoogleplayPurchaseBegin"

using namespace BeamK2;

FName UK2BeamNode_ApiRequest_PostGoogleplayPurchaseBegin::GetSelfFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamPaymentsApi, GetSelf);
}

FName UK2BeamNode_ApiRequest_PostGoogleplayPurchaseBegin::GetRequestFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamPaymentsApi, PostGoogleplayPurchaseBegin);
}

FName UK2BeamNode_ApiRequest_PostGoogleplayPurchaseBegin::GetMakeFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UPostGoogleplayPurchaseBeginRequest, Make);
}

FString UK2BeamNode_ApiRequest_PostGoogleplayPurchaseBegin::GetServiceName() const
{
	return TEXT("Payments");
}

FString UK2BeamNode_ApiRequest_PostGoogleplayPurchaseBegin::GetEndpointName() const
{
	return TEXT("PostGoogleplayPurchaseBegin");
}

UClass* UK2BeamNode_ApiRequest_PostGoogleplayPurchaseBegin::GetApiClass() const
{
	return UBeamPaymentsApi::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_PostGoogleplayPurchaseBegin::GetRequestClass() const
{
	return UPostGoogleplayPurchaseBeginRequest::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_PostGoogleplayPurchaseBegin::GetResponseClass() const
{
	return UBeginPurchaseResponse::StaticClass();
}

FString UK2BeamNode_ApiRequest_PostGoogleplayPurchaseBegin::GetRequestSuccessDelegateName() const
{
	return TEXT("OnPostGoogleplayPurchaseBeginSuccess");
}

FString UK2BeamNode_ApiRequest_PostGoogleplayPurchaseBegin::GetRequestErrorDelegateName() const
{
	return TEXT("OnPostGoogleplayPurchaseBeginError");
}

FString UK2BeamNode_ApiRequest_PostGoogleplayPurchaseBegin::GetRequestCompleteDelegateName() const
{
	return TEXT("OnPostGoogleplayPurchaseBeginComplete");
}

#undef LOCTEXT_NAMESPACE
