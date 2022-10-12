
#pragma once

#include "CoreMinimal.h"
#include "BeamCoreTypes.h"

#include "AutoGen/AccountPlayerView.h"

#include "BasicAccountsGetMeRequest.generated.h"

UCLASS(BlueprintType)
class BEAMABLECORE_API UBasicAccountsGetMeRequest : public UObject, public IBeamBaseRequestInterface
{
	GENERATED_BODY()
	
public:

	// Path Params
	
	
	// Query Params
	

	// Body Params
	

	// Beam Base Request Declaration
	UBasicAccountsGetMeRequest() = default;

	virtual void BuildVerb(FString& VerbString) const override;
	virtual void BuildRoute(FString& RouteString) const override;
	virtual void BuildBody(FString& BodyString) const override;

	UFUNCTION(BlueprintPure, meta=(DefaultToSelf="Outer", AdvancedDisplay="Outer"))
	static UBasicAccountsGetMeRequest* MakeBasicAccountsGetMeRequest(UObject* Outer);
};

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnBasicAccountsGetMeSuccess, FBeamRequestContext, Context, UBasicAccountsGetMeRequest*, Request, UAccountPlayerView*, Response);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnBasicAccountsGetMeError, FBeamRequestContext, Context, UBasicAccountsGetMeRequest*, Request, FBeamErrorResponse, Error);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnBasicAccountsGetMeComplete, FBeamRequestContext, Context, UBasicAccountsGetMeRequest*, Request);

using FBasicAccountsGetMeFullResponse = FBeamFullResponse<UBasicAccountsGetMeRequest*, UAccountPlayerView*>;
DECLARE_DELEGATE_OneParam(FOnBasicAccountsGetMeFullResponse, FBasicAccountsGetMeFullResponse);
