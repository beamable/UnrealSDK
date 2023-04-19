

#include "BeamableCoreBlueprintNodes/Public/BeamFlow/ApiRequest/AutoGen/Events/K2BeamNode_ApiRequest_PutContent.h"

#include "BeamK2.h"

#include "BeamableCore/Public/AutoGen/SubSystems/BeamEventsApi.h"
#include "BeamableCore/Public/AutoGen/SubSystems/Events/PutContentRequest.h"
#include "BeamableCore/Public/AutoGen/CommonResponse.h"

#define LOCTEXT_NAMESPACE "K2BeamNode_ApiRequest_PutContent"

using namespace BeamK2;

FName UK2BeamNode_ApiRequest_PutContent::GetSelfFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamEventsApi, GetSelf);
}

FName UK2BeamNode_ApiRequest_PutContent::GetRequestFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamEventsApi, PutContent);
}

FName UK2BeamNode_ApiRequest_PutContent::GetMakeFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UPutContentRequest, Make);
}

FString UK2BeamNode_ApiRequest_PutContent::GetServiceName() const
{
	return TEXT("Events");
}

FString UK2BeamNode_ApiRequest_PutContent::GetEndpointName() const
{
	return TEXT("PutContent");
}

UClass* UK2BeamNode_ApiRequest_PutContent::GetApiClass() const
{
	return UBeamEventsApi::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_PutContent::GetRequestClass() const
{
	return UPutContentRequest::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_PutContent::GetResponseClass() const
{
	return UCommonResponse::StaticClass();
}

FString UK2BeamNode_ApiRequest_PutContent::GetRequestSuccessDelegateName() const
{
	return TEXT("OnPutContentSuccess");
}

FString UK2BeamNode_ApiRequest_PutContent::GetRequestErrorDelegateName() const
{
	return TEXT("OnPutContentError");
}

FString UK2BeamNode_ApiRequest_PutContent::GetRequestCompleteDelegateName() const
{
	return TEXT("OnPutContentComplete");
}

#undef LOCTEXT_NAMESPACE
