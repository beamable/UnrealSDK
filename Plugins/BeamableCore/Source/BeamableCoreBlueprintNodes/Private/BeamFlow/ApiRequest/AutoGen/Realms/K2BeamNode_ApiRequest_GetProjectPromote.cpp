

#include "BeamableCoreBlueprintNodes/Public/BeamFlow/ApiRequest/AutoGen/Realms/K2BeamNode_ApiRequest_GetProjectPromote.h"

#include "BeamK2.h"

#include "BeamableCore/Public/AutoGen/SubSystems/BeamRealmsApi.h"
#include "BeamableCore/Public/AutoGen/SubSystems/Realms/GetProjectPromoteRequest.h"
#include "BeamableCore/Public/AutoGen/PromoteRealmResponseOld.h"

#define LOCTEXT_NAMESPACE "K2BeamNode_ApiRequest_GetProjectPromote"

using namespace BeamK2;

FName UK2BeamNode_ApiRequest_GetProjectPromote::GetSelfFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamRealmsApi, GetSelf);
}

FName UK2BeamNode_ApiRequest_GetProjectPromote::GetRequestFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamRealmsApi, GetProjectPromote);
}

FName UK2BeamNode_ApiRequest_GetProjectPromote::GetMakeFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UGetProjectPromoteRequest, Make);
}

FString UK2BeamNode_ApiRequest_GetProjectPromote::GetServiceName() const
{
	return TEXT("Realms");
}

FString UK2BeamNode_ApiRequest_GetProjectPromote::GetEndpointName() const
{
	return TEXT("GetProjectPromote");
}

UClass* UK2BeamNode_ApiRequest_GetProjectPromote::GetApiClass() const
{
	return UBeamRealmsApi::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_GetProjectPromote::GetRequestClass() const
{
	return UGetProjectPromoteRequest::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_GetProjectPromote::GetResponseClass() const
{
	return UPromoteRealmResponseOld::StaticClass();
}

FString UK2BeamNode_ApiRequest_GetProjectPromote::GetRequestSuccessDelegateName() const
{
	return TEXT("OnGetProjectPromoteSuccess");
}

FString UK2BeamNode_ApiRequest_GetProjectPromote::GetRequestErrorDelegateName() const
{
	return TEXT("OnGetProjectPromoteError");
}

FString UK2BeamNode_ApiRequest_GetProjectPromote::GetRequestCompleteDelegateName() const
{
	return TEXT("OnGetProjectPromoteComplete");
}

#undef LOCTEXT_NAMESPACE
