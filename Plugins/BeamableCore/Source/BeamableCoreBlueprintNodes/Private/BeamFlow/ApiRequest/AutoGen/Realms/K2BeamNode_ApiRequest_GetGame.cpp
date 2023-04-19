

#include "BeamableCoreBlueprintNodes/Public/BeamFlow/ApiRequest/AutoGen/Realms/K2BeamNode_ApiRequest_GetGame.h"

#include "BeamK2.h"

#include "BeamableCore/Public/AutoGen/SubSystems/BeamRealmsApi.h"
#include "BeamableCore/Public/AutoGen/SubSystems/Realms/GetGameRequest.h"
#include "BeamableCore/Public/AutoGen/GetGameResponse.h"

#define LOCTEXT_NAMESPACE "K2BeamNode_ApiRequest_GetGame"

using namespace BeamK2;

FName UK2BeamNode_ApiRequest_GetGame::GetSelfFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamRealmsApi, GetSelf);
}

FName UK2BeamNode_ApiRequest_GetGame::GetRequestFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamRealmsApi, GetGame);
}

FName UK2BeamNode_ApiRequest_GetGame::GetMakeFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UGetGameRequest, Make);
}

FString UK2BeamNode_ApiRequest_GetGame::GetServiceName() const
{
	return TEXT("Realms");
}

FString UK2BeamNode_ApiRequest_GetGame::GetEndpointName() const
{
	return TEXT("GetGame");
}

UClass* UK2BeamNode_ApiRequest_GetGame::GetApiClass() const
{
	return UBeamRealmsApi::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_GetGame::GetRequestClass() const
{
	return UGetGameRequest::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_GetGame::GetResponseClass() const
{
	return UGetGameResponse::StaticClass();
}

FString UK2BeamNode_ApiRequest_GetGame::GetRequestSuccessDelegateName() const
{
	return TEXT("OnGetGameSuccess");
}

FString UK2BeamNode_ApiRequest_GetGame::GetRequestErrorDelegateName() const
{
	return TEXT("OnGetGameError");
}

FString UK2BeamNode_ApiRequest_GetGame::GetRequestCompleteDelegateName() const
{
	return TEXT("OnGetGameComplete");
}

#undef LOCTEXT_NAMESPACE
