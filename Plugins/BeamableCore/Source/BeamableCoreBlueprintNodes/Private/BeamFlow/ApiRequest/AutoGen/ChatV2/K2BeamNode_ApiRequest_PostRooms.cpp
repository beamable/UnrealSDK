

#include "BeamableCoreBlueprintNodes/Public/BeamFlow/ApiRequest/AutoGen/ChatV2/K2BeamNode_ApiRequest_PostRooms.h"

#include "BeamK2.h"

#include "BeamableCore/Public/AutoGen/SubSystems/BeamChatV2Api.h"
#include "BeamableCore/Public/AutoGen/SubSystems/ChatV2/PostRoomsRequest.h"
#include "BeamableCore/Public/AutoGen/CreateRoomResponse.h"

#define LOCTEXT_NAMESPACE "K2BeamNode_ApiRequest_PostRooms"

using namespace BeamK2;

FName UK2BeamNode_ApiRequest_PostRooms::GetSelfFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamChatV2Api, GetSelf);
}

FName UK2BeamNode_ApiRequest_PostRooms::GetRequestFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamChatV2Api, PostRooms);
}

FName UK2BeamNode_ApiRequest_PostRooms::GetMakeFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UPostRoomsRequest, Make);
}

FString UK2BeamNode_ApiRequest_PostRooms::GetServiceName() const
{
	return TEXT("ChatV2");
}

FString UK2BeamNode_ApiRequest_PostRooms::GetEndpointName() const
{
	return TEXT("PostRooms");
}

UClass* UK2BeamNode_ApiRequest_PostRooms::GetApiClass() const
{
	return UBeamChatV2Api::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_PostRooms::GetRequestClass() const
{
	return UPostRoomsRequest::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_PostRooms::GetResponseClass() const
{
	return UCreateRoomResponse::StaticClass();
}

FString UK2BeamNode_ApiRequest_PostRooms::GetRequestSuccessDelegateName() const
{
	return TEXT("OnPostRoomsSuccess");
}

FString UK2BeamNode_ApiRequest_PostRooms::GetRequestErrorDelegateName() const
{
	return TEXT("OnPostRoomsError");
}

FString UK2BeamNode_ApiRequest_PostRooms::GetRequestCompleteDelegateName() const
{
	return TEXT("OnPostRoomsComplete");
}

#undef LOCTEXT_NAMESPACE
