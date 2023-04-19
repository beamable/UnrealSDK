

#include "BeamableCoreBlueprintNodes/Public/BeamFlow/ApiRequest/AutoGen/Calendars/K2BeamNode_ApiRequest_ObjectCalendarsPostClaim.h"

#include "BeamK2.h"

#include "BeamableCore/Public/AutoGen/SubSystems/BeamCalendarsApi.h"
#include "BeamableCore/Public/AutoGen/SubSystems/Calendars/ObjectCalendarsPostClaimRequest.h"
#include "BeamableCore/Public/AutoGen/CommonResponse.h"

#define LOCTEXT_NAMESPACE "K2BeamNode_ApiRequest_ObjectCalendarsPostClaim"

using namespace BeamK2;

FName UK2BeamNode_ApiRequest_ObjectCalendarsPostClaim::GetSelfFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamCalendarsApi, GetSelf);
}

FName UK2BeamNode_ApiRequest_ObjectCalendarsPostClaim::GetRequestFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamCalendarsApi, PostClaim);
}

FName UK2BeamNode_ApiRequest_ObjectCalendarsPostClaim::GetMakeFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UObjectCalendarsPostClaimRequest, Make);
}

FString UK2BeamNode_ApiRequest_ObjectCalendarsPostClaim::GetServiceName() const
{
	return TEXT("Calendars");
}

FString UK2BeamNode_ApiRequest_ObjectCalendarsPostClaim::GetEndpointName() const
{
	return TEXT("PostClaim");
}

UClass* UK2BeamNode_ApiRequest_ObjectCalendarsPostClaim::GetApiClass() const
{
	return UBeamCalendarsApi::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_ObjectCalendarsPostClaim::GetRequestClass() const
{
	return UObjectCalendarsPostClaimRequest::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_ObjectCalendarsPostClaim::GetResponseClass() const
{
	return UCommonResponse::StaticClass();
}

FString UK2BeamNode_ApiRequest_ObjectCalendarsPostClaim::GetRequestSuccessDelegateName() const
{
	return TEXT("OnObjectCalendarsPostClaimSuccess");
}

FString UK2BeamNode_ApiRequest_ObjectCalendarsPostClaim::GetRequestErrorDelegateName() const
{
	return TEXT("OnObjectCalendarsPostClaimError");
}

FString UK2BeamNode_ApiRequest_ObjectCalendarsPostClaim::GetRequestCompleteDelegateName() const
{
	return TEXT("OnObjectCalendarsPostClaimComplete");
}

#undef LOCTEXT_NAMESPACE
