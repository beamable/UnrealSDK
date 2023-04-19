

#include "BeamableCoreBlueprintNodes/Public/BeamFlow/ApiRequest/AutoGen/Realms/K2BeamNode_ApiRequest_GetProject.h"

#include "BeamK2.h"

#include "BeamableCore/Public/AutoGen/SubSystems/BeamRealmsApi.h"
#include "BeamableCore/Public/AutoGen/SubSystems/Realms/GetProjectRequest.h"
#include "BeamableCore/Public/AutoGen/ProjectView.h"

#define LOCTEXT_NAMESPACE "K2BeamNode_ApiRequest_GetProject"

using namespace BeamK2;

FName UK2BeamNode_ApiRequest_GetProject::GetSelfFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamRealmsApi, GetSelf);
}

FName UK2BeamNode_ApiRequest_GetProject::GetRequestFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamRealmsApi, GetProject);
}

FName UK2BeamNode_ApiRequest_GetProject::GetMakeFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UGetProjectRequest, Make);
}

FString UK2BeamNode_ApiRequest_GetProject::GetServiceName() const
{
	return TEXT("Realms");
}

FString UK2BeamNode_ApiRequest_GetProject::GetEndpointName() const
{
	return TEXT("GetProject");
}

UClass* UK2BeamNode_ApiRequest_GetProject::GetApiClass() const
{
	return UBeamRealmsApi::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_GetProject::GetRequestClass() const
{
	return UGetProjectRequest::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_GetProject::GetResponseClass() const
{
	return UProjectView::StaticClass();
}

FString UK2BeamNode_ApiRequest_GetProject::GetRequestSuccessDelegateName() const
{
	return TEXT("OnGetProjectSuccess");
}

FString UK2BeamNode_ApiRequest_GetProject::GetRequestErrorDelegateName() const
{
	return TEXT("OnGetProjectError");
}

FString UK2BeamNode_ApiRequest_GetProject::GetRequestCompleteDelegateName() const
{
	return TEXT("OnGetProjectComplete");
}

#undef LOCTEXT_NAMESPACE
