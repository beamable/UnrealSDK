

#include "BeamableCoreBlueprintNodes/Public/BeamFlow/ApiRequest/AutoGen/Events/K2BeamNode_ApiRequest_GetEvents.h"

#include "BeamK2.h"

#include "BeamableCore/Public/AutoGen/SubSystems/BeamEventsApi.h"
#include "BeamableCore/Public/AutoGen/SubSystems/Events/GetEventsRequest.h"
#include "BeamableCore/Public/AutoGen/EventObjectData.h"

#define LOCTEXT_NAMESPACE "K2BeamNode_ApiRequest_GetEvents"

using namespace BeamK2;

FName UK2BeamNode_ApiRequest_GetEvents::GetSelfFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamEventsApi, GetSelf);
}

FName UK2BeamNode_ApiRequest_GetEvents::GetRequestFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamEventsApi, GetEvents);
}

FName UK2BeamNode_ApiRequest_GetEvents::GetMakeFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UGetEventsRequest, Make);
}

FString UK2BeamNode_ApiRequest_GetEvents::GetServiceName() const
{
	return TEXT("Events");
}

FString UK2BeamNode_ApiRequest_GetEvents::GetEndpointName() const
{
	return TEXT("GetEvents");
}

UClass* UK2BeamNode_ApiRequest_GetEvents::GetApiClass() const
{
	return UBeamEventsApi::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_GetEvents::GetRequestClass() const
{
	return UGetEventsRequest::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_GetEvents::GetResponseClass() const
{
	return UEventObjectData::StaticClass();
}

FString UK2BeamNode_ApiRequest_GetEvents::GetRequestSuccessDelegateName() const
{
	return TEXT("OnGetEventsSuccess");
}

FString UK2BeamNode_ApiRequest_GetEvents::GetRequestErrorDelegateName() const
{
	return TEXT("OnGetEventsError");
}

FString UK2BeamNode_ApiRequest_GetEvents::GetRequestCompleteDelegateName() const
{
	return TEXT("OnGetEventsComplete");
}

#undef LOCTEXT_NAMESPACE
