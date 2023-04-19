

#include "BeamableCoreBlueprintNodes/Public/BeamFlow/ApiRequest/AutoGen/Content/K2BeamNode_ApiRequest_GetLocalizations.h"

#include "BeamK2.h"

#include "BeamableCore/Public/AutoGen/SubSystems/BeamContentApi.h"
#include "BeamableCore/Public/AutoGen/SubSystems/Content/GetLocalizationsRequest.h"
#include "BeamableCore/Public/AutoGen/GetLocalizationsResponse.h"

#define LOCTEXT_NAMESPACE "K2BeamNode_ApiRequest_GetLocalizations"

using namespace BeamK2;

FName UK2BeamNode_ApiRequest_GetLocalizations::GetSelfFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamContentApi, GetSelf);
}

FName UK2BeamNode_ApiRequest_GetLocalizations::GetRequestFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamContentApi, GetLocalizations);
}

FName UK2BeamNode_ApiRequest_GetLocalizations::GetMakeFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UGetLocalizationsRequest, Make);
}

FString UK2BeamNode_ApiRequest_GetLocalizations::GetServiceName() const
{
	return TEXT("Content");
}

FString UK2BeamNode_ApiRequest_GetLocalizations::GetEndpointName() const
{
	return TEXT("GetLocalizations");
}

UClass* UK2BeamNode_ApiRequest_GetLocalizations::GetApiClass() const
{
	return UBeamContentApi::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_GetLocalizations::GetRequestClass() const
{
	return UGetLocalizationsRequest::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_GetLocalizations::GetResponseClass() const
{
	return UGetLocalizationsResponse::StaticClass();
}

FString UK2BeamNode_ApiRequest_GetLocalizations::GetRequestSuccessDelegateName() const
{
	return TEXT("OnGetLocalizationsSuccess");
}

FString UK2BeamNode_ApiRequest_GetLocalizations::GetRequestErrorDelegateName() const
{
	return TEXT("OnGetLocalizationsError");
}

FString UK2BeamNode_ApiRequest_GetLocalizations::GetRequestCompleteDelegateName() const
{
	return TEXT("OnGetLocalizationsComplete");
}

#undef LOCTEXT_NAMESPACE
