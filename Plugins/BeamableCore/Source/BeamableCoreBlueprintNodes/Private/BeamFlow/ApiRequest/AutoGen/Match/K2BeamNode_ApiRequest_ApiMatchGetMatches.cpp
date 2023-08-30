

#include "BeamableCoreBlueprintNodes/Public/BeamFlow/ApiRequest/AutoGen/Match/K2BeamNode_ApiRequest_ApiMatchGetMatches.h"

#include "BeamK2.h"

#include "BeamableCore/Public/AutoGen/SubSystems/BeamMatchApi.h"
#include "BeamableCore/Public/AutoGen/SubSystems/Match/ApiMatchGetMatchesRequest.h"
#include "BeamableCore/Public/AutoGen/Match.h"

#define LOCTEXT_NAMESPACE "K2BeamNode_ApiRequest_ApiMatchGetMatches"

using namespace BeamK2;

FName UK2BeamNode_ApiRequest_ApiMatchGetMatches::GetSelfFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamMatchApi, GetSelf);
}

FName UK2BeamNode_ApiRequest_ApiMatchGetMatches::GetRequestFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamMatchApi, GetMatches);
}

FName UK2BeamNode_ApiRequest_ApiMatchGetMatches::GetMakeFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UApiMatchGetMatchesRequest, Make);
}

FString UK2BeamNode_ApiRequest_ApiMatchGetMatches::GetServiceName() const
{
	return TEXT("Match");
}

FString UK2BeamNode_ApiRequest_ApiMatchGetMatches::GetEndpointName() const
{
	return TEXT("GetMatches");
}

UClass* UK2BeamNode_ApiRequest_ApiMatchGetMatches::GetApiClass() const
{
	return UBeamMatchApi::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_ApiMatchGetMatches::GetRequestClass() const
{
	return UApiMatchGetMatchesRequest::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_ApiMatchGetMatches::GetResponseClass() const
{
	return UMatch::StaticClass();
}

FString UK2BeamNode_ApiRequest_ApiMatchGetMatches::GetRequestSuccessDelegateName() const
{
	return TEXT("OnApiMatchGetMatchesSuccess");
}

FString UK2BeamNode_ApiRequest_ApiMatchGetMatches::GetRequestErrorDelegateName() const
{
	return TEXT("OnApiMatchGetMatchesError");
}

FString UK2BeamNode_ApiRequest_ApiMatchGetMatches::GetRequestCompleteDelegateName() const
{
	return TEXT("OnApiMatchGetMatchesComplete");
}

#undef LOCTEXT_NAMESPACE
