
#pragma once

#include "CoreMinimal.h"
#include "BeamBackend/BeamBaseRequestInterface.h"
#include "BeamBackend/BeamRequestContext.h"
#include "BeamBackend/BeamErrorResponse.h"
#include "BeamBackend/BeamFullResponse.h"

#include "BeamableCore/Public/AutoGen/AuthV2RefreshTokenAuthRequestBody.h"
#include "BeamableCore/Public/AutoGen/AuthV2AuthResponse.h"

#include "PostRefreshTokenRequest.generated.h"

UCLASS(BlueprintType)
class BEAMABLECORE_API UPostRefreshTokenRequest : public UObject, public IBeamBaseRequestInterface
{
	GENERATED_BODY()
	
public:

	// Path Params
	
	
	// Query Params
	

	// Body Params
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="", Category="Beam")
	UAuthV2RefreshTokenAuthRequestBody* Body = {};

	// Beam Base Request Declaration
	UPostRefreshTokenRequest() = default;

	virtual void BuildVerb(FString& VerbString) const override;
	virtual void BuildRoute(FString& RouteString) const override;
	virtual void BuildBody(FString& BodyString) const override;

	UFUNCTION(BlueprintPure, BlueprintInternalUseOnly, Category="Beam|Auth|Utils|Make/Break", DisplayName="Make PostRefreshToken",  meta=(DefaultToSelf="RequestOwner", AdvancedDisplay="_RefreshToken,_CustomerId,_RealmId,_Context,RequestOwner", AutoCreateRefTerm="CustomHeaders"))
	static UPostRefreshTokenRequest* Make(FOptionalString _RefreshToken, FOptionalBeamCid _CustomerId, FOptionalBeamPid _RealmId, FOptionalAuthV2ContextInfo _Context, UObject* RequestOwner, TMap<FString, FString> CustomHeaders);
};

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnPostRefreshTokenSuccess, FBeamRequestContext, Context, UPostRefreshTokenRequest*, Request, UAuthV2AuthResponse*, Response);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnPostRefreshTokenError, FBeamRequestContext, Context, UPostRefreshTokenRequest*, Request, FBeamErrorResponse, Error);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnPostRefreshTokenComplete, FBeamRequestContext, Context, UPostRefreshTokenRequest*, Request);

using FPostRefreshTokenFullResponse = FBeamFullResponse<UPostRefreshTokenRequest*, UAuthV2AuthResponse*>;
DECLARE_DELEGATE_OneParam(FOnPostRefreshTokenFullResponse, FPostRefreshTokenFullResponse);
