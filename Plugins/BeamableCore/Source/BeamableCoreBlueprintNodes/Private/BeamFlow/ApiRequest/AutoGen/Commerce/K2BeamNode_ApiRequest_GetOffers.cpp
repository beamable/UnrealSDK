

#include "BeamableCoreBlueprintNodes/Public/BeamFlow/ApiRequest/AutoGen/Commerce/K2BeamNode_ApiRequest_GetOffers.h"

#include "BeamK2.h"

#include "BeamableCore/Public/AutoGen/SubSystems/BeamCommerceApi.h"
#include "BeamableCore/Public/AutoGen/SubSystems/Commerce/GetOffersRequest.h"
#include "BeamableCore/Public/AutoGen/GetActiveOffersResponse.h"

#define LOCTEXT_NAMESPACE "K2BeamNode_ApiRequest_GetOffers"

using namespace BeamK2;

FName UK2BeamNode_ApiRequest_GetOffers::GetSelfFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamCommerceApi, GetSelf);
}

FName UK2BeamNode_ApiRequest_GetOffers::GetRequestFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamCommerceApi, GetOffers);
}

FName UK2BeamNode_ApiRequest_GetOffers::GetMakeFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UGetOffersRequest, Make);
}

FString UK2BeamNode_ApiRequest_GetOffers::GetServiceName() const
{
	return TEXT("Commerce");
}

FString UK2BeamNode_ApiRequest_GetOffers::GetEndpointName() const
{
	return TEXT("GetOffers");
}

UClass* UK2BeamNode_ApiRequest_GetOffers::GetApiClass() const
{
	return UBeamCommerceApi::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_GetOffers::GetRequestClass() const
{
	return UGetOffersRequest::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_GetOffers::GetResponseClass() const
{
	return UGetActiveOffersResponse::StaticClass();
}

FString UK2BeamNode_ApiRequest_GetOffers::GetRequestSuccessDelegateName() const
{
	return TEXT("OnGetOffersSuccess");
}

FString UK2BeamNode_ApiRequest_GetOffers::GetRequestErrorDelegateName() const
{
	return TEXT("OnGetOffersError");
}

FString UK2BeamNode_ApiRequest_GetOffers::GetRequestCompleteDelegateName() const
{
	return TEXT("OnGetOffersComplete");
}

#undef LOCTEXT_NAMESPACE
