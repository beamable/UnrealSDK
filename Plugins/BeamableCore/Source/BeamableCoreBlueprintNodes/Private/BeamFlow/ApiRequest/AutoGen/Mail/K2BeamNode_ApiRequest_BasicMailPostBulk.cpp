

#include "BeamableCoreBlueprintNodes/Public/BeamFlow/ApiRequest/AutoGen/Mail/K2BeamNode_ApiRequest_BasicMailPostBulk.h"

#include "BeamK2.h"

#include "BeamableCore/Public/AutoGen/SubSystems/BeamMailApi.h"
#include "BeamableCore/Public/AutoGen/SubSystems/Mail/BasicMailPostBulkRequest.h"
#include "BeamableCore/Public/AutoGen/MailSuccessResponse.h"

#define LOCTEXT_NAMESPACE "K2BeamNode_ApiRequest_BasicMailPostBulk"

using namespace BeamK2;

FName UK2BeamNode_ApiRequest_BasicMailPostBulk::GetSelfFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamMailApi, GetSelf);
}

FName UK2BeamNode_ApiRequest_BasicMailPostBulk::GetRequestFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamMailApi, BasicMailPostBulk);
}

FName UK2BeamNode_ApiRequest_BasicMailPostBulk::GetMakeFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBasicMailPostBulkRequest, Make);
}

FString UK2BeamNode_ApiRequest_BasicMailPostBulk::GetServiceName() const
{
	return TEXT("Mail");
}

FString UK2BeamNode_ApiRequest_BasicMailPostBulk::GetEndpointName() const
{
	return TEXT("BasicMailPostBulk");
}

UClass* UK2BeamNode_ApiRequest_BasicMailPostBulk::GetApiClass() const
{
	return UBeamMailApi::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_BasicMailPostBulk::GetRequestClass() const
{
	return UBasicMailPostBulkRequest::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_BasicMailPostBulk::GetResponseClass() const
{
	return UMailSuccessResponse::StaticClass();
}

FString UK2BeamNode_ApiRequest_BasicMailPostBulk::GetRequestSuccessDelegateName() const
{
	return TEXT("OnBasicMailPostBulkSuccess");
}

FString UK2BeamNode_ApiRequest_BasicMailPostBulk::GetRequestErrorDelegateName() const
{
	return TEXT("OnBasicMailPostBulkError");
}

FString UK2BeamNode_ApiRequest_BasicMailPostBulk::GetRequestCompleteDelegateName() const
{
	return TEXT("OnBasicMailPostBulkComplete");
}

#undef LOCTEXT_NAMESPACE
