

#include "BeamableCoreBlueprintNodes/Public/BeamFlow/ApiRequest/AutoGen/Commerce/K2BeamNode_ApiRequest_GetOffersAdmin.h"

#include "BeamK2.h"

#include "BeamableCore/Public/AutoGen/SubSystems/BeamCommerceApi.h"
#include "BeamableCore/Public/AutoGen/SubSystems/Commerce/GetOffersAdminRequest.h"
#include "BeamableCore/Public/AutoGen/GetActiveOffersResponse.h"

#define LOCTEXT_NAMESPACE "K2BeamNode_ApiRequest_GetOffersAdmin"

using namespace BeamK2;

FName UK2BeamNode_ApiRequest_GetOffersAdmin::GetSelfFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamCommerceApi, GetSelf);
}

FName UK2BeamNode_ApiRequest_GetOffersAdmin::GetRequestFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamCommerceApi, GetOffersAdmin);
}

FName UK2BeamNode_ApiRequest_GetOffersAdmin::GetMakeFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UGetOffersAdminRequest, Make);
}

FString UK2BeamNode_ApiRequest_GetOffersAdmin::GetServiceName() const
{
	return TEXT("Commerce");
}

FString UK2BeamNode_ApiRequest_GetOffersAdmin::GetEndpointName() const
{
	return TEXT("GetOffersAdmin");
}

UClass* UK2BeamNode_ApiRequest_GetOffersAdmin::GetApiClass() const
{
	return UBeamCommerceApi::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_GetOffersAdmin::GetRequestClass() const
{
	return UGetOffersAdminRequest::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_GetOffersAdmin::GetResponseClass() const
{
	return UGetActiveOffersResponse::StaticClass();
}

FString UK2BeamNode_ApiRequest_GetOffersAdmin::GetRequestSuccessDelegateName() const
{
	return TEXT("OnGetOffersAdminSuccess");
}

FString UK2BeamNode_ApiRequest_GetOffersAdmin::GetRequestErrorDelegateName() const
{
	return TEXT("OnGetOffersAdminError");
}

FString UK2BeamNode_ApiRequest_GetOffersAdmin::GetRequestCompleteDelegateName() const
{
	return TEXT("OnGetOffersAdminComplete");
}

#undef LOCTEXT_NAMESPACE
