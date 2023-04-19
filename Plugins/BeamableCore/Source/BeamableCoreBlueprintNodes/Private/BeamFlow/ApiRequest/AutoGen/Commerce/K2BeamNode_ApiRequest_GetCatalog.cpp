

#include "BeamableCoreBlueprintNodes/Public/BeamFlow/ApiRequest/AutoGen/Commerce/K2BeamNode_ApiRequest_GetCatalog.h"

#include "BeamK2.h"

#include "BeamableCore/Public/AutoGen/SubSystems/BeamCommerceApi.h"
#include "BeamableCore/Public/AutoGen/SubSystems/Commerce/GetCatalogRequest.h"
#include "BeamableCore/Public/AutoGen/GetCatalogResponse.h"

#define LOCTEXT_NAMESPACE "K2BeamNode_ApiRequest_GetCatalog"

using namespace BeamK2;

FName UK2BeamNode_ApiRequest_GetCatalog::GetSelfFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamCommerceApi, GetSelf);
}

FName UK2BeamNode_ApiRequest_GetCatalog::GetRequestFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamCommerceApi, GetCatalog);
}

FName UK2BeamNode_ApiRequest_GetCatalog::GetMakeFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UGetCatalogRequest, Make);
}

FString UK2BeamNode_ApiRequest_GetCatalog::GetServiceName() const
{
	return TEXT("Commerce");
}

FString UK2BeamNode_ApiRequest_GetCatalog::GetEndpointName() const
{
	return TEXT("GetCatalog");
}

UClass* UK2BeamNode_ApiRequest_GetCatalog::GetApiClass() const
{
	return UBeamCommerceApi::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_GetCatalog::GetRequestClass() const
{
	return UGetCatalogRequest::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_GetCatalog::GetResponseClass() const
{
	return UGetCatalogResponse::StaticClass();
}

FString UK2BeamNode_ApiRequest_GetCatalog::GetRequestSuccessDelegateName() const
{
	return TEXT("OnGetCatalogSuccess");
}

FString UK2BeamNode_ApiRequest_GetCatalog::GetRequestErrorDelegateName() const
{
	return TEXT("OnGetCatalogError");
}

FString UK2BeamNode_ApiRequest_GetCatalog::GetRequestCompleteDelegateName() const
{
	return TEXT("OnGetCatalogComplete");
}

#undef LOCTEXT_NAMESPACE
