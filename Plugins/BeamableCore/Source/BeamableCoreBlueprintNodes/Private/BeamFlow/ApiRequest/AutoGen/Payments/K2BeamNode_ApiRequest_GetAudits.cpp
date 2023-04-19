

#include "BeamableCoreBlueprintNodes/Public/BeamFlow/ApiRequest/AutoGen/Payments/K2BeamNode_ApiRequest_GetAudits.h"

#include "BeamK2.h"

#include "BeamableCore/Public/AutoGen/SubSystems/BeamPaymentsApi.h"
#include "BeamableCore/Public/AutoGen/SubSystems/Payments/GetAuditsRequest.h"
#include "BeamableCore/Public/AutoGen/ListAuditResponse.h"

#define LOCTEXT_NAMESPACE "K2BeamNode_ApiRequest_GetAudits"

using namespace BeamK2;

FName UK2BeamNode_ApiRequest_GetAudits::GetSelfFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamPaymentsApi, GetSelf);
}

FName UK2BeamNode_ApiRequest_GetAudits::GetRequestFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamPaymentsApi, GetAudits);
}

FName UK2BeamNode_ApiRequest_GetAudits::GetMakeFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UGetAuditsRequest, Make);
}

FString UK2BeamNode_ApiRequest_GetAudits::GetServiceName() const
{
	return TEXT("Payments");
}

FString UK2BeamNode_ApiRequest_GetAudits::GetEndpointName() const
{
	return TEXT("GetAudits");
}

UClass* UK2BeamNode_ApiRequest_GetAudits::GetApiClass() const
{
	return UBeamPaymentsApi::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_GetAudits::GetRequestClass() const
{
	return UGetAuditsRequest::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_GetAudits::GetResponseClass() const
{
	return UListAuditResponse::StaticClass();
}

FString UK2BeamNode_ApiRequest_GetAudits::GetRequestSuccessDelegateName() const
{
	return TEXT("OnGetAuditsSuccess");
}

FString UK2BeamNode_ApiRequest_GetAudits::GetRequestErrorDelegateName() const
{
	return TEXT("OnGetAuditsError");
}

FString UK2BeamNode_ApiRequest_GetAudits::GetRequestCompleteDelegateName() const
{
	return TEXT("OnGetAuditsComplete");
}

#undef LOCTEXT_NAMESPACE
