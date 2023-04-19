

#include "BeamableCoreBlueprintNodes/Public/BeamFlow/ApiRequest/AutoGen/Notification/K2BeamNode_ApiRequest_PostGeneric.h"

#include "BeamK2.h"

#include "BeamableCore/Public/AutoGen/SubSystems/BeamNotificationApi.h"
#include "BeamableCore/Public/AutoGen/SubSystems/Notification/PostGenericRequest.h"
#include "BeamableCore/Public/AutoGen/CommonResponse.h"

#define LOCTEXT_NAMESPACE "K2BeamNode_ApiRequest_PostGeneric"

using namespace BeamK2;

FName UK2BeamNode_ApiRequest_PostGeneric::GetSelfFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamNotificationApi, GetSelf);
}

FName UK2BeamNode_ApiRequest_PostGeneric::GetRequestFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamNotificationApi, PostGeneric);
}

FName UK2BeamNode_ApiRequest_PostGeneric::GetMakeFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UPostGenericRequest, Make);
}

FString UK2BeamNode_ApiRequest_PostGeneric::GetServiceName() const
{
	return TEXT("Notification");
}

FString UK2BeamNode_ApiRequest_PostGeneric::GetEndpointName() const
{
	return TEXT("PostGeneric");
}

UClass* UK2BeamNode_ApiRequest_PostGeneric::GetApiClass() const
{
	return UBeamNotificationApi::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_PostGeneric::GetRequestClass() const
{
	return UPostGenericRequest::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_PostGeneric::GetResponseClass() const
{
	return UCommonResponse::StaticClass();
}

FString UK2BeamNode_ApiRequest_PostGeneric::GetRequestSuccessDelegateName() const
{
	return TEXT("OnPostGenericSuccess");
}

FString UK2BeamNode_ApiRequest_PostGeneric::GetRequestErrorDelegateName() const
{
	return TEXT("OnPostGenericError");
}

FString UK2BeamNode_ApiRequest_PostGeneric::GetRequestCompleteDelegateName() const
{
	return TEXT("OnPostGenericComplete");
}

#undef LOCTEXT_NAMESPACE
