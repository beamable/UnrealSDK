
#pragma once

#include "CoreMinimal.h"
#include "BeamBackend/BeamBaseRequestInterface.h"
#include "BeamBackend/BeamRequestContext.h"
#include "BeamBackend/BeamErrorResponse.h"
#include "BeamBackend/BeamFullResponse.h"

#include "BeamableCore/Public/AutoGen/AuthV2PasswordAuthRequestBody.h"
#include "BeamableCore/Public/AutoGen/AuthV2AuthResponse.h"

#include "PostTokensPasswordRequest.generated.h"

UCLASS(BlueprintType)
class BEAMABLECORE_API UPostTokensPasswordRequest : public UObject, public IBeamBaseRequestInterface
{
	GENERATED_BODY()
	
public:

	// Path Params
	
	
	// Query Params
	

	// Body Params
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="", Category="Beam")
	UAuthV2PasswordAuthRequestBody* Body = {};

	// Beam Base Request Declaration
	UPostTokensPasswordRequest() = default;

	virtual void BuildVerb(FString& VerbString) const override;
	virtual void BuildRoute(FString& RouteString) const override;
	virtual void BuildBody(FString& BodyString) const override;

	UFUNCTION(BlueprintPure, BlueprintInternalUseOnly, Category="Beam|Auth|Utils|Make/Break", DisplayName="Make PostTokensPassword",  meta=(DefaultToSelf="RequestOwner", AdvancedDisplay="_Email,_Password,_Scope,_CustomerId,_RealmId,_Context,RequestOwner", AutoCreateRefTerm="CustomHeaders"))
	static UPostTokensPasswordRequest* Make(FOptionalString _Email, FOptionalString _Password, FOptionalString _Scope, FOptionalBeamCid _CustomerId, FOptionalBeamPid _RealmId, FOptionalAuthV2ContextInfo _Context, UObject* RequestOwner, TMap<FString, FString> CustomHeaders);
};

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnPostTokensPasswordSuccess, FBeamRequestContext, Context, UPostTokensPasswordRequest*, Request, UAuthV2AuthResponse*, Response);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnPostTokensPasswordError, FBeamRequestContext, Context, UPostTokensPasswordRequest*, Request, FBeamErrorResponse, Error);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnPostTokensPasswordComplete, FBeamRequestContext, Context, UPostTokensPasswordRequest*, Request);

using FPostTokensPasswordFullResponse = FBeamFullResponse<UPostTokensPasswordRequest*, UAuthV2AuthResponse*>;
DECLARE_DELEGATE_OneParam(FOnPostTokensPasswordFullResponse, FPostTokensPasswordFullResponse);
