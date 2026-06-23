

#include "BeamableUnrealMicroserviceClientsBp/Public/AutoGen/BeamFarmMs/K2BeamNode_ApiRequest_BeamFarmMsGetGroundItems.h"

#include "BeamK2.h"

#include "BeamableUnrealMicroserviceClients/Public/AutoGen/SubSystems/BeamBeamFarmMsApi.h"
#include "BeamableUnrealMicroserviceClients/Public/AutoGen/SubSystems/BeamFarmMs/BeamFarmMsGetGroundItemsRequest.h"
#include "BeamableUnrealMicroserviceClients/Public/AutoGen/GetGroundItemsResult.h"

#define LOCTEXT_NAMESPACE "K2BeamNode_ApiRequest_BeamFarmMsGetGroundItems"

using namespace BeamK2;

FName UK2BeamNode_ApiRequest_BeamFarmMsGetGroundItems::GetSelfFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamBeamFarmMsApi, GetSelf);
}

FName UK2BeamNode_ApiRequest_BeamFarmMsGetGroundItems::GetRequestFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamBeamFarmMsApi, GetGroundItems);
}

FName UK2BeamNode_ApiRequest_BeamFarmMsGetGroundItems::GetMakeFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamFarmMsGetGroundItemsRequest, Make);
}

FString UK2BeamNode_ApiRequest_BeamFarmMsGetGroundItems::GetServiceName() const
{
	return TEXT("BeamFarmMs");
}

FString UK2BeamNode_ApiRequest_BeamFarmMsGetGroundItems::GetEndpointName() const
{
	return TEXT("GetGroundItems");
}

UClass* UK2BeamNode_ApiRequest_BeamFarmMsGetGroundItems::GetApiClass() const
{
	return UBeamBeamFarmMsApi::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_BeamFarmMsGetGroundItems::GetRequestClass() const
{
	return UBeamFarmMsGetGroundItemsRequest::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_BeamFarmMsGetGroundItems::GetResponseClass() const
{
	return UGetGroundItemsResult::StaticClass();
}

FString UK2BeamNode_ApiRequest_BeamFarmMsGetGroundItems::GetRequestSuccessDelegateName() const
{
	return TEXT("OnBeamFarmMsGetGroundItemsSuccess");
}

FString UK2BeamNode_ApiRequest_BeamFarmMsGetGroundItems::GetRequestErrorDelegateName() const
{
	return TEXT("OnBeamFarmMsGetGroundItemsError");
}

FString UK2BeamNode_ApiRequest_BeamFarmMsGetGroundItems::GetRequestCompleteDelegateName() const
{
	return TEXT("OnBeamFarmMsGetGroundItemsComplete");
}

#undef LOCTEXT_NAMESPACE
