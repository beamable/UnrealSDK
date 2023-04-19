

#include "BeamableCoreBlueprintNodes/Public/BeamFlow/ApiRequest/AutoGen/Mail/K2BeamNode_ApiRequest_ObjectMailPostBulk.h"

#include "BeamK2.h"

#include "BeamableCore/Public/AutoGen/SubSystems/BeamMailApi.h"
#include "BeamableCore/Public/AutoGen/SubSystems/Mail/ObjectMailPostBulkRequest.h"
#include "BeamableCore/Public/AutoGen/MailSuccessResponse.h"

#define LOCTEXT_NAMESPACE "K2BeamNode_ApiRequest_ObjectMailPostBulk"

using namespace BeamK2;

FName UK2BeamNode_ApiRequest_ObjectMailPostBulk::GetSelfFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamMailApi, GetSelf);
}

FName UK2BeamNode_ApiRequest_ObjectMailPostBulk::GetRequestFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamMailApi, ObjectMailPostBulk);
}

FName UK2BeamNode_ApiRequest_ObjectMailPostBulk::GetMakeFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UObjectMailPostBulkRequest, Make);
}

FString UK2BeamNode_ApiRequest_ObjectMailPostBulk::GetServiceName() const
{
	return TEXT("Mail");
}

FString UK2BeamNode_ApiRequest_ObjectMailPostBulk::GetEndpointName() const
{
	return TEXT("ObjectMailPostBulk");
}

UClass* UK2BeamNode_ApiRequest_ObjectMailPostBulk::GetApiClass() const
{
	return UBeamMailApi::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_ObjectMailPostBulk::GetRequestClass() const
{
	return UObjectMailPostBulkRequest::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_ObjectMailPostBulk::GetResponseClass() const
{
	return UMailSuccessResponse::StaticClass();
}

FString UK2BeamNode_ApiRequest_ObjectMailPostBulk::GetRequestSuccessDelegateName() const
{
	return TEXT("OnObjectMailPostBulkSuccess");
}

FString UK2BeamNode_ApiRequest_ObjectMailPostBulk::GetRequestErrorDelegateName() const
{
	return TEXT("OnObjectMailPostBulkError");
}

FString UK2BeamNode_ApiRequest_ObjectMailPostBulk::GetRequestCompleteDelegateName() const
{
	return TEXT("OnObjectMailPostBulkComplete");
}

#undef LOCTEXT_NAMESPACE
