
#pragma once

#include "CoreMinimal.h"
#include "BeamBackend/BeamBaseRequestInterface.h"
#include "BeamBackend/BeamRequestContext.h"
#include "BeamBackend/BeamErrorResponse.h"
#include "BeamBackend/BeamFullResponse.h"

#include "AutoGen/CancelPurchaseRequestBody.h"
#include "AutoGen/PaymentResultResponse.h"

#include "PostTestPurchaseCancelRequest.generated.h"

UCLASS(BlueprintType)
class BEAMABLECORE_API UPostTestPurchaseCancelRequest : public UObject, public IBeamBaseRequestInterface
{
	GENERATED_BODY()
	
public:

	// Path Params
	
	
	// Query Params
	

	// Body Params
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="", Category="Beam")
	UCancelPurchaseRequestBody* Body;

	// Beam Base Request Declaration
	UPostTestPurchaseCancelRequest() = default;

	virtual void BuildVerb(FString& VerbString) const override;
	virtual void BuildRoute(FString& RouteString) const override;
	virtual void BuildBody(FString& BodyString) const override;

	UFUNCTION(BlueprintPure, BlueprintInternalUseOnly, Category="Beam|Backend|Payments", DisplayName="Beam - Make PostTestPurchaseCancel",  meta=(DefaultToSelf="Outer", AdvancedDisplay="Outer"))
	static UPostTestPurchaseCancelRequest* Make(int64 _Txid, UObject* Outer);
};

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnPostTestPurchaseCancelSuccess, FBeamRequestContext, Context, UPostTestPurchaseCancelRequest*, Request, UPaymentResultResponse*, Response);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnPostTestPurchaseCancelError, FBeamRequestContext, Context, UPostTestPurchaseCancelRequest*, Request, FBeamErrorResponse, Error);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnPostTestPurchaseCancelComplete, FBeamRequestContext, Context, UPostTestPurchaseCancelRequest*, Request);

using FPostTestPurchaseCancelFullResponse = FBeamFullResponse<UPostTestPurchaseCancelRequest*, UPaymentResultResponse*>;
DECLARE_DELEGATE_OneParam(FOnPostTestPurchaseCancelFullResponse, FPostTestPurchaseCancelFullResponse);
