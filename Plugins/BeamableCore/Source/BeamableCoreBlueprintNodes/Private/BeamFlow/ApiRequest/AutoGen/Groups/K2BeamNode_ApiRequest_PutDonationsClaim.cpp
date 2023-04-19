

#include "BeamableCoreBlueprintNodes/Public/BeamFlow/ApiRequest/AutoGen/Groups/K2BeamNode_ApiRequest_PutDonationsClaim.h"

#include "BeamK2.h"

#include "BeamableCore/Public/AutoGen/SubSystems/BeamGroupsApi.h"
#include "BeamableCore/Public/AutoGen/SubSystems/Groups/PutDonationsClaimRequest.h"
#include "BeamableCore/Public/AutoGen/EmptyResponse.h"

#define LOCTEXT_NAMESPACE "K2BeamNode_ApiRequest_PutDonationsClaim"

using namespace BeamK2;

FName UK2BeamNode_ApiRequest_PutDonationsClaim::GetSelfFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamGroupsApi, GetSelf);
}

FName UK2BeamNode_ApiRequest_PutDonationsClaim::GetRequestFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamGroupsApi, PutDonationsClaim);
}

FName UK2BeamNode_ApiRequest_PutDonationsClaim::GetMakeFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UPutDonationsClaimRequest, Make);
}

FString UK2BeamNode_ApiRequest_PutDonationsClaim::GetServiceName() const
{
	return TEXT("Groups");
}

FString UK2BeamNode_ApiRequest_PutDonationsClaim::GetEndpointName() const
{
	return TEXT("PutDonationsClaim");
}

UClass* UK2BeamNode_ApiRequest_PutDonationsClaim::GetApiClass() const
{
	return UBeamGroupsApi::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_PutDonationsClaim::GetRequestClass() const
{
	return UPutDonationsClaimRequest::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_PutDonationsClaim::GetResponseClass() const
{
	return UEmptyResponse::StaticClass();
}

FString UK2BeamNode_ApiRequest_PutDonationsClaim::GetRequestSuccessDelegateName() const
{
	return TEXT("OnPutDonationsClaimSuccess");
}

FString UK2BeamNode_ApiRequest_PutDonationsClaim::GetRequestErrorDelegateName() const
{
	return TEXT("OnPutDonationsClaimError");
}

FString UK2BeamNode_ApiRequest_PutDonationsClaim::GetRequestCompleteDelegateName() const
{
	return TEXT("OnPutDonationsClaimComplete");
}

#undef LOCTEXT_NAMESPACE
