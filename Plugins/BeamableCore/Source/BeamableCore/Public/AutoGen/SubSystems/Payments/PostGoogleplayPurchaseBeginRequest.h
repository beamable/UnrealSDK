
#pragma once

#include "CoreMinimal.h"
#include "BeamBackend/BeamBaseRequestInterface.h"
#include "BeamBackend/BeamRequestContext.h"
#include "BeamBackend/BeamErrorResponse.h"
#include "BeamBackend/BeamFullResponse.h"

#include "BeamableCore/Public/AutoGen/BeginPurchaseRequestBody.h"
#include "BeamableCore/Public/AutoGen/BeginPurchaseResponse.h"

#include "PostGoogleplayPurchaseBeginRequest.generated.h"

UCLASS(BlueprintType)
class BEAMABLECORE_API UPostGoogleplayPurchaseBeginRequest : public UObject, public IBeamBaseRequestInterface
{
	GENERATED_BODY()
	
public:

	// Path Params
	
	
	// Query Params
	

	// Body Params
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="", Category="Beam")
	UBeginPurchaseRequestBody* Body = {};

	// Beam Base Request Declaration
	UPostGoogleplayPurchaseBeginRequest() = default;

	virtual void BuildVerb(FString& VerbString) const override;
	virtual void BuildRoute(FString& RouteString) const override;
	virtual void BuildBody(FString& BodyString) const override;

	UFUNCTION(BlueprintPure, BlueprintInternalUseOnly, Category="Beam|Payments|Utils|Make/Break", DisplayName="Make PostGoogleplayPurchaseBegin",  meta=(DefaultToSelf="RequestOwner", AdvancedDisplay="_Language,_Time,RequestOwner", AutoCreateRefTerm="CustomHeaders"))
	static UPostGoogleplayPurchaseBeginRequest* Make(FString _PurchaseId, FOptionalString _Language, FOptionalString _Time, UObject* RequestOwner, TMap<FString, FString> CustomHeaders);
};

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnPostGoogleplayPurchaseBeginSuccess, FBeamRequestContext, Context, UPostGoogleplayPurchaseBeginRequest*, Request, UBeginPurchaseResponse*, Response);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnPostGoogleplayPurchaseBeginError, FBeamRequestContext, Context, UPostGoogleplayPurchaseBeginRequest*, Request, FBeamErrorResponse, Error);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnPostGoogleplayPurchaseBeginComplete, FBeamRequestContext, Context, UPostGoogleplayPurchaseBeginRequest*, Request);

using FPostGoogleplayPurchaseBeginFullResponse = FBeamFullResponse<UPostGoogleplayPurchaseBeginRequest*, UBeginPurchaseResponse*>;
DECLARE_DELEGATE_OneParam(FOnPostGoogleplayPurchaseBeginFullResponse, FPostGoogleplayPurchaseBeginFullResponse);
