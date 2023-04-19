

#include "BeamableCoreBlueprintNodes/Public/BeamFlow/ApiRequest/AutoGen/Stats/K2BeamNode_ApiRequest_PostSearchExtended.h"

#include "BeamK2.h"

#include "BeamableCore/Public/AutoGen/SubSystems/BeamStatsApi.h"
#include "BeamableCore/Public/AutoGen/SubSystems/Stats/PostSearchExtendedRequest.h"
#include "BeamableCore/Public/AutoGen/SearchExtendedResponse.h"

#define LOCTEXT_NAMESPACE "K2BeamNode_ApiRequest_PostSearchExtended"

using namespace BeamK2;

FName UK2BeamNode_ApiRequest_PostSearchExtended::GetSelfFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamStatsApi, GetSelf);
}

FName UK2BeamNode_ApiRequest_PostSearchExtended::GetRequestFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamStatsApi, PostSearchExtended);
}

FName UK2BeamNode_ApiRequest_PostSearchExtended::GetMakeFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UPostSearchExtendedRequest, Make);
}

FString UK2BeamNode_ApiRequest_PostSearchExtended::GetServiceName() const
{
	return TEXT("Stats");
}

FString UK2BeamNode_ApiRequest_PostSearchExtended::GetEndpointName() const
{
	return TEXT("PostSearchExtended");
}

UClass* UK2BeamNode_ApiRequest_PostSearchExtended::GetApiClass() const
{
	return UBeamStatsApi::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_PostSearchExtended::GetRequestClass() const
{
	return UPostSearchExtendedRequest::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_PostSearchExtended::GetResponseClass() const
{
	return USearchExtendedResponse::StaticClass();
}

FString UK2BeamNode_ApiRequest_PostSearchExtended::GetRequestSuccessDelegateName() const
{
	return TEXT("OnPostSearchExtendedSuccess");
}

FString UK2BeamNode_ApiRequest_PostSearchExtended::GetRequestErrorDelegateName() const
{
	return TEXT("OnPostSearchExtendedError");
}

FString UK2BeamNode_ApiRequest_PostSearchExtended::GetRequestCompleteDelegateName() const
{
	return TEXT("OnPostSearchExtendedComplete");
}

#undef LOCTEXT_NAMESPACE
