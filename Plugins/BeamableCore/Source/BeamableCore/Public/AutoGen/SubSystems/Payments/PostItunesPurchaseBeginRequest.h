
#pragma once

#include "CoreMinimal.h"
#include "BeamBackend/BeamBaseRequestInterface.h"
#include "BeamBackend/BeamRequestContext.h"
#include "BeamBackend/BeamErrorResponse.h"
#include "BeamBackend/BeamFullResponse.h"

#include "AutoGen/BeginPurchaseRequestBody.h"
#include "AutoGen/BeginPurchaseResponse.h"

#include "PostItunesPurchaseBeginRequest.generated.h"

UCLASS(BlueprintType)
class BEAMABLECORE_API UPostItunesPurchaseBeginRequest : public UObject, public IBeamBaseRequestInterface
{
	GENERATED_BODY()
	
public:

	// Path Params
	
	
	// Query Params
	

	// Body Params
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="", Category="Beam")
	UBeginPurchaseRequestBody* Body;

	// Beam Base Request Declaration
	UPostItunesPurchaseBeginRequest() = default;

	virtual void BuildVerb(FString& VerbString) const override;
	virtual void BuildRoute(FString& RouteString) const override;
	virtual void BuildBody(FString& BodyString) const override;

	UFUNCTION(BlueprintPure, BlueprintInternalUseOnly, Category="Beam|Backend|Payments", DisplayName="Beam - Make PostItunesPurchaseBegin",  meta=(DefaultToSelf="Outer", AdvancedDisplay="_Language,_Time,Outer"))
	static UPostItunesPurchaseBeginRequest* Make(FString _PurchaseId, FOptionalString _Language, FOptionalString _Time, UObject* Outer);
};

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnPostItunesPurchaseBeginSuccess, FBeamRequestContext, Context, UPostItunesPurchaseBeginRequest*, Request, UBeginPurchaseResponse*, Response);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnPostItunesPurchaseBeginError, FBeamRequestContext, Context, UPostItunesPurchaseBeginRequest*, Request, FBeamErrorResponse, Error);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnPostItunesPurchaseBeginComplete, FBeamRequestContext, Context, UPostItunesPurchaseBeginRequest*, Request);

using FPostItunesPurchaseBeginFullResponse = FBeamFullResponse<UPostItunesPurchaseBeginRequest*, UBeginPurchaseResponse*>;
DECLARE_DELEGATE_OneParam(FOnPostItunesPurchaseBeginFullResponse, FPostItunesPurchaseBeginFullResponse);
