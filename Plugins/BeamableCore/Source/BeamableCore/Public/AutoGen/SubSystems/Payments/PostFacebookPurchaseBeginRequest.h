
#pragma once

#include "CoreMinimal.h"
#include "BeamBackend/BeamBaseRequestInterface.h"
#include "BeamBackend/BeamRequestContext.h"
#include "BeamBackend/BeamErrorResponse.h"
#include "BeamBackend/BeamFullResponse.h"

#include "AutoGen/BeginPurchaseRequestBody.h"
#include "AutoGen/BeginPurchaseResponse.h"

#include "PostFacebookPurchaseBeginRequest.generated.h"

UCLASS(BlueprintType)
class BEAMABLECORE_API UPostFacebookPurchaseBeginRequest : public UObject, public IBeamBaseRequestInterface
{
	GENERATED_BODY()
	
public:

	// Path Params
	
	
	// Query Params
	

	// Body Params
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="", Category="Beam")
	UBeginPurchaseRequestBody* Body;

	// Beam Base Request Declaration
	UPostFacebookPurchaseBeginRequest() = default;

	virtual void BuildVerb(FString& VerbString) const override;
	virtual void BuildRoute(FString& RouteString) const override;
	virtual void BuildBody(FString& BodyString) const override;

	UFUNCTION(BlueprintPure, BlueprintInternalUseOnly, Category="Beam|Backend|Payments", DisplayName="Beam - Make PostFacebookPurchaseBegin",  meta=(DefaultToSelf="RequestOwner", AdvancedDisplay="_Language,_Time,RequestOwner"))
	static UPostFacebookPurchaseBeginRequest* Make(FString _PurchaseId, FOptionalString _Language, FOptionalString _Time, UObject* RequestOwner);
};

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnPostFacebookPurchaseBeginSuccess, FBeamRequestContext, Context, UPostFacebookPurchaseBeginRequest*, Request, UBeginPurchaseResponse*, Response);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnPostFacebookPurchaseBeginError, FBeamRequestContext, Context, UPostFacebookPurchaseBeginRequest*, Request, FBeamErrorResponse, Error);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnPostFacebookPurchaseBeginComplete, FBeamRequestContext, Context, UPostFacebookPurchaseBeginRequest*, Request);

using FPostFacebookPurchaseBeginFullResponse = FBeamFullResponse<UPostFacebookPurchaseBeginRequest*, UBeginPurchaseResponse*>;
DECLARE_DELEGATE_OneParam(FOnPostFacebookPurchaseBeginFullResponse, FPostFacebookPurchaseBeginFullResponse);
