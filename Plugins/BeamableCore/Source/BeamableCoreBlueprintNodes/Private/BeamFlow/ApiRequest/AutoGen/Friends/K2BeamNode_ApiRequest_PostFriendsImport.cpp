

#include "BeamableCoreBlueprintNodes/Public/BeamFlow/ApiRequest/AutoGen/Friends/K2BeamNode_ApiRequest_PostFriendsImport.h"

#include "BeamK2.h"

#include "BeamableCore/Public/AutoGen/SubSystems/BeamFriendsApi.h"
#include "BeamableCore/Public/AutoGen/SubSystems/Friends/PostFriendsImportRequest.h"
#include "BeamableCore/Public/AutoGen/EmptyResponse.h"

#define LOCTEXT_NAMESPACE "K2BeamNode_ApiRequest_PostFriendsImport"

using namespace BeamK2;

FName UK2BeamNode_ApiRequest_PostFriendsImport::GetSelfFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamFriendsApi, GetSelf);
}

FName UK2BeamNode_ApiRequest_PostFriendsImport::GetRequestFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UBeamFriendsApi, PostFriendsImport);
}

FName UK2BeamNode_ApiRequest_PostFriendsImport::GetMakeFunctionName() const
{
	return GET_FUNCTION_NAME_CHECKED(UPostFriendsImportRequest, Make);
}

FString UK2BeamNode_ApiRequest_PostFriendsImport::GetServiceName() const
{
	return TEXT("Friends");
}

FString UK2BeamNode_ApiRequest_PostFriendsImport::GetEndpointName() const
{
	return TEXT("PostFriendsImport");
}

UClass* UK2BeamNode_ApiRequest_PostFriendsImport::GetApiClass() const
{
	return UBeamFriendsApi::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_PostFriendsImport::GetRequestClass() const
{
	return UPostFriendsImportRequest::StaticClass();
}

UClass* UK2BeamNode_ApiRequest_PostFriendsImport::GetResponseClass() const
{
	return UEmptyResponse::StaticClass();
}

FString UK2BeamNode_ApiRequest_PostFriendsImport::GetRequestSuccessDelegateName() const
{
	return TEXT("OnPostFriendsImportSuccess");
}

FString UK2BeamNode_ApiRequest_PostFriendsImport::GetRequestErrorDelegateName() const
{
	return TEXT("OnPostFriendsImportError");
}

FString UK2BeamNode_ApiRequest_PostFriendsImport::GetRequestCompleteDelegateName() const
{
	return TEXT("OnPostFriendsImportComplete");
}

#undef LOCTEXT_NAMESPACE
