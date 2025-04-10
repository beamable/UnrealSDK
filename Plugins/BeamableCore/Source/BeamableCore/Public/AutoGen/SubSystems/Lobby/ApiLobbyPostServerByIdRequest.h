
#pragma once

#include "CoreMinimal.h"
#include "BeamBackend/BeamBaseRequestInterface.h"
#include "BeamBackend/BeamRequestContext.h"
#include "BeamBackend/BeamErrorResponse.h"
#include "BeamBackend/BeamFullResponse.h"

#include "Serialization/BeamJsonUtils.h"
#include "BeamableCore/Public/AutoGen/CreateFederatedGameServer.h"
#include "BeamableCore/Public/AutoGen/ApiLobbiesServerPostLobbyResponse.h"

#include "ApiLobbyPostServerByIdRequest.generated.h"

UCLASS(BlueprintType)
class BEAMABLECORE_API UApiLobbyPostServerByIdRequest : public UObject, public IBeamBaseRequestInterface
{
	GENERATED_BODY()
	
public:

	// Path Params
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Id", Category="Beam")
	FGuid Id = {};
	
	// Query Params
	

	// Body Params
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="", Category="Beam")
	UCreateFederatedGameServer* Body = {};

	// Beam Base Request Declaration
	UApiLobbyPostServerByIdRequest() = default;

	virtual void BuildVerb(FString& VerbString) const override;
	virtual void BuildRoute(FString& RouteString) const override;
	virtual void BuildBody(FString& BodyString) const override;

	UFUNCTION(BlueprintPure, BlueprintInternalUseOnly, Category="Beam|Lobby|Utils|Make/Break", DisplayName="Make ApiLobbyPostServerById",  meta=(DefaultToSelf="RequestOwner", AdvancedDisplay="_MatchType,RequestOwner", AutoCreateRefTerm="CustomHeaders"))
	static UApiLobbyPostServerByIdRequest* Make(FGuid _Id, FOptionalBeamContentId _MatchType, UObject* RequestOwner, TMap<FString, FString> CustomHeaders);
};

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnApiLobbyPostServerByIdSuccess, FBeamRequestContext, Context, UApiLobbyPostServerByIdRequest*, Request, UApiLobbiesServerPostLobbyResponse*, Response);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnApiLobbyPostServerByIdError, FBeamRequestContext, Context, UApiLobbyPostServerByIdRequest*, Request, FBeamErrorResponse, Error);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnApiLobbyPostServerByIdComplete, FBeamRequestContext, Context, UApiLobbyPostServerByIdRequest*, Request);

using FApiLobbyPostServerByIdFullResponse = FBeamFullResponse<UApiLobbyPostServerByIdRequest*, UApiLobbiesServerPostLobbyResponse*>;
DECLARE_DELEGATE_OneParam(FOnApiLobbyPostServerByIdFullResponse, FApiLobbyPostServerByIdFullResponse);
