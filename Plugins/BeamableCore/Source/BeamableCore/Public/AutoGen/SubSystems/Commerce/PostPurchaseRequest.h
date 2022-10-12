
#pragma once

#include "CoreMinimal.h"
#include "BeamCoreTypes.h"


#include "AutoGen/PurchaseRequestBody.h"
#include "AutoGen/CommonResponse.h"

#include "PostPurchaseRequest.generated.h"

UCLASS(BlueprintType)
class BEAMABLECORE_API UPostPurchaseRequest : public UObject, public IBeamBaseRequestInterface
{
	GENERATED_BODY()
	
public:

	// Path Params
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Object Id")
	int64 ObjectId;
	
	// Query Params
	

	// Body Params
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="")
	UPurchaseRequestBody* Body;

	// Beam Base Request Declaration
	UPostPurchaseRequest() = default;

	virtual void BuildVerb(FString& VerbString) const override;
	virtual void BuildRoute(FString& RouteString) const override;
	virtual void BuildBody(FString& BodyString) const override;

	UFUNCTION(BlueprintPure, meta=(DefaultToSelf="Outer", AdvancedDisplay="Outer"))
	static UPostPurchaseRequest* MakePostPurchaseRequest(int64 _ObjectId, FString _PurchaseId, UObject* Outer);
};

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnPostPurchaseSuccess, FBeamRequestContext, Context, UPostPurchaseRequest*, Request, UCommonResponse*, Response);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnPostPurchaseError, FBeamRequestContext, Context, UPostPurchaseRequest*, Request, FBeamErrorResponse, Error);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnPostPurchaseComplete, FBeamRequestContext, Context, UPostPurchaseRequest*, Request);

using FPostPurchaseFullResponse = FBeamFullResponse<UPostPurchaseRequest*, UCommonResponse*>;
DECLARE_DELEGATE_OneParam(FOnPostPurchaseFullResponse, FPostPurchaseFullResponse);
