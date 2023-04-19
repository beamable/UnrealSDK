

#include "BeamableCoreBlueprintNodes/Public/BeamFlow/ApiRequest/AutoGen/Tournaments/K2BeamNode_ApiRequest_GetGlobal.h"

#include "BeamK2.h"

#include "BeamableCore/Public/AutoGen/SubSystems/BeamTournamentsApi.h"
#include "BeamableCore/Public/AutoGen/SubSystems/Tournaments/GetGlobalRequest.h"
#include "BeamableCore/Public/AutoGen/GetStandingsResponse.h"

#define LOCTEXT_NAMESPACE "K2BeamNode_ApiRequest_GetGlobal"

using namespace BeamK2;

FName UK2BeamNode_ApiRequest_GetGlobal::GetSelfFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamTournamentsApi, GetSelf);
}

FName UK2BeamNode_ApiRequest_GetGlobal::GetRequestFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamTournamentsApi, GetGlobal);
}

FName UK2BeamNode_ApiRequest_GetGlobal::GetMakeFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UGetGlobalRequest, Make);
}

FString UK2BeamNode_ApiRequest_GetGlobal::GetServiceName() const
{
	return TEXT("Tournaments");
}

FString UK2BeamNode_ApiRequest_GetGlobal::GetEndpointName() const
{
	return TEXT("GetGlobal");
}

UClass* UK2BeamNode_ApiRequest_GetGlobal::GetApiClass() const
{
	return UBeamTournamentsApi::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_GetGlobal::GetRequestClass() const
{
	return UGetGlobalRequest::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_GetGlobal::GetResponseClass() const
{
	return UGetStandingsResponse::StaticClass();
}

FString UK2BeamNode_ApiRequest_GetGlobal::GetRequestSuccessDelegateName() const
{
	return TEXT("OnGetGlobalSuccess");
}

FString UK2BeamNode_ApiRequest_GetGlobal::GetRequestErrorDelegateName() const
{
	return TEXT("OnGetGlobalError");
}

FString UK2BeamNode_ApiRequest_GetGlobal::GetRequestCompleteDelegateName() const
{
	return TEXT("OnGetGlobalComplete");
}

#undef LOCTEXT_NAMESPACE
