

#include "BeamableCoreBlueprintNodes/Public/BeamFlow/ApiRequest/AutoGen/Realms/K2BeamNode_ApiRequest_PostProjectBeamable.h"

#include "BeamK2.h"

#include "BeamableCore/Public/AutoGen/SubSystems/BeamRealmsApi.h"
#include "BeamableCore/Public/AutoGen/SubSystems/Realms/PostProjectBeamableRequest.h"
#include "BeamableCore/Public/AutoGen/CommonResponse.h"

#define LOCTEXT_NAMESPACE "K2BeamNode_ApiRequest_PostProjectBeamable"

using namespace BeamK2;

FName UK2BeamNode_ApiRequest_PostProjectBeamable::GetSelfFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamRealmsApi, GetSelf);
}

FName UK2BeamNode_ApiRequest_PostProjectBeamable::GetRequestFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamRealmsApi, PostProjectBeamable);
}

FName UK2BeamNode_ApiRequest_PostProjectBeamable::GetMakeFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UPostProjectBeamableRequest, Make);
}

FString UK2BeamNode_ApiRequest_PostProjectBeamable::GetServiceName() const
{
	return TEXT("Realms");
}

FString UK2BeamNode_ApiRequest_PostProjectBeamable::GetEndpointName() const
{
	return TEXT("PostProjectBeamable");
}

UClass* UK2BeamNode_ApiRequest_PostProjectBeamable::GetApiClass() const
{
	return UBeamRealmsApi::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_PostProjectBeamable::GetRequestClass() const
{
	return UPostProjectBeamableRequest::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_PostProjectBeamable::GetResponseClass() const
{
	return UCommonResponse::StaticClass();
}

FString UK2BeamNode_ApiRequest_PostProjectBeamable::GetRequestSuccessDelegateName() const
{
	return TEXT("OnPostProjectBeamableSuccess");
}

FString UK2BeamNode_ApiRequest_PostProjectBeamable::GetRequestErrorDelegateName() const
{
	return TEXT("OnPostProjectBeamableError");
}

FString UK2BeamNode_ApiRequest_PostProjectBeamable::GetRequestCompleteDelegateName() const
{
	return TEXT("OnPostProjectBeamableComplete");
}

#undef LOCTEXT_NAMESPACE
