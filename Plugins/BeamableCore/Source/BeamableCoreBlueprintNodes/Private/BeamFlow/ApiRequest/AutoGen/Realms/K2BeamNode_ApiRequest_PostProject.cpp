

#include "BeamableCoreBlueprintNodes/Public/BeamFlow/ApiRequest/AutoGen/Realms/K2BeamNode_ApiRequest_PostProject.h"

#include "BeamK2.h"

#include "BeamableCore/Public/AutoGen/SubSystems/BeamRealmsApi.h"
#include "BeamableCore/Public/AutoGen/SubSystems/Realms/PostProjectRequest.h"
#include "BeamableCore/Public/AutoGen/CommonResponse.h"

#define LOCTEXT_NAMESPACE "K2BeamNode_ApiRequest_PostProject"

using namespace BeamK2;

FName UK2BeamNode_ApiRequest_PostProject::GetSelfFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamRealmsApi, GetSelf);
}

FName UK2BeamNode_ApiRequest_PostProject::GetRequestFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamRealmsApi, PostProject);
}

FName UK2BeamNode_ApiRequest_PostProject::GetMakeFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UPostProjectRequest, Make);
}

FString UK2BeamNode_ApiRequest_PostProject::GetServiceName() const
{
	return TEXT("Realms");
}

FString UK2BeamNode_ApiRequest_PostProject::GetEndpointName() const
{
	return TEXT("PostProject");
}

UClass* UK2BeamNode_ApiRequest_PostProject::GetApiClass() const
{
	return UBeamRealmsApi::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_PostProject::GetRequestClass() const
{
	return UPostProjectRequest::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_PostProject::GetResponseClass() const
{
	return UCommonResponse::StaticClass();
}

FString UK2BeamNode_ApiRequest_PostProject::GetRequestSuccessDelegateName() const
{
	return TEXT("OnPostProjectSuccess");
}

FString UK2BeamNode_ApiRequest_PostProject::GetRequestErrorDelegateName() const
{
	return TEXT("OnPostProjectError");
}

FString UK2BeamNode_ApiRequest_PostProject::GetRequestCompleteDelegateName() const
{
	return TEXT("OnPostProjectComplete");
}

#undef LOCTEXT_NAMESPACE
