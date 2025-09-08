

#include "BeamableCoreBlueprintNodes/Public/BeamFlow/ApiRequest/AutoGen/Admin/K2BeamNode_ApiRequest_DeleteInflightFailures.h"

#include "BeamK2.h"

#include "BeamableCore/Public/AutoGen/SubSystems/BeamAdminApi.h"
#include "BeamableCore/Public/AutoGen/SubSystems/Admin/DeleteInflightFailuresRequest.h"
#include "BeamableCore/Public/AutoGen/EmptyMessage.h"

#define LOCTEXT_NAMESPACE "K2BeamNode_ApiRequest_DeleteInflightFailures"

using namespace BeamK2;

FName UK2BeamNode_ApiRequest_DeleteInflightFailures::GetSelfFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamAdminApi, GetSelf);
}

FName UK2BeamNode_ApiRequest_DeleteInflightFailures::GetRequestFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamAdminApi, DeleteInflightFailures);
}

FName UK2BeamNode_ApiRequest_DeleteInflightFailures::GetMakeFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UDeleteInflightFailuresRequest, Make);
}

FString UK2BeamNode_ApiRequest_DeleteInflightFailures::GetServiceName() const
{
	return TEXT("Admin");
}

FString UK2BeamNode_ApiRequest_DeleteInflightFailures::GetEndpointName() const
{
	return TEXT("DeleteInflightFailures");
}

UClass* UK2BeamNode_ApiRequest_DeleteInflightFailures::GetApiClass() const
{
	return UBeamAdminApi::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_DeleteInflightFailures::GetRequestClass() const
{
	return UDeleteInflightFailuresRequest::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_DeleteInflightFailures::GetResponseClass() const
{
	return UEmptyMessage::StaticClass();
}

FString UK2BeamNode_ApiRequest_DeleteInflightFailures::GetRequestSuccessDelegateName() const
{
	return TEXT("OnDeleteInflightFailuresSuccess");
}

FString UK2BeamNode_ApiRequest_DeleteInflightFailures::GetRequestErrorDelegateName() const
{
	return TEXT("OnDeleteInflightFailuresError");
}

FString UK2BeamNode_ApiRequest_DeleteInflightFailures::GetRequestCompleteDelegateName() const
{
	return TEXT("OnDeleteInflightFailuresComplete");
}

#undef LOCTEXT_NAMESPACE
