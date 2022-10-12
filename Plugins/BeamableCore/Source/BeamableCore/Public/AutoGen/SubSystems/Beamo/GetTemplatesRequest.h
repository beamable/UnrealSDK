
#pragma once

#include "CoreMinimal.h"
#include "BeamCoreTypes.h"

#include "AutoGen/GetTemplatesResponse.h"

#include "GetTemplatesRequest.generated.h"

UCLASS(BlueprintType)
class BEAMABLECORE_API UGetTemplatesRequest : public UObject, public IBeamBaseRequestInterface
{
	GENERATED_BODY()
	
public:

	// Path Params
	
	
	// Query Params
	

	// Body Params
	

	// Beam Base Request Declaration
	UGetTemplatesRequest() = default;

	virtual void BuildVerb(FString& VerbString) const override;
	virtual void BuildRoute(FString& RouteString) const override;
	virtual void BuildBody(FString& BodyString) const override;

	UFUNCTION(BlueprintPure, meta=(DefaultToSelf="Outer", AdvancedDisplay="Outer"))
	static UGetTemplatesRequest* MakeGetTemplatesRequest(UObject* Outer);
};

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnGetTemplatesSuccess, FBeamRequestContext, Context, UGetTemplatesRequest*, Request, UGetTemplatesResponse*, Response);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnGetTemplatesError, FBeamRequestContext, Context, UGetTemplatesRequest*, Request, FBeamErrorResponse, Error);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnGetTemplatesComplete, FBeamRequestContext, Context, UGetTemplatesRequest*, Request);

using FGetTemplatesFullResponse = FBeamFullResponse<UGetTemplatesRequest*, UGetTemplatesResponse*>;
DECLARE_DELEGATE_OneParam(FOnGetTemplatesFullResponse, FGetTemplatesFullResponse);