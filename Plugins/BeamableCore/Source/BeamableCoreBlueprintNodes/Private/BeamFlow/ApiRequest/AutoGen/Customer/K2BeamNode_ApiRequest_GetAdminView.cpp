

#include "BeamableCoreBlueprintNodes/Public/BeamFlow/ApiRequest/AutoGen/Customer/K2BeamNode_ApiRequest_GetAdminView.h"

#include "BeamK2.h"

#include "BeamableCore/Public/AutoGen/SubSystems/BeamCustomerApi.h"
#include "BeamableCore/Public/AutoGen/SubSystems/Customer/GetAdminViewRequest.h"
#include "BeamableCore/Public/AutoGen/CustomerActorCustomer.h"

#define LOCTEXT_NAMESPACE "K2BeamNode_ApiRequest_GetAdminView"

using namespace BeamK2;

FName UK2BeamNode_ApiRequest_GetAdminView::GetSelfFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamCustomerApi, GetSelf);
}

FName UK2BeamNode_ApiRequest_GetAdminView::GetRequestFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamCustomerApi, GetAdminView);
}

FName UK2BeamNode_ApiRequest_GetAdminView::GetMakeFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UGetAdminViewRequest, Make);
}

FString UK2BeamNode_ApiRequest_GetAdminView::GetServiceName() const
{
	return TEXT("Customer");
}

FString UK2BeamNode_ApiRequest_GetAdminView::GetEndpointName() const
{
	return TEXT("GetAdminView");
}

UClass* UK2BeamNode_ApiRequest_GetAdminView::GetApiClass() const
{
	return UBeamCustomerApi::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_GetAdminView::GetRequestClass() const
{
	return UGetAdminViewRequest::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_GetAdminView::GetResponseClass() const
{
	return UCustomerActorCustomer::StaticClass();
}

FString UK2BeamNode_ApiRequest_GetAdminView::GetRequestSuccessDelegateName() const
{
	return TEXT("OnGetAdminViewSuccess");
}

FString UK2BeamNode_ApiRequest_GetAdminView::GetRequestErrorDelegateName() const
{
	return TEXT("OnGetAdminViewError");
}

FString UK2BeamNode_ApiRequest_GetAdminView::GetRequestCompleteDelegateName() const
{
	return TEXT("OnGetAdminViewComplete");
}

#undef LOCTEXT_NAMESPACE
