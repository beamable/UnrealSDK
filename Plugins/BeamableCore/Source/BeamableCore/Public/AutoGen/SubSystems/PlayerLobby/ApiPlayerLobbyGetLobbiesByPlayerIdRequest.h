
#pragma once

#include "CoreMinimal.h"
#include "BeamBackend/BeamBaseRequestInterface.h"
#include "BeamBackend/BeamRequestContext.h"
#include "BeamBackend/BeamErrorResponse.h"
#include "BeamBackend/BeamFullResponse.h"

#include "Serialization/BeamJsonUtils.h"
#include "BeamableCore/Public/AutoGen/Lobby.h"

#include "ApiPlayerLobbyGetLobbiesByPlayerIdRequest.generated.h"

UCLASS(BlueprintType)
class BEAMABLECORE_API UApiPlayerLobbyGetLobbiesByPlayerIdRequest : public UObject, public IBeamBaseRequestInterface
{
	GENERATED_BODY()
	
public:

	// Path Params
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Player Id", Category="Beam")
	FString PlayerId = {};
	
	// Query Params
	

	// Body Params
	

	// Beam Base Request Declaration
	UApiPlayerLobbyGetLobbiesByPlayerIdRequest() = default;

	virtual void BuildVerb(FString& VerbString) const override;
	virtual void BuildRoute(FString& RouteString) const override;
	virtual void BuildBody(FString& BodyString) const override;

	UFUNCTION(BlueprintPure, BlueprintInternalUseOnly, Category="Beam|PlayerLobby|Utils|Make/Break", DisplayName="Make ApiPlayerLobbyGetLobbiesByPlayerId",  meta=(DefaultToSelf="RequestOwner", AdvancedDisplay="RequestOwner", AutoCreateRefTerm="CustomHeaders"))
	static UApiPlayerLobbyGetLobbiesByPlayerIdRequest* Make(FString _PlayerId, UObject* RequestOwner, TMap<FString, FString> CustomHeaders);
};

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnApiPlayerLobbyGetLobbiesByPlayerIdSuccess, FBeamRequestContext, Context, UApiPlayerLobbyGetLobbiesByPlayerIdRequest*, Request, ULobby*, Response);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnApiPlayerLobbyGetLobbiesByPlayerIdError, FBeamRequestContext, Context, UApiPlayerLobbyGetLobbiesByPlayerIdRequest*, Request, FBeamErrorResponse, Error);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnApiPlayerLobbyGetLobbiesByPlayerIdComplete, FBeamRequestContext, Context, UApiPlayerLobbyGetLobbiesByPlayerIdRequest*, Request);

using FApiPlayerLobbyGetLobbiesByPlayerIdFullResponse = FBeamFullResponse<UApiPlayerLobbyGetLobbiesByPlayerIdRequest*, ULobby*>;
DECLARE_DELEGATE_OneParam(FOnApiPlayerLobbyGetLobbiesByPlayerIdFullResponse, FApiPlayerLobbyGetLobbiesByPlayerIdFullResponse);
