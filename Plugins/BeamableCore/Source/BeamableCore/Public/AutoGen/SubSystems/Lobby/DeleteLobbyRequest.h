
#pragma once

#include "CoreMinimal.h"
#include "BeamBackend/BeamBaseRequestInterface.h"
#include "BeamBackend/BeamRequestContext.h"
#include "BeamBackend/BeamErrorResponse.h"
#include "BeamBackend/BeamFullResponse.h"

#include "Serialization/BeamJsonUtils.h"
#include "BeamableCore/Public/AutoGen/RemoveFromLobby.h"
#include "BeamableCore/Public/AutoGen/Acknowledge.h"

#include "DeleteLobbyRequest.generated.h"

UCLASS(BlueprintType)
class BEAMABLECORE_API UDeleteLobbyRequest : public UObject, public IBeamBaseRequestInterface
{
	GENERATED_BODY()
	
public:

	// Path Params
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Id", Category="Beam")
	FGuid Id = {};
	
	// Query Params
	

	// Body Params
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="", Category="Beam")
	URemoveFromLobby* Body = {};

	// Beam Base Request Declaration
	UDeleteLobbyRequest() = default;

	virtual void BuildVerb(FString& VerbString) const override;
	virtual void BuildRoute(FString& RouteString) const override;
	virtual void BuildBody(FString& BodyString) const override;

	UFUNCTION(BlueprintPure, BlueprintInternalUseOnly, Category="Beam|Lobby|Utils|Make/Break", DisplayName="Make DeleteLobby",  meta=(DefaultToSelf="RequestOwner", AdvancedDisplay="_PlayerId,RequestOwner", AutoCreateRefTerm="CustomHeaders"))
	static UDeleteLobbyRequest* Make(FGuid _Id, FOptionalBeamGamerTag _PlayerId, UObject* RequestOwner, TMap<FString, FString> CustomHeaders);
};

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnDeleteLobbySuccess, FBeamRequestContext, Context, UDeleteLobbyRequest*, Request, UAcknowledge*, Response);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnDeleteLobbyError, FBeamRequestContext, Context, UDeleteLobbyRequest*, Request, FBeamErrorResponse, Error);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnDeleteLobbyComplete, FBeamRequestContext, Context, UDeleteLobbyRequest*, Request);

using FDeleteLobbyFullResponse = FBeamFullResponse<UDeleteLobbyRequest*, UAcknowledge*>;
DECLARE_DELEGATE_OneParam(FOnDeleteLobbyFullResponse, FDeleteLobbyFullResponse);
