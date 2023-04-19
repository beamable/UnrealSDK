

#include "BeamableCoreBlueprintNodes/Public/BeamFlow/ApiRequest/AutoGen/Stats/K2BeamNode_ApiRequest_PutSubscribe.h"

#include "BeamK2.h"

#include "BeamableCore/Public/AutoGen/SubSystems/BeamStatsApi.h"
#include "BeamableCore/Public/AutoGen/SubSystems/Stats/PutSubscribeRequest.h"
#include "BeamableCore/Public/AutoGen/CommonResponse.h"

#define LOCTEXT_NAMESPACE "K2BeamNode_ApiRequest_PutSubscribe"

using namespace BeamK2;

FName UK2BeamNode_ApiRequest_PutSubscribe::GetSelfFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamStatsApi, GetSelf);
}

FName UK2BeamNode_ApiRequest_PutSubscribe::GetRequestFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamStatsApi, PutSubscribe);
}

FName UK2BeamNode_ApiRequest_PutSubscribe::GetMakeFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UPutSubscribeRequest, Make);
}

FString UK2BeamNode_ApiRequest_PutSubscribe::GetServiceName() const
{
	return TEXT("Stats");
}

FString UK2BeamNode_ApiRequest_PutSubscribe::GetEndpointName() const
{
	return TEXT("PutSubscribe");
}

UClass* UK2BeamNode_ApiRequest_PutSubscribe::GetApiClass() const
{
	return UBeamStatsApi::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_PutSubscribe::GetRequestClass() const
{
	return UPutSubscribeRequest::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_PutSubscribe::GetResponseClass() const
{
	return UCommonResponse::StaticClass();
}

FString UK2BeamNode_ApiRequest_PutSubscribe::GetRequestSuccessDelegateName() const
{
	return TEXT("OnPutSubscribeSuccess");
}

FString UK2BeamNode_ApiRequest_PutSubscribe::GetRequestErrorDelegateName() const
{
	return TEXT("OnPutSubscribeError");
}

FString UK2BeamNode_ApiRequest_PutSubscribe::GetRequestCompleteDelegateName() const
{
	return TEXT("OnPutSubscribeComplete");
}

#undef LOCTEXT_NAMESPACE
