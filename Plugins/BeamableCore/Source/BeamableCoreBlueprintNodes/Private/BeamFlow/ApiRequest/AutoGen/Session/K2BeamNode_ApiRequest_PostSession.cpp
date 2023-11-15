

#include "BeamableCoreBlueprintNodes/Public/BeamFlow/ApiRequest/AutoGen/Session/K2BeamNode_ApiRequest_PostSession.h"

#include "BeamK2.h"

#include "BeamableCore/Public/AutoGen/SubSystems/BeamSessionApi.h"
#include "BeamableCore/Public/AutoGen/SubSystems/Session/PostSessionRequest.h"
#include "BeamableCore/Public/AutoGen/StartSessionResponse.h"

#define LOCTEXT_NAMESPACE "K2BeamNode_ApiRequest_PostSession"

using namespace BeamK2;

FName UK2BeamNode_ApiRequest_PostSession::GetSelfFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamSessionApi, GetSelf);
}

FName UK2BeamNode_ApiRequest_PostSession::GetRequestFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamSessionApi, PostSession);
}

FName UK2BeamNode_ApiRequest_PostSession::GetMakeFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UPostSessionRequest, Make);
}

FString UK2BeamNode_ApiRequest_PostSession::GetServiceName() const
{
	return TEXT("Session");
}

FString UK2BeamNode_ApiRequest_PostSession::GetEndpointName() const
{
	return TEXT("PostSession");
}

UClass* UK2BeamNode_ApiRequest_PostSession::GetApiClass() const
{
	return UBeamSessionApi::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_PostSession::GetRequestClass() const
{
	return UPostSessionRequest::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_PostSession::GetResponseClass() const
{
	return UStartSessionResponse::StaticClass();
}

FString UK2BeamNode_ApiRequest_PostSession::GetRequestSuccessDelegateName() const
{
	return TEXT("OnPostSessionSuccess");
}

FString UK2BeamNode_ApiRequest_PostSession::GetRequestErrorDelegateName() const
{
	return TEXT("OnPostSessionError");
}

FString UK2BeamNode_ApiRequest_PostSession::GetRequestCompleteDelegateName() const
{
	return TEXT("OnPostSessionComplete");
}

#undef LOCTEXT_NAMESPACE
