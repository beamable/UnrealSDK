

#include "BeamableCoreBlueprintNodes/Public/BeamFlow/ApiRequest/AutoGen/Beamo/K2BeamNode_ApiRequest_PutImageCommit.h"

#include "BeamK2.h"

#include "BeamableCore/Public/AutoGen/SubSystems/BeamBeamoApi.h"
#include "BeamableCore/Public/AutoGen/SubSystems/Beamo/PutImageCommitRequest.h"
#include "BeamableCore/Public/AutoGen/LambdaResponse.h"

#define LOCTEXT_NAMESPACE "K2BeamNode_ApiRequest_PutImageCommit"

using namespace BeamK2;

FName UK2BeamNode_ApiRequest_PutImageCommit::GetSelfFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamBeamoApi, GetSelf);
}

FName UK2BeamNode_ApiRequest_PutImageCommit::GetRequestFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamBeamoApi, PutImageCommit);
}

FName UK2BeamNode_ApiRequest_PutImageCommit::GetMakeFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UPutImageCommitRequest, Make);
}

FString UK2BeamNode_ApiRequest_PutImageCommit::GetServiceName() const
{
	return TEXT("Beamo");
}

FString UK2BeamNode_ApiRequest_PutImageCommit::GetEndpointName() const
{
	return TEXT("PutImageCommit");
}

UClass* UK2BeamNode_ApiRequest_PutImageCommit::GetApiClass() const
{
	return UBeamBeamoApi::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_PutImageCommit::GetRequestClass() const
{
	return UPutImageCommitRequest::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_PutImageCommit::GetResponseClass() const
{
	return ULambdaResponse::StaticClass();
}

FString UK2BeamNode_ApiRequest_PutImageCommit::GetRequestSuccessDelegateName() const
{
	return TEXT("OnPutImageCommitSuccess");
}

FString UK2BeamNode_ApiRequest_PutImageCommit::GetRequestErrorDelegateName() const
{
	return TEXT("OnPutImageCommitError");
}

FString UK2BeamNode_ApiRequest_PutImageCommit::GetRequestCompleteDelegateName() const
{
	return TEXT("OnPutImageCommitComplete");
}

#undef LOCTEXT_NAMESPACE
