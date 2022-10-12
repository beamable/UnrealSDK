
#pragma once

#include "CoreMinimal.h"
#include "BeamCoreTypes.h"

#include "AutoGen/TrackPurchaseRequestBody.h"
#include "AutoGen/PaymentResultResponse.h"

#include "PostWindowsPurchaseTrackRequest.generated.h"

UCLASS(BlueprintType)
class BEAMABLECORE_API UPostWindowsPurchaseTrackRequest : public UObject, public IBeamBaseRequestInterface
{
	GENERATED_BODY()
	
public:

	// Path Params
	
	
	// Query Params
	

	// Body Params
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="")
	UTrackPurchaseRequestBody* Body;

	// Beam Base Request Declaration
	UPostWindowsPurchaseTrackRequest() = default;

	virtual void BuildVerb(FString& VerbString) const override;
	virtual void BuildRoute(FString& RouteString) const override;
	virtual void BuildBody(FString& BodyString) const override;

	UFUNCTION(BlueprintPure, meta=(DefaultToSelf="Outer", AdvancedDisplay="Outer"))
	static UPostWindowsPurchaseTrackRequest* MakePostWindowsPurchaseTrackRequest(double _PriceInLocalCurrency, FString _SkuName, FString _SkuProductId, FString _Store, TArray<UItemCreateRequestBody*> _ObtainItems, TArray<UCurrencyChange*> _ObtainCurrency, FString _PurchaseId, FString _IsoCurrencySymbol, UObject* Outer);
};

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnPostWindowsPurchaseTrackSuccess, FBeamRequestContext, Context, UPostWindowsPurchaseTrackRequest*, Request, UPaymentResultResponse*, Response);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnPostWindowsPurchaseTrackError, FBeamRequestContext, Context, UPostWindowsPurchaseTrackRequest*, Request, FBeamErrorResponse, Error);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnPostWindowsPurchaseTrackComplete, FBeamRequestContext, Context, UPostWindowsPurchaseTrackRequest*, Request);

using FPostWindowsPurchaseTrackFullResponse = FBeamFullResponse<UPostWindowsPurchaseTrackRequest*, UPaymentResultResponse*>;
DECLARE_DELEGATE_OneParam(FOnPostWindowsPurchaseTrackFullResponse, FPostWindowsPurchaseTrackFullResponse);
