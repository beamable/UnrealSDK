

#include "BeamableCoreBlueprintNodes/Public/BeamFlow/ApiRequest/AutoGen/Mail/K2BeamNode_ApiRequest_ObjectMailPostBulkByObjectId.h"

#include "BeamK2.h"

#include "BeamableCore/Public/AutoGen/SubSystems/BeamMailApi.h"
#include "BeamableCore/Public/AutoGen/SubSystems/Mail/ObjectMailPostBulkByObjectIdRequest.h"
#include "BeamableCore/Public/AutoGen/MailSuccessResponse.h"

#define LOCTEXT_NAMESPACE "K2BeamNode_ApiRequest_ObjectMailPostBulkByObjectId"

using namespace BeamK2;

FName UK2BeamNode_ApiRequest_ObjectMailPostBulkByObjectId::GetSelfFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamMailApi, GetSelf);
}

FName UK2BeamNode_ApiRequest_ObjectMailPostBulkByObjectId::GetRequestFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamMailApi, ObjectMailPostBulkByObjectId);
}

FName UK2BeamNode_ApiRequest_ObjectMailPostBulkByObjectId::GetMakeFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UObjectMailPostBulkByObjectIdRequest, Make);
}

FString UK2BeamNode_ApiRequest_ObjectMailPostBulkByObjectId::GetServiceName() const
{
	return TEXT("Mail");
}

FString UK2BeamNode_ApiRequest_ObjectMailPostBulkByObjectId::GetEndpointName() const
{
	return TEXT("ObjectMailPostBulkByObjectId");
}

UClass* UK2BeamNode_ApiRequest_ObjectMailPostBulkByObjectId::GetApiClass() const
{
	return UBeamMailApi::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_ObjectMailPostBulkByObjectId::GetRequestClass() const
{
	return UObjectMailPostBulkByObjectIdRequest::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_ObjectMailPostBulkByObjectId::GetResponseClass() const
{
	return UMailSuccessResponse::StaticClass();
}

FString UK2BeamNode_ApiRequest_ObjectMailPostBulkByObjectId::GetRequestSuccessDelegateName() const
{
	return TEXT("OnObjectMailPostBulkByObjectIdSuccess");
}

FString UK2BeamNode_ApiRequest_ObjectMailPostBulkByObjectId::GetRequestErrorDelegateName() const
{
	return TEXT("OnObjectMailPostBulkByObjectIdError");
}

FString UK2BeamNode_ApiRequest_ObjectMailPostBulkByObjectId::GetRequestCompleteDelegateName() const
{
	return TEXT("OnObjectMailPostBulkByObjectIdComplete");
}

#undef LOCTEXT_NAMESPACE
