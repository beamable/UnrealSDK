
#pragma once

#include "CoreMinimal.h"
#include "BeamBackend/BeamBaseRequestInterface.h"
#include "BeamBackend/BeamRequestContext.h"
#include "BeamBackend/BeamErrorResponse.h"
#include "BeamBackend/BeamFullResponse.h"

#include "BeamableCore/Public/AutoGen/BeginPaymentRequestBody.h"
#include "BeamableCore/Public/AutoGen/PaymentResponse.h"

#include "PostPaymentsRequest.generated.h"

UCLASS(BlueprintType)
class BEAMABLECORE_API UPostPaymentsRequest : public UObject, public IBeamBaseRequestInterface
{
	GENERATED_BODY()
	
public:

	// Path Params
	
	
	// Query Params
	

	// Body Params
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="", Category="Beam")
	UBeginPaymentRequestBody* Body = {};

	// Beam Base Request Declaration
	UPostPaymentsRequest() = default;

	virtual void BuildVerb(FString& VerbString) const override;
	virtual void BuildRoute(FString& RouteString) const override;
	virtual void BuildBody(FString& BodyString) const override;

	UFUNCTION(BlueprintPure, BlueprintInternalUseOnly, Category="Beam|Payment|Utils|Make/Break", DisplayName="Make PostPayments",  meta=(DefaultToSelf="RequestOwner", AdvancedDisplay="_InitHistoryData,RequestOwner", AutoCreateRefTerm="CustomHeaders"))
	static UPostPaymentsRequest* Make(FString _PlayerId, FString _PaymentProvider, UTransactionDetails* _Details, FOptionalString _InitHistoryData, UObject* RequestOwner, TMap<FString, FString> CustomHeaders);
};

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnPostPaymentsSuccess, FBeamRequestContext, Context, UPostPaymentsRequest*, Request, UPaymentResponse*, Response);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnPostPaymentsError, FBeamRequestContext, Context, UPostPaymentsRequest*, Request, FBeamErrorResponse, Error);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnPostPaymentsComplete, FBeamRequestContext, Context, UPostPaymentsRequest*, Request);

using FPostPaymentsFullResponse = FBeamFullResponse<UPostPaymentsRequest*, UPaymentResponse*>;
DECLARE_DELEGATE_OneParam(FOnPostPaymentsFullResponse, FPostPaymentsFullResponse);
