

#include "BeamableCoreBlueprintNodes/Public/BeamFlow/ApiRequest/AutoGen/Session/K2BeamNode_ApiRequest_PostSessions.h"

#include "BeamK2.h"

#include "BeamableCore/Public/AutoGen/SubSystems/BeamSessionApi.h"
#include "BeamableCore/Public/AutoGen/SubSystems/Session/PostSessionsRequest.h"
#include "BeamableCore/Public/AutoGen/ApiSessionsPostSessionResponse.h"

#define LOCTEXT_NAMESPACE "K2BeamNode_ApiRequest_PostSessions"

using namespace BeamK2;

FName UK2BeamNode_ApiRequest_PostSessions::GetSelfFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamSessionApi, GetSelf);
}

FName UK2BeamNode_ApiRequest_PostSessions::GetRequestFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamSessionApi, PostSessions);
}

FName UK2BeamNode_ApiRequest_PostSessions::GetMakeFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UPostSessionsRequest, Make);
}

FString UK2BeamNode_ApiRequest_PostSessions::GetServiceName() const
{
	return TEXT("Session");
}

FString UK2BeamNode_ApiRequest_PostSessions::GetEndpointName() const
{
	return TEXT("PostSessions");
}

UClass* UK2BeamNode_ApiRequest_PostSessions::GetApiClass() const
{
	return UBeamSessionApi::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_PostSessions::GetRequestClass() const
{
	return UPostSessionsRequest::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_PostSessions::GetResponseClass() const
{
	return UApiSessionsPostSessionResponse::StaticClass();
}

FString UK2BeamNode_ApiRequest_PostSessions::GetRequestSuccessDelegateName() const
{
	return TEXT("OnPostSessionsSuccess");
}

FString UK2BeamNode_ApiRequest_PostSessions::GetRequestErrorDelegateName() const
{
	return TEXT("OnPostSessionsError");
}

FString UK2BeamNode_ApiRequest_PostSessions::GetRequestCompleteDelegateName() const
{
	return TEXT("OnPostSessionsComplete");
}

#undef LOCTEXT_NAMESPACE
