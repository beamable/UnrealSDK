

#include "BeamableCoreBlueprintNodes/Public/BeamFlow/ApiRequest/AutoGen/Tournaments/K2BeamNode_ApiRequest_GetChampions.h"

#include "BeamK2.h"

#include "BeamableCore/Public/AutoGen/SubSystems/BeamTournamentsApi.h"
#include "BeamableCore/Public/AutoGen/SubSystems/Tournaments/GetChampionsRequest.h"
#include "BeamableCore/Public/AutoGen/GetChampionsResponse.h"

#define LOCTEXT_NAMESPACE "K2BeamNode_ApiRequest_GetChampions"

using namespace BeamK2;

FName UK2BeamNode_ApiRequest_GetChampions::GetSelfFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamTournamentsApi, GetSelf);
}

FName UK2BeamNode_ApiRequest_GetChampions::GetRequestFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamTournamentsApi, GetChampions);
}

FName UK2BeamNode_ApiRequest_GetChampions::GetMakeFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UGetChampionsRequest, Make);
}

FString UK2BeamNode_ApiRequest_GetChampions::GetServiceName() const
{
	return TEXT("Tournaments");
}

FString UK2BeamNode_ApiRequest_GetChampions::GetEndpointName() const
{
	return TEXT("GetChampions");
}

UClass* UK2BeamNode_ApiRequest_GetChampions::GetApiClass() const
{
	return UBeamTournamentsApi::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_GetChampions::GetRequestClass() const
{
	return UGetChampionsRequest::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_GetChampions::GetResponseClass() const
{
	return UGetChampionsResponse::StaticClass();
}

FString UK2BeamNode_ApiRequest_GetChampions::GetRequestSuccessDelegateName() const
{
	return TEXT("OnGetChampionsSuccess");
}

FString UK2BeamNode_ApiRequest_GetChampions::GetRequestErrorDelegateName() const
{
	return TEXT("OnGetChampionsError");
}

FString UK2BeamNode_ApiRequest_GetChampions::GetRequestCompleteDelegateName() const
{
	return TEXT("OnGetChampionsComplete");
}

#undef LOCTEXT_NAMESPACE
