

#include "BeamableCoreBlueprintNodes/Public/BeamFlow/ApiRequest/AutoGen/Auth/K2BeamNode_ApiRequest_DeleteTokens.h"

#include "BeamK2.h"

#include "BeamableCore/Public/AutoGen/SubSystems/BeamAuthApi.h"
#include "BeamableCore/Public/AutoGen/SubSystems/Auth/DeleteTokensRequest.h"
#include "BeamableCore/Public/AutoGen/AuthV2EmptyMessage.h"

#define LOCTEXT_NAMESPACE "K2BeamNode_ApiRequest_DeleteTokens"

using namespace BeamK2;

FName UK2BeamNode_ApiRequest_DeleteTokens::GetSelfFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamAuthApi, GetSelf);
}

FName UK2BeamNode_ApiRequest_DeleteTokens::GetRequestFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamAuthApi, DeleteTokens);
}

FName UK2BeamNode_ApiRequest_DeleteTokens::GetMakeFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UDeleteTokensRequest, Make);
}

FString UK2BeamNode_ApiRequest_DeleteTokens::GetServiceName() const
{
	return TEXT("Auth");
}

FString UK2BeamNode_ApiRequest_DeleteTokens::GetEndpointName() const
{
	return TEXT("DeleteTokens");
}

UClass* UK2BeamNode_ApiRequest_DeleteTokens::GetApiClass() const
{
	return UBeamAuthApi::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_DeleteTokens::GetRequestClass() const
{
	return UDeleteTokensRequest::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_DeleteTokens::GetResponseClass() const
{
	return UAuthV2EmptyMessage::StaticClass();
}

FString UK2BeamNode_ApiRequest_DeleteTokens::GetRequestSuccessDelegateName() const
{
	return TEXT("OnDeleteTokensSuccess");
}

FString UK2BeamNode_ApiRequest_DeleteTokens::GetRequestErrorDelegateName() const
{
	return TEXT("OnDeleteTokensError");
}

FString UK2BeamNode_ApiRequest_DeleteTokens::GetRequestCompleteDelegateName() const
{
	return TEXT("OnDeleteTokensComplete");
}

#undef LOCTEXT_NAMESPACE
