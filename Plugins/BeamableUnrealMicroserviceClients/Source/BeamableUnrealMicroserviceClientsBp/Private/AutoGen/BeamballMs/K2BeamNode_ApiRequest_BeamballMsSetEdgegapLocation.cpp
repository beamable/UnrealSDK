

#include "BeamableUnrealMicroserviceClientsBp/Public/AutoGen/BeamballMs/K2BeamNode_ApiRequest_BeamballMsSetEdgegapLocation.h"

#include "BeamK2.h"

#include "BeamableUnrealMicroserviceClients/Public/AutoGen/SubSystems/BeamBeamballMsApi.h"
#include "BeamableUnrealMicroserviceClients/Public/AutoGen/SubSystems/BeamballMs/BeamballMsSetEdgegapLocationRequest.h"
#include "Serialization/BeamPlainTextResponseBody.h"

#define LOCTEXT_NAMESPACE "K2BeamNode_ApiRequest_BeamballMsSetEdgegapLocation"

using namespace BeamK2;

FName UK2BeamNode_ApiRequest_BeamballMsSetEdgegapLocation::GetSelfFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamBeamballMsApi, GetSelf);
}

FName UK2BeamNode_ApiRequest_BeamballMsSetEdgegapLocation::GetRequestFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamBeamballMsApi, SetEdgegapLocation);
}

FName UK2BeamNode_ApiRequest_BeamballMsSetEdgegapLocation::GetMakeFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamballMsSetEdgegapLocationRequest, Make);
}

FString UK2BeamNode_ApiRequest_BeamballMsSetEdgegapLocation::GetServiceName() const
{
	return TEXT("BeamballMs");
}

FString UK2BeamNode_ApiRequest_BeamballMsSetEdgegapLocation::GetEndpointName() const
{
	return TEXT("SetEdgegapLocation");
}

UClass* UK2BeamNode_ApiRequest_BeamballMsSetEdgegapLocation::GetApiClass() const
{
	return UBeamBeamballMsApi::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_BeamballMsSetEdgegapLocation::GetRequestClass() const
{
	return UBeamballMsSetEdgegapLocationRequest::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_BeamballMsSetEdgegapLocation::GetResponseClass() const
{
	return UBeamPlainTextResponseBody::StaticClass();
}

FString UK2BeamNode_ApiRequest_BeamballMsSetEdgegapLocation::GetRequestSuccessDelegateName() const
{
	return TEXT("OnBeamballMsSetEdgegapLocationSuccess");
}

FString UK2BeamNode_ApiRequest_BeamballMsSetEdgegapLocation::GetRequestErrorDelegateName() const
{
	return TEXT("OnBeamballMsSetEdgegapLocationError");
}

FString UK2BeamNode_ApiRequest_BeamballMsSetEdgegapLocation::GetRequestCompleteDelegateName() const
{
	return TEXT("OnBeamballMsSetEdgegapLocationComplete");
}

#undef LOCTEXT_NAMESPACE
