

#include "BeamableCoreBlueprintNodes/Public/BeamFlow/ApiRequest/AutoGen/Announcements/K2BeamNode_ApiRequest_GetAnnouncements.h"

#include "BeamK2.h"

#include "BeamableCore/Public/AutoGen/SubSystems/BeamAnnouncementsApi.h"
#include "BeamableCore/Public/AutoGen/SubSystems/Announcements/GetAnnouncementsRequest.h"
#include "BeamableCore/Public/AutoGen/AnnouncementQueryResponse.h"

#define LOCTEXT_NAMESPACE "K2BeamNode_ApiRequest_GetAnnouncements"

using namespace BeamK2;

FName UK2BeamNode_ApiRequest_GetAnnouncements::GetSelfFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamAnnouncementsApi, GetSelf);
}

FName UK2BeamNode_ApiRequest_GetAnnouncements::GetRequestFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamAnnouncementsApi, GetAnnouncements);
}

FName UK2BeamNode_ApiRequest_GetAnnouncements::GetMakeFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UGetAnnouncementsRequest, Make);
}

FString UK2BeamNode_ApiRequest_GetAnnouncements::GetServiceName() const
{
	return TEXT("Announcements");
}

FString UK2BeamNode_ApiRequest_GetAnnouncements::GetEndpointName() const
{
	return TEXT("GetAnnouncements");
}

UClass* UK2BeamNode_ApiRequest_GetAnnouncements::GetApiClass() const
{
	return UBeamAnnouncementsApi::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_GetAnnouncements::GetRequestClass() const
{
	return UGetAnnouncementsRequest::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_GetAnnouncements::GetResponseClass() const
{
	return UAnnouncementQueryResponse::StaticClass();
}

FString UK2BeamNode_ApiRequest_GetAnnouncements::GetRequestSuccessDelegateName() const
{
	return TEXT("OnGetAnnouncementsSuccess");
}

FString UK2BeamNode_ApiRequest_GetAnnouncements::GetRequestErrorDelegateName() const
{
	return TEXT("OnGetAnnouncementsError");
}

FString UK2BeamNode_ApiRequest_GetAnnouncements::GetRequestCompleteDelegateName() const
{
	return TEXT("OnGetAnnouncementsComplete");
}

#undef LOCTEXT_NAMESPACE
