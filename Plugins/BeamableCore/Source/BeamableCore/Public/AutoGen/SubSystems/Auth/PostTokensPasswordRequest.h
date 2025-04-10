
#pragma once

#include "CoreMinimal.h"
#include "BeamBackend/BeamBaseRequestInterface.h"
#include "BeamBackend/BeamRequestContext.h"
#include "BeamBackend/BeamErrorResponse.h"
#include "BeamBackend/BeamFullResponse.h"

#include "BeamableCore/Public/AutoGen/PasswordAuthRequestBody.h"
#include "BeamableCore/Public/AutoGen/AuthResponse.h"

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
	UPasswordAuthRequestBody* Body = {};

	// Beam Base Request Declaration
	UPostTokensPasswordRequest() = default;

	virtual void BuildVerb(FString& VerbString) const override;
	virtual void BuildRoute(FString& RouteString) const override;
	virtual void BuildBody(FString& BodyString) const override;

	UFUNCTION(BlueprintPure, BlueprintInternalUseOnly, Category="Beam|Auth|Utils|Make/Break", DisplayName="Make PostTokensPassword",  meta=(DefaultToSelf="RequestOwner", AdvancedDisplay="_Email,_Password,_Scope,_CustomerId,_RealmId,_Context,RequestOwner", AutoCreateRefTerm="CustomHeaders"))
	static UPostTokensPasswordRequest* Make(FOptionalString _Email, FOptionalString _Password, FOptionalString _Scope, FOptionalBeamCid _CustomerId, FOptionalBeamPid _RealmId, FOptionalContextInfo _Context, UObject* RequestOwner, TMap<FString, FString> CustomHeaders);
};

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnPostTokensPasswordSuccess, FBeamRequestContext, Context, UPostTokensPasswordRequest*, Request, UAuthResponse*, Response);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnPostTokensPasswordError, FBeamRequestContext, Context, UPostTokensPasswordRequest*, Request, FBeamErrorResponse, Error);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnPostTokensPasswordComplete, FBeamRequestContext, Context, UPostTokensPasswordRequest*, Request);

using FPostTokensPasswordFullResponse = FBeamFullResponse<UPostTokensPasswordRequest*, UAuthResponse*>;
DECLARE_DELEGATE_OneParam(FOnPostTokensPasswordFullResponse, FPostTokensPasswordFullResponse);
