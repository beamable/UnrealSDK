

#include "BeamableCoreBlueprintNodes/Public/BeamFlow/ApiRequest/AutoGen/Beamo/K2BeamNode_ApiRequest_PutServicesLogsContext.h"

#include "BeamK2.h"

#include "BeamableCore/Public/AutoGen/SubSystems/BeamBeamoApi.h"
#include "BeamableCore/Public/AutoGen/SubSystems/Beamo/PutServicesLogsContextRequest.h"
#include "BeamableCore/Public/AutoGen/BeamoV2EmptyMessage.h"

#define LOCTEXT_NAMESPACE "K2BeamNode_ApiRequest_PutServicesLogsContext"

using namespace BeamK2;

FName UK2BeamNode_ApiRequest_PutServicesLogsContext::GetSelfFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamBeamoApi, GetSelf);
}

FName UK2BeamNode_ApiRequest_PutServicesLogsContext::GetRequestFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamBeamoApi, PutServicesLogsContext);
}

FName UK2BeamNode_ApiRequest_PutServicesLogsContext::GetMakeFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UPutServicesLogsContextRequest, Make);
}

FString UK2BeamNode_ApiRequest_PutServicesLogsContext::GetServiceName() const
{
	return TEXT("Beamo");
}

FString UK2BeamNode_ApiRequest_PutServicesLogsContext::GetEndpointName() const
{
	return TEXT("PutServicesLogsContext");
}

UClass* UK2BeamNode_ApiRequest_PutServicesLogsContext::GetApiClass() const
{
	return UBeamBeamoApi::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_PutServicesLogsContext::GetRequestClass() const
{
	return UPutServicesLogsContextRequest::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_PutServicesLogsContext::GetResponseClass() const
{
	return UBeamoV2EmptyMessage::StaticClass();
}

FString UK2BeamNode_ApiRequest_PutServicesLogsContext::GetRequestSuccessDelegateName() const
{
	return TEXT("OnPutServicesLogsContextSuccess");
}

FString UK2BeamNode_ApiRequest_PutServicesLogsContext::GetRequestErrorDelegateName() const
{
	return TEXT("OnPutServicesLogsContextError");
}

FString UK2BeamNode_ApiRequest_PutServicesLogsContext::GetRequestCompleteDelegateName() const
{
	return TEXT("OnPutServicesLogsContextComplete");
}

#undef LOCTEXT_NAMESPACE
