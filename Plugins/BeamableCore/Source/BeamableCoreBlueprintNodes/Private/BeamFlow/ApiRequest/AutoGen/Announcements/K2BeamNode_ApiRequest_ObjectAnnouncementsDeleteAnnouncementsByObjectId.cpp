

#include "BeamableCoreBlueprintNodes/Public/BeamFlow/ApiRequest/AutoGen/Announcements/K2BeamNode_ApiRequest_ObjectAnnouncementsDeleteAnnouncementsByObjectId.h"

#include "BeamK2.h"

#include "BeamableCore/Public/AutoGen/SubSystems/BeamAnnouncementsApi.h"
#include "BeamableCore/Public/AutoGen/SubSystems/Announcements/ObjectAnnouncementsDeleteAnnouncementsByObjectIdRequest.h"
#include "BeamableCore/Public/AutoGen/CommonResponse.h"

#define LOCTEXT_NAMESPACE "K2BeamNode_ApiRequest_ObjectAnnouncementsDeleteAnnouncementsByObjectId"

using namespace BeamK2;

FName UK2BeamNode_ApiRequest_ObjectAnnouncementsDeleteAnnouncementsByObjectId::GetSelfFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamAnnouncementsApi, GetSelf);
}

FName UK2BeamNode_ApiRequest_ObjectAnnouncementsDeleteAnnouncementsByObjectId::GetRequestFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamAnnouncementsApi, ObjectAnnouncementsDeleteAnnouncementsByObjectId);
}

FName UK2BeamNode_ApiRequest_ObjectAnnouncementsDeleteAnnouncementsByObjectId::GetMakeFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UObjectAnnouncementsDeleteAnnouncementsByObjectIdRequest, Make);
}

FString UK2BeamNode_ApiRequest_ObjectAnnouncementsDeleteAnnouncementsByObjectId::GetServiceName() const
{
	return TEXT("Announcements");
}

FString UK2BeamNode_ApiRequest_ObjectAnnouncementsDeleteAnnouncementsByObjectId::GetEndpointName() const
{
	return TEXT("ObjectAnnouncementsDeleteAnnouncementsByObjectId");
}

UClass* UK2BeamNode_ApiRequest_ObjectAnnouncementsDeleteAnnouncementsByObjectId::GetApiClass() const
{
	return UBeamAnnouncementsApi::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_ObjectAnnouncementsDeleteAnnouncementsByObjectId::GetRequestClass() const
{
	return UObjectAnnouncementsDeleteAnnouncementsByObjectIdRequest::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_ObjectAnnouncementsDeleteAnnouncementsByObjectId::GetResponseClass() const
{
	return UCommonResponse::StaticClass();
}

FString UK2BeamNode_ApiRequest_ObjectAnnouncementsDeleteAnnouncementsByObjectId::GetRequestSuccessDelegateName() const
{
	return TEXT("OnObjectAnnouncementsDeleteAnnouncementsByObjectIdSuccess");
}

FString UK2BeamNode_ApiRequest_ObjectAnnouncementsDeleteAnnouncementsByObjectId::GetRequestErrorDelegateName() const
{
	return TEXT("OnObjectAnnouncementsDeleteAnnouncementsByObjectIdError");
}

FString UK2BeamNode_ApiRequest_ObjectAnnouncementsDeleteAnnouncementsByObjectId::GetRequestCompleteDelegateName() const
{
	return TEXT("OnObjectAnnouncementsDeleteAnnouncementsByObjectIdComplete");
}

#undef LOCTEXT_NAMESPACE
