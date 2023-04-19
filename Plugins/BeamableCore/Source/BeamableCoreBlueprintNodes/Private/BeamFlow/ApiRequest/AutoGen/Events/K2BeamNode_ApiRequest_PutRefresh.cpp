

#include "BeamableCoreBlueprintNodes/Public/BeamFlow/ApiRequest/AutoGen/Events/K2BeamNode_ApiRequest_PutRefresh.h"

#include "BeamK2.h"

#include "BeamableCore/Public/AutoGen/SubSystems/BeamEventsApi.h"
#include "BeamableCore/Public/AutoGen/SubSystems/Events/PutRefreshRequest.h"
#include "BeamableCore/Public/AutoGen/CommonResponse.h"

#define LOCTEXT_NAMESPACE "K2BeamNode_ApiRequest_PutRefresh"

using namespace BeamK2;

FName UK2BeamNode_ApiRequest_PutRefresh::GetSelfFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamEventsApi, GetSelf);
}

FName UK2BeamNode_ApiRequest_PutRefresh::GetRequestFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamEventsApi, PutRefresh);
}

FName UK2BeamNode_ApiRequest_PutRefresh::GetMakeFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UPutRefreshRequest, Make);
}

FString UK2BeamNode_ApiRequest_PutRefresh::GetServiceName() const
{
	return TEXT("Events");
}

FString UK2BeamNode_ApiRequest_PutRefresh::GetEndpointName() const
{
	return TEXT("PutRefresh");
}

UClass* UK2BeamNode_ApiRequest_PutRefresh::GetApiClass() const
{
	return UBeamEventsApi::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_PutRefresh::GetRequestClass() const
{
	return UPutRefreshRequest::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_PutRefresh::GetResponseClass() const
{
	return UCommonResponse::StaticClass();
}

FString UK2BeamNode_ApiRequest_PutRefresh::GetRequestSuccessDelegateName() const
{
	return TEXT("OnPutRefreshSuccess");
}

FString UK2BeamNode_ApiRequest_PutRefresh::GetRequestErrorDelegateName() const
{
	return TEXT("OnPutRefreshError");
}

FString UK2BeamNode_ApiRequest_PutRefresh::GetRequestCompleteDelegateName() const
{
	return TEXT("OnPutRefreshComplete");
}

#undef LOCTEXT_NAMESPACE
