

#include "BeamableCoreBlueprintNodes/Public/BeamFlow/ApiRequest/AutoGen/Events/K2BeamNode_ApiRequest_GetCalendar.h"

#include "BeamK2.h"

#include "BeamableCore/Public/AutoGen/SubSystems/BeamEventsApi.h"
#include "BeamableCore/Public/AutoGen/SubSystems/Events/GetCalendarRequest.h"
#include "BeamableCore/Public/AutoGen/EventsInDateRangeResponse.h"

#define LOCTEXT_NAMESPACE "K2BeamNode_ApiRequest_GetCalendar"

using namespace BeamK2;

FName UK2BeamNode_ApiRequest_GetCalendar::GetSelfFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamEventsApi, GetSelf);
}

FName UK2BeamNode_ApiRequest_GetCalendar::GetRequestFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamEventsApi, GetCalendar);
}

FName UK2BeamNode_ApiRequest_GetCalendar::GetMakeFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UGetCalendarRequest, Make);
}

FString UK2BeamNode_ApiRequest_GetCalendar::GetServiceName() const
{
	return TEXT("Events");
}

FString UK2BeamNode_ApiRequest_GetCalendar::GetEndpointName() const
{
	return TEXT("GetCalendar");
}

UClass* UK2BeamNode_ApiRequest_GetCalendar::GetApiClass() const
{
	return UBeamEventsApi::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_GetCalendar::GetRequestClass() const
{
	return UGetCalendarRequest::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_GetCalendar::GetResponseClass() const
{
	return UEventsInDateRangeResponse::StaticClass();
}

FString UK2BeamNode_ApiRequest_GetCalendar::GetRequestSuccessDelegateName() const
{
	return TEXT("OnGetCalendarSuccess");
}

FString UK2BeamNode_ApiRequest_GetCalendar::GetRequestErrorDelegateName() const
{
	return TEXT("OnGetCalendarError");
}

FString UK2BeamNode_ApiRequest_GetCalendar::GetRequestCompleteDelegateName() const
{
	return TEXT("OnGetCalendarComplete");
}

#undef LOCTEXT_NAMESPACE
