
#pragma once

#include "CoreMinimal.h"
#include "BeamBackend/BeamBaseRequestInterface.h"
#include "BeamBackend/BeamRequestContext.h"
#include "BeamBackend/BeamErrorResponse.h"
#include "BeamBackend/BeamFullResponse.h"

#include "BeamableCore/Public/AutoGen/Lobby.h"
#include "BeamableCore/Public/AutoGen/SetLobbyResponse.h"

#include "PutLobbiesRequest.generated.h"

UCLASS(BlueprintType)
class BEAMABLECORE_API UPutLobbiesRequest : public UObject, public IBeamBaseRequestInterface
{
	GENERATED_BODY()
	
public:

	// Path Params
	
	
	// Query Params
	

	// Body Params
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="", Category="Beam")
	ULobby* Body = {};

	// Beam Base Request Declaration
	UPutLobbiesRequest() = default;

	virtual void BuildVerb(FString& VerbString) const override;
	virtual void BuildRoute(FString& RouteString) const override;
	virtual void BuildBody(FString& BodyString) const override;

	UFUNCTION(BlueprintPure, BlueprintInternalUseOnly, Category="Beam|Lobby|Utils|Make/Break", DisplayName="Make PutLobbies",  meta=(DefaultToSelf="RequestOwner", AdvancedDisplay="_LobbyId,_MatchType,_Created,_Name,_Description,_Host,_Passcode,_Restriction,_MaxPlayers,_Players,_Data,RequestOwner", AutoCreateRefTerm="CustomHeaders"))
	static UPutLobbiesRequest* Make(FOptionalString _LobbyId, FOptionalMatchType _MatchType, FOptionalDateTime _Created, FOptionalString _Name, FOptionalString _Description, FOptionalBeamGamerTag _Host, FOptionalString _Passcode, FOptionalLobbyRestriction _Restriction, FOptionalInt32 _MaxPlayers, FOptionalArrayOfLobbyPlayer _Players, FOptionalMapOfString _Data, UObject* RequestOwner, TMap<FString, FString> CustomHeaders);
};

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnPutLobbiesSuccess, FBeamRequestContext, Context, UPutLobbiesRequest*, Request, USetLobbyResponse*, Response);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnPutLobbiesError, FBeamRequestContext, Context, UPutLobbiesRequest*, Request, FBeamErrorResponse, Error);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnPutLobbiesComplete, FBeamRequestContext, Context, UPutLobbiesRequest*, Request);

using FPutLobbiesFullResponse = FBeamFullResponse<UPutLobbiesRequest*, USetLobbyResponse*>;
DECLARE_DELEGATE_OneParam(FOnPutLobbiesFullResponse, FPutLobbiesFullResponse);
