
#pragma once

#include "CoreMinimal.h"
#include "BeamBackend/BeamBaseRequestInterface.h"
#include "BeamBackend/BeamRequestContext.h"
#include "BeamBackend/BeamErrorResponse.h"
#include "BeamBackend/BeamFullResponse.h"

#include "Serialization/BeamJsonUtils.h"
#include "BeamableCore/Public/AutoGen/LeaveParty.h"
#include "BeamableCore/Public/AutoGen/ApiPartiesMembersDeletePartyResponse.h"

#include "DeleteMembersRequest.generated.h"

UCLASS(BlueprintType)
class BEAMABLECORE_API UDeleteMembersRequest : public UObject, public IBeamBaseRequestInterface
{
	GENERATED_BODY()
	
public:

	// Path Params
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Id", Category="Beam")
	FGuid Id = {};
	
	// Query Params
	

	// Body Params
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="", Category="Beam")
	ULeaveParty* Body = {};

	// Beam Base Request Declaration
	UDeleteMembersRequest() = default;

	virtual void BuildVerb(FString& VerbString) const override;
	virtual void BuildRoute(FString& RouteString) const override;
	virtual void BuildBody(FString& BodyString) const override;

	UFUNCTION(BlueprintPure, BlueprintInternalUseOnly, Category="Beam|Party|Utils|Make/Break", DisplayName="Make DeleteMembers",  meta=(DefaultToSelf="RequestOwner", AdvancedDisplay="_PlayerId,RequestOwner", AutoCreateRefTerm="CustomHeaders"))
	static UDeleteMembersRequest* Make(FGuid _Id, FOptionalBeamGamerTag _PlayerId, UObject* RequestOwner, TMap<FString, FString> CustomHeaders);
};

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnDeleteMembersSuccess, FBeamRequestContext, Context, UDeleteMembersRequest*, Request, UApiPartiesMembersDeletePartyResponse*, Response);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnDeleteMembersError, FBeamRequestContext, Context, UDeleteMembersRequest*, Request, FBeamErrorResponse, Error);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnDeleteMembersComplete, FBeamRequestContext, Context, UDeleteMembersRequest*, Request);

using FDeleteMembersFullResponse = FBeamFullResponse<UDeleteMembersRequest*, UApiPartiesMembersDeletePartyResponse*>;
DECLARE_DELEGATE_OneParam(FOnDeleteMembersFullResponse, FDeleteMembersFullResponse);
