
#pragma once

#include "CoreMinimal.h"
#include "BeamBackend/BeamBaseRequestInterface.h"
#include "BeamBackend/BeamRequestContext.h"
#include "BeamBackend/BeamErrorResponse.h"
#include "BeamBackend/BeamFullResponse.h"

#include "Serialization/BeamJsonUtils.h"
#include "BeamableCore/Public/AutoGen/ApiPlayersLobbiesDeletePlayerLobbyResponse.h"

#include "DeleteLobbiesRequest.generated.h"

UCLASS(BlueprintType)
class BEAMABLECORE_API UDeleteLobbiesRequest : public UObject, public IBeamBaseRequestInterface
{
	GENERATED_BODY()
	
public:

	// Path Params
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Player Id", Category="Beam")
	FString PlayerId = {};
	
	// Query Params
	

	// Body Params
	

	// Beam Base Request Declaration
	UDeleteLobbiesRequest() = default;

	virtual void BuildVerb(FString& VerbString) const override;
	virtual void BuildRoute(FString& RouteString) const override;
	virtual void BuildBody(FString& BodyString) const override;

	UFUNCTION(BlueprintPure, BlueprintInternalUseOnly, Category="Beam|PlayerLobby|Utils|Make/Break", DisplayName="Make DeleteLobbies",  meta=(DefaultToSelf="RequestOwner", AdvancedDisplay="RequestOwner", AutoCreateRefTerm="CustomHeaders"))
	static UDeleteLobbiesRequest* Make(FString _PlayerId, UObject* RequestOwner, TMap<FString, FString> CustomHeaders);
};

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnDeleteLobbiesSuccess, FBeamRequestContext, Context, UDeleteLobbiesRequest*, Request, UApiPlayersLobbiesDeletePlayerLobbyResponse*, Response);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnDeleteLobbiesError, FBeamRequestContext, Context, UDeleteLobbiesRequest*, Request, FBeamErrorResponse, Error);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnDeleteLobbiesComplete, FBeamRequestContext, Context, UDeleteLobbiesRequest*, Request);

using FDeleteLobbiesFullResponse = FBeamFullResponse<UDeleteLobbiesRequest*, UApiPlayersLobbiesDeletePlayerLobbyResponse*>;
DECLARE_DELEGATE_OneParam(FOnDeleteLobbiesFullResponse, FDeleteLobbiesFullResponse);
