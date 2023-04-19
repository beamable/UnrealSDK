

#include "BeamableCoreBlueprintNodes/Public/BeamFlow/ApiRequest/AutoGen/Mail/K2BeamNode_ApiRequest_GetDetail.h"

#include "BeamK2.h"

#include "BeamableCore/Public/AutoGen/SubSystems/BeamMailApi.h"
#include "BeamableCore/Public/AutoGen/SubSystems/Mail/GetDetailRequest.h"
#include "BeamableCore/Public/AutoGen/MailResponse.h"

#define LOCTEXT_NAMESPACE "K2BeamNode_ApiRequest_GetDetail"

using namespace BeamK2;

FName UK2BeamNode_ApiRequest_GetDetail::GetSelfFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamMailApi, GetSelf);
}

FName UK2BeamNode_ApiRequest_GetDetail::GetRequestFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamMailApi, GetDetail);
}

FName UK2BeamNode_ApiRequest_GetDetail::GetMakeFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UGetDetailRequest, Make);
}

FString UK2BeamNode_ApiRequest_GetDetail::GetServiceName() const
{
	return TEXT("Mail");
}

FString UK2BeamNode_ApiRequest_GetDetail::GetEndpointName() const
{
	return TEXT("GetDetail");
}

UClass* UK2BeamNode_ApiRequest_GetDetail::GetApiClass() const
{
	return UBeamMailApi::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_GetDetail::GetRequestClass() const
{
	return UGetDetailRequest::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_GetDetail::GetResponseClass() const
{
	return UMailResponse::StaticClass();
}

FString UK2BeamNode_ApiRequest_GetDetail::GetRequestSuccessDelegateName() const
{
	return TEXT("OnGetDetailSuccess");
}

FString UK2BeamNode_ApiRequest_GetDetail::GetRequestErrorDelegateName() const
{
	return TEXT("OnGetDetailError");
}

FString UK2BeamNode_ApiRequest_GetDetail::GetRequestCompleteDelegateName() const
{
	return TEXT("OnGetDetailComplete");
}

#undef LOCTEXT_NAMESPACE
