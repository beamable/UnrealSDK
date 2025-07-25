
#pragma once

#include "CoreMinimal.h"
#include "BeamBackend/BeamBaseRequestInterface.h"
#include "BeamBackend/BeamRequestContext.h"
#include "BeamBackend/BeamErrorResponse.h"
#include "BeamBackend/BeamFullResponse.h"

#include "BeamableCore/Public/AutoGen/CreateAccountWithCredsRequestBody.h"
#include "BeamableCore/Public/AutoGen/CreateAccountWithCredsApiResponse.h"

#include "PostSignupRequest.generated.h"

UCLASS(BlueprintType)
class BEAMABLECORE_API UPostSignupRequest : public UObject, public IBeamBaseRequestInterface
{
	GENERATED_BODY()
	
public:

	// Path Params
	
	
	// Query Params
	

	// Body Params
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="", Category="Beam")
	UCreateAccountWithCredsRequestBody* Body = {};

	// Beam Base Request Declaration
	UPostSignupRequest() = default;

	virtual void BuildVerb(FString& VerbString) const override;
	virtual void BuildRoute(FString& RouteString) const override;
	virtual void BuildBody(FString& BodyString) const override;

	UFUNCTION(BlueprintPure, BlueprintInternalUseOnly, Category="Beam|Accounts|Utils|Make/Break", DisplayName="Make PostSignup",  meta=(DefaultToSelf="RequestOwner", AdvancedDisplay="_Username,_ProviderNamespace,_ChallengeSolution,_ExternalToken,_ProviderService,_Password,_InitProperties,RequestOwner", AutoCreateRefTerm="CustomHeaders"))
	static UPostSignupRequest* Make(FOptionalString _Username, FOptionalString _ProviderNamespace, FOptionalChallengeSolution _ChallengeSolution, FOptionalString _ExternalToken, FOptionalString _ProviderService, FOptionalString _Password, FOptionalMapOfString _InitProperties, UObject* RequestOwner, TMap<FString, FString> CustomHeaders);
};

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnPostSignupSuccess, FBeamRequestContext, Context, UPostSignupRequest*, Request, UCreateAccountWithCredsApiResponse*, Response);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnPostSignupError, FBeamRequestContext, Context, UPostSignupRequest*, Request, FBeamErrorResponse, Error);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnPostSignupComplete, FBeamRequestContext, Context, UPostSignupRequest*, Request);

using FPostSignupFullResponse = FBeamFullResponse<UPostSignupRequest*, UCreateAccountWithCredsApiResponse*>;
DECLARE_DELEGATE_OneParam(FOnPostSignupFullResponse, FPostSignupFullResponse);
