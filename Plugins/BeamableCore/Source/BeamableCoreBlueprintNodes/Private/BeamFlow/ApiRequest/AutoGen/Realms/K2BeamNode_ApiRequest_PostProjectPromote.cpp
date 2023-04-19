

#include "BeamableCoreBlueprintNodes/Public/BeamFlow/ApiRequest/AutoGen/Realms/K2BeamNode_ApiRequest_PostProjectPromote.h"

#include "BeamK2.h"

#include "BeamableCore/Public/AutoGen/SubSystems/BeamRealmsApi.h"
#include "BeamableCore/Public/AutoGen/SubSystems/Realms/PostProjectPromoteRequest.h"
#include "BeamableCore/Public/AutoGen/PromoteRealmResponseOld.h"

#define LOCTEXT_NAMESPACE "K2BeamNode_ApiRequest_PostProjectPromote"

using namespace BeamK2;

FName UK2BeamNode_ApiRequest_PostProjectPromote::GetSelfFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamRealmsApi, GetSelf);
}

FName UK2BeamNode_ApiRequest_PostProjectPromote::GetRequestFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamRealmsApi, PostProjectPromote);
}

FName UK2BeamNode_ApiRequest_PostProjectPromote::GetMakeFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UPostProjectPromoteRequest, Make);
}

FString UK2BeamNode_ApiRequest_PostProjectPromote::GetServiceName() const
{
	return TEXT("Realms");
}

FString UK2BeamNode_ApiRequest_PostProjectPromote::GetEndpointName() const
{
	return TEXT("PostProjectPromote");
}

UClass* UK2BeamNode_ApiRequest_PostProjectPromote::GetApiClass() const
{
	return UBeamRealmsApi::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_PostProjectPromote::GetRequestClass() const
{
	return UPostProjectPromoteRequest::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_PostProjectPromote::GetResponseClass() const
{
	return UPromoteRealmResponseOld::StaticClass();
}

FString UK2BeamNode_ApiRequest_PostProjectPromote::GetRequestSuccessDelegateName() const
{
	return TEXT("OnPostProjectPromoteSuccess");
}

FString UK2BeamNode_ApiRequest_PostProjectPromote::GetRequestErrorDelegateName() const
{
	return TEXT("OnPostProjectPromoteError");
}

FString UK2BeamNode_ApiRequest_PostProjectPromote::GetRequestCompleteDelegateName() const
{
	return TEXT("OnPostProjectPromoteComplete");
}

#undef LOCTEXT_NAMESPACE
