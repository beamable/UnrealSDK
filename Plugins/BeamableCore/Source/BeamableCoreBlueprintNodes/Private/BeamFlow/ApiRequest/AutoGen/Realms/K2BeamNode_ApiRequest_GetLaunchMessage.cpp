

#include "BeamableCoreBlueprintNodes/Public/BeamFlow/ApiRequest/AutoGen/Realms/K2BeamNode_ApiRequest_GetLaunchMessage.h"

#include "BeamK2.h"

#include "BeamableCore/Public/AutoGen/SubSystems/BeamRealmsApi.h"
#include "BeamableCore/Public/AutoGen/SubSystems/Realms/GetLaunchMessageRequest.h"
#include "BeamableCore/Public/AutoGen/LaunchMessageListResponse.h"

#define LOCTEXT_NAMESPACE "K2BeamNode_ApiRequest_GetLaunchMessage"

using namespace BeamK2;

FName UK2BeamNode_ApiRequest_GetLaunchMessage::GetSelfFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamRealmsApi, GetSelf);
}

FName UK2BeamNode_ApiRequest_GetLaunchMessage::GetRequestFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamRealmsApi, GetLaunchMessage);
}

FName UK2BeamNode_ApiRequest_GetLaunchMessage::GetMakeFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UGetLaunchMessageRequest, Make);
}

FString UK2BeamNode_ApiRequest_GetLaunchMessage::GetServiceName() const
{
	return TEXT("Realms");
}

FString UK2BeamNode_ApiRequest_GetLaunchMessage::GetEndpointName() const
{
	return TEXT("GetLaunchMessage");
}

UClass* UK2BeamNode_ApiRequest_GetLaunchMessage::GetApiClass() const
{
	return UBeamRealmsApi::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_GetLaunchMessage::GetRequestClass() const
{
	return UGetLaunchMessageRequest::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_GetLaunchMessage::GetResponseClass() const
{
	return ULaunchMessageListResponse::StaticClass();
}

FString UK2BeamNode_ApiRequest_GetLaunchMessage::GetRequestSuccessDelegateName() const
{
	return TEXT("OnGetLaunchMessageSuccess");
}

FString UK2BeamNode_ApiRequest_GetLaunchMessage::GetRequestErrorDelegateName() const
{
	return TEXT("OnGetLaunchMessageError");
}

FString UK2BeamNode_ApiRequest_GetLaunchMessage::GetRequestCompleteDelegateName() const
{
	return TEXT("OnGetLaunchMessageComplete");
}

#undef LOCTEXT_NAMESPACE
