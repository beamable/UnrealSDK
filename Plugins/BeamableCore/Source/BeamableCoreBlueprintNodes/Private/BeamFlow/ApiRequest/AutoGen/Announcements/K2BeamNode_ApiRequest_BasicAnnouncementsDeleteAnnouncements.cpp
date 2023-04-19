

#include "BeamableCoreBlueprintNodes/Public/BeamFlow/ApiRequest/AutoGen/Announcements/K2BeamNode_ApiRequest_BasicAnnouncementsDeleteAnnouncements.h"

#include "BeamK2.h"

#include "BeamableCore/Public/AutoGen/SubSystems/BeamAnnouncementsApi.h"
#include "BeamableCore/Public/AutoGen/SubSystems/Announcements/BasicAnnouncementsDeleteAnnouncementsRequest.h"
#include "BeamableCore/Public/AutoGen/EmptyResponse.h"

#define LOCTEXT_NAMESPACE "K2BeamNode_ApiRequest_BasicAnnouncementsDeleteAnnouncements"

using namespace BeamK2;

FName UK2BeamNode_ApiRequest_BasicAnnouncementsDeleteAnnouncements::GetSelfFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamAnnouncementsApi, GetSelf);
}

FName UK2BeamNode_ApiRequest_BasicAnnouncementsDeleteAnnouncements::GetRequestFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamAnnouncementsApi, BasicAnnouncementsDeleteAnnouncements);
}

FName UK2BeamNode_ApiRequest_BasicAnnouncementsDeleteAnnouncements::GetMakeFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBasicAnnouncementsDeleteAnnouncementsRequest, Make);
}

FString UK2BeamNode_ApiRequest_BasicAnnouncementsDeleteAnnouncements::GetServiceName() const
{
	return TEXT("Announcements");
}

FString UK2BeamNode_ApiRequest_BasicAnnouncementsDeleteAnnouncements::GetEndpointName() const
{
	return TEXT("BasicAnnouncementsDeleteAnnouncements");
}

UClass* UK2BeamNode_ApiRequest_BasicAnnouncementsDeleteAnnouncements::GetApiClass() const
{
	return UBeamAnnouncementsApi::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_BasicAnnouncementsDeleteAnnouncements::GetRequestClass() const
{
	return UBasicAnnouncementsDeleteAnnouncementsRequest::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_BasicAnnouncementsDeleteAnnouncements::GetResponseClass() const
{
	return UEmptyResponse::StaticClass();
}

FString UK2BeamNode_ApiRequest_BasicAnnouncementsDeleteAnnouncements::GetRequestSuccessDelegateName() const
{
	return TEXT("OnBasicAnnouncementsDeleteAnnouncementsSuccess");
}

FString UK2BeamNode_ApiRequest_BasicAnnouncementsDeleteAnnouncements::GetRequestErrorDelegateName() const
{
	return TEXT("OnBasicAnnouncementsDeleteAnnouncementsError");
}

FString UK2BeamNode_ApiRequest_BasicAnnouncementsDeleteAnnouncements::GetRequestCompleteDelegateName() const
{
	return TEXT("OnBasicAnnouncementsDeleteAnnouncementsComplete");
}

#undef LOCTEXT_NAMESPACE
