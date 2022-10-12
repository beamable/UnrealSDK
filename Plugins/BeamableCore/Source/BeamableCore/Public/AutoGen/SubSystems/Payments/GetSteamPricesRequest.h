
#pragma once

#include "CoreMinimal.h"
#include "BeamCoreTypes.h"


#include "AutoGen/LocalizedPriceMap.h"

#include "GetSteamPricesRequest.generated.h"

UCLASS(BlueprintType)
class BEAMABLECORE_API UGetSteamPricesRequest : public UObject, public IBeamBaseRequestInterface
{
	GENERATED_BODY()
	
public:

	// Path Params
	
	
	// Query Params
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Steam Id")
	int64 SteamId;

	// Body Params
	

	// Beam Base Request Declaration
	UGetSteamPricesRequest() = default;

	virtual void BuildVerb(FString& VerbString) const override;
	virtual void BuildRoute(FString& RouteString) const override;
	virtual void BuildBody(FString& BodyString) const override;

	UFUNCTION(BlueprintPure, meta=(DefaultToSelf="Outer", AdvancedDisplay="Outer"))
	static UGetSteamPricesRequest* MakeGetSteamPricesRequest(int64 _SteamId, UObject* Outer);
};

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnGetSteamPricesSuccess, FBeamRequestContext, Context, UGetSteamPricesRequest*, Request, ULocalizedPriceMap*, Response);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnGetSteamPricesError, FBeamRequestContext, Context, UGetSteamPricesRequest*, Request, FBeamErrorResponse, Error);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnGetSteamPricesComplete, FBeamRequestContext, Context, UGetSteamPricesRequest*, Request);

using FGetSteamPricesFullResponse = FBeamFullResponse<UGetSteamPricesRequest*, ULocalizedPriceMap*>;
DECLARE_DELEGATE_OneParam(FOnGetSteamPricesFullResponse, FGetSteamPricesFullResponse);
