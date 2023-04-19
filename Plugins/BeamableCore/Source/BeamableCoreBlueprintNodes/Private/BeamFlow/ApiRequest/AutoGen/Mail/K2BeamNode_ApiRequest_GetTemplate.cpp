

#include "BeamableCoreBlueprintNodes/Public/BeamFlow/ApiRequest/AutoGen/Mail/K2BeamNode_ApiRequest_GetTemplate.h"

#include "BeamK2.h"

#include "BeamableCore/Public/AutoGen/SubSystems/BeamMailApi.h"
#include "BeamableCore/Public/AutoGen/SubSystems/Mail/GetTemplateRequest.h"
#include "BeamableCore/Public/AutoGen/MailTemplate.h"

#define LOCTEXT_NAMESPACE "K2BeamNode_ApiRequest_GetTemplate"

using namespace BeamK2;

FName UK2BeamNode_ApiRequest_GetTemplate::GetSelfFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamMailApi, GetSelf);
}

FName UK2BeamNode_ApiRequest_GetTemplate::GetRequestFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamMailApi, GetTemplate);
}

FName UK2BeamNode_ApiRequest_GetTemplate::GetMakeFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UGetTemplateRequest, Make);
}

FString UK2BeamNode_ApiRequest_GetTemplate::GetServiceName() const
{
	return TEXT("Mail");
}

FString UK2BeamNode_ApiRequest_GetTemplate::GetEndpointName() const
{
	return TEXT("GetTemplate");
}

UClass* UK2BeamNode_ApiRequest_GetTemplate::GetApiClass() const
{
	return UBeamMailApi::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_GetTemplate::GetRequestClass() const
{
	return UGetTemplateRequest::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_GetTemplate::GetResponseClass() const
{
	return UMailTemplate::StaticClass();
}

FString UK2BeamNode_ApiRequest_GetTemplate::GetRequestSuccessDelegateName() const
{
	return TEXT("OnGetTemplateSuccess");
}

FString UK2BeamNode_ApiRequest_GetTemplate::GetRequestErrorDelegateName() const
{
	return TEXT("OnGetTemplateError");
}

FString UK2BeamNode_ApiRequest_GetTemplate::GetRequestCompleteDelegateName() const
{
	return TEXT("OnGetTemplateComplete");
}

#undef LOCTEXT_NAMESPACE
