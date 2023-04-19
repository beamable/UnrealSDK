

#include "BeamableCoreBlueprintNodes/Public/BeamFlow/ApiRequest/AutoGen/Mail/K2BeamNode_ApiRequest_ObjectMailGetMail.h"

#include "BeamK2.h"

#include "BeamableCore/Public/AutoGen/SubSystems/BeamMailApi.h"
#include "BeamableCore/Public/AutoGen/SubSystems/Mail/ObjectMailGetMailRequest.h"
#include "BeamableCore/Public/AutoGen/MailQueryResponse.h"

#define LOCTEXT_NAMESPACE "K2BeamNode_ApiRequest_ObjectMailGetMail"

using namespace BeamK2;

FName UK2BeamNode_ApiRequest_ObjectMailGetMail::GetSelfFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamMailApi, GetSelf);
}

FName UK2BeamNode_ApiRequest_ObjectMailGetMail::GetRequestFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamMailApi, ObjectMailGetMail);
}

FName UK2BeamNode_ApiRequest_ObjectMailGetMail::GetMakeFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UObjectMailGetMailRequest, Make);
}

FString UK2BeamNode_ApiRequest_ObjectMailGetMail::GetServiceName() const
{
	return TEXT("Mail");
}

FString UK2BeamNode_ApiRequest_ObjectMailGetMail::GetEndpointName() const
{
	return TEXT("ObjectMailGetMail");
}

UClass* UK2BeamNode_ApiRequest_ObjectMailGetMail::GetApiClass() const
{
	return UBeamMailApi::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_ObjectMailGetMail::GetRequestClass() const
{
	return UObjectMailGetMailRequest::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_ObjectMailGetMail::GetResponseClass() const
{
	return UMailQueryResponse::StaticClass();
}

FString UK2BeamNode_ApiRequest_ObjectMailGetMail::GetRequestSuccessDelegateName() const
{
	return TEXT("OnObjectMailGetMailSuccess");
}

FString UK2BeamNode_ApiRequest_ObjectMailGetMail::GetRequestErrorDelegateName() const
{
	return TEXT("OnObjectMailGetMailError");
}

FString UK2BeamNode_ApiRequest_ObjectMailGetMail::GetRequestCompleteDelegateName() const
{
	return TEXT("OnObjectMailGetMailComplete");
}

#undef LOCTEXT_NAMESPACE
