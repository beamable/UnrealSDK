
#pragma once

#include "CoreMinimal.h"
#include "BeamBackend/BeamBaseRequestInterface.h"
#include "BeamBackend/BeamRequestContext.h"
#include "BeamBackend/BeamErrorResponse.h"
#include "BeamBackend/BeamFullResponse.h"


#include "BeamableCore/Public/AutoGen/UpdateLobby.h"
#include "BeamableCore/Public/AutoGen/Lobby.h"

#include "ApiLobbyPutMetadataRequest.generated.h"

UCLASS(BlueprintType)
class BEAMABLECORE_API UApiLobbyPutMetadataRequest : public UObject, public IBeamBaseRequestInterface
{
	GENERATED_BODY()
	
public:

	// Path Params
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Id", Category="Beam")
	FGuid Id = {};
	
	// Query Params
	

	// Body Params
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="", Category="Beam")
	UUpdateLobby* Body = {};

	// Beam Base Request Declaration
	UApiLobbyPutMetadataRequest() = default;

	virtual void BuildVerb(FString& VerbString) const override;
	virtual void BuildRoute(FString& RouteString) const override;
	virtual void BuildBody(FString& BodyString) const override;

	UFUNCTION(BlueprintPure, BlueprintInternalUseOnly, Category="Beam|Backend|Lobby", DisplayName="Beam - Make ApiLobbyPutMetadata",  meta=(DefaultToSelf="RequestOwner", AdvancedDisplay="_Name,_Description,_Restriction,_MatchType,_MaxPlayers,_NewHost,RequestOwner", AutoCreateRefTerm="CustomHeaders"))
	static UApiLobbyPutMetadataRequest* Make(FGuid _Id, FOptionalString _Name, FOptionalString _Description, FOptionalString _Restriction, FOptionalBeamContentId _MatchType, FOptionalInt32 _MaxPlayers, FOptionalString _NewHost, UObject* RequestOwner, TMap<FString, FString> CustomHeaders);
};

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnApiLobbyPutMetadataSuccess, FBeamRequestContext, Context, UApiLobbyPutMetadataRequest*, Request, ULobby*, Response);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnApiLobbyPutMetadataError, FBeamRequestContext, Context, UApiLobbyPutMetadataRequest*, Request, FBeamErrorResponse, Error);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnApiLobbyPutMetadataComplete, FBeamRequestContext, Context, UApiLobbyPutMetadataRequest*, Request);

using FApiLobbyPutMetadataFullResponse = FBeamFullResponse<UApiLobbyPutMetadataRequest*, ULobby*>;
DECLARE_DELEGATE_OneParam(FOnApiLobbyPutMetadataFullResponse, FApiLobbyPutMetadataFullResponse);
