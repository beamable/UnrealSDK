
#pragma once

#include "CoreMinimal.h"
#include "BeamCoreTypes.h"

#include "AutoGen/GetStatusResponse.h"

#include "GetStatusRequest.generated.h"

UCLASS(BlueprintType)
class BEAMABLECORE_API UGetStatusRequest : public UObject, public IBeamBaseRequestInterface
{
	GENERATED_BODY()
	
public:

	// Path Params
	
	
	// Query Params
	

	// Body Params
	

	// Beam Base Request Declaration
	UGetStatusRequest() = default;

	virtual void BuildVerb(FString& VerbString) const override;
	virtual void BuildRoute(FString& RouteString) const override;
	virtual void BuildBody(FString& BodyString) const override;

	UFUNCTION(BlueprintPure, meta=(DefaultToSelf="Outer", AdvancedDisplay="Outer"))
	static UGetStatusRequest* MakeGetStatusRequest(UObject* Outer);
};

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnGetStatusSuccess, FBeamRequestContext, Context, UGetStatusRequest*, Request, UGetStatusResponse*, Response);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnGetStatusError, FBeamRequestContext, Context, UGetStatusRequest*, Request, FBeamErrorResponse, Error);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnGetStatusComplete, FBeamRequestContext, Context, UGetStatusRequest*, Request);

using FGetStatusFullResponse = FBeamFullResponse<UGetStatusRequest*, UGetStatusResponse*>;
DECLARE_DELEGATE_OneParam(FOnGetStatusFullResponse, FGetStatusFullResponse);
