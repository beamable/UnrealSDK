
#pragma once

#include "CoreMinimal.h"
#include "BeamBackend/BeamBaseRequestInterface.h"
#include "BeamBackend/BeamRequestContext.h"
#include "BeamBackend/BeamErrorResponse.h"
#include "BeamBackend/BeamFullResponse.h"

#include "Serialization/BeamJsonUtils.h"
#include "BeamableCore/Public/AutoGen/Transaction.h"

#include "GetPaymentRequest.generated.h"

UCLASS(BlueprintType)
class BEAMABLECORE_API UGetPaymentRequest : public UObject, public IBeamBaseRequestInterface
{
	GENERATED_BODY()
	
public:

	// Path Params
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Transaction Id", Category="Beam")
	int64 TransactionId = {};
	
	// Query Params
	

	// Body Params
	

	// Beam Base Request Declaration
	UGetPaymentRequest() = default;

	virtual void BuildVerb(FString& VerbString) const override;
	virtual void BuildRoute(FString& RouteString) const override;
	virtual void BuildBody(FString& BodyString) const override;

	UFUNCTION(BlueprintPure, BlueprintInternalUseOnly, Category="Beam|Payment|Utils|Make/Break", DisplayName="Make GetPayment",  meta=(DefaultToSelf="RequestOwner", AdvancedDisplay="RequestOwner", AutoCreateRefTerm="CustomHeaders"))
	static UGetPaymentRequest* Make(int64 _TransactionId, UObject* RequestOwner, TMap<FString, FString> CustomHeaders);
};

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnGetPaymentSuccess, FBeamRequestContext, Context, UGetPaymentRequest*, Request, UTransaction*, Response);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnGetPaymentError, FBeamRequestContext, Context, UGetPaymentRequest*, Request, FBeamErrorResponse, Error);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnGetPaymentComplete, FBeamRequestContext, Context, UGetPaymentRequest*, Request);

using FGetPaymentFullResponse = FBeamFullResponse<UGetPaymentRequest*, UTransaction*>;
DECLARE_DELEGATE_OneParam(FOnGetPaymentFullResponse, FGetPaymentFullResponse);
