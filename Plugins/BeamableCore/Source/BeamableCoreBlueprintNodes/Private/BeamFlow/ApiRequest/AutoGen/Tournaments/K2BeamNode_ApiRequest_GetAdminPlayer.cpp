

#include "BeamableCoreBlueprintNodes/Public/BeamFlow/ApiRequest/AutoGen/Tournaments/K2BeamNode_ApiRequest_GetAdminPlayer.h"

#include "BeamK2.h"

#include "BeamableCore/Public/AutoGen/SubSystems/BeamTournamentsApi.h"
#include "BeamableCore/Public/AutoGen/SubSystems/Tournaments/GetAdminPlayerRequest.h"
#include "BeamableCore/Public/AutoGen/AdminGetPlayerStatusResponse.h"

#define LOCTEXT_NAMESPACE "K2BeamNode_ApiRequest_GetAdminPlayer"

using namespace BeamK2;

FName UK2BeamNode_ApiRequest_GetAdminPlayer::GetSelfFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamTournamentsApi, GetSelf);
}

FName UK2BeamNode_ApiRequest_GetAdminPlayer::GetRequestFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamTournamentsApi, GetAdminPlayer);
}

FName UK2BeamNode_ApiRequest_GetAdminPlayer::GetMakeFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UGetAdminPlayerRequest, Make);
}

FString UK2BeamNode_ApiRequest_GetAdminPlayer::GetServiceName() const
{
	return TEXT("Tournaments");
}

FString UK2BeamNode_ApiRequest_GetAdminPlayer::GetEndpointName() const
{
	return TEXT("GetAdminPlayer");
}

UClass* UK2BeamNode_ApiRequest_GetAdminPlayer::GetApiClass() const
{
	return UBeamTournamentsApi::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_GetAdminPlayer::GetRequestClass() const
{
	return UGetAdminPlayerRequest::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_GetAdminPlayer::GetResponseClass() const
{
	return UAdminGetPlayerStatusResponse::StaticClass();
}

FString UK2BeamNode_ApiRequest_GetAdminPlayer::GetRequestSuccessDelegateName() const
{
	return TEXT("OnGetAdminPlayerSuccess");
}

FString UK2BeamNode_ApiRequest_GetAdminPlayer::GetRequestErrorDelegateName() const
{
	return TEXT("OnGetAdminPlayerError");
}

FString UK2BeamNode_ApiRequest_GetAdminPlayer::GetRequestCompleteDelegateName() const
{
	return TEXT("OnGetAdminPlayerComplete");
}

#undef LOCTEXT_NAMESPACE
