

#include "BeamableCoreBlueprintNodes/Public/BeamFlow/ApiRequest/AutoGen/Inventory/K2BeamNode_ApiRequest_PutProxyReload.h"

#include "BeamK2.h"

#include "BeamableCore/Public/AutoGen/SubSystems/BeamInventoryApi.h"
#include "BeamableCore/Public/AutoGen/SubSystems/Inventory/PutProxyReloadRequest.h"
#include "BeamableCore/Public/AutoGen/CommonResponse.h"

#define LOCTEXT_NAMESPACE "K2BeamNode_ApiRequest_PutProxyReload"

using namespace BeamK2;

FName UK2BeamNode_ApiRequest_PutProxyReload::GetSelfFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamInventoryApi, GetSelf);
}

FName UK2BeamNode_ApiRequest_PutProxyReload::GetRequestFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamInventoryApi, PutProxyReload);
}

FName UK2BeamNode_ApiRequest_PutProxyReload::GetMakeFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UPutProxyReloadRequest, Make);
}

FString UK2BeamNode_ApiRequest_PutProxyReload::GetServiceName() const
{
	return TEXT("Inventory");
}

FString UK2BeamNode_ApiRequest_PutProxyReload::GetEndpointName() const
{
	return TEXT("PutProxyReload");
}

UClass* UK2BeamNode_ApiRequest_PutProxyReload::GetApiClass() const
{
	return UBeamInventoryApi::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_PutProxyReload::GetRequestClass() const
{
	return UPutProxyReloadRequest::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_PutProxyReload::GetResponseClass() const
{
	return UCommonResponse::StaticClass();
}

FString UK2BeamNode_ApiRequest_PutProxyReload::GetRequestSuccessDelegateName() const
{
	return TEXT("OnPutProxyReloadSuccess");
}

FString UK2BeamNode_ApiRequest_PutProxyReload::GetRequestErrorDelegateName() const
{
	return TEXT("OnPutProxyReloadError");
}

FString UK2BeamNode_ApiRequest_PutProxyReload::GetRequestCompleteDelegateName() const
{
	return TEXT("OnPutProxyReloadComplete");
}

#undef LOCTEXT_NAMESPACE
