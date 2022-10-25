

#include "BeamFlow/ApiRequest/AutoGen/ChatV2/K2BeamNode_ApiRequest_GetChatV2.h"

#include "BeamK2.h"

#include "AutoGen/SubSystems/BeamChatV2Api.h"
#include "AutoGen/SubSystems/ChatV2/GetChatV2Request.h"
#include "AutoGen/GetRoomsResponse.h"

#define LOCTEXT_NAMESPACE "K2BeamNode_ApiRequest_GetChatV2"

using namespace BeamK2;

FName UK2BeamNode_ApiRequest_GetChatV2::GetSelfFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamChatV2Api, GetSelf);
}

FName UK2BeamNode_ApiRequest_GetChatV2::GetRequestFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamChatV2Api, GetChatV2);
}

FName UK2BeamNode_ApiRequest_GetChatV2::GetMakeFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UGetChatV2Request, Make);
}

FString UK2BeamNode_ApiRequest_GetChatV2::GetServiceName() const
{
	return TEXT("ChatV2");
}

FString UK2BeamNode_ApiRequest_GetChatV2::GetEndpointName() const
{
	return TEXT("GetChatV2");
}

UClass* UK2BeamNode_ApiRequest_GetChatV2::GetApiClass() const
{
	return UBeamChatV2Api::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_GetChatV2::GetRequestClass() const
{
	return UGetChatV2Request::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_GetChatV2::GetResponseClass() const
{
	return UGetRoomsResponse::StaticClass();
}

FString UK2BeamNode_ApiRequest_GetChatV2::GetRequestSuccessDelegateName() const
{
	return TEXT("OnGetChatV2Success");
}

FString UK2BeamNode_ApiRequest_GetChatV2::GetRequestErrorDelegateName() const
{
	return TEXT("OnGetChatV2Error");
}

FString UK2BeamNode_ApiRequest_GetChatV2::GetRequestCompleteDelegateName() const
{
	return TEXT("OnGetChatV2Complete");
}

#undef LOCTEXT_NAMESPACE
