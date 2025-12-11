
#pragma once

#include "CoreMinimal.h"
#include "BeamBackend/BeamBaseRequestInterface.h"
#include "BeamBackend/BeamRequestContext.h"
#include "BeamBackend/BeamErrorResponse.h"
#include "BeamBackend/BeamFullResponse.h"

#include "Serialization/BeamJsonUtils.h"
#include "BeamableCore/Public/AutoGen/UpdatePaymentRequestBody.h"
#include "BeamableCore/Public/AutoGen/Transaction.h"

#include "PatchPaymentRequest.generated.h"

UCLASS(BlueprintType)
class BEAMABLECORE_API UPatchPaymentRequest : public UObject, public IBeamBaseRequestInterface
{
	GENERATED_BODY()
	
public:

	// Path Params
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Transaction Id", Category="Beam")
	int64 TransactionId = {};
	
	// Query Params
	

	// Body Params
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="", Category="Beam")
	UUpdatePaymentRequestBody* Body = {};

	// Beam Base Request Declaration
	UPatchPaymentRequest() = default;

	virtual void BuildVerb(FString& VerbString) const override;
	virtual void BuildRoute(FString& RouteString) const override;
	virtual void BuildBody(FString& BodyString) const override;

	UFUNCTION(BlueprintPure, BlueprintInternalUseOnly, Category="Beam|Payment|Utils|Make/Break", DisplayName="Make PatchPayment",  meta=(DefaultToSelf="RequestOwner", AdvancedDisplay="_Reason,RequestOwner", AutoCreateRefTerm="CustomHeaders"))
	static UPatchPaymentRequest* Make(int64 _TransactionId, EBeamTransactionState _State, FOptionalString _Reason, UObject* RequestOwner, TMap<FString, FString> CustomHeaders);
};

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnPatchPaymentSuccess, FBeamRequestContext, Context, UPatchPaymentRequest*, Request, UTransaction*, Response);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnPatchPaymentError, FBeamRequestContext, Context, UPatchPaymentRequest*, Request, FBeamErrorResponse, Error);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnPatchPaymentComplete, FBeamRequestContext, Context, UPatchPaymentRequest*, Request);

using FPatchPaymentFullResponse = FBeamFullResponse<UPatchPaymentRequest*, UTransaction*>;
DECLARE_DELEGATE_OneParam(FOnPatchPaymentFullResponse, FPatchPaymentFullResponse);
