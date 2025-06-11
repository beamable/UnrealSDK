
#pragma once

#include "CoreMinimal.h"
#include "BeamBackend/BeamBaseRequestInterface.h"
#include "BeamBackend/BeamRequestContext.h"
#include "BeamBackend/BeamErrorResponse.h"
#include "BeamBackend/BeamFullResponse.h"

#include "BeamableCore/Public/AutoGen/VerifyPurchaseRequestBody.h"
#include "BeamableCore/Public/AutoGen/PaymentResultResponse.h"

#include "PostGoogleplayPurchaseVerifyRequest.generated.h"

UCLASS(BlueprintType)
class BEAMABLECORE_API UPostGoogleplayPurchaseVerifyRequest : public UObject, public IBeamBaseRequestInterface
{
	GENERATED_BODY()
	
public:

	// Path Params
	
	
	// Query Params
	

	// Body Params
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="", Category="Beam")
	UVerifyPurchaseRequestBody* Body = {};

	// Beam Base Request Declaration
	UPostGoogleplayPurchaseVerifyRequest() = default;

	virtual void BuildVerb(FString& VerbString) const override;
	virtual void BuildRoute(FString& RouteString) const override;
	virtual void BuildBody(FString& BodyString) const override;

	UFUNCTION(BlueprintPure, BlueprintInternalUseOnly, Category="Beam|Payments|Utils|Make/Break", DisplayName="Make PostGoogleplayPurchaseVerify",  meta=(DefaultToSelf="RequestOwner", AdvancedDisplay="RequestOwner", AutoCreateRefTerm="CustomHeaders"))
	static UPostGoogleplayPurchaseVerifyRequest* Make(FString _Receipt, UObject* RequestOwner, TMap<FString, FString> CustomHeaders);
};

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnPostGoogleplayPurchaseVerifySuccess, FBeamRequestContext, Context, UPostGoogleplayPurchaseVerifyRequest*, Request, UPaymentResultResponse*, Response);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnPostGoogleplayPurchaseVerifyError, FBeamRequestContext, Context, UPostGoogleplayPurchaseVerifyRequest*, Request, FBeamErrorResponse, Error);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnPostGoogleplayPurchaseVerifyComplete, FBeamRequestContext, Context, UPostGoogleplayPurchaseVerifyRequest*, Request);

using FPostGoogleplayPurchaseVerifyFullResponse = FBeamFullResponse<UPostGoogleplayPurchaseVerifyRequest*, UPaymentResultResponse*>;
DECLARE_DELEGATE_OneParam(FOnPostGoogleplayPurchaseVerifyFullResponse, FPostGoogleplayPurchaseVerifyFullResponse);
