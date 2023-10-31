

#include "BeamableCoreBlueprintNodes/Public/BeamFlow/ApiRequest/AutoGen/Beamo/K2BeamNode_ApiRequest_PostImageUrls.h"

#include "BeamK2.h"

#include "BeamableCore/Public/AutoGen/SubSystems/BeamBeamoApi.h"
#include "BeamableCore/Public/AutoGen/SubSystems/Beamo/PostImageUrlsRequest.h"
#include "BeamableCore/Public/AutoGen/PreSignedUrlsResponse.h"

#define LOCTEXT_NAMESPACE "K2BeamNode_ApiRequest_PostImageUrls"

using namespace BeamK2;

FName UK2BeamNode_ApiRequest_PostImageUrls::GetSelfFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamBeamoApi, GetSelf);
}

FName UK2BeamNode_ApiRequest_PostImageUrls::GetRequestFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamBeamoApi, PostImageUrls);
}

FName UK2BeamNode_ApiRequest_PostImageUrls::GetMakeFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UPostImageUrlsRequest, Make);
}

FString UK2BeamNode_ApiRequest_PostImageUrls::GetServiceName() const
{
	return TEXT("Beamo");
}

FString UK2BeamNode_ApiRequest_PostImageUrls::GetEndpointName() const
{
	return TEXT("PostImageUrls");
}

UClass* UK2BeamNode_ApiRequest_PostImageUrls::GetApiClass() const
{
	return UBeamBeamoApi::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_PostImageUrls::GetRequestClass() const
{
	return UPostImageUrlsRequest::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_PostImageUrls::GetResponseClass() const
{
	return UPreSignedUrlsResponse::StaticClass();
}

FString UK2BeamNode_ApiRequest_PostImageUrls::GetRequestSuccessDelegateName() const
{
	return TEXT("OnPostImageUrlsSuccess");
}

FString UK2BeamNode_ApiRequest_PostImageUrls::GetRequestErrorDelegateName() const
{
	return TEXT("OnPostImageUrlsError");
}

FString UK2BeamNode_ApiRequest_PostImageUrls::GetRequestCompleteDelegateName() const
{
	return TEXT("OnPostImageUrlsComplete");
}

#undef LOCTEXT_NAMESPACE
