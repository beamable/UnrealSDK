
#pragma once

#include "CoreMinimal.h"
#include "BeamBackend/BeamBaseRequestInterface.h"
#include "BeamBackend/BeamRequestContext.h"
#include "BeamBackend/BeamErrorResponse.h"
#include "BeamBackend/BeamFullResponse.h"

#include "BeamableCore/Public/AutoGen/AccountPlayerView.h"

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

	UFUNCTION(BlueprintPure, BlueprintInternalUseOnly, Category="Beam|Accounts|Utils|Make/Break", DisplayName="Make BasicAccountsGetMe",  meta=(DefaultToSelf="RequestOwner", AdvancedDisplay="RequestOwner", AutoCreateRefTerm="CustomHeaders"))
	static UBasicAccountsGetMeRequest* Make(UObject* RequestOwner, TMap<FString, FString> CustomHeaders);
};

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnBasicAccountsGetMeSuccess, FBeamRequestContext, Context, UBasicAccountsGetMeRequest*, Request, UAccountPlayerView*, Response);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnBasicAccountsGetMeError, FBeamRequestContext, Context, UBasicAccountsGetMeRequest*, Request, FBeamErrorResponse, Error);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnBasicAccountsGetMeComplete, FBeamRequestContext, Context, UBasicAccountsGetMeRequest*, Request);

using FBasicAccountsGetMeFullResponse = FBeamFullResponse<UBasicAccountsGetMeRequest*, UAccountPlayerView*>;
DECLARE_DELEGATE_OneParam(FOnBasicAccountsGetMeFullResponse, FBasicAccountsGetMeFullResponse);
