

#include "BeamableCoreBlueprintNodes/Public/BeamFlow/ApiRequest/AutoGen/Content/K2BeamNode_ApiRequest_PostManifestsArchive.h"

#include "BeamK2.h"

#include "BeamableCore/Public/AutoGen/SubSystems/BeamContentApi.h"
#include "BeamableCore/Public/AutoGen/SubSystems/Content/PostManifestsArchiveRequest.h"
#include "BeamableCore/Public/AutoGen/EmptyResponse.h"

#define LOCTEXT_NAMESPACE "K2BeamNode_ApiRequest_PostManifestsArchive"

using namespace BeamK2;

FName UK2BeamNode_ApiRequest_PostManifestsArchive::GetSelfFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamContentApi, GetSelf);
}

FName UK2BeamNode_ApiRequest_PostManifestsArchive::GetRequestFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamContentApi, PostManifestsArchive);
}

FName UK2BeamNode_ApiRequest_PostManifestsArchive::GetMakeFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UPostManifestsArchiveRequest, Make);
}

FString UK2BeamNode_ApiRequest_PostManifestsArchive::GetServiceName() const
{
	return TEXT("Content");
}

FString UK2BeamNode_ApiRequest_PostManifestsArchive::GetEndpointName() const
{
	return TEXT("PostManifestsArchive");
}

UClass* UK2BeamNode_ApiRequest_PostManifestsArchive::GetApiClass() const
{
	return UBeamContentApi::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_PostManifestsArchive::GetRequestClass() const
{
	return UPostManifestsArchiveRequest::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_PostManifestsArchive::GetResponseClass() const
{
	return UEmptyResponse::StaticClass();
}

FString UK2BeamNode_ApiRequest_PostManifestsArchive::GetRequestSuccessDelegateName() const
{
	return TEXT("OnPostManifestsArchiveSuccess");
}

FString UK2BeamNode_ApiRequest_PostManifestsArchive::GetRequestErrorDelegateName() const
{
	return TEXT("OnPostManifestsArchiveError");
}

FString UK2BeamNode_ApiRequest_PostManifestsArchive::GetRequestCompleteDelegateName() const
{
	return TEXT("OnPostManifestsArchiveComplete");
}

#undef LOCTEXT_NAMESPACE
