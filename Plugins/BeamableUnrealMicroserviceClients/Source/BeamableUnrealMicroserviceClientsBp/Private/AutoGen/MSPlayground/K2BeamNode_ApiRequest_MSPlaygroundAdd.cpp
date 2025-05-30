

#include "BeamableUnrealMicroserviceClientsBp/Public/AutoGen/MSPlayground/K2BeamNode_ApiRequest_MSPlaygroundAdd.h"

#include "BeamK2.h"

#include "BeamableUnrealMicroserviceClients/Public/AutoGen/SubSystems/BeamMSPlaygroundApi.h"
#include "BeamableUnrealMicroserviceClients/Public/AutoGen/SubSystems/MSPlayground/MSPlaygroundAddRequest.h"
#include "BeamableUnrealMicroserviceClients/Public/AutoGen/MSPlaygroundAddResponse.h"

#define LOCTEXT_NAMESPACE "K2BeamNode_ApiRequest_MSPlaygroundAdd"

using namespace BeamK2;

FName UK2BeamNode_ApiRequest_MSPlaygroundAdd::GetSelfFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamMSPlaygroundApi, GetSelf);
}

FName UK2BeamNode_ApiRequest_MSPlaygroundAdd::GetRequestFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamMSPlaygroundApi, Add);
}

FName UK2BeamNode_ApiRequest_MSPlaygroundAdd::GetMakeFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UMSPlaygroundAddRequest, Make);
}

FString UK2BeamNode_ApiRequest_MSPlaygroundAdd::GetServiceName() const
{
	return TEXT("MSPlayground");
}

FString UK2BeamNode_ApiRequest_MSPlaygroundAdd::GetEndpointName() const
{
	return TEXT("Add");
}

UClass* UK2BeamNode_ApiRequest_MSPlaygroundAdd::GetApiClass() const
{
	return UBeamMSPlaygroundApi::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_MSPlaygroundAdd::GetRequestClass() const
{
	return UMSPlaygroundAddRequest::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_MSPlaygroundAdd::GetResponseClass() const
{
	return UMSPlaygroundAddResponse::StaticClass();
}

FString UK2BeamNode_ApiRequest_MSPlaygroundAdd::GetRequestSuccessDelegateName() const
{
	return TEXT("OnMSPlaygroundAddSuccess");
}

FString UK2BeamNode_ApiRequest_MSPlaygroundAdd::GetRequestErrorDelegateName() const
{
	return TEXT("OnMSPlaygroundAddError");
}

FString UK2BeamNode_ApiRequest_MSPlaygroundAdd::GetRequestCompleteDelegateName() const
{
	return TEXT("OnMSPlaygroundAddComplete");
}

#undef LOCTEXT_NAMESPACE
