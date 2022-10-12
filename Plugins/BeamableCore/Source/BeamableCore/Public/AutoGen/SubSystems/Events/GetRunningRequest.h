
#pragma once

#include "CoreMinimal.h"
#include "BeamCoreTypes.h"

#include "AutoGen/EventQueryResponse.h"

#include "GetRunningRequest.generated.h"

UCLASS(BlueprintType)
class BEAMABLECORE_API UGetRunningRequest : public UObject, public IBeamBaseRequestInterface
{
	GENERATED_BODY()
	
public:

	// Path Params
	
	
	// Query Params
	

	// Body Params
	

	// Beam Base Request Declaration
	UGetRunningRequest() = default;

	virtual void BuildVerb(FString& VerbString) const override;
	virtual void BuildRoute(FString& RouteString) const override;
	virtual void BuildBody(FString& BodyString) const override;

	UFUNCTION(BlueprintPure, meta=(DefaultToSelf="Outer", AdvancedDisplay="Outer"))
	static UGetRunningRequest* MakeGetRunningRequest(UObject* Outer);
};

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnGetRunningSuccess, FBeamRequestContext, Context, UGetRunningRequest*, Request, UEventQueryResponse*, Response);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnGetRunningError, FBeamRequestContext, Context, UGetRunningRequest*, Request, FBeamErrorResponse, Error);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnGetRunningComplete, FBeamRequestContext, Context, UGetRunningRequest*, Request);

using FGetRunningFullResponse = FBeamFullResponse<UGetRunningRequest*, UEventQueryResponse*>;
DECLARE_DELEGATE_OneParam(FOnGetRunningFullResponse, FGetRunningFullResponse);
