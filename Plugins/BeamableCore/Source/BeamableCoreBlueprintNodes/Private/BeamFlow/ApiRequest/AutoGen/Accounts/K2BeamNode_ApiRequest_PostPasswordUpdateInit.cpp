

#include "BeamableCoreBlueprintNodes/Public/BeamFlow/ApiRequest/AutoGen/Accounts/K2BeamNode_ApiRequest_PostPasswordUpdateInit.h"

#include "BeamK2.h"

#include "BeamableCore/Public/AutoGen/SubSystems/BeamAccountsApi.h"
#include "BeamableCore/Public/AutoGen/SubSystems/Accounts/PostPasswordUpdateInitRequest.h"
#include "BeamableCore/Public/AutoGen/EmptyResponse.h"

#define LOCTEXT_NAMESPACE "K2BeamNode_ApiRequest_PostPasswordUpdateInit"

using namespace BeamK2;

FName UK2BeamNode_ApiRequest_PostPasswordUpdateInit::GetSelfFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamAccountsApi, GetSelf);
}

FName UK2BeamNode_ApiRequest_PostPasswordUpdateInit::GetRequestFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamAccountsApi, PostPasswordUpdateInit);
}

FName UK2BeamNode_ApiRequest_PostPasswordUpdateInit::GetMakeFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UPostPasswordUpdateInitRequest, Make);
}

FString UK2BeamNode_ApiRequest_PostPasswordUpdateInit::GetServiceName() const
{
	return TEXT("Accounts");
}

FString UK2BeamNode_ApiRequest_PostPasswordUpdateInit::GetEndpointName() const
{
	return TEXT("PostPasswordUpdateInit");
}

UClass* UK2BeamNode_ApiRequest_PostPasswordUpdateInit::GetApiClass() const
{
	return UBeamAccountsApi::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_PostPasswordUpdateInit::GetRequestClass() const
{
	return UPostPasswordUpdateInitRequest::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_PostPasswordUpdateInit::GetResponseClass() const
{
	return UEmptyResponse::StaticClass();
}

FString UK2BeamNode_ApiRequest_PostPasswordUpdateInit::GetRequestSuccessDelegateName() const
{
	return TEXT("OnPostPasswordUpdateInitSuccess");
}

FString UK2BeamNode_ApiRequest_PostPasswordUpdateInit::GetRequestErrorDelegateName() const
{
	return TEXT("OnPostPasswordUpdateInitError");
}

FString UK2BeamNode_ApiRequest_PostPasswordUpdateInit::GetRequestCompleteDelegateName() const
{
	return TEXT("OnPostPasswordUpdateInitComplete");
}

#undef LOCTEXT_NAMESPACE
