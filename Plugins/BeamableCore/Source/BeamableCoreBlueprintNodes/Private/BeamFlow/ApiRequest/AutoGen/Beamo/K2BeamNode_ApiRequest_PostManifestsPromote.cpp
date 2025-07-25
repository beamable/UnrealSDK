

#include "BeamableCoreBlueprintNodes/Public/BeamFlow/ApiRequest/AutoGen/Beamo/K2BeamNode_ApiRequest_PostManifestsPromote.h"

#include "BeamK2.h"

#include "BeamableCore/Public/AutoGen/SubSystems/BeamBeamoApi.h"
#include "BeamableCore/Public/AutoGen/SubSystems/Beamo/PostManifestsPromoteRequest.h"
#include "BeamableCore/Public/AutoGen/BeamoV2EmptyMessage.h"

#define LOCTEXT_NAMESPACE "K2BeamNode_ApiRequest_PostManifestsPromote"

using namespace BeamK2;

FName UK2BeamNode_ApiRequest_PostManifestsPromote::GetSelfFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamBeamoApi, GetSelf);
}

FName UK2BeamNode_ApiRequest_PostManifestsPromote::GetRequestFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamBeamoApi, PostManifestsPromote);
}

FName UK2BeamNode_ApiRequest_PostManifestsPromote::GetMakeFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UPostManifestsPromoteRequest, Make);
}

FString UK2BeamNode_ApiRequest_PostManifestsPromote::GetServiceName() const
{
	return TEXT("Beamo");
}

FString UK2BeamNode_ApiRequest_PostManifestsPromote::GetEndpointName() const
{
	return TEXT("PostManifestsPromote");
}

UClass* UK2BeamNode_ApiRequest_PostManifestsPromote::GetApiClass() const
{
	return UBeamBeamoApi::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_PostManifestsPromote::GetRequestClass() const
{
	return UPostManifestsPromoteRequest::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_PostManifestsPromote::GetResponseClass() const
{
	return UBeamoV2EmptyMessage::StaticClass();
}

FString UK2BeamNode_ApiRequest_PostManifestsPromote::GetRequestSuccessDelegateName() const
{
	return TEXT("OnPostManifestsPromoteSuccess");
}

FString UK2BeamNode_ApiRequest_PostManifestsPromote::GetRequestErrorDelegateName() const
{
	return TEXT("OnPostManifestsPromoteError");
}

FString UK2BeamNode_ApiRequest_PostManifestsPromote::GetRequestCompleteDelegateName() const
{
	return TEXT("OnPostManifestsPromoteComplete");
}

#undef LOCTEXT_NAMESPACE
