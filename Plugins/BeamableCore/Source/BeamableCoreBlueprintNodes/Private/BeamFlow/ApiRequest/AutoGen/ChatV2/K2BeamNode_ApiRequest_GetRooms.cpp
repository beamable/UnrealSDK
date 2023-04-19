

#include "BeamableCoreBlueprintNodes/Public/BeamFlow/ApiRequest/AutoGen/ChatV2/K2BeamNode_ApiRequest_GetRooms.h"

#include "BeamK2.h"

#include "BeamableCore/Public/AutoGen/SubSystems/BeamChatV2Api.h"
#include "BeamableCore/Public/AutoGen/SubSystems/ChatV2/GetRoomsRequest.h"
#include "BeamableCore/Public/AutoGen/GetRoomsResponse.h"

#define LOCTEXT_NAMESPACE "K2BeamNode_ApiRequest_GetRooms"

using namespace BeamK2;

FName UK2BeamNode_ApiRequest_GetRooms::GetSelfFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamChatV2Api, GetSelf);
}

FName UK2BeamNode_ApiRequest_GetRooms::GetRequestFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamChatV2Api, GetRooms);
}

FName UK2BeamNode_ApiRequest_GetRooms::GetMakeFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UGetRoomsRequest, Make);
}

FString UK2BeamNode_ApiRequest_GetRooms::GetServiceName() const
{
	return TEXT("ChatV2");
}

FString UK2BeamNode_ApiRequest_GetRooms::GetEndpointName() const
{
	return TEXT("GetRooms");
}

UClass* UK2BeamNode_ApiRequest_GetRooms::GetApiClass() const
{
	return UBeamChatV2Api::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_GetRooms::GetRequestClass() const
{
	return UGetRoomsRequest::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_GetRooms::GetResponseClass() const
{
	return UGetRoomsResponse::StaticClass();
}

FString UK2BeamNode_ApiRequest_GetRooms::GetRequestSuccessDelegateName() const
{
	return TEXT("OnGetRoomsSuccess");
}

FString UK2BeamNode_ApiRequest_GetRooms::GetRequestErrorDelegateName() const
{
	return TEXT("OnGetRoomsError");
}

FString UK2BeamNode_ApiRequest_GetRooms::GetRequestCompleteDelegateName() const
{
	return TEXT("OnGetRoomsComplete");
}

#undef LOCTEXT_NAMESPACE
