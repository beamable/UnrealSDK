

#include "BeamableCoreBlueprintNodes/Public/BeamFlow/ApiRequest/AutoGen/Announcements/K2BeamNode_ApiRequest_PutRead.h"

#include "BeamK2.h"

#include "BeamableCore/Public/AutoGen/SubSystems/BeamAnnouncementsApi.h"
#include "BeamableCore/Public/AutoGen/SubSystems/Announcements/PutReadRequest.h"
#include "BeamableCore/Public/AutoGen/CommonResponse.h"

#define LOCTEXT_NAMESPACE "K2BeamNode_ApiRequest_PutRead"

using namespace BeamK2;

FName UK2BeamNode_ApiRequest_PutRead::GetSelfFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamAnnouncementsApi, GetSelf);
}

FName UK2BeamNode_ApiRequest_PutRead::GetRequestFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamAnnouncementsApi, PutRead);
}

FName UK2BeamNode_ApiRequest_PutRead::GetMakeFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UPutReadRequest, Make);
}

FString UK2BeamNode_ApiRequest_PutRead::GetServiceName() const
{
	return TEXT("Announcements");
}

FString UK2BeamNode_ApiRequest_PutRead::GetEndpointName() const
{
	return TEXT("PutRead");
}

UClass* UK2BeamNode_ApiRequest_PutRead::GetApiClass() const
{
	return UBeamAnnouncementsApi::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_PutRead::GetRequestClass() const
{
	return UPutReadRequest::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_PutRead::GetResponseClass() const
{
	return UCommonResponse::StaticClass();
}

FString UK2BeamNode_ApiRequest_PutRead::GetRequestSuccessDelegateName() const
{
	return TEXT("OnPutReadSuccess");
}

FString UK2BeamNode_ApiRequest_PutRead::GetRequestErrorDelegateName() const
{
	return TEXT("OnPutReadError");
}

FString UK2BeamNode_ApiRequest_PutRead::GetRequestCompleteDelegateName() const
{
	return TEXT("OnPutReadComplete");
}

#undef LOCTEXT_NAMESPACE
