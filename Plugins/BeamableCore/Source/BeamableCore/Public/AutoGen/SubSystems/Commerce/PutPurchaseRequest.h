
#pragma once

#include "CoreMinimal.h"
#include "BeamCoreTypes.h"


#include "AutoGen/ReportPurchaseRequestBody.h"
#include "AutoGen/ResultResponse.h"

#include "PutPurchaseRequest.generated.h"

UCLASS(BlueprintType)
class BEAMABLECORE_API UPutPurchaseRequest : public UObject, public IBeamBaseRequestInterface
{
	GENERATED_BODY()
	
public:

	// Path Params
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Object Id")
	int64 ObjectId;
	
	// Query Params
	

	// Body Params
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="")
	UReportPurchaseRequestBody* Body;

	// Beam Base Request Declaration
	UPutPurchaseRequest() = default;

	virtual void BuildVerb(FString& VerbString) const override;
	virtual void BuildRoute(FString& RouteString) const override;
	virtual void BuildBody(FString& BodyString) const override;

	UFUNCTION(BlueprintPure, meta=(DefaultToSelf="Outer", AdvancedDisplay="_bFree,Outer"))
	static UPutPurchaseRequest* MakePutPurchaseRequest(int64 _ObjectId, FString _ListingId, FOptionalBool _bFree, UObject* Outer);
};

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnPutPurchaseSuccess, FBeamRequestContext, Context, UPutPurchaseRequest*, Request, UResultResponse*, Response);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnPutPurchaseError, FBeamRequestContext, Context, UPutPurchaseRequest*, Request, FBeamErrorResponse, Error);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnPutPurchaseComplete, FBeamRequestContext, Context, UPutPurchaseRequest*, Request);

using FPutPurchaseFullResponse = FBeamFullResponse<UPutPurchaseRequest*, UResultResponse*>;
DECLARE_DELEGATE_OneParam(FOnPutPurchaseFullResponse, FPutPurchaseFullResponse);
