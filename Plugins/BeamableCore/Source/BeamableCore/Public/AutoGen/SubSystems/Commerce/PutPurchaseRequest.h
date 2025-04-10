
#pragma once

#include "CoreMinimal.h"
#include "BeamBackend/BeamBaseRequestInterface.h"
#include "BeamBackend/BeamRequestContext.h"
#include "BeamBackend/BeamErrorResponse.h"
#include "BeamBackend/BeamFullResponse.h"

#include "Serialization/BeamJsonUtils.h"
#include "BeamableCore/Public/AutoGen/ReportPurchaseRequestBody.h"
#include "BeamableCore/Public/AutoGen/ResultResponse.h"

#include "PutPurchaseRequest.generated.h"

UCLASS(BlueprintType)
class BEAMABLECORE_API UPutPurchaseRequest : public UObject, public IBeamBaseRequestInterface
{
	GENERATED_BODY()
	
public:

	// Path Params
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Object Id", Category="Beam")
	int64 ObjectId = {};
	
	// Query Params
	

	// Body Params
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="", Category="Beam")
	UReportPurchaseRequestBody* Body = {};

	// Beam Base Request Declaration
	UPutPurchaseRequest() = default;

	virtual void BuildVerb(FString& VerbString) const override;
	virtual void BuildRoute(FString& RouteString) const override;
	virtual void BuildBody(FString& BodyString) const override;

	UFUNCTION(BlueprintPure, BlueprintInternalUseOnly, Category="Beam|Commerce|Utils|Make/Break", DisplayName="Make PutPurchase",  meta=(DefaultToSelf="RequestOwner", AdvancedDisplay="_bFree,RequestOwner", AutoCreateRefTerm="CustomHeaders"))
	static UPutPurchaseRequest* Make(int64 _ObjectId, FString _ListingId, FOptionalBool _bFree, UObject* RequestOwner, TMap<FString, FString> CustomHeaders);
};

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnPutPurchaseSuccess, FBeamRequestContext, Context, UPutPurchaseRequest*, Request, UResultResponse*, Response);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnPutPurchaseError, FBeamRequestContext, Context, UPutPurchaseRequest*, Request, FBeamErrorResponse, Error);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnPutPurchaseComplete, FBeamRequestContext, Context, UPutPurchaseRequest*, Request);

using FPutPurchaseFullResponse = FBeamFullResponse<UPutPurchaseRequest*, UResultResponse*>;
DECLARE_DELEGATE_OneParam(FOnPutPurchaseFullResponse, FPutPurchaseFullResponse);
