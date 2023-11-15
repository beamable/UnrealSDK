

#include "BeamableCoreBlueprintNodes/Public/BeamFlow/ApiRequest/AutoGen/Player/K2BeamNode_ApiRequest_PutPresenceStatus.h"

#include "BeamK2.h"

#include "BeamableCore/Public/AutoGen/SubSystems/BeamPlayerApi.h"
#include "BeamableCore/Public/AutoGen/SubSystems/Player/PutPresenceStatusRequest.h"
#include "BeamableCore/Public/AutoGen/OnlineStatus.h"

#define LOCTEXT_NAMESPACE "K2BeamNode_ApiRequest_PutPresenceStatus"

using namespace BeamK2;

FName UK2BeamNode_ApiRequest_PutPresenceStatus::GetSelfFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamPlayerApi, GetSelf);
}

FName UK2BeamNode_ApiRequest_PutPresenceStatus::GetRequestFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamPlayerApi, PutPresenceStatus);
}

FName UK2BeamNode_ApiRequest_PutPresenceStatus::GetMakeFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UPutPresenceStatusRequest, Make);
}

FString UK2BeamNode_ApiRequest_PutPresenceStatus::GetServiceName() const
{
	return TEXT("Player");
}

FString UK2BeamNode_ApiRequest_PutPresenceStatus::GetEndpointName() const
{
	return TEXT("PutPresenceStatus");
}

UClass* UK2BeamNode_ApiRequest_PutPresenceStatus::GetApiClass() const
{
	return UBeamPlayerApi::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_PutPresenceStatus::GetRequestClass() const
{
	return UPutPresenceStatusRequest::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_PutPresenceStatus::GetResponseClass() const
{
	return UOnlineStatus::StaticClass();
}

FString UK2BeamNode_ApiRequest_PutPresenceStatus::GetRequestSuccessDelegateName() const
{
	return TEXT("OnPutPresenceStatusSuccess");
}

FString UK2BeamNode_ApiRequest_PutPresenceStatus::GetRequestErrorDelegateName() const
{
	return TEXT("OnPutPresenceStatusError");
}

FString UK2BeamNode_ApiRequest_PutPresenceStatus::GetRequestCompleteDelegateName() const
{
	return TEXT("OnPutPresenceStatusComplete");
}

#undef LOCTEXT_NAMESPACE
