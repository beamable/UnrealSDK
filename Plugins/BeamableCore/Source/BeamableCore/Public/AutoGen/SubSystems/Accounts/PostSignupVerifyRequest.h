
#pragma once

#include "CoreMinimal.h"
#include "BeamBackend/BeamBaseRequestInterface.h"
#include "BeamBackend/BeamRequestContext.h"
#include "BeamBackend/BeamErrorResponse.h"
#include "BeamBackend/BeamFullResponse.h"

#include "BeamableCore/Public/AutoGen/SignupVerificationRequestBody.h"
#include "BeamableCore/Public/AutoGen/SignupVerificationResponse.h"

#include "PostSignupVerifyRequest.generated.h"

UCLASS(BlueprintType)
class BEAMABLECORE_API UPostSignupVerifyRequest : public UObject, public IBeamBaseRequestInterface
{
	GENERATED_BODY()
	
public:

	// Path Params
	
	
	// Query Params
	

	// Body Params
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="", Category="Beam")
	USignupVerificationRequestBody* Body = {};

	// Beam Base Request Declaration
	UPostSignupVerifyRequest() = default;

	virtual void BuildVerb(FString& VerbString) const override;
	virtual void BuildRoute(FString& RouteString) const override;
	virtual void BuildBody(FString& BodyString) const override;

	UFUNCTION(BlueprintPure, BlueprintInternalUseOnly, Category="Beam|Accounts|Utils|Make/Break", DisplayName="Make PostSignupVerify",  meta=(DefaultToSelf="RequestOwner", AdvancedDisplay="RequestOwner", AutoCreateRefTerm="CustomHeaders"))
	static UPostSignupVerifyRequest* Make(FString _Email, FString _Code, UObject* RequestOwner, TMap<FString, FString> CustomHeaders);
};

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnPostSignupVerifySuccess, FBeamRequestContext, Context, UPostSignupVerifyRequest*, Request, USignupVerificationResponse*, Response);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnPostSignupVerifyError, FBeamRequestContext, Context, UPostSignupVerifyRequest*, Request, FBeamErrorResponse, Error);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnPostSignupVerifyComplete, FBeamRequestContext, Context, UPostSignupVerifyRequest*, Request);

using FPostSignupVerifyFullResponse = FBeamFullResponse<UPostSignupVerifyRequest*, USignupVerificationResponse*>;
DECLARE_DELEGATE_OneParam(FOnPostSignupVerifyFullResponse, FPostSignupVerifyFullResponse);
