

#include "BeamableCoreBlueprintNodes/Public/BeamFlow/ApiRequest/AutoGen/Mail/K2BeamNode_ApiRequest_BasicMailGetMail.h"

#include "BeamK2.h"

#include "BeamableCore/Public/AutoGen/SubSystems/BeamMailApi.h"
#include "BeamableCore/Public/AutoGen/SubSystems/Mail/BasicMailGetMailRequest.h"
#include "BeamableCore/Public/AutoGen/MailResponse.h"

#define LOCTEXT_NAMESPACE "K2BeamNode_ApiRequest_BasicMailGetMail"

using namespace BeamK2;

FName UK2BeamNode_ApiRequest_BasicMailGetMail::GetSelfFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamMailApi, GetSelf);
}

FName UK2BeamNode_ApiRequest_BasicMailGetMail::GetRequestFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamMailApi, BasicMailGetMail);
}

FName UK2BeamNode_ApiRequest_BasicMailGetMail::GetMakeFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBasicMailGetMailRequest, Make);
}

FString UK2BeamNode_ApiRequest_BasicMailGetMail::GetServiceName() const
{
	return TEXT("Mail");
}

FString UK2BeamNode_ApiRequest_BasicMailGetMail::GetEndpointName() const
{
	return TEXT("BasicMailGetMail");
}

UClass* UK2BeamNode_ApiRequest_BasicMailGetMail::GetApiClass() const
{
	return UBeamMailApi::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_BasicMailGetMail::GetRequestClass() const
{
	return UBasicMailGetMailRequest::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_BasicMailGetMail::GetResponseClass() const
{
	return UMailResponse::StaticClass();
}

FString UK2BeamNode_ApiRequest_BasicMailGetMail::GetRequestSuccessDelegateName() const
{
	return TEXT("OnBasicMailGetMailSuccess");
}

FString UK2BeamNode_ApiRequest_BasicMailGetMail::GetRequestErrorDelegateName() const
{
	return TEXT("OnBasicMailGetMailError");
}

FString UK2BeamNode_ApiRequest_BasicMailGetMail::GetRequestCompleteDelegateName() const
{
	return TEXT("OnBasicMailGetMailComplete");
}

#undef LOCTEXT_NAMESPACE
