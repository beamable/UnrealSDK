
#pragma once

#include "CoreMinimal.h"
#include "BeamBackend/BeamBaseRequestInterface.h"
#include "BeamBackend/BeamRequestContext.h"
#include "BeamBackend/BeamErrorResponse.h"
#include "BeamBackend/BeamFullResponse.h"

#include "BeamableCore/Public/AutoGen/Optionals/OptionalInt32.h"
#include "BeamableCore/Public/AutoGen/Optionals/OptionalBeamContentId.h"
#include "BeamableCore/Public/AutoGen/LobbyQueryResponse.h"

#include "ApiLobbyGetLobbiesRequest.generated.h"

UCLASS(BlueprintType)
class BEAMABLECORE_API UApiLobbyGetLobbiesRequest : public UObject, public IBeamBaseRequestInterface
{
	GENERATED_BODY()
	
public:

	// Path Params
	
	
	// Query Params
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Skip", Category="Beam")
	FOptionalInt32 Skip = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Limit", Category="Beam")
	FOptionalInt32 Limit = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Match Type", Category="Beam")
	FOptionalBeamContentId MatchType = {};

	// Body Params
	

	// Beam Base Request Declaration
	UApiLobbyGetLobbiesRequest() = default;

	virtual void BuildVerb(FString& VerbString) const override;
	virtual void BuildRoute(FString& RouteString) const override;
	virtual void BuildBody(FString& BodyString) const override;

	UFUNCTION(BlueprintPure, BlueprintInternalUseOnly, Category="Beam|Lobby|Utils|Make/Break", DisplayName="Make ApiLobbyGetLobbies",  meta=(DefaultToSelf="RequestOwner", AdvancedDisplay="_Skip,_Limit,_MatchType,RequestOwner", AutoCreateRefTerm="CustomHeaders"))
	static UApiLobbyGetLobbiesRequest* Make(FOptionalInt32 _Skip, FOptionalInt32 _Limit, FOptionalBeamContentId _MatchType, UObject* RequestOwner, TMap<FString, FString> CustomHeaders);
};

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnApiLobbyGetLobbiesSuccess, FBeamRequestContext, Context, UApiLobbyGetLobbiesRequest*, Request, ULobbyQueryResponse*, Response);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnApiLobbyGetLobbiesError, FBeamRequestContext, Context, UApiLobbyGetLobbiesRequest*, Request, FBeamErrorResponse, Error);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnApiLobbyGetLobbiesComplete, FBeamRequestContext, Context, UApiLobbyGetLobbiesRequest*, Request);

using FApiLobbyGetLobbiesFullResponse = FBeamFullResponse<UApiLobbyGetLobbiesRequest*, ULobbyQueryResponse*>;
DECLARE_DELEGATE_OneParam(FOnApiLobbyGetLobbiesFullResponse, FApiLobbyGetLobbiesFullResponse);
