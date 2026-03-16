

#include "BeamableCoreBlueprintNodes/Public/BeamFlow/ApiRequest/AutoGen/Content/K2BeamNode_ApiRequest_PostBinaryPrivateUrls.h"

#include "BeamK2.h"

#include "BeamableCore/Public/AutoGen/SubSystems/BeamContentApi.h"
#include "BeamableCore/Public/AutoGen/SubSystems/Content/PostBinaryPrivateUrlsRequest.h"
#include "BeamableCore/Public/AutoGen/GetBinaryDownloadUrlsResponse.h"

#define LOCTEXT_NAMESPACE "K2BeamNode_ApiRequest_PostBinaryPrivateUrls"

using namespace BeamK2;

FName UK2BeamNode_ApiRequest_PostBinaryPrivateUrls::GetSelfFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamContentApi, GetSelf);
}

FName UK2BeamNode_ApiRequest_PostBinaryPrivateUrls::GetRequestFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamContentApi, PostBinaryPrivateUrls);
}

FName UK2BeamNode_ApiRequest_PostBinaryPrivateUrls::GetMakeFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UPostBinaryPrivateUrlsRequest, Make);
}

FString UK2BeamNode_ApiRequest_PostBinaryPrivateUrls::GetServiceName() const
{
	return TEXT("Content");
}

FString UK2BeamNode_ApiRequest_PostBinaryPrivateUrls::GetEndpointName() const
{
	return TEXT("PostBinaryPrivateUrls");
}

UClass* UK2BeamNode_ApiRequest_PostBinaryPrivateUrls::GetApiClass() const
{
	return UBeamContentApi::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_PostBinaryPrivateUrls::GetRequestClass() const
{
	return UPostBinaryPrivateUrlsRequest::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_PostBinaryPrivateUrls::GetResponseClass() const
{
	return UGetBinaryDownloadUrlsResponse::StaticClass();
}

FString UK2BeamNode_ApiRequest_PostBinaryPrivateUrls::GetRequestSuccessDelegateName() const
{
	return TEXT("OnPostBinaryPrivateUrlsSuccess");
}

FString UK2BeamNode_ApiRequest_PostBinaryPrivateUrls::GetRequestErrorDelegateName() const
{
	return TEXT("OnPostBinaryPrivateUrlsError");
}

FString UK2BeamNode_ApiRequest_PostBinaryPrivateUrls::GetRequestCompleteDelegateName() const
{
	return TEXT("OnPostBinaryPrivateUrlsComplete");
}

#undef LOCTEXT_NAMESPACE
