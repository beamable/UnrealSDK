

#include "BeamableCoreBlueprintNodes/Public/BeamFlow/ApiRequest/AutoGen/Mail/K2BeamNode_ApiRequest_ObjectMailPutMail.h"

#include "BeamK2.h"

#include "BeamableCore/Public/AutoGen/SubSystems/BeamMailApi.h"
#include "BeamableCore/Public/AutoGen/SubSystems/Mail/ObjectMailPutMailRequest.h"
#include "BeamableCore/Public/AutoGen/MailSuccessResponse.h"

#define LOCTEXT_NAMESPACE "K2BeamNode_ApiRequest_ObjectMailPutMail"

using namespace BeamK2;

FName UK2BeamNode_ApiRequest_ObjectMailPutMail::GetSelfFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamMailApi, GetSelf);
}

FName UK2BeamNode_ApiRequest_ObjectMailPutMail::GetRequestFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamMailApi, ObjectMailPutMail);
}

FName UK2BeamNode_ApiRequest_ObjectMailPutMail::GetMakeFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UObjectMailPutMailRequest, Make);
}

FString UK2BeamNode_ApiRequest_ObjectMailPutMail::GetServiceName() const
{
	return TEXT("Mail");
}

FString UK2BeamNode_ApiRequest_ObjectMailPutMail::GetEndpointName() const
{
	return TEXT("ObjectMailPutMail");
}

UClass* UK2BeamNode_ApiRequest_ObjectMailPutMail::GetApiClass() const
{
	return UBeamMailApi::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_ObjectMailPutMail::GetRequestClass() const
{
	return UObjectMailPutMailRequest::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_ObjectMailPutMail::GetResponseClass() const
{
	return UMailSuccessResponse::StaticClass();
}

FString UK2BeamNode_ApiRequest_ObjectMailPutMail::GetRequestSuccessDelegateName() const
{
	return TEXT("OnObjectMailPutMailSuccess");
}

FString UK2BeamNode_ApiRequest_ObjectMailPutMail::GetRequestErrorDelegateName() const
{
	return TEXT("OnObjectMailPutMailError");
}

FString UK2BeamNode_ApiRequest_ObjectMailPutMail::GetRequestCompleteDelegateName() const
{
	return TEXT("OnObjectMailPutMailComplete");
}

#undef LOCTEXT_NAMESPACE
