

#include "BeamableCoreBlueprintNodes/Public/BeamFlow/ApiRequest/AutoGen/Realms/K2BeamNode_ApiRequest_BasicRealmsGetCustomers.h"

#include "BeamK2.h"

#include "BeamableCore/Public/AutoGen/SubSystems/BeamRealmsApi.h"
#include "BeamableCore/Public/AutoGen/SubSystems/Realms/BasicRealmsGetCustomersRequest.h"
#include "BeamableCore/Public/AutoGen/RealmsBasicCustomersResponse.h"

#define LOCTEXT_NAMESPACE "K2BeamNode_ApiRequest_BasicRealmsGetCustomers"

using namespace BeamK2;

FName UK2BeamNode_ApiRequest_BasicRealmsGetCustomers::GetSelfFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamRealmsApi, GetSelf);
}

FName UK2BeamNode_ApiRequest_BasicRealmsGetCustomers::GetRequestFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamRealmsApi, GetCustomers);
}

FName UK2BeamNode_ApiRequest_BasicRealmsGetCustomers::GetMakeFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBasicRealmsGetCustomersRequest, Make);
}

FString UK2BeamNode_ApiRequest_BasicRealmsGetCustomers::GetServiceName() const
{
	return TEXT("Realms");
}

FString UK2BeamNode_ApiRequest_BasicRealmsGetCustomers::GetEndpointName() const
{
	return TEXT("GetCustomers");
}

UClass* UK2BeamNode_ApiRequest_BasicRealmsGetCustomers::GetApiClass() const
{
	return UBeamRealmsApi::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_BasicRealmsGetCustomers::GetRequestClass() const
{
	return UBasicRealmsGetCustomersRequest::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_BasicRealmsGetCustomers::GetResponseClass() const
{
	return URealmsBasicCustomersResponse::StaticClass();
}

FString UK2BeamNode_ApiRequest_BasicRealmsGetCustomers::GetRequestSuccessDelegateName() const
{
	return TEXT("OnBasicRealmsGetCustomersSuccess");
}

FString UK2BeamNode_ApiRequest_BasicRealmsGetCustomers::GetRequestErrorDelegateName() const
{
	return TEXT("OnBasicRealmsGetCustomersError");
}

FString UK2BeamNode_ApiRequest_BasicRealmsGetCustomers::GetRequestCompleteDelegateName() const
{
	return TEXT("OnBasicRealmsGetCustomersComplete");
}

#undef LOCTEXT_NAMESPACE
