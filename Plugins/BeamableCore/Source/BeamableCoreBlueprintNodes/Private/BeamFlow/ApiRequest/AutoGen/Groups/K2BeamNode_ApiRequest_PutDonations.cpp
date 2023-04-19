

#include "BeamableCoreBlueprintNodes/Public/BeamFlow/ApiRequest/AutoGen/Groups/K2BeamNode_ApiRequest_PutDonations.h"

#include "BeamK2.h"

#include "BeamableCore/Public/AutoGen/SubSystems/BeamGroupsApi.h"
#include "BeamableCore/Public/AutoGen/SubSystems/Groups/PutDonationsRequest.h"
#include "BeamableCore/Public/AutoGen/EmptyResponse.h"

#define LOCTEXT_NAMESPACE "K2BeamNode_ApiRequest_PutDonations"

using namespace BeamK2;

FName UK2BeamNode_ApiRequest_PutDonations::GetSelfFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamGroupsApi, GetSelf);
}

FName UK2BeamNode_ApiRequest_PutDonations::GetRequestFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamGroupsApi, PutDonations);
}

FName UK2BeamNode_ApiRequest_PutDonations::GetMakeFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UPutDonationsRequest, Make);
}

FString UK2BeamNode_ApiRequest_PutDonations::GetServiceName() const
{
	return TEXT("Groups");
}

FString UK2BeamNode_ApiRequest_PutDonations::GetEndpointName() const
{
	return TEXT("PutDonations");
}

UClass* UK2BeamNode_ApiRequest_PutDonations::GetApiClass() const
{
	return UBeamGroupsApi::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_PutDonations::GetRequestClass() const
{
	return UPutDonationsRequest::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_PutDonations::GetResponseClass() const
{
	return UEmptyResponse::StaticClass();
}

FString UK2BeamNode_ApiRequest_PutDonations::GetRequestSuccessDelegateName() const
{
	return TEXT("OnPutDonationsSuccess");
}

FString UK2BeamNode_ApiRequest_PutDonations::GetRequestErrorDelegateName() const
{
	return TEXT("OnPutDonationsError");
}

FString UK2BeamNode_ApiRequest_PutDonations::GetRequestCompleteDelegateName() const
{
	return TEXT("OnPutDonationsComplete");
}

#undef LOCTEXT_NAMESPACE
