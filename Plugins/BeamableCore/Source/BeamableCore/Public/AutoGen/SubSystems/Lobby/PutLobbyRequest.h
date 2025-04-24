
#pragma once

#include "CoreMinimal.h"
#include "BeamBackend/BeamBaseRequestInterface.h"
#include "BeamBackend/BeamRequestContext.h"
#include "BeamBackend/BeamErrorResponse.h"
#include "BeamBackend/BeamFullResponse.h"

#include "Serialization/BeamJsonUtils.h"
#include "BeamableCore/Public/AutoGen/JoinLobby.h"
#include "BeamableCore/Public/AutoGen/Lobby.h"

#include "PutLobbyRequest.generated.h"

UCLASS(BlueprintType)
class BEAMABLECORE_API UPutLobbyRequest : public UObject, public IBeamBaseRequestInterface
{
	GENERATED_BODY()
	
public:

	// Path Params
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Id", Category="Beam")
	FGuid Id = {};
	
	// Query Params
	

	// Body Params
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="", Category="Beam")
	UJoinLobby* Body = {};

	// Beam Base Request Declaration
	UPutLobbyRequest() = default;

	virtual void BuildVerb(FString& VerbString) const override;
	virtual void BuildRoute(FString& RouteString) const override;
	virtual void BuildBody(FString& BodyString) const override;

	UFUNCTION(BlueprintPure, BlueprintInternalUseOnly, Category="Beam|Lobby|Utils|Make/Break", DisplayName="Make PutLobby",  meta=(DefaultToSelf="RequestOwner", AdvancedDisplay="_Passcode,_Tags,RequestOwner", AutoCreateRefTerm="CustomHeaders"))
	static UPutLobbyRequest* Make(FGuid _Id, FOptionalString _Passcode, FOptionalArrayOfBeamTag _Tags, UObject* RequestOwner, TMap<FString, FString> CustomHeaders);
};

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnPutLobbySuccess, FBeamRequestContext, Context, UPutLobbyRequest*, Request, ULobby*, Response);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnPutLobbyError, FBeamRequestContext, Context, UPutLobbyRequest*, Request, FBeamErrorResponse, Error);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnPutLobbyComplete, FBeamRequestContext, Context, UPutLobbyRequest*, Request);

using FPutLobbyFullResponse = FBeamFullResponse<UPutLobbyRequest*, ULobby*>;
DECLARE_DELEGATE_OneParam(FOnPutLobbyFullResponse, FPutLobbyFullResponse);
