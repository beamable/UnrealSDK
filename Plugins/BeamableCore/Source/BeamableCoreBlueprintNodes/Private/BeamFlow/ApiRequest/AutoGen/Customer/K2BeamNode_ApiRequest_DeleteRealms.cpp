

#include "BeamableCoreBlueprintNodes/Public/BeamFlow/ApiRequest/AutoGen/Customer/K2BeamNode_ApiRequest_DeleteRealms.h"

#include "BeamK2.h"

#include "BeamableCore/Public/AutoGen/SubSystems/BeamCustomerApi.h"
#include "BeamableCore/Public/AutoGen/SubSystems/Customer/DeleteRealmsRequest.h"
#include "BeamableCore/Public/AutoGen/EmptyMessage.h"

#define LOCTEXT_NAMESPACE "K2BeamNode_ApiRequest_DeleteRealms"

using namespace BeamK2;

FName UK2BeamNode_ApiRequest_DeleteRealms::GetSelfFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamCustomerApi, GetSelf);
}

FName UK2BeamNode_ApiRequest_DeleteRealms::GetRequestFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamCustomerApi, DeleteRealms);
}

FName UK2BeamNode_ApiRequest_DeleteRealms::GetMakeFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UDeleteRealmsRequest, Make);
}

FString UK2BeamNode_ApiRequest_DeleteRealms::GetServiceName() const
{
	return TEXT("Customer");
}

FString UK2BeamNode_ApiRequest_DeleteRealms::GetEndpointName() const
{
	return TEXT("DeleteRealms");
}

UClass* UK2BeamNode_ApiRequest_DeleteRealms::GetApiClass() const
{
	return UBeamCustomerApi::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_DeleteRealms::GetRequestClass() const
{
	return UDeleteRealmsRequest::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_DeleteRealms::GetResponseClass() const
{
	return UEmptyMessage::StaticClass();
}

FString UK2BeamNode_ApiRequest_DeleteRealms::GetRequestSuccessDelegateName() const
{
	return TEXT("OnDeleteRealmsSuccess");
}

FString UK2BeamNode_ApiRequest_DeleteRealms::GetRequestErrorDelegateName() const
{
	return TEXT("OnDeleteRealmsError");
}

FString UK2BeamNode_ApiRequest_DeleteRealms::GetRequestCompleteDelegateName() const
{
	return TEXT("OnDeleteRealmsComplete");
}

#undef LOCTEXT_NAMESPACE
