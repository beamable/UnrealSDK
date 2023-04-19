

#include "BeamableCoreBlueprintNodes/Public/BeamFlow/ApiRequest/AutoGen/ChatV2/K2BeamNode_ApiRequest_PostMessages.h"

#include "BeamK2.h"

#include "BeamableCore/Public/AutoGen/SubSystems/BeamChatV2Api.h"
#include "BeamableCore/Public/AutoGen/SubSystems/ChatV2/PostMessagesRequest.h"
#include "BeamableCore/Public/AutoGen/SendMessageResponse.h"

#define LOCTEXT_NAMESPACE "K2BeamNode_ApiRequest_PostMessages"

using namespace BeamK2;

FName UK2BeamNode_ApiRequest_PostMessages::GetSelfFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamChatV2Api, GetSelf);
}

FName UK2BeamNode_ApiRequest_PostMessages::GetRequestFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamChatV2Api, PostMessages);
}

FName UK2BeamNode_ApiRequest_PostMessages::GetMakeFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UPostMessagesRequest, Make);
}

FString UK2BeamNode_ApiRequest_PostMessages::GetServiceName() const
{
	return TEXT("ChatV2");
}

FString UK2BeamNode_ApiRequest_PostMessages::GetEndpointName() const
{
	return TEXT("PostMessages");
}

UClass* UK2BeamNode_ApiRequest_PostMessages::GetApiClass() const
{
	return UBeamChatV2Api::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_PostMessages::GetRequestClass() const
{
	return UPostMessagesRequest::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_PostMessages::GetResponseClass() const
{
	return USendMessageResponse::StaticClass();
}

FString UK2BeamNode_ApiRequest_PostMessages::GetRequestSuccessDelegateName() const
{
	return TEXT("OnPostMessagesSuccess");
}

FString UK2BeamNode_ApiRequest_PostMessages::GetRequestErrorDelegateName() const
{
	return TEXT("OnPostMessagesError");
}

FString UK2BeamNode_ApiRequest_PostMessages::GetRequestCompleteDelegateName() const
{
	return TEXT("OnPostMessagesComplete");
}

#undef LOCTEXT_NAMESPACE
