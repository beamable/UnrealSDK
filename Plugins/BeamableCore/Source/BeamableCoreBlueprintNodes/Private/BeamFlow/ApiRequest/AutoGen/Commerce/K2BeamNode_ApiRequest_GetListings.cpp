

#include "BeamableCoreBlueprintNodes/Public/BeamFlow/ApiRequest/AutoGen/Commerce/K2BeamNode_ApiRequest_GetListings.h"

#include "BeamK2.h"

#include "BeamableCore/Public/AutoGen/SubSystems/BeamCommerceApi.h"
#include "BeamableCore/Public/AutoGen/SubSystems/Commerce/GetListingsRequest.h"
#include "BeamableCore/Public/AutoGen/ActiveListingResponse.h"

#define LOCTEXT_NAMESPACE "K2BeamNode_ApiRequest_GetListings"

using namespace BeamK2;

FName UK2BeamNode_ApiRequest_GetListings::GetSelfFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamCommerceApi, GetSelf);
}

FName UK2BeamNode_ApiRequest_GetListings::GetRequestFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamCommerceApi, GetListings);
}

FName UK2BeamNode_ApiRequest_GetListings::GetMakeFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UGetListingsRequest, Make);
}

FString UK2BeamNode_ApiRequest_GetListings::GetServiceName() const
{
	return TEXT("Commerce");
}

FString UK2BeamNode_ApiRequest_GetListings::GetEndpointName() const
{
	return TEXT("GetListings");
}

UClass* UK2BeamNode_ApiRequest_GetListings::GetApiClass() const
{
	return UBeamCommerceApi::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_GetListings::GetRequestClass() const
{
	return UGetListingsRequest::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_GetListings::GetResponseClass() const
{
	return UActiveListingResponse::StaticClass();
}

FString UK2BeamNode_ApiRequest_GetListings::GetRequestSuccessDelegateName() const
{
	return TEXT("OnGetListingsSuccess");
}

FString UK2BeamNode_ApiRequest_GetListings::GetRequestErrorDelegateName() const
{
	return TEXT("OnGetListingsError");
}

FString UK2BeamNode_ApiRequest_GetListings::GetRequestCompleteDelegateName() const
{
	return TEXT("OnGetListingsComplete");
}

#undef LOCTEXT_NAMESPACE
