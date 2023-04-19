

#include "BeamableCoreBlueprintNodes/Public/BeamFlow/ApiRequest/AutoGen/ChatV2/K2BeamNode_ApiRequest_DeleteRooms.h"

#include "BeamK2.h"

#include "BeamableCore/Public/AutoGen/SubSystems/BeamChatV2Api.h"
#include "BeamableCore/Public/AutoGen/SubSystems/ChatV2/DeleteRoomsRequest.h"
#include "BeamableCore/Public/AutoGen/LeaveRoomResponse.h"

#define LOCTEXT_NAMESPACE "K2BeamNode_ApiRequest_DeleteRooms"

using namespace BeamK2;

FName UK2BeamNode_ApiRequest_DeleteRooms::GetSelfFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamChatV2Api, GetSelf);
}

FName UK2BeamNode_ApiRequest_DeleteRooms::GetRequestFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamChatV2Api, DeleteRooms);
}

FName UK2BeamNode_ApiRequest_DeleteRooms::GetMakeFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UDeleteRoomsRequest, Make);
}

FString UK2BeamNode_ApiRequest_DeleteRooms::GetServiceName() const
{
	return TEXT("ChatV2");
}

FString UK2BeamNode_ApiRequest_DeleteRooms::GetEndpointName() const
{
	return TEXT("DeleteRooms");
}

UClass* UK2BeamNode_ApiRequest_DeleteRooms::GetApiClass() const
{
	return UBeamChatV2Api::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_DeleteRooms::GetRequestClass() const
{
	return UDeleteRoomsRequest::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_DeleteRooms::GetResponseClass() const
{
	return ULeaveRoomResponse::StaticClass();
}

FString UK2BeamNode_ApiRequest_DeleteRooms::GetRequestSuccessDelegateName() const
{
	return TEXT("OnDeleteRoomsSuccess");
}

FString UK2BeamNode_ApiRequest_DeleteRooms::GetRequestErrorDelegateName() const
{
	return TEXT("OnDeleteRoomsError");
}

FString UK2BeamNode_ApiRequest_DeleteRooms::GetRequestCompleteDelegateName() const
{
	return TEXT("OnDeleteRoomsComplete");
}

#undef LOCTEXT_NAMESPACE
