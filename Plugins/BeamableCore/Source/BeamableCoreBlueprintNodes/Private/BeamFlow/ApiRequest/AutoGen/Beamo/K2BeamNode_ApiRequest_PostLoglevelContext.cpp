

#include "BeamableCoreBlueprintNodes/Public/BeamFlow/ApiRequest/AutoGen/Beamo/K2BeamNode_ApiRequest_PostLoglevelContext.h"

#include "BeamK2.h"

#include "BeamableCore/Public/AutoGen/SubSystems/BeamBeamoApi.h"
#include "BeamableCore/Public/AutoGen/SubSystems/Beamo/PostLoglevelContextRequest.h"
#include "BeamableCore/Public/AutoGen/BeamoV2EmptyMessage.h"

#define LOCTEXT_NAMESPACE "K2BeamNode_ApiRequest_PostLoglevelContext"

using namespace BeamK2;

FName UK2BeamNode_ApiRequest_PostLoglevelContext::GetSelfFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamBeamoApi, GetSelf);
}

FName UK2BeamNode_ApiRequest_PostLoglevelContext::GetRequestFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamBeamoApi, PostLoglevelContext);
}

FName UK2BeamNode_ApiRequest_PostLoglevelContext::GetMakeFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UPostLoglevelContextRequest, Make);
}

FString UK2BeamNode_ApiRequest_PostLoglevelContext::GetServiceName() const
{
	return TEXT("Beamo");
}

FString UK2BeamNode_ApiRequest_PostLoglevelContext::GetEndpointName() const
{
	return TEXT("PostLoglevelContext");
}

UClass* UK2BeamNode_ApiRequest_PostLoglevelContext::GetApiClass() const
{
	return UBeamBeamoApi::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_PostLoglevelContext::GetRequestClass() const
{
	return UPostLoglevelContextRequest::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_PostLoglevelContext::GetResponseClass() const
{
	return UBeamoV2EmptyMessage::StaticClass();
}

FString UK2BeamNode_ApiRequest_PostLoglevelContext::GetRequestSuccessDelegateName() const
{
	return TEXT("OnPostLoglevelContextSuccess");
}

FString UK2BeamNode_ApiRequest_PostLoglevelContext::GetRequestErrorDelegateName() const
{
	return TEXT("OnPostLoglevelContextError");
}

FString UK2BeamNode_ApiRequest_PostLoglevelContext::GetRequestCompleteDelegateName() const
{
	return TEXT("OnPostLoglevelContextComplete");
}

#undef LOCTEXT_NAMESPACE
