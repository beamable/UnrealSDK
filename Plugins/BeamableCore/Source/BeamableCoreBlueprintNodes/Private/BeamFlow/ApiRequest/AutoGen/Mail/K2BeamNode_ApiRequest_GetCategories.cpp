

#include "BeamableCoreBlueprintNodes/Public/BeamFlow/ApiRequest/AutoGen/Mail/K2BeamNode_ApiRequest_GetCategories.h"

#include "BeamK2.h"

#include "BeamableCore/Public/AutoGen/SubSystems/BeamMailApi.h"
#include "BeamableCore/Public/AutoGen/SubSystems/Mail/GetCategoriesRequest.h"
#include "BeamableCore/Public/AutoGen/ListMailCategoriesResponse.h"

#define LOCTEXT_NAMESPACE "K2BeamNode_ApiRequest_GetCategories"

using namespace BeamK2;

FName UK2BeamNode_ApiRequest_GetCategories::GetSelfFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamMailApi, GetSelf);
}

FName UK2BeamNode_ApiRequest_GetCategories::GetRequestFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamMailApi, GetCategories);
}

FName UK2BeamNode_ApiRequest_GetCategories::GetMakeFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UGetCategoriesRequest, Make);
}

FString UK2BeamNode_ApiRequest_GetCategories::GetServiceName() const
{
	return TEXT("Mail");
}

FString UK2BeamNode_ApiRequest_GetCategories::GetEndpointName() const
{
	return TEXT("GetCategories");
}

UClass* UK2BeamNode_ApiRequest_GetCategories::GetApiClass() const
{
	return UBeamMailApi::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_GetCategories::GetRequestClass() const
{
	return UGetCategoriesRequest::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_GetCategories::GetResponseClass() const
{
	return UListMailCategoriesResponse::StaticClass();
}

FString UK2BeamNode_ApiRequest_GetCategories::GetRequestSuccessDelegateName() const
{
	return TEXT("OnGetCategoriesSuccess");
}

FString UK2BeamNode_ApiRequest_GetCategories::GetRequestErrorDelegateName() const
{
	return TEXT("OnGetCategoriesError");
}

FString UK2BeamNode_ApiRequest_GetCategories::GetRequestCompleteDelegateName() const
{
	return TEXT("OnGetCategoriesComplete");
}

#undef LOCTEXT_NAMESPACE
