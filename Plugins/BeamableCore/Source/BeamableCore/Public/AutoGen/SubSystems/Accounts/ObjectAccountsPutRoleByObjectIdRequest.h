
#pragma once

#include "CoreMinimal.h"
#include "BeamBackend/BeamBaseRequestInterface.h"
#include "BeamBackend/BeamRequestContext.h"
#include "BeamBackend/BeamErrorResponse.h"
#include "BeamBackend/BeamFullResponse.h"

#include "BeamBackend/SemanticTypes/BeamAccountId.h"
#include "BeamableCore/Public/AutoGen/UpdateRole.h"
#include "BeamableCore/Public/AutoGen/EmptyResponse.h"

#include "ObjectAccountsPutRoleByObjectIdRequest.generated.h"

UCLASS(BlueprintType)
class BEAMABLECORE_API UObjectAccountsPutRoleByObjectIdRequest : public UObject, public IBeamBaseRequestInterface
{
	GENERATED_BODY()
	
public:

	// Path Params
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Object Id", Category="Beam")
	FBeamAccountId ObjectId = {};
	
	// Query Params
	

	// Body Params
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="", Category="Beam")
	UUpdateRole* Body = {};

	// Beam Base Request Declaration
	UObjectAccountsPutRoleByObjectIdRequest() = default;

	virtual void BuildVerb(FString& VerbString) const override;
	virtual void BuildRoute(FString& RouteString) const override;
	virtual void BuildBody(FString& BodyString) const override;

	UFUNCTION(BlueprintPure, BlueprintInternalUseOnly, Category="Beam|Accounts|Utils|Make/Break", DisplayName="Make ObjectAccountsPutRoleByObjectId",  meta=(DefaultToSelf="RequestOwner", AdvancedDisplay="_Cid,_Realm,_Role,RequestOwner", AutoCreateRefTerm="CustomHeaders"))
	static UObjectAccountsPutRoleByObjectIdRequest* Make(FBeamAccountId _ObjectId, FOptionalBeamCid _Cid, FOptionalBeamPid _Realm, FOptionalString _Role, UObject* RequestOwner, TMap<FString, FString> CustomHeaders);
};

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnObjectAccountsPutRoleByObjectIdSuccess, FBeamRequestContext, Context, UObjectAccountsPutRoleByObjectIdRequest*, Request, UEmptyResponse*, Response);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnObjectAccountsPutRoleByObjectIdError, FBeamRequestContext, Context, UObjectAccountsPutRoleByObjectIdRequest*, Request, FBeamErrorResponse, Error);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnObjectAccountsPutRoleByObjectIdComplete, FBeamRequestContext, Context, UObjectAccountsPutRoleByObjectIdRequest*, Request);

using FObjectAccountsPutRoleByObjectIdFullResponse = FBeamFullResponse<UObjectAccountsPutRoleByObjectIdRequest*, UEmptyResponse*>;
DECLARE_DELEGATE_OneParam(FOnObjectAccountsPutRoleByObjectIdFullResponse, FObjectAccountsPutRoleByObjectIdFullResponse);
