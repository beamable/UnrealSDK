

#include "BeamableCoreBlueprintNodes/Public/BeamFlow/ApiRequest/AutoGen/Mail/K2BeamNode_ApiRequest_PutAcceptMany.h"

#include "BeamK2.h"

#include "BeamableCore/Public/AutoGen/SubSystems/BeamMailApi.h"
#include "BeamableCore/Public/AutoGen/SubSystems/Mail/PutAcceptManyRequest.h"
#include "BeamableCore/Public/AutoGen/MailSuccessResponse.h"

#define LOCTEXT_NAMESPACE "K2BeamNode_ApiRequest_PutAcceptMany"

using namespace BeamK2;

FName UK2BeamNode_ApiRequest_PutAcceptMany::GetSelfFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamMailApi, GetSelf);
}

FName UK2BeamNode_ApiRequest_PutAcceptMany::GetRequestFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamMailApi, PutAcceptMany);
}

FName UK2BeamNode_ApiRequest_PutAcceptMany::GetMakeFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UPutAcceptManyRequest, Make);
}

FString UK2BeamNode_ApiRequest_PutAcceptMany::GetServiceName() const
{
	return TEXT("Mail");
}

FString UK2BeamNode_ApiRequest_PutAcceptMany::GetEndpointName() const
{
	return TEXT("PutAcceptMany");
}

UClass* UK2BeamNode_ApiRequest_PutAcceptMany::GetApiClass() const
{
	return UBeamMailApi::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_PutAcceptMany::GetRequestClass() const
{
	return UPutAcceptManyRequest::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_PutAcceptMany::GetResponseClass() const
{
	return UMailSuccessResponse::StaticClass();
}

FString UK2BeamNode_ApiRequest_PutAcceptMany::GetRequestSuccessDelegateName() const
{
	return TEXT("OnPutAcceptManySuccess");
}

FString UK2BeamNode_ApiRequest_PutAcceptMany::GetRequestErrorDelegateName() const
{
	return TEXT("OnPutAcceptManyError");
}

FString UK2BeamNode_ApiRequest_PutAcceptMany::GetRequestCompleteDelegateName() const
{
	return TEXT("OnPutAcceptManyComplete");
}

#undef LOCTEXT_NAMESPACE
