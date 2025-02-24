

#include "BeamableCoreBlueprintNodes/Public/BeamFlow/ApiRequest/AutoGen/Auth/K2BeamNode_ApiRequest_PostTokensGuest.h"

#include "BeamK2.h"

#include "BeamableCore/Public/AutoGen/SubSystems/BeamAuthApi.h"
#include "BeamableCore/Public/AutoGen/SubSystems/Auth/PostTokensGuestRequest.h"
#include "BeamableCore/Public/AutoGen/AuthResponse.h"

#define LOCTEXT_NAMESPACE "K2BeamNode_ApiRequest_PostTokensGuest"

using namespace BeamK2;

FName UK2BeamNode_ApiRequest_PostTokensGuest::GetSelfFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamAuthApi, GetSelf);
}

FName UK2BeamNode_ApiRequest_PostTokensGuest::GetRequestFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamAuthApi, PostTokensGuest);
}

FName UK2BeamNode_ApiRequest_PostTokensGuest::GetMakeFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UPostTokensGuestRequest, Make);
}

FString UK2BeamNode_ApiRequest_PostTokensGuest::GetServiceName() const
{
	return TEXT("Auth");
}

FString UK2BeamNode_ApiRequest_PostTokensGuest::GetEndpointName() const
{
	return TEXT("PostTokensGuest");
}

UClass* UK2BeamNode_ApiRequest_PostTokensGuest::GetApiClass() const
{
	return UBeamAuthApi::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_PostTokensGuest::GetRequestClass() const
{
	return UPostTokensGuestRequest::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_PostTokensGuest::GetResponseClass() const
{
	return UAuthResponse::StaticClass();
}

FString UK2BeamNode_ApiRequest_PostTokensGuest::GetRequestSuccessDelegateName() const
{
	return TEXT("OnPostTokensGuestSuccess");
}

FString UK2BeamNode_ApiRequest_PostTokensGuest::GetRequestErrorDelegateName() const
{
	return TEXT("OnPostTokensGuestError");
}

FString UK2BeamNode_ApiRequest_PostTokensGuest::GetRequestCompleteDelegateName() const
{
	return TEXT("OnPostTokensGuestComplete");
}

#undef LOCTEXT_NAMESPACE
