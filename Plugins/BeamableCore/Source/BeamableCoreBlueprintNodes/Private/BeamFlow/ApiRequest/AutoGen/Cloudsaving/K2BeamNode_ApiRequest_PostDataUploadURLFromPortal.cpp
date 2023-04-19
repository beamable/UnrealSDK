

#include "BeamableCoreBlueprintNodes/Public/BeamFlow/ApiRequest/AutoGen/Cloudsaving/K2BeamNode_ApiRequest_PostDataUploadURLFromPortal.h"

#include "BeamK2.h"

#include "BeamableCore/Public/AutoGen/SubSystems/BeamCloudsavingApi.h"
#include "BeamableCore/Public/AutoGen/SubSystems/Cloudsaving/PostDataUploadURLFromPortalRequest.h"
#include "BeamableCore/Public/AutoGen/URLSResponse.h"

#define LOCTEXT_NAMESPACE "K2BeamNode_ApiRequest_PostDataUploadURLFromPortal"

using namespace BeamK2;

FName UK2BeamNode_ApiRequest_PostDataUploadURLFromPortal::GetSelfFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamCloudsavingApi, GetSelf);
}

FName UK2BeamNode_ApiRequest_PostDataUploadURLFromPortal::GetRequestFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamCloudsavingApi, PostDataUploadURLFromPortal);
}

FName UK2BeamNode_ApiRequest_PostDataUploadURLFromPortal::GetMakeFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UPostDataUploadURLFromPortalRequest, Make);
}

FString UK2BeamNode_ApiRequest_PostDataUploadURLFromPortal::GetServiceName() const
{
	return TEXT("Cloudsaving");
}

FString UK2BeamNode_ApiRequest_PostDataUploadURLFromPortal::GetEndpointName() const
{
	return TEXT("PostDataUploadURLFromPortal");
}

UClass* UK2BeamNode_ApiRequest_PostDataUploadURLFromPortal::GetApiClass() const
{
	return UBeamCloudsavingApi::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_PostDataUploadURLFromPortal::GetRequestClass() const
{
	return UPostDataUploadURLFromPortalRequest::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_PostDataUploadURLFromPortal::GetResponseClass() const
{
	return UURLSResponse::StaticClass();
}

FString UK2BeamNode_ApiRequest_PostDataUploadURLFromPortal::GetRequestSuccessDelegateName() const
{
	return TEXT("OnPostDataUploadURLFromPortalSuccess");
}

FString UK2BeamNode_ApiRequest_PostDataUploadURLFromPortal::GetRequestErrorDelegateName() const
{
	return TEXT("OnPostDataUploadURLFromPortalError");
}

FString UK2BeamNode_ApiRequest_PostDataUploadURLFromPortal::GetRequestCompleteDelegateName() const
{
	return TEXT("OnPostDataUploadURLFromPortalComplete");
}

#undef LOCTEXT_NAMESPACE
