

#include "BeamableCoreBlueprintNodes/Public/BeamFlow/ApiRequest/AutoGen/BeamoOtel/K2BeamNode_ApiRequest_GetOtelViews.h"

#include "BeamK2.h"

#include "BeamableCore/Public/AutoGen/SubSystems/BeamBeamoOtelApi.h"
#include "BeamableCore/Public/AutoGen/SubSystems/BeamoOtel/GetOtelViewsRequest.h"
#include "BeamableCore/Public/AutoGen/OtelViewsResponse.h"

#define LOCTEXT_NAMESPACE "K2BeamNode_ApiRequest_GetOtelViews"

using namespace BeamK2;

FName UK2BeamNode_ApiRequest_GetOtelViews::GetSelfFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamBeamoOtelApi, GetSelf);
}

FName UK2BeamNode_ApiRequest_GetOtelViews::GetRequestFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamBeamoOtelApi, GetOtelViews);
}

FName UK2BeamNode_ApiRequest_GetOtelViews::GetMakeFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UGetOtelViewsRequest, Make);
}

FString UK2BeamNode_ApiRequest_GetOtelViews::GetServiceName() const
{
	return TEXT("BeamoOtel");
}

FString UK2BeamNode_ApiRequest_GetOtelViews::GetEndpointName() const
{
	return TEXT("GetOtelViews");
}

UClass* UK2BeamNode_ApiRequest_GetOtelViews::GetApiClass() const
{
	return UBeamBeamoOtelApi::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_GetOtelViews::GetRequestClass() const
{
	return UGetOtelViewsRequest::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_GetOtelViews::GetResponseClass() const
{
	return UOtelViewsResponse::StaticClass();
}

FString UK2BeamNode_ApiRequest_GetOtelViews::GetRequestSuccessDelegateName() const
{
	return TEXT("OnGetOtelViewsSuccess");
}

FString UK2BeamNode_ApiRequest_GetOtelViews::GetRequestErrorDelegateName() const
{
	return TEXT("OnGetOtelViewsError");
}

FString UK2BeamNode_ApiRequest_GetOtelViews::GetRequestCompleteDelegateName() const
{
	return TEXT("OnGetOtelViewsComplete");
}

#undef LOCTEXT_NAMESPACE
