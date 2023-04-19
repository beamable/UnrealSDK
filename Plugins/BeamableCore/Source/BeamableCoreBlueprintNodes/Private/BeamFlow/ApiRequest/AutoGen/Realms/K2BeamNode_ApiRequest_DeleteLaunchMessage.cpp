

#include "BeamableCoreBlueprintNodes/Public/BeamFlow/ApiRequest/AutoGen/Realms/K2BeamNode_ApiRequest_DeleteLaunchMessage.h"

#include "BeamK2.h"

#include "BeamableCore/Public/AutoGen/SubSystems/BeamRealmsApi.h"
#include "BeamableCore/Public/AutoGen/SubSystems/Realms/DeleteLaunchMessageRequest.h"
#include "BeamableCore/Public/AutoGen/CommonResponse.h"

#define LOCTEXT_NAMESPACE "K2BeamNode_ApiRequest_DeleteLaunchMessage"

using namespace BeamK2;

FName UK2BeamNode_ApiRequest_DeleteLaunchMessage::GetSelfFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamRealmsApi, GetSelf);
}

FName UK2BeamNode_ApiRequest_DeleteLaunchMessage::GetRequestFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamRealmsApi, DeleteLaunchMessage);
}

FName UK2BeamNode_ApiRequest_DeleteLaunchMessage::GetMakeFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UDeleteLaunchMessageRequest, Make);
}

FString UK2BeamNode_ApiRequest_DeleteLaunchMessage::GetServiceName() const
{
	return TEXT("Realms");
}

FString UK2BeamNode_ApiRequest_DeleteLaunchMessage::GetEndpointName() const
{
	return TEXT("DeleteLaunchMessage");
}

UClass* UK2BeamNode_ApiRequest_DeleteLaunchMessage::GetApiClass() const
{
	return UBeamRealmsApi::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_DeleteLaunchMessage::GetRequestClass() const
{
	return UDeleteLaunchMessageRequest::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_DeleteLaunchMessage::GetResponseClass() const
{
	return UCommonResponse::StaticClass();
}

FString UK2BeamNode_ApiRequest_DeleteLaunchMessage::GetRequestSuccessDelegateName() const
{
	return TEXT("OnDeleteLaunchMessageSuccess");
}

FString UK2BeamNode_ApiRequest_DeleteLaunchMessage::GetRequestErrorDelegateName() const
{
	return TEXT("OnDeleteLaunchMessageError");
}

FString UK2BeamNode_ApiRequest_DeleteLaunchMessage::GetRequestCompleteDelegateName() const
{
	return TEXT("OnDeleteLaunchMessageComplete");
}

#undef LOCTEXT_NAMESPACE
