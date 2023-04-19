

#include "BeamableCoreBlueprintNodes/Public/BeamFlow/ApiRequest/AutoGen/Mail/K2BeamNode_ApiRequest_PostMail.h"

#include "BeamK2.h"

#include "BeamableCore/Public/AutoGen/SubSystems/BeamMailApi.h"
#include "BeamableCore/Public/AutoGen/SubSystems/Mail/PostMailRequest.h"
#include "BeamableCore/Public/AutoGen/SendMailResponse.h"

#define LOCTEXT_NAMESPACE "K2BeamNode_ApiRequest_PostMail"

using namespace BeamK2;

FName UK2BeamNode_ApiRequest_PostMail::GetSelfFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamMailApi, GetSelf);
}

FName UK2BeamNode_ApiRequest_PostMail::GetRequestFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamMailApi, PostMail);
}

FName UK2BeamNode_ApiRequest_PostMail::GetMakeFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UPostMailRequest, Make);
}

FString UK2BeamNode_ApiRequest_PostMail::GetServiceName() const
{
	return TEXT("Mail");
}

FString UK2BeamNode_ApiRequest_PostMail::GetEndpointName() const
{
	return TEXT("PostMail");
}

UClass* UK2BeamNode_ApiRequest_PostMail::GetApiClass() const
{
	return UBeamMailApi::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_PostMail::GetRequestClass() const
{
	return UPostMailRequest::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_PostMail::GetResponseClass() const
{
	return USendMailResponse::StaticClass();
}

FString UK2BeamNode_ApiRequest_PostMail::GetRequestSuccessDelegateName() const
{
	return TEXT("OnPostMailSuccess");
}

FString UK2BeamNode_ApiRequest_PostMail::GetRequestErrorDelegateName() const
{
	return TEXT("OnPostMailError");
}

FString UK2BeamNode_ApiRequest_PostMail::GetRequestCompleteDelegateName() const
{
	return TEXT("OnPostMailComplete");
}

#undef LOCTEXT_NAMESPACE
