
#pragma once

#include "CoreMinimal.h"
#include "BeamBackend/BeamBaseRequestInterface.h"
#include "BeamBackend/BeamRequestContext.h"
#include "BeamBackend/BeamErrorResponse.h"
#include "BeamBackend/BeamFullResponse.h"

#include "BeamableCore/Public/AutoGen/TrackPurchaseRequestBody.h"
#include "BeamableCore/Public/AutoGen/PaymentResultResponse.h"

#include "PostCouponPurchaseTrackRequest.generated.h"

UCLASS(BlueprintType)
class BEAMABLECORE_API UPostCouponPurchaseTrackRequest : public UObject, public IBeamBaseRequestInterface
{
	GENERATED_BODY()
	
public:

	// Path Params
	
	
	// Query Params
	

	// Body Params
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="", Category="Beam")
	UTrackPurchaseRequestBody* Body = {};

	// Beam Base Request Declaration
	UPostCouponPurchaseTrackRequest() = default;

	virtual void BuildVerb(FString& VerbString) const override;
	virtual void BuildRoute(FString& RouteString) const override;
	virtual void BuildBody(FString& BodyString) const override;

	UFUNCTION(BlueprintPure, BlueprintInternalUseOnly, Category="Beam|Payments|Utils|Make/Break", DisplayName="Make PostCouponPurchaseTrack",  meta=(DefaultToSelf="RequestOwner", AdvancedDisplay="RequestOwner", AutoCreateRefTerm="CustomHeaders"))
	static UPostCouponPurchaseTrackRequest* Make(double _PriceInLocalCurrency, FString _SkuName, FString _SkuProductId, FString _Store, FString _PurchaseId, FString _IsoCurrencySymbol, TArray<UItemCreateRequestBody*> _ObtainItems, TArray<UCurrencyChange*> _ObtainCurrency, UObject* RequestOwner, TMap<FString, FString> CustomHeaders);
};

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnPostCouponPurchaseTrackSuccess, FBeamRequestContext, Context, UPostCouponPurchaseTrackRequest*, Request, UPaymentResultResponse*, Response);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnPostCouponPurchaseTrackError, FBeamRequestContext, Context, UPostCouponPurchaseTrackRequest*, Request, FBeamErrorResponse, Error);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnPostCouponPurchaseTrackComplete, FBeamRequestContext, Context, UPostCouponPurchaseTrackRequest*, Request);

using FPostCouponPurchaseTrackFullResponse = FBeamFullResponse<UPostCouponPurchaseTrackRequest*, UPaymentResultResponse*>;
DECLARE_DELEGATE_OneParam(FOnPostCouponPurchaseTrackFullResponse, FPostCouponPurchaseTrackFullResponse);
