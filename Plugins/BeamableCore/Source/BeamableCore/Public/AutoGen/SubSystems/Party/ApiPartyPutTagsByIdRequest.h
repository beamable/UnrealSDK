
#pragma once

#include "CoreMinimal.h"
#include "BeamBackend/BeamBaseRequestInterface.h"
#include "BeamBackend/BeamRequestContext.h"
#include "BeamBackend/BeamErrorResponse.h"
#include "BeamBackend/BeamFullResponse.h"

#include "Serialization/BeamJsonUtils.h"
#include "BeamableCore/Public/AutoGen/UpdatePartyTags.h"
#include "BeamableCore/Public/AutoGen/Party.h"

#include "ApiPartyPutTagsByIdRequest.generated.h"

UCLASS(BlueprintType)
class BEAMABLECORE_API UApiPartyPutTagsByIdRequest : public UObject, public IBeamBaseRequestInterface
{
	GENERATED_BODY()
	
public:

	// Path Params
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Id", Category="Beam")
	FGuid Id = {};
	
	// Query Params
	

	// Body Params
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="", Category="Beam")
	UUpdatePartyTags* Body = {};

	// Beam Base Request Declaration
	UApiPartyPutTagsByIdRequest() = default;

	virtual void BuildVerb(FString& VerbString) const override;
	virtual void BuildRoute(FString& RouteString) const override;
	virtual void BuildBody(FString& BodyString) const override;

	UFUNCTION(BlueprintPure, BlueprintInternalUseOnly, Category="Beam|Party|Utils|Make/Break", DisplayName="Make ApiPartyPutTagsById",  meta=(DefaultToSelf="RequestOwner", AdvancedDisplay="_PlayerId,_MemberTags,RequestOwner", AutoCreateRefTerm="CustomHeaders"))
	static UApiPartyPutTagsByIdRequest* Make(FGuid _Id, FOptionalString _PlayerId, FOptionalArrayOfBeamTag _MemberTags, UObject* RequestOwner, TMap<FString, FString> CustomHeaders);
};

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnApiPartyPutTagsByIdSuccess, FBeamRequestContext, Context, UApiPartyPutTagsByIdRequest*, Request, UParty*, Response);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnApiPartyPutTagsByIdError, FBeamRequestContext, Context, UApiPartyPutTagsByIdRequest*, Request, FBeamErrorResponse, Error);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnApiPartyPutTagsByIdComplete, FBeamRequestContext, Context, UApiPartyPutTagsByIdRequest*, Request);

using FApiPartyPutTagsByIdFullResponse = FBeamFullResponse<UApiPartyPutTagsByIdRequest*, UParty*>;
DECLARE_DELEGATE_OneParam(FOnApiPartyPutTagsByIdFullResponse, FApiPartyPutTagsByIdFullResponse);
