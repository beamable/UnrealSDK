

#include "BeamableCoreBlueprintNodes/Public/BeamFlow/ApiRequest/AutoGen/Accounts/K2BeamNode_ApiRequest_GetAvailable.h"

#include "BeamK2.h"

#include "BeamableCore/Public/AutoGen/SubSystems/BeamAccountsApi.h"
#include "BeamableCore/Public/AutoGen/SubSystems/Accounts/GetAvailableRequest.h"
#include "BeamableCore/Public/AutoGen/AccountAvailableResponse.h"

#define LOCTEXT_NAMESPACE "K2BeamNode_ApiRequest_GetAvailable"

using namespace BeamK2;

FName UK2BeamNode_ApiRequest_GetAvailable::GetSelfFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamAccountsApi, GetSelf);
}

FName UK2BeamNode_ApiRequest_GetAvailable::GetRequestFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamAccountsApi, GetAvailable);
}

FName UK2BeamNode_ApiRequest_GetAvailable::GetMakeFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UGetAvailableRequest, Make);
}

FString UK2BeamNode_ApiRequest_GetAvailable::GetServiceName() const
{
	return TEXT("Accounts");
}

FString UK2BeamNode_ApiRequest_GetAvailable::GetEndpointName() const
{
	return TEXT("GetAvailable");
}

UClass* UK2BeamNode_ApiRequest_GetAvailable::GetApiClass() const
{
	return UBeamAccountsApi::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_GetAvailable::GetRequestClass() const
{
	return UGetAvailableRequest::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_GetAvailable::GetResponseClass() const
{
	return UAccountAvailableResponse::StaticClass();
}

FString UK2BeamNode_ApiRequest_GetAvailable::GetRequestSuccessDelegateName() const
{
	return TEXT("OnGetAvailableSuccess");
}

FString UK2BeamNode_ApiRequest_GetAvailable::GetRequestErrorDelegateName() const
{
	return TEXT("OnGetAvailableError");
}

FString UK2BeamNode_ApiRequest_GetAvailable::GetRequestCompleteDelegateName() const
{
	return TEXT("OnGetAvailableComplete");
}

#undef LOCTEXT_NAMESPACE
