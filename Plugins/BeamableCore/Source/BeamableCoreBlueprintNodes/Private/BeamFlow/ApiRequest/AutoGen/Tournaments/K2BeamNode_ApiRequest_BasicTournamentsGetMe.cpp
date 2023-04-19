

#include "BeamableCoreBlueprintNodes/Public/BeamFlow/ApiRequest/AutoGen/Tournaments/K2BeamNode_ApiRequest_BasicTournamentsGetMe.h"

#include "BeamK2.h"

#include "BeamableCore/Public/AutoGen/SubSystems/BeamTournamentsApi.h"
#include "BeamableCore/Public/AutoGen/SubSystems/Tournaments/BasicTournamentsGetMeRequest.h"
#include "BeamableCore/Public/AutoGen/GetPlayerStatusResponse.h"

#define LOCTEXT_NAMESPACE "K2BeamNode_ApiRequest_BasicTournamentsGetMe"

using namespace BeamK2;

FName UK2BeamNode_ApiRequest_BasicTournamentsGetMe::GetSelfFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamTournamentsApi, GetSelf);
}

FName UK2BeamNode_ApiRequest_BasicTournamentsGetMe::GetRequestFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamTournamentsApi, GetMe);
}

FName UK2BeamNode_ApiRequest_BasicTournamentsGetMe::GetMakeFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBasicTournamentsGetMeRequest, Make);
}

FString UK2BeamNode_ApiRequest_BasicTournamentsGetMe::GetServiceName() const
{
	return TEXT("Tournaments");
}

FString UK2BeamNode_ApiRequest_BasicTournamentsGetMe::GetEndpointName() const
{
	return TEXT("GetMe");
}

UClass* UK2BeamNode_ApiRequest_BasicTournamentsGetMe::GetApiClass() const
{
	return UBeamTournamentsApi::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_BasicTournamentsGetMe::GetRequestClass() const
{
	return UBasicTournamentsGetMeRequest::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_BasicTournamentsGetMe::GetResponseClass() const
{
	return UGetPlayerStatusResponse::StaticClass();
}

FString UK2BeamNode_ApiRequest_BasicTournamentsGetMe::GetRequestSuccessDelegateName() const
{
	return TEXT("OnBasicTournamentsGetMeSuccess");
}

FString UK2BeamNode_ApiRequest_BasicTournamentsGetMe::GetRequestErrorDelegateName() const
{
	return TEXT("OnBasicTournamentsGetMeError");
}

FString UK2BeamNode_ApiRequest_BasicTournamentsGetMe::GetRequestCompleteDelegateName() const
{
	return TEXT("OnBasicTournamentsGetMeComplete");
}

#undef LOCTEXT_NAMESPACE
