
#pragma once

#include "CoreMinimal.h"
#include "BeamCoreTypes.h"

#include "AutoGen/Optionals/OptionalInt64.h"
#include "AutoGen/Manifest.h"

#include "GetCloudsavingRequest.generated.h"

UCLASS(BlueprintType)
class BEAMABLECORE_API UGetCloudsavingRequest : public UObject, public IBeamBaseRequestInterface
{
	GENERATED_BODY()
	
public:

	// Path Params
	
	
	// Query Params
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Player Id")
	FOptionalInt64 PlayerId;

	// Body Params
	

	// Beam Base Request Declaration
	UGetCloudsavingRequest() = default;

	virtual void BuildVerb(FString& VerbString) const override;
	virtual void BuildRoute(FString& RouteString) const override;
	virtual void BuildBody(FString& BodyString) const override;

	UFUNCTION(BlueprintPure, meta=(DefaultToSelf="Outer", AdvancedDisplay="_PlayerId,Outer"))
	static UGetCloudsavingRequest* MakeGetCloudsavingRequest(FOptionalInt64 _PlayerId, UObject* Outer);
};

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnGetCloudsavingSuccess, FBeamRequestContext, Context, UGetCloudsavingRequest*, Request, UManifest*, Response);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnGetCloudsavingError, FBeamRequestContext, Context, UGetCloudsavingRequest*, Request, FBeamErrorResponse, Error);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnGetCloudsavingComplete, FBeamRequestContext, Context, UGetCloudsavingRequest*, Request);

using FGetCloudsavingFullResponse = FBeamFullResponse<UGetCloudsavingRequest*, UManifest*>;
DECLARE_DELEGATE_OneParam(FOnGetCloudsavingFullResponse, FGetCloudsavingFullResponse);
