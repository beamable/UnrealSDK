
#pragma once

#include "CoreMinimal.h"
#include "BeamBackend/BeamBaseRequestInterface.h"
#include "BeamBackend/BeamRequestContext.h"
#include "BeamBackend/BeamErrorResponse.h"
#include "BeamBackend/BeamFullResponse.h"

#include "BeamableUnrealMicroserviceClients/Public/AutoGen/BeamballMsUpdateFromDiscordResponse.h"

#include "BeamballMsUpdateFromDiscordRequest.generated.h"

UCLASS(BlueprintType)
class BEAMABLEUNREALMICROSERVICECLIENTS_API UBeamballMsUpdateFromDiscordRequest : public UObject, public IBeamBaseRequestInterface
{
	GENERATED_BODY()
	
public:

	// Path Params
	
	
	// Query Params
	

	// Body Params
	

	// Beam Base Request Declaration
	UBeamballMsUpdateFromDiscordRequest() = default;

	virtual void BuildVerb(FString& VerbString) const override;
	virtual void BuildRoute(FString& RouteString) const override;
	virtual void BuildBody(FString& BodyString) const override;

	UFUNCTION(BlueprintPure, BlueprintInternalUseOnly, Category="Beam|BeamballMs|Utils|Make/Break", DisplayName="Make BeamballMsUpdateFromDiscord",  meta=(DefaultToSelf="RequestOwner", AdvancedDisplay="RequestOwner", AutoCreateRefTerm="CustomHeaders"))
	static UBeamballMsUpdateFromDiscordRequest* Make(UObject* RequestOwner, TMap<FString, FString> CustomHeaders);
};

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnBeamballMsUpdateFromDiscordSuccess, FBeamRequestContext, Context, UBeamballMsUpdateFromDiscordRequest*, Request, UBeamballMsUpdateFromDiscordResponse*, Response);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnBeamballMsUpdateFromDiscordError, FBeamRequestContext, Context, UBeamballMsUpdateFromDiscordRequest*, Request, FBeamErrorResponse, Error);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnBeamballMsUpdateFromDiscordComplete, FBeamRequestContext, Context, UBeamballMsUpdateFromDiscordRequest*, Request);

using FBeamballMsUpdateFromDiscordFullResponse = FBeamFullResponse<UBeamballMsUpdateFromDiscordRequest*, UBeamballMsUpdateFromDiscordResponse*>;
DECLARE_DELEGATE_OneParam(FOnBeamballMsUpdateFromDiscordFullResponse, FBeamballMsUpdateFromDiscordFullResponse);
