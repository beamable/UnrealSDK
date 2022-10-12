
#pragma once

#include "CoreMinimal.h"
#include "BeamCoreTypes.h"

#include "AutoGen/FailPurchaseRequestBody.h"
#include "AutoGen/PaymentResultResponse.h"

#include "PostFacebookPurchaseFailRequest.generated.h"

UCLASS(BlueprintType)
class BEAMABLECORE_API UPostFacebookPurchaseFailRequest : public UObject, public IBeamBaseRequestInterface
{
	GENERATED_BODY()
	
public:

	// Path Params
	
	
	// Query Params
	

	// Body Params
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="")
	UFailPurchaseRequestBody* Body;

	// Beam Base Request Declaration
	UPostFacebookPurchaseFailRequest() = default;

	virtual void BuildVerb(FString& VerbString) const override;
	virtual void BuildRoute(FString& RouteString) const override;
	virtual void BuildBody(FString& BodyString) const override;

	UFUNCTION(BlueprintPure, meta=(DefaultToSelf="Outer", AdvancedDisplay="Outer"))
	static UPostFacebookPurchaseFailRequest* MakePostFacebookPurchaseFailRequest(int64 _Txid, FString _Reason, UObject* Outer);
};

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnPostFacebookPurchaseFailSuccess, FBeamRequestContext, Context, UPostFacebookPurchaseFailRequest*, Request, UPaymentResultResponse*, Response);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnPostFacebookPurchaseFailError, FBeamRequestContext, Context, UPostFacebookPurchaseFailRequest*, Request, FBeamErrorResponse, Error);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnPostFacebookPurchaseFailComplete, FBeamRequestContext, Context, UPostFacebookPurchaseFailRequest*, Request);

using FPostFacebookPurchaseFailFullResponse = FBeamFullResponse<UPostFacebookPurchaseFailRequest*, UPaymentResultResponse*>;
DECLARE_DELEGATE_OneParam(FOnPostFacebookPurchaseFailFullResponse, FPostFacebookPurchaseFailFullResponse);