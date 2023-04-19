

#include "BeamableCoreBlueprintNodes/Public/BeamFlow/ApiRequest/AutoGen/Push/K2BeamNode_ApiRequest_BasicPushPostRegister.h"

#include "BeamK2.h"

#include "BeamableCore/Public/AutoGen/SubSystems/BeamPushApi.h"
#include "BeamableCore/Public/AutoGen/SubSystems/Push/BasicPushPostRegisterRequest.h"
#include "BeamableCore/Public/AutoGen/EmptyRsp.h"

#define LOCTEXT_NAMESPACE "K2BeamNode_ApiRequest_BasicPushPostRegister"

using namespace BeamK2;

FName UK2BeamNode_ApiRequest_BasicPushPostRegister::GetSelfFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamPushApi, GetSelf);
}

FName UK2BeamNode_ApiRequest_BasicPushPostRegister::GetRequestFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamPushApi, PostRegister);
}

FName UK2BeamNode_ApiRequest_BasicPushPostRegister::GetMakeFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBasicPushPostRegisterRequest, Make);
}

FString UK2BeamNode_ApiRequest_BasicPushPostRegister::GetServiceName() const
{
	return TEXT("Push");
}

FString UK2BeamNode_ApiRequest_BasicPushPostRegister::GetEndpointName() const
{
	return TEXT("PostRegister");
}

UClass* UK2BeamNode_ApiRequest_BasicPushPostRegister::GetApiClass() const
{
	return UBeamPushApi::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_BasicPushPostRegister::GetRequestClass() const
{
	return UBasicPushPostRegisterRequest::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_BasicPushPostRegister::GetResponseClass() const
{
	return UEmptyRsp::StaticClass();
}

FString UK2BeamNode_ApiRequest_BasicPushPostRegister::GetRequestSuccessDelegateName() const
{
	return TEXT("OnBasicPushPostRegisterSuccess");
}

FString UK2BeamNode_ApiRequest_BasicPushPostRegister::GetRequestErrorDelegateName() const
{
	return TEXT("OnBasicPushPostRegisterError");
}

FString UK2BeamNode_ApiRequest_BasicPushPostRegister::GetRequestCompleteDelegateName() const
{
	return TEXT("OnBasicPushPostRegisterComplete");
}

#undef LOCTEXT_NAMESPACE
