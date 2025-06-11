
#pragma once

#include "CoreMinimal.h"
#include "BeamBackend/BeamBaseRequestInterface.h"
#include "BeamBackend/BeamRequestContext.h"
#include "BeamBackend/BeamErrorResponse.h"
#include "BeamBackend/BeamFullResponse.h"

#include "Serialization/BeamJsonUtils.h"
#include "BeamableCore/Public/AutoGen/GiveCouponReq.h"
#include "BeamableCore/Public/AutoGen/CommonResponse.h"

#include "PostCouponsRequest.generated.h"

UCLASS(BlueprintType)
class BEAMABLECORE_API UPostCouponsRequest : public UObject, public IBeamBaseRequestInterface
{
	GENERATED_BODY()
	
public:

	// Path Params
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Object Id", Category="Beam")
	int64 ObjectId = {};
	
	// Query Params
	

	// Body Params
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="", Category="Beam")
	UGiveCouponReq* Body = {};

	// Beam Base Request Declaration
	UPostCouponsRequest() = default;

	virtual void BuildVerb(FString& VerbString) const override;
	virtual void BuildRoute(FString& RouteString) const override;
	virtual void BuildBody(FString& BodyString) const override;

	UFUNCTION(BlueprintPure, BlueprintInternalUseOnly, Category="Beam|Commerce|Utils|Make/Break", DisplayName="Make PostCoupons",  meta=(DefaultToSelf="RequestOwner", AdvancedDisplay="RequestOwner", AutoCreateRefTerm="CustomHeaders"))
	static UPostCouponsRequest* Make(int64 _ObjectId, FString _Listing, UObject* RequestOwner, TMap<FString, FString> CustomHeaders);
};

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnPostCouponsSuccess, FBeamRequestContext, Context, UPostCouponsRequest*, Request, UCommonResponse*, Response);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnPostCouponsError, FBeamRequestContext, Context, UPostCouponsRequest*, Request, FBeamErrorResponse, Error);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnPostCouponsComplete, FBeamRequestContext, Context, UPostCouponsRequest*, Request);

using FPostCouponsFullResponse = FBeamFullResponse<UPostCouponsRequest*, UCommonResponse*>;
DECLARE_DELEGATE_OneParam(FOnPostCouponsFullResponse, FPostCouponsFullResponse);
