

#include "BeamableCoreBlueprintNodes/Public/BeamFlow/ApiRequest/AutoGen/Calendars/K2BeamNode_ApiRequest_GetCalendars.h"

#include "BeamK2.h"

#include "BeamableCore/Public/AutoGen/SubSystems/BeamCalendarsApi.h"
#include "BeamableCore/Public/AutoGen/SubSystems/Calendars/GetCalendarsRequest.h"
#include "BeamableCore/Public/AutoGen/CalendarQueryResponse.h"

#define LOCTEXT_NAMESPACE "K2BeamNode_ApiRequest_GetCalendars"

using namespace BeamK2;

FName UK2BeamNode_ApiRequest_GetCalendars::GetSelfFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamCalendarsApi, GetSelf);
}

FName UK2BeamNode_ApiRequest_GetCalendars::GetRequestFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamCalendarsApi, GetCalendars);
}

FName UK2BeamNode_ApiRequest_GetCalendars::GetMakeFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UGetCalendarsRequest, Make);
}

FString UK2BeamNode_ApiRequest_GetCalendars::GetServiceName() const
{
	return TEXT("Calendars");
}

FString UK2BeamNode_ApiRequest_GetCalendars::GetEndpointName() const
{
	return TEXT("GetCalendars");
}

UClass* UK2BeamNode_ApiRequest_GetCalendars::GetApiClass() const
{
	return UBeamCalendarsApi::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_GetCalendars::GetRequestClass() const
{
	return UGetCalendarsRequest::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_GetCalendars::GetResponseClass() const
{
	return UCalendarQueryResponse::StaticClass();
}

FString UK2BeamNode_ApiRequest_GetCalendars::GetRequestSuccessDelegateName() const
{
	return TEXT("OnGetCalendarsSuccess");
}

FString UK2BeamNode_ApiRequest_GetCalendars::GetRequestErrorDelegateName() const
{
	return TEXT("OnGetCalendarsError");
}

FString UK2BeamNode_ApiRequest_GetCalendars::GetRequestCompleteDelegateName() const
{
	return TEXT("OnGetCalendarsComplete");
}

#undef LOCTEXT_NAMESPACE
