

#include "BeamableCoreBlueprintNodes/Public/BeamFlow/ApiRequest/AutoGen/Realms/K2BeamNode_ApiRequest_BasicRealmsPostGame.h"

#include "BeamK2.h"

#include "BeamableCore/Public/AutoGen/SubSystems/BeamRealmsApi.h"
#include "BeamableCore/Public/AutoGen/SubSystems/Realms/BasicRealmsPostGameRequest.h"
#include "BeamableCore/Public/AutoGen/CommonResponse.h"

#define LOCTEXT_NAMESPACE "K2BeamNode_ApiRequest_BasicRealmsPostGame"

using namespace BeamK2;

FName UK2BeamNode_ApiRequest_BasicRealmsPostGame::GetSelfFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamRealmsApi, GetSelf);
}

FName UK2BeamNode_ApiRequest_BasicRealmsPostGame::GetRequestFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamRealmsApi, PostGame);
}

FName UK2BeamNode_ApiRequest_BasicRealmsPostGame::GetMakeFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBasicRealmsPostGameRequest, Make);
}

FString UK2BeamNode_ApiRequest_BasicRealmsPostGame::GetServiceName() const
{
	return TEXT("Realms");
}

FString UK2BeamNode_ApiRequest_BasicRealmsPostGame::GetEndpointName() const
{
	return TEXT("PostGame");
}

UClass* UK2BeamNode_ApiRequest_BasicRealmsPostGame::GetApiClass() const
{
	return UBeamRealmsApi::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_BasicRealmsPostGame::GetRequestClass() const
{
	return UBasicRealmsPostGameRequest::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_BasicRealmsPostGame::GetResponseClass() const
{
	return UCommonResponse::StaticClass();
}

FString UK2BeamNode_ApiRequest_BasicRealmsPostGame::GetRequestSuccessDelegateName() const
{
	return TEXT("OnBasicRealmsPostGameSuccess");
}

FString UK2BeamNode_ApiRequest_BasicRealmsPostGame::GetRequestErrorDelegateName() const
{
	return TEXT("OnBasicRealmsPostGameError");
}

FString UK2BeamNode_ApiRequest_BasicRealmsPostGame::GetRequestCompleteDelegateName() const
{
	return TEXT("OnBasicRealmsPostGameComplete");
}

#undef LOCTEXT_NAMESPACE
