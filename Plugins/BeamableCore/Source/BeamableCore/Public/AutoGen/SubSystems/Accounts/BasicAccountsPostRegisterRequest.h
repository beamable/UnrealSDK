
#pragma once

#include "CoreMinimal.h"
#include "BeamCoreTypes.h"

#include "AutoGen/AccountRegistration.h"
#include "AutoGen/AccountPlayerView.h"

#include "BasicAccountsPostRegisterRequest.generated.h"

UCLASS(BlueprintType)
class BEAMABLECORE_API UBasicAccountsPostRegisterRequest : public UObject, public IBeamBaseRequestInterface
{
	GENERATED_BODY()
	
public:

	// Path Params
	
	
	// Query Params
	

	// Body Params
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="")
	UAccountRegistration* Body;

	// Beam Base Request Declaration
	UBasicAccountsPostRegisterRequest() = default;

	virtual void BuildVerb(FString& VerbString) const override;
	virtual void BuildRoute(FString& RouteString) const override;
	virtual void BuildBody(FString& BodyString) const override;

	UFUNCTION(BlueprintPure, meta=(DefaultToSelf="Outer", AdvancedDisplay="Outer"))
	static UBasicAccountsPostRegisterRequest* MakeBasicAccountsPostRegisterRequest(FString _Email, FString _Password, UObject* Outer);
};

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnBasicAccountsPostRegisterSuccess, FBeamRequestContext, Context, UBasicAccountsPostRegisterRequest*, Request, UAccountPlayerView*, Response);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnBasicAccountsPostRegisterError, FBeamRequestContext, Context, UBasicAccountsPostRegisterRequest*, Request, FBeamErrorResponse, Error);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnBasicAccountsPostRegisterComplete, FBeamRequestContext, Context, UBasicAccountsPostRegisterRequest*, Request);

using FBasicAccountsPostRegisterFullResponse = FBeamFullResponse<UBasicAccountsPostRegisterRequest*, UAccountPlayerView*>;
DECLARE_DELEGATE_OneParam(FOnBasicAccountsPostRegisterFullResponse, FBasicAccountsPostRegisterFullResponse);
