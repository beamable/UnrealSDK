

#include "BeamableCoreBlueprintNodes/Public/BeamFlow/ApiRequest/AutoGen/Mail/K2BeamNode_ApiRequest_ObjectMailPostSearchByObjectId.h"

#include "BeamK2.h"

#include "BeamableCore/Public/AutoGen/SubSystems/BeamMailApi.h"
#include "BeamableCore/Public/AutoGen/SubSystems/Mail/ObjectMailPostSearchByObjectIdRequest.h"
#include "BeamableCore/Public/AutoGen/MailSearchResponse.h"

#define LOCTEXT_NAMESPACE "K2BeamNode_ApiRequest_ObjectMailPostSearchByObjectId"

using namespace BeamK2;

FName UK2BeamNode_ApiRequest_ObjectMailPostSearchByObjectId::GetSelfFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamMailApi, GetSelf);
}

FName UK2BeamNode_ApiRequest_ObjectMailPostSearchByObjectId::GetRequestFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamMailApi, PostSearch);
}

FName UK2BeamNode_ApiRequest_ObjectMailPostSearchByObjectId::GetMakeFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UObjectMailPostSearchByObjectIdRequest, Make);
}

FString UK2BeamNode_ApiRequest_ObjectMailPostSearchByObjectId::GetServiceName() const
{
	return TEXT("Mail");
}

FString UK2BeamNode_ApiRequest_ObjectMailPostSearchByObjectId::GetEndpointName() const
{
	return TEXT("PostSearch");
}

UClass* UK2BeamNode_ApiRequest_ObjectMailPostSearchByObjectId::GetApiClass() const
{
	return UBeamMailApi::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_ObjectMailPostSearchByObjectId::GetRequestClass() const
{
	return UObjectMailPostSearchByObjectIdRequest::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_ObjectMailPostSearchByObjectId::GetResponseClass() const
{
	return UMailSearchResponse::StaticClass();
}

FString UK2BeamNode_ApiRequest_ObjectMailPostSearchByObjectId::GetRequestSuccessDelegateName() const
{
	return TEXT("OnObjectMailPostSearchByObjectIdSuccess");
}

FString UK2BeamNode_ApiRequest_ObjectMailPostSearchByObjectId::GetRequestErrorDelegateName() const
{
	return TEXT("OnObjectMailPostSearchByObjectIdError");
}

FString UK2BeamNode_ApiRequest_ObjectMailPostSearchByObjectId::GetRequestCompleteDelegateName() const
{
	return TEXT("OnObjectMailPostSearchByObjectIdComplete");
}

#undef LOCTEXT_NAMESPACE
