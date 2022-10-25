

#include "BeamFlow/ApiRequest/AutoGen/Commerce/K2BeamNode_ApiRequest_PostCatalogLegacy.h"

#include "BeamK2.h"

#include "AutoGen/SubSystems/BeamCommerceApi.h"
#include "AutoGen/SubSystems/Commerce/PostCatalogLegacyRequest.h"
#include "AutoGen/ResultResponse.h"

#define LOCTEXT_NAMESPACE "K2BeamNode_ApiRequest_PostCatalogLegacy"

using namespace BeamK2;

FName UK2BeamNode_ApiRequest_PostCatalogLegacy::GetSelfFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamCommerceApi, GetSelf);
}

FName UK2BeamNode_ApiRequest_PostCatalogLegacy::GetRequestFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamCommerceApi, PostCatalogLegacy);
}

FName UK2BeamNode_ApiRequest_PostCatalogLegacy::GetMakeFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UPostCatalogLegacyRequest, Make);
}

FString UK2BeamNode_ApiRequest_PostCatalogLegacy::GetServiceName() const
{
	return TEXT("Commerce");
}

FString UK2BeamNode_ApiRequest_PostCatalogLegacy::GetEndpointName() const
{
	return TEXT("PostCatalogLegacy");
}

UClass* UK2BeamNode_ApiRequest_PostCatalogLegacy::GetApiClass() const
{
	return UBeamCommerceApi::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_PostCatalogLegacy::GetRequestClass() const
{
	return UPostCatalogLegacyRequest::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_PostCatalogLegacy::GetResponseClass() const
{
	return UResultResponse::StaticClass();
}

FString UK2BeamNode_ApiRequest_PostCatalogLegacy::GetRequestSuccessDelegateName() const
{
	return TEXT("OnPostCatalogLegacySuccess");
}

FString UK2BeamNode_ApiRequest_PostCatalogLegacy::GetRequestErrorDelegateName() const
{
	return TEXT("OnPostCatalogLegacyError");
}

FString UK2BeamNode_ApiRequest_PostCatalogLegacy::GetRequestCompleteDelegateName() const
{
	return TEXT("OnPostCatalogLegacyComplete");
}

#undef LOCTEXT_NAMESPACE
