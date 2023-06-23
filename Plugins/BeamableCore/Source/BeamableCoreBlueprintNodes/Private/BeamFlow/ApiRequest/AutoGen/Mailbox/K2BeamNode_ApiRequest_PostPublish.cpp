

#include "BeamableCoreBlueprintNodes/Public/BeamFlow/ApiRequest/AutoGen/Mailbox/K2BeamNode_ApiRequest_PostPublish.h"

#include "BeamK2.h"

#include "BeamableCore/Public/AutoGen/SubSystems/BeamMailboxApi.h"
#include "BeamableCore/Public/AutoGen/SubSystems/Mailbox/PostPublishRequest.h"
#include "BeamableCore/Public/AutoGen/ApiMailboxPublishPostMailboxResponse.h"

#define LOCTEXT_NAMESPACE "K2BeamNode_ApiRequest_PostPublish"

using namespace BeamK2;

FName UK2BeamNode_ApiRequest_PostPublish::GetSelfFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamMailboxApi, GetSelf);
}

FName UK2BeamNode_ApiRequest_PostPublish::GetRequestFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamMailboxApi, PostPublish);
}

FName UK2BeamNode_ApiRequest_PostPublish::GetMakeFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UPostPublishRequest, Make);
}

FString UK2BeamNode_ApiRequest_PostPublish::GetServiceName() const
{
	return TEXT("Mailbox");
}

FString UK2BeamNode_ApiRequest_PostPublish::GetEndpointName() const
{
	return TEXT("PostPublish");
}

UClass* UK2BeamNode_ApiRequest_PostPublish::GetApiClass() const
{
	return UBeamMailboxApi::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_PostPublish::GetRequestClass() const
{
	return UPostPublishRequest::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_PostPublish::GetResponseClass() const
{
	return UApiMailboxPublishPostMailboxResponse::StaticClass();
}

FString UK2BeamNode_ApiRequest_PostPublish::GetRequestSuccessDelegateName() const
{
	return TEXT("OnPostPublishSuccess");
}

FString UK2BeamNode_ApiRequest_PostPublish::GetRequestErrorDelegateName() const
{
	return TEXT("OnPostPublishError");
}

FString UK2BeamNode_ApiRequest_PostPublish::GetRequestCompleteDelegateName() const
{
	return TEXT("OnPostPublishComplete");
}

#undef LOCTEXT_NAMESPACE
