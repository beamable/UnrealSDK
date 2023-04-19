

#include "BeamableCoreBlueprintNodes/Public/BeamFlow/ApiRequest/AutoGen/Content/K2BeamNode_ApiRequest_PostBinary.h"

#include "BeamK2.h"

#include "BeamableCore/Public/AutoGen/SubSystems/BeamContentApi.h"
#include "BeamableCore/Public/AutoGen/SubSystems/Content/PostBinaryRequest.h"
#include "BeamableCore/Public/AutoGen/SaveBinaryResponse.h"

#define LOCTEXT_NAMESPACE "K2BeamNode_ApiRequest_PostBinary"

using namespace BeamK2;

FName UK2BeamNode_ApiRequest_PostBinary::GetSelfFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamContentApi, GetSelf);
}

FName UK2BeamNode_ApiRequest_PostBinary::GetRequestFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamContentApi, PostBinary);
}

FName UK2BeamNode_ApiRequest_PostBinary::GetMakeFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UPostBinaryRequest, Make);
}

FString UK2BeamNode_ApiRequest_PostBinary::GetServiceName() const
{
	return TEXT("Content");
}

FString UK2BeamNode_ApiRequest_PostBinary::GetEndpointName() const
{
	return TEXT("PostBinary");
}

UClass* UK2BeamNode_ApiRequest_PostBinary::GetApiClass() const
{
	return UBeamContentApi::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_PostBinary::GetRequestClass() const
{
	return UPostBinaryRequest::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_PostBinary::GetResponseClass() const
{
	return USaveBinaryResponse::StaticClass();
}

FString UK2BeamNode_ApiRequest_PostBinary::GetRequestSuccessDelegateName() const
{
	return TEXT("OnPostBinarySuccess");
}

FString UK2BeamNode_ApiRequest_PostBinary::GetRequestErrorDelegateName() const
{
	return TEXT("OnPostBinaryError");
}

FString UK2BeamNode_ApiRequest_PostBinary::GetRequestCompleteDelegateName() const
{
	return TEXT("OnPostBinaryComplete");
}

#undef LOCTEXT_NAMESPACE
