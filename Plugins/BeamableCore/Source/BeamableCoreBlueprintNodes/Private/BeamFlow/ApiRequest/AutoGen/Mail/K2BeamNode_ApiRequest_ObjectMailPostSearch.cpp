

#include "BeamableCoreBlueprintNodes/Public/BeamFlow/ApiRequest/AutoGen/Mail/K2BeamNode_ApiRequest_ObjectMailPostSearch.h"

#include "BeamK2.h"

#include "BeamableCore/Public/AutoGen/SubSystems/BeamMailApi.h"
#include "BeamableCore/Public/AutoGen/SubSystems/Mail/ObjectMailPostSearchRequest.h"
#include "BeamableCore/Public/AutoGen/MailSearchResponse.h"

#define LOCTEXT_NAMESPACE "K2BeamNode_ApiRequest_ObjectMailPostSearch"

using namespace BeamK2;

FName UK2BeamNode_ApiRequest_ObjectMailPostSearch::GetSelfFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamMailApi, GetSelf);
}

FName UK2BeamNode_ApiRequest_ObjectMailPostSearch::GetRequestFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamMailApi, PostSearch);
}

FName UK2BeamNode_ApiRequest_ObjectMailPostSearch::GetMakeFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UObjectMailPostSearchRequest, Make);
}

FString UK2BeamNode_ApiRequest_ObjectMailPostSearch::GetServiceName() const
{
	return TEXT("Mail");
}

FString UK2BeamNode_ApiRequest_ObjectMailPostSearch::GetEndpointName() const
{
	return TEXT("PostSearch");
}

UClass* UK2BeamNode_ApiRequest_ObjectMailPostSearch::GetApiClass() const
{
	return UBeamMailApi::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_ObjectMailPostSearch::GetRequestClass() const
{
	return UObjectMailPostSearchRequest::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_ObjectMailPostSearch::GetResponseClass() const
{
	return UMailSearchResponse::StaticClass();
}

FString UK2BeamNode_ApiRequest_ObjectMailPostSearch::GetRequestSuccessDelegateName() const
{
	return TEXT("OnObjectMailPostSearchSuccess");
}

FString UK2BeamNode_ApiRequest_ObjectMailPostSearch::GetRequestErrorDelegateName() const
{
	return TEXT("OnObjectMailPostSearchError");
}

FString UK2BeamNode_ApiRequest_ObjectMailPostSearch::GetRequestCompleteDelegateName() const
{
	return TEXT("OnObjectMailPostSearchComplete");
}

#undef LOCTEXT_NAMESPACE
