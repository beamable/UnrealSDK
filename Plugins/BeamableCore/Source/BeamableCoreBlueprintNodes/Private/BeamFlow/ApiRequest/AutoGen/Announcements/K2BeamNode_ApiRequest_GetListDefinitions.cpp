

#include "BeamableCoreBlueprintNodes/Public/BeamFlow/ApiRequest/AutoGen/Announcements/K2BeamNode_ApiRequest_GetListDefinitions.h"

#include "BeamK2.h"

#include "BeamableCore/Public/AutoGen/SubSystems/BeamAnnouncementsApi.h"
#include "BeamableCore/Public/AutoGen/SubSystems/Announcements/GetListDefinitionsRequest.h"
#include "BeamableCore/Public/AutoGen/ListDefinitionsResponse.h"

#define LOCTEXT_NAMESPACE "K2BeamNode_ApiRequest_GetListDefinitions"

using namespace BeamK2;

FName UK2BeamNode_ApiRequest_GetListDefinitions::GetSelfFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamAnnouncementsApi, GetSelf);
}

FName UK2BeamNode_ApiRequest_GetListDefinitions::GetRequestFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamAnnouncementsApi, GetListDefinitions);
}

FName UK2BeamNode_ApiRequest_GetListDefinitions::GetMakeFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UGetListDefinitionsRequest, Make);
}

FString UK2BeamNode_ApiRequest_GetListDefinitions::GetServiceName() const
{
	return TEXT("Announcements");
}

FString UK2BeamNode_ApiRequest_GetListDefinitions::GetEndpointName() const
{
	return TEXT("GetListDefinitions");
}

UClass* UK2BeamNode_ApiRequest_GetListDefinitions::GetApiClass() const
{
	return UBeamAnnouncementsApi::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_GetListDefinitions::GetRequestClass() const
{
	return UGetListDefinitionsRequest::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_GetListDefinitions::GetResponseClass() const
{
	return UListDefinitionsResponse::StaticClass();
}

FString UK2BeamNode_ApiRequest_GetListDefinitions::GetRequestSuccessDelegateName() const
{
	return TEXT("OnGetListDefinitionsSuccess");
}

FString UK2BeamNode_ApiRequest_GetListDefinitions::GetRequestErrorDelegateName() const
{
	return TEXT("OnGetListDefinitionsError");
}

FString UK2BeamNode_ApiRequest_GetListDefinitions::GetRequestCompleteDelegateName() const
{
	return TEXT("OnGetListDefinitionsComplete");
}

#undef LOCTEXT_NAMESPACE
