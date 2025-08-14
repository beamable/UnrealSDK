

#include "BeamableUnrealMicroserviceClientsBp/Public/AutoGen/MSPlayground/K2BeamNode_ApiRequest_MSPlaygroundTestArr.h"

#include "BeamK2.h"

#include "BeamableUnrealMicroserviceClients/Public/AutoGen/SubSystems/BeamMSPlaygroundApi.h"
#include "BeamableUnrealMicroserviceClients/Public/AutoGen/SubSystems/MSPlayground/MSPlaygroundTestArrRequest.h"
#include "BeamableUnrealMicroserviceClients/Public/AutoGen/MSPlaygroundTestArrResponse.h"

#define LOCTEXT_NAMESPACE "K2BeamNode_ApiRequest_MSPlaygroundTestArr"

using namespace BeamK2;

FName UK2BeamNode_ApiRequest_MSPlaygroundTestArr::GetSelfFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamMSPlaygroundApi, GetSelf);
}

FName UK2BeamNode_ApiRequest_MSPlaygroundTestArr::GetRequestFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamMSPlaygroundApi, TestArr);
}

FName UK2BeamNode_ApiRequest_MSPlaygroundTestArr::GetMakeFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UMSPlaygroundTestArrRequest, Make);
}

FString UK2BeamNode_ApiRequest_MSPlaygroundTestArr::GetServiceName() const
{
	return TEXT("MSPlayground");
}

FString UK2BeamNode_ApiRequest_MSPlaygroundTestArr::GetEndpointName() const
{
	return TEXT("TestArr");
}

UClass* UK2BeamNode_ApiRequest_MSPlaygroundTestArr::GetApiClass() const
{
	return UBeamMSPlaygroundApi::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_MSPlaygroundTestArr::GetRequestClass() const
{
	return UMSPlaygroundTestArrRequest::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_MSPlaygroundTestArr::GetResponseClass() const
{
	return UMSPlaygroundTestArrResponse::StaticClass();
}

FString UK2BeamNode_ApiRequest_MSPlaygroundTestArr::GetRequestSuccessDelegateName() const
{
	return TEXT("OnMSPlaygroundTestArrSuccess");
}

FString UK2BeamNode_ApiRequest_MSPlaygroundTestArr::GetRequestErrorDelegateName() const
{
	return TEXT("OnMSPlaygroundTestArrError");
}

FString UK2BeamNode_ApiRequest_MSPlaygroundTestArr::GetRequestCompleteDelegateName() const
{
	return TEXT("OnMSPlaygroundTestArrComplete");
}

#undef LOCTEXT_NAMESPACE
