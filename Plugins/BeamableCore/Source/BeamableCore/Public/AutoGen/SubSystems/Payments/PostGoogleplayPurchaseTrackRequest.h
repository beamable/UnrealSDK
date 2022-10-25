
#pragma once

#include "CoreMinimal.h"
#include "BeamBackend/BeamBaseRequestInterface.h"
#include "BeamBackend/BeamRequestContext.h"
#include "BeamBackend/BeamErrorResponse.h"
#include "BeamBackend/BeamFullResponse.h"

#include "AutoGen/TrackPurchaseRequestBody.h"
#include "AutoGen/PaymentResultResponse.h"

#include "PostGoogleplayPurchaseTrackRequest.generated.h"

UCLASS(BlueprintType)
class BEAMABLECORE_API UPostGoogleplayPurchaseTrackRequest : public UObject, public IBeamBaseRequestInterface
{
	GENERATED_BODY()
	
public:

	// Path Params
	
	
	// Query Params
	

	// Body Params
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="", Category="Beam")
	UTrackPurchaseRequestBody* Body;

	// Beam Base Request Declaration
	UPostGoogleplayPurchaseTrackRequest() = default;

	virtual void BuildVerb(FString& VerbString) const override;
	virtual void BuildRoute(FString& RouteString) const override;
	virtual void BuildBody(FString& BodyString) const override;

	UFUNCTION(BlueprintPure, BlueprintInternalUseOnly, Category="Beam|Backend|Payments", DisplayName="Beam - Make PostGoogleplayPurchaseTrack",  meta=(DefaultToSelf="Outer", AdvancedDisplay="Outer"))
	static UPostGoogleplayPurchaseTrackRequest* Make(double _PriceInLocalCurrency, FString _SkuName, FString _SkuProductId, FString _Store, FString _PurchaseId, FString _IsoCurrencySymbol, TArray<UItemCreateRequestBody*> _ObtainItems, TArray<UCurrencyChange*> _ObtainCurrency, UObject* Outer);
};

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnPostGoogleplayPurchaseTrackSuccess, FBeamRequestContext, Context, UPostGoogleplayPurchaseTrackRequest*, Request, UPaymentResultResponse*, Response);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnPostGoogleplayPurchaseTrackError, FBeamRequestContext, Context, UPostGoogleplayPurchaseTrackRequest*, Request, FBeamErrorResponse, Error);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnPostGoogleplayPurchaseTrackComplete, FBeamRequestContext, Context, UPostGoogleplayPurchaseTrackRequest*, Request);

using FPostGoogleplayPurchaseTrackFullResponse = FBeamFullResponse<UPostGoogleplayPurchaseTrackRequest*, UPaymentResultResponse*>;
DECLARE_DELEGATE_OneParam(FOnPostGoogleplayPurchaseTrackFullResponse, FPostGoogleplayPurchaseTrackFullResponse);
