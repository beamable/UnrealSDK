

#include "BeamableCoreBlueprintNodes/Public/BeamFlow/ApiRequest/AutoGen/Realms/K2BeamNode_ApiRequest_PutProject.h"

#include "BeamK2.h"

#include "BeamableCore/Public/AutoGen/SubSystems/BeamRealmsApi.h"
#include "BeamableCore/Public/AutoGen/SubSystems/Realms/PutProjectRequest.h"
#include "BeamableCore/Public/AutoGen/CommonResponse.h"

#define LOCTEXT_NAMESPACE "K2BeamNode_ApiRequest_PutProject"

using namespace BeamK2;

FName UK2BeamNode_ApiRequest_PutProject::GetSelfFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamRealmsApi, GetSelf);
}

FName UK2BeamNode_ApiRequest_PutProject::GetRequestFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamRealmsApi, PutProject);
}

FName UK2BeamNode_ApiRequest_PutProject::GetMakeFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UPutProjectRequest, Make);
}

FString UK2BeamNode_ApiRequest_PutProject::GetServiceName() const
{
	return TEXT("Realms");
}

FString UK2BeamNode_ApiRequest_PutProject::GetEndpointName() const
{
	return TEXT("PutProject");
}

UClass* UK2BeamNode_ApiRequest_PutProject::GetApiClass() const
{
	return UBeamRealmsApi::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_PutProject::GetRequestClass() const
{
	return UPutProjectRequest::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_PutProject::GetResponseClass() const
{
	return UCommonResponse::StaticClass();
}

FString UK2BeamNode_ApiRequest_PutProject::GetRequestSuccessDelegateName() const
{
	return TEXT("OnPutProjectSuccess");
}

FString UK2BeamNode_ApiRequest_PutProject::GetRequestErrorDelegateName() const
{
	return TEXT("OnPutProjectError");
}

FString UK2BeamNode_ApiRequest_PutProject::GetRequestCompleteDelegateName() const
{
	return TEXT("OnPutProjectComplete");
}

#undef LOCTEXT_NAMESPACE
