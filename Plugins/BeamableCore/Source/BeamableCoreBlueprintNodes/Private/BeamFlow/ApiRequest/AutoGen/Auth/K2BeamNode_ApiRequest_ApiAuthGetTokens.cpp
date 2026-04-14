

#include "BeamableCoreBlueprintNodes/Public/BeamFlow/ApiRequest/AutoGen/Auth/K2BeamNode_ApiRequest_ApiAuthGetTokens.h"

#include "BeamK2.h"

#include "BeamableCore/Public/AutoGen/SubSystems/BeamAuthApi.h"
#include "BeamableCore/Public/AutoGen/SubSystems/Auth/ApiAuthGetTokensRequest.h"
#include "BeamableCore/Public/AutoGen/AuthV2ListTokensResponse.h"

#define LOCTEXT_NAMESPACE "K2BeamNode_ApiRequest_ApiAuthGetTokens"

using namespace BeamK2;

FName UK2BeamNode_ApiRequest_ApiAuthGetTokens::GetSelfFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamAuthApi, GetSelf);
}

FName UK2BeamNode_ApiRequest_ApiAuthGetTokens::GetRequestFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamAuthApi, ApiAuthGetTokens);
}

FName UK2BeamNode_ApiRequest_ApiAuthGetTokens::GetMakeFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UApiAuthGetTokensRequest, Make);
}

FString UK2BeamNode_ApiRequest_ApiAuthGetTokens::GetServiceName() const
{
	return TEXT("Auth");
}

FString UK2BeamNode_ApiRequest_ApiAuthGetTokens::GetEndpointName() const
{
	return TEXT("ApiAuthGetTokens");
}

UClass* UK2BeamNode_ApiRequest_ApiAuthGetTokens::GetApiClass() const
{
	return UBeamAuthApi::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_ApiAuthGetTokens::GetRequestClass() const
{
	return UApiAuthGetTokensRequest::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_ApiAuthGetTokens::GetResponseClass() const
{
	return UAuthV2ListTokensResponse::StaticClass();
}

FString UK2BeamNode_ApiRequest_ApiAuthGetTokens::GetRequestSuccessDelegateName() const
{
	return TEXT("OnApiAuthGetTokensSuccess");
}

FString UK2BeamNode_ApiRequest_ApiAuthGetTokens::GetRequestErrorDelegateName() const
{
	return TEXT("OnApiAuthGetTokensError");
}

FString UK2BeamNode_ApiRequest_ApiAuthGetTokens::GetRequestCompleteDelegateName() const
{
	return TEXT("OnApiAuthGetTokensComplete");
}

#undef LOCTEXT_NAMESPACE
