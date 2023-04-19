

#include "BeamableCoreBlueprintNodes/Public/BeamFlow/ApiRequest/AutoGen/Announcements/K2BeamNode_ApiRequest_BasicAnnouncementsGetList.h"

#include "BeamK2.h"

#include "BeamableCore/Public/AutoGen/SubSystems/BeamAnnouncementsApi.h"
#include "BeamableCore/Public/AutoGen/SubSystems/Announcements/BasicAnnouncementsGetListRequest.h"
#include "BeamableCore/Public/AutoGen/AnnouncementContentResponse.h"

#define LOCTEXT_NAMESPACE "K2BeamNode_ApiRequest_BasicAnnouncementsGetList"

using namespace BeamK2;

FName UK2BeamNode_ApiRequest_BasicAnnouncementsGetList::GetSelfFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamAnnouncementsApi, GetSelf);
}

FName UK2BeamNode_ApiRequest_BasicAnnouncementsGetList::GetRequestFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamAnnouncementsApi, GetList);
}

FName UK2BeamNode_ApiRequest_BasicAnnouncementsGetList::GetMakeFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBasicAnnouncementsGetListRequest, Make);
}

FString UK2BeamNode_ApiRequest_BasicAnnouncementsGetList::GetServiceName() const
{
	return TEXT("Announcements");
}

FString UK2BeamNode_ApiRequest_BasicAnnouncementsGetList::GetEndpointName() const
{
	return TEXT("GetList");
}

UClass* UK2BeamNode_ApiRequest_BasicAnnouncementsGetList::GetApiClass() const
{
	return UBeamAnnouncementsApi::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_BasicAnnouncementsGetList::GetRequestClass() const
{
	return UBasicAnnouncementsGetListRequest::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_BasicAnnouncementsGetList::GetResponseClass() const
{
	return UAnnouncementContentResponse::StaticClass();
}

FString UK2BeamNode_ApiRequest_BasicAnnouncementsGetList::GetRequestSuccessDelegateName() const
{
	return TEXT("OnBasicAnnouncementsGetListSuccess");
}

FString UK2BeamNode_ApiRequest_BasicAnnouncementsGetList::GetRequestErrorDelegateName() const
{
	return TEXT("OnBasicAnnouncementsGetListError");
}

FString UK2BeamNode_ApiRequest_BasicAnnouncementsGetList::GetRequestCompleteDelegateName() const
{
	return TEXT("OnBasicAnnouncementsGetListComplete");
}

#undef LOCTEXT_NAMESPACE
