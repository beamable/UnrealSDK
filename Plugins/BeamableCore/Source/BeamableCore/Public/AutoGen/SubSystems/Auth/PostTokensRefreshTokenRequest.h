
#pragma once

#include "CoreMinimal.h"
#include "BeamBackend/BeamBaseRequestInterface.h"
#include "BeamBackend/BeamRequestContext.h"
#include "BeamBackend/BeamErrorResponse.h"
#include "BeamBackend/BeamFullResponse.h"

#include "BeamableCore/Public/AutoGen/RefreshTokenAuthRequestBody.h"
#include "BeamableCore/Public/AutoGen/AuthResponse.h"

#include "PostTokensRefreshTokenRequest.generated.h"

UCLASS(BlueprintType)
class BEAMABLECORE_API UPostTokensRefreshTokenRequest : public UObject, public IBeamBaseRequestInterface
{
	GENERATED_BODY()
	
public:

	// Path Params
	
	
	// Query Params
	

	// Body Params
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="", Category="Beam")
	URefreshTokenAuthRequestBody* Body = {};

	// Beam Base Request Declaration
	UPostTokensRefreshTokenRequest() = default;

	virtual void BuildVerb(FString& VerbString) const override;
	virtual void BuildRoute(FString& RouteString) const override;
	virtual void BuildBody(FString& BodyString) const override;

	UFUNCTION(BlueprintPure, BlueprintInternalUseOnly, Category="Beam|Auth|Utils|Make/Break", DisplayName="Make PostTokensRefreshToken",  meta=(DefaultToSelf="RequestOwner", AdvancedDisplay="_RefreshToken,_CustomerId,_RealmId,_Context,RequestOwner", AutoCreateRefTerm="CustomHeaders"))
	static UPostTokensRefreshTokenRequest* Make(FOptionalString _RefreshToken, FOptionalBeamCid _CustomerId, FOptionalBeamPid _RealmId, FOptionalContextInfo _Context, UObject* RequestOwner, TMap<FString, FString> CustomHeaders);
};

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnPostTokensRefreshTokenSuccess, FBeamRequestContext, Context, UPostTokensRefreshTokenRequest*, Request, UAuthResponse*, Response);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnPostTokensRefreshTokenError, FBeamRequestContext, Context, UPostTokensRefreshTokenRequest*, Request, FBeamErrorResponse, Error);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnPostTokensRefreshTokenComplete, FBeamRequestContext, Context, UPostTokensRefreshTokenRequest*, Request);

using FPostTokensRefreshTokenFullResponse = FBeamFullResponse<UPostTokensRefreshTokenRequest*, UAuthResponse*>;
DECLARE_DELEGATE_OneParam(FOnPostTokensRefreshTokenFullResponse, FPostTokensRefreshTokenFullResponse);
