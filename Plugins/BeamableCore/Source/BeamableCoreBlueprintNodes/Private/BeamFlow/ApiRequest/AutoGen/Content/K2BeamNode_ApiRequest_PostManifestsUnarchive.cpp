

#include "BeamableCoreBlueprintNodes/Public/BeamFlow/ApiRequest/AutoGen/Content/K2BeamNode_ApiRequest_PostManifestsUnarchive.h"

#include "BeamK2.h"

#include "BeamableCore/Public/AutoGen/SubSystems/BeamContentApi.h"
#include "BeamableCore/Public/AutoGen/SubSystems/Content/PostManifestsUnarchiveRequest.h"
#include "BeamableCore/Public/AutoGen/EmptyResponse.h"

#define LOCTEXT_NAMESPACE "K2BeamNode_ApiRequest_PostManifestsUnarchive"

using namespace BeamK2;

FName UK2BeamNode_ApiRequest_PostManifestsUnarchive::GetSelfFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamContentApi, GetSelf);
}

FName UK2BeamNode_ApiRequest_PostManifestsUnarchive::GetRequestFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamContentApi, PostManifestsUnarchive);
}

FName UK2BeamNode_ApiRequest_PostManifestsUnarchive::GetMakeFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UPostManifestsUnarchiveRequest, Make);
}

FString UK2BeamNode_ApiRequest_PostManifestsUnarchive::GetServiceName() const
{
	return TEXT("Content");
}

FString UK2BeamNode_ApiRequest_PostManifestsUnarchive::GetEndpointName() const
{
	return TEXT("PostManifestsUnarchive");
}

UClass* UK2BeamNode_ApiRequest_PostManifestsUnarchive::GetApiClass() const
{
	return UBeamContentApi::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_PostManifestsUnarchive::GetRequestClass() const
{
	return UPostManifestsUnarchiveRequest::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_PostManifestsUnarchive::GetResponseClass() const
{
	return UEmptyResponse::StaticClass();
}

FString UK2BeamNode_ApiRequest_PostManifestsUnarchive::GetRequestSuccessDelegateName() const
{
	return TEXT("OnPostManifestsUnarchiveSuccess");
}

FString UK2BeamNode_ApiRequest_PostManifestsUnarchive::GetRequestErrorDelegateName() const
{
	return TEXT("OnPostManifestsUnarchiveError");
}

FString UK2BeamNode_ApiRequest_PostManifestsUnarchive::GetRequestCompleteDelegateName() const
{
	return TEXT("OnPostManifestsUnarchiveComplete");
}

#undef LOCTEXT_NAMESPACE
