

#include "BeamableCoreBlueprintNodes/Public/BeamFlow/ApiRequest/AutoGen/Cloudsaving/K2BeamNode_ApiRequest_PostDataDownloadURLFromPortal.h"

#include "BeamK2.h"

#include "BeamableCore/Public/AutoGen/SubSystems/BeamCloudsavingApi.h"
#include "BeamableCore/Public/AutoGen/SubSystems/Cloudsaving/PostDataDownloadURLFromPortalRequest.h"
#include "BeamableCore/Public/AutoGen/URLSResponse.h"

#define LOCTEXT_NAMESPACE "K2BeamNode_ApiRequest_PostDataDownloadURLFromPortal"

using namespace BeamK2;

FName UK2BeamNode_ApiRequest_PostDataDownloadURLFromPortal::GetSelfFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamCloudsavingApi, GetSelf);
}

FName UK2BeamNode_ApiRequest_PostDataDownloadURLFromPortal::GetRequestFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamCloudsavingApi, PostDataDownloadURLFromPortal);
}

FName UK2BeamNode_ApiRequest_PostDataDownloadURLFromPortal::GetMakeFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UPostDataDownloadURLFromPortalRequest, Make);
}

FString UK2BeamNode_ApiRequest_PostDataDownloadURLFromPortal::GetServiceName() const
{
	return TEXT("Cloudsaving");
}

FString UK2BeamNode_ApiRequest_PostDataDownloadURLFromPortal::GetEndpointName() const
{
	return TEXT("PostDataDownloadURLFromPortal");
}

UClass* UK2BeamNode_ApiRequest_PostDataDownloadURLFromPortal::GetApiClass() const
{
	return UBeamCloudsavingApi::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_PostDataDownloadURLFromPortal::GetRequestClass() const
{
	return UPostDataDownloadURLFromPortalRequest::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_PostDataDownloadURLFromPortal::GetResponseClass() const
{
	return UURLSResponse::StaticClass();
}

FString UK2BeamNode_ApiRequest_PostDataDownloadURLFromPortal::GetRequestSuccessDelegateName() const
{
	return TEXT("OnPostDataDownloadURLFromPortalSuccess");
}

FString UK2BeamNode_ApiRequest_PostDataDownloadURLFromPortal::GetRequestErrorDelegateName() const
{
	return TEXT("OnPostDataDownloadURLFromPortalError");
}

FString UK2BeamNode_ApiRequest_PostDataDownloadURLFromPortal::GetRequestCompleteDelegateName() const
{
	return TEXT("OnPostDataDownloadURLFromPortalComplete");
}

#undef LOCTEXT_NAMESPACE
