

#include "BeamableCoreBlueprintNodes/Public/BeamFlow/ApiRequest/AutoGen/Content/K2BeamNode_ApiRequest_PutManifestRepeat.h"

#include "BeamK2.h"

#include "BeamableCore/Public/AutoGen/SubSystems/BeamContentApi.h"
#include "BeamableCore/Public/AutoGen/SubSystems/Content/PutManifestRepeatRequest.h"
#include "BeamableCore/Public/AutoGen/CommonResponse.h"

#define LOCTEXT_NAMESPACE "K2BeamNode_ApiRequest_PutManifestRepeat"

using namespace BeamK2;

FName UK2BeamNode_ApiRequest_PutManifestRepeat::GetSelfFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamContentApi, GetSelf);
}

FName UK2BeamNode_ApiRequest_PutManifestRepeat::GetRequestFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamContentApi, PutManifestRepeat);
}

FName UK2BeamNode_ApiRequest_PutManifestRepeat::GetMakeFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UPutManifestRepeatRequest, Make);
}

FString UK2BeamNode_ApiRequest_PutManifestRepeat::GetServiceName() const
{
	return TEXT("Content");
}

FString UK2BeamNode_ApiRequest_PutManifestRepeat::GetEndpointName() const
{
	return TEXT("PutManifestRepeat");
}

UClass* UK2BeamNode_ApiRequest_PutManifestRepeat::GetApiClass() const
{
	return UBeamContentApi::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_PutManifestRepeat::GetRequestClass() const
{
	return UPutManifestRepeatRequest::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_PutManifestRepeat::GetResponseClass() const
{
	return UCommonResponse::StaticClass();
}

FString UK2BeamNode_ApiRequest_PutManifestRepeat::GetRequestSuccessDelegateName() const
{
	return TEXT("OnPutManifestRepeatSuccess");
}

FString UK2BeamNode_ApiRequest_PutManifestRepeat::GetRequestErrorDelegateName() const
{
	return TEXT("OnPutManifestRepeatError");
}

FString UK2BeamNode_ApiRequest_PutManifestRepeat::GetRequestCompleteDelegateName() const
{
	return TEXT("OnPutManifestRepeatComplete");
}

#undef LOCTEXT_NAMESPACE
