

#include "BeamableCoreBlueprintNodes/Public/BeamFlow/ApiRequest/AutoGen/Announcements/K2BeamNode_ApiRequest_BasicAnnouncementsGetSearch.h"

#include "BeamK2.h"

#include "BeamableCore/Public/AutoGen/SubSystems/BeamAnnouncementsApi.h"
#include "BeamableCore/Public/AutoGen/SubSystems/Announcements/BasicAnnouncementsGetSearchRequest.h"
#include "BeamableCore/Public/AutoGen/AnnouncementContentResponse.h"

#define LOCTEXT_NAMESPACE "K2BeamNode_ApiRequest_BasicAnnouncementsGetSearch"

using namespace BeamK2;

FName UK2BeamNode_ApiRequest_BasicAnnouncementsGetSearch::GetSelfFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamAnnouncementsApi, GetSelf);
}

FName UK2BeamNode_ApiRequest_BasicAnnouncementsGetSearch::GetRequestFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamAnnouncementsApi, GetSearch);
}

FName UK2BeamNode_ApiRequest_BasicAnnouncementsGetSearch::GetMakeFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBasicAnnouncementsGetSearchRequest, Make);
}

FString UK2BeamNode_ApiRequest_BasicAnnouncementsGetSearch::GetServiceName() const
{
	return TEXT("Announcements");
}

FString UK2BeamNode_ApiRequest_BasicAnnouncementsGetSearch::GetEndpointName() const
{
	return TEXT("GetSearch");
}

UClass* UK2BeamNode_ApiRequest_BasicAnnouncementsGetSearch::GetApiClass() const
{
	return UBeamAnnouncementsApi::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_BasicAnnouncementsGetSearch::GetRequestClass() const
{
	return UBasicAnnouncementsGetSearchRequest::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_BasicAnnouncementsGetSearch::GetResponseClass() const
{
	return UAnnouncementContentResponse::StaticClass();
}

FString UK2BeamNode_ApiRequest_BasicAnnouncementsGetSearch::GetRequestSuccessDelegateName() const
{
	return TEXT("OnBasicAnnouncementsGetSearchSuccess");
}

FString UK2BeamNode_ApiRequest_BasicAnnouncementsGetSearch::GetRequestErrorDelegateName() const
{
	return TEXT("OnBasicAnnouncementsGetSearchError");
}

FString UK2BeamNode_ApiRequest_BasicAnnouncementsGetSearch::GetRequestCompleteDelegateName() const
{
	return TEXT("OnBasicAnnouncementsGetSearchComplete");
}

#undef LOCTEXT_NAMESPACE
