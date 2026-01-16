
#pragma once

#include "CoreMinimal.h"
#include "BeamBackend/BeamBaseRequestInterface.h"
#include "BeamBackend/BeamRequestContext.h"
#include "BeamBackend/BeamErrorResponse.h"
#include "BeamBackend/BeamFullResponse.h"

#include "Serialization/BeamJsonUtils.h"
#include "BeamableCore/Public/AutoGen/CompletePaymentRequestBody.h"
#include "BeamableCore/Public/AutoGen/Transaction.h"

#include "PutPaymentRequest.generated.h"

UCLASS(BlueprintType)
class BEAMABLECORE_API UPutPaymentRequest : public UObject, public IBeamBaseRequestInterface
{
	GENERATED_BODY()
	
public:

	// Path Params
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Transaction Id", Category="Beam")
	int64 TransactionId = {};
	
	// Query Params
	

	// Body Params
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="", Category="Beam")
	UCompletePaymentRequestBody* Body = {};

	// Beam Base Request Declaration
	UPutPaymentRequest() = default;

	virtual void BuildVerb(FString& VerbString) const override;
	virtual void BuildRoute(FString& RouteString) const override;
	virtual void BuildBody(FString& BodyString) const override;

	UFUNCTION(BlueprintPure, BlueprintInternalUseOnly, Category="Beam|Payment|Utils|Make/Break", DisplayName="Make PutPayment",  meta=(DefaultToSelf="RequestOwner", AdvancedDisplay="RequestOwner", AutoCreateRefTerm="CustomHeaders"))
	static UPutPaymentRequest* Make(int64 _TransactionId, FString _PaymentProvider, FString _Receipt, FString _PlayerId, UObject* RequestOwner, TMap<FString, FString> CustomHeaders);
};

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnPutPaymentSuccess, FBeamRequestContext, Context, UPutPaymentRequest*, Request, UTransaction*, Response);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnPutPaymentError, FBeamRequestContext, Context, UPutPaymentRequest*, Request, FBeamErrorResponse, Error);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnPutPaymentComplete, FBeamRequestContext, Context, UPutPaymentRequest*, Request);

using FPutPaymentFullResponse = FBeamFullResponse<UPutPaymentRequest*, UTransaction*>;
DECLARE_DELEGATE_OneParam(FOnPutPaymentFullResponse, FPutPaymentFullResponse);
