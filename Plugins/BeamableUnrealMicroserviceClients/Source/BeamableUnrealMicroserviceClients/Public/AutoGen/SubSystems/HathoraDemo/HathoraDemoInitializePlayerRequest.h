
#pragma once

#include "CoreMinimal.h"
#include "BeamBackend/BeamBaseRequestInterface.h"
#include "BeamBackend/BeamRequestContext.h"
#include "BeamBackend/BeamErrorResponse.h"
#include "BeamBackend/BeamFullResponse.h"

#include "Serialization/BeamPlainTextResponseBody.h"

#include "HathoraDemoInitializePlayerRequest.generated.h"

UCLASS(BlueprintType)
class BEAMABLEUNREALMICROSERVICECLIENTS_API UHathoraDemoInitializePlayerRequest : public UObject, public IBeamBaseRequestInterface
{
	GENERATED_BODY()
	
public:

	// Path Params
	
	
	// Query Params
	

	// Body Params
	

	// Beam Base Request Declaration
	UHathoraDemoInitializePlayerRequest() = default;

	virtual void BuildVerb(FString& VerbString) const override;
	virtual void BuildRoute(FString& RouteString) const override;
	virtual void BuildBody(FString& BodyString) const override;

	UFUNCTION(BlueprintPure, BlueprintInternalUseOnly, Category="Beam|2 - Backend|HathoraDemo", DisplayName="Make HathoraDemoInitializePlayer",  meta=(DefaultToSelf="RequestOwner", AdvancedDisplay="RequestOwner", AutoCreateRefTerm="CustomHeaders"))
	static UHathoraDemoInitializePlayerRequest* Make(UObject* RequestOwner, TMap<FString, FString> CustomHeaders);
};

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnHathoraDemoInitializePlayerSuccess, FBeamRequestContext, Context, UHathoraDemoInitializePlayerRequest*, Request, UBeamPlainTextResponseBody*, Response);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnHathoraDemoInitializePlayerError, FBeamRequestContext, Context, UHathoraDemoInitializePlayerRequest*, Request, FBeamErrorResponse, Error);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnHathoraDemoInitializePlayerComplete, FBeamRequestContext, Context, UHathoraDemoInitializePlayerRequest*, Request);

using FHathoraDemoInitializePlayerFullResponse = FBeamFullResponse<UHathoraDemoInitializePlayerRequest*, UBeamPlainTextResponseBody*>;
DECLARE_DELEGATE_OneParam(FOnHathoraDemoInitializePlayerFullResponse, FHathoraDemoInitializePlayerFullResponse);
