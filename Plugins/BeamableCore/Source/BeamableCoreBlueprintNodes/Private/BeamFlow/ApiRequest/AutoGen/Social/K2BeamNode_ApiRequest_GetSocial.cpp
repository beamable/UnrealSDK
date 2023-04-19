

#include "BeamableCoreBlueprintNodes/Public/BeamFlow/ApiRequest/AutoGen/Social/K2BeamNode_ApiRequest_GetSocial.h"

#include "BeamK2.h"

#include "BeamableCore/Public/AutoGen/SubSystems/BeamSocialApi.h"
#include "BeamableCore/Public/AutoGen/SubSystems/Social/GetSocialRequest.h"
#include "BeamableCore/Public/AutoGen/GetSocialStatusesResponse.h"

#define LOCTEXT_NAMESPACE "K2BeamNode_ApiRequest_GetSocial"

using namespace BeamK2;

FName UK2BeamNode_ApiRequest_GetSocial::GetSelfFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamSocialApi, GetSelf);
}

FName UK2BeamNode_ApiRequest_GetSocial::GetRequestFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamSocialApi, GetSocial);
}

FName UK2BeamNode_ApiRequest_GetSocial::GetMakeFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UGetSocialRequest, Make);
}

FString UK2BeamNode_ApiRequest_GetSocial::GetServiceName() const
{
	return TEXT("Social");
}

FString UK2BeamNode_ApiRequest_GetSocial::GetEndpointName() const
{
	return TEXT("GetSocial");
}

UClass* UK2BeamNode_ApiRequest_GetSocial::GetApiClass() const
{
	return UBeamSocialApi::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_GetSocial::GetRequestClass() const
{
	return UGetSocialRequest::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_GetSocial::GetResponseClass() const
{
	return UGetSocialStatusesResponse::StaticClass();
}

FString UK2BeamNode_ApiRequest_GetSocial::GetRequestSuccessDelegateName() const
{
	return TEXT("OnGetSocialSuccess");
}

FString UK2BeamNode_ApiRequest_GetSocial::GetRequestErrorDelegateName() const
{
	return TEXT("OnGetSocialError");
}

FString UK2BeamNode_ApiRequest_GetSocial::GetRequestCompleteDelegateName() const
{
	return TEXT("OnGetSocialComplete");
}

#undef LOCTEXT_NAMESPACE
