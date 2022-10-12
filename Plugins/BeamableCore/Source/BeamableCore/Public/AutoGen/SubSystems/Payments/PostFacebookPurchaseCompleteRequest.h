
#pragma once

#include "CoreMinimal.h"
#include "BeamCoreTypes.h"

#include "AutoGen/CompletePurchaseRequestBody.h"
#include "AutoGen/PaymentResultResponse.h"

#include "PostFacebookPurchaseCompleteRequest.generated.h"

UCLASS(BlueprintType)
class BEAMABLECORE_API UPostFacebookPurchaseCompleteRequest : public UObject, public IBeamBaseRequestInterface
{
	GENERATED_BODY()
	
public:

	// Path Params
	
	
	// Query Params
	

	// Body Params
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="")
	UCompletePurchaseRequestBody* Body;

	// Beam Base Request Declaration
	UPostFacebookPurchaseCompleteRequest() = default;

	virtual void BuildVerb(FString& VerbString) const override;
	virtual void BuildRoute(FString& RouteString) const override;
	virtual void BuildBody(FString& BodyString) const override;

	UFUNCTION(BlueprintPure, meta=(DefaultToSelf="Outer", AdvancedDisplay="Outer"))
	static UPostFacebookPurchaseCompleteRequest* MakePostFacebookPurchaseCompleteRequest(int64 _Txid, FString _Receipt, FString _PriceInLocalCurrency, FString _IsoCurrencySymbol, UObject* Outer);
};

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnPostFacebookPurchaseCompleteSuccess, FBeamRequestContext, Context, UPostFacebookPurchaseCompleteRequest*, Request, UPaymentResultResponse*, Response);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnPostFacebookPurchaseCompleteError, FBeamRequestContext, Context, UPostFacebookPurchaseCompleteRequest*, Request, FBeamErrorResponse, Error);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnPostFacebookPurchaseCompleteComplete, FBeamRequestContext, Context, UPostFacebookPurchaseCompleteRequest*, Request);

using FPostFacebookPurchaseCompleteFullResponse = FBeamFullResponse<UPostFacebookPurchaseCompleteRequest*, UPaymentResultResponse*>;
DECLARE_DELEGATE_OneParam(FOnPostFacebookPurchaseCompleteFullResponse, FPostFacebookPurchaseCompleteFullResponse);