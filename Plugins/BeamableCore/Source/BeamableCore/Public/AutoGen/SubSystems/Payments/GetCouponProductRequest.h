
#pragma once

#include "CoreMinimal.h"
#include "BeamBackend/BeamBaseRequestInterface.h"
#include "BeamBackend/BeamRequestContext.h"
#include "BeamBackend/BeamErrorResponse.h"
#include "BeamBackend/BeamFullResponse.h"

#include "Serialization/BeamJsonUtils.h"
#include "BeamableCore/Public/AutoGen/GetProductResponse.h"

#include "GetCouponProductRequest.generated.h"

UCLASS(BlueprintType)
class BEAMABLECORE_API UGetCouponProductRequest : public UObject, public IBeamBaseRequestInterface
{
	GENERATED_BODY()
	
public:

	// Path Params
	
	
	// Query Params
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Sku", Category="Beam")
	FString Sku = {};

	// Body Params
	

	// Beam Base Request Declaration
	UGetCouponProductRequest() = default;

	virtual void BuildVerb(FString& VerbString) const override;
	virtual void BuildRoute(FString& RouteString) const override;
	virtual void BuildBody(FString& BodyString) const override;

	UFUNCTION(BlueprintPure, BlueprintInternalUseOnly, Category="Beam|Payments|Utils|Make/Break", DisplayName="Make GetCouponProduct",  meta=(DefaultToSelf="RequestOwner", AdvancedDisplay="RequestOwner", AutoCreateRefTerm="CustomHeaders"))
	static UGetCouponProductRequest* Make(FString _Sku, UObject* RequestOwner, TMap<FString, FString> CustomHeaders);
};

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnGetCouponProductSuccess, FBeamRequestContext, Context, UGetCouponProductRequest*, Request, UGetProductResponse*, Response);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnGetCouponProductError, FBeamRequestContext, Context, UGetCouponProductRequest*, Request, FBeamErrorResponse, Error);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnGetCouponProductComplete, FBeamRequestContext, Context, UGetCouponProductRequest*, Request);

using FGetCouponProductFullResponse = FBeamFullResponse<UGetCouponProductRequest*, UGetProductResponse*>;
DECLARE_DELEGATE_OneParam(FOnGetCouponProductFullResponse, FGetCouponProductFullResponse);
