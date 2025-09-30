

#include "BeamableCoreBlueprintNodes/Public/BeamFlow/ApiRequest/AutoGen/Customer/K2BeamNode_ApiRequest_PostRealms.h"

#include "BeamK2.h"

#include "BeamableCore/Public/AutoGen/SubSystems/BeamCustomerApi.h"
#include "BeamableCore/Public/AutoGen/SubSystems/Customer/PostRealmsRequest.h"
#include "BeamableCore/Public/AutoGen/EmptyMessage.h"

#define LOCTEXT_NAMESPACE "K2BeamNode_ApiRequest_PostRealms"

using namespace BeamK2;

FName UK2BeamNode_ApiRequest_PostRealms::GetSelfFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamCustomerApi, GetSelf);
}

FName UK2BeamNode_ApiRequest_PostRealms::GetRequestFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamCustomerApi, PostRealms);
}

FName UK2BeamNode_ApiRequest_PostRealms::GetMakeFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UPostRealmsRequest, Make);
}

FString UK2BeamNode_ApiRequest_PostRealms::GetServiceName() const
{
	return TEXT("Customer");
}

FString UK2BeamNode_ApiRequest_PostRealms::GetEndpointName() const
{
	return TEXT("PostRealms");
}

UClass* UK2BeamNode_ApiRequest_PostRealms::GetApiClass() const
{
	return UBeamCustomerApi::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_PostRealms::GetRequestClass() const
{
	return UPostRealmsRequest::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_PostRealms::GetResponseClass() const
{
	return UEmptyMessage::StaticClass();
}

FString UK2BeamNode_ApiRequest_PostRealms::GetRequestSuccessDelegateName() const
{
	return TEXT("OnPostRealmsSuccess");
}

FString UK2BeamNode_ApiRequest_PostRealms::GetRequestErrorDelegateName() const
{
	return TEXT("OnPostRealmsError");
}

FString UK2BeamNode_ApiRequest_PostRealms::GetRequestCompleteDelegateName() const
{
	return TEXT("OnPostRealmsComplete");
}

#undef LOCTEXT_NAMESPACE
