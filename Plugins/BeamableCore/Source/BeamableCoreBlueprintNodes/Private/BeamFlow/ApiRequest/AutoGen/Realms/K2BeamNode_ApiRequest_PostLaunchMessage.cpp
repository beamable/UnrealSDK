

#include "BeamableCoreBlueprintNodes/Public/BeamFlow/ApiRequest/AutoGen/Realms/K2BeamNode_ApiRequest_PostLaunchMessage.h"

#include "BeamK2.h"

#include "BeamableCore/Public/AutoGen/SubSystems/BeamRealmsApi.h"
#include "BeamableCore/Public/AutoGen/SubSystems/Realms/PostLaunchMessageRequest.h"
#include "BeamableCore/Public/AutoGen/CommonResponse.h"

#define LOCTEXT_NAMESPACE "K2BeamNode_ApiRequest_PostLaunchMessage"

using namespace BeamK2;

FName UK2BeamNode_ApiRequest_PostLaunchMessage::GetSelfFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamRealmsApi, GetSelf);
}

FName UK2BeamNode_ApiRequest_PostLaunchMessage::GetRequestFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamRealmsApi, PostLaunchMessage);
}

FName UK2BeamNode_ApiRequest_PostLaunchMessage::GetMakeFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UPostLaunchMessageRequest, Make);
}

FString UK2BeamNode_ApiRequest_PostLaunchMessage::GetServiceName() const
{
	return TEXT("Realms");
}

FString UK2BeamNode_ApiRequest_PostLaunchMessage::GetEndpointName() const
{
	return TEXT("PostLaunchMessage");
}

UClass* UK2BeamNode_ApiRequest_PostLaunchMessage::GetApiClass() const
{
	return UBeamRealmsApi::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_PostLaunchMessage::GetRequestClass() const
{
	return UPostLaunchMessageRequest::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_PostLaunchMessage::GetResponseClass() const
{
	return UCommonResponse::StaticClass();
}

FString UK2BeamNode_ApiRequest_PostLaunchMessage::GetRequestSuccessDelegateName() const
{
	return TEXT("OnPostLaunchMessageSuccess");
}

FString UK2BeamNode_ApiRequest_PostLaunchMessage::GetRequestErrorDelegateName() const
{
	return TEXT("OnPostLaunchMessageError");
}

FString UK2BeamNode_ApiRequest_PostLaunchMessage::GetRequestCompleteDelegateName() const
{
	return TEXT("OnPostLaunchMessageComplete");
}

#undef LOCTEXT_NAMESPACE
