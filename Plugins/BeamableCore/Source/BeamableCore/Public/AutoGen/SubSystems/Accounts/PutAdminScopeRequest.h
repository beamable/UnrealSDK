
#pragma once

#include "CoreMinimal.h"
#include "BeamBackend/BeamBaseRequestInterface.h"
#include "BeamBackend/BeamRequestContext.h"
#include "BeamBackend/BeamErrorResponse.h"
#include "BeamBackend/BeamFullResponse.h"

#include "BeamBackend/SemanticTypes/BeamAccountId.h"
#include "BeamableCore/Public/AutoGen/UpdateRole.h"
#include "BeamableCore/Public/AutoGen/EmptyResponse.h"

#include "PutAdminScopeRequest.generated.h"

UCLASS(BlueprintType)
class BEAMABLECORE_API UPutAdminScopeRequest : public UObject, public IBeamBaseRequestInterface
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
	UPutAdminScopeRequest() = default;

	virtual void BuildVerb(FString& VerbString) const override;
	virtual void BuildRoute(FString& RouteString) const override;
	virtual void BuildBody(FString& BodyString) const override;

	UFUNCTION(BlueprintPure, BlueprintInternalUseOnly, Category="Beam|Accounts|Utils|Make/Break", DisplayName="Make PutAdminScope",  meta=(DefaultToSelf="RequestOwner", AdvancedDisplay="_Cid,_Realm,_Role,RequestOwner", AutoCreateRefTerm="CustomHeaders"))
	static UPutAdminScopeRequest* Make(FBeamAccountId _ObjectId, FOptionalBeamCid _Cid, FOptionalBeamPid _Realm, FOptionalString _Role, UObject* RequestOwner, TMap<FString, FString> CustomHeaders);
};

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnPutAdminScopeSuccess, FBeamRequestContext, Context, UPutAdminScopeRequest*, Request, UEmptyResponse*, Response);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnPutAdminScopeError, FBeamRequestContext, Context, UPutAdminScopeRequest*, Request, FBeamErrorResponse, Error);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnPutAdminScopeComplete, FBeamRequestContext, Context, UPutAdminScopeRequest*, Request);

using FPutAdminScopeFullResponse = FBeamFullResponse<UPutAdminScopeRequest*, UEmptyResponse*>;
DECLARE_DELEGATE_OneParam(FOnPutAdminScopeFullResponse, FPutAdminScopeFullResponse);
