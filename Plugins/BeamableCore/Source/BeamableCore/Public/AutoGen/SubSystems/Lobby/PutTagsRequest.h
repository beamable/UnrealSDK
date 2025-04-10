
#pragma once

#include "CoreMinimal.h"
#include "BeamBackend/BeamBaseRequestInterface.h"
#include "BeamBackend/BeamRequestContext.h"
#include "BeamBackend/BeamErrorResponse.h"
#include "BeamBackend/BeamFullResponse.h"

#include "Serialization/BeamJsonUtils.h"
#include "BeamableCore/Public/AutoGen/AddTags.h"
#include "BeamableCore/Public/AutoGen/Lobby.h"

#include "PutTagsRequest.generated.h"

UCLASS(BlueprintType)
class BEAMABLECORE_API UPutTagsRequest : public UObject, public IBeamBaseRequestInterface
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
	UPutTagsRequest() = default;

	virtual void BuildVerb(FString& VerbString) const override;
	virtual void BuildRoute(FString& RouteString) const override;
	virtual void BuildBody(FString& BodyString) const override;

	UFUNCTION(BlueprintPure, BlueprintInternalUseOnly, Category="Beam|Lobby|Utils|Make/Break", DisplayName="Make PutTags",  meta=(DefaultToSelf="RequestOwner", AdvancedDisplay="_PlayerId,_bReplace,_Tags,RequestOwner", AutoCreateRefTerm="CustomHeaders"))
	static UPutTagsRequest* Make(FGuid _Id, FOptionalBeamGamerTag _PlayerId, FOptionalBool _bReplace, FOptionalArrayOfBeamTag _Tags, UObject* RequestOwner, TMap<FString, FString> CustomHeaders);
};

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnPutTagsSuccess, FBeamRequestContext, Context, UPutTagsRequest*, Request, ULobby*, Response);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnPutTagsError, FBeamRequestContext, Context, UPutTagsRequest*, Request, FBeamErrorResponse, Error);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnPutTagsComplete, FBeamRequestContext, Context, UPutTagsRequest*, Request);

using FPutTagsFullResponse = FBeamFullResponse<UPutTagsRequest*, ULobby*>;
DECLARE_DELEGATE_OneParam(FOnPutTagsFullResponse, FPutTagsFullResponse);
