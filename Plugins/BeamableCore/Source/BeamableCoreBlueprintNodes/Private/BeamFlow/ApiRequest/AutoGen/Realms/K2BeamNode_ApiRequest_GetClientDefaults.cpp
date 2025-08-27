

#include "BeamableCoreBlueprintNodes/Public/BeamFlow/ApiRequest/AutoGen/Realms/K2BeamNode_ApiRequest_GetClientDefaults.h"

#include "BeamK2.h"

#include "BeamableCore/Public/AutoGen/SubSystems/BeamRealmsApi.h"
#include "BeamableCore/Public/AutoGen/SubSystems/Realms/GetClientDefaultsRequest.h"
#include "BeamableCore/Public/AutoGen/RealmConfiguration.h"

#define LOCTEXT_NAMESPACE "K2BeamNode_ApiRequest_GetClientDefaults"

using namespace BeamK2;

FName UK2BeamNode_ApiRequest_GetClientDefaults::GetSelfFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamRealmsApi, GetSelf);
}

FName UK2BeamNode_ApiRequest_GetClientDefaults::GetRequestFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamRealmsApi, GetClientDefaults);
}

FName UK2BeamNode_ApiRequest_GetClientDefaults::GetMakeFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UGetClientDefaultsRequest, Make);
}

FString UK2BeamNode_ApiRequest_GetClientDefaults::GetServiceName() const
{
	return TEXT("Realms");
}

FString UK2BeamNode_ApiRequest_GetClientDefaults::GetEndpointName() const
{
	return TEXT("GetClientDefaults");
}

UClass* UK2BeamNode_ApiRequest_GetClientDefaults::GetApiClass() const
{
	return UBeamRealmsApi::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_GetClientDefaults::GetRequestClass() const
{
	return UGetClientDefaultsRequest::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_GetClientDefaults::GetResponseClass() const
{
	return URealmConfiguration::StaticClass();
}

FString UK2BeamNode_ApiRequest_GetClientDefaults::GetRequestSuccessDelegateName() const
{
	return TEXT("OnGetClientDefaultsSuccess");
}

FString UK2BeamNode_ApiRequest_GetClientDefaults::GetRequestErrorDelegateName() const
{
	return TEXT("OnGetClientDefaultsError");
}

FString UK2BeamNode_ApiRequest_GetClientDefaults::GetRequestCompleteDelegateName() const
{
	return TEXT("OnGetClientDefaultsComplete");
}

#undef LOCTEXT_NAMESPACE
