

#include "BeamableCoreBlueprintNodes/Public/BeamFlow/ApiRequest/AutoGen/Announcements/K2BeamNode_ApiRequest_PostAnnouncements.h"

#include "BeamK2.h"

#include "BeamableCore/Public/AutoGen/SubSystems/BeamAnnouncementsApi.h"
#include "BeamableCore/Public/AutoGen/SubSystems/Announcements/PostAnnouncementsRequest.h"
#include "BeamableCore/Public/AutoGen/EmptyResponse.h"

#define LOCTEXT_NAMESPACE "K2BeamNode_ApiRequest_PostAnnouncements"

using namespace BeamK2;

FName UK2BeamNode_ApiRequest_PostAnnouncements::GetSelfFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamAnnouncementsApi, GetSelf);
}

FName UK2BeamNode_ApiRequest_PostAnnouncements::GetRequestFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamAnnouncementsApi, PostAnnouncements);
}

FName UK2BeamNode_ApiRequest_PostAnnouncements::GetMakeFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UPostAnnouncementsRequest, Make);
}

FString UK2BeamNode_ApiRequest_PostAnnouncements::GetServiceName() const
{
	return TEXT("Announcements");
}

FString UK2BeamNode_ApiRequest_PostAnnouncements::GetEndpointName() const
{
	return TEXT("PostAnnouncements");
}

UClass* UK2BeamNode_ApiRequest_PostAnnouncements::GetApiClass() const
{
	return UBeamAnnouncementsApi::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_PostAnnouncements::GetRequestClass() const
{
	return UPostAnnouncementsRequest::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_PostAnnouncements::GetResponseClass() const
{
	return UEmptyResponse::StaticClass();
}

FString UK2BeamNode_ApiRequest_PostAnnouncements::GetRequestSuccessDelegateName() const
{
	return TEXT("OnPostAnnouncementsSuccess");
}

FString UK2BeamNode_ApiRequest_PostAnnouncements::GetRequestErrorDelegateName() const
{
	return TEXT("OnPostAnnouncementsError");
}

FString UK2BeamNode_ApiRequest_PostAnnouncements::GetRequestCompleteDelegateName() const
{
	return TEXT("OnPostAnnouncementsComplete");
}

#undef LOCTEXT_NAMESPACE
