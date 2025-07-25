

#include "BeamableCoreBlueprintNodes/Public/BeamFlow/ApiRequest/AutoGen/Beamo/K2BeamNode_ApiRequest_PostManifestsCurrent.h"

#include "BeamK2.h"

#include "BeamableCore/Public/AutoGen/SubSystems/BeamBeamoApi.h"
#include "BeamableCore/Public/AutoGen/SubSystems/Beamo/PostManifestsCurrentRequest.h"
#include "BeamableCore/Public/AutoGen/BeamoV2EmptyMessage.h"

#define LOCTEXT_NAMESPACE "K2BeamNode_ApiRequest_PostManifestsCurrent"

using namespace BeamK2;

FName UK2BeamNode_ApiRequest_PostManifestsCurrent::GetSelfFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamBeamoApi, GetSelf);
}

FName UK2BeamNode_ApiRequest_PostManifestsCurrent::GetRequestFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamBeamoApi, PostManifestsCurrent);
}

FName UK2BeamNode_ApiRequest_PostManifestsCurrent::GetMakeFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UPostManifestsCurrentRequest, Make);
}

FString UK2BeamNode_ApiRequest_PostManifestsCurrent::GetServiceName() const
{
	return TEXT("Beamo");
}

FString UK2BeamNode_ApiRequest_PostManifestsCurrent::GetEndpointName() const
{
	return TEXT("PostManifestsCurrent");
}

UClass* UK2BeamNode_ApiRequest_PostManifestsCurrent::GetApiClass() const
{
	return UBeamBeamoApi::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_PostManifestsCurrent::GetRequestClass() const
{
	return UPostManifestsCurrentRequest::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_PostManifestsCurrent::GetResponseClass() const
{
	return UBeamoV2EmptyMessage::StaticClass();
}

FString UK2BeamNode_ApiRequest_PostManifestsCurrent::GetRequestSuccessDelegateName() const
{
	return TEXT("OnPostManifestsCurrentSuccess");
}

FString UK2BeamNode_ApiRequest_PostManifestsCurrent::GetRequestErrorDelegateName() const
{
	return TEXT("OnPostManifestsCurrentError");
}

FString UK2BeamNode_ApiRequest_PostManifestsCurrent::GetRequestCompleteDelegateName() const
{
	return TEXT("OnPostManifestsCurrentComplete");
}

#undef LOCTEXT_NAMESPACE
