

#include "BeamableCoreBlueprintNodes/Public/BeamFlow/ApiRequest/AutoGen/Events/K2BeamNode_ApiRequest_BasicEventsGetContent.h"

#include "BeamK2.h"

#include "BeamableCore/Public/AutoGen/SubSystems/BeamEventsApi.h"
#include "BeamableCore/Public/AutoGen/SubSystems/Events/BasicEventsGetContentRequest.h"
#include "BeamableCore/Public/AutoGen/EventContentResponse.h"

#define LOCTEXT_NAMESPACE "K2BeamNode_ApiRequest_BasicEventsGetContent"

using namespace BeamK2;

FName UK2BeamNode_ApiRequest_BasicEventsGetContent::GetSelfFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamEventsApi, GetSelf);
}

FName UK2BeamNode_ApiRequest_BasicEventsGetContent::GetRequestFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamEventsApi, GetContent);
}

FName UK2BeamNode_ApiRequest_BasicEventsGetContent::GetMakeFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBasicEventsGetContentRequest, Make);
}

FString UK2BeamNode_ApiRequest_BasicEventsGetContent::GetServiceName() const
{
	return TEXT("Events");
}

FString UK2BeamNode_ApiRequest_BasicEventsGetContent::GetEndpointName() const
{
	return TEXT("GetContent");
}

UClass* UK2BeamNode_ApiRequest_BasicEventsGetContent::GetApiClass() const
{
	return UBeamEventsApi::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_BasicEventsGetContent::GetRequestClass() const
{
	return UBasicEventsGetContentRequest::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_BasicEventsGetContent::GetResponseClass() const
{
	return UEventContentResponse::StaticClass();
}

FString UK2BeamNode_ApiRequest_BasicEventsGetContent::GetRequestSuccessDelegateName() const
{
	return TEXT("OnBasicEventsGetContentSuccess");
}

FString UK2BeamNode_ApiRequest_BasicEventsGetContent::GetRequestErrorDelegateName() const
{
	return TEXT("OnBasicEventsGetContentError");
}

FString UK2BeamNode_ApiRequest_BasicEventsGetContent::GetRequestCompleteDelegateName() const
{
	return TEXT("OnBasicEventsGetContentComplete");
}

#undef LOCTEXT_NAMESPACE
