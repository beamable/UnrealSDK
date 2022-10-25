

#include "BeamFlow/ApiRequest/AutoGen/Matchmaking/K2BeamNode_ApiRequest_PutTick.h"

#include "BeamK2.h"

#include "AutoGen/SubSystems/BeamMatchmakingApi.h"
#include "AutoGen/SubSystems/Matchmaking/PutTickRequest.h"
#include "AutoGen/EmptyResponse.h"

#define LOCTEXT_NAMESPACE "K2BeamNode_ApiRequest_PutTick"

using namespace BeamK2;

FName UK2BeamNode_ApiRequest_PutTick::GetSelfFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamMatchmakingApi, GetSelf);
}

FName UK2BeamNode_ApiRequest_PutTick::GetRequestFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamMatchmakingApi, PutTick);
}

FName UK2BeamNode_ApiRequest_PutTick::GetMakeFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UPutTickRequest, Make);
}

FString UK2BeamNode_ApiRequest_PutTick::GetServiceName() const
{
	return TEXT("Matchmaking");
}

FString UK2BeamNode_ApiRequest_PutTick::GetEndpointName() const
{
	return TEXT("PutTick");
}

UClass* UK2BeamNode_ApiRequest_PutTick::GetApiClass() const
{
	return UBeamMatchmakingApi::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_PutTick::GetRequestClass() const
{
	return UPutTickRequest::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_PutTick::GetResponseClass() const
{
	return UEmptyResponse::StaticClass();
}

FString UK2BeamNode_ApiRequest_PutTick::GetRequestSuccessDelegateName() const
{
	return TEXT("OnPutTickSuccess");
}

FString UK2BeamNode_ApiRequest_PutTick::GetRequestErrorDelegateName() const
{
	return TEXT("OnPutTickError");
}

FString UK2BeamNode_ApiRequest_PutTick::GetRequestCompleteDelegateName() const
{
	return TEXT("OnPutTickComplete");
}

#undef LOCTEXT_NAMESPACE
