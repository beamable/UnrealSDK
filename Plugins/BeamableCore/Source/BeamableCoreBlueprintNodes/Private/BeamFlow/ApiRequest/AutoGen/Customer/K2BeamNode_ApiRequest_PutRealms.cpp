

#include "BeamableCoreBlueprintNodes/Public/BeamFlow/ApiRequest/AutoGen/Customer/K2BeamNode_ApiRequest_PutRealms.h"

#include "BeamK2.h"

#include "BeamableCore/Public/AutoGen/SubSystems/BeamCustomerApi.h"
#include "BeamableCore/Public/AutoGen/SubSystems/Customer/PutRealmsRequest.h"
#include "BeamableCore/Public/AutoGen/EmptyMessage.h"

#define LOCTEXT_NAMESPACE "K2BeamNode_ApiRequest_PutRealms"

using namespace BeamK2;

FName UK2BeamNode_ApiRequest_PutRealms::GetSelfFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamCustomerApi, GetSelf);
}

FName UK2BeamNode_ApiRequest_PutRealms::GetRequestFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamCustomerApi, PutRealms);
}

FName UK2BeamNode_ApiRequest_PutRealms::GetMakeFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UPutRealmsRequest, Make);
}

FString UK2BeamNode_ApiRequest_PutRealms::GetServiceName() const
{
	return TEXT("Customer");
}

FString UK2BeamNode_ApiRequest_PutRealms::GetEndpointName() const
{
	return TEXT("PutRealms");
}

UClass* UK2BeamNode_ApiRequest_PutRealms::GetApiClass() const
{
	return UBeamCustomerApi::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_PutRealms::GetRequestClass() const
{
	return UPutRealmsRequest::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_PutRealms::GetResponseClass() const
{
	return UEmptyMessage::StaticClass();
}

FString UK2BeamNode_ApiRequest_PutRealms::GetRequestSuccessDelegateName() const
{
	return TEXT("OnPutRealmsSuccess");
}

FString UK2BeamNode_ApiRequest_PutRealms::GetRequestErrorDelegateName() const
{
	return TEXT("OnPutRealmsError");
}

FString UK2BeamNode_ApiRequest_PutRealms::GetRequestCompleteDelegateName() const
{
	return TEXT("OnPutRealmsComplete");
}

#undef LOCTEXT_NAMESPACE
