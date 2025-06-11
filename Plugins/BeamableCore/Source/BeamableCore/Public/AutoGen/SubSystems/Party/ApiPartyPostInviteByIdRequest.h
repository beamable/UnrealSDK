
#pragma once

#include "CoreMinimal.h"
#include "BeamBackend/BeamBaseRequestInterface.h"
#include "BeamBackend/BeamRequestContext.h"
#include "BeamBackend/BeamErrorResponse.h"
#include "BeamBackend/BeamFullResponse.h"

#include "Serialization/BeamJsonUtils.h"
#include "BeamableCore/Public/AutoGen/InviteToParty.h"
#include "BeamableCore/Public/AutoGen/ApiPartiesInvitePostPartyResponse.h"

#include "ApiPartyPostInviteByIdRequest.generated.h"

UCLASS(BlueprintType)
class BEAMABLECORE_API UApiPartyPostInviteByIdRequest : public UObject, public IBeamBaseRequestInterface
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
	UApiPartyPostInviteByIdRequest() = default;

	virtual void BuildVerb(FString& VerbString) const override;
	virtual void BuildRoute(FString& RouteString) const override;
	virtual void BuildBody(FString& BodyString) const override;

	UFUNCTION(BlueprintPure, BlueprintInternalUseOnly, Category="Beam|Party|Utils|Make/Break", DisplayName="Make ApiPartyPostInviteById",  meta=(DefaultToSelf="RequestOwner", AdvancedDisplay="_PlayerId,RequestOwner", AutoCreateRefTerm="CustomHeaders"))
	static UApiPartyPostInviteByIdRequest* Make(FGuid _Id, FOptionalBeamGamerTag _PlayerId, UObject* RequestOwner, TMap<FString, FString> CustomHeaders);
};

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnApiPartyPostInviteByIdSuccess, FBeamRequestContext, Context, UApiPartyPostInviteByIdRequest*, Request, UApiPartiesInvitePostPartyResponse*, Response);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnApiPartyPostInviteByIdError, FBeamRequestContext, Context, UApiPartyPostInviteByIdRequest*, Request, FBeamErrorResponse, Error);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnApiPartyPostInviteByIdComplete, FBeamRequestContext, Context, UApiPartyPostInviteByIdRequest*, Request);

using FApiPartyPostInviteByIdFullResponse = FBeamFullResponse<UApiPartyPostInviteByIdRequest*, UApiPartiesInvitePostPartyResponse*>;
DECLARE_DELEGATE_OneParam(FOnApiPartyPostInviteByIdFullResponse, FApiPartyPostInviteByIdFullResponse);
