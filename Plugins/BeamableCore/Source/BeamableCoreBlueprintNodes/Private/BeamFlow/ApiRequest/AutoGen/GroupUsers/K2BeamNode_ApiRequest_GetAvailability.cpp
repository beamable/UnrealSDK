

#include "BeamableCoreBlueprintNodes/Public/BeamFlow/ApiRequest/AutoGen/GroupUsers/K2BeamNode_ApiRequest_GetAvailability.h"

#include "BeamK2.h"

#include "BeamableCore/Public/AutoGen/SubSystems/BeamGroupUsersApi.h"
#include "BeamableCore/Public/AutoGen/SubSystems/GroupUsers/GetAvailabilityRequest.h"
#include "BeamableCore/Public/AutoGen/AvailabilityResponse.h"

#define LOCTEXT_NAMESPACE "K2BeamNode_ApiRequest_GetAvailability"

using namespace BeamK2;

FName UK2BeamNode_ApiRequest_GetAvailability::GetSelfFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamGroupUsersApi, GetSelf);
}

FName UK2BeamNode_ApiRequest_GetAvailability::GetRequestFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamGroupUsersApi, GetAvailability);
}

FName UK2BeamNode_ApiRequest_GetAvailability::GetMakeFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UGetAvailabilityRequest, Make);
}

FString UK2BeamNode_ApiRequest_GetAvailability::GetServiceName() const
{
	return TEXT("GroupUsers");
}

FString UK2BeamNode_ApiRequest_GetAvailability::GetEndpointName() const
{
	return TEXT("GetAvailability");
}

UClass* UK2BeamNode_ApiRequest_GetAvailability::GetApiClass() const
{
	return UBeamGroupUsersApi::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_GetAvailability::GetRequestClass() const
{
	return UGetAvailabilityRequest::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_GetAvailability::GetResponseClass() const
{
	return UAvailabilityResponse::StaticClass();
}

FString UK2BeamNode_ApiRequest_GetAvailability::GetRequestSuccessDelegateName() const
{
	return TEXT("OnGetAvailabilitySuccess");
}

FString UK2BeamNode_ApiRequest_GetAvailability::GetRequestErrorDelegateName() const
{
	return TEXT("OnGetAvailabilityError");
}

FString UK2BeamNode_ApiRequest_GetAvailability::GetRequestCompleteDelegateName() const
{
	return TEXT("OnGetAvailabilityComplete");
}

#undef LOCTEXT_NAMESPACE
