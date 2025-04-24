
#pragma once

#include "CoreMinimal.h"
#include "BeamBackend/BeamBaseRequestInterface.h"
#include "BeamBackend/BeamRequestContext.h"
#include "BeamBackend/BeamErrorResponse.h"
#include "BeamBackend/BeamFullResponse.h"

#include "BeamableCore/Public/AutoGen/TrackPurchaseRequestBody.h"
#include "BeamableCore/Public/AutoGen/PaymentResultResponse.h"

#include "PostTestPurchaseTrackRequest.generated.h"

UCLASS(BlueprintType)
class BEAMABLECORE_API UPostTestPurchaseTrackRequest : public UObject, public IBeamBaseRequestInterface
{
	GENERATED_BODY()
	
public:

	// Path Params
	
	
	// Query Params
	

	// Body Params
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="", Category="Beam")
	UTrackPurchaseRequestBody* Body = {};

	// Beam Base Request Declaration
	UPostTestPurchaseTrackRequest() = default;

	virtual void BuildVerb(FString& VerbString) const override;
	virtual void BuildRoute(FString& RouteString) const override;
	virtual void BuildBody(FString& BodyString) const override;

	UFUNCTION(BlueprintPure, BlueprintInternalUseOnly, Category="Beam|Payments|Utils|Make/Break", DisplayName="Make PostTestPurchaseTrack",  meta=(DefaultToSelf="RequestOwner", AdvancedDisplay="RequestOwner", AutoCreateRefTerm="CustomHeaders"))
	static UPostTestPurchaseTrackRequest* Make(double _PriceInLocalCurrency, FString _SkuName, FString _SkuProductId, FString _Store, FString _PurchaseId, FString _IsoCurrencySymbol, TArray<UItemCreateRequestBody*> _ObtainItems, TArray<UCurrencyChange*> _ObtainCurrency, UObject* RequestOwner, TMap<FString, FString> CustomHeaders);
};

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnPostTestPurchaseTrackSuccess, FBeamRequestContext, Context, UPostTestPurchaseTrackRequest*, Request, UPaymentResultResponse*, Response);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnPostTestPurchaseTrackError, FBeamRequestContext, Context, UPostTestPurchaseTrackRequest*, Request, FBeamErrorResponse, Error);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnPostTestPurchaseTrackComplete, FBeamRequestContext, Context, UPostTestPurchaseTrackRequest*, Request);

using FPostTestPurchaseTrackFullResponse = FBeamFullResponse<UPostTestPurchaseTrackRequest*, UPaymentResultResponse*>;
DECLARE_DELEGATE_OneParam(FOnPostTestPurchaseTrackFullResponse, FPostTestPurchaseTrackFullResponse);
