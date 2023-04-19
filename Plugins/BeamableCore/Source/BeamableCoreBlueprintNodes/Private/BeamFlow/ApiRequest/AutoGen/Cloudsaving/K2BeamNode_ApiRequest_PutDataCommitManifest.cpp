

#include "BeamableCoreBlueprintNodes/Public/BeamFlow/ApiRequest/AutoGen/Cloudsaving/K2BeamNode_ApiRequest_PutDataCommitManifest.h"

#include "BeamK2.h"

#include "BeamableCore/Public/AutoGen/SubSystems/BeamCloudsavingApi.h"
#include "BeamableCore/Public/AutoGen/SubSystems/Cloudsaving/PutDataCommitManifestRequest.h"
#include "BeamableCore/Public/AutoGen/CloudsavingBasicManifest.h"

#define LOCTEXT_NAMESPACE "K2BeamNode_ApiRequest_PutDataCommitManifest"

using namespace BeamK2;

FName UK2BeamNode_ApiRequest_PutDataCommitManifest::GetSelfFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamCloudsavingApi, GetSelf);
}

FName UK2BeamNode_ApiRequest_PutDataCommitManifest::GetRequestFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamCloudsavingApi, PutDataCommitManifest);
}

FName UK2BeamNode_ApiRequest_PutDataCommitManifest::GetMakeFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UPutDataCommitManifestRequest, Make);
}

FString UK2BeamNode_ApiRequest_PutDataCommitManifest::GetServiceName() const
{
	return TEXT("Cloudsaving");
}

FString UK2BeamNode_ApiRequest_PutDataCommitManifest::GetEndpointName() const
{
	return TEXT("PutDataCommitManifest");
}

UClass* UK2BeamNode_ApiRequest_PutDataCommitManifest::GetApiClass() const
{
	return UBeamCloudsavingApi::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_PutDataCommitManifest::GetRequestClass() const
{
	return UPutDataCommitManifestRequest::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_PutDataCommitManifest::GetResponseClass() const
{
	return UCloudsavingBasicManifest::StaticClass();
}

FString UK2BeamNode_ApiRequest_PutDataCommitManifest::GetRequestSuccessDelegateName() const
{
	return TEXT("OnPutDataCommitManifestSuccess");
}

FString UK2BeamNode_ApiRequest_PutDataCommitManifest::GetRequestErrorDelegateName() const
{
	return TEXT("OnPutDataCommitManifestError");
}

FString UK2BeamNode_ApiRequest_PutDataCommitManifest::GetRequestCompleteDelegateName() const
{
	return TEXT("OnPutDataCommitManifestComplete");
}

#undef LOCTEXT_NAMESPACE
