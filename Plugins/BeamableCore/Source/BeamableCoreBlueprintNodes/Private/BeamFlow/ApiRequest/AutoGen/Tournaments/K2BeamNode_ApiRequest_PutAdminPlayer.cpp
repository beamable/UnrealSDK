

#include "BeamableCoreBlueprintNodes/Public/BeamFlow/ApiRequest/AutoGen/Tournaments/K2BeamNode_ApiRequest_PutAdminPlayer.h"

#include "BeamK2.h"

#include "BeamableCore/Public/AutoGen/SubSystems/BeamTournamentsApi.h"
#include "BeamableCore/Public/AutoGen/SubSystems/Tournaments/PutAdminPlayerRequest.h"
#include "BeamableCore/Public/AutoGen/AdminPlayerStatus.h"

#define LOCTEXT_NAMESPACE "K2BeamNode_ApiRequest_PutAdminPlayer"

using namespace BeamK2;

FName UK2BeamNode_ApiRequest_PutAdminPlayer::GetSelfFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamTournamentsApi, GetSelf);
}

FName UK2BeamNode_ApiRequest_PutAdminPlayer::GetRequestFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamTournamentsApi, PutAdminPlayer);
}

FName UK2BeamNode_ApiRequest_PutAdminPlayer::GetMakeFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UPutAdminPlayerRequest, Make);
}

FString UK2BeamNode_ApiRequest_PutAdminPlayer::GetServiceName() const
{
	return TEXT("Tournaments");
}

FString UK2BeamNode_ApiRequest_PutAdminPlayer::GetEndpointName() const
{
	return TEXT("PutAdminPlayer");
}

UClass* UK2BeamNode_ApiRequest_PutAdminPlayer::GetApiClass() const
{
	return UBeamTournamentsApi::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_PutAdminPlayer::GetRequestClass() const
{
	return UPutAdminPlayerRequest::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_PutAdminPlayer::GetResponseClass() const
{
	return UAdminPlayerStatus::StaticClass();
}

FString UK2BeamNode_ApiRequest_PutAdminPlayer::GetRequestSuccessDelegateName() const
{
	return TEXT("OnPutAdminPlayerSuccess");
}

FString UK2BeamNode_ApiRequest_PutAdminPlayer::GetRequestErrorDelegateName() const
{
	return TEXT("OnPutAdminPlayerError");
}

FString UK2BeamNode_ApiRequest_PutAdminPlayer::GetRequestCompleteDelegateName() const
{
	return TEXT("OnPutAdminPlayerComplete");
}

#undef LOCTEXT_NAMESPACE
