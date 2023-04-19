

#include "BeamableCoreBlueprintNodes/Public/BeamFlow/ApiRequest/AutoGen/Realms/K2BeamNode_ApiRequest_DeleteProject.h"

#include "BeamK2.h"

#include "BeamableCore/Public/AutoGen/SubSystems/BeamRealmsApi.h"
#include "BeamableCore/Public/AutoGen/SubSystems/Realms/DeleteProjectRequest.h"
#include "BeamableCore/Public/AutoGen/CommonResponse.h"

#define LOCTEXT_NAMESPACE "K2BeamNode_ApiRequest_DeleteProject"

using namespace BeamK2;

FName UK2BeamNode_ApiRequest_DeleteProject::GetSelfFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamRealmsApi, GetSelf);
}

FName UK2BeamNode_ApiRequest_DeleteProject::GetRequestFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamRealmsApi, DeleteProject);
}

FName UK2BeamNode_ApiRequest_DeleteProject::GetMakeFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UDeleteProjectRequest, Make);
}

FString UK2BeamNode_ApiRequest_DeleteProject::GetServiceName() const
{
	return TEXT("Realms");
}

FString UK2BeamNode_ApiRequest_DeleteProject::GetEndpointName() const
{
	return TEXT("DeleteProject");
}

UClass* UK2BeamNode_ApiRequest_DeleteProject::GetApiClass() const
{
	return UBeamRealmsApi::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_DeleteProject::GetRequestClass() const
{
	return UDeleteProjectRequest::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_DeleteProject::GetResponseClass() const
{
	return UCommonResponse::StaticClass();
}

FString UK2BeamNode_ApiRequest_DeleteProject::GetRequestSuccessDelegateName() const
{
	return TEXT("OnDeleteProjectSuccess");
}

FString UK2BeamNode_ApiRequest_DeleteProject::GetRequestErrorDelegateName() const
{
	return TEXT("OnDeleteProjectError");
}

FString UK2BeamNode_ApiRequest_DeleteProject::GetRequestCompleteDelegateName() const
{
	return TEXT("OnDeleteProjectComplete");
}

#undef LOCTEXT_NAMESPACE
