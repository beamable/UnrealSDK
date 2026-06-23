
#pragma once

#include "CoreMinimal.h"
#include "BeamBackend/BeamBaseRequestInterface.h"
#include "BeamBackend/BeamRequestContext.h"
#include "BeamBackend/BeamErrorResponse.h"
#include "BeamBackend/BeamFullResponse.h"

#include "BeamableUnrealMicroserviceClients/Public/AutoGen/DiscordWhitelistedInfo.h"

#include "BeamballMsUpdateUserWhitelistedStatusRequest.generated.h"

UCLASS(BlueprintType)
class BEAMABLEUNREALMICROSERVICECLIENTS_API UBeamballMsUpdateUserWhitelistedStatusRequest : public UObject, public IBeamBaseRequestInterface
{
	GENERATED_BODY()
	
public:

	// Path Params
	
	
	// Query Params
	

	// Body Params
	

	// Beam Base Request Declaration
	UBeamballMsUpdateUserWhitelistedStatusRequest() = default;

	virtual void BuildVerb(FString& VerbString) const override;
	virtual void BuildRoute(FString& RouteString) const override;
	virtual void BuildBody(FString& BodyString) const override;

	UFUNCTION(BlueprintPure, BlueprintInternalUseOnly, Category="Beam|BeamballMs|Utils|Make/Break", DisplayName="Make BeamballMsUpdateUserWhitelistedStatus",  meta=(DefaultToSelf="RequestOwner", AdvancedDisplay="RequestOwner", AutoCreateRefTerm="CustomHeaders"))
	static UBeamballMsUpdateUserWhitelistedStatusRequest* Make(UObject* RequestOwner, TMap<FString, FString> CustomHeaders);
};

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnBeamballMsUpdateUserWhitelistedStatusSuccess, FBeamRequestContext, Context, UBeamballMsUpdateUserWhitelistedStatusRequest*, Request, UDiscordWhitelistedInfo*, Response);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnBeamballMsUpdateUserWhitelistedStatusError, FBeamRequestContext, Context, UBeamballMsUpdateUserWhitelistedStatusRequest*, Request, FBeamErrorResponse, Error);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnBeamballMsUpdateUserWhitelistedStatusComplete, FBeamRequestContext, Context, UBeamballMsUpdateUserWhitelistedStatusRequest*, Request);

using FBeamballMsUpdateUserWhitelistedStatusFullResponse = FBeamFullResponse<UBeamballMsUpdateUserWhitelistedStatusRequest*, UDiscordWhitelistedInfo*>;
DECLARE_DELEGATE_OneParam(FOnBeamballMsUpdateUserWhitelistedStatusFullResponse, FBeamballMsUpdateUserWhitelistedStatusFullResponse);
