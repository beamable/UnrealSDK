
#pragma once

#include "CoreMinimal.h"
#include "BeamBackend/BeamBaseRequestInterface.h"
#include "BeamBackend/BeamRequestContext.h"
#include "BeamBackend/BeamErrorResponse.h"
#include "BeamBackend/BeamFullResponse.h"

#include "BeamableUnrealMicroserviceClients/Public/AutoGen/RegisteredPlayerList.h"

#include "BeamFarmMsListRegisteredPlayersRequest.generated.h"

UCLASS(BlueprintType)
class BEAMABLEUNREALMICROSERVICECLIENTS_API UBeamFarmMsListRegisteredPlayersRequest : public UObject, public IBeamBaseRequestInterface
{
	GENERATED_BODY()
	
public:

	// Path Params
	
	
	// Query Params
	

	// Body Params
	

	// Beam Base Request Declaration
	UBeamFarmMsListRegisteredPlayersRequest() = default;

	virtual void BuildVerb(FString& VerbString) const override;
	virtual void BuildRoute(FString& RouteString) const override;
	virtual void BuildBody(FString& BodyString) const override;

	UFUNCTION(BlueprintPure, BlueprintInternalUseOnly, Category="Beam|BeamFarmMs|Utils|Make/Break", DisplayName="Make BeamFarmMsListRegisteredPlayers",  meta=(DefaultToSelf="RequestOwner", AdvancedDisplay="RequestOwner", AutoCreateRefTerm="CustomHeaders"))
	static UBeamFarmMsListRegisteredPlayersRequest* Make(UObject* RequestOwner, TMap<FString, FString> CustomHeaders);
};

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnBeamFarmMsListRegisteredPlayersSuccess, FBeamRequestContext, Context, UBeamFarmMsListRegisteredPlayersRequest*, Request, URegisteredPlayerList*, Response);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnBeamFarmMsListRegisteredPlayersError, FBeamRequestContext, Context, UBeamFarmMsListRegisteredPlayersRequest*, Request, FBeamErrorResponse, Error);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnBeamFarmMsListRegisteredPlayersComplete, FBeamRequestContext, Context, UBeamFarmMsListRegisteredPlayersRequest*, Request);

using FBeamFarmMsListRegisteredPlayersFullResponse = FBeamFullResponse<UBeamFarmMsListRegisteredPlayersRequest*, URegisteredPlayerList*>;
DECLARE_DELEGATE_OneParam(FOnBeamFarmMsListRegisteredPlayersFullResponse, FBeamFarmMsListRegisteredPlayersFullResponse);
