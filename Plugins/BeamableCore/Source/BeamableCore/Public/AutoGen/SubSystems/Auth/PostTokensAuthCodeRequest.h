
#pragma once

#include "CoreMinimal.h"
#include "BeamBackend/BeamBaseRequestInterface.h"
#include "BeamBackend/BeamRequestContext.h"
#include "BeamBackend/BeamErrorResponse.h"
#include "BeamBackend/BeamFullResponse.h"

#include "BeamableCore/Public/AutoGen/AuthV2AuthorizationCodeAuthRequestBody.h"
#include "BeamableCore/Public/AutoGen/AuthV2AuthResponse.h"

#include "PostTokensAuthCodeRequest.generated.h"

UCLASS(BlueprintType)
class BEAMABLECORE_API UPostTokensAuthCodeRequest : public UObject, public IBeamBaseRequestInterface
{
	GENERATED_BODY()
	
public:

	// Path Params
	
	
	// Query Params
	

	// Body Params
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="", Category="Beam")
	UAuthV2AuthorizationCodeAuthRequestBody* Body = {};

	// Beam Base Request Declaration
	UPostTokensAuthCodeRequest() = default;

	virtual void BuildVerb(FString& VerbString) const override;
	virtual void BuildRoute(FString& RouteString) const override;
	virtual void BuildBody(FString& BodyString) const override;

	UFUNCTION(BlueprintPure, BlueprintInternalUseOnly, Category="Beam|Auth|Utils|Make/Break", DisplayName="Make PostTokensAuthCode",  meta=(DefaultToSelf="RequestOwner", AdvancedDisplay="_ClientId,_Code,_RedirectUri,_Scope,_CustomerId,_RealmId,_Context,RequestOwner", AutoCreateRefTerm="CustomHeaders"))
	static UPostTokensAuthCodeRequest* Make(FOptionalString _ClientId, FOptionalString _Code, FOptionalString _RedirectUri, FOptionalString _Scope, FOptionalBeamCid _CustomerId, FOptionalBeamPid _RealmId, FOptionalAuthV2ContextInfo _Context, UObject* RequestOwner, TMap<FString, FString> CustomHeaders);
};

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnPostTokensAuthCodeSuccess, FBeamRequestContext, Context, UPostTokensAuthCodeRequest*, Request, UAuthV2AuthResponse*, Response);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnPostTokensAuthCodeError, FBeamRequestContext, Context, UPostTokensAuthCodeRequest*, Request, FBeamErrorResponse, Error);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnPostTokensAuthCodeComplete, FBeamRequestContext, Context, UPostTokensAuthCodeRequest*, Request);

using FPostTokensAuthCodeFullResponse = FBeamFullResponse<UPostTokensAuthCodeRequest*, UAuthV2AuthResponse*>;
DECLARE_DELEGATE_OneParam(FOnPostTokensAuthCodeFullResponse, FPostTokensAuthCodeFullResponse);
