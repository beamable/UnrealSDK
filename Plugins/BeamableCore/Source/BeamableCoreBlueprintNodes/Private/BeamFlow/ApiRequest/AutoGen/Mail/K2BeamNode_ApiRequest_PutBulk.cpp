

#include "BeamableCoreBlueprintNodes/Public/BeamFlow/ApiRequest/AutoGen/Mail/K2BeamNode_ApiRequest_PutBulk.h"

#include "BeamK2.h"

#include "BeamableCore/Public/AutoGen/SubSystems/BeamMailApi.h"
#include "BeamableCore/Public/AutoGen/SubSystems/Mail/PutBulkRequest.h"
#include "BeamableCore/Public/AutoGen/MailSuccessResponse.h"

#define LOCTEXT_NAMESPACE "K2BeamNode_ApiRequest_PutBulk"

using namespace BeamK2;

FName UK2BeamNode_ApiRequest_PutBulk::GetSelfFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamMailApi, GetSelf);
}

FName UK2BeamNode_ApiRequest_PutBulk::GetRequestFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamMailApi, PutBulk);
}

FName UK2BeamNode_ApiRequest_PutBulk::GetMakeFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UPutBulkRequest, Make);
}

FString UK2BeamNode_ApiRequest_PutBulk::GetServiceName() const
{
	return TEXT("Mail");
}

FString UK2BeamNode_ApiRequest_PutBulk::GetEndpointName() const
{
	return TEXT("PutBulk");
}

UClass* UK2BeamNode_ApiRequest_PutBulk::GetApiClass() const
{
	return UBeamMailApi::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_PutBulk::GetRequestClass() const
{
	return UPutBulkRequest::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_PutBulk::GetResponseClass() const
{
	return UMailSuccessResponse::StaticClass();
}

FString UK2BeamNode_ApiRequest_PutBulk::GetRequestSuccessDelegateName() const
{
	return TEXT("OnPutBulkSuccess");
}

FString UK2BeamNode_ApiRequest_PutBulk::GetRequestErrorDelegateName() const
{
	return TEXT("OnPutBulkError");
}

FString UK2BeamNode_ApiRequest_PutBulk::GetRequestCompleteDelegateName() const
{
	return TEXT("OnPutBulkComplete");
}

#undef LOCTEXT_NAMESPACE
