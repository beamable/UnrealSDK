

#include "BeamableCoreBlueprintNodes/Public/BeamFlow/ApiRequest/AutoGen/Accounts/K2BeamNode_ApiRequest_PostEmailUpdateInit.h"

#include "BeamK2.h"

#include "BeamableCore/Public/AutoGen/SubSystems/BeamAccountsApi.h"
#include "BeamableCore/Public/AutoGen/SubSystems/Accounts/PostEmailUpdateInitRequest.h"
#include "BeamableCore/Public/AutoGen/EmptyResponse.h"

#define LOCTEXT_NAMESPACE "K2BeamNode_ApiRequest_PostEmailUpdateInit"

using namespace BeamK2;

FName UK2BeamNode_ApiRequest_PostEmailUpdateInit::GetSelfFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamAccountsApi, GetSelf);
}

FName UK2BeamNode_ApiRequest_PostEmailUpdateInit::GetRequestFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamAccountsApi, PostEmailUpdateInit);
}

FName UK2BeamNode_ApiRequest_PostEmailUpdateInit::GetMakeFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UPostEmailUpdateInitRequest, Make);
}

FString UK2BeamNode_ApiRequest_PostEmailUpdateInit::GetServiceName() const
{
	return TEXT("Accounts");
}

FString UK2BeamNode_ApiRequest_PostEmailUpdateInit::GetEndpointName() const
{
	return TEXT("PostEmailUpdateInit");
}

UClass* UK2BeamNode_ApiRequest_PostEmailUpdateInit::GetApiClass() const
{
	return UBeamAccountsApi::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_PostEmailUpdateInit::GetRequestClass() const
{
	return UPostEmailUpdateInitRequest::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_PostEmailUpdateInit::GetResponseClass() const
{
	return UEmptyResponse::StaticClass();
}

FString UK2BeamNode_ApiRequest_PostEmailUpdateInit::GetRequestSuccessDelegateName() const
{
	return TEXT("OnPostEmailUpdateInitSuccess");
}

FString UK2BeamNode_ApiRequest_PostEmailUpdateInit::GetRequestErrorDelegateName() const
{
	return TEXT("OnPostEmailUpdateInitError");
}

FString UK2BeamNode_ApiRequest_PostEmailUpdateInit::GetRequestCompleteDelegateName() const
{
	return TEXT("OnPostEmailUpdateInitComplete");
}

#undef LOCTEXT_NAMESPACE
