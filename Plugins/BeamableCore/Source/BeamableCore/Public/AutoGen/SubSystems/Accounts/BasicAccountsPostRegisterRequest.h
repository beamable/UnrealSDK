
#pragma once

#include "CoreMinimal.h"
#include "BeamBackend/BeamBaseRequestInterface.h"
#include "BeamBackend/BeamRequestContext.h"
#include "BeamBackend/BeamErrorResponse.h"
#include "BeamBackend/BeamFullResponse.h"

#include "BeamableCore/Public/AutoGen/AccountRegistration.h"
#include "BeamableCore/Public/AutoGen/AccountPlayerView.h"

#include "BasicAccountsPostRegisterRequest.generated.h"

UCLASS(BlueprintType)
class BEAMABLECORE_API UBasicAccountsPostRegisterRequest : public UObject, public IBeamBaseRequestInterface
{
	GENERATED_BODY()
	
public:

	// Path Params
	
	
	// Query Params
	

	// Body Params
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="", Category="Beam")
	UAccountRegistration* Body = {};

	// Beam Base Request Declaration
	UBasicAccountsPostRegisterRequest() = default;

	virtual void BuildVerb(FString& VerbString) const override;
	virtual void BuildRoute(FString& RouteString) const override;
	virtual void BuildBody(FString& BodyString) const override;

	UFUNCTION(BlueprintPure, BlueprintInternalUseOnly, Category="Beam|Accounts|Utils|Make/Break", DisplayName="Make BasicAccountsPostRegister",  meta=(DefaultToSelf="RequestOwner", AdvancedDisplay="RequestOwner", AutoCreateRefTerm="CustomHeaders"))
	static UBasicAccountsPostRegisterRequest* Make(FString _Email, FString _Password, UObject* RequestOwner, TMap<FString, FString> CustomHeaders);
};

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnBasicAccountsPostRegisterSuccess, FBeamRequestContext, Context, UBasicAccountsPostRegisterRequest*, Request, UAccountPlayerView*, Response);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnBasicAccountsPostRegisterError, FBeamRequestContext, Context, UBasicAccountsPostRegisterRequest*, Request, FBeamErrorResponse, Error);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnBasicAccountsPostRegisterComplete, FBeamRequestContext, Context, UBasicAccountsPostRegisterRequest*, Request);

using FBasicAccountsPostRegisterFullResponse = FBeamFullResponse<UBasicAccountsPostRegisterRequest*, UAccountPlayerView*>;
DECLARE_DELEGATE_OneParam(FOnBasicAccountsPostRegisterFullResponse, FBasicAccountsPostRegisterFullResponse);
