

#include "BeamableCoreBlueprintNodes/Public/BeamFlow/ApiRequest/AutoGen/Realms/K2BeamNode_ApiRequest_PutProjectRename.h"

#include "BeamK2.h"

#include "BeamableCore/Public/AutoGen/SubSystems/BeamRealmsApi.h"
#include "BeamableCore/Public/AutoGen/SubSystems/Realms/PutProjectRenameRequest.h"
#include "BeamableCore/Public/AutoGen/CommonResponse.h"

#define LOCTEXT_NAMESPACE "K2BeamNode_ApiRequest_PutProjectRename"

using namespace BeamK2;

FName UK2BeamNode_ApiRequest_PutProjectRename::GetSelfFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamRealmsApi, GetSelf);
}

FName UK2BeamNode_ApiRequest_PutProjectRename::GetRequestFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamRealmsApi, PutProjectRename);
}

FName UK2BeamNode_ApiRequest_PutProjectRename::GetMakeFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UPutProjectRenameRequest, Make);
}

FString UK2BeamNode_ApiRequest_PutProjectRename::GetServiceName() const
{
	return TEXT("Realms");
}

FString UK2BeamNode_ApiRequest_PutProjectRename::GetEndpointName() const
{
	return TEXT("PutProjectRename");
}

UClass* UK2BeamNode_ApiRequest_PutProjectRename::GetApiClass() const
{
	return UBeamRealmsApi::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_PutProjectRename::GetRequestClass() const
{
	return UPutProjectRenameRequest::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_PutProjectRename::GetResponseClass() const
{
	return UCommonResponse::StaticClass();
}

FString UK2BeamNode_ApiRequest_PutProjectRename::GetRequestSuccessDelegateName() const
{
	return TEXT("OnPutProjectRenameSuccess");
}

FString UK2BeamNode_ApiRequest_PutProjectRename::GetRequestErrorDelegateName() const
{
	return TEXT("OnPutProjectRenameError");
}

FString UK2BeamNode_ApiRequest_PutProjectRename::GetRequestCompleteDelegateName() const
{
	return TEXT("OnPutProjectRenameComplete");
}

#undef LOCTEXT_NAMESPACE
