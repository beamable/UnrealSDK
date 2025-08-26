

#include "BeamableCoreBlueprintNodes/Public/BeamFlow/ApiRequest/AutoGen/BeamoOtel/K2BeamNode_ApiRequest_PutOtelViews.h"

#include "BeamK2.h"

#include "BeamableCore/Public/AutoGen/SubSystems/BeamBeamoOtelApi.h"
#include "BeamableCore/Public/AutoGen/SubSystems/BeamoOtel/PutOtelViewsRequest.h"
#include "BeamableCore/Public/AutoGen/OtelView.h"

#define LOCTEXT_NAMESPACE "K2BeamNode_ApiRequest_PutOtelViews"

using namespace BeamK2;

FName UK2BeamNode_ApiRequest_PutOtelViews::GetSelfFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamBeamoOtelApi, GetSelf);
}

FName UK2BeamNode_ApiRequest_PutOtelViews::GetRequestFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamBeamoOtelApi, PutOtelViews);
}

FName UK2BeamNode_ApiRequest_PutOtelViews::GetMakeFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UPutOtelViewsRequest, Make);
}

FString UK2BeamNode_ApiRequest_PutOtelViews::GetServiceName() const
{
	return TEXT("BeamoOtel");
}

FString UK2BeamNode_ApiRequest_PutOtelViews::GetEndpointName() const
{
	return TEXT("PutOtelViews");
}

UClass* UK2BeamNode_ApiRequest_PutOtelViews::GetApiClass() const
{
	return UBeamBeamoOtelApi::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_PutOtelViews::GetRequestClass() const
{
	return UPutOtelViewsRequest::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_PutOtelViews::GetResponseClass() const
{
	return UOtelView::StaticClass();
}

FString UK2BeamNode_ApiRequest_PutOtelViews::GetRequestSuccessDelegateName() const
{
	return TEXT("OnPutOtelViewsSuccess");
}

FString UK2BeamNode_ApiRequest_PutOtelViews::GetRequestErrorDelegateName() const
{
	return TEXT("OnPutOtelViewsError");
}

FString UK2BeamNode_ApiRequest_PutOtelViews::GetRequestCompleteDelegateName() const
{
	return TEXT("OnPutOtelViewsComplete");
}

#undef LOCTEXT_NAMESPACE
