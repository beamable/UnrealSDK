
#pragma once

#include "CoreMinimal.h"
#include "BeamBackend/BeamBaseRequestInterface.h"
#include "BeamBackend/BeamRequestContext.h"
#include "BeamBackend/BeamErrorResponse.h"
#include "BeamBackend/BeamFullResponse.h"


#include "BeamableCore/Public/AutoGen/InviteToParty.h"
#include "BeamableCore/Public/AutoGen/ApiPartiesInvitePostPartyResponse.h"

#include "ApiPartyPostInviteRequest.generated.h"

UCLASS(BlueprintType)
class BEAMABLECORE_API UApiPartyPostInviteRequest : public UObject, public IBeamBaseRequestInterface
{
	GENERATED_BODY()
	
public:

	// Path Params
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Id", Category="Beam")
	FGuid Id = {};
	
	// Query Params
	

	// Body Params
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="", Category="Beam")
	UInviteToParty* Body = {};

	// Beam Base Request Declaration
	UApiPartyPostInviteRequest() = default;

	virtual void BuildVerb(FString& VerbString) const override;
	virtual void BuildRoute(FString& RouteString) const override;
	virtual void BuildBody(FString& BodyString) const override;

	UFUNCTION(BlueprintPure, BlueprintInternalUseOnly, Category="Beam|Backend|Party", DisplayName="Beam - Make ApiPartyPostInvite",  meta=(DefaultToSelf="RequestOwner", AdvancedDisplay="_PlayerId,RequestOwner", AutoCreateRefTerm="CustomHeaders"))
	static UApiPartyPostInviteRequest* Make(FGuid _Id, FOptionalString _PlayerId, UObject* RequestOwner, TMap<FString, FString> CustomHeaders);
};

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnApiPartyPostInviteSuccess, FBeamRequestContext, Context, UApiPartyPostInviteRequest*, Request, UApiPartiesInvitePostPartyResponse*, Response);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnApiPartyPostInviteError, FBeamRequestContext, Context, UApiPartyPostInviteRequest*, Request, FBeamErrorResponse, Error);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnApiPartyPostInviteComplete, FBeamRequestContext, Context, UApiPartyPostInviteRequest*, Request);

using FApiPartyPostInviteFullResponse = FBeamFullResponse<UApiPartyPostInviteRequest*, UApiPartiesInvitePostPartyResponse*>;
DECLARE_DELEGATE_OneParam(FOnApiPartyPostInviteFullResponse, FApiPartyPostInviteFullResponse);
