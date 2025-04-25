

#include "BeamableCoreBlueprintNodes/Public/BeamFlow/ApiRequest/AutoGen/Realms/K2BeamNode_ApiRequest_GetCustomerActivate.h"

#include "BeamK2.h"

#include "BeamableCore/Public/AutoGen/SubSystems/BeamRealmsApi.h"
#include "BeamableCore/Public/AutoGen/SubSystems/Realms/GetCustomerActivateRequest.h"
#include "Serialization/BeamPlainTextResponseBody.h"

#define LOCTEXT_NAMESPACE "K2BeamNode_ApiRequest_GetCustomerActivate"

using namespace BeamK2;

FName UK2BeamNode_ApiRequest_GetCustomerActivate::GetSelfFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamRealmsApi, GetSelf);
}

FName UK2BeamNode_ApiRequest_GetCustomerActivate::GetRequestFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamRealmsApi, GetCustomerActivate);
}

FName UK2BeamNode_ApiRequest_GetCustomerActivate::GetMakeFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UGetCustomerActivateRequest, Make);
}

FString UK2BeamNode_ApiRequest_GetCustomerActivate::GetServiceName() const
{
	return TEXT("Realms");
}

FString UK2BeamNode_ApiRequest_GetCustomerActivate::GetEndpointName() const
{
	return TEXT("GetCustomerActivate");
}

UClass* UK2BeamNode_ApiRequest_GetCustomerActivate::GetApiClass() const
{
	return UBeamRealmsApi::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_GetCustomerActivate::GetRequestClass() const
{
	return UGetCustomerActivateRequest::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_GetCustomerActivate::GetResponseClass() const
{
	return UBeamPlainTextResponseBody::StaticClass();
}

FString UK2BeamNode_ApiRequest_GetCustomerActivate::GetRequestSuccessDelegateName() const
{
	return TEXT("OnGetCustomerActivateSuccess");
}

FString UK2BeamNode_ApiRequest_GetCustomerActivate::GetRequestErrorDelegateName() const
{
	return TEXT("OnGetCustomerActivateError");
}

FString UK2BeamNode_ApiRequest_GetCustomerActivate::GetRequestCompleteDelegateName() const
{
	return TEXT("OnGetCustomerActivateComplete");
}

#undef LOCTEXT_NAMESPACE
