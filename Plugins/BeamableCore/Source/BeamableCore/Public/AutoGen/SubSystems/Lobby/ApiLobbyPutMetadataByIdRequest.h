
#pragma once

#include "CoreMinimal.h"
#include "BeamBackend/BeamBaseRequestInterface.h"
#include "BeamBackend/BeamRequestContext.h"
#include "BeamBackend/BeamErrorResponse.h"
#include "BeamBackend/BeamFullResponse.h"

#include "Serialization/BeamJsonUtils.h"
#include "BeamableCore/Public/AutoGen/UpdateLobby.h"
#include "BeamableCore/Public/AutoGen/Lobby.h"

#include "ApiLobbyPutMetadataByIdRequest.generated.h"

UCLASS(BlueprintType)
class BEAMABLECORE_API UApiLobbyPutMetadataByIdRequest : public UObject, public IBeamBaseRequestInterface
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
	UApiLobbyPutMetadataByIdRequest() = default;

	virtual void BuildVerb(FString& VerbString) const override;
	virtual void BuildRoute(FString& RouteString) const override;
	virtual void BuildBody(FString& BodyString) const override;

	UFUNCTION(BlueprintPure, BlueprintInternalUseOnly, Category="Beam|Lobby|Utils|Make/Break", DisplayName="Make ApiLobbyPutMetadataById",  meta=(DefaultToSelf="RequestOwner", AdvancedDisplay="_Name,_Description,_Restriction,_MatchType,_MaxPlayers,_NewHost,_Data,RequestOwner", AutoCreateRefTerm="CustomHeaders"))
	static UApiLobbyPutMetadataByIdRequest* Make(FGuid _Id, FOptionalString _Name, FOptionalString _Description, FOptionalLobbyRestriction _Restriction, FOptionalBeamContentId _MatchType, FOptionalInt32 _MaxPlayers, FOptionalString _NewHost, FOptionalUpdateData _Data, UObject* RequestOwner, TMap<FString, FString> CustomHeaders);
};

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnApiLobbyPutMetadataByIdSuccess, FBeamRequestContext, Context, UApiLobbyPutMetadataByIdRequest*, Request, ULobby*, Response);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnApiLobbyPutMetadataByIdError, FBeamRequestContext, Context, UApiLobbyPutMetadataByIdRequest*, Request, FBeamErrorResponse, Error);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnApiLobbyPutMetadataByIdComplete, FBeamRequestContext, Context, UApiLobbyPutMetadataByIdRequest*, Request);

using FApiLobbyPutMetadataByIdFullResponse = FBeamFullResponse<UApiLobbyPutMetadataByIdRequest*, ULobby*>;
DECLARE_DELEGATE_OneParam(FOnApiLobbyPutMetadataByIdFullResponse, FApiLobbyPutMetadataByIdFullResponse);
