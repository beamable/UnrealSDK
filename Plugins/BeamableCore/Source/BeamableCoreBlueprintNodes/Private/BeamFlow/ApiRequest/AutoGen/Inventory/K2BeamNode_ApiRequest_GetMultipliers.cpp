

#include "BeamableCoreBlueprintNodes/Public/BeamFlow/ApiRequest/AutoGen/Inventory/K2BeamNode_ApiRequest_GetMultipliers.h"

#include "BeamK2.h"

#include "BeamableCore/Public/AutoGen/SubSystems/BeamInventoryApi.h"
#include "BeamableCore/Public/AutoGen/SubSystems/Inventory/GetMultipliersRequest.h"
#include "BeamableCore/Public/AutoGen/MultipliersGetResponse.h"

#define LOCTEXT_NAMESPACE "K2BeamNode_ApiRequest_GetMultipliers"

using namespace BeamK2;

FName UK2BeamNode_ApiRequest_GetMultipliers::GetSelfFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamInventoryApi, GetSelf);
}

FName UK2BeamNode_ApiRequest_GetMultipliers::GetRequestFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamInventoryApi, GetMultipliers);
}

FName UK2BeamNode_ApiRequest_GetMultipliers::GetMakeFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UGetMultipliersRequest, Make);
}

FString UK2BeamNode_ApiRequest_GetMultipliers::GetServiceName() const
{
	return TEXT("Inventory");
}

FString UK2BeamNode_ApiRequest_GetMultipliers::GetEndpointName() const
{
	return TEXT("GetMultipliers");
}

UClass* UK2BeamNode_ApiRequest_GetMultipliers::GetApiClass() const
{
	return UBeamInventoryApi::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_GetMultipliers::GetRequestClass() const
{
	return UGetMultipliersRequest::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_GetMultipliers::GetResponseClass() const
{
	return UMultipliersGetResponse::StaticClass();
}

FString UK2BeamNode_ApiRequest_GetMultipliers::GetRequestSuccessDelegateName() const
{
	return TEXT("OnGetMultipliersSuccess");
}

FString UK2BeamNode_ApiRequest_GetMultipliers::GetRequestErrorDelegateName() const
{
	return TEXT("OnGetMultipliersError");
}

FString UK2BeamNode_ApiRequest_GetMultipliers::GetRequestCompleteDelegateName() const
{
	return TEXT("OnGetMultipliersComplete");
}

#undef LOCTEXT_NAMESPACE
