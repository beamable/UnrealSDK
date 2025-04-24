
#pragma once

#include "CoreMinimal.h"
#include "BeamBackend/BeamBaseRequestInterface.h"
#include "BeamBackend/BeamRequestContext.h"
#include "BeamBackend/BeamErrorResponse.h"
#include "BeamBackend/BeamFullResponse.h"

#include "BeamableCore/Public/AutoGen/CancelPurchaseRequestBody.h"
#include "BeamableCore/Public/AutoGen/PaymentResultResponse.h"

#include "PostWindowsPurchaseCancelRequest.generated.h"

UCLASS(BlueprintType)
class BEAMABLECORE_API UPostWindowsPurchaseCancelRequest : public UObject, public IBeamBaseRequestInterface
{
	GENERATED_BODY()
	
public:

	// Path Params
	
	
	// Query Params
	

	// Body Params
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="", Category="Beam")
	UCancelPurchaseRequestBody* Body = {};

	// Beam Base Request Declaration
	UPostWindowsPurchaseCancelRequest() = default;

	virtual void BuildVerb(FString& VerbString) const override;
	virtual void BuildRoute(FString& RouteString) const override;
	virtual void BuildBody(FString& BodyString) const override;

	UFUNCTION(BlueprintPure, BlueprintInternalUseOnly, Category="Beam|Payments|Utils|Make/Break", DisplayName="Make PostWindowsPurchaseCancel",  meta=(DefaultToSelf="RequestOwner", AdvancedDisplay="RequestOwner", AutoCreateRefTerm="CustomHeaders"))
	static UPostWindowsPurchaseCancelRequest* Make(int64 _Txid, UObject* RequestOwner, TMap<FString, FString> CustomHeaders);
};

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnPostWindowsPurchaseCancelSuccess, FBeamRequestContext, Context, UPostWindowsPurchaseCancelRequest*, Request, UPaymentResultResponse*, Response);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnPostWindowsPurchaseCancelError, FBeamRequestContext, Context, UPostWindowsPurchaseCancelRequest*, Request, FBeamErrorResponse, Error);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnPostWindowsPurchaseCancelComplete, FBeamRequestContext, Context, UPostWindowsPurchaseCancelRequest*, Request);

using FPostWindowsPurchaseCancelFullResponse = FBeamFullResponse<UPostWindowsPurchaseCancelRequest*, UPaymentResultResponse*>;
DECLARE_DELEGATE_OneParam(FOnPostWindowsPurchaseCancelFullResponse, FPostWindowsPurchaseCancelFullResponse);
