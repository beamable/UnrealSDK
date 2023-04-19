

#include "BeamableCoreBlueprintNodes/Public/BeamFlow/ApiRequest/AutoGen/Groups/K2BeamNode_ApiRequest_PostDonations.h"

#include "BeamK2.h"

#include "BeamableCore/Public/AutoGen/SubSystems/BeamGroupsApi.h"
#include "BeamableCore/Public/AutoGen/SubSystems/Groups/PostDonationsRequest.h"
#include "BeamableCore/Public/AutoGen/EmptyResponse.h"

#define LOCTEXT_NAMESPACE "K2BeamNode_ApiRequest_PostDonations"

using namespace BeamK2;

FName UK2BeamNode_ApiRequest_PostDonations::GetSelfFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamGroupsApi, GetSelf);
}

FName UK2BeamNode_ApiRequest_PostDonations::GetRequestFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamGroupsApi, PostDonations);
}

FName UK2BeamNode_ApiRequest_PostDonations::GetMakeFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UPostDonationsRequest, Make);
}

FString UK2BeamNode_ApiRequest_PostDonations::GetServiceName() const
{
	return TEXT("Groups");
}

FString UK2BeamNode_ApiRequest_PostDonations::GetEndpointName() const
{
	return TEXT("PostDonations");
}

UClass* UK2BeamNode_ApiRequest_PostDonations::GetApiClass() const
{
	return UBeamGroupsApi::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_PostDonations::GetRequestClass() const
{
	return UPostDonationsRequest::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_PostDonations::GetResponseClass() const
{
	return UEmptyResponse::StaticClass();
}

FString UK2BeamNode_ApiRequest_PostDonations::GetRequestSuccessDelegateName() const
{
	return TEXT("OnPostDonationsSuccess");
}

FString UK2BeamNode_ApiRequest_PostDonations::GetRequestErrorDelegateName() const
{
	return TEXT("OnPostDonationsError");
}

FString UK2BeamNode_ApiRequest_PostDonations::GetRequestCompleteDelegateName() const
{
	return TEXT("OnPostDonationsComplete");
}

#undef LOCTEXT_NAMESPACE
