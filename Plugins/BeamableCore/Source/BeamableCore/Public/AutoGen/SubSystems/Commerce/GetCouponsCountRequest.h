
#pragma once

#include "CoreMinimal.h"
#include "BeamCoreTypes.h"


#include "AutoGen/GetTotalCouponResponse.h"

#include "GetCouponsCountRequest.generated.h"

UCLASS(BlueprintType)
class BEAMABLECORE_API UGetCouponsCountRequest : public UObject, public IBeamBaseRequestInterface
{
	GENERATED_BODY()
	
public:

	// Path Params
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Object Id")
	int64 ObjectId;
	
	// Query Params
	

	// Body Params
	

	// Beam Base Request Declaration
	UGetCouponsCountRequest() = default;

	virtual void BuildVerb(FString& VerbString) const override;
	virtual void BuildRoute(FString& RouteString) const override;
	virtual void BuildBody(FString& BodyString) const override;

	UFUNCTION(BlueprintPure, meta=(DefaultToSelf="Outer", AdvancedDisplay="Outer"))
	static UGetCouponsCountRequest* MakeGetCouponsCountRequest(int64 _ObjectId, UObject* Outer);
};

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnGetCouponsCountSuccess, FBeamRequestContext, Context, UGetCouponsCountRequest*, Request, UGetTotalCouponResponse*, Response);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnGetCouponsCountError, FBeamRequestContext, Context, UGetCouponsCountRequest*, Request, FBeamErrorResponse, Error);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnGetCouponsCountComplete, FBeamRequestContext, Context, UGetCouponsCountRequest*, Request);

using FGetCouponsCountFullResponse = FBeamFullResponse<UGetCouponsCountRequest*, UGetTotalCouponResponse*>;
DECLARE_DELEGATE_OneParam(FOnGetCouponsCountFullResponse, FGetCouponsCountFullResponse);
