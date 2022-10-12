
#pragma once

#include "CoreMinimal.h"
#include "BeamCoreTypes.h"

#include "AutoGen/GetGameResponse.h"

#include "GetGamesRequest.generated.h"

UCLASS(BlueprintType)
class BEAMABLECORE_API UGetGamesRequest : public UObject, public IBeamBaseRequestInterface
{
	GENERATED_BODY()
	
public:

	// Path Params
	
	
	// Query Params
	

	// Body Params
	

	// Beam Base Request Declaration
	UGetGamesRequest() = default;

	virtual void BuildVerb(FString& VerbString) const override;
	virtual void BuildRoute(FString& RouteString) const override;
	virtual void BuildBody(FString& BodyString) const override;

	UFUNCTION(BlueprintPure, meta=(DefaultToSelf="Outer", AdvancedDisplay="Outer"))
	static UGetGamesRequest* MakeGetGamesRequest(UObject* Outer);
};

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnGetGamesSuccess, FBeamRequestContext, Context, UGetGamesRequest*, Request, UGetGameResponse*, Response);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnGetGamesError, FBeamRequestContext, Context, UGetGamesRequest*, Request, FBeamErrorResponse, Error);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnGetGamesComplete, FBeamRequestContext, Context, UGetGamesRequest*, Request);

using FGetGamesFullResponse = FBeamFullResponse<UGetGamesRequest*, UGetGameResponse*>;
DECLARE_DELEGATE_OneParam(FOnGetGamesFullResponse, FGetGamesFullResponse);
