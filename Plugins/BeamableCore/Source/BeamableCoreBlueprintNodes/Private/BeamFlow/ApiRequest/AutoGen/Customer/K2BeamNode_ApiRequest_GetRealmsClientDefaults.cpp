

#include "BeamableCoreBlueprintNodes/Public/BeamFlow/ApiRequest/AutoGen/Customer/K2BeamNode_ApiRequest_GetRealmsClientDefaults.h"

#include "BeamK2.h"

#include "BeamableCore/Public/AutoGen/SubSystems/BeamCustomerApi.h"
#include "BeamableCore/Public/AutoGen/SubSystems/Customer/GetRealmsClientDefaultsRequest.h"
#include "BeamableCore/Public/AutoGen/CustomerActorRealmConfiguration.h"

#define LOCTEXT_NAMESPACE "K2BeamNode_ApiRequest_GetRealmsClientDefaults"

using namespace BeamK2;

FName UK2BeamNode_ApiRequest_GetRealmsClientDefaults::GetSelfFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamCustomerApi, GetSelf);
}

FName UK2BeamNode_ApiRequest_GetRealmsClientDefaults::GetRequestFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamCustomerApi, GetRealmsClientDefaults);
}

FName UK2BeamNode_ApiRequest_GetRealmsClientDefaults::GetMakeFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UGetRealmsClientDefaultsRequest, Make);
}

FString UK2BeamNode_ApiRequest_GetRealmsClientDefaults::GetServiceName() const
{
	return TEXT("Customer");
}

FString UK2BeamNode_ApiRequest_GetRealmsClientDefaults::GetEndpointName() const
{
	return TEXT("GetRealmsClientDefaults");
}

UClass* UK2BeamNode_ApiRequest_GetRealmsClientDefaults::GetApiClass() const
{
	return UBeamCustomerApi::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_GetRealmsClientDefaults::GetRequestClass() const
{
	return UGetRealmsClientDefaultsRequest::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_GetRealmsClientDefaults::GetResponseClass() const
{
	return UCustomerActorRealmConfiguration::StaticClass();
}

FString UK2BeamNode_ApiRequest_GetRealmsClientDefaults::GetRequestSuccessDelegateName() const
{
	return TEXT("OnGetRealmsClientDefaultsSuccess");
}

FString UK2BeamNode_ApiRequest_GetRealmsClientDefaults::GetRequestErrorDelegateName() const
{
	return TEXT("OnGetRealmsClientDefaultsError");
}

FString UK2BeamNode_ApiRequest_GetRealmsClientDefaults::GetRequestCompleteDelegateName() const
{
	return TEXT("OnGetRealmsClientDefaultsComplete");
}

#undef LOCTEXT_NAMESPACE
