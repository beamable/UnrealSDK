

#include "BeamableCoreBlueprintNodes/Public/BeamFlow/ApiRequest/AutoGen/Friends/K2BeamNode_ApiRequest_GetMy.h"

#include "BeamK2.h"

#include "BeamableCore/Public/AutoGen/SubSystems/BeamFriendsApi.h"
#include "BeamableCore/Public/AutoGen/SubSystems/Friends/GetMyRequest.h"
#include "BeamableCore/Public/AutoGen/Social.h"

#define LOCTEXT_NAMESPACE "K2BeamNode_ApiRequest_GetMy"

using namespace BeamK2;

FName UK2BeamNode_ApiRequest_GetMy::GetSelfFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamFriendsApi, GetSelf);
}

FName UK2BeamNode_ApiRequest_GetMy::GetRequestFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamFriendsApi, GetMy);
}

FName UK2BeamNode_ApiRequest_GetMy::GetMakeFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UGetMyRequest, Make);
}

FString UK2BeamNode_ApiRequest_GetMy::GetServiceName() const
{
	return TEXT("Friends");
}

FString UK2BeamNode_ApiRequest_GetMy::GetEndpointName() const
{
	return TEXT("GetMy");
}

UClass* UK2BeamNode_ApiRequest_GetMy::GetApiClass() const
{
	return UBeamFriendsApi::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_GetMy::GetRequestClass() const
{
	return UGetMyRequest::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_GetMy::GetResponseClass() const
{
	return USocial::StaticClass();
}

FString UK2BeamNode_ApiRequest_GetMy::GetRequestSuccessDelegateName() const
{
	return TEXT("OnGetMySuccess");
}

FString UK2BeamNode_ApiRequest_GetMy::GetRequestErrorDelegateName() const
{
	return TEXT("OnGetMyError");
}

FString UK2BeamNode_ApiRequest_GetMy::GetRequestCompleteDelegateName() const
{
	return TEXT("OnGetMyComplete");
}

#undef LOCTEXT_NAMESPACE
