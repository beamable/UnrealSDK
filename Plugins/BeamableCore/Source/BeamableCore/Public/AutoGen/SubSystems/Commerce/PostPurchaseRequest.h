
#pragma once

#include "CoreMinimal.h"
#include "BeamBackend/BeamBaseRequestInterface.h"
#include "BeamBackend/BeamRequestContext.h"
#include "BeamBackend/BeamErrorResponse.h"
#include "BeamBackend/BeamFullResponse.h"

#include "Serialization/BeamJsonUtils.h"
#include "BeamableCore/Public/AutoGen/PurchaseRequestBody.h"
#include "BeamableCore/Public/AutoGen/CommonResponse.h"

#include "PostPurchaseRequest.generated.h"

UCLASS(BlueprintType)
class BEAMABLECORE_API UPostPurchaseRequest : public UObject, public IBeamBaseRequestInterface
{
	GENERATED_BODY()
	
public:

	// Path Params
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Object Id", Category="Beam")
	int64 ObjectId = {};
	
	// Query Params
	

	// Body Params
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="", Category="Beam")
	UPurchaseRequestBody* Body = {};

	// Beam Base Request Declaration
	UPostPurchaseRequest() = default;

	virtual void BuildVerb(FString& VerbString) const override;
	virtual void BuildRoute(FString& RouteString) const override;
	virtual void BuildBody(FString& BodyString) const override;

	UFUNCTION(BlueprintPure, BlueprintInternalUseOnly, Category="Beam|Commerce|Utils|Make/Break", DisplayName="Make PostPurchase",  meta=(DefaultToSelf="RequestOwner", AdvancedDisplay="RequestOwner", AutoCreateRefTerm="CustomHeaders"))
	static UPostPurchaseRequest* Make(int64 _ObjectId, FString _PurchaseId, UObject* RequestOwner, TMap<FString, FString> CustomHeaders);
};

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnPostPurchaseSuccess, FBeamRequestContext, Context, UPostPurchaseRequest*, Request, UCommonResponse*, Response);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnPostPurchaseError, FBeamRequestContext, Context, UPostPurchaseRequest*, Request, FBeamErrorResponse, Error);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnPostPurchaseComplete, FBeamRequestContext, Context, UPostPurchaseRequest*, Request);

using FPostPurchaseFullResponse = FBeamFullResponse<UPostPurchaseRequest*, UCommonResponse*>;
DECLARE_DELEGATE_OneParam(FOnPostPurchaseFullResponse, FPostPurchaseFullResponse);
