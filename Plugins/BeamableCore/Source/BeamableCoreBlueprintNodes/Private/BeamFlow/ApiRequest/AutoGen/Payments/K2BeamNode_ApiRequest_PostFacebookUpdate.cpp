

#include "BeamableCoreBlueprintNodes/Public/BeamFlow/ApiRequest/AutoGen/Payments/K2BeamNode_ApiRequest_PostFacebookUpdate.h"

#include "BeamK2.h"

#include "BeamableCore/Public/AutoGen/SubSystems/BeamPaymentsApi.h"
#include "BeamableCore/Public/AutoGen/SubSystems/Payments/PostFacebookUpdateRequest.h"
#include "Serialization/BeamPlainTextResponseBody.h"

#define LOCTEXT_NAMESPACE "K2BeamNode_ApiRequest_PostFacebookUpdate"

using namespace BeamK2;

FName UK2BeamNode_ApiRequest_PostFacebookUpdate::GetSelfFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamPaymentsApi, GetSelf);
}

FName UK2BeamNode_ApiRequest_PostFacebookUpdate::GetRequestFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamPaymentsApi, PostFacebookUpdate);
}

FName UK2BeamNode_ApiRequest_PostFacebookUpdate::GetMakeFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UPostFacebookUpdateRequest, Make);
}

FString UK2BeamNode_ApiRequest_PostFacebookUpdate::GetServiceName() const
{
	return TEXT("Payments");
}

FString UK2BeamNode_ApiRequest_PostFacebookUpdate::GetEndpointName() const
{
	return TEXT("PostFacebookUpdate");
}

UClass* UK2BeamNode_ApiRequest_PostFacebookUpdate::GetApiClass() const
{
	return UBeamPaymentsApi::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_PostFacebookUpdate::GetRequestClass() const
{
	return UPostFacebookUpdateRequest::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_PostFacebookUpdate::GetResponseClass() const
{
	return UBeamPlainTextResponseBody::StaticClass();
}

FString UK2BeamNode_ApiRequest_PostFacebookUpdate::GetRequestSuccessDelegateName() const
{
	return TEXT("OnPostFacebookUpdateSuccess");
}

FString UK2BeamNode_ApiRequest_PostFacebookUpdate::GetRequestErrorDelegateName() const
{
	return TEXT("OnPostFacebookUpdateError");
}

FString UK2BeamNode_ApiRequest_PostFacebookUpdate::GetRequestCompleteDelegateName() const
{
	return TEXT("OnPostFacebookUpdateComplete");
}

#undef LOCTEXT_NAMESPACE
