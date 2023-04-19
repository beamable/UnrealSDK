

#include "BeamableCoreBlueprintNodes/Public/BeamFlow/ApiRequest/AutoGen/Announcements/K2BeamNode_ApiRequest_GetListTags.h"

#include "BeamK2.h"

#include "BeamableCore/Public/AutoGen/SubSystems/BeamAnnouncementsApi.h"
#include "BeamableCore/Public/AutoGen/SubSystems/Announcements/GetListTagsRequest.h"
#include "BeamableCore/Public/AutoGen/ListTagsResponse.h"

#define LOCTEXT_NAMESPACE "K2BeamNode_ApiRequest_GetListTags"

using namespace BeamK2;

FName UK2BeamNode_ApiRequest_GetListTags::GetSelfFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamAnnouncementsApi, GetSelf);
}

FName UK2BeamNode_ApiRequest_GetListTags::GetRequestFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamAnnouncementsApi, GetListTags);
}

FName UK2BeamNode_ApiRequest_GetListTags::GetMakeFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UGetListTagsRequest, Make);
}

FString UK2BeamNode_ApiRequest_GetListTags::GetServiceName() const
{
	return TEXT("Announcements");
}

FString UK2BeamNode_ApiRequest_GetListTags::GetEndpointName() const
{
	return TEXT("GetListTags");
}

UClass* UK2BeamNode_ApiRequest_GetListTags::GetApiClass() const
{
	return UBeamAnnouncementsApi::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_GetListTags::GetRequestClass() const
{
	return UGetListTagsRequest::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_GetListTags::GetResponseClass() const
{
	return UListTagsResponse::StaticClass();
}

FString UK2BeamNode_ApiRequest_GetListTags::GetRequestSuccessDelegateName() const
{
	return TEXT("OnGetListTagsSuccess");
}

FString UK2BeamNode_ApiRequest_GetListTags::GetRequestErrorDelegateName() const
{
	return TEXT("OnGetListTagsError");
}

FString UK2BeamNode_ApiRequest_GetListTags::GetRequestCompleteDelegateName() const
{
	return TEXT("OnGetListTagsComplete");
}

#undef LOCTEXT_NAMESPACE
