
#pragma once

#include "CoreMinimal.h"
#include "BeamBackend/BeamBaseRequestInterface.h"
#include "BeamBackend/BeamRequestContext.h"
#include "BeamBackend/BeamErrorResponse.h"
#include "BeamBackend/BeamFullResponse.h"

#include "BeamableCore/Public/AutoGen/FailPurchaseRequestBody.h"
#include "BeamableCore/Public/AutoGen/PaymentResultResponse.h"

#include "PostFacebookPurchaseFailRequest.generated.h"

UCLASS(BlueprintType)
class BEAMABLECORE_API UPostFacebookPurchaseFailRequest : public UObject, public IBeamBaseRequestInterface
{
	GENERATED_BODY()
	
public:

	// Path Params
	
	
	// Query Params
	

	// Body Params
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="", Category="Beam")
	UFailPurchaseRequestBody* Body = {};

	// Beam Base Request Declaration
	UPostFacebookPurchaseFailRequest() = default;

	virtual void BuildVerb(FString& VerbString) const override;
	virtual void BuildRoute(FString& RouteString) const override;
	virtual void BuildBody(FString& BodyString) const override;

	UFUNCTION(BlueprintPure, BlueprintInternalUseOnly, Category="Beam|Payments|Utils|Make/Break", DisplayName="Make PostFacebookPurchaseFail",  meta=(DefaultToSelf="RequestOwner", AdvancedDisplay="RequestOwner", AutoCreateRefTerm="CustomHeaders"))
	static UPostFacebookPurchaseFailRequest* Make(int64 _Txid, FString _Reason, UObject* RequestOwner, TMap<FString, FString> CustomHeaders);
};

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnPostFacebookPurchaseFailSuccess, FBeamRequestContext, Context, UPostFacebookPurchaseFailRequest*, Request, UPaymentResultResponse*, Response);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnPostFacebookPurchaseFailError, FBeamRequestContext, Context, UPostFacebookPurchaseFailRequest*, Request, FBeamErrorResponse, Error);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnPostFacebookPurchaseFailComplete, FBeamRequestContext, Context, UPostFacebookPurchaseFailRequest*, Request);

using FPostFacebookPurchaseFailFullResponse = FBeamFullResponse<UPostFacebookPurchaseFailRequest*, UPaymentResultResponse*>;
DECLARE_DELEGATE_OneParam(FOnPostFacebookPurchaseFailFullResponse, FPostFacebookPurchaseFailFullResponse);
