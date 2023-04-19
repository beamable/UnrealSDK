

#include "BeamableCoreBlueprintNodes/Public/BeamFlow/ApiRequest/AutoGen/Inventory/K2BeamNode_ApiRequest_PutPreview.h"

#include "BeamK2.h"

#include "BeamableCore/Public/AutoGen/SubSystems/BeamInventoryApi.h"
#include "BeamableCore/Public/AutoGen/SubSystems/Inventory/PutPreviewRequest.h"
#include "BeamableCore/Public/AutoGen/PreviewVipBonusResponse.h"

#define LOCTEXT_NAMESPACE "K2BeamNode_ApiRequest_PutPreview"

using namespace BeamK2;

FName UK2BeamNode_ApiRequest_PutPreview::GetSelfFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamInventoryApi, GetSelf);
}

FName UK2BeamNode_ApiRequest_PutPreview::GetRequestFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamInventoryApi, PutPreview);
}

FName UK2BeamNode_ApiRequest_PutPreview::GetMakeFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UPutPreviewRequest, Make);
}

FString UK2BeamNode_ApiRequest_PutPreview::GetServiceName() const
{
	return TEXT("Inventory");
}

FString UK2BeamNode_ApiRequest_PutPreview::GetEndpointName() const
{
	return TEXT("PutPreview");
}

UClass* UK2BeamNode_ApiRequest_PutPreview::GetApiClass() const
{
	return UBeamInventoryApi::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_PutPreview::GetRequestClass() const
{
	return UPutPreviewRequest::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_PutPreview::GetResponseClass() const
{
	return UPreviewVipBonusResponse::StaticClass();
}

FString UK2BeamNode_ApiRequest_PutPreview::GetRequestSuccessDelegateName() const
{
	return TEXT("OnPutPreviewSuccess");
}

FString UK2BeamNode_ApiRequest_PutPreview::GetRequestErrorDelegateName() const
{
	return TEXT("OnPutPreviewError");
}

FString UK2BeamNode_ApiRequest_PutPreview::GetRequestCompleteDelegateName() const
{
	return TEXT("OnPutPreviewComplete");
}

#undef LOCTEXT_NAMESPACE
