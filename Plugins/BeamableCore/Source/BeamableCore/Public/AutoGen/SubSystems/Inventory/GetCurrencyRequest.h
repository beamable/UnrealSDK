
#pragma once

#include "CoreMinimal.h"
#include "BeamCoreTypes.h"

#include "AutoGen/CurrencyContentResponse.h"

#include "GetCurrencyRequest.generated.h"

UCLASS(BlueprintType)
class BEAMABLECORE_API UGetCurrencyRequest : public UObject, public IBeamBaseRequestInterface
{
	GENERATED_BODY()
	
public:

	// Path Params
	
	
	// Query Params
	

	// Body Params
	

	// Beam Base Request Declaration
	UGetCurrencyRequest() = default;

	virtual void BuildVerb(FString& VerbString) const override;
	virtual void BuildRoute(FString& RouteString) const override;
	virtual void BuildBody(FString& BodyString) const override;

	UFUNCTION(BlueprintPure, meta=(DefaultToSelf="Outer", AdvancedDisplay="Outer"))
	static UGetCurrencyRequest* MakeGetCurrencyRequest(UObject* Outer);
};

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnGetCurrencySuccess, FBeamRequestContext, Context, UGetCurrencyRequest*, Request, UCurrencyContentResponse*, Response);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnGetCurrencyError, FBeamRequestContext, Context, UGetCurrencyRequest*, Request, FBeamErrorResponse, Error);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnGetCurrencyComplete, FBeamRequestContext, Context, UGetCurrencyRequest*, Request);

using FGetCurrencyFullResponse = FBeamFullResponse<UGetCurrencyRequest*, UCurrencyContentResponse*>;
DECLARE_DELEGATE_OneParam(FOnGetCurrencyFullResponse, FGetCurrencyFullResponse);
