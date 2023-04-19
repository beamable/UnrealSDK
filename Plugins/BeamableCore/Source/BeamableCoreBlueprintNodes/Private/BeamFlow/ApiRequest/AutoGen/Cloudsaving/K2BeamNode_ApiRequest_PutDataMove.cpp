

#include "BeamableCoreBlueprintNodes/Public/BeamFlow/ApiRequest/AutoGen/Cloudsaving/K2BeamNode_ApiRequest_PutDataMove.h"

#include "BeamK2.h"

#include "BeamableCore/Public/AutoGen/SubSystems/BeamCloudsavingApi.h"
#include "BeamableCore/Public/AutoGen/SubSystems/Cloudsaving/PutDataMoveRequest.h"
#include "BeamableCore/Public/AutoGen/CloudsavingBasicManifest.h"

#define LOCTEXT_NAMESPACE "K2BeamNode_ApiRequest_PutDataMove"

using namespace BeamK2;

FName UK2BeamNode_ApiRequest_PutDataMove::GetSelfFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamCloudsavingApi, GetSelf);
}

FName UK2BeamNode_ApiRequest_PutDataMove::GetRequestFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamCloudsavingApi, PutDataMove);
}

FName UK2BeamNode_ApiRequest_PutDataMove::GetMakeFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UPutDataMoveRequest, Make);
}

FString UK2BeamNode_ApiRequest_PutDataMove::GetServiceName() const
{
	return TEXT("Cloudsaving");
}

FString UK2BeamNode_ApiRequest_PutDataMove::GetEndpointName() const
{
	return TEXT("PutDataMove");
}

UClass* UK2BeamNode_ApiRequest_PutDataMove::GetApiClass() const
{
	return UBeamCloudsavingApi::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_PutDataMove::GetRequestClass() const
{
	return UPutDataMoveRequest::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_PutDataMove::GetResponseClass() const
{
	return UCloudsavingBasicManifest::StaticClass();
}

FString UK2BeamNode_ApiRequest_PutDataMove::GetRequestSuccessDelegateName() const
{
	return TEXT("OnPutDataMoveSuccess");
}

FString UK2BeamNode_ApiRequest_PutDataMove::GetRequestErrorDelegateName() const
{
	return TEXT("OnPutDataMoveError");
}

FString UK2BeamNode_ApiRequest_PutDataMove::GetRequestCompleteDelegateName() const
{
	return TEXT("OnPutDataMoveComplete");
}

#undef LOCTEXT_NAMESPACE
