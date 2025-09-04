

#include "BeamableCoreBlueprintNodes/Public/BeamFlow/ApiRequest/AutoGen/Customer/K2BeamNode_ApiRequest_PutGames.h"

#include "BeamK2.h"

#include "BeamableCore/Public/AutoGen/SubSystems/BeamCustomerApi.h"
#include "BeamableCore/Public/AutoGen/SubSystems/Customer/PutGamesRequest.h"
#include "BeamableCore/Public/AutoGen/EmptyMessage.h"

#define LOCTEXT_NAMESPACE "K2BeamNode_ApiRequest_PutGames"

using namespace BeamK2;

FName UK2BeamNode_ApiRequest_PutGames::GetSelfFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamCustomerApi, GetSelf);
}

FName UK2BeamNode_ApiRequest_PutGames::GetRequestFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamCustomerApi, PutGames);
}

FName UK2BeamNode_ApiRequest_PutGames::GetMakeFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UPutGamesRequest, Make);
}

FString UK2BeamNode_ApiRequest_PutGames::GetServiceName() const
{
	return TEXT("Customer");
}

FString UK2BeamNode_ApiRequest_PutGames::GetEndpointName() const
{
	return TEXT("PutGames");
}

UClass* UK2BeamNode_ApiRequest_PutGames::GetApiClass() const
{
	return UBeamCustomerApi::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_PutGames::GetRequestClass() const
{
	return UPutGamesRequest::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_PutGames::GetResponseClass() const
{
	return UEmptyMessage::StaticClass();
}

FString UK2BeamNode_ApiRequest_PutGames::GetRequestSuccessDelegateName() const
{
	return TEXT("OnPutGamesSuccess");
}

FString UK2BeamNode_ApiRequest_PutGames::GetRequestErrorDelegateName() const
{
	return TEXT("OnPutGamesError");
}

FString UK2BeamNode_ApiRequest_PutGames::GetRequestCompleteDelegateName() const
{
	return TEXT("OnPutGamesComplete");
}

#undef LOCTEXT_NAMESPACE
