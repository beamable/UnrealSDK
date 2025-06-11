
#pragma once

#include "CoreMinimal.h"
#include "BeamBackend/BeamBaseRequestInterface.h"
#include "BeamBackend/BeamRequestContext.h"
#include "BeamBackend/BeamErrorResponse.h"
#include "BeamBackend/BeamFullResponse.h"

#include "BeamableCore/Public/AutoGen/ThirdPartyAvailableRequestBody.h"
#include "BeamableCore/Public/AutoGen/AccountPlayerView.h"

#include "DeleteMeThirdPartyRequest.generated.h"

UCLASS(BlueprintType)
class BEAMABLECORE_API UDeleteMeThirdPartyRequest : public UObject, public IBeamBaseRequestInterface
{
	GENERATED_BODY()
	
public:

	// Path Params
	
	
	// Query Params
	

	// Body Params
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="", Category="Beam")
	UThirdPartyAvailableRequestBody* Body = {};

	// Beam Base Request Declaration
	UDeleteMeThirdPartyRequest() = default;

	virtual void BuildVerb(FString& VerbString) const override;
	virtual void BuildRoute(FString& RouteString) const override;
	virtual void BuildBody(FString& BodyString) const override;

	UFUNCTION(BlueprintPure, BlueprintInternalUseOnly, Category="Beam|Accounts|Utils|Make/Break", DisplayName="Make DeleteMeThirdParty",  meta=(DefaultToSelf="RequestOwner", AdvancedDisplay="RequestOwner", AutoCreateRefTerm="CustomHeaders"))
	static UDeleteMeThirdPartyRequest* Make(FString _ThirdParty, FString _Token, UObject* RequestOwner, TMap<FString, FString> CustomHeaders);
};

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnDeleteMeThirdPartySuccess, FBeamRequestContext, Context, UDeleteMeThirdPartyRequest*, Request, UAccountPlayerView*, Response);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnDeleteMeThirdPartyError, FBeamRequestContext, Context, UDeleteMeThirdPartyRequest*, Request, FBeamErrorResponse, Error);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnDeleteMeThirdPartyComplete, FBeamRequestContext, Context, UDeleteMeThirdPartyRequest*, Request);

using FDeleteMeThirdPartyFullResponse = FBeamFullResponse<UDeleteMeThirdPartyRequest*, UAccountPlayerView*>;
DECLARE_DELEGATE_OneParam(FOnDeleteMeThirdPartyFullResponse, FDeleteMeThirdPartyFullResponse);
