
#pragma once

#include "CoreMinimal.h"
#include "BeamBackend/BeamBaseRequestInterface.h"
#include "BeamBackend/BeamRequestContext.h"
#include "BeamBackend/BeamErrorResponse.h"
#include "BeamBackend/BeamFullResponse.h"

#include "Serialization/BeamJsonUtils.h"
#include "BeamableCore/Public/AutoGen/LocalizedPriceMap.h"

#include "GetSteamPricesRequest.generated.h"

UCLASS(BlueprintType)
class BEAMABLECORE_API UGetSteamPricesRequest : public UObject, public IBeamBaseRequestInterface
{
	GENERATED_BODY()
	
public:

	// Path Params
	
	
	// Query Params
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Steam Id", Category="Beam")
	int64 SteamId = {};

	// Body Params
	

	// Beam Base Request Declaration
	UGetSteamPricesRequest() = default;

	virtual void BuildVerb(FString& VerbString) const override;
	virtual void BuildRoute(FString& RouteString) const override;
	virtual void BuildBody(FString& BodyString) const override;

	UFUNCTION(BlueprintPure, BlueprintInternalUseOnly, Category="Beam|Payments|Utils|Make/Break", DisplayName="Make GetSteamPrices",  meta=(DefaultToSelf="RequestOwner", AdvancedDisplay="RequestOwner", AutoCreateRefTerm="CustomHeaders"))
	static UGetSteamPricesRequest* Make(int64 _SteamId, UObject* RequestOwner, TMap<FString, FString> CustomHeaders);
};

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnGetSteamPricesSuccess, FBeamRequestContext, Context, UGetSteamPricesRequest*, Request, ULocalizedPriceMap*, Response);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnGetSteamPricesError, FBeamRequestContext, Context, UGetSteamPricesRequest*, Request, FBeamErrorResponse, Error);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnGetSteamPricesComplete, FBeamRequestContext, Context, UGetSteamPricesRequest*, Request);

using FGetSteamPricesFullResponse = FBeamFullResponse<UGetSteamPricesRequest*, ULocalizedPriceMap*>;
DECLARE_DELEGATE_OneParam(FOnGetSteamPricesFullResponse, FGetSteamPricesFullResponse);
