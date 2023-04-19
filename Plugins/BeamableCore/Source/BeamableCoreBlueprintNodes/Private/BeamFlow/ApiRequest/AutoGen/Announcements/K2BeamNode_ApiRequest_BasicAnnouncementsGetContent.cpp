

#include "BeamableCoreBlueprintNodes/Public/BeamFlow/ApiRequest/AutoGen/Announcements/K2BeamNode_ApiRequest_BasicAnnouncementsGetContent.h"

#include "BeamK2.h"

#include "BeamableCore/Public/AutoGen/SubSystems/BeamAnnouncementsApi.h"
#include "BeamableCore/Public/AutoGen/SubSystems/Announcements/BasicAnnouncementsGetContentRequest.h"
#include "BeamableCore/Public/AutoGen/AnnouncementContentResponse.h"

#define LOCTEXT_NAMESPACE "K2BeamNode_ApiRequest_BasicAnnouncementsGetContent"

using namespace BeamK2;

FName UK2BeamNode_ApiRequest_BasicAnnouncementsGetContent::GetSelfFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamAnnouncementsApi, GetSelf);
}

FName UK2BeamNode_ApiRequest_BasicAnnouncementsGetContent::GetRequestFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamAnnouncementsApi, GetContent);
}

FName UK2BeamNode_ApiRequest_BasicAnnouncementsGetContent::GetMakeFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBasicAnnouncementsGetContentRequest, Make);
}

FString UK2BeamNode_ApiRequest_BasicAnnouncementsGetContent::GetServiceName() const
{
	return TEXT("Announcements");
}

FString UK2BeamNode_ApiRequest_BasicAnnouncementsGetContent::GetEndpointName() const
{
	return TEXT("GetContent");
}

UClass* UK2BeamNode_ApiRequest_BasicAnnouncementsGetContent::GetApiClass() const
{
	return UBeamAnnouncementsApi::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_BasicAnnouncementsGetContent::GetRequestClass() const
{
	return UBasicAnnouncementsGetContentRequest::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_BasicAnnouncementsGetContent::GetResponseClass() const
{
	return UAnnouncementContentResponse::StaticClass();
}

FString UK2BeamNode_ApiRequest_BasicAnnouncementsGetContent::GetRequestSuccessDelegateName() const
{
	return TEXT("OnBasicAnnouncementsGetContentSuccess");
}

FString UK2BeamNode_ApiRequest_BasicAnnouncementsGetContent::GetRequestErrorDelegateName() const
{
	return TEXT("OnBasicAnnouncementsGetContentError");
}

FString UK2BeamNode_ApiRequest_BasicAnnouncementsGetContent::GetRequestCompleteDelegateName() const
{
	return TEXT("OnBasicAnnouncementsGetContentComplete");
}

#undef LOCTEXT_NAMESPACE
