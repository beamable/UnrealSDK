
#pragma once

#include "CoreMinimal.h"
#include "BeamCoreTypes.h"


#include "AutoGen/SubscriptionVerificationResponse.h"

#include "GetFacebookUpdateRequest.generated.h"

UCLASS(BlueprintType)
class BEAMABLECORE_API UGetFacebookUpdateRequest : public UObject, public IBeamBaseRequestInterface
{
	GENERATED_BODY()
	
public:

	// Path Params
	
	
	// Query Params
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Hub Mode")
	FString HubMode;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Hub Challenge")
	FString HubChallenge;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Hub Verify Token")
	FString HubVerifyToken;

	// Body Params
	

	// Beam Base Request Declaration
	UGetFacebookUpdateRequest() = default;

	virtual void BuildVerb(FString& VerbString) const override;
	virtual void BuildRoute(FString& RouteString) const override;
	virtual void BuildBody(FString& BodyString) const override;

	UFUNCTION(BlueprintPure, meta=(DefaultToSelf="Outer", AdvancedDisplay="Outer"))
	static UGetFacebookUpdateRequest* MakeGetFacebookUpdateRequest(FString _HubMode, FString _HubChallenge, FString _HubVerifyToken, UObject* Outer);
};

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnGetFacebookUpdateSuccess, FBeamRequestContext, Context, UGetFacebookUpdateRequest*, Request, USubscriptionVerificationResponse*, Response);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnGetFacebookUpdateError, FBeamRequestContext, Context, UGetFacebookUpdateRequest*, Request, FBeamErrorResponse, Error);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnGetFacebookUpdateComplete, FBeamRequestContext, Context, UGetFacebookUpdateRequest*, Request);

using FGetFacebookUpdateFullResponse = FBeamFullResponse<UGetFacebookUpdateRequest*, USubscriptionVerificationResponse*>;
DECLARE_DELEGATE_OneParam(FOnGetFacebookUpdateFullResponse, FGetFacebookUpdateFullResponse);
