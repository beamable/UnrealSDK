
#pragma once

#include "CoreMinimal.h"
#include "BeamBackend/BeamBaseRequestInterface.h"
#include "BeamBackend/BeamRequestContext.h"
#include "BeamBackend/BeamErrorResponse.h"
#include "BeamBackend/BeamFullResponse.h"

#include "BeamableCore/Public/AutoGen/FailPurchaseRequestBody.h"
#include "BeamableCore/Public/AutoGen/PaymentResultResponse.h"

#include "PostSteamPurchaseFailRequest.generated.h"

UCLASS(BlueprintType)
class BEAMABLECORE_API UPostSteamPurchaseFailRequest : public UObject, public IBeamBaseRequestInterface
{
	GENERATED_BODY()
	
public:

	// Path Params
	
	
	// Query Params
	

	// Body Params
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="", Category="Beam")
	UFailPurchaseRequestBody* Body = {};

	// Beam Base Request Declaration
	UPostSteamPurchaseFailRequest() = default;

	virtual void BuildVerb(FString& VerbString) const override;
	virtual void BuildRoute(FString& RouteString) const override;
	virtual void BuildBody(FString& BodyString) const override;

	UFUNCTION(BlueprintPure, BlueprintInternalUseOnly, Category="Beam|Payments|Utils|Make/Break", DisplayName="Make PostSteamPurchaseFail",  meta=(DefaultToSelf="RequestOwner", AdvancedDisplay="RequestOwner", AutoCreateRefTerm="CustomHeaders"))
	static UPostSteamPurchaseFailRequest* Make(int64 _Txid, FString _Reason, UObject* RequestOwner, TMap<FString, FString> CustomHeaders);
};

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnPostSteamPurchaseFailSuccess, FBeamRequestContext, Context, UPostSteamPurchaseFailRequest*, Request, UPaymentResultResponse*, Response);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnPostSteamPurchaseFailError, FBeamRequestContext, Context, UPostSteamPurchaseFailRequest*, Request, FBeamErrorResponse, Error);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnPostSteamPurchaseFailComplete, FBeamRequestContext, Context, UPostSteamPurchaseFailRequest*, Request);

using FPostSteamPurchaseFailFullResponse = FBeamFullResponse<UPostSteamPurchaseFailRequest*, UPaymentResultResponse*>;
DECLARE_DELEGATE_OneParam(FOnPostSteamPurchaseFailFullResponse, FPostSteamPurchaseFailFullResponse);
