

#include "BeamableCoreBlueprintNodes/Public/BeamFlow/ApiRequest/AutoGen/Content/K2BeamNode_ApiRequest_DeleteLocalizations.h"

#include "BeamK2.h"

#include "BeamableCore/Public/AutoGen/SubSystems/BeamContentApi.h"
#include "BeamableCore/Public/AutoGen/SubSystems/Content/DeleteLocalizationsRequest.h"
#include "BeamableCore/Public/AutoGen/CommonResponse.h"

#define LOCTEXT_NAMESPACE "K2BeamNode_ApiRequest_DeleteLocalizations"

using namespace BeamK2;

FName UK2BeamNode_ApiRequest_DeleteLocalizations::GetSelfFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamContentApi, GetSelf);
}

FName UK2BeamNode_ApiRequest_DeleteLocalizations::GetRequestFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamContentApi, DeleteLocalizations);
}

FName UK2BeamNode_ApiRequest_DeleteLocalizations::GetMakeFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UDeleteLocalizationsRequest, Make);
}

FString UK2BeamNode_ApiRequest_DeleteLocalizations::GetServiceName() const
{
	return TEXT("Content");
}

FString UK2BeamNode_ApiRequest_DeleteLocalizations::GetEndpointName() const
{
	return TEXT("DeleteLocalizations");
}

UClass* UK2BeamNode_ApiRequest_DeleteLocalizations::GetApiClass() const
{
	return UBeamContentApi::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_DeleteLocalizations::GetRequestClass() const
{
	return UDeleteLocalizationsRequest::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_DeleteLocalizations::GetResponseClass() const
{
	return UCommonResponse::StaticClass();
}

FString UK2BeamNode_ApiRequest_DeleteLocalizations::GetRequestSuccessDelegateName() const
{
	return TEXT("OnDeleteLocalizationsSuccess");
}

FString UK2BeamNode_ApiRequest_DeleteLocalizations::GetRequestErrorDelegateName() const
{
	return TEXT("OnDeleteLocalizationsError");
}

FString UK2BeamNode_ApiRequest_DeleteLocalizations::GetRequestCompleteDelegateName() const
{
	return TEXT("OnDeleteLocalizationsComplete");
}

#undef LOCTEXT_NAMESPACE
