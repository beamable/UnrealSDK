

#include "BeamableCoreBlueprintNodes/Public/BeamFlow/ApiRequest/AutoGen/BeamoOtel/K2BeamNode_ApiRequest_PostOtelViews.h"

#include "BeamK2.h"

#include "BeamableCore/Public/AutoGen/SubSystems/BeamBeamoOtelApi.h"
#include "BeamableCore/Public/AutoGen/SubSystems/BeamoOtel/PostOtelViewsRequest.h"
#include "BeamableCore/Public/AutoGen/OtelView.h"

#define LOCTEXT_NAMESPACE "K2BeamNode_ApiRequest_PostOtelViews"

using namespace BeamK2;

FName UK2BeamNode_ApiRequest_PostOtelViews::GetSelfFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamBeamoOtelApi, GetSelf);
}

FName UK2BeamNode_ApiRequest_PostOtelViews::GetRequestFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamBeamoOtelApi, PostOtelViews);
}

FName UK2BeamNode_ApiRequest_PostOtelViews::GetMakeFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UPostOtelViewsRequest, Make);
}

FString UK2BeamNode_ApiRequest_PostOtelViews::GetServiceName() const
{
	return TEXT("BeamoOtel");
}

FString UK2BeamNode_ApiRequest_PostOtelViews::GetEndpointName() const
{
	return TEXT("PostOtelViews");
}

UClass* UK2BeamNode_ApiRequest_PostOtelViews::GetApiClass() const
{
	return UBeamBeamoOtelApi::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_PostOtelViews::GetRequestClass() const
{
	return UPostOtelViewsRequest::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_PostOtelViews::GetResponseClass() const
{
	return UOtelView::StaticClass();
}

FString UK2BeamNode_ApiRequest_PostOtelViews::GetRequestSuccessDelegateName() const
{
	return TEXT("OnPostOtelViewsSuccess");
}

FString UK2BeamNode_ApiRequest_PostOtelViews::GetRequestErrorDelegateName() const
{
	return TEXT("OnPostOtelViewsError");
}

FString UK2BeamNode_ApiRequest_PostOtelViews::GetRequestCompleteDelegateName() const
{
	return TEXT("OnPostOtelViewsComplete");
}

#undef LOCTEXT_NAMESPACE
