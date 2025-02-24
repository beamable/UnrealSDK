

#include "BeamableCoreBlueprintNodes/Public/BeamFlow/ApiRequest/AutoGen/Mail/K2BeamNode_ApiRequest_ObjectMailPutMailByObjectId.h"

#include "BeamK2.h"

#include "BeamableCore/Public/AutoGen/SubSystems/BeamMailApi.h"
#include "BeamableCore/Public/AutoGen/SubSystems/Mail/ObjectMailPutMailByObjectIdRequest.h"
#include "BeamableCore/Public/AutoGen/MailSuccessResponse.h"

#define LOCTEXT_NAMESPACE "K2BeamNode_ApiRequest_ObjectMailPutMailByObjectId"

using namespace BeamK2;

FName UK2BeamNode_ApiRequest_ObjectMailPutMailByObjectId::GetSelfFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamMailApi, GetSelf);
}

FName UK2BeamNode_ApiRequest_ObjectMailPutMailByObjectId::GetRequestFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamMailApi, ObjectMailPutMailByObjectId);
}

FName UK2BeamNode_ApiRequest_ObjectMailPutMailByObjectId::GetMakeFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UObjectMailPutMailByObjectIdRequest, Make);
}

FString UK2BeamNode_ApiRequest_ObjectMailPutMailByObjectId::GetServiceName() const
{
	return TEXT("Mail");
}

FString UK2BeamNode_ApiRequest_ObjectMailPutMailByObjectId::GetEndpointName() const
{
	return TEXT("ObjectMailPutMailByObjectId");
}

UClass* UK2BeamNode_ApiRequest_ObjectMailPutMailByObjectId::GetApiClass() const
{
	return UBeamMailApi::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_ObjectMailPutMailByObjectId::GetRequestClass() const
{
	return UObjectMailPutMailByObjectIdRequest::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_ObjectMailPutMailByObjectId::GetResponseClass() const
{
	return UMailSuccessResponse::StaticClass();
}

FString UK2BeamNode_ApiRequest_ObjectMailPutMailByObjectId::GetRequestSuccessDelegateName() const
{
	return TEXT("OnObjectMailPutMailByObjectIdSuccess");
}

FString UK2BeamNode_ApiRequest_ObjectMailPutMailByObjectId::GetRequestErrorDelegateName() const
{
	return TEXT("OnObjectMailPutMailByObjectIdError");
}

FString UK2BeamNode_ApiRequest_ObjectMailPutMailByObjectId::GetRequestCompleteDelegateName() const
{
	return TEXT("OnObjectMailPutMailByObjectIdComplete");
}

#undef LOCTEXT_NAMESPACE
