

#include "BeamableCoreBlueprintNodes/Public/BeamFlow/ApiRequest/AutoGen/Customer/K2BeamNode_ApiRequest_PutRealmsRename.h"

#include "BeamK2.h"

#include "BeamableCore/Public/AutoGen/SubSystems/BeamCustomerApi.h"
#include "BeamableCore/Public/AutoGen/SubSystems/Customer/PutRealmsRenameRequest.h"
#include "BeamableCore/Public/AutoGen/EmptyMessage.h"

#define LOCTEXT_NAMESPACE "K2BeamNode_ApiRequest_PutRealmsRename"

using namespace BeamK2;

FName UK2BeamNode_ApiRequest_PutRealmsRename::GetSelfFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamCustomerApi, GetSelf);
}

FName UK2BeamNode_ApiRequest_PutRealmsRename::GetRequestFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamCustomerApi, PutRealmsRename);
}

FName UK2BeamNode_ApiRequest_PutRealmsRename::GetMakeFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UPutRealmsRenameRequest, Make);
}

FString UK2BeamNode_ApiRequest_PutRealmsRename::GetServiceName() const
{
	return TEXT("Customer");
}

FString UK2BeamNode_ApiRequest_PutRealmsRename::GetEndpointName() const
{
	return TEXT("PutRealmsRename");
}

UClass* UK2BeamNode_ApiRequest_PutRealmsRename::GetApiClass() const
{
	return UBeamCustomerApi::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_PutRealmsRename::GetRequestClass() const
{
	return UPutRealmsRenameRequest::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_PutRealmsRename::GetResponseClass() const
{
	return UEmptyMessage::StaticClass();
}

FString UK2BeamNode_ApiRequest_PutRealmsRename::GetRequestSuccessDelegateName() const
{
	return TEXT("OnPutRealmsRenameSuccess");
}

FString UK2BeamNode_ApiRequest_PutRealmsRename::GetRequestErrorDelegateName() const
{
	return TEXT("OnPutRealmsRenameError");
}

FString UK2BeamNode_ApiRequest_PutRealmsRename::GetRequestCompleteDelegateName() const
{
	return TEXT("OnPutRealmsRenameComplete");
}

#undef LOCTEXT_NAMESPACE
