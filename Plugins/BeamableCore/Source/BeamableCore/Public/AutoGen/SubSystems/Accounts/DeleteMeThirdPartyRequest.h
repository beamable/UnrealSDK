
#pragma once

#include "CoreMinimal.h"
#include "BeamCoreTypes.h"

#include "AutoGen/ThirdPartyAvailableRequestBody.h"
#include "AutoGen/AccountPlayerView.h"

#include "DeleteMeThirdPartyRequest.generated.h"

UCLASS(BlueprintType)
class BEAMABLECORE_API UDeleteMeThirdPartyRequest : public UObject, public IBeamBaseRequestInterface
{
	GENERATED_BODY()
	
public:

	// Path Params
	
	
	// Query Params
	

	// Body Params
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="")
	UThirdPartyAvailableRequestBody* Body;

	// Beam Base Request Declaration
	UDeleteMeThirdPartyRequest() = default;

	virtual void BuildVerb(FString& VerbString) const override;
	virtual void BuildRoute(FString& RouteString) const override;
	virtual void BuildBody(FString& BodyString) const override;

	UFUNCTION(BlueprintPure, meta=(DefaultToSelf="Outer", AdvancedDisplay="Outer"))
	static UDeleteMeThirdPartyRequest* MakeDeleteMeThirdPartyRequest(FString _ThirdParty, FString _Token, UObject* Outer);
};

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnDeleteMeThirdPartySuccess, FBeamRequestContext, Context, UDeleteMeThirdPartyRequest*, Request, UAccountPlayerView*, Response);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnDeleteMeThirdPartyError, FBeamRequestContext, Context, UDeleteMeThirdPartyRequest*, Request, FBeamErrorResponse, Error);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnDeleteMeThirdPartyComplete, FBeamRequestContext, Context, UDeleteMeThirdPartyRequest*, Request);

using FDeleteMeThirdPartyFullResponse = FBeamFullResponse<UDeleteMeThirdPartyRequest*, UAccountPlayerView*>;
DECLARE_DELEGATE_OneParam(FOnDeleteMeThirdPartyFullResponse, FDeleteMeThirdPartyFullResponse);
