
#pragma once

#include "CoreMinimal.h"
#include "BeamCoreTypes.h"


#include "AutoGen/AccountAvailableResponse.h"

#include "GetAvailableRequest.generated.h"

UCLASS(BlueprintType)
class BEAMABLECORE_API UGetAvailableRequest : public UObject, public IBeamBaseRequestInterface
{
	GENERATED_BODY()
	
public:

	// Path Params
	
	
	// Query Params
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Email")
	FString Email;

	// Body Params
	

	// Beam Base Request Declaration
	UGetAvailableRequest() = default;

	virtual void BuildVerb(FString& VerbString) const override;
	virtual void BuildRoute(FString& RouteString) const override;
	virtual void BuildBody(FString& BodyString) const override;

	UFUNCTION(BlueprintPure, meta=(DefaultToSelf="Outer", AdvancedDisplay="Outer"))
	static UGetAvailableRequest* MakeGetAvailableRequest(FString _Email, UObject* Outer);
};

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnGetAvailableSuccess, FBeamRequestContext, Context, UGetAvailableRequest*, Request, UAccountAvailableResponse*, Response);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnGetAvailableError, FBeamRequestContext, Context, UGetAvailableRequest*, Request, FBeamErrorResponse, Error);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnGetAvailableComplete, FBeamRequestContext, Context, UGetAvailableRequest*, Request);

using FGetAvailableFullResponse = FBeamFullResponse<UGetAvailableRequest*, UAccountAvailableResponse*>;
DECLARE_DELEGATE_OneParam(FOnGetAvailableFullResponse, FGetAvailableFullResponse);
