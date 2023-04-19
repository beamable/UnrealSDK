

#include "BeamableCoreBlueprintNodes/Public/BeamFlow/ApiRequest/AutoGen/Content/K2BeamNode_ApiRequest_PutLocalizations.h"

#include "BeamK2.h"

#include "BeamableCore/Public/AutoGen/SubSystems/BeamContentApi.h"
#include "BeamableCore/Public/AutoGen/SubSystems/Content/PutLocalizationsRequest.h"
#include "BeamableCore/Public/AutoGen/CommonResponse.h"

#define LOCTEXT_NAMESPACE "K2BeamNode_ApiRequest_PutLocalizations"

using namespace BeamK2;

FName UK2BeamNode_ApiRequest_PutLocalizations::GetSelfFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamContentApi, GetSelf);
}

FName UK2BeamNode_ApiRequest_PutLocalizations::GetRequestFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamContentApi, PutLocalizations);
}

FName UK2BeamNode_ApiRequest_PutLocalizations::GetMakeFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UPutLocalizationsRequest, Make);
}

FString UK2BeamNode_ApiRequest_PutLocalizations::GetServiceName() const
{
	return TEXT("Content");
}

FString UK2BeamNode_ApiRequest_PutLocalizations::GetEndpointName() const
{
	return TEXT("PutLocalizations");
}

UClass* UK2BeamNode_ApiRequest_PutLocalizations::GetApiClass() const
{
	return UBeamContentApi::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_PutLocalizations::GetRequestClass() const
{
	return UPutLocalizationsRequest::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_PutLocalizations::GetResponseClass() const
{
	return UCommonResponse::StaticClass();
}

FString UK2BeamNode_ApiRequest_PutLocalizations::GetRequestSuccessDelegateName() const
{
	return TEXT("OnPutLocalizationsSuccess");
}

FString UK2BeamNode_ApiRequest_PutLocalizations::GetRequestErrorDelegateName() const
{
	return TEXT("OnPutLocalizationsError");
}

FString UK2BeamNode_ApiRequest_PutLocalizations::GetRequestCompleteDelegateName() const
{
	return TEXT("OnPutLocalizationsComplete");
}

#undef LOCTEXT_NAMESPACE
