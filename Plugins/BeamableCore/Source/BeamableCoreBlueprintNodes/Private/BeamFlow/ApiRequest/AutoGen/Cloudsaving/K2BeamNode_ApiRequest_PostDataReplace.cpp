

#include "BeamableCoreBlueprintNodes/Public/BeamFlow/ApiRequest/AutoGen/Cloudsaving/K2BeamNode_ApiRequest_PostDataReplace.h"

#include "BeamK2.h"

#include "BeamableCore/Public/AutoGen/SubSystems/BeamCloudsavingApi.h"
#include "BeamableCore/Public/AutoGen/SubSystems/Cloudsaving/PostDataReplaceRequest.h"
#include "BeamableCore/Public/AutoGen/CloudsavingBasicManifest.h"

#define LOCTEXT_NAMESPACE "K2BeamNode_ApiRequest_PostDataReplace"

using namespace BeamK2;

FName UK2BeamNode_ApiRequest_PostDataReplace::GetSelfFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamCloudsavingApi, GetSelf);
}

FName UK2BeamNode_ApiRequest_PostDataReplace::GetRequestFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamCloudsavingApi, PostDataReplace);
}

FName UK2BeamNode_ApiRequest_PostDataReplace::GetMakeFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UPostDataReplaceRequest, Make);
}

FString UK2BeamNode_ApiRequest_PostDataReplace::GetServiceName() const
{
	return TEXT("Cloudsaving");
}

FString UK2BeamNode_ApiRequest_PostDataReplace::GetEndpointName() const
{
	return TEXT("PostDataReplace");
}

UClass* UK2BeamNode_ApiRequest_PostDataReplace::GetApiClass() const
{
	return UBeamCloudsavingApi::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_PostDataReplace::GetRequestClass() const
{
	return UPostDataReplaceRequest::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_PostDataReplace::GetResponseClass() const
{
	return UCloudsavingBasicManifest::StaticClass();
}

FString UK2BeamNode_ApiRequest_PostDataReplace::GetRequestSuccessDelegateName() const
{
	return TEXT("OnPostDataReplaceSuccess");
}

FString UK2BeamNode_ApiRequest_PostDataReplace::GetRequestErrorDelegateName() const
{
	return TEXT("OnPostDataReplaceError");
}

FString UK2BeamNode_ApiRequest_PostDataReplace::GetRequestCompleteDelegateName() const
{
	return TEXT("OnPostDataReplaceComplete");
}

#undef LOCTEXT_NAMESPACE
