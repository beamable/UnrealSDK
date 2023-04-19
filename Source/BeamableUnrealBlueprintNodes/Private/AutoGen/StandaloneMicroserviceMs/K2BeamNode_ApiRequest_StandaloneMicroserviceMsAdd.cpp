

#include "BeamableUnrealBlueprintNodes/Public/AutoGen/StandaloneMicroserviceMs/K2BeamNode_ApiRequest_StandaloneMicroserviceMsAdd.h"

#include "BeamK2.h"

#include "BeamableUnreal/AutoGen/SubSystems/BeamStandaloneMicroserviceMsApi.h"
#include "BeamableUnreal/AutoGen/SubSystems/StandaloneMicroserviceMs/StandaloneMicroserviceMsAddRequest.h"
#include "BeamableUnreal/AutoGen/StandaloneMicroserviceMsAddResponse.h"

#define LOCTEXT_NAMESPACE "K2BeamNode_ApiRequest_StandaloneMicroserviceMsAdd"

using namespace BeamK2;

FName UK2BeamNode_ApiRequest_StandaloneMicroserviceMsAdd::GetSelfFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamStandaloneMicroserviceMsApi, GetSelf);
}

FName UK2BeamNode_ApiRequest_StandaloneMicroserviceMsAdd::GetRequestFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamStandaloneMicroserviceMsApi, Add);
}

FName UK2BeamNode_ApiRequest_StandaloneMicroserviceMsAdd::GetMakeFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UStandaloneMicroserviceMsAddRequest, Make);
}

FString UK2BeamNode_ApiRequest_StandaloneMicroserviceMsAdd::GetServiceName() const
{
	return TEXT("StandaloneMicroserviceMs");
}

FString UK2BeamNode_ApiRequest_StandaloneMicroserviceMsAdd::GetEndpointName() const
{
	return TEXT("Add");
}

UClass* UK2BeamNode_ApiRequest_StandaloneMicroserviceMsAdd::GetApiClass() const
{
	return UBeamStandaloneMicroserviceMsApi::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_StandaloneMicroserviceMsAdd::GetRequestClass() const
{
	return UStandaloneMicroserviceMsAddRequest::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_StandaloneMicroserviceMsAdd::GetResponseClass() const
{
	return UStandaloneMicroserviceMsAddResponse::StaticClass();
}

FString UK2BeamNode_ApiRequest_StandaloneMicroserviceMsAdd::GetRequestSuccessDelegateName() const
{
	return TEXT("OnStandaloneMicroserviceMsAddSuccess");
}

FString UK2BeamNode_ApiRequest_StandaloneMicroserviceMsAdd::GetRequestErrorDelegateName() const
{
	return TEXT("OnStandaloneMicroserviceMsAddError");
}

FString UK2BeamNode_ApiRequest_StandaloneMicroserviceMsAdd::GetRequestCompleteDelegateName() const
{
	return TEXT("OnStandaloneMicroserviceMsAddComplete");
}

#undef LOCTEXT_NAMESPACE
