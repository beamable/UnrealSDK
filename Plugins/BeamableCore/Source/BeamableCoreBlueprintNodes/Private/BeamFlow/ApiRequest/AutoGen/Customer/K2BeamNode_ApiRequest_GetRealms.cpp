

#include "BeamableCoreBlueprintNodes/Public/BeamFlow/ApiRequest/AutoGen/Customer/K2BeamNode_ApiRequest_GetRealms.h"

#include "BeamK2.h"

#include "BeamableCore/Public/AutoGen/SubSystems/BeamCustomerApi.h"
#include "BeamableCore/Public/AutoGen/SubSystems/Customer/GetRealmsRequest.h"
#include "BeamableCore/Public/AutoGen/RealmView.h"

#define LOCTEXT_NAMESPACE "K2BeamNode_ApiRequest_GetRealms"

using namespace BeamK2;

FName UK2BeamNode_ApiRequest_GetRealms::GetSelfFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamCustomerApi, GetSelf);
}

FName UK2BeamNode_ApiRequest_GetRealms::GetRequestFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamCustomerApi, GetRealms);
}

FName UK2BeamNode_ApiRequest_GetRealms::GetMakeFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UGetRealmsRequest, Make);
}

FString UK2BeamNode_ApiRequest_GetRealms::GetServiceName() const
{
	return TEXT("Customer");
}

FString UK2BeamNode_ApiRequest_GetRealms::GetEndpointName() const
{
	return TEXT("GetRealms");
}

UClass* UK2BeamNode_ApiRequest_GetRealms::GetApiClass() const
{
	return UBeamCustomerApi::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_GetRealms::GetRequestClass() const
{
	return UGetRealmsRequest::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_GetRealms::GetResponseClass() const
{
	return URealmView::StaticClass();
}

FString UK2BeamNode_ApiRequest_GetRealms::GetRequestSuccessDelegateName() const
{
	return TEXT("OnGetRealmsSuccess");
}

FString UK2BeamNode_ApiRequest_GetRealms::GetRequestErrorDelegateName() const
{
	return TEXT("OnGetRealmsError");
}

FString UK2BeamNode_ApiRequest_GetRealms::GetRequestCompleteDelegateName() const
{
	return TEXT("OnGetRealmsComplete");
}

#undef LOCTEXT_NAMESPACE
