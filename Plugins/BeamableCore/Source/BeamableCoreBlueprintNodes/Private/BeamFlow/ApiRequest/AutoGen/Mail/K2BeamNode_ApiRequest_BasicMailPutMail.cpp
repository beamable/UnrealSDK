

#include "BeamableCoreBlueprintNodes/Public/BeamFlow/ApiRequest/AutoGen/Mail/K2BeamNode_ApiRequest_BasicMailPutMail.h"

#include "BeamK2.h"

#include "BeamableCore/Public/AutoGen/SubSystems/BeamMailApi.h"
#include "BeamableCore/Public/AutoGen/SubSystems/Mail/BasicMailPutMailRequest.h"
#include "BeamableCore/Public/AutoGen/MailSuccessResponse.h"

#define LOCTEXT_NAMESPACE "K2BeamNode_ApiRequest_BasicMailPutMail"

using namespace BeamK2;

FName UK2BeamNode_ApiRequest_BasicMailPutMail::GetSelfFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamMailApi, GetSelf);
}

FName UK2BeamNode_ApiRequest_BasicMailPutMail::GetRequestFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamMailApi, BasicMailPutMail);
}

FName UK2BeamNode_ApiRequest_BasicMailPutMail::GetMakeFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBasicMailPutMailRequest, Make);
}

FString UK2BeamNode_ApiRequest_BasicMailPutMail::GetServiceName() const
{
	return TEXT("Mail");
}

FString UK2BeamNode_ApiRequest_BasicMailPutMail::GetEndpointName() const
{
	return TEXT("BasicMailPutMail");
}

UClass* UK2BeamNode_ApiRequest_BasicMailPutMail::GetApiClass() const
{
	return UBeamMailApi::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_BasicMailPutMail::GetRequestClass() const
{
	return UBasicMailPutMailRequest::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_BasicMailPutMail::GetResponseClass() const
{
	return UMailSuccessResponse::StaticClass();
}

FString UK2BeamNode_ApiRequest_BasicMailPutMail::GetRequestSuccessDelegateName() const
{
	return TEXT("OnBasicMailPutMailSuccess");
}

FString UK2BeamNode_ApiRequest_BasicMailPutMail::GetRequestErrorDelegateName() const
{
	return TEXT("OnBasicMailPutMailError");
}

FString UK2BeamNode_ApiRequest_BasicMailPutMail::GetRequestCompleteDelegateName() const
{
	return TEXT("OnBasicMailPutMailComplete");
}

#undef LOCTEXT_NAMESPACE
