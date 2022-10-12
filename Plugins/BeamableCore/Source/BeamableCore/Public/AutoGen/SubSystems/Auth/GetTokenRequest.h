
#pragma once

#include "CoreMinimal.h"
#include "BeamCoreTypes.h"


#include "AutoGen/Token.h"

#include "GetTokenRequest.generated.h"

UCLASS(BlueprintType)
class BEAMABLECORE_API UGetTokenRequest : public UObject, public IBeamBaseRequestInterface
{
	GENERATED_BODY()
	
public:

	// Path Params
	
	
	// Query Params
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Token")
	FString Token;

	// Body Params
	

	// Beam Base Request Declaration
	UGetTokenRequest() = default;

	virtual void BuildVerb(FString& VerbString) const override;
	virtual void BuildRoute(FString& RouteString) const override;
	virtual void BuildBody(FString& BodyString) const override;

	UFUNCTION(BlueprintPure, meta=(DefaultToSelf="Outer", AdvancedDisplay="Outer"))
	static UGetTokenRequest* MakeGetTokenRequest(FString _Token, UObject* Outer);
};

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnGetTokenSuccess, FBeamRequestContext, Context, UGetTokenRequest*, Request, UToken*, Response);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnGetTokenError, FBeamRequestContext, Context, UGetTokenRequest*, Request, FBeamErrorResponse, Error);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnGetTokenComplete, FBeamRequestContext, Context, UGetTokenRequest*, Request);

using FGetTokenFullResponse = FBeamFullResponse<UGetTokenRequest*, UToken*>;
DECLARE_DELEGATE_OneParam(FOnGetTokenFullResponse, FGetTokenFullResponse);
