

#include "BeamableUnrealMicroserviceClientsBp/Public/AutoGen/HathoraDemo/K2BeamNode_ApiRequest_HathoraDemoInitializePlayer.h"

#include "BeamK2.h"

#include "BeamableUnrealMicroserviceClients/Public/AutoGen/SubSystems/BeamHathoraDemoApi.h"
#include "BeamableUnrealMicroserviceClients/Public/AutoGen/SubSystems/HathoraDemo/HathoraDemoInitializePlayerRequest.h"
#include "Serialization/BeamPlainTextResponseBody.h"

#define LOCTEXT_NAMESPACE "K2BeamNode_ApiRequest_HathoraDemoInitializePlayer"

using namespace BeamK2;

FName UK2BeamNode_ApiRequest_HathoraDemoInitializePlayer::GetSelfFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamHathoraDemoApi, GetSelf);
}

FName UK2BeamNode_ApiRequest_HathoraDemoInitializePlayer::GetRequestFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamHathoraDemoApi, InitializePlayer);
}

FName UK2BeamNode_ApiRequest_HathoraDemoInitializePlayer::GetMakeFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UHathoraDemoInitializePlayerRequest, Make);
}

FString UK2BeamNode_ApiRequest_HathoraDemoInitializePlayer::GetServiceName() const
{
	return TEXT("HathoraDemo");
}

FString UK2BeamNode_ApiRequest_HathoraDemoInitializePlayer::GetEndpointName() const
{
	return TEXT("InitializePlayer");
}

UClass* UK2BeamNode_ApiRequest_HathoraDemoInitializePlayer::GetApiClass() const
{
	return UBeamHathoraDemoApi::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_HathoraDemoInitializePlayer::GetRequestClass() const
{
	return UHathoraDemoInitializePlayerRequest::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_HathoraDemoInitializePlayer::GetResponseClass() const
{
	return UBeamPlainTextResponseBody::StaticClass();
}

FString UK2BeamNode_ApiRequest_HathoraDemoInitializePlayer::GetRequestSuccessDelegateName() const
{
	return TEXT("OnHathoraDemoInitializePlayerSuccess");
}

FString UK2BeamNode_ApiRequest_HathoraDemoInitializePlayer::GetRequestErrorDelegateName() const
{
	return TEXT("OnHathoraDemoInitializePlayerError");
}

FString UK2BeamNode_ApiRequest_HathoraDemoInitializePlayer::GetRequestCompleteDelegateName() const
{
	return TEXT("OnHathoraDemoInitializePlayerComplete");
}

#undef LOCTEXT_NAMESPACE
