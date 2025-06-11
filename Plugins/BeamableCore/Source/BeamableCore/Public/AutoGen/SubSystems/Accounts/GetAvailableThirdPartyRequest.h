
#pragma once

#include "CoreMinimal.h"
#include "BeamBackend/BeamBaseRequestInterface.h"
#include "BeamBackend/BeamRequestContext.h"
#include "BeamBackend/BeamErrorResponse.h"
#include "BeamBackend/BeamFullResponse.h"

#include "Serialization/BeamJsonUtils.h"
#include "BeamableCore/Public/AutoGen/AccountAvailableResponse.h"

#include "GetAvailableThirdPartyRequest.generated.h"

UCLASS(BlueprintType)
class BEAMABLECORE_API UGetAvailableThirdPartyRequest : public UObject, public IBeamBaseRequestInterface
{
	GENERATED_BODY()
	
public:

	// Path Params
	
	
	// Query Params
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Third Party", Category="Beam")
	FString ThirdParty = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Token", Category="Beam")
	FString Token = {};

	// Body Params
	

	// Beam Base Request Declaration
	UGetAvailableThirdPartyRequest() = default;

	virtual void BuildVerb(FString& VerbString) const override;
	virtual void BuildRoute(FString& RouteString) const override;
	virtual void BuildBody(FString& BodyString) const override;

	UFUNCTION(BlueprintPure, BlueprintInternalUseOnly, Category="Beam|Accounts|Utils|Make/Break", DisplayName="Make GetAvailableThirdParty",  meta=(DefaultToSelf="RequestOwner", AdvancedDisplay="RequestOwner", AutoCreateRefTerm="CustomHeaders"))
	static UGetAvailableThirdPartyRequest* Make(FString _ThirdParty, FString _Token, UObject* RequestOwner, TMap<FString, FString> CustomHeaders);
};

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnGetAvailableThirdPartySuccess, FBeamRequestContext, Context, UGetAvailableThirdPartyRequest*, Request, UAccountAvailableResponse*, Response);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnGetAvailableThirdPartyError, FBeamRequestContext, Context, UGetAvailableThirdPartyRequest*, Request, FBeamErrorResponse, Error);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnGetAvailableThirdPartyComplete, FBeamRequestContext, Context, UGetAvailableThirdPartyRequest*, Request);

using FGetAvailableThirdPartyFullResponse = FBeamFullResponse<UGetAvailableThirdPartyRequest*, UAccountAvailableResponse*>;
DECLARE_DELEGATE_OneParam(FOnGetAvailableThirdPartyFullResponse, FGetAvailableThirdPartyFullResponse);
