

#include "BeamableCoreBlueprintNodes/Public/BeamFlow/ApiRequest/AutoGen/Payments/K2BeamNode_ApiRequest_PostSteamAuth.h"

#include "BeamK2.h"

#include "BeamableCore/Public/AutoGen/SubSystems/BeamPaymentsApi.h"
#include "BeamableCore/Public/AutoGen/SubSystems/Payments/PostSteamAuthRequest.h"
#include "BeamableCore/Public/AutoGen/EmptyResponse.h"

#define LOCTEXT_NAMESPACE "K2BeamNode_ApiRequest_PostSteamAuth"

using namespace BeamK2;

FName UK2BeamNode_ApiRequest_PostSteamAuth::GetSelfFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamPaymentsApi, GetSelf);
}

FName UK2BeamNode_ApiRequest_PostSteamAuth::GetRequestFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamPaymentsApi, PostSteamAuth);
}

FName UK2BeamNode_ApiRequest_PostSteamAuth::GetMakeFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UPostSteamAuthRequest, Make);
}

FString UK2BeamNode_ApiRequest_PostSteamAuth::GetServiceName() const
{
	return TEXT("Payments");
}

FString UK2BeamNode_ApiRequest_PostSteamAuth::GetEndpointName() const
{
	return TEXT("PostSteamAuth");
}

UClass* UK2BeamNode_ApiRequest_PostSteamAuth::GetApiClass() const
{
	return UBeamPaymentsApi::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_PostSteamAuth::GetRequestClass() const
{
	return UPostSteamAuthRequest::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_PostSteamAuth::GetResponseClass() const
{
	return UEmptyResponse::StaticClass();
}

FString UK2BeamNode_ApiRequest_PostSteamAuth::GetRequestSuccessDelegateName() const
{
	return TEXT("OnPostSteamAuthSuccess");
}

FString UK2BeamNode_ApiRequest_PostSteamAuth::GetRequestErrorDelegateName() const
{
	return TEXT("OnPostSteamAuthError");
}

FString UK2BeamNode_ApiRequest_PostSteamAuth::GetRequestCompleteDelegateName() const
{
	return TEXT("OnPostSteamAuthComplete");
}

#undef LOCTEXT_NAMESPACE
