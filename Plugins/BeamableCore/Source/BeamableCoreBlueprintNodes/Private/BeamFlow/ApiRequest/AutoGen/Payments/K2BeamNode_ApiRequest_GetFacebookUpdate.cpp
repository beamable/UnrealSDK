

#include "BeamableCoreBlueprintNodes/Public/BeamFlow/ApiRequest/AutoGen/Payments/K2BeamNode_ApiRequest_GetFacebookUpdate.h"

#include "BeamK2.h"

#include "BeamableCore/Public/AutoGen/SubSystems/BeamPaymentsApi.h"
#include "BeamableCore/Public/AutoGen/SubSystems/Payments/GetFacebookUpdateRequest.h"
#include "Serialization/BeamPlainTextResponseBody.h"

#define LOCTEXT_NAMESPACE "K2BeamNode_ApiRequest_GetFacebookUpdate"

using namespace BeamK2;

FName UK2BeamNode_ApiRequest_GetFacebookUpdate::GetSelfFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamPaymentsApi, GetSelf);
}

FName UK2BeamNode_ApiRequest_GetFacebookUpdate::GetRequestFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamPaymentsApi, GetFacebookUpdate);
}

FName UK2BeamNode_ApiRequest_GetFacebookUpdate::GetMakeFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UGetFacebookUpdateRequest, Make);
}

FString UK2BeamNode_ApiRequest_GetFacebookUpdate::GetServiceName() const
{
	return TEXT("Payments");
}

FString UK2BeamNode_ApiRequest_GetFacebookUpdate::GetEndpointName() const
{
	return TEXT("GetFacebookUpdate");
}

UClass* UK2BeamNode_ApiRequest_GetFacebookUpdate::GetApiClass() const
{
	return UBeamPaymentsApi::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_GetFacebookUpdate::GetRequestClass() const
{
	return UGetFacebookUpdateRequest::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_GetFacebookUpdate::GetResponseClass() const
{
	return UBeamPlainTextResponseBody::StaticClass();
}

FString UK2BeamNode_ApiRequest_GetFacebookUpdate::GetRequestSuccessDelegateName() const
{
	return TEXT("OnGetFacebookUpdateSuccess");
}

FString UK2BeamNode_ApiRequest_GetFacebookUpdate::GetRequestErrorDelegateName() const
{
	return TEXT("OnGetFacebookUpdateError");
}

FString UK2BeamNode_ApiRequest_GetFacebookUpdate::GetRequestCompleteDelegateName() const
{
	return TEXT("OnGetFacebookUpdateComplete");
}

#undef LOCTEXT_NAMESPACE
