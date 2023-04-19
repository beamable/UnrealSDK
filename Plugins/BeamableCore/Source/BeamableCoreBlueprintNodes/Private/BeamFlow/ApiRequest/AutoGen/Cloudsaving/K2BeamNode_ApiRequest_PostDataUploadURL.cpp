

#include "BeamableCoreBlueprintNodes/Public/BeamFlow/ApiRequest/AutoGen/Cloudsaving/K2BeamNode_ApiRequest_PostDataUploadURL.h"

#include "BeamK2.h"

#include "BeamableCore/Public/AutoGen/SubSystems/BeamCloudsavingApi.h"
#include "BeamableCore/Public/AutoGen/SubSystems/Cloudsaving/PostDataUploadURLRequest.h"
#include "BeamableCore/Public/AutoGen/URLSResponse.h"

#define LOCTEXT_NAMESPACE "K2BeamNode_ApiRequest_PostDataUploadURL"

using namespace BeamK2;

FName UK2BeamNode_ApiRequest_PostDataUploadURL::GetSelfFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamCloudsavingApi, GetSelf);
}

FName UK2BeamNode_ApiRequest_PostDataUploadURL::GetRequestFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamCloudsavingApi, PostDataUploadURL);
}

FName UK2BeamNode_ApiRequest_PostDataUploadURL::GetMakeFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UPostDataUploadURLRequest, Make);
}

FString UK2BeamNode_ApiRequest_PostDataUploadURL::GetServiceName() const
{
	return TEXT("Cloudsaving");
}

FString UK2BeamNode_ApiRequest_PostDataUploadURL::GetEndpointName() const
{
	return TEXT("PostDataUploadURL");
}

UClass* UK2BeamNode_ApiRequest_PostDataUploadURL::GetApiClass() const
{
	return UBeamCloudsavingApi::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_PostDataUploadURL::GetRequestClass() const
{
	return UPostDataUploadURLRequest::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_PostDataUploadURL::GetResponseClass() const
{
	return UURLSResponse::StaticClass();
}

FString UK2BeamNode_ApiRequest_PostDataUploadURL::GetRequestSuccessDelegateName() const
{
	return TEXT("OnPostDataUploadURLSuccess");
}

FString UK2BeamNode_ApiRequest_PostDataUploadURL::GetRequestErrorDelegateName() const
{
	return TEXT("OnPostDataUploadURLError");
}

FString UK2BeamNode_ApiRequest_PostDataUploadURL::GetRequestCompleteDelegateName() const
{
	return TEXT("OnPostDataUploadURLComplete");
}

#undef LOCTEXT_NAMESPACE
