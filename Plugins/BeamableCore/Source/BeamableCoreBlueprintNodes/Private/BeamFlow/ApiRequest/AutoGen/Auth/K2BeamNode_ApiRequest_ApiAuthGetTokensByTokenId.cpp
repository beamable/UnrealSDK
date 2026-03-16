

#include "BeamableCoreBlueprintNodes/Public/BeamFlow/ApiRequest/AutoGen/Auth/K2BeamNode_ApiRequest_ApiAuthGetTokensByTokenId.h"

#include "BeamK2.h"

#include "BeamableCore/Public/AutoGen/SubSystems/BeamAuthApi.h"
#include "BeamableCore/Public/AutoGen/SubSystems/Auth/ApiAuthGetTokensByTokenIdRequest.h"
#include "BeamableCore/Public/AutoGen/AuthV2RefreshToken.h"

#define LOCTEXT_NAMESPACE "K2BeamNode_ApiRequest_ApiAuthGetTokensByTokenId"

using namespace BeamK2;

FName UK2BeamNode_ApiRequest_ApiAuthGetTokensByTokenId::GetSelfFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamAuthApi, GetSelf);
}

FName UK2BeamNode_ApiRequest_ApiAuthGetTokensByTokenId::GetRequestFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamAuthApi, ApiAuthGetTokensByTokenId);
}

FName UK2BeamNode_ApiRequest_ApiAuthGetTokensByTokenId::GetMakeFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UApiAuthGetTokensByTokenIdRequest, Make);
}

FString UK2BeamNode_ApiRequest_ApiAuthGetTokensByTokenId::GetServiceName() const
{
	return TEXT("Auth");
}

FString UK2BeamNode_ApiRequest_ApiAuthGetTokensByTokenId::GetEndpointName() const
{
	return TEXT("ApiAuthGetTokensByTokenId");
}

UClass* UK2BeamNode_ApiRequest_ApiAuthGetTokensByTokenId::GetApiClass() const
{
	return UBeamAuthApi::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_ApiAuthGetTokensByTokenId::GetRequestClass() const
{
	return UApiAuthGetTokensByTokenIdRequest::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_ApiAuthGetTokensByTokenId::GetResponseClass() const
{
	return UAuthV2RefreshToken::StaticClass();
}

FString UK2BeamNode_ApiRequest_ApiAuthGetTokensByTokenId::GetRequestSuccessDelegateName() const
{
	return TEXT("OnApiAuthGetTokensByTokenIdSuccess");
}

FString UK2BeamNode_ApiRequest_ApiAuthGetTokensByTokenId::GetRequestErrorDelegateName() const
{
	return TEXT("OnApiAuthGetTokensByTokenIdError");
}

FString UK2BeamNode_ApiRequest_ApiAuthGetTokensByTokenId::GetRequestCompleteDelegateName() const
{
	return TEXT("OnApiAuthGetTokensByTokenIdComplete");
}

#undef LOCTEXT_NAMESPACE
