
#pragma once

#include "CoreMinimal.h"
#include "BeamBackend/BeamBaseRequestInterface.h"
#include "BeamBackend/BeamRequestContext.h"
#include "BeamBackend/BeamErrorResponse.h"
#include "BeamBackend/BeamFullResponse.h"

#include "Serialization/BeamJsonUtils.h"
#include "BeamableCore/Public/AutoGen/RemoveTags.h"
#include "BeamableCore/Public/AutoGen/Lobby.h"

#include "DeleteTagsRequest.generated.h"

UCLASS(BlueprintType)
class BEAMABLECORE_API UDeleteTagsRequest : public UObject, public IBeamBaseRequestInterface
{
	GENERATED_BODY()
	
public:

	// Path Params
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Id", Category="Beam")
	FGuid Id = {};
	
	// Query Params
	

	// Body Params
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="", Category="Beam")
	URemoveTags* Body = {};

	// Beam Base Request Declaration
	UDeleteTagsRequest() = default;

	virtual void BuildVerb(FString& VerbString) const override;
	virtual void BuildRoute(FString& RouteString) const override;
	virtual void BuildBody(FString& BodyString) const override;

	UFUNCTION(BlueprintPure, BlueprintInternalUseOnly, Category="Beam|Lobby|Utils|Make/Break", DisplayName="Make DeleteTags",  meta=(DefaultToSelf="RequestOwner", AdvancedDisplay="_PlayerId,_Tags,RequestOwner", AutoCreateRefTerm="CustomHeaders"))
	static UDeleteTagsRequest* Make(FGuid _Id, FOptionalBeamGamerTag _PlayerId, FOptionalArrayOfString _Tags, UObject* RequestOwner, TMap<FString, FString> CustomHeaders);
};

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnDeleteTagsSuccess, FBeamRequestContext, Context, UDeleteTagsRequest*, Request, ULobby*, Response);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnDeleteTagsError, FBeamRequestContext, Context, UDeleteTagsRequest*, Request, FBeamErrorResponse, Error);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnDeleteTagsComplete, FBeamRequestContext, Context, UDeleteTagsRequest*, Request);

using FDeleteTagsFullResponse = FBeamFullResponse<UDeleteTagsRequest*, ULobby*>;
DECLARE_DELEGATE_OneParam(FOnDeleteTagsFullResponse, FDeleteTagsFullResponse);
