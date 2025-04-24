
#pragma once

#include "CoreMinimal.h"
#include "BeamBackend/BeamBaseRequestInterface.h"
#include "BeamBackend/BeamRequestContext.h"
#include "BeamBackend/BeamErrorResponse.h"
#include "BeamBackend/BeamFullResponse.h"

#include "BeamableUnrealMicroserviceClients/Public/AutoGen/DiscordWhitelistedInfo.h"

#include "DiscordSampleMsUpdateUserWhitelistedStatusRequest.generated.h"

UCLASS(BlueprintType)
class BEAMABLEUNREALMICROSERVICECLIENTS_API UDiscordSampleMsUpdateUserWhitelistedStatusRequest : public UObject, public IBeamBaseRequestInterface
{
	GENERATED_BODY()
	
public:

	// Path Params
	
	
	// Query Params
	

	// Body Params
	

	// Beam Base Request Declaration
	UDiscordSampleMsUpdateUserWhitelistedStatusRequest() = default;

	virtual void BuildVerb(FString& VerbString) const override;
	virtual void BuildRoute(FString& RouteString) const override;
	virtual void BuildBody(FString& BodyString) const override;

	UFUNCTION(BlueprintPure, BlueprintInternalUseOnly, Category="Beam|DiscordSampleMs|Utils|Make/Break", DisplayName="Make DiscordSampleMsUpdateUserWhitelistedStatus",  meta=(DefaultToSelf="RequestOwner", AdvancedDisplay="RequestOwner", AutoCreateRefTerm="CustomHeaders"))
	static UDiscordSampleMsUpdateUserWhitelistedStatusRequest* Make(UObject* RequestOwner, TMap<FString, FString> CustomHeaders);
};

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnDiscordSampleMsUpdateUserWhitelistedStatusSuccess, FBeamRequestContext, Context, UDiscordSampleMsUpdateUserWhitelistedStatusRequest*, Request, UDiscordWhitelistedInfo*, Response);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnDiscordSampleMsUpdateUserWhitelistedStatusError, FBeamRequestContext, Context, UDiscordSampleMsUpdateUserWhitelistedStatusRequest*, Request, FBeamErrorResponse, Error);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnDiscordSampleMsUpdateUserWhitelistedStatusComplete, FBeamRequestContext, Context, UDiscordSampleMsUpdateUserWhitelistedStatusRequest*, Request);

using FDiscordSampleMsUpdateUserWhitelistedStatusFullResponse = FBeamFullResponse<UDiscordSampleMsUpdateUserWhitelistedStatusRequest*, UDiscordWhitelistedInfo*>;
DECLARE_DELEGATE_OneParam(FOnDiscordSampleMsUpdateUserWhitelistedStatusFullResponse, FDiscordSampleMsUpdateUserWhitelistedStatusFullResponse);
