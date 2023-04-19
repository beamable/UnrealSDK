

#include "BeamableCoreBlueprintNodes/Public/BeamFlow/ApiRequest/AutoGen/Tournaments/K2BeamNode_ApiRequest_BasicTournamentsGetGroups.h"

#include "BeamK2.h"

#include "BeamableCore/Public/AutoGen/SubSystems/BeamTournamentsApi.h"
#include "BeamableCore/Public/AutoGen/SubSystems/Tournaments/BasicTournamentsGetGroupsRequest.h"
#include "BeamableCore/Public/AutoGen/GetGroupsResponse.h"

#define LOCTEXT_NAMESPACE "K2BeamNode_ApiRequest_BasicTournamentsGetGroups"

using namespace BeamK2;

FName UK2BeamNode_ApiRequest_BasicTournamentsGetGroups::GetSelfFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamTournamentsApi, GetSelf);
}

FName UK2BeamNode_ApiRequest_BasicTournamentsGetGroups::GetRequestFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamTournamentsApi, GetGroups);
}

FName UK2BeamNode_ApiRequest_BasicTournamentsGetGroups::GetMakeFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBasicTournamentsGetGroupsRequest, Make);
}

FString UK2BeamNode_ApiRequest_BasicTournamentsGetGroups::GetServiceName() const
{
	return TEXT("Tournaments");
}

FString UK2BeamNode_ApiRequest_BasicTournamentsGetGroups::GetEndpointName() const
{
	return TEXT("GetGroups");
}

UClass* UK2BeamNode_ApiRequest_BasicTournamentsGetGroups::GetApiClass() const
{
	return UBeamTournamentsApi::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_BasicTournamentsGetGroups::GetRequestClass() const
{
	return UBasicTournamentsGetGroupsRequest::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_BasicTournamentsGetGroups::GetResponseClass() const
{
	return UGetGroupsResponse::StaticClass();
}

FString UK2BeamNode_ApiRequest_BasicTournamentsGetGroups::GetRequestSuccessDelegateName() const
{
	return TEXT("OnBasicTournamentsGetGroupsSuccess");
}

FString UK2BeamNode_ApiRequest_BasicTournamentsGetGroups::GetRequestErrorDelegateName() const
{
	return TEXT("OnBasicTournamentsGetGroupsError");
}

FString UK2BeamNode_ApiRequest_BasicTournamentsGetGroups::GetRequestCompleteDelegateName() const
{
	return TEXT("OnBasicTournamentsGetGroupsComplete");
}

#undef LOCTEXT_NAMESPACE
