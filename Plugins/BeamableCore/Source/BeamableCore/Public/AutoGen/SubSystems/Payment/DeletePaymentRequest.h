
#pragma once

#include "CoreMinimal.h"
#include "BeamBackend/BeamBaseRequestInterface.h"
#include "BeamBackend/BeamRequestContext.h"
#include "BeamBackend/BeamErrorResponse.h"
#include "BeamBackend/BeamFullResponse.h"

#include "Serialization/BeamJsonUtils.h"
#include "BeamableCore/Public/AutoGen/Transaction.h"

#include "DeletePaymentRequest.generated.h"

UCLASS(BlueprintType)
class BEAMABLECORE_API UDeletePaymentRequest : public UObject, public IBeamBaseRequestInterface
{
	GENERATED_BODY()
	
public:

	// Path Params
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Transaction Id", Category="Beam")
	int64 TransactionId = {};
	
	// Query Params
	

	// Body Params
	

	// Beam Base Request Declaration
	UDeletePaymentRequest() = default;

	virtual void BuildVerb(FString& VerbString) const override;
	virtual void BuildRoute(FString& RouteString) const override;
	virtual void BuildBody(FString& BodyString) const override;

	UFUNCTION(BlueprintPure, BlueprintInternalUseOnly, Category="Beam|Payment|Utils|Make/Break", DisplayName="Make DeletePayment",  meta=(DefaultToSelf="RequestOwner", AdvancedDisplay="RequestOwner", AutoCreateRefTerm="CustomHeaders"))
	static UDeletePaymentRequest* Make(int64 _TransactionId, UObject* RequestOwner, TMap<FString, FString> CustomHeaders);
};

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnDeletePaymentSuccess, FBeamRequestContext, Context, UDeletePaymentRequest*, Request, UTransaction*, Response);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnDeletePaymentError, FBeamRequestContext, Context, UDeletePaymentRequest*, Request, FBeamErrorResponse, Error);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnDeletePaymentComplete, FBeamRequestContext, Context, UDeletePaymentRequest*, Request);

using FDeletePaymentFullResponse = FBeamFullResponse<UDeletePaymentRequest*, UTransaction*>;
DECLARE_DELEGATE_OneParam(FOnDeletePaymentFullResponse, FDeletePaymentFullResponse);
