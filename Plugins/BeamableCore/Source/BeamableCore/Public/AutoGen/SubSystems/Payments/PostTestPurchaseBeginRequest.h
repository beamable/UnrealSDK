
#pragma once

#include "CoreMinimal.h"
#include "BeamBackend/BeamBaseRequestInterface.h"
#include "BeamBackend/BeamRequestContext.h"
#include "BeamBackend/BeamErrorResponse.h"
#include "BeamBackend/BeamFullResponse.h"

#include "AutoGen/BeginPurchaseRequestBody.h"
#include "AutoGen/BeginPurchaseResponse.h"

#include "PostTestPurchaseBeginRequest.generated.h"

UCLASS(BlueprintType)
class BEAMABLECORE_API UPostTestPurchaseBeginRequest : public UObject, public IBeamBaseRequestInterface
{
	GENERATED_BODY()
	
public:

	// Path Params
	
	
	// Query Params
	

	// Body Params
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="", Category="Beam")
	UBeginPurchaseRequestBody* Body;

	// Beam Base Request Declaration
	UPostTestPurchaseBeginRequest() = default;

	virtual void BuildVerb(FString& VerbString) const override;
	virtual void BuildRoute(FString& RouteString) const override;
	virtual void BuildBody(FString& BodyString) const override;

	UFUNCTION(BlueprintPure, BlueprintInternalUseOnly, Category="Beam|Backend|Payments", DisplayName="Beam - Make PostTestPurchaseBegin",  meta=(DefaultToSelf="Outer", AdvancedDisplay="_Language,_Time,Outer"))
	static UPostTestPurchaseBeginRequest* Make(FString _PurchaseId, FOptionalString _Language, FOptionalString _Time, UObject* Outer);
};

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnPostTestPurchaseBeginSuccess, FBeamRequestContext, Context, UPostTestPurchaseBeginRequest*, Request, UBeginPurchaseResponse*, Response);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnPostTestPurchaseBeginError, FBeamRequestContext, Context, UPostTestPurchaseBeginRequest*, Request, FBeamErrorResponse, Error);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnPostTestPurchaseBeginComplete, FBeamRequestContext, Context, UPostTestPurchaseBeginRequest*, Request);

using FPostTestPurchaseBeginFullResponse = FBeamFullResponse<UPostTestPurchaseBeginRequest*, UBeginPurchaseResponse*>;
DECLARE_DELEGATE_OneParam(FOnPostTestPurchaseBeginFullResponse, FPostTestPurchaseBeginFullResponse);
