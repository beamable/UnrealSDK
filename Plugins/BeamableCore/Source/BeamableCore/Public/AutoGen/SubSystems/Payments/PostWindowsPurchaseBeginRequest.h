
#pragma once

#include "CoreMinimal.h"
#include "BeamBackend/BeamBaseRequestInterface.h"
#include "BeamBackend/BeamRequestContext.h"
#include "BeamBackend/BeamErrorResponse.h"
#include "BeamBackend/BeamFullResponse.h"

#include "AutoGen/BeginPurchaseRequestBody.h"
#include "AutoGen/BeginPurchaseResponse.h"

#include "PostWindowsPurchaseBeginRequest.generated.h"

UCLASS(BlueprintType)
class BEAMABLECORE_API UPostWindowsPurchaseBeginRequest : public UObject, public IBeamBaseRequestInterface
{
	GENERATED_BODY()
	
public:

	// Path Params
	
	
	// Query Params
	

	// Body Params
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="", Category="Beam")
	UBeginPurchaseRequestBody* Body;

	// Beam Base Request Declaration
	UPostWindowsPurchaseBeginRequest() = default;

	virtual void BuildVerb(FString& VerbString) const override;
	virtual void BuildRoute(FString& RouteString) const override;
	virtual void BuildBody(FString& BodyString) const override;

	UFUNCTION(BlueprintPure, BlueprintInternalUseOnly, Category="Beam|Backend|Payments", DisplayName="Beam - Make PostWindowsPurchaseBegin",  meta=(DefaultToSelf="Outer", AdvancedDisplay="_Language,_Time,Outer"))
	static UPostWindowsPurchaseBeginRequest* Make(FString _PurchaseId, FOptionalString _Language, FOptionalString _Time, UObject* Outer);
};

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnPostWindowsPurchaseBeginSuccess, FBeamRequestContext, Context, UPostWindowsPurchaseBeginRequest*, Request, UBeginPurchaseResponse*, Response);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnPostWindowsPurchaseBeginError, FBeamRequestContext, Context, UPostWindowsPurchaseBeginRequest*, Request, FBeamErrorResponse, Error);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnPostWindowsPurchaseBeginComplete, FBeamRequestContext, Context, UPostWindowsPurchaseBeginRequest*, Request);

using FPostWindowsPurchaseBeginFullResponse = FBeamFullResponse<UPostWindowsPurchaseBeginRequest*, UBeginPurchaseResponse*>;
DECLARE_DELEGATE_OneParam(FOnPostWindowsPurchaseBeginFullResponse, FPostWindowsPurchaseBeginFullResponse);
