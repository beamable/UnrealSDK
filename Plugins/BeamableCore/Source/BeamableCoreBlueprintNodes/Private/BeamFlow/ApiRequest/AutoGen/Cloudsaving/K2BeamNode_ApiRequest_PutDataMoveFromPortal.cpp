

#include "BeamableCoreBlueprintNodes/Public/BeamFlow/ApiRequest/AutoGen/Cloudsaving/K2BeamNode_ApiRequest_PutDataMoveFromPortal.h"

#include "BeamK2.h"

#include "BeamableCore/Public/AutoGen/SubSystems/BeamCloudsavingApi.h"
#include "BeamableCore/Public/AutoGen/SubSystems/Cloudsaving/PutDataMoveFromPortalRequest.h"
#include "BeamableCore/Public/AutoGen/CloudsavingBasicManifest.h"

#define LOCTEXT_NAMESPACE "K2BeamNode_ApiRequest_PutDataMoveFromPortal"

using namespace BeamK2;

FName UK2BeamNode_ApiRequest_PutDataMoveFromPortal::GetSelfFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamCloudsavingApi, GetSelf);
}

FName UK2BeamNode_ApiRequest_PutDataMoveFromPortal::GetRequestFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamCloudsavingApi, PutDataMoveFromPortal);
}

FName UK2BeamNode_ApiRequest_PutDataMoveFromPortal::GetMakeFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UPutDataMoveFromPortalRequest, Make);
}

FString UK2BeamNode_ApiRequest_PutDataMoveFromPortal::GetServiceName() const
{
	return TEXT("Cloudsaving");
}

FString UK2BeamNode_ApiRequest_PutDataMoveFromPortal::GetEndpointName() const
{
	return TEXT("PutDataMoveFromPortal");
}

UClass* UK2BeamNode_ApiRequest_PutDataMoveFromPortal::GetApiClass() const
{
	return UBeamCloudsavingApi::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_PutDataMoveFromPortal::GetRequestClass() const
{
	return UPutDataMoveFromPortalRequest::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_PutDataMoveFromPortal::GetResponseClass() const
{
	return UCloudsavingBasicManifest::StaticClass();
}

FString UK2BeamNode_ApiRequest_PutDataMoveFromPortal::GetRequestSuccessDelegateName() const
{
	return TEXT("OnPutDataMoveFromPortalSuccess");
}

FString UK2BeamNode_ApiRequest_PutDataMoveFromPortal::GetRequestErrorDelegateName() const
{
	return TEXT("OnPutDataMoveFromPortalError");
}

FString UK2BeamNode_ApiRequest_PutDataMoveFromPortal::GetRequestCompleteDelegateName() const
{
	return TEXT("OnPutDataMoveFromPortalComplete");
}

#undef LOCTEXT_NAMESPACE
