
#pragma once

#include "CoreMinimal.h"
#include "BeamCoreTypes.h"


#include "AutoGen/GetProductResponse.h"

#include "GetCouponProductRequest.generated.h"

UCLASS(BlueprintType)
class BEAMABLECORE_API UGetCouponProductRequest : public UObject, public IBeamBaseRequestInterface
{
	GENERATED_BODY()
	
public:

	// Path Params
	
	
	// Query Params
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Sku")
	FString Sku;

	// Body Params
	

	// Beam Base Request Declaration
	UGetCouponProductRequest() = default;

	virtual void BuildVerb(FString& VerbString) const override;
	virtual void BuildRoute(FString& RouteString) const override;
	virtual void BuildBody(FString& BodyString) const override;

	UFUNCTION(BlueprintPure, meta=(DefaultToSelf="Outer", AdvancedDisplay="Outer"))
	static UGetCouponProductRequest* MakeGetCouponProductRequest(FString _Sku, UObject* Outer);
};

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnGetCouponProductSuccess, FBeamRequestContext, Context, UGetCouponProductRequest*, Request, UGetProductResponse*, Response);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnGetCouponProductError, FBeamRequestContext, Context, UGetCouponProductRequest*, Request, FBeamErrorResponse, Error);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnGetCouponProductComplete, FBeamRequestContext, Context, UGetCouponProductRequest*, Request);

using FGetCouponProductFullResponse = FBeamFullResponse<UGetCouponProductRequest*, UGetProductResponse*>;
DECLARE_DELEGATE_OneParam(FOnGetCouponProductFullResponse, FGetCouponProductFullResponse);
