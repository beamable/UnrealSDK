
#pragma once

#include "CoreMinimal.h"
#include "BeamBackend/BeamBaseRequestInterface.h"
#include "BeamBackend/BeamRequestContext.h"
#include "BeamBackend/BeamErrorResponse.h"
#include "BeamBackend/BeamFullResponse.h"

#include "BeamableCore/Public/AutoGen/CompletePurchaseRequestBody.h"
#include "BeamableCore/Public/AutoGen/PaymentResultResponse.h"

#include "PostCouponPurchaseCompleteRequest.generated.h"

UCLASS(BlueprintType)
class BEAMABLECORE_API UPostCouponPurchaseCompleteRequest : public UObject, public IBeamBaseRequestInterface
{
	GENERATED_BODY()
	
public:

	// Path Params
	
	
	// Query Params
	

	// Body Params
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="", Category="Beam")
	UCompletePurchaseRequestBody* Body = {};

	// Beam Base Request Declaration
	UPostCouponPurchaseCompleteRequest() = default;

	virtual void BuildVerb(FString& VerbString) const override;
	virtual void BuildRoute(FString& RouteString) const override;
	virtual void BuildBody(FString& BodyString) const override;

	UFUNCTION(BlueprintPure, BlueprintInternalUseOnly, Category="Beam|Payments|Utils|Make/Break", DisplayName="Make PostCouponPurchaseComplete",  meta=(DefaultToSelf="RequestOwner", AdvancedDisplay="RequestOwner", AutoCreateRefTerm="CustomHeaders"))
	static UPostCouponPurchaseCompleteRequest* Make(int64 _Txid, FString _Receipt, FString _PriceInLocalCurrency, FString _IsoCurrencySymbol, UObject* RequestOwner, TMap<FString, FString> CustomHeaders);
};

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnPostCouponPurchaseCompleteSuccess, FBeamRequestContext, Context, UPostCouponPurchaseCompleteRequest*, Request, UPaymentResultResponse*, Response);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnPostCouponPurchaseCompleteError, FBeamRequestContext, Context, UPostCouponPurchaseCompleteRequest*, Request, FBeamErrorResponse, Error);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnPostCouponPurchaseCompleteComplete, FBeamRequestContext, Context, UPostCouponPurchaseCompleteRequest*, Request);

using FPostCouponPurchaseCompleteFullResponse = FBeamFullResponse<UPostCouponPurchaseCompleteRequest*, UPaymentResultResponse*>;
DECLARE_DELEGATE_OneParam(FOnPostCouponPurchaseCompleteFullResponse, FPostCouponPurchaseCompleteFullResponse);
