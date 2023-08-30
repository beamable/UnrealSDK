

#include "BeamableCoreBlueprintNodes/Public/BeamFlow/ApiRequest/AutoGen/Auth/K2BeamNode_ApiRequest_ApiAuthPostServer.h"

#include "BeamK2.h"

#include "BeamableCore/Public/AutoGen/SubSystems/BeamAuthApi.h"
#include "BeamableCore/Public/AutoGen/SubSystems/Auth/ApiAuthPostServerRequest.h"
#include "BeamableCore/Public/AutoGen/ServerTokenResponse.h"

#define LOCTEXT_NAMESPACE "K2BeamNode_ApiRequest_ApiAuthPostServer"

using namespace BeamK2;

FName UK2BeamNode_ApiRequest_ApiAuthPostServer::GetSelfFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamAuthApi, GetSelf);
}

FName UK2BeamNode_ApiRequest_ApiAuthPostServer::GetRequestFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamAuthApi, PostServer);
}

FName UK2BeamNode_ApiRequest_ApiAuthPostServer::GetMakeFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UApiAuthPostServerRequest, Make);
}

FString UK2BeamNode_ApiRequest_ApiAuthPostServer::GetServiceName() const
{
	return TEXT("Auth");
}

FString UK2BeamNode_ApiRequest_ApiAuthPostServer::GetEndpointName() const
{
	return TEXT("PostServer");
}

UClass* UK2BeamNode_ApiRequest_ApiAuthPostServer::GetApiClass() const
{
	return UBeamAuthApi::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_ApiAuthPostServer::GetRequestClass() const
{
	return UApiAuthPostServerRequest::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_ApiAuthPostServer::GetResponseClass() const
{
	return UServerTokenResponse::StaticClass();
}

FString UK2BeamNode_ApiRequest_ApiAuthPostServer::GetRequestSuccessDelegateName() const
{
	return TEXT("OnApiAuthPostServerSuccess");
}

FString UK2BeamNode_ApiRequest_ApiAuthPostServer::GetRequestErrorDelegateName() const
{
	return TEXT("OnApiAuthPostServerError");
}

FString UK2BeamNode_ApiRequest_ApiAuthPostServer::GetRequestCompleteDelegateName() const
{
	return TEXT("OnApiAuthPostServerComplete");
}

#undef LOCTEXT_NAMESPACE
