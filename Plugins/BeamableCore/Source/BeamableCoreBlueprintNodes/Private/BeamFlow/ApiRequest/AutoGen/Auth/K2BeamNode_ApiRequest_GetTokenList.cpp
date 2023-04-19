

#include "BeamableCoreBlueprintNodes/Public/BeamFlow/ApiRequest/AutoGen/Auth/K2BeamNode_ApiRequest_GetTokenList.h"

#include "BeamK2.h"

#include "BeamableCore/Public/AutoGen/SubSystems/BeamAuthApi.h"
#include "BeamableCore/Public/AutoGen/SubSystems/Auth/GetTokenListRequest.h"
#include "BeamableCore/Public/AutoGen/ListTokenResponse.h"

#define LOCTEXT_NAMESPACE "K2BeamNode_ApiRequest_GetTokenList"

using namespace BeamK2;

FName UK2BeamNode_ApiRequest_GetTokenList::GetSelfFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamAuthApi, GetSelf);
}

FName UK2BeamNode_ApiRequest_GetTokenList::GetRequestFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamAuthApi, GetTokenList);
}

FName UK2BeamNode_ApiRequest_GetTokenList::GetMakeFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UGetTokenListRequest, Make);
}

FString UK2BeamNode_ApiRequest_GetTokenList::GetServiceName() const
{
	return TEXT("Auth");
}

FString UK2BeamNode_ApiRequest_GetTokenList::GetEndpointName() const
{
	return TEXT("GetTokenList");
}

UClass* UK2BeamNode_ApiRequest_GetTokenList::GetApiClass() const
{
	return UBeamAuthApi::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_GetTokenList::GetRequestClass() const
{
	return UGetTokenListRequest::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_GetTokenList::GetResponseClass() const
{
	return UListTokenResponse::StaticClass();
}

FString UK2BeamNode_ApiRequest_GetTokenList::GetRequestSuccessDelegateName() const
{
	return TEXT("OnGetTokenListSuccess");
}

FString UK2BeamNode_ApiRequest_GetTokenList::GetRequestErrorDelegateName() const
{
	return TEXT("OnGetTokenListError");
}

FString UK2BeamNode_ApiRequest_GetTokenList::GetRequestCompleteDelegateName() const
{
	return TEXT("OnGetTokenListComplete");
}

#undef LOCTEXT_NAMESPACE
