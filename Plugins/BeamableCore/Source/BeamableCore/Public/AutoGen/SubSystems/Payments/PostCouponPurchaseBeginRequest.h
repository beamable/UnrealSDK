
#pragma once

#include "CoreMinimal.h"
#include "BeamBackend/BeamBaseRequestInterface.h"
#include "BeamBackend/BeamRequestContext.h"
#include "BeamBackend/BeamErrorResponse.h"
#include "BeamBackend/BeamFullResponse.h"

#include "BeamableCore/Public/AutoGen/BeginPurchaseRequestBody.h"
#include "BeamableCore/Public/AutoGen/BeginPurchaseResponse.h"

#include "PostCouponPurchaseBeginRequest.generated.h"

UCLASS(BlueprintType)
class BEAMABLECORE_API UPostCouponPurchaseBeginRequest : public UObject, public IBeamBaseRequestInterface
{
	GENERATED_BODY()
	
public:

	// Path Params
	
	
	// Query Params
	

	// Body Params
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="", Category="Beam")
	UBeginPurchaseRequestBody* Body = {};

	// Beam Base Request Declaration
	UPostCouponPurchaseBeginRequest() = default;

	virtual void BuildVerb(FString& VerbString) const override;
	virtual void BuildRoute(FString& RouteString) const override;
	virtual void BuildBody(FString& BodyString) const override;

	UFUNCTION(BlueprintPure, BlueprintInternalUseOnly, Category="Beam|Payments|Utils|Make/Break", DisplayName="Make PostCouponPurchaseBegin",  meta=(DefaultToSelf="RequestOwner", AdvancedDisplay="_Language,_Time,RequestOwner", AutoCreateRefTerm="CustomHeaders"))
	static UPostCouponPurchaseBeginRequest* Make(FString _PurchaseId, FOptionalString _Language, FOptionalString _Time, UObject* RequestOwner, TMap<FString, FString> CustomHeaders);
};

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnPostCouponPurchaseBeginSuccess, FBeamRequestContext, Context, UPostCouponPurchaseBeginRequest*, Request, UBeginPurchaseResponse*, Response);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnPostCouponPurchaseBeginError, FBeamRequestContext, Context, UPostCouponPurchaseBeginRequest*, Request, FBeamErrorResponse, Error);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnPostCouponPurchaseBeginComplete, FBeamRequestContext, Context, UPostCouponPurchaseBeginRequest*, Request);

using FPostCouponPurchaseBeginFullResponse = FBeamFullResponse<UPostCouponPurchaseBeginRequest*, UBeginPurchaseResponse*>;
DECLARE_DELEGATE_OneParam(FOnPostCouponPurchaseBeginFullResponse, FPostCouponPurchaseBeginFullResponse);
