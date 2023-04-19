

#include "BeamableCoreBlueprintNodes/Public/BeamFlow/ApiRequest/AutoGen/Realms/K2BeamNode_ApiRequest_PutGame.h"

#include "BeamK2.h"

#include "BeamableCore/Public/AutoGen/SubSystems/BeamRealmsApi.h"
#include "BeamableCore/Public/AutoGen/SubSystems/Realms/PutGameRequest.h"
#include "BeamableCore/Public/AutoGen/CommonResponse.h"

#define LOCTEXT_NAMESPACE "K2BeamNode_ApiRequest_PutGame"

using namespace BeamK2;

FName UK2BeamNode_ApiRequest_PutGame::GetSelfFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamRealmsApi, GetSelf);
}

FName UK2BeamNode_ApiRequest_PutGame::GetRequestFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamRealmsApi, PutGame);
}

FName UK2BeamNode_ApiRequest_PutGame::GetMakeFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UPutGameRequest, Make);
}

FString UK2BeamNode_ApiRequest_PutGame::GetServiceName() const
{
	return TEXT("Realms");
}

FString UK2BeamNode_ApiRequest_PutGame::GetEndpointName() const
{
	return TEXT("PutGame");
}

UClass* UK2BeamNode_ApiRequest_PutGame::GetApiClass() const
{
	return UBeamRealmsApi::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_PutGame::GetRequestClass() const
{
	return UPutGameRequest::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_PutGame::GetResponseClass() const
{
	return UCommonResponse::StaticClass();
}

FString UK2BeamNode_ApiRequest_PutGame::GetRequestSuccessDelegateName() const
{
	return TEXT("OnPutGameSuccess");
}

FString UK2BeamNode_ApiRequest_PutGame::GetRequestErrorDelegateName() const
{
	return TEXT("OnPutGameError");
}

FString UK2BeamNode_ApiRequest_PutGame::GetRequestCompleteDelegateName() const
{
	return TEXT("OnPutGameComplete");
}

#undef LOCTEXT_NAMESPACE
