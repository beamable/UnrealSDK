

#include "BeamableCoreBlueprintNodes/Public/BeamFlow/ApiRequest/AutoGen/Calendars/K2BeamNode_ApiRequest_ObjectCalendarsPostClaimByObjectId.h"

#include "BeamK2.h"

#include "BeamableCore/Public/AutoGen/SubSystems/BeamCalendarsApi.h"
#include "BeamableCore/Public/AutoGen/SubSystems/Calendars/ObjectCalendarsPostClaimByObjectIdRequest.h"
#include "BeamableCore/Public/AutoGen/CommonResponse.h"

#define LOCTEXT_NAMESPACE "K2BeamNode_ApiRequest_ObjectCalendarsPostClaimByObjectId"

using namespace BeamK2;

FName UK2BeamNode_ApiRequest_ObjectCalendarsPostClaimByObjectId::GetSelfFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamCalendarsApi, GetSelf);
}

FName UK2BeamNode_ApiRequest_ObjectCalendarsPostClaimByObjectId::GetRequestFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamCalendarsApi, PostClaim);
}

FName UK2BeamNode_ApiRequest_ObjectCalendarsPostClaimByObjectId::GetMakeFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UObjectCalendarsPostClaimByObjectIdRequest, Make);
}

FString UK2BeamNode_ApiRequest_ObjectCalendarsPostClaimByObjectId::GetServiceName() const
{
	return TEXT("Calendars");
}

FString UK2BeamNode_ApiRequest_ObjectCalendarsPostClaimByObjectId::GetEndpointName() const
{
	return TEXT("PostClaim");
}

UClass* UK2BeamNode_ApiRequest_ObjectCalendarsPostClaimByObjectId::GetApiClass() const
{
	return UBeamCalendarsApi::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_ObjectCalendarsPostClaimByObjectId::GetRequestClass() const
{
	return UObjectCalendarsPostClaimByObjectIdRequest::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_ObjectCalendarsPostClaimByObjectId::GetResponseClass() const
{
	return UCommonResponse::StaticClass();
}

FString UK2BeamNode_ApiRequest_ObjectCalendarsPostClaimByObjectId::GetRequestSuccessDelegateName() const
{
	return TEXT("OnObjectCalendarsPostClaimByObjectIdSuccess");
}

FString UK2BeamNode_ApiRequest_ObjectCalendarsPostClaimByObjectId::GetRequestErrorDelegateName() const
{
	return TEXT("OnObjectCalendarsPostClaimByObjectIdError");
}

FString UK2BeamNode_ApiRequest_ObjectCalendarsPostClaimByObjectId::GetRequestCompleteDelegateName() const
{
	return TEXT("OnObjectCalendarsPostClaimByObjectIdComplete");
}

#undef LOCTEXT_NAMESPACE
