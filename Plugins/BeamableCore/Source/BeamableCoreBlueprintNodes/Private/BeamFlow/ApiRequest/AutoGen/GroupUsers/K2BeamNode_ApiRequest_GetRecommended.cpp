

#include "BeamableCoreBlueprintNodes/Public/BeamFlow/ApiRequest/AutoGen/GroupUsers/K2BeamNode_ApiRequest_GetRecommended.h"

#include "BeamK2.h"

#include "BeamableCore/Public/AutoGen/SubSystems/BeamGroupUsersApi.h"
#include "BeamableCore/Public/AutoGen/SubSystems/GroupUsers/GetRecommendedRequest.h"
#include "BeamableCore/Public/AutoGen/GroupSearchResponse.h"

#define LOCTEXT_NAMESPACE "K2BeamNode_ApiRequest_GetRecommended"

using namespace BeamK2;

FName UK2BeamNode_ApiRequest_GetRecommended::GetSelfFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamGroupUsersApi, GetSelf);
}

FName UK2BeamNode_ApiRequest_GetRecommended::GetRequestFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamGroupUsersApi, GetRecommended);
}

FName UK2BeamNode_ApiRequest_GetRecommended::GetMakeFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UGetRecommendedRequest, Make);
}

FString UK2BeamNode_ApiRequest_GetRecommended::GetServiceName() const
{
	return TEXT("GroupUsers");
}

FString UK2BeamNode_ApiRequest_GetRecommended::GetEndpointName() const
{
	return TEXT("GetRecommended");
}

UClass* UK2BeamNode_ApiRequest_GetRecommended::GetApiClass() const
{
	return UBeamGroupUsersApi::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_GetRecommended::GetRequestClass() const
{
	return UGetRecommendedRequest::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_GetRecommended::GetResponseClass() const
{
	return UGroupSearchResponse::StaticClass();
}

FString UK2BeamNode_ApiRequest_GetRecommended::GetRequestSuccessDelegateName() const
{
	return TEXT("OnGetRecommendedSuccess");
}

FString UK2BeamNode_ApiRequest_GetRecommended::GetRequestErrorDelegateName() const
{
	return TEXT("OnGetRecommendedError");
}

FString UK2BeamNode_ApiRequest_GetRecommended::GetRequestCompleteDelegateName() const
{
	return TEXT("OnGetRecommendedComplete");
}

#undef LOCTEXT_NAMESPACE
