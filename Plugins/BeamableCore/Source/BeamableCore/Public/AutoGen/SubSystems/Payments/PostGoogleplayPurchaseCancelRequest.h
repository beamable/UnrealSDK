
#pragma once

#include "CoreMinimal.h"
#include "BeamBackend/BeamBaseRequestInterface.h"
#include "BeamBackend/BeamRequestContext.h"
#include "BeamBackend/BeamErrorResponse.h"
#include "BeamBackend/BeamFullResponse.h"

#include "BeamableCore/Public/AutoGen/CancelPurchaseRequestBody.h"
#include "BeamableCore/Public/AutoGen/PaymentResultResponse.h"

#include "PostGoogleplayPurchaseCancelRequest.generated.h"

UCLASS(BlueprintType)
class BEAMABLECORE_API UPostGoogleplayPurchaseCancelRequest : public UObject, public IBeamBaseRequestInterface
{
	GENERATED_BODY()
	
public:

	// Path Params
	
	
	// Query Params
	

	// Body Params
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="", Category="Beam")
	UCancelPurchaseRequestBody* Body = {};

	// Beam Base Request Declaration
	UPostGoogleplayPurchaseCancelRequest() = default;

	virtual void BuildVerb(FString& VerbString) const override;
	virtual void BuildRoute(FString& RouteString) const override;
	virtual void BuildBody(FString& BodyString) const override;

	UFUNCTION(BlueprintPure, BlueprintInternalUseOnly, Category="Beam|Payments|Utils|Make/Break", DisplayName="Make PostGoogleplayPurchaseCancel",  meta=(DefaultToSelf="RequestOwner", AdvancedDisplay="RequestOwner", AutoCreateRefTerm="CustomHeaders"))
	static UPostGoogleplayPurchaseCancelRequest* Make(int64 _Txid, UObject* RequestOwner, TMap<FString, FString> CustomHeaders);
};

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnPostGoogleplayPurchaseCancelSuccess, FBeamRequestContext, Context, UPostGoogleplayPurchaseCancelRequest*, Request, UPaymentResultResponse*, Response);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnPostGoogleplayPurchaseCancelError, FBeamRequestContext, Context, UPostGoogleplayPurchaseCancelRequest*, Request, FBeamErrorResponse, Error);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnPostGoogleplayPurchaseCancelComplete, FBeamRequestContext, Context, UPostGoogleplayPurchaseCancelRequest*, Request);

using FPostGoogleplayPurchaseCancelFullResponse = FBeamFullResponse<UPostGoogleplayPurchaseCancelRequest*, UPaymentResultResponse*>;
DECLARE_DELEGATE_OneParam(FOnPostGoogleplayPurchaseCancelFullResponse, FPostGoogleplayPurchaseCancelFullResponse);
