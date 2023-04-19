

#include "BeamableCoreBlueprintNodes/Public/BeamFlow/ApiRequest/AutoGen/Cloudsaving/K2BeamNode_ApiRequest_PostDataDownloadURL.h"

#include "BeamK2.h"

#include "BeamableCore/Public/AutoGen/SubSystems/BeamCloudsavingApi.h"
#include "BeamableCore/Public/AutoGen/SubSystems/Cloudsaving/PostDataDownloadURLRequest.h"
#include "BeamableCore/Public/AutoGen/URLSResponse.h"

#define LOCTEXT_NAMESPACE "K2BeamNode_ApiRequest_PostDataDownloadURL"

using namespace BeamK2;

FName UK2BeamNode_ApiRequest_PostDataDownloadURL::GetSelfFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamCloudsavingApi, GetSelf);
}

FName UK2BeamNode_ApiRequest_PostDataDownloadURL::GetRequestFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamCloudsavingApi, PostDataDownloadURL);
}

FName UK2BeamNode_ApiRequest_PostDataDownloadURL::GetMakeFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UPostDataDownloadURLRequest, Make);
}

FString UK2BeamNode_ApiRequest_PostDataDownloadURL::GetServiceName() const
{
	return TEXT("Cloudsaving");
}

FString UK2BeamNode_ApiRequest_PostDataDownloadURL::GetEndpointName() const
{
	return TEXT("PostDataDownloadURL");
}

UClass* UK2BeamNode_ApiRequest_PostDataDownloadURL::GetApiClass() const
{
	return UBeamCloudsavingApi::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_PostDataDownloadURL::GetRequestClass() const
{
	return UPostDataDownloadURLRequest::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_PostDataDownloadURL::GetResponseClass() const
{
	return UURLSResponse::StaticClass();
}

FString UK2BeamNode_ApiRequest_PostDataDownloadURL::GetRequestSuccessDelegateName() const
{
	return TEXT("OnPostDataDownloadURLSuccess");
}

FString UK2BeamNode_ApiRequest_PostDataDownloadURL::GetRequestErrorDelegateName() const
{
	return TEXT("OnPostDataDownloadURLError");
}

FString UK2BeamNode_ApiRequest_PostDataDownloadURL::GetRequestCompleteDelegateName() const
{
	return TEXT("OnPostDataDownloadURLComplete");
}

#undef LOCTEXT_NAMESPACE
