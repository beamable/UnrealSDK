
#pragma once

#include "CoreMinimal.h"
#include "BeamBackend/BeamBaseRequestInterface.h"
#include "BeamBackend/BeamRequestContext.h"
#include "BeamBackend/BeamErrorResponse.h"
#include "BeamBackend/BeamFullResponse.h"

#include "Serialization/BeamJsonUtils.h"
#include "BeamableCore/Public/AutoGen/AddTags.h"
#include "BeamableCore/Public/AutoGen/Lobby.h"

#include "ApiLobbyPutTagsByIdRequest.generated.h"

UCLASS(BlueprintType)
class BEAMABLECORE_API UApiLobbyPutTagsByIdRequest : public UObject, public IBeamBaseRequestInterface
{
	GENERATED_BODY()
	
public:

	// Path Params
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Id", Category="Beam")
	FGuid Id = {};
	
	// Query Params
	

	// Body Params
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="", Category="Beam")
	UAddTags* Body = {};

	// Beam Base Request Declaration
	UApiLobbyPutTagsByIdRequest() = default;

	virtual void BuildVerb(FString& VerbString) const override;
	virtual void BuildRoute(FString& RouteString) const override;
	virtual void BuildBody(FString& BodyString) const override;

	UFUNCTION(BlueprintPure, BlueprintInternalUseOnly, Category="Beam|Lobby|Utils|Make/Break", DisplayName="Make ApiLobbyPutTagsById",  meta=(DefaultToSelf="RequestOwner", AdvancedDisplay="_PlayerId,_bReplace,_Tags,RequestOwner", AutoCreateRefTerm="CustomHeaders"))
	static UApiLobbyPutTagsByIdRequest* Make(FGuid _Id, FOptionalBeamGamerTag _PlayerId, FOptionalBool _bReplace, FOptionalArrayOfBeamTag _Tags, UObject* RequestOwner, TMap<FString, FString> CustomHeaders);
};

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnApiLobbyPutTagsByIdSuccess, FBeamRequestContext, Context, UApiLobbyPutTagsByIdRequest*, Request, ULobby*, Response);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnApiLobbyPutTagsByIdError, FBeamRequestContext, Context, UApiLobbyPutTagsByIdRequest*, Request, FBeamErrorResponse, Error);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnApiLobbyPutTagsByIdComplete, FBeamRequestContext, Context, UApiLobbyPutTagsByIdRequest*, Request);

using FApiLobbyPutTagsByIdFullResponse = FBeamFullResponse<UApiLobbyPutTagsByIdRequest*, ULobby*>;
DECLARE_DELEGATE_OneParam(FOnApiLobbyPutTagsByIdFullResponse, FApiLobbyPutTagsByIdFullResponse);
