
#pragma once

#include "CoreMinimal.h"
#include "BeamBackend/BeamBaseRequestInterface.h"
#include "BeamBackend/BeamRequestContext.h"
#include "BeamBackend/BeamErrorResponse.h"
#include "BeamBackend/BeamFullResponse.h"

#include "BeamableCore/Public/AutoGen/GetTransactionsResponse.h"

#include "ApiPaymentGetPaymentsRequest.generated.h"

UCLASS(BlueprintType)
class BEAMABLECORE_API UApiPaymentGetPaymentsRequest : public UObject, public IBeamBaseRequestInterface
{
	GENERATED_BODY()
	
public:

	// Path Params
	
	
	// Query Params
	

	// Body Params
	

	// Beam Base Request Declaration
	UApiPaymentGetPaymentsRequest() = default;

	virtual void BuildVerb(FString& VerbString) const override;
	virtual void BuildRoute(FString& RouteString) const override;
	virtual void BuildBody(FString& BodyString) const override;

	UFUNCTION(BlueprintPure, BlueprintInternalUseOnly, Category="Beam|Payment|Utils|Make/Break", DisplayName="Make ApiPaymentGetPayments",  meta=(DefaultToSelf="RequestOwner", AdvancedDisplay="RequestOwner", AutoCreateRefTerm="CustomHeaders"))
	static UApiPaymentGetPaymentsRequest* Make(UObject* RequestOwner, TMap<FString, FString> CustomHeaders);
};

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnApiPaymentGetPaymentsSuccess, FBeamRequestContext, Context, UApiPaymentGetPaymentsRequest*, Request, UGetTransactionsResponse*, Response);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnApiPaymentGetPaymentsError, FBeamRequestContext, Context, UApiPaymentGetPaymentsRequest*, Request, FBeamErrorResponse, Error);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnApiPaymentGetPaymentsComplete, FBeamRequestContext, Context, UApiPaymentGetPaymentsRequest*, Request);

using FApiPaymentGetPaymentsFullResponse = FBeamFullResponse<UApiPaymentGetPaymentsRequest*, UGetTransactionsResponse*>;
DECLARE_DELEGATE_OneParam(FOnApiPaymentGetPaymentsFullResponse, FApiPaymentGetPaymentsFullResponse);
