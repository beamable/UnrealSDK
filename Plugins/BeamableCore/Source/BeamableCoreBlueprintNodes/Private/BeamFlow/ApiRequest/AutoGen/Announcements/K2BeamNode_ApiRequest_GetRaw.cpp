

#include "BeamableCoreBlueprintNodes/Public/BeamFlow/ApiRequest/AutoGen/Announcements/K2BeamNode_ApiRequest_GetRaw.h"

#include "BeamK2.h"

#include "BeamableCore/Public/AutoGen/SubSystems/BeamAnnouncementsApi.h"
#include "BeamableCore/Public/AutoGen/SubSystems/Announcements/GetRawRequest.h"
#include "BeamableCore/Public/AutoGen/AnnouncementRawResponse.h"

#define LOCTEXT_NAMESPACE "K2BeamNode_ApiRequest_GetRaw"

using namespace BeamK2;

FName UK2BeamNode_ApiRequest_GetRaw::GetSelfFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamAnnouncementsApi, GetSelf);
}

FName UK2BeamNode_ApiRequest_GetRaw::GetRequestFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamAnnouncementsApi, GetRaw);
}

FName UK2BeamNode_ApiRequest_GetRaw::GetMakeFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UGetRawRequest, Make);
}

FString UK2BeamNode_ApiRequest_GetRaw::GetServiceName() const
{
	return TEXT("Announcements");
}

FString UK2BeamNode_ApiRequest_GetRaw::GetEndpointName() const
{
	return TEXT("GetRaw");
}

UClass* UK2BeamNode_ApiRequest_GetRaw::GetApiClass() const
{
	return UBeamAnnouncementsApi::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_GetRaw::GetRequestClass() const
{
	return UGetRawRequest::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_GetRaw::GetResponseClass() const
{
	return UAnnouncementRawResponse::StaticClass();
}

FString UK2BeamNode_ApiRequest_GetRaw::GetRequestSuccessDelegateName() const
{
	return TEXT("OnGetRawSuccess");
}

FString UK2BeamNode_ApiRequest_GetRaw::GetRequestErrorDelegateName() const
{
	return TEXT("OnGetRawError");
}

FString UK2BeamNode_ApiRequest_GetRaw::GetRequestCompleteDelegateName() const
{
	return TEXT("OnGetRawComplete");
}

#undef LOCTEXT_NAMESPACE
