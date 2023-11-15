

#include "BeamableUnrealBlueprintNodes\Public\AutoGen/MSPlaygroundMs/K2BeamNode_ApiRequest_MSPlaygroundMsAdd.h"

#include "BeamK2.h"

#include "BeamableUnreal\AutoGen/SubSystems/BeamMSPlaygroundMsApi.h"
#include "BeamableUnreal\AutoGen/SubSystems/MSPlaygroundMs/MSPlaygroundMsAddRequest.h"
#include "BeamableUnreal\AutoGen/MSPlaygroundMsAddResponse.h"

#define LOCTEXT_NAMESPACE "K2BeamNode_ApiRequest_MSPlaygroundMsAdd"

using namespace BeamK2;

FName UK2BeamNode_ApiRequest_MSPlaygroundMsAdd::GetSelfFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamMSPlaygroundMsApi, GetSelf);
}

FName UK2BeamNode_ApiRequest_MSPlaygroundMsAdd::GetRequestFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamMSPlaygroundMsApi, Add);
}

FName UK2BeamNode_ApiRequest_MSPlaygroundMsAdd::GetMakeFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UMSPlaygroundMsAddRequest, Make);
}

FString UK2BeamNode_ApiRequest_MSPlaygroundMsAdd::GetServiceName() const
{
	return TEXT("MSPlaygroundMs");
}

FString UK2BeamNode_ApiRequest_MSPlaygroundMsAdd::GetEndpointName() const
{
	return TEXT("Add");
}

UClass* UK2BeamNode_ApiRequest_MSPlaygroundMsAdd::GetApiClass() const
{
	return UBeamMSPlaygroundMsApi::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_MSPlaygroundMsAdd::GetRequestClass() const
{
	return UMSPlaygroundMsAddRequest::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_MSPlaygroundMsAdd::GetResponseClass() const
{
	return UMSPlaygroundMsAddResponse::StaticClass();
}

FString UK2BeamNode_ApiRequest_MSPlaygroundMsAdd::GetRequestSuccessDelegateName() const
{
	return TEXT("OnMSPlaygroundMsAddSuccess");
}

FString UK2BeamNode_ApiRequest_MSPlaygroundMsAdd::GetRequestErrorDelegateName() const
{
	return TEXT("OnMSPlaygroundMsAddError");
}

FString UK2BeamNode_ApiRequest_MSPlaygroundMsAdd::GetRequestCompleteDelegateName() const
{
	return TEXT("OnMSPlaygroundMsAddComplete");
}

#undef LOCTEXT_NAMESPACE
