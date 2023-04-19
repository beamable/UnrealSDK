

#include "BeamableCoreBlueprintNodes/Public/BeamFlow/ApiRequest/AutoGen/Tournaments/K2BeamNode_ApiRequest_GetMeGroup.h"

#include "BeamK2.h"

#include "BeamableCore/Public/AutoGen/SubSystems/BeamTournamentsApi.h"
#include "BeamableCore/Public/AutoGen/SubSystems/Tournaments/GetMeGroupRequest.h"
#include "BeamableCore/Public/AutoGen/GetGroupStatusResponse.h"

#define LOCTEXT_NAMESPACE "K2BeamNode_ApiRequest_GetMeGroup"

using namespace BeamK2;

FName UK2BeamNode_ApiRequest_GetMeGroup::GetSelfFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamTournamentsApi, GetSelf);
}

FName UK2BeamNode_ApiRequest_GetMeGroup::GetRequestFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamTournamentsApi, GetMeGroup);
}

FName UK2BeamNode_ApiRequest_GetMeGroup::GetMakeFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UGetMeGroupRequest, Make);
}

FString UK2BeamNode_ApiRequest_GetMeGroup::GetServiceName() const
{
	return TEXT("Tournaments");
}

FString UK2BeamNode_ApiRequest_GetMeGroup::GetEndpointName() const
{
	return TEXT("GetMeGroup");
}

UClass* UK2BeamNode_ApiRequest_GetMeGroup::GetApiClass() const
{
	return UBeamTournamentsApi::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_GetMeGroup::GetRequestClass() const
{
	return UGetMeGroupRequest::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_GetMeGroup::GetResponseClass() const
{
	return UGetGroupStatusResponse::StaticClass();
}

FString UK2BeamNode_ApiRequest_GetMeGroup::GetRequestSuccessDelegateName() const
{
	return TEXT("OnGetMeGroupSuccess");
}

FString UK2BeamNode_ApiRequest_GetMeGroup::GetRequestErrorDelegateName() const
{
	return TEXT("OnGetMeGroupError");
}

FString UK2BeamNode_ApiRequest_GetMeGroup::GetRequestCompleteDelegateName() const
{
	return TEXT("OnGetMeGroupComplete");
}

#undef LOCTEXT_NAMESPACE
