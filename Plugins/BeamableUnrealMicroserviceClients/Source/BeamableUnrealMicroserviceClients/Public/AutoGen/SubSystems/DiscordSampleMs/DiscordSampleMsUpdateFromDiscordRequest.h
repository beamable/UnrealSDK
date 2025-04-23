
#pragma once

#include "CoreMinimal.h"
#include "BeamBackend/BeamBaseRequestInterface.h"
#include "BeamBackend/BeamRequestContext.h"
#include "BeamBackend/BeamErrorResponse.h"
#include "BeamBackend/BeamFullResponse.h"

#include "BeamableUnrealMicroserviceClients/Public/AutoGen/DiscordSampleMsUpdateFromDiscordResponse.h"

#include "DiscordSampleMsUpdateFromDiscordRequest.generated.h"

UCLASS(BlueprintType)
class BEAMABLEUNREALMICROSERVICECLIENTS_API UDiscordSampleMsUpdateFromDiscordRequest : public UObject, public IBeamBaseRequestInterface
{
	GENERATED_BODY()
	
public:

	// Path Params
	
	
	// Query Params
	

	// Body Params
	

	// Beam Base Request Declaration
	UDiscordSampleMsUpdateFromDiscordRequest() = default;

	virtual void BuildVerb(FString& VerbString) const override;
	virtual void BuildRoute(FString& RouteString) const override;
	virtual void BuildBody(FString& BodyString) const override;

	UFUNCTION(BlueprintPure, BlueprintInternalUseOnly, Category="Beam|DiscordSampleMs|Utils|Make/Break", DisplayName="Make DiscordSampleMsUpdateFromDiscord",  meta=(DefaultToSelf="RequestOwner", AdvancedDisplay="RequestOwner", AutoCreateRefTerm="CustomHeaders"))
	static UDiscordSampleMsUpdateFromDiscordRequest* Make(UObject* RequestOwner, TMap<FString, FString> CustomHeaders);
};

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnDiscordSampleMsUpdateFromDiscordSuccess, FBeamRequestContext, Context, UDiscordSampleMsUpdateFromDiscordRequest*, Request, UDiscordSampleMsUpdateFromDiscordResponse*, Response);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnDiscordSampleMsUpdateFromDiscordError, FBeamRequestContext, Context, UDiscordSampleMsUpdateFromDiscordRequest*, Request, FBeamErrorResponse, Error);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnDiscordSampleMsUpdateFromDiscordComplete, FBeamRequestContext, Context, UDiscordSampleMsUpdateFromDiscordRequest*, Request);

using FDiscordSampleMsUpdateFromDiscordFullResponse = FBeamFullResponse<UDiscordSampleMsUpdateFromDiscordRequest*, UDiscordSampleMsUpdateFromDiscordResponse*>;
DECLARE_DELEGATE_OneParam(FOnDiscordSampleMsUpdateFromDiscordFullResponse, FDiscordSampleMsUpdateFromDiscordFullResponse);
