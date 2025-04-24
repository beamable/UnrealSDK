
#pragma once

#include "CoreMinimal.h"
#include "BeamBackend/BeamBaseRequestInterface.h"
#include "BeamBackend/BeamRequestContext.h"
#include "BeamBackend/BeamErrorResponse.h"
#include "BeamBackend/BeamFullResponse.h"

#include "Serialization/BeamJsonUtils.h"
#include "BeamableCore/Public/AutoGen/OnlineStatus.h"

#include "GetPresenceRequest.generated.h"

UCLASS(BlueprintType)
class BEAMABLECORE_API UGetPresenceRequest : public UObject, public IBeamBaseRequestInterface
{
	GENERATED_BODY()
	
public:

	// Path Params
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Player Id", Category="Beam")
	FString PlayerId = {};
	
	// Query Params
	

	// Body Params
	

	// Beam Base Request Declaration
	UGetPresenceRequest() = default;

	virtual void BuildVerb(FString& VerbString) const override;
	virtual void BuildRoute(FString& RouteString) const override;
	virtual void BuildBody(FString& BodyString) const override;

	UFUNCTION(BlueprintPure, BlueprintInternalUseOnly, Category="Beam|Player|Utils|Make/Break", DisplayName="Make GetPresence",  meta=(DefaultToSelf="RequestOwner", AdvancedDisplay="RequestOwner", AutoCreateRefTerm="CustomHeaders"))
	static UGetPresenceRequest* Make(FString _PlayerId, UObject* RequestOwner, TMap<FString, FString> CustomHeaders);
};

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnGetPresenceSuccess, FBeamRequestContext, Context, UGetPresenceRequest*, Request, UOnlineStatus*, Response);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnGetPresenceError, FBeamRequestContext, Context, UGetPresenceRequest*, Request, FBeamErrorResponse, Error);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnGetPresenceComplete, FBeamRequestContext, Context, UGetPresenceRequest*, Request);

using FGetPresenceFullResponse = FBeamFullResponse<UGetPresenceRequest*, UOnlineStatus*>;
DECLARE_DELEGATE_OneParam(FOnGetPresenceFullResponse, FGetPresenceFullResponse);
