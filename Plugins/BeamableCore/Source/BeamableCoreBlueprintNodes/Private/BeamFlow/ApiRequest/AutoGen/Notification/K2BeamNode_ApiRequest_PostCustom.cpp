

#include "BeamableCoreBlueprintNodes/Public/BeamFlow/ApiRequest/AutoGen/Notification/K2BeamNode_ApiRequest_PostCustom.h"

#include "BeamK2.h"

#include "BeamableCore/Public/AutoGen/SubSystems/BeamNotificationApi.h"
#include "BeamableCore/Public/AutoGen/SubSystems/Notification/PostCustomRequest.h"
#include "BeamableCore/Public/AutoGen/CommonResponse.h"

#define LOCTEXT_NAMESPACE "K2BeamNode_ApiRequest_PostCustom"

using namespace BeamK2;

FName UK2BeamNode_ApiRequest_PostCustom::GetSelfFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamNotificationApi, GetSelf);
}

FName UK2BeamNode_ApiRequest_PostCustom::GetRequestFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamNotificationApi, PostCustom);
}

FName UK2BeamNode_ApiRequest_PostCustom::GetMakeFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UPostCustomRequest, Make);
}

FString UK2BeamNode_ApiRequest_PostCustom::GetServiceName() const
{
	return TEXT("Notification");
}

FString UK2BeamNode_ApiRequest_PostCustom::GetEndpointName() const
{
	return TEXT("PostCustom");
}

UClass* UK2BeamNode_ApiRequest_PostCustom::GetApiClass() const
{
	return UBeamNotificationApi::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_PostCustom::GetRequestClass() const
{
	return UPostCustomRequest::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_PostCustom::GetResponseClass() const
{
	return UCommonResponse::StaticClass();
}

FString UK2BeamNode_ApiRequest_PostCustom::GetRequestSuccessDelegateName() const
{
	return TEXT("OnPostCustomSuccess");
}

FString UK2BeamNode_ApiRequest_PostCustom::GetRequestErrorDelegateName() const
{
	return TEXT("OnPostCustomError");
}

FString UK2BeamNode_ApiRequest_PostCustom::GetRequestCompleteDelegateName() const
{
	return TEXT("OnPostCustomComplete");
}

#undef LOCTEXT_NAMESPACE
