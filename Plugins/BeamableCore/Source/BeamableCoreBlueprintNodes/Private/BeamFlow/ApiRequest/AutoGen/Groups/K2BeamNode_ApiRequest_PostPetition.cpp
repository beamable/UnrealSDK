

#include "BeamableCoreBlueprintNodes/Public/BeamFlow/ApiRequest/AutoGen/Groups/K2BeamNode_ApiRequest_PostPetition.h"

#include "BeamK2.h"

#include "BeamableCore/Public/AutoGen/SubSystems/BeamGroupsApi.h"
#include "BeamableCore/Public/AutoGen/SubSystems/Groups/PostPetitionRequest.h"
#include "BeamableCore/Public/AutoGen/CommonResponse.h"

#define LOCTEXT_NAMESPACE "K2BeamNode_ApiRequest_PostPetition"

using namespace BeamK2;

FName UK2BeamNode_ApiRequest_PostPetition::GetSelfFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamGroupsApi, GetSelf);
}

FName UK2BeamNode_ApiRequest_PostPetition::GetRequestFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamGroupsApi, PostPetition);
}

FName UK2BeamNode_ApiRequest_PostPetition::GetMakeFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UPostPetitionRequest, Make);
}

FString UK2BeamNode_ApiRequest_PostPetition::GetServiceName() const
{
	return TEXT("Groups");
}

FString UK2BeamNode_ApiRequest_PostPetition::GetEndpointName() const
{
	return TEXT("PostPetition");
}

UClass* UK2BeamNode_ApiRequest_PostPetition::GetApiClass() const
{
	return UBeamGroupsApi::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_PostPetition::GetRequestClass() const
{
	return UPostPetitionRequest::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_PostPetition::GetResponseClass() const
{
	return UCommonResponse::StaticClass();
}

FString UK2BeamNode_ApiRequest_PostPetition::GetRequestSuccessDelegateName() const
{
	return TEXT("OnPostPetitionSuccess");
}

FString UK2BeamNode_ApiRequest_PostPetition::GetRequestErrorDelegateName() const
{
	return TEXT("OnPostPetitionError");
}

FString UK2BeamNode_ApiRequest_PostPetition::GetRequestCompleteDelegateName() const
{
	return TEXT("OnPostPetitionComplete");
}

#undef LOCTEXT_NAMESPACE
