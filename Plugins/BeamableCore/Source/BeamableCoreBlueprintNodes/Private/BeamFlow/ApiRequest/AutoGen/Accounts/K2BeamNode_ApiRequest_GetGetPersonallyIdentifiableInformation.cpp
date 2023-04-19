

#include "BeamableCoreBlueprintNodes/Public/BeamFlow/ApiRequest/AutoGen/Accounts/K2BeamNode_ApiRequest_GetGetPersonallyIdentifiableInformation.h"

#include "BeamK2.h"

#include "BeamableCore/Public/AutoGen/SubSystems/BeamAccountsApi.h"
#include "BeamableCore/Public/AutoGen/SubSystems/Accounts/GetGetPersonallyIdentifiableInformationRequest.h"
#include "BeamableCore/Public/AutoGen/AccountPersonallyIdentifiableInformationResponse.h"

#define LOCTEXT_NAMESPACE "K2BeamNode_ApiRequest_GetGetPersonallyIdentifiableInformation"

using namespace BeamK2;

FName UK2BeamNode_ApiRequest_GetGetPersonallyIdentifiableInformation::GetSelfFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamAccountsApi, GetSelf);
}

FName UK2BeamNode_ApiRequest_GetGetPersonallyIdentifiableInformation::GetRequestFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamAccountsApi, GetGetPersonallyIdentifiableInformation);
}

FName UK2BeamNode_ApiRequest_GetGetPersonallyIdentifiableInformation::GetMakeFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UGetGetPersonallyIdentifiableInformationRequest, Make);
}

FString UK2BeamNode_ApiRequest_GetGetPersonallyIdentifiableInformation::GetServiceName() const
{
	return TEXT("Accounts");
}

FString UK2BeamNode_ApiRequest_GetGetPersonallyIdentifiableInformation::GetEndpointName() const
{
	return TEXT("GetGetPersonallyIdentifiableInformation");
}

UClass* UK2BeamNode_ApiRequest_GetGetPersonallyIdentifiableInformation::GetApiClass() const
{
	return UBeamAccountsApi::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_GetGetPersonallyIdentifiableInformation::GetRequestClass() const
{
	return UGetGetPersonallyIdentifiableInformationRequest::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_GetGetPersonallyIdentifiableInformation::GetResponseClass() const
{
	return UAccountPersonallyIdentifiableInformationResponse::StaticClass();
}

FString UK2BeamNode_ApiRequest_GetGetPersonallyIdentifiableInformation::GetRequestSuccessDelegateName() const
{
	return TEXT("OnGetGetPersonallyIdentifiableInformationSuccess");
}

FString UK2BeamNode_ApiRequest_GetGetPersonallyIdentifiableInformation::GetRequestErrorDelegateName() const
{
	return TEXT("OnGetGetPersonallyIdentifiableInformationError");
}

FString UK2BeamNode_ApiRequest_GetGetPersonallyIdentifiableInformation::GetRequestCompleteDelegateName() const
{
	return TEXT("OnGetGetPersonallyIdentifiableInformationComplete");
}

#undef LOCTEXT_NAMESPACE
