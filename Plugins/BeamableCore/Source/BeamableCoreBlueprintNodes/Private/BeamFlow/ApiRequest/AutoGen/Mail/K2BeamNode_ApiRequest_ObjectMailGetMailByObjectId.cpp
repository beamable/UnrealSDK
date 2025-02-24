

#include "BeamableCoreBlueprintNodes/Public/BeamFlow/ApiRequest/AutoGen/Mail/K2BeamNode_ApiRequest_ObjectMailGetMailByObjectId.h"

#include "BeamK2.h"

#include "BeamableCore/Public/AutoGen/SubSystems/BeamMailApi.h"
#include "BeamableCore/Public/AutoGen/SubSystems/Mail/ObjectMailGetMailByObjectIdRequest.h"
#include "BeamableCore/Public/AutoGen/MailQueryResponse.h"

#define LOCTEXT_NAMESPACE "K2BeamNode_ApiRequest_ObjectMailGetMailByObjectId"

using namespace BeamK2;

FName UK2BeamNode_ApiRequest_ObjectMailGetMailByObjectId::GetSelfFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamMailApi, GetSelf);
}

FName UK2BeamNode_ApiRequest_ObjectMailGetMailByObjectId::GetRequestFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamMailApi, ObjectMailGetMailByObjectId);
}

FName UK2BeamNode_ApiRequest_ObjectMailGetMailByObjectId::GetMakeFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UObjectMailGetMailByObjectIdRequest, Make);
}

FString UK2BeamNode_ApiRequest_ObjectMailGetMailByObjectId::GetServiceName() const
{
	return TEXT("Mail");
}

FString UK2BeamNode_ApiRequest_ObjectMailGetMailByObjectId::GetEndpointName() const
{
	return TEXT("ObjectMailGetMailByObjectId");
}

UClass* UK2BeamNode_ApiRequest_ObjectMailGetMailByObjectId::GetApiClass() const
{
	return UBeamMailApi::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_ObjectMailGetMailByObjectId::GetRequestClass() const
{
	return UObjectMailGetMailByObjectIdRequest::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_ObjectMailGetMailByObjectId::GetResponseClass() const
{
	return UMailQueryResponse::StaticClass();
}

FString UK2BeamNode_ApiRequest_ObjectMailGetMailByObjectId::GetRequestSuccessDelegateName() const
{
	return TEXT("OnObjectMailGetMailByObjectIdSuccess");
}

FString UK2BeamNode_ApiRequest_ObjectMailGetMailByObjectId::GetRequestErrorDelegateName() const
{
	return TEXT("OnObjectMailGetMailByObjectIdError");
}

FString UK2BeamNode_ApiRequest_ObjectMailGetMailByObjectId::GetRequestCompleteDelegateName() const
{
	return TEXT("OnObjectMailGetMailByObjectIdComplete");
}

#undef LOCTEXT_NAMESPACE
