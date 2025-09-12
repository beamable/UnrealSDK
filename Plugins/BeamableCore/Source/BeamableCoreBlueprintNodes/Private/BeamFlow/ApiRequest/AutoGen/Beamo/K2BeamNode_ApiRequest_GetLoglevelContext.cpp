

#include "BeamableCoreBlueprintNodes/Public/BeamFlow/ApiRequest/AutoGen/Beamo/K2BeamNode_ApiRequest_GetLoglevelContext.h"

#include "BeamK2.h"

#include "BeamableCore/Public/AutoGen/SubSystems/BeamBeamoApi.h"
#include "BeamableCore/Public/AutoGen/SubSystems/Beamo/GetLoglevelContextRequest.h"
#include "BeamableCore/Public/AutoGen/BeamoV2LogSwitchContextDocument.h"

#define LOCTEXT_NAMESPACE "K2BeamNode_ApiRequest_GetLoglevelContext"

using namespace BeamK2;

FName UK2BeamNode_ApiRequest_GetLoglevelContext::GetSelfFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamBeamoApi, GetSelf);
}

FName UK2BeamNode_ApiRequest_GetLoglevelContext::GetRequestFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamBeamoApi, GetLoglevelContext);
}

FName UK2BeamNode_ApiRequest_GetLoglevelContext::GetMakeFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UGetLoglevelContextRequest, Make);
}

FString UK2BeamNode_ApiRequest_GetLoglevelContext::GetServiceName() const
{
	return TEXT("Beamo");
}

FString UK2BeamNode_ApiRequest_GetLoglevelContext::GetEndpointName() const
{
	return TEXT("GetLoglevelContext");
}

UClass* UK2BeamNode_ApiRequest_GetLoglevelContext::GetApiClass() const
{
	return UBeamBeamoApi::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_GetLoglevelContext::GetRequestClass() const
{
	return UGetLoglevelContextRequest::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_GetLoglevelContext::GetResponseClass() const
{
	return UBeamoV2LogSwitchContextDocument::StaticClass();
}

FString UK2BeamNode_ApiRequest_GetLoglevelContext::GetRequestSuccessDelegateName() const
{
	return TEXT("OnGetLoglevelContextSuccess");
}

FString UK2BeamNode_ApiRequest_GetLoglevelContext::GetRequestErrorDelegateName() const
{
	return TEXT("OnGetLoglevelContextError");
}

FString UK2BeamNode_ApiRequest_GetLoglevelContext::GetRequestCompleteDelegateName() const
{
	return TEXT("OnGetLoglevelContextComplete");
}

#undef LOCTEXT_NAMESPACE
