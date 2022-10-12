
#pragma once

#include "CoreMinimal.h"
#include "BeamCoreTypes.h"

#include "AutoGen/ServicePlansResponse.h"

#include "GetPlansRequest.generated.h"

UCLASS(BlueprintType)
class BEAMABLECORE_API UGetPlansRequest : public UObject, public IBeamBaseRequestInterface
{
	GENERATED_BODY()
	
public:

	// Path Params
	
	
	// Query Params
	

	// Body Params
	

	// Beam Base Request Declaration
	UGetPlansRequest() = default;

	virtual void BuildVerb(FString& VerbString) const override;
	virtual void BuildRoute(FString& RouteString) const override;
	virtual void BuildBody(FString& BodyString) const override;

	UFUNCTION(BlueprintPure, meta=(DefaultToSelf="Outer", AdvancedDisplay="Outer"))
	static UGetPlansRequest* MakeGetPlansRequest(UObject* Outer);
};

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnGetPlansSuccess, FBeamRequestContext, Context, UGetPlansRequest*, Request, UServicePlansResponse*, Response);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnGetPlansError, FBeamRequestContext, Context, UGetPlansRequest*, Request, FBeamErrorResponse, Error);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnGetPlansComplete, FBeamRequestContext, Context, UGetPlansRequest*, Request);

using FGetPlansFullResponse = FBeamFullResponse<UGetPlansRequest*, UServicePlansResponse*>;
DECLARE_DELEGATE_OneParam(FOnGetPlansFullResponse, FGetPlansFullResponse);