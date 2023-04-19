

#include "BeamableCoreBlueprintNodes/Public/BeamFlow/ApiRequest/AutoGen/Events/K2BeamNode_ApiRequest_PutEndPhase.h"

#include "BeamK2.h"

#include "BeamableCore/Public/AutoGen/SubSystems/BeamEventsApi.h"
#include "BeamableCore/Public/AutoGen/SubSystems/Events/PutEndPhaseRequest.h"
#include "BeamableCore/Public/AutoGen/CommonResponse.h"

#define LOCTEXT_NAMESPACE "K2BeamNode_ApiRequest_PutEndPhase"

using namespace BeamK2;

FName UK2BeamNode_ApiRequest_PutEndPhase::GetSelfFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamEventsApi, GetSelf);
}

FName UK2BeamNode_ApiRequest_PutEndPhase::GetRequestFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamEventsApi, PutEndPhase);
}

FName UK2BeamNode_ApiRequest_PutEndPhase::GetMakeFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UPutEndPhaseRequest, Make);
}

FString UK2BeamNode_ApiRequest_PutEndPhase::GetServiceName() const
{
	return TEXT("Events");
}

FString UK2BeamNode_ApiRequest_PutEndPhase::GetEndpointName() const
{
	return TEXT("PutEndPhase");
}

UClass* UK2BeamNode_ApiRequest_PutEndPhase::GetApiClass() const
{
	return UBeamEventsApi::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_PutEndPhase::GetRequestClass() const
{
	return UPutEndPhaseRequest::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_PutEndPhase::GetResponseClass() const
{
	return UCommonResponse::StaticClass();
}

FString UK2BeamNode_ApiRequest_PutEndPhase::GetRequestSuccessDelegateName() const
{
	return TEXT("OnPutEndPhaseSuccess");
}

FString UK2BeamNode_ApiRequest_PutEndPhase::GetRequestErrorDelegateName() const
{
	return TEXT("OnPutEndPhaseError");
}

FString UK2BeamNode_ApiRequest_PutEndPhase::GetRequestCompleteDelegateName() const
{
	return TEXT("OnPutEndPhaseComplete");
}

#undef LOCTEXT_NAMESPACE
