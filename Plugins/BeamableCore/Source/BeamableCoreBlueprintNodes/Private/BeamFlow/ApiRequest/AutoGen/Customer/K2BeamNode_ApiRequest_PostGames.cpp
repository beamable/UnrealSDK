

#include "BeamableCoreBlueprintNodes/Public/BeamFlow/ApiRequest/AutoGen/Customer/K2BeamNode_ApiRequest_PostGames.h"

#include "BeamK2.h"

#include "BeamableCore/Public/AutoGen/SubSystems/BeamCustomerApi.h"
#include "BeamableCore/Public/AutoGen/SubSystems/Customer/PostGamesRequest.h"
#include "BeamableCore/Public/AutoGen/RealmView.h"

#define LOCTEXT_NAMESPACE "K2BeamNode_ApiRequest_PostGames"

using namespace BeamK2;

FName UK2BeamNode_ApiRequest_PostGames::GetSelfFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamCustomerApi, GetSelf);
}

FName UK2BeamNode_ApiRequest_PostGames::GetRequestFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamCustomerApi, PostGames);
}

FName UK2BeamNode_ApiRequest_PostGames::GetMakeFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UPostGamesRequest, Make);
}

FString UK2BeamNode_ApiRequest_PostGames::GetServiceName() const
{
	return TEXT("Customer");
}

FString UK2BeamNode_ApiRequest_PostGames::GetEndpointName() const
{
	return TEXT("PostGames");
}

UClass* UK2BeamNode_ApiRequest_PostGames::GetApiClass() const
{
	return UBeamCustomerApi::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_PostGames::GetRequestClass() const
{
	return UPostGamesRequest::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_PostGames::GetResponseClass() const
{
	return URealmView::StaticClass();
}

FString UK2BeamNode_ApiRequest_PostGames::GetRequestSuccessDelegateName() const
{
	return TEXT("OnPostGamesSuccess");
}

FString UK2BeamNode_ApiRequest_PostGames::GetRequestErrorDelegateName() const
{
	return TEXT("OnPostGamesError");
}

FString UK2BeamNode_ApiRequest_PostGames::GetRequestCompleteDelegateName() const
{
	return TEXT("OnPostGamesComplete");
}

#undef LOCTEXT_NAMESPACE
