

#include "BeamableCoreBlueprintNodes/Public/BeamFlow/ApiRequest/AutoGen/Announcements/K2BeamNode_ApiRequest_ObjectAnnouncementsPostClaim.h"

#include "BeamK2.h"

#include "BeamableCore/Public/AutoGen/SubSystems/BeamAnnouncementsApi.h"
#include "BeamableCore/Public/AutoGen/SubSystems/Announcements/ObjectAnnouncementsPostClaimRequest.h"
#include "BeamableCore/Public/AutoGen/CommonResponse.h"

#define LOCTEXT_NAMESPACE "K2BeamNode_ApiRequest_ObjectAnnouncementsPostClaim"

using namespace BeamK2;

FName UK2BeamNode_ApiRequest_ObjectAnnouncementsPostClaim::GetSelfFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamAnnouncementsApi, GetSelf);
}

FName UK2BeamNode_ApiRequest_ObjectAnnouncementsPostClaim::GetRequestFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamAnnouncementsApi, PostClaim);
}

FName UK2BeamNode_ApiRequest_ObjectAnnouncementsPostClaim::GetMakeFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UObjectAnnouncementsPostClaimRequest, Make);
}

FString UK2BeamNode_ApiRequest_ObjectAnnouncementsPostClaim::GetServiceName() const
{
	return TEXT("Announcements");
}

FString UK2BeamNode_ApiRequest_ObjectAnnouncementsPostClaim::GetEndpointName() const
{
	return TEXT("PostClaim");
}

UClass* UK2BeamNode_ApiRequest_ObjectAnnouncementsPostClaim::GetApiClass() const
{
	return UBeamAnnouncementsApi::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_ObjectAnnouncementsPostClaim::GetRequestClass() const
{
	return UObjectAnnouncementsPostClaimRequest::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_ObjectAnnouncementsPostClaim::GetResponseClass() const
{
	return UCommonResponse::StaticClass();
}

FString UK2BeamNode_ApiRequest_ObjectAnnouncementsPostClaim::GetRequestSuccessDelegateName() const
{
	return TEXT("OnObjectAnnouncementsPostClaimSuccess");
}

FString UK2BeamNode_ApiRequest_ObjectAnnouncementsPostClaim::GetRequestErrorDelegateName() const
{
	return TEXT("OnObjectAnnouncementsPostClaimError");
}

FString UK2BeamNode_ApiRequest_ObjectAnnouncementsPostClaim::GetRequestCompleteDelegateName() const
{
	return TEXT("OnObjectAnnouncementsPostClaimComplete");
}

#undef LOCTEXT_NAMESPACE
