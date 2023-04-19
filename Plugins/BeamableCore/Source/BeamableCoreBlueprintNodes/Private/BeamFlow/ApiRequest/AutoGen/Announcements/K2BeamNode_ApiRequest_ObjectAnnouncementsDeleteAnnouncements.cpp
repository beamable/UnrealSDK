

#include "BeamableCoreBlueprintNodes/Public/BeamFlow/ApiRequest/AutoGen/Announcements/K2BeamNode_ApiRequest_ObjectAnnouncementsDeleteAnnouncements.h"

#include "BeamK2.h"

#include "BeamableCore/Public/AutoGen/SubSystems/BeamAnnouncementsApi.h"
#include "BeamableCore/Public/AutoGen/SubSystems/Announcements/ObjectAnnouncementsDeleteAnnouncementsRequest.h"
#include "BeamableCore/Public/AutoGen/CommonResponse.h"

#define LOCTEXT_NAMESPACE "K2BeamNode_ApiRequest_ObjectAnnouncementsDeleteAnnouncements"

using namespace BeamK2;

FName UK2BeamNode_ApiRequest_ObjectAnnouncementsDeleteAnnouncements::GetSelfFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamAnnouncementsApi, GetSelf);
}

FName UK2BeamNode_ApiRequest_ObjectAnnouncementsDeleteAnnouncements::GetRequestFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamAnnouncementsApi, ObjectAnnouncementsDeleteAnnouncements);
}

FName UK2BeamNode_ApiRequest_ObjectAnnouncementsDeleteAnnouncements::GetMakeFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UObjectAnnouncementsDeleteAnnouncementsRequest, Make);
}

FString UK2BeamNode_ApiRequest_ObjectAnnouncementsDeleteAnnouncements::GetServiceName() const
{
	return TEXT("Announcements");
}

FString UK2BeamNode_ApiRequest_ObjectAnnouncementsDeleteAnnouncements::GetEndpointName() const
{
	return TEXT("ObjectAnnouncementsDeleteAnnouncements");
}

UClass* UK2BeamNode_ApiRequest_ObjectAnnouncementsDeleteAnnouncements::GetApiClass() const
{
	return UBeamAnnouncementsApi::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_ObjectAnnouncementsDeleteAnnouncements::GetRequestClass() const
{
	return UObjectAnnouncementsDeleteAnnouncementsRequest::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_ObjectAnnouncementsDeleteAnnouncements::GetResponseClass() const
{
	return UCommonResponse::StaticClass();
}

FString UK2BeamNode_ApiRequest_ObjectAnnouncementsDeleteAnnouncements::GetRequestSuccessDelegateName() const
{
	return TEXT("OnObjectAnnouncementsDeleteAnnouncementsSuccess");
}

FString UK2BeamNode_ApiRequest_ObjectAnnouncementsDeleteAnnouncements::GetRequestErrorDelegateName() const
{
	return TEXT("OnObjectAnnouncementsDeleteAnnouncementsError");
}

FString UK2BeamNode_ApiRequest_ObjectAnnouncementsDeleteAnnouncements::GetRequestCompleteDelegateName() const
{
	return TEXT("OnObjectAnnouncementsDeleteAnnouncementsComplete");
}

#undef LOCTEXT_NAMESPACE
