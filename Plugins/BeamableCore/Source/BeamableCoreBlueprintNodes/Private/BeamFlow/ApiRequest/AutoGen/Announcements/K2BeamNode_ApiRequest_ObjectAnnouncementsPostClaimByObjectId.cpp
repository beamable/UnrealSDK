

#include "BeamableCoreBlueprintNodes/Public/BeamFlow/ApiRequest/AutoGen/Announcements/K2BeamNode_ApiRequest_ObjectAnnouncementsPostClaimByObjectId.h"

#include "BeamK2.h"

#include "BeamableCore/Public/AutoGen/SubSystems/BeamAnnouncementsApi.h"
#include "BeamableCore/Public/AutoGen/SubSystems/Announcements/ObjectAnnouncementsPostClaimByObjectIdRequest.h"
#include "BeamableCore/Public/AutoGen/CommonResponse.h"

#define LOCTEXT_NAMESPACE "K2BeamNode_ApiRequest_ObjectAnnouncementsPostClaimByObjectId"

using namespace BeamK2;

FName UK2BeamNode_ApiRequest_ObjectAnnouncementsPostClaimByObjectId::GetSelfFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamAnnouncementsApi, GetSelf);
}

FName UK2BeamNode_ApiRequest_ObjectAnnouncementsPostClaimByObjectId::GetRequestFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamAnnouncementsApi, PostClaim);
}

FName UK2BeamNode_ApiRequest_ObjectAnnouncementsPostClaimByObjectId::GetMakeFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UObjectAnnouncementsPostClaimByObjectIdRequest, Make);
}

FString UK2BeamNode_ApiRequest_ObjectAnnouncementsPostClaimByObjectId::GetServiceName() const
{
	return TEXT("Announcements");
}

FString UK2BeamNode_ApiRequest_ObjectAnnouncementsPostClaimByObjectId::GetEndpointName() const
{
	return TEXT("PostClaim");
}

UClass* UK2BeamNode_ApiRequest_ObjectAnnouncementsPostClaimByObjectId::GetApiClass() const
{
	return UBeamAnnouncementsApi::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_ObjectAnnouncementsPostClaimByObjectId::GetRequestClass() const
{
	return UObjectAnnouncementsPostClaimByObjectIdRequest::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_ObjectAnnouncementsPostClaimByObjectId::GetResponseClass() const
{
	return UCommonResponse::StaticClass();
}

FString UK2BeamNode_ApiRequest_ObjectAnnouncementsPostClaimByObjectId::GetRequestSuccessDelegateName() const
{
	return TEXT("OnObjectAnnouncementsPostClaimByObjectIdSuccess");
}

FString UK2BeamNode_ApiRequest_ObjectAnnouncementsPostClaimByObjectId::GetRequestErrorDelegateName() const
{
	return TEXT("OnObjectAnnouncementsPostClaimByObjectIdError");
}

FString UK2BeamNode_ApiRequest_ObjectAnnouncementsPostClaimByObjectId::GetRequestCompleteDelegateName() const
{
	return TEXT("OnObjectAnnouncementsPostClaimByObjectIdComplete");
}

#undef LOCTEXT_NAMESPACE
