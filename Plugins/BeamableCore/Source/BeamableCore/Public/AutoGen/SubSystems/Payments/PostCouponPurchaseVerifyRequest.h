
#pragma once

#include "CoreMinimal.h"
#include "BeamCoreTypes.h"

#include "AutoGen/VerifyPurchaseRequestBody.h"
#include "AutoGen/PaymentResultResponse.h"

#include "PostCouponPurchaseVerifyRequest.generated.h"

UCLASS(BlueprintType)
class BEAMABLECORE_API UPostCouponPurchaseVerifyRequest : public UObject, public IBeamBaseRequestInterface
{
	GENERATED_BODY()
	
public:

	// Path Params
	
	
	// Query Params
	

	// Body Params
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="")
	UVerifyPurchaseRequestBody* Body;

	// Beam Base Request Declaration
	UPostCouponPurchaseVerifyRequest() = default;

	virtual void BuildVerb(FString& VerbString) const override;
	virtual void BuildRoute(FString& RouteString) const override;
	virtual void BuildBody(FString& BodyString) const override;

	UFUNCTION(BlueprintPure, meta=(DefaultToSelf="Outer", AdvancedDisplay="Outer"))
	static UPostCouponPurchaseVerifyRequest* MakePostCouponPurchaseVerifyRequest(FString _Receipt, UObject* Outer);
};

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnPostCouponPurchaseVerifySuccess, FBeamRequestContext, Context, UPostCouponPurchaseVerifyRequest*, Request, UPaymentResultResponse*, Response);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnPostCouponPurchaseVerifyError, FBeamRequestContext, Context, UPostCouponPurchaseVerifyRequest*, Request, FBeamErrorResponse, Error);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnPostCouponPurchaseVerifyComplete, FBeamRequestContext, Context, UPostCouponPurchaseVerifyRequest*, Request);

using FPostCouponPurchaseVerifyFullResponse = FBeamFullResponse<UPostCouponPurchaseVerifyRequest*, UPaymentResultResponse*>;
DECLARE_DELEGATE_OneParam(FOnPostCouponPurchaseVerifyFullResponse, FPostCouponPurchaseVerifyFullResponse);