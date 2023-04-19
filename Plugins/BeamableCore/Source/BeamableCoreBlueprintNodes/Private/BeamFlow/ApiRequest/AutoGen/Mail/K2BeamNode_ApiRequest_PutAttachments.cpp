

#include "BeamableCoreBlueprintNodes/Public/BeamFlow/ApiRequest/AutoGen/Mail/K2BeamNode_ApiRequest_PutAttachments.h"

#include "BeamK2.h"

#include "BeamableCore/Public/AutoGen/SubSystems/BeamMailApi.h"
#include "BeamableCore/Public/AutoGen/SubSystems/Mail/PutAttachmentsRequest.h"
#include "BeamableCore/Public/AutoGen/MailSuccessResponse.h"

#define LOCTEXT_NAMESPACE "K2BeamNode_ApiRequest_PutAttachments"

using namespace BeamK2;

FName UK2BeamNode_ApiRequest_PutAttachments::GetSelfFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamMailApi, GetSelf);
}

FName UK2BeamNode_ApiRequest_PutAttachments::GetRequestFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamMailApi, PutAttachments);
}

FName UK2BeamNode_ApiRequest_PutAttachments::GetMakeFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UPutAttachmentsRequest, Make);
}

FString UK2BeamNode_ApiRequest_PutAttachments::GetServiceName() const
{
	return TEXT("Mail");
}

FString UK2BeamNode_ApiRequest_PutAttachments::GetEndpointName() const
{
	return TEXT("PutAttachments");
}

UClass* UK2BeamNode_ApiRequest_PutAttachments::GetApiClass() const
{
	return UBeamMailApi::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_PutAttachments::GetRequestClass() const
{
	return UPutAttachmentsRequest::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_PutAttachments::GetResponseClass() const
{
	return UMailSuccessResponse::StaticClass();
}

FString UK2BeamNode_ApiRequest_PutAttachments::GetRequestSuccessDelegateName() const
{
	return TEXT("OnPutAttachmentsSuccess");
}

FString UK2BeamNode_ApiRequest_PutAttachments::GetRequestErrorDelegateName() const
{
	return TEXT("OnPutAttachmentsError");
}

FString UK2BeamNode_ApiRequest_PutAttachments::GetRequestCompleteDelegateName() const
{
	return TEXT("OnPutAttachmentsComplete");
}

#undef LOCTEXT_NAMESPACE
