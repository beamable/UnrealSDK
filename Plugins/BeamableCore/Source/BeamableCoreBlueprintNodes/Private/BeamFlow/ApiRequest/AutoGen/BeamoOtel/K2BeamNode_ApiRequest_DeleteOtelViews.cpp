

#include "BeamableCoreBlueprintNodes/Public/BeamFlow/ApiRequest/AutoGen/BeamoOtel/K2BeamNode_ApiRequest_DeleteOtelViews.h"

#include "BeamK2.h"

#include "BeamableCore/Public/AutoGen/SubSystems/BeamBeamoOtelApi.h"
#include "BeamableCore/Public/AutoGen/SubSystems/BeamoOtel/DeleteOtelViewsRequest.h"
#include "BeamableCore/Public/AutoGen/ApiBeamoOtelViewsDeleteBeamoOtelResponse.h"

#define LOCTEXT_NAMESPACE "K2BeamNode_ApiRequest_DeleteOtelViews"

using namespace BeamK2;

FName UK2BeamNode_ApiRequest_DeleteOtelViews::GetSelfFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamBeamoOtelApi, GetSelf);
}

FName UK2BeamNode_ApiRequest_DeleteOtelViews::GetRequestFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamBeamoOtelApi, DeleteOtelViews);
}

FName UK2BeamNode_ApiRequest_DeleteOtelViews::GetMakeFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UDeleteOtelViewsRequest, Make);
}

FString UK2BeamNode_ApiRequest_DeleteOtelViews::GetServiceName() const
{
	return TEXT("BeamoOtel");
}

FString UK2BeamNode_ApiRequest_DeleteOtelViews::GetEndpointName() const
{
	return TEXT("DeleteOtelViews");
}

UClass* UK2BeamNode_ApiRequest_DeleteOtelViews::GetApiClass() const
{
	return UBeamBeamoOtelApi::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_DeleteOtelViews::GetRequestClass() const
{
	return UDeleteOtelViewsRequest::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_DeleteOtelViews::GetResponseClass() const
{
	return UApiBeamoOtelViewsDeleteBeamoOtelResponse::StaticClass();
}

FString UK2BeamNode_ApiRequest_DeleteOtelViews::GetRequestSuccessDelegateName() const
{
	return TEXT("OnDeleteOtelViewsSuccess");
}

FString UK2BeamNode_ApiRequest_DeleteOtelViews::GetRequestErrorDelegateName() const
{
	return TEXT("OnDeleteOtelViewsError");
}

FString UK2BeamNode_ApiRequest_DeleteOtelViews::GetRequestCompleteDelegateName() const
{
	return TEXT("OnDeleteOtelViewsComplete");
}

#undef LOCTEXT_NAMESPACE
