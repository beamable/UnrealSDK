
#pragma once

#include "CoreMinimal.h"
#include "BeamCoreTypes.h"

#include "AutoGen/Social.h"

#include "GetMyRequest.generated.h"

UCLASS(BlueprintType)
class BEAMABLECORE_API UGetMyRequest : public UObject, public IBeamBaseRequestInterface
{
	GENERATED_BODY()
	
public:

	// Path Params
	
	
	// Query Params
	

	// Body Params
	

	// Beam Base Request Declaration
	UGetMyRequest() = default;

	virtual void BuildVerb(FString& VerbString) const override;
	virtual void BuildRoute(FString& RouteString) const override;
	virtual void BuildBody(FString& BodyString) const override;

	UFUNCTION(BlueprintPure, meta=(DefaultToSelf="Outer", AdvancedDisplay="Outer"))
	static UGetMyRequest* MakeGetMyRequest(UObject* Outer);
};

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnGetMySuccess, FBeamRequestContext, Context, UGetMyRequest*, Request, USocial*, Response);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnGetMyError, FBeamRequestContext, Context, UGetMyRequest*, Request, FBeamErrorResponse, Error);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnGetMyComplete, FBeamRequestContext, Context, UGetMyRequest*, Request);

using FGetMyFullResponse = FBeamFullResponse<UGetMyRequest*, USocial*>;
DECLARE_DELEGATE_OneParam(FOnGetMyFullResponse, FGetMyFullResponse);
