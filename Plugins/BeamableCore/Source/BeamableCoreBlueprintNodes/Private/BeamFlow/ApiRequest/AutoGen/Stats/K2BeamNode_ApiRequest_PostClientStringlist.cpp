

#include "BeamableCoreBlueprintNodes/Public/BeamFlow/ApiRequest/AutoGen/Stats/K2BeamNode_ApiRequest_PostClientStringlist.h"

#include "BeamK2.h"

#include "BeamableCore/Public/AutoGen/SubSystems/BeamStatsApi.h"
#include "BeamableCore/Public/AutoGen/SubSystems/Stats/PostClientStringlistRequest.h"
#include "BeamableCore/Public/AutoGen/EmptyResponse.h"

#define LOCTEXT_NAMESPACE "K2BeamNode_ApiRequest_PostClientStringlist"

using namespace BeamK2;

FName UK2BeamNode_ApiRequest_PostClientStringlist::GetSelfFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamStatsApi, GetSelf);
}

FName UK2BeamNode_ApiRequest_PostClientStringlist::GetRequestFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamStatsApi, PostClientStringlist);
}

FName UK2BeamNode_ApiRequest_PostClientStringlist::GetMakeFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UPostClientStringlistRequest, Make);
}

FString UK2BeamNode_ApiRequest_PostClientStringlist::GetServiceName() const
{
	return TEXT("Stats");
}

FString UK2BeamNode_ApiRequest_PostClientStringlist::GetEndpointName() const
{
	return TEXT("PostClientStringlist");
}

UClass* UK2BeamNode_ApiRequest_PostClientStringlist::GetApiClass() const
{
	return UBeamStatsApi::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_PostClientStringlist::GetRequestClass() const
{
	return UPostClientStringlistRequest::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_PostClientStringlist::GetResponseClass() const
{
	return UEmptyResponse::StaticClass();
}

FString UK2BeamNode_ApiRequest_PostClientStringlist::GetRequestSuccessDelegateName() const
{
	return TEXT("OnPostClientStringlistSuccess");
}

FString UK2BeamNode_ApiRequest_PostClientStringlist::GetRequestErrorDelegateName() const
{
	return TEXT("OnPostClientStringlistError");
}

FString UK2BeamNode_ApiRequest_PostClientStringlist::GetRequestCompleteDelegateName() const
{
	return TEXT("OnPostClientStringlistComplete");
}

#undef LOCTEXT_NAMESPACE
