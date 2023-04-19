

#include "BeamableCoreBlueprintNodes/Public/BeamFlow/ApiRequest/AutoGen/Cloudsaving/K2BeamNode_ApiRequest_DeleteData.h"

#include "BeamK2.h"

#include "BeamableCore/Public/AutoGen/SubSystems/BeamCloudsavingApi.h"
#include "BeamableCore/Public/AutoGen/SubSystems/Cloudsaving/DeleteDataRequest.h"
#include "BeamableCore/Public/AutoGen/EmptyResponse.h"

#define LOCTEXT_NAMESPACE "K2BeamNode_ApiRequest_DeleteData"

using namespace BeamK2;

FName UK2BeamNode_ApiRequest_DeleteData::GetSelfFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamCloudsavingApi, GetSelf);
}

FName UK2BeamNode_ApiRequest_DeleteData::GetRequestFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamCloudsavingApi, DeleteData);
}

FName UK2BeamNode_ApiRequest_DeleteData::GetMakeFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UDeleteDataRequest, Make);
}

FString UK2BeamNode_ApiRequest_DeleteData::GetServiceName() const
{
	return TEXT("Cloudsaving");
}

FString UK2BeamNode_ApiRequest_DeleteData::GetEndpointName() const
{
	return TEXT("DeleteData");
}

UClass* UK2BeamNode_ApiRequest_DeleteData::GetApiClass() const
{
	return UBeamCloudsavingApi::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_DeleteData::GetRequestClass() const
{
	return UDeleteDataRequest::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_DeleteData::GetResponseClass() const
{
	return UEmptyResponse::StaticClass();
}

FString UK2BeamNode_ApiRequest_DeleteData::GetRequestSuccessDelegateName() const
{
	return TEXT("OnDeleteDataSuccess");
}

FString UK2BeamNode_ApiRequest_DeleteData::GetRequestErrorDelegateName() const
{
	return TEXT("OnDeleteDataError");
}

FString UK2BeamNode_ApiRequest_DeleteData::GetRequestCompleteDelegateName() const
{
	return TEXT("OnDeleteDataComplete");
}

#undef LOCTEXT_NAMESPACE
