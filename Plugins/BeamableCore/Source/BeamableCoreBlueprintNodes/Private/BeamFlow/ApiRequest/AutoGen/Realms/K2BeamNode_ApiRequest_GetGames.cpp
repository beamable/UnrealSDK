

#include "BeamableCoreBlueprintNodes/Public/BeamFlow/ApiRequest/AutoGen/Realms/K2BeamNode_ApiRequest_GetGames.h"

#include "BeamK2.h"

#include "BeamableCore/Public/AutoGen/SubSystems/BeamRealmsApi.h"
#include "BeamableCore/Public/AutoGen/SubSystems/Realms/GetGamesRequest.h"
#include "BeamableCore/Public/AutoGen/GetGameResponse.h"

#define LOCTEXT_NAMESPACE "K2BeamNode_ApiRequest_GetGames"

using namespace BeamK2;

FName UK2BeamNode_ApiRequest_GetGames::GetSelfFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamRealmsApi, GetSelf);
}

FName UK2BeamNode_ApiRequest_GetGames::GetRequestFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamRealmsApi, GetGames);
}

FName UK2BeamNode_ApiRequest_GetGames::GetMakeFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UGetGamesRequest, Make);
}

FString UK2BeamNode_ApiRequest_GetGames::GetServiceName() const
{
	return TEXT("Realms");
}

FString UK2BeamNode_ApiRequest_GetGames::GetEndpointName() const
{
	return TEXT("GetGames");
}

UClass* UK2BeamNode_ApiRequest_GetGames::GetApiClass() const
{
	return UBeamRealmsApi::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_GetGames::GetRequestClass() const
{
	return UGetGamesRequest::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_GetGames::GetResponseClass() const
{
	return UGetGameResponse::StaticClass();
}

FString UK2BeamNode_ApiRequest_GetGames::GetRequestSuccessDelegateName() const
{
	return TEXT("OnGetGamesSuccess");
}

FString UK2BeamNode_ApiRequest_GetGames::GetRequestErrorDelegateName() const
{
	return TEXT("OnGetGamesError");
}

FString UK2BeamNode_ApiRequest_GetGames::GetRequestCompleteDelegateName() const
{
	return TEXT("OnGetGamesComplete");
}

#undef LOCTEXT_NAMESPACE
