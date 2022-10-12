
#pragma once

#include "CoreMinimal.h"
#include "BeamCoreTypes.h"

#include "AutoGen/FailPurchaseRequestBody.h"
#include "AutoGen/PaymentResultResponse.h"

#include "PostGoogleplayPurchaseFailRequest.generated.h"

UCLASS(BlueprintType)
class BEAMABLECORE_API UPostGoogleplayPurchaseFailRequest : public UObject, public IBeamBaseRequestInterface
{
	GENERATED_BODY()
	
public:

	// Path Params
	
	
	// Query Params
	

	// Body Params
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="")
	UFailPurchaseRequestBody* Body;

	// Beam Base Request Declaration
	UPostGoogleplayPurchaseFailRequest() = default;

	virtual void BuildVerb(FString& VerbString) const override;
	virtual void BuildRoute(FString& RouteString) const override;
	virtual void BuildBody(FString& BodyString) const override;

	UFUNCTION(BlueprintPure, meta=(DefaultToSelf="Outer", AdvancedDisplay="Outer"))
	static UPostGoogleplayPurchaseFailRequest* MakePostGoogleplayPurchaseFailRequest(int64 _Txid, FString _Reason, UObject* Outer);
};

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnPostGoogleplayPurchaseFailSuccess, FBeamRequestContext, Context, UPostGoogleplayPurchaseFailRequest*, Request, UPaymentResultResponse*, Response);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnPostGoogleplayPurchaseFailError, FBeamRequestContext, Context, UPostGoogleplayPurchaseFailRequest*, Request, FBeamErrorResponse, Error);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnPostGoogleplayPurchaseFailComplete, FBeamRequestContext, Context, UPostGoogleplayPurchaseFailRequest*, Request);

using FPostGoogleplayPurchaseFailFullResponse = FBeamFullResponse<UPostGoogleplayPurchaseFailRequest*, UPaymentResultResponse*>;
DECLARE_DELEGATE_OneParam(FOnPostGoogleplayPurchaseFailFullResponse, FPostGoogleplayPurchaseFailFullResponse);
