

#include "BeamableCoreBlueprintNodes/Public/BeamFlow/ApiRequest/AutoGen/Cloudsaving/K2BeamNode_ApiRequest_GetCloudsaving.h"

#include "BeamK2.h"

#include "BeamableCore/Public/AutoGen/SubSystems/BeamCloudsavingApi.h"
#include "BeamableCore/Public/AutoGen/SubSystems/Cloudsaving/GetCloudsavingRequest.h"
#include "BeamableCore/Public/AutoGen/CloudsavingBasicManifest.h"

#define LOCTEXT_NAMESPACE "K2BeamNode_ApiRequest_GetCloudsaving"

using namespace BeamK2;

FName UK2BeamNode_ApiRequest_GetCloudsaving::GetSelfFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamCloudsavingApi, GetSelf);
}

FName UK2BeamNode_ApiRequest_GetCloudsaving::GetRequestFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamCloudsavingApi, GetCloudsaving);
}

FName UK2BeamNode_ApiRequest_GetCloudsaving::GetMakeFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UGetCloudsavingRequest, Make);
}

FString UK2BeamNode_ApiRequest_GetCloudsaving::GetServiceName() const
{
	return TEXT("Cloudsaving");
}

FString UK2BeamNode_ApiRequest_GetCloudsaving::GetEndpointName() const
{
	return TEXT("GetCloudsaving");
}

UClass* UK2BeamNode_ApiRequest_GetCloudsaving::GetApiClass() const
{
	return UBeamCloudsavingApi::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_GetCloudsaving::GetRequestClass() const
{
	return UGetCloudsavingRequest::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_GetCloudsaving::GetResponseClass() const
{
	return UCloudsavingBasicManifest::StaticClass();
}

FString UK2BeamNode_ApiRequest_GetCloudsaving::GetRequestSuccessDelegateName() const
{
	return TEXT("OnGetCloudsavingSuccess");
}

FString UK2BeamNode_ApiRequest_GetCloudsaving::GetRequestErrorDelegateName() const
{
	return TEXT("OnGetCloudsavingError");
}

FString UK2BeamNode_ApiRequest_GetCloudsaving::GetRequestCompleteDelegateName() const
{
	return TEXT("OnGetCloudsavingComplete");
}

#undef LOCTEXT_NAMESPACE
