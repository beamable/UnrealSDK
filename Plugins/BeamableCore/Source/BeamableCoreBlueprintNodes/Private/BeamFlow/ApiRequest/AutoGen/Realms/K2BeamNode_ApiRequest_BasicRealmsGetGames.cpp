

#include "BeamableCoreBlueprintNodes/Public/BeamFlow/ApiRequest/AutoGen/Realms/K2BeamNode_ApiRequest_BasicRealmsGetGames.h"

#include "BeamK2.h"

#include "BeamableCore/Public/AutoGen/SubSystems/BeamRealmsApi.h"
#include "BeamableCore/Public/AutoGen/SubSystems/Realms/BasicRealmsGetGamesRequest.h"
#include "BeamableCore/Public/AutoGen/GetGameResponse.h"

#define LOCTEXT_NAMESPACE "K2BeamNode_ApiRequest_BasicRealmsGetGames"

using namespace BeamK2;

FName UK2BeamNode_ApiRequest_BasicRealmsGetGames::GetSelfFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamRealmsApi, GetSelf);
}

FName UK2BeamNode_ApiRequest_BasicRealmsGetGames::GetRequestFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamRealmsApi, GetGames);
}

FName UK2BeamNode_ApiRequest_BasicRealmsGetGames::GetMakeFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBasicRealmsGetGamesRequest, Make);
}

FString UK2BeamNode_ApiRequest_BasicRealmsGetGames::GetServiceName() const
{
	return TEXT("Realms");
}

FString UK2BeamNode_ApiRequest_BasicRealmsGetGames::GetEndpointName() const
{
	return TEXT("GetGames");
}

UClass* UK2BeamNode_ApiRequest_BasicRealmsGetGames::GetApiClass() const
{
	return UBeamRealmsApi::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_BasicRealmsGetGames::GetRequestClass() const
{
	return UBasicRealmsGetGamesRequest::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_BasicRealmsGetGames::GetResponseClass() const
{
	return UGetGameResponse::StaticClass();
}

FString UK2BeamNode_ApiRequest_BasicRealmsGetGames::GetRequestSuccessDelegateName() const
{
	return TEXT("OnBasicRealmsGetGamesSuccess");
}

FString UK2BeamNode_ApiRequest_BasicRealmsGetGames::GetRequestErrorDelegateName() const
{
	return TEXT("OnBasicRealmsGetGamesError");
}

FString UK2BeamNode_ApiRequest_BasicRealmsGetGames::GetRequestCompleteDelegateName() const
{
	return TEXT("OnBasicRealmsGetGamesComplete");
}

#undef LOCTEXT_NAMESPACE
