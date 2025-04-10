
#pragma once

#include "CoreMinimal.h"
#include "BeamBackend/BeamBaseRequestInterface.h"
#include "BeamBackend/BeamRequestContext.h"
#include "BeamBackend/BeamErrorResponse.h"
#include "BeamBackend/BeamFullResponse.h"

#include "Serialization/BeamJsonUtils.h"
#include "BeamableCore/Public/AutoGen/UpdateParty.h"
#include "BeamableCore/Public/AutoGen/Party.h"

#include "ApiPartyPutMetadataByIdRequest.generated.h"

UCLASS(BlueprintType)
class BEAMABLECORE_API UApiPartyPutMetadataByIdRequest : public UObject, public IBeamBaseRequestInterface
{
	GENERATED_BODY()
	
public:

	// Path Params
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Id", Category="Beam")
	FGuid Id = {};
	
	// Query Params
	

	// Body Params
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="", Category="Beam")
	UUpdateParty* Body = {};

	// Beam Base Request Declaration
	UApiPartyPutMetadataByIdRequest() = default;

	virtual void BuildVerb(FString& VerbString) const override;
	virtual void BuildRoute(FString& RouteString) const override;
	virtual void BuildBody(FString& BodyString) const override;

	UFUNCTION(BlueprintPure, BlueprintInternalUseOnly, Category="Beam|Party|Utils|Make/Break", DisplayName="Make ApiPartyPutMetadataById",  meta=(DefaultToSelf="RequestOwner", AdvancedDisplay="_Restriction,_MaxSize,RequestOwner", AutoCreateRefTerm="CustomHeaders"))
	static UApiPartyPutMetadataByIdRequest* Make(FGuid _Id, FOptionalString _Restriction, FOptionalInt32 _MaxSize, UObject* RequestOwner, TMap<FString, FString> CustomHeaders);
};

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnApiPartyPutMetadataByIdSuccess, FBeamRequestContext, Context, UApiPartyPutMetadataByIdRequest*, Request, UParty*, Response);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnApiPartyPutMetadataByIdError, FBeamRequestContext, Context, UApiPartyPutMetadataByIdRequest*, Request, FBeamErrorResponse, Error);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnApiPartyPutMetadataByIdComplete, FBeamRequestContext, Context, UApiPartyPutMetadataByIdRequest*, Request);

using FApiPartyPutMetadataByIdFullResponse = FBeamFullResponse<UApiPartyPutMetadataByIdRequest*, UParty*>;
DECLARE_DELEGATE_OneParam(FOnApiPartyPutMetadataByIdFullResponse, FApiPartyPutMetadataByIdFullResponse);
